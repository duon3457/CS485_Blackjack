//***************************************************************************
// File name:  Player.cpp
// Author:     Kitt Oster
// Date:       5/2/2021
// Class:      CS485
// Assignment: Blackjack
// Purpose:    Implement the player
//***************************************************************************

#include "Player.h"

Player::Player(std::shared_ptr<IMoveStrategy> pcMoveStrat,
               std::string name, Money cBank){
  mpcMoveStrat = pcMoveStrat;
  mName = name;
  mcBank = cBank;
  mcBet = -1;
  mCurrentHand = 0;
  mcHands = std::vector<Hand>(1);
}
  
bool Player::doneWithTurn(){
  return mCurrentHand == 0;
}

void Player::endTurn(){
  mbSplittable = true;
  mCurrentHand++;
  if(mCurrentHand >= getNumHands()){
    mCurrentHand = 0;
  }
}

void Player::receiveCard(Card cNewCard){
  receiveCard(cNewCard, mCurrentHand);
}

void Player::receiveCard(Card cNewCard, int handNum){
  mcHands.at(handNum).addCard(cNewCard);
}

bool Player::makeMove(std::shared_ptr<IMove>& pcMove,
                      std::vector<Card> tableCards){
  mbSplittable = false; //made a move this turn means they cannot split
  return mpcMoveStrat->determineMove(mcHands.at(mCurrentHand),
                                     pcMove, tableCards);
}

bool Player::makeBet(Money cAmount){
  if(mpcMoveStrat->determineBet(*this, cAmount)){
    mcBet = cAmount;
    return true;
  }
  else{
    return false;
  }
}

bool Player::isHuman(){
  return mpcMoveStrat->isHuman();
}

bool Player::trySplit(){
  if (canSplit())
  {
    mbSplittable = false; // can no longer split after splitting
  }
  mcHands.push_back(Hand());
  ++mCurrentHand;
  mcHands.at(mCurrentHand).addCard(mcHands.at(mCurrentHand - 1).split());
  //Need a split in hand.
  return true;
}

void Player::clearHand()
{
  Hand cHand;
  for (Hand h : mcHands)
  {
    h = cHand;
  }
}

bool Player::hasLost(){
  return mcBank.getAmount() > 0;
}

void Player::changeStrat(std::shared_ptr<IMoveStrategy> newStrat){
  mpcMoveStrat = newStrat;
}
  
std::vector<Card> Player::getFaceUpCards(){
  std::vector<Card> cFaceUpCards;
  std::vector<Card> cCardsFromThisHand;
  for(int i = 0; i < getNumHands(); i++){
    cCardsFromThisHand = mcHands.at(i).getFaceUpCards();
    cFaceUpCards.insert(cFaceUpCards.end(), cCardsFromThisHand.begin(),
                        cCardsFromThisHand.end());
  }
  return cFaceUpCards;
}

std::vector<Hand> Player::getHands(){
  return mcHands;
}

Hand& Player::getCurrentHand(){
  return mcHands.at(mCurrentHand);
}

int Player::getNumHands(){
  return (int) mcHands.size();
}

Money Player::getBank(){
  return mcBank;
}

Money Player::getBet(){
  return mcBet;
}

std::string Player::getName(){
  return mName;
}

void Player::setName(std::string name){
  mName = name;
}

void Player::setBalance(Money newBalance){
  mcBank = newBalance;
}

bool Player::isFullyBust(){
  for(int i = 0; i < getNumHands(); i++){
    if(mcHands[i].getHandValue() <= 21){
      return false;
    }
  }
  return true;
}

bool Player::readyToStart(){
  mbSplittable = true; //Start of turn, players can split
  return mpcMoveStrat != nullptr;
}

bool Player::canSplit()
{
    return mbSplittable;
}

void Player::endRound(int dealerVal){
  for(int i = 0; i < getNumHands(); i++){
    int sum = mcHands[i].getHandValue();

    if (sum == (int) Status::Blackjack)
    {
      mcBank = mcBank + mcBet * 1.5;
    }
    else if ((sum > dealerVal || dealerVal > (int)Status::Blackjack) && sum < (int) Status::Blackjack)
    {
      mcBank = mcBank + mcBet;
    }
    else{
      mcBank = mcBank - mcBet;
    }
  }
  
  clearHand();
  mcBet = Money(-1, mcBank.getCurrency());
  mCurrentHand = 0;
}
