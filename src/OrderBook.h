#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
private:
	std::vector <OrderBookEntry> orders;
public:
	/** construct reading a csv data file */
	OrderBook(std::string filename);
	/** retrun vector of all know products in the data set */
	std::vector<std::string> getKnowProducts();
	/** retrun vector of Orders aacording to the sens filters */
	std::vector<OrderBookEntry> getOrders(OrderBookType type,
											std::string product,
											std::string timestamp);
	/** retrun earliest time */
	std::string getEarliestTime();
	/** retrun next time */
	std::string getNextTime(std::string timestamp);

	void insertOrder(OrderBookEntry& order);

	std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

	static double getHighPrice(std::vector<OrderBookEntry>& orders);
	static double getLowPrice(std::vector<OrderBookEntry>& orders);
	static double getVWAP(std::vector<OrderBookEntry>& orders);
};

