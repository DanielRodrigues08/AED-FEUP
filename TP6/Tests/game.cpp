#include "game.h"
#include <queue>
#include <sstream>

Circle::Circle(int p, bool s): points(p), state(s), nVisits(0) {}

int Circle::getPoints() const {
    return points;
}

bool Circle::getState() const {
    return state;
}

void Circle::changeState() {
    if (state == false)
        state = true;
    else
        state = false;
}

int Circle::getNVisits() const {
    return nVisits;
}

void Circle::incNVisits() {
    nVisits++;
}


BinaryTree<Circle>& Game::getGame() {
    return game;
}


//-----------------------------------------------------------------

//TODO

BinaryTree<Circle>* makeTree(int height, vector<int>& points, vector<bool>& states, int pos = 0){
    Circle *c = new Circle(points[pos], states[pos]);
    if(height==0)
        return new BinaryTree<Circle> (*c);
    return new BinaryTree<Circle>(*c, *makeTree(height-1, points, states, 2*pos+1), *makeTree(height-1, points, states, 2*pos+2));
}

Game::Game(int height, vector<int>& points, vector<bool>& states) {
    game = *(makeTree(height, points, states));
}

//TODO
int Game::play() {
	return 0;
}

//TODO
int Game::mostVisited() const {
	return 0;
}

