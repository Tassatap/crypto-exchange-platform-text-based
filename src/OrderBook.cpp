#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <iostream>
#include <algorithm>


/** construct reading a csv data file */
OrderBook::OrderBook(std::string filename)
{
	orders = CSVReader::readCSV(filename);
}
/** retrun vector of all know products in the data set */
std::vector <std::string> OrderBook::getKnowProducts()
{
	std::vector<std::string> products;

	std::map<std::string, bool> prodMap;

	for (OrderBookEntry& e : orders)
	{
		prodMap[e.product] = true;
	}

	for (auto const& e : prodMap)
	{
		products.push_back(e.first);
	}

	return products;
}
/** retrun vector of Orders aacording to the sens filters */
std::vector <OrderBookEntry> OrderBook::getOrders(OrderBookType type,
													std::string product,
													std::string timestamp)
{
	std::vector <OrderBookEntry> orders_sub;
	for (OrderBookEntry& e : orders)
	{
		if (e.orderType == type &&
			e.product == product &&
			e.timestamp == timestamp)
		{
			orders_sub.push_back(e);
		}
	}
	return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
	double max = orders[0].price;
	for (OrderBookEntry& e: orders)
	{
		if (e.price > max)max = e.price;
	}
	return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
	double min = orders[0].price;
	for (OrderBookEntry& e : orders)
	{
		if (e.price < min)min = e.price;
	}
	return min;
}

double OrderBook::getVWAP(std::vector<OrderBookEntry>& orders) {
	double totalPriceVolume = 0.0;
	double totalVolume = 0.0;

	for (OrderBookEntry& order : orders) {
		totalPriceVolume += order.price * order.amount;
		totalVolume += order.amount;
	}

	if (totalVolume == 0) return 0.0; // Avoid division by zero
	return totalPriceVolume / totalVolume;
}


std::string OrderBook::getEarliestTime()
{
	return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
	std::string next_timestamp= "";
	for (OrderBookEntry& e : orders)
	{
		if (e.timestamp > timestamp)
		{
			next_timestamp = e.timestamp;
			break;
		}
	}
	if (next_timestamp == "")
	{
		next_timestamp = orders[0].timestamp;
	}
	return next_timestamp;
}


void OrderBook::insertOrder(OrderBookEntry& order)
{
	orders.push_back(order);
	std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
	// asks = orderbook.asks in this timeframe
	std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask,
															product,
															timestamp);
	// bids = orderbook.bids in this timeframe
	std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid,
															product,
															timestamp);
	// sales = []
	std::vector<OrderBookEntry> sales;
	// sort asks lowest first
	std::sort(asks.begin(), asks.end(), OrderBookEntry::comparePriceAsc);
	// sort bids highest first
	std::sort(bids.begin(), bids.end(), OrderBookEntry::comparePriceDesc);
	// for ask in asks:
	for (OrderBookEntry& ask : asks)
	{
		// for bid in bids:
		for (OrderBookEntry& bid : bids)
		{
			// if bid.price >= ask.price # we have a match
			if (bid.price >= ask.price)
			{
				OrderBookEntry sale{ ask.price,0,timestamp, product, OrderBookType::asksale };
				 
				if (bid.username == "simuser")
				{
					sale.username = "simuser";
					sale.orderType = OrderBookType::bidsale;
				}
				if (ask.username == "simuser")
				{
					sale.username = "simuser";
					sale.orderType = OrderBookType::asksale;
				}
				// sale = new orderbookentry()
				// sale.price = ask.price
				// if bid.amount == ask.amount: # bid completely clears ask
				if (bid.amount == ask.amount)
				{
					sale.amount = ask.amount;
					sales.push_back(sale);
					bid.amount = 0; //# make sure the bid is not processed again
					// # can do no more with this ask
					// # go onto the next ask
					break;
				}

				// if bid.amount > ask.amount: # ask is completely gone slice the bid
				if (bid.amount > ask.amount)
				{
					// sale.amount = ask.amount
					sale.amount = ask.amount;
					// sales.append(sale)
					sales.push_back(sale);
					// # we adjust the bid in place
					// # so it can be used to process the next ask
					// bid.amount = bid.amount - ask.amount
					bid.amount = bid.amount - ask.amount;
					// # ask is completely gone, so go to next ask
					break;
				}

				// if bid.amount < ask.amount # bid is completely gone, slice the ask
				if (bid.amount < ask.amount&&
					bid.amount > 0)
				{
					// sale.amount = bid.amount
					sale.amount = ask.amount;
					// sales.append(sale)
					sales.push_back(sale);
					// # update the ask
					// # and allow further bids to process the remaining amount
					// ask.amount = ask.amount - bid.amount
					ask.amount = ask.amount - bid.amount;
					// bid.amount = 0 # make sure the bid is not processed again
					//2
					bid.amount = 0;
					// # some ask remains so go to the next bid
					continue;
					// return sales
				}
				
			}
		}
	}
	return sales;
}