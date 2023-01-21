#ifndef ROCK_H_
#define ROCK_H_

#include <iostream>
#include <cmath>

struct Interval{
    int left, right;
    Interval(int l, int r){left=l; right=r;}
};


class RockFestival{
    int nFriends, nShows;
    double* scores;
    Interval* biggerInterval(Interval* i1, Interval* i2);
    Interval* biggerInterval(Interval* i1, Interval* i2, Interval* i3);

    public:
        RockFestival(int f, int s);
        void readScores();
        void cumSumScores();
        Interval* bestInterval(int leftEdge, int rightEdge);
        ~RockFestival();
};

#endif