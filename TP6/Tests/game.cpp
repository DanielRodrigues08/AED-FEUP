#include "game.h"
#include <queue>
#include <sstream>

ostream& operator<<(ostream &f, const Circle &circle) {
    f << circle.getPoints();
    return f;
}

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

BinaryTree<Circle> makeTree(int height, vector<int>& points, vector<bool>& states, int pos = 0){
    Circle c =  Circle(points[pos], states[pos]);
    if(height==0)
        return  BinaryTree<Circle> (c);
    return  BinaryTree<Circle>(c, makeTree(height-1, points, states, 2*pos+1), makeTree(height-1, points, states, 2*pos+2));
}

Game::Game(int height, vector<int>& points, vector<bool>& states) {
    game = makeTree(height, points, states);
}


//TODO
int Game::play() {
    int count = 0, pos = 0;
    BTItrLevel<Circle> it(game);
    while (!it.isAtEnd()){
        int n = 0;
        count = it.retrieve().getPoints();
        it.retrieve().incNVisits();

        if(it.retrieve().getState()){ // FALSE -> ESQUERDA(2*p + 1) ; TRUE -> DIREITA(2*p + 2)
            n = 2 * pos +2;
        }else{
            n = 2*pos +1;
        }
        it.retrieve().changeState();
        while (pos != n && !it.isAtEnd()){
            pos++;
            it.advance();
        }
    }
    return count;
}

//TODO
int Game::mostVisited() const {
	BTItrLevel<Circle> it(game);
    it.advance();
    int max = it.retrieve().getNVisits();
    it.advance();
    while(!it.isAtEnd()){
        if(it.retrieve().getNVisits()> max)
            max = it.retrieve().getNVisits();
        it.advance();
    }
    return max;
}

