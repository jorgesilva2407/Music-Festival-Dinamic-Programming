#include "rock.hpp"

Interval* RockFestival::maxInterval(Interval* i1, Interval* i2){
    if(scores[i1->right] - scores[i1->left-1] == scores[i2->right] - scores[i2->left-1]){
        
        if(i1->right - i1->left >= i2->right - i2->left){
            delete i2;
            return i1;
        }
        
        delete i1;
        return i2;
    }

    if(scores[i1->right] - scores[i1->left-1] > scores[i2->right] - scores[i2->left-1]){
        delete i2;
        return i1;
    }

    delete i1;
    return i2;
}

RockFestival::RockFestival(int f, int s){
    nFriends = f;
    nShows = s;
    scores = new double[s+1];
    for(int i=0; i < s+1; i++){
        scores[i] = 0;
    }
}

void RockFestival::readScores(){
    for(int i=0; i < nFriends; i++){
        double score;
        for(int j=1; j <= nShows; j++){
            std::cin >> score;
            scores[j] += score;
        }
    }
}

void RockFestival::cumSumScores(){
    for(int i=1; i <= nShows; i++){
        scores[i] += scores[i-1];
    }
}

Interval* RockFestival::bestInterval(int leftEdge, int rightEdge){
    if(leftEdge == rightEdge){
        return new Interval(leftEdge, rightEdge);
    }

    int numElements = rightEdge - leftEdge + 1;
    int middle = leftEdge + std::ceil(numElements/2);

    if(numElements == 2){
        double sum_left = scores[leftEdge] - scores[leftEdge - 1];
        double sum_right = scores[rightEdge] - scores[rightEdge - 1];
        double sum_lmr = scores[rightEdge] - scores[leftEdge - 1];

        if(sum_lmr >= sum_left && sum_lmr >= sum_right){
            return new Interval(leftEdge, rightEdge);
        }

        if(sum_left >= sum_right){
            return new Interval(leftEdge,leftEdge);
        } else {
            return new Interval(rightEdge,rightEdge);
        }
    }
    
    Interval* left = bestInterval(leftEdge, middle-1);
    Interval* right = bestInterval(middle+1, rightEdge);

    int crossLeft = middle, crossRight = middle;
    double aux = scores[middle] - scores[middle-1];

    for(int i=middle-1; i >= leftEdge; i--){
        if(scores[middle] - scores[i-1] >= aux){
            aux = scores[middle] - scores[i-1];
            crossLeft = i;
        }
    }

    aux = scores[middle] - scores[middle-1];

    for(int i=middle+1; i <= rightEdge; i++){
        if(scores[i] - scores[middle-1] >= aux){
            aux = scores[i] - scores[middle-1];
            crossRight = i;
        }
    }

    Interval* cross = new Interval(crossLeft, crossRight);

    return maxInterval(left, right, cross);
}

RockFestival::~RockFestival(){
    delete[] scores;
}