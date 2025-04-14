#include <iostream>

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
    while (true)
    {
        printMenu();
        int userOption = getUserOption();
        processUserOption(userOption);
    }
    return 0;
}

