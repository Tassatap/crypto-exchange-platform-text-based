#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"

void printMenu()
{
    // 1 print help 
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats 
    std::cout << "2: Print exchange stats " << std::endl;
    // 3 make an offer 
    std::cout << "3: Make an offer  " << std::endl;
    // 4 make a bid 
    std::cout << "4: Make a bid  " << std::endl;
    // 5 print wallet 
    std::cout << "5: Print wallet " << std::endl;
    // 6 continue
    std::cout << "6: Continue " << std::endl;
    std::cout << "===============================  " << std::endl;
    std::cout << "Please enter an option(1 - 6) : " << std::endl;
}

void printHelp()
{
    std::cout << "Help - your aim is to make money." << std::endl;
    std::cout << "Analyse the market and make bids" << std::endl;
    std::cout << "and offers. " << std::endl;
}

void printMarketStats()
{
    std::cout << "Market looks good " << std::endl;
}
void enterOffer()
{
    std::cout << "Make an offer - enter the amount" << std::endl;
}
void enterBid()
{
    std::cout << "Make a bid - enter the amount" << std::endl;
}
void printWallet()
{
    std::cout << "Yout wallet is empty" << std::endl;
}
void gotoNextTimeFrame()
{
    std::cout << "Going to next tiem frame" << std::endl;
}
int getUserOption()
{
    int userOption;
    std::cin >> userOption;
    std::cout << "Please enter an option(1 - 6) : " << std::endl;
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void processUserOption(int userOption)
{
    if (userOption < 1 or userOption > 6)
    {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    if (userOption == 1)
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printMarketStats();
    }
    if (userOption == 3)
    {
        enterOffer();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        gotoNextTimeFrame();
    }
}


double computeAveragePrice(std::vector<OrderBookEntry>& entries)
{
    double sum = 0;
    for (OrderBookEntry& order : entries)
    {
        sum = order.price + sum;
    }
    return sum / entries.size();
}

double computeLowPrice(std::vector<OrderBookEntry>& entries)
{
    double LowPrice = entries[0].price;
    for (OrderBookEntry& order : entries)
    {
        if (order.price < LowPrice)
        {
            LowPrice = order.price;
        }
        else
        {
            LowPrice = LowPrice;
        }
    }
    return LowPrice;
}

double computeHighPrice(std::vector<OrderBookEntry>& entries)
{
    double highPrice = entries[0].price;
    for (OrderBookEntry& order : entries)
    {
        if (order.price > highPrice)
        {
            highPrice = order.price;
        }
        else
        {
            highPrice = highPrice;
        }
    }
    return highPrice;
    return 0;
}

double computePriceSpread(std::vector<OrderBookEntry>& entries)
{
    double PriceSpread = computeHighPrice(entries) - computeLowPrice(entries);
    return PriceSpread;
}

int main()
{
    while (false) //we don't need this for now.
    {
        printMenu();
        int userOption = getUserOption();
        processUserOption(userOption);
    }

    std::vector<OrderBookEntry> orders;

    orders.push_back(OrderBookEntry(2000,
                                    0.02,
                                    "2020/03/17 17:01:24.884492",
                                    "BTC/UTC",
                                    OrderBookType::bid));
    orders.push_back(OrderBookEntry(3000,
                                    0.02,
                                    "2020/03/17 17:01:24.884492",
                                    "BTC/UTC",
                                    OrderBookType::bid));
    orders.push_back(OrderBookEntry(8000,
                                    0.02,
                                    "2020/03/17 17:01:24.884492",
                                    "BTC/UTC",
                                    OrderBookType::bid));
    orders.push_back(OrderBookEntry(1800,
                                    0.02,
                                    "2020/03/17 17:01:24.884492",
                                    "BTC/UTC",
                                    OrderBookType::bid));
    orders.push_back(OrderBookEntry(10000,
                                    0.02,
                                    "2020/03/17 17:01:24.884492",
                                    "BTC/UTC",
                                    OrderBookType::bid));

    for (unsigned int i = 0; i < orders.size(); ++i)
    {
        std::cout << "The price " << i + 1 << " = " << orders[i].price << std::endl;
    }

    double AveragePrice = computeAveragePrice(orders);
    std::cout << "AveragePrice = " << AveragePrice << std::endl;
    double LowPrice = computeLowPrice(orders);
    std::cout << "LowPrice = " << LowPrice << std::endl;
    double HighPrice = computeHighPrice(orders);
    std::cout << "HighPrice = " << HighPrice << std::endl;
    double PriceSpread = computePriceSpread(orders);
    std::cout << "PriceSpread = " << PriceSpread << std::endl;
    return 0;
}

