#include <iostream>
#include "rock.hpp"

int main(){
    while(true){
        int f, s;
        std::cin >> f >> s;
        
        if(!f && !s) break;
        
        RockFestival rockInRio(f,s);
        rockInRio.readScores();
        rockInRio.cumSumScores();
        Interval* best = rockInRio.bestInterval(1,s);
        std::cout << best->left << " " << best->right << std::endl;
        delete best;
    }
}