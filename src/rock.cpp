#include "rock.hpp"

/**
 * @brief Retorna o maior intervalor entre o 1 e o 2.
 * 
 * @param i1 Intervalo 1
 * @param i2 Intervalo 2
 * @return Interval*
 */
Interval* RockFestival::biggerInterval(Interval* i1, Interval* i2){
    // verifica se a soma dos intervalos é a mesma
    if(scores[i1->right] - scores[i1->left-1] == scores[i2->right] - scores[i2->left-1]){
        // sendo a mesma, o que tem mais elementos é retornado e o outro é deletado
        if(i1->right - i1->left >= i2->right - i2->left){
            delete i2;
            return i1;
        }
        
        delete i1;
        return i2;
    }

    // no caso das somas serem diferentes
    // se a soma de i1 for maior que a de i2, deleta i2 e retorna i1
    if(scores[i1->right] - scores[i1->left-1] > scores[i2->right] - scores[i2->left-1]){
        delete i2;
        return i1;
    }

    // se a soma de i2 for maior ou igual a de i1, delete i1 e retorna i2
    delete i1;
    return i2;
}

/**
 * @brief Retorno o maior intervalo dentre os 3.
 * 
 * @param i1 Intervalo 1
 * @param i2 Intervalo 2
 * @param i3 Intervalo 3
 * @return Interval*
 */
Interval* RockFestival::biggerInterval(Interval* i1, Interval* i2, Interval* i3){
    return biggerInterval(biggerInterval(i1,i2),i3);
}

/**
 * @brief Constroi o objeto RockFestival::RockFestival
 * 
 * @param f Número de amigos
 * @param s Número de shows
 */
RockFestival::RockFestival(int f, int s){
    nFriends = f;
    nShows = s;
    scores = new double[s+1];
    for(int i=0; i < s+1; i++){
        scores[i] = 0;
    }
}

/**
 * @brief Faz a leitura das notas que cada amigo atribuiu para cada show.
 * 
 */
void RockFestival::readScores(){
    for(int i=0; i < nFriends; i++){
        double score;
        for(int j=1; j <= nShows; j++){
            std::cin >> score;
            scores[j] += score;
        }
    }
}

/**
 * @brief Transforma o vetor com a soma das notas em um vetor com as somas cumulativas das notas.
 * 
 */
void RockFestival::cumSumScores(){
    for(int i=1; i <= nShows; i++){
        scores[i] += scores[i-1];
    }
}

/**
 * @brief Encontra o subvetor máximo do vetor com as notas.
 * 
 * @param leftEdge 
 * @param rightEdge 
 * @return Interval* 
 */
Interval* RockFestival::bestInterval(int leftEdge, int rightEdge){
    // caso onde o subvetor analisado possui apenas um elemento
    if(leftEdge == rightEdge){
        return new Interval(leftEdge, rightEdge);
    }

    // calcula o número de elementos do subvetor e o índice do elemento do meio
    int numElements = rightEdge - leftEdge + 1;
    int middle = leftEdge + std::ceil(numElements/2);

    // caso onde o subvetor tem apenas dois elementos
    if(numElements == 2){
        // calcula a soma dos 3 possíveis subvetores que podem ser formados em um vetor de dois elementos
        double sum_left = scores[leftEdge] - scores[leftEdge - 1];
        double sum_right = scores[rightEdge] - scores[rightEdge - 1];
        double sum_lmr = scores[rightEdge] - scores[leftEdge - 1];

        // verifica qual o maior subvetor e retorna-o
        if(sum_lmr >= sum_left && sum_lmr >= sum_right){
            return new Interval(leftEdge, rightEdge);
        }

        if(sum_left >= sum_right){
            return new Interval(leftEdge,leftEdge);
        } else {
            return new Interval(rightEdge,rightEdge);
        }
    }
    
    // entra nesta parte do programa apenas se tem mais de 2 elementos
    // divide o vetor em 3 partes, uma que vai do começo até um elemento antes do meio, o elemento do meio
    // e outra que vai de um elemento após o meio até o fim
    // calcula o subvetor máximo da primeira e terceira partes
    Interval* left = bestInterval(leftEdge, middle-1);
    Interval* right = bestInterval(middle+1, rightEdge);

    // incializa limites do subvetor máximo que cruza o meio
    int crossLeft = middle, crossRight = middle;
    // variável auxiliar para computar o valor do subvetor máximo
    double aux = scores[middle] - scores[middle-1];
    
    // encontra o limite da esquerda do subvetor máximo que cruza o meio
    for(int i=middle-1; i >= leftEdge; i--){
        if(scores[middle] - scores[i-1] >= aux){
            aux = scores[middle] - scores[i-1];
            crossLeft = i;
        }
    }
    
    aux = scores[middle] - scores[middle-1];

    // encontra o limite da esquerda do subvetor máximo que cruza o meio
    for(int i=middle+1; i <= rightEdge; i++){
        if(scores[i] - scores[middle-1] >= aux){
            aux = scores[i] - scores[middle-1];
            crossRight = i;
        }
    }

    // cria o intervalo que cruza o meio
    Interval* cross = new Interval(crossLeft, crossRight);

    // retorna o maior dos 3 intervalos
    return biggerInterval(left, right, cross);
}

/**
 * @brief Destroi o objeto RockFestival::RockFestival
 * 
 */
RockFestival::~RockFestival(){
    delete[] scores;
}