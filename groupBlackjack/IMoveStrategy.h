//***************************************************************************
// File name:  IMoveStrategy.h
// Author:     Kitt Oster
// Date:       5/2/2021
// Class:      CS485
// Assignment: Blackjack
// Purpose:    Define the Move Strategy interface
//***************************************************************************

#pragma once

#include "Player.h"
#include "Hand.h"
#include "Card.h"
#include "IMove.h"
#include <vector>
#include <memory>

class IMoveStrategy {
public:
  virtual bool determineMove(Hand& cCurrentHand,
                             std::shared_ptr<IMove> pcCurrentMove,
                             std::vector<Card>& cTableCards) = 0;
  virtual bool determineBet(Player& player, Money& bet) = 0;
  virtual bool isHuman() = 0;
};
