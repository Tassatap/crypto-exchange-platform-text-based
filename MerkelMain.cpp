#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    int input;
    while (true)
    {
        loadOrderbook();
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::loadOrderbook()
{
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

}

void MerkelMain::printMenu()
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

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money." << std::endl;
    std::cout << "Analyse the market and make bids" << std::endl;
    std::cout << "and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{
    std::cout << "OrderBook contains : " << orders.size() << " entries" << std::endl;
}
void MerkelMain::enterOffer()
{
    std::cout << "Make an offer - enter the amount" << std::endl;
}
void MerkelMain::enterBid()
{
    std::cout << "Make a bid - enter the amount" << std::endl;
}
void MerkelMain::printWallet()
{
    std::cout << "Yout wallet is empty" << std::endl;
}
void MerkelMain::gotoNextTimeFrame()
{
    std::cout << "Going to next tiem frame" << std::endl;
}
int MerkelMain::getUserOption()
{
    int userOption;
    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
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

double MerkelMain::computeAveragePrice(std::vector<OrderBookEntry>& entries)
{
    double sum = 0;
    for (OrderBookEntry& order : entries)
    {
        sum = order.price + sum;
    }
    return sum / entries.size();
}

double MerkelMain::computeLowPrice(std::vector<OrderBookEntry>& entries)
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

double MerkelMain::computeHighPrice(std::vector<OrderBookEntry>& entries)
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

double MerkelMain::computePriceSpread(std::vector<OrderBookEntry>& entries)
{
    double PriceSpread = MerkelMain::computeHighPrice(entries) - MerkelMain::computeLowPrice(entries);
    return PriceSpread;
}

