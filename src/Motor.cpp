/*****************************************************************
 * Motor.cpp
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/

#include <iostream>
#include <string>

#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <pthread.h>

#include "Motor.h"

using namespace std;

void *moveAll(void *t_data) {
    //cout << "MoveAll" <<endl;

    if (t_data != NULL) {
        Motor *m = (Motor *) t_data;
        while (!m->gameFinished()) {
            //cout << "not Finish"<< endl;

            for (int i = 0; i < m->getListPlayers().size(); i++) {
                m->avancer(i, m->getListPlayers().at(i));
            }
            //m->printAllPlayers();
            for (int i = 0; i < m->getListPlayers().size(); i++) {
                Character p = m->getListPlayers()[i];
                if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 67) {
                    m->removePlayer(i, p);
                }
            }
        }
    } else {
        cerr << "error in thread" << endl;
    }

}

void *moveNO(void *t_data) {
    //cout << "MoveNO" <<endl;
    if (t_data != NULL) {
        Motor *m = (Motor *) t_data;
        if (m->gameFinished())
            cout << "NOgameFinished" << endl;
        while (!m->gameFinished()) {
            cout << "testNO" << endl;
            for (int i = 0; i < m->getListPlayers().size(); i++) {
                Character p = m->getListPlayers()[i];
                if (p.getX() < 256 && p.getY() < 64 && !p.hasFinished()) {
                    //cout << "testNO" << endl;
                    if (p.getX() <= 0 && p.getY() >= 60) {
                        m->removePlayer(i, p);
                        cout << "teeeeee" << endl;
                    } else {
                        m->avancer(i, p);
                    }
                }
            }
        }
    } else {
        cerr << "error in thread" << endl;
    }
}

void *moveNE(void *t_data) {
    //cout << "MoveNE" <<endl;
    if (t_data != NULL) {
        Motor *m = (Motor *) t_data;
        if (m->gameFinished())
            cout << "NEgameFinished" << endl;
        while (!m->gameFinished()) {
            cout << "testNE" << endl;
            for (int i = 0; i < m->getListPlayers().size(); i++) {
                Character p = m->getListPlayers()[i];
                if (p.getX() >= 255 && p.getY() < 64 && !p.hasFinished()) {
                    m->avancer(i, p);
                }
            }
        }
    } else {
        cerr << "error in thread" << endl;
    }
}

void *moveSO(void *t_data) {
    //cout << "MoveSO" <<endl;
    if (t_data != NULL) {
        Motor *m = (Motor *) t_data;
        if (m->gameFinished())
            cout << "SOgameFinished" << endl;
        while (!m->gameFinished()) {
            cout << "test MoveSO" << endl;
            for (int i = 0; i < m->getListPlayers().size(); i++) {
                Character p = m->getListPlayers()[i];
                if (p.getX() < 256 && p.getY() > 63 && !p.hasFinished()) {
                    if (p.getX() <= 0 && p.getY() <= 67) {
                        m->removePlayer(i, p);
                    } else {
                        m->avancer(i, p);
                    }
                }
            }
        }
    } else {
        cerr << "error in thread" << endl;
    }
}

void *moveSE(void *t_data) {
    //cout << "MoveSE" <<endl;
    if (t_data != NULL) {
        Motor *m = (Motor *) t_data;
        if (m->gameFinished())
            cout << "SEgameFinished" << endl;
        while (!m->gameFinished()) {
            cout << "test MoveSE" << endl;
            for (int i = 0; i < m->getListPlayers().size(); i++) {
                Character p = m->getListPlayers()[i];
                if (p.getX() >= 255 && p.getY() > 63 && !p.hasFinished()) {
                    m->avancer(i, p);
                }
            }
        }
    } else {
        cerr << "error in thread" << endl;
    }
}

void *movePerson(void *t_data) {
    cout << "movePerson" << endl;
    if (t_data != NULL) {
        thread_Struct *data = (struct thread_Struct *) t_data;
        Motor *m = (data->m);
        int index(data->index);
        Character c = m->getListPlayers()[index];
        while (!(c.getY() >= 60 && c.getY() <= 67 && c.getX() == 0) && !c.hasFinished()) {
            m->avancer(index, c);
        }
        int nbp = m->nbP();
        cout <<  nbp << endl;
        if (c.getX() <= 0 && c.getY() <= 67 ) {
            m->removePlayer(index, c);
        }
    }
}


Motor::Motor(int nbPl, int nbTd, bool nbMs) {
    nbPlayers = nbPl;
    nbThreads = nbTd;
    needMeasures = nbMs;
    plateau = Plateau();
    /*if(needMeasures){

     for(int i=0; i<5; i++){
      time_t startTime;
      time(&startTime);

       this->createPlayers();
       //struct rusage r_usage;
       clock_t start_t;
       clock_t end_t;


       start_t = clock();

       this->run();


       end_t = clock ();
       //t2 = time(0);


       measuresTab[i] = ((float)(end_t - start_t))/CLOCKS_PER_SEC;
       time_t endTime;
        time(&endTime);

        timeMeasures[i] = difftime(endTime,startTime);
       //time = time + (t2 - t1);

       //getrusage(RUSAGE_SELF,&r_usage);
       //maxResident = maxResident + r_usage.ru_maxrss;

       //printf("Memory usage = %ld\n",maxResident);
       //printf("Memory usage = %ld\n",r_usage.ru_maxrss);
       //printf("AVEC TIME ON OBTIENT = %ld\n",(t2 - t1));
       //printf ("Temps d'execution pour %d---> %f.\n\n", i+1, measuresTab[i]);
     }

     float max = measuresTab[0];
     float min = measuresTab[0];
     float moyenne;
     int indiceMax = 0;
     int indiceMin = 0;

     float maxTime = timeMeasures[0];
     float minTime = timeMeasures[0];
     double moyenneTime;
     int indiceMaxTime = 0;
     int indiceMinTime = 0;

     for(int i=1; i<5; i++){
        if(max < measuresTab[i])
          indiceMax = i;
        if(min > measuresTab[i])
          indiceMin = i;

        if(maxTime < timeMeasures[i])
          indiceMaxTime = i;
        if(minTime > timeMeasures[i])
          indiceMinTime = i;
       //moyenne = moyenne + measuresTab[i];
       //printf("%f\n", measuresTab[i]);
     }

     for(int i=0; i<5; i++){
        if(i!=indiceMax && i!=indiceMin)
          moyenne = moyenne + measuresTab[i];

        if(i!=indiceMaxTime && i!=indiceMinTime)
          moyenneTime = moyenneTime + timeMeasures[i];
     }

     //printf("TOTAL DES TEMPS---->%f\n", moyenne);
     moyenne = moyenne / 3;
     moyenneTime = moyenneTime / 3;
     //maxResident = maxResident / 3;

     //printf ("Temps d'execution moyen ---> %f et une empreinte maximale moyenne de %ld.\n", moyenne, maxResident);
     printf ("Temps d'execution moyen ---> %f.\n", moyenne);
     printf ("Temps de réponse moyen ---> %f.\n", moyenneTime);

     //printf("Le temps moyen de calcul pour le programme est de %lf\n", moyenne);
   }
   else{*/
    this->createPlayers();
    this->run();
    //this->test();
    //}
}

