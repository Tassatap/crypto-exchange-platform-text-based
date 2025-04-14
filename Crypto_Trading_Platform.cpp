#include <iostream>
#include <string>
#include <vector>

enum class OrderBookType { bid, ask };

class OrderBookEntry
{
public:
    OrderBookEntry(double price,
                   double amount,
                   std::string timestamp,
                   std::string product,
                   OrderBookType orderType)
    : price(price),
      amount(amount),
      timestamp(timestamp),
      product(product),
      orderType(orderType)
    {
        //this->price = price;
        //this->amount = amount;
        //this->timestamp = timestamp;
        //this->product = product;
        //this->orderType = orderType;
    }

    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
};


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

int main()
{
    

    //double price = 5319.450228;
    //double amount = 0.00020075;
    //std::string timestamp{ "2020/03/17 17:01:24.884492" };
    //std::string product{ "BTC/UTC" };
    //OrderBookType orderType = OrderBookType::bid;

    std::vector<double> prices;
    std::vector<double> amounts;
    std::vector<std::string> timestamps;
    std::vector<std::string> products;
    std::vector<OrderBookType> orderType;

    prices.push_back(5319.450228);
    amounts.push_back(0.00020075);
    timestamps.push_back("2020/03/17 17:01:24.884492");
    products.push_back("BTC/UTC");
    orderType.push_back(OrderBookType::bid);

    while (false)
    {
        printMenu();
        int userOption = getUserOption();
        processUserOption(userOption);
    }

    std::vector<OrderBookEntry> orders;


    OrderBookEntry order1(1000, 
                        0.02, 
                        "2020/03/17 17:01:24.884492", 
                        "BTC/UTC", 
                        OrderBookType::bid);

    OrderBookEntry order2(3000,
                        0.02,
                        "2020/03/17 17:01:24.884492",
                        "BTC/UTC",
                        OrderBookType::bid);

    //order1.price = 100000;
    //order1.amount = 0.02;
    //order1.timestamp = "2020/03/17 17:01:24.884492";
    //order1.product = "BTC/UTC";
    //order1.orderType = OrderBookType::bid;

    orders.push_back(OrderBookEntry(1000,
                                    0.02,
                                    "2020/03/17 17:01:24.884492",
                                    "BTC/UTC",
                                    OrderBookType::bid));
    orders.push_back(OrderBookEntry(3000,
                                    0.02,
                                    "2020/03/17 17:01:24.884492",
                                    "BTC/UTC",
                                    OrderBookType::bid));

    std::cout << "The price is " << orders[1].price << std::endl;
    
    for (OrderBookEntry& order : orders)
    {
        std::cout << "The price is " << order.price << std::endl;
    }

    for (unsigned int i = 0; i < orders.size() ; ++i)
    {
        std::cout << "The price is " << orders[i].price << std::endl;
    }

    return 0;
}

