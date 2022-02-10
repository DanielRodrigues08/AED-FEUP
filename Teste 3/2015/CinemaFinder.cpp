/*
 * CinemaFinder.cpp
 */

#include "CinemaFinder.h"
#include "Cinema.h"
#include "Film.h"
#include <algorithm>

CinemaFinder::CinemaFinder() { }

CinemaFinder::~CinemaFinder() { }

void CinemaFinder::addFilm(Film *f1) {
	FilmPtr fp1;
	fp1.film = f1;
	films.insert(fp1);
}

void CinemaFinder::addCinema(const Cinema &c1)
{ cinemas.push(c1); }

tabHFilm CinemaFinder::getFilms() const
{ return films; }

priority_queue<Cinema> CinemaFinder::getCinemas() const
{ return cinemas; }


// TODO


//b1
list<string> CinemaFinder::filmsWithActor(string actorName) const {
    list<string> result;
    for(auto film : films){
        if(film.film->actorExists(actorName))
            result.push_back(film.film->getTitle());
    }
    return result;
}


//b2
void CinemaFinder::addActor(string filmTitle, string actorName) {
    for(auto film : films){
        if(film.film->getTitle()==filmTitle){
            film.film->addActor(actorName);
            return;
        }
    }

    Film* film = new Film(filmTitle);
    films.insert({film});
}


//c1
string CinemaFinder::nearestCinema(string service1) const {
    auto aux = cinemas;
    while(!aux.empty()) {
        if (aux.top().hasService(service1))
            return aux.top().getName();
        aux.pop();
    }
    return "";
}


//c2
void CinemaFinder::addServiceToNearestCinema(string service1, unsigned maxDistance) {
    if(cinemas.empty()) throw CinemaNotFound();
    if(cinemas.top().getDistance() >= maxDistance) throw CinemaNotFound();
    auto aux = cinemas.top();
    cinemas.pop();
    aux.addService(service1);
    cinemas.push(aux);
}