void Motor::run() {

    if (nbThreads == 0) { // On peut enlever ce thread et lancer dans le main
        pthread_t t0;
        pthread_create(&t0, NULL, moveAll, this);
        pthread_join(t0, NULL);
    }

    if (nbThreads == 1) {
        pthread_t t0;
        pthread_t t1;
        pthread_t t2;
        pthread_t t3;
        pthread_create(&t0, NULL, moveNO, this); //s'occupe de la partie nord ouest
        pthread_create(&t1, NULL, moveNE, this); //s'occupe de la partie nord est
        pthread_create(&t2, NULL, moveSO, this); //s'occupe de la partie sud ouest
        pthread_create(&t3, NULL, moveSE, this); //s'occupe de la partie sud est
        pthread_join(t0, NULL);
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        pthread_join(t3, NULL);
    }

    if (nbThreads == 2) {
        Character c(0, 0); //Just to init struct
        struct thread_Struct data = {this, c, 0};
        vector<pthread_t> allThreads;
        for (int i = 0; i < getListPlayers().size(); i++) {
            pthread_t tmp;
            data.m = this;
            data.c = getListPlayers()[i];
            data.index = i;
            pthread_create(&tmp, NULL, movePerson, &data);
            allThreads.push_back(tmp);
        }
        for (int i = 0; i < allThreads.size(); i++) {
            //cin.get();
            pthread_join(allThreads[i], NULL);
        }
    }

}

void Motor::createPlayers() {
    this->removeAllPlayers();
    for (int i = 0; i < this->nbPlayers; i++) {
        int randX = rand() % 512;
        int randY = rand() % 128;
        //cout << "X : " << randX << " Y : " << randY << endl;
        while (!plateau.addPlayer(randX, randY)) {
            randX = rand() % 512;
            randY = rand() % 128;
            //cout << "X : " << randX << " Y : " << randY << endl;
        }
        Character c(randX, randY);
        listPlayers.push_back(c);

    }
}

