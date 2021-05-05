#include "BlackjackTextUI.h"


BlackjackTextUI::BlackjackTextUI()
{
	mpcPresenter = new BlackjackPresenter(this);
}

BlackjackTextUI::BlackjackTextUI(int numPlayers)
{
	mpcPresenter = new BlackjackPresenter(this, numPlayers, 1);
}

BlackjackPresenter::~BlackjackPresenter()
{
	delete mpcView;
}

void BlackjackTextUI::newGame(int numPlayers)
{
	mpcPresenter->newGame(numPlayers);
}

void BlackjackTextUI::nextRound()
{
	mpcPresenter->nextRound();
}

void BlackjackTextUI::stand()
{
	mpcPresenter->stand();
}

void BlackjackTextUI::drawCard()
{
	mpcPresenter->draw();
}

void BlackjackTextUI::split()
{
	mpcPresenter->split();
}

void BlackjackTextUI::bet(long long amount)
{
	mpcPresenter->bet(amount);
}

void BlackjackTextUI::onStand()
{
	
}

void BlackjackTextUI::onDrawCard()
{

}

void BlackjackTextUI::onSplit()
{

}

void BlackjackTextUI::onBet(long long amount)
{

}

void BlackjackTextUI::render()
{

}


/****************  TextUI specific functions  ********************/

void BlackjackTextUI::printWelcome()
{
	std::cout << "***********************************\n";
	std::cout << "***    WELCOME TO BLACKJACK!    ***\n";
	std::cout << "***********************************\n";
}

void BlackjackTextUI::printHeader()
{
	std::cout << "***********************************\n";
	std::cout << "***          BLACKJACK          ***\n";
	std::cout << "***********************************\n";
}

void BlackjackTextUI::onGameStartup()
{
	const int MAX = 5, MIN = 1;
	int numPlayers = -1;

	std::cout << "Enter number of players (1-5): ";
	do
	{
		std::cin >> numPlayers;
	} while (numPlayers > MAX || numPlayers < MIN);

	std::cout << "Cool\n\n";

}

void BlackjackTextUI::playGame()
{

}