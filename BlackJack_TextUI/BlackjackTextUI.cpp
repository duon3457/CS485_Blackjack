#include "BlackjackTextUI.h"


BlackjackTextUI::BlackjackTextUI()
{
	mpcPresenter = new BlackjackPresenter(this);
}

BlackjackTextUI::BlackjackTextUI(int numPlayers)
{
	mpcPresenter = new BlackjackPresenter(this, numPlayers, 1);
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

void BlackjackTextUI::printGameState()
{
	std::vector<std::vector<std::string>> cards = mpcPresenter->getOpponentCards();
	std::vector<std::string> dealerCards = mpcPresenter->getDealerCards();
	std::cout << std::endl;

	// print opponents cards
	for (int i = 0; i < mpcPresenter->getNumPlayers() - 1; i++)
	{
		std::cout << "Opponent " << i + 1 << " cards: ";
		for (std::string card : cards[i])
		{
			std::cout << card << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// Print Dealer cards
	std::cout << "Dealer cards: ";
	for (std::string card : dealerCards)
	{
		std::cout << card << " ";
	}
	std::cout << std::endl << std::endl;

	// Print your bank
	std::cout << "Chips available: " << mpcPresenter->getBalance() << std::endl;
}

void BlackjackTextUI::printPlayerCards()
{
	std::cout << "Your cards: ";
	for (std::string str : mpcPresenter->getCurrentPlayerHand())
	{
		std::cout << str << " ";
	}
	std::cout << std::endl << std::endl;
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
	mpcPresenter->newGame(numPlayers);

	for (int i = 0; i < numPlayers - 1; i++)
	{
		mpcPresenter->setPlayerType("Card Counter", i);
	}
	mpcPresenter->setPlayerType("Human", numPlayers - 1);

	mpcPresenter->newGame();
}

void BlackjackTextUI::playGame()
{
	const int STAND = 1;
	const int DRAW = 2;
	const int SPLIT = 3;
	const int QUIT = 4;
	const bool STOP_PLAYING = false;
	const std::vector<std::string> EMPTY_HAND;

	bool bKeepPlaying = true;
	long long betAmount = -1;
	int turns = 0;
	int move;

	while (bKeepPlaying)
	{
		move = -1;
		mcHand = EMPTY_HAND;		

		// Print state of the game and options
		system("cls");
		printHeader();

		// Do betting
		mpcPresenter->doCPUBets();
		std::cout << "\nCurrent balance: " << mpcPresenter->getBalance();
		std::cout << "\nHow much would you like to bet? ";
		do
		{
			//mpcPresenter->doCPUBets();
			std::cin >> betAmount;

		} while (!mpcPresenter->bet(betAmount));
		mpcPresenter->doCPUBets();

		system("cls");
		printHeader();
		printGameState();

		// Prints the move options if the human's turn is still going
		while (/*move != STAND &&*/ mpcPresenter->roundOngoing() && move != QUIT)
		{
			mpcPresenter->doCPUMoves();

			printPlayerCards();
			
			// Sets the move to stand automatically if bust
			if (Status::Bust == mpcPresenter->result())
			{
				move = STAND;
			}

      if (move != STAND)
      {
        move = SPLIT;
        std::cout << "OPTIONS: \n(1) Stand \n(2) Draw\n";
        if (mpcPresenter->canSplit())
        {
          std::cout << "(3) Split\n";
        }
        std::cout << "(4) Quit\n";

				do
				{
					std::cout << "Enter your move: ";
					std::cin >> move;
				} while ((move == SPLIT && !mpcPresenter->canSplit()) || (move > QUIT || move < STAND));
				std::cout << std::endl;
			}

			// Executes selected move
			switch (move)
			{
			case STAND:
				mpcPresenter->stand();
				break;

			case DRAW:
				mpcPresenter->draw();
				break;

			case SPLIT:
				mcHand.push_back(mpcPresenter->getCurrentPlayerHand()[0]);// TODO
				mpcPresenter->split();
				break;
			case QUIT:
				bKeepPlaying = STOP_PLAYING;
				break;
			}

      turns++;
		}
    
		mpcPresenter->doCPUMoves();
    printEndRoundScreen();
		mpcPresenter->nextRound();   
	}
}


void BlackjackTextUI::printEndRoundScreen(){
	std::string something = "";
	std::vector<std::string> hand = mpcPresenter->getCurrentPlayerHand();
  std::vector<std::vector<std::string>> cards = mpcPresenter->getOpponentCards();
	int numPlayers = mpcPresenter->getNumPlayers();
	std::vector<std::string> dealerCards = mpcPresenter->getDealerCards();

  std::vector<Status> endStatuses = mpcPresenter->endRound();

	long long balance = mpcPresenter->getBalance();

	system("cls");
	printHeader();
	std::cout << "\nRound results:\n\n";

  // Print your bank
  std::cout << "Chips: " << balance << std::endl;

  // Print your cards
  std::cout << "Your cards: ";
  for (std::string str : hand)
  {
    std::cout << str << " ";
  }  
  std::cout << std::endl << std::endl;

  // print opponents cards
  for (int i = 0; i < numPlayers - 1; i++)
  {
    std::cout << "Opponent " << i + 1 << " cards: ";
    for (std::string card : cards[i])
    {
      std::cout << card << " ";
    }
    std::cout << std::endl;
  }
	std::cout << std::endl;

	// Print Dealer cards
	std::cout << "Dealer cards: ";
	for (std::string card : dealerCards)
	{
		std::cout << card << " ";
	}
	std::cout << std::endl;

	std::cout << "\nEnter literally anything to continue: ";
	std::cin >> something;
}