void Motor::removePlayer(int i, Character &c) {
    c.finish();
    this->listPlayers[i] = c;
    //this->listPlayers.erase(this->listPlayers.begin() + i);
    this->plateau.removePlayer(c.getX(), c.getY());
}


void Motor::printAllPlayers() {
    for (vector<Character>::iterator it = this->listPlayers.begin(); it != this->listPlayers.end(); ++it)
        it->print();
}

int Motor::nbP(){
    int j=0;
    for(int i= 0 ; i< getListPlayers().size();i++){
        Character c = getListPlayers()[i];
        if(!c.hasFinished())
            j++;
    }
    return j;
}

bool Motor::gameFinished() {
    //cout << "nb" <<this->listPlayers.size() << endl;
    for(int i= 0 ; i< getListPlayers().size();i++){
        Character c = getListPlayers()[i];
        if(!c.hasFinished())
            return false;
    }
    return true;
    //return this->listPlayers.size() == 0;
}

vector<Character> Motor::getListPlayers() {
    return this->listPlayers;
}

void Motor::removeAllPlayers() {
    this->listPlayers.clear();
}

void Motor::setPlayer(int i, Character c) {
    listPlayers[i] = c;
}

void Motor::avancer(int index, Character &p) {
    //removePlayer(index,p);
    //cout << "before" << endl;
    //p.print();

    Point pt = changePosition(p.getX(), p.getY());

    cout << index << " change from "<< p.getX() << "," << p.getY() << "to ";
    pt.print();
    cout <<  endl;

    if (this->plateau.movePlayer(p.getX(), p.getY(), pt.getX(), pt.getY())) {
        p.move(pt);
    }
    //p.print();
    listPlayers[index] = p;
    //this->plateau.printAllPlayersCases();*/
}

Point Motor::changePosition(int x, int y) {
    //return Point(0,64);
    int LockD = 0;
    int LockH = 0;
    int LockV = 0;

    if ((y < (plateau.getHeigth() - plateau.getOpenHeigthWall1()) / 2 && x < plateau.getWidthLastWall())
        || (y < (plateau.getHeigth() - plateau.getOpenHeigthWall2()) / 2 && x >= plateau.getWidthLastWall())) {
        //if((y < 60 && x < 128) || (y < 56 && x > 127)){
        for (int i = 0; i < 5; i++) {
            if (plateau.check(x - 1, y + i)) {
                if (i != 4)
                    LockH = 1;
                if (i != 0)
                    LockD = 1;
            }
        }
        for (int i = 0; i < 4; i++) {
            if (plateau.check(x + i, y + 4)) {
                LockV = 1;
                if (i != 3)
                    LockD = 1;
            }
        }
        if (LockD == 0) {
            return Point(x - 1, y + 1);
        } else if (LockH == 0) {
            return Point(x - 1, y);
        } else if (LockV == 0) {
            return Point(x, y + 1);
        } else {
            return Point(x, y);
        }
    } else if ((y >= ((plateau.getHeigth() + plateau.getOpenHeigthWall1()) / 2) - 3 && x < plateau.getWidthLastWall())
               || (y >= ((plateau.getHeigth() + plateau.getOpenHeigthWall2()) / 2) - 3 &&
                   x >= plateau.getWidthLastWall())) {


        for (int i = 0; i < 5; i++) {
            if (plateau.check(x - 1, y - i + 3)) {
                if (i != 4)
                    LockH = 1;
                if (i != 0)
                    LockD = 1;
            }
        }
        for (int i = 0; i < 4; i++) {
            if (plateau.check(x + i, y - 1)) {
                LockV = 1;
                if (i != 3)
                    LockD = 1;
            }
        }
        if (LockD == 0) {
            return Point(x - 1, y - 1);
        } else if (LockH == 0) {
            return Point(x - 1, y);
        } else if (LockV == 0) {
            return Point(x, y - 1);
        } else {
            return Point(x, y);
        }
    } else {
        for (int i = 0; i < 4; i++) {
            if (plateau.check(x - 1, y + i)) {
                LockH = 1;
            }
        }
        if (LockH == 0) {
            return Point(x - 1, y);
        } else {
            return Point(x, y);
        }
    }
    //*/
}

void Motor::test() {

    Point pt  = changePosition(363,68);

    cout << pt.getX() << endl;
    cout << pt.getY() << endl;

}
