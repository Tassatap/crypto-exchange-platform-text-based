#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();
    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    // 1 print help 
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats 
    std::cout << "2: Print exchange stats " << std::endl;
    // 3 make an offer 
    std::cout << "3: Make an ask  " << std::endl;
    // 4 make a bid 
    std::cout << "4: Make a bid  " << std::endl;
    // 5 print wallet 
    std::cout << "5: Print wallet " << std::endl;
    // 6 continue
    std::cout << "6: Continue " << std::endl;

    std::cout << "===============================  " << std::endl;

    std::cout << "Current Time : " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money." << std::endl;
    std::cout << "Analyse the market and make bids" << std::endl;
    std::cout << "and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (std::string const& p : orderBook.getKnowProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entriesAsk = orderBook.getOrders(OrderBookType::ask,
                                                                    p, currentTime);
        std::cout << "Asks seen: " << entriesAsk.size() << std::endl;
        std::cout << "Max asks: " << OrderBook::getHighPrice(entriesAsk) << std::endl;
        std::cout << "Min asks: " << OrderBook::getLowPrice(entriesAsk) << std::endl;
        std::cout << "VWAP: " << OrderBook::getVWAP(entriesAsk) << std::endl;

        std::vector<OrderBookEntry> entriesBid = orderBook.getOrders(OrderBookType::bid,
            p, currentTime);
        std::cout << "Bids seen: " << entriesBid.size() << std::endl;
        std::cout << "Max Bids: " << OrderBook::getHighPrice(entriesBid) << std::endl;
        std::cout << "Min Bids: " << OrderBook::getLowPrice(entriesBid) << std::endl;
        std::cout << "VWAP: " << OrderBook::getVWAP(entriesBid) << std::endl;
    }
}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product,price,amount eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad input!" << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask
            );
            orderBook.insertOrder(obe);
        }
        catch (const std::exception& e)
        {
            std::cout << "MerkelMain::enterAsk Bad input " << std::endl;
        }
    }


    std::cout << "You typed: " << input << std::endl;
}
void MerkelMain::enterBid()
{
    std::cout << "Make a bid - enter the amount: product,price,amount eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input!" << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid
            );
            orderBook.insertOrder(obe);
        }
        catch (const std::exception& e)
        {
            std::cout << "MerkelMain::enterBid Bad input " << std::endl;
        }



        std::cout << "You typed: " << input << std::endl;
    }
}
void MerkelMain::printWallet()
{
    std::cout << "Yout wallet is empty" << std::endl;
}
void MerkelMain::gotoNextTimeFrame()
{
    std::cout << "Going to next tiem frame" << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
    currentTime = orderBook.getNextTime(currentTime);
    std::cout << "Sales: " << sales.size() << std::endl;
    for (OrderBookEntry& sale : sales)
    {
        std::cout << "Sales amount: " << sale.price << " amount " << sale.amount << std::endl;
    }
}

int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    std::cout << "Please enter an option(1 - 6) : " << std::endl;
    std::getline(std::cin, line);
    try {
        userOption = std::stoi(line);
    }
    catch (const std::exception& e)
    {

    }

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
        enterAsk();
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

