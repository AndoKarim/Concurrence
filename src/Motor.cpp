/*****************************************************************
 * Motor.cpp
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/

#include <iostream>
#include <vector>
#include "Motor.h"

using namespace std;


void *moveAll(void *t_data) {
    //cout << "MoveAll" <<endl;

    if (t_data != NULL) {
        Motor *m = (Motor *) t_data;
        while (!m->gameFinished()) {

            for (int i = 0; i < m->getListPlayers().size(); i++) {
                Character p = m->getListPlayers()[i];
                m->avancer(i, p);
                if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 67) {
                    m->removePlayer(i, p);
                }
            }
            //m->printAllPlayers();
            /*for (int i = 0; i < m->getListPlayers().size(); i++) {
                Character p = m->getListPlayers()[i];
                if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 67) {
                    m->removePlayer(i, p);
                }
            }*/
        }
    } else {
        cerr << "error in thread" << endl;
    }

}

void *moveNO(void *t_data) {
    //cout << "MoveNO" <<endl;
    if (t_data != NULL) {
        Motor *m = (Motor *) t_data;
        switch (m->getNumEtape()) {
            case 1:
                while (!m->gameFinished()) {
                    cout << "testNO" << endl;
                    for (int i = 0; i < m->getListPlayers().size(); i++) {
                        Character p = m->getListPlayers()[i];
                        if (p.getX() < 256 && p.getY() < 64 && !p.hasFinished()) {
                            //cout << "testNO" << endl;
                            if (p.getX() <= 0 && p.getY() >= 60) {
                                m->removePlayer(i, p);
                            } else {
                                m->avancer(i, p);
                            }
                        }
                    }
                }
                break;
            case 2:
                map<string, sem_t *> *semaphores = m->getSemaphores();

                sem_t *semNO, *semNE, *semSO, *semSE;
                semNO = semaphores->find("NO")->second;
                semNE = semaphores->find("NE")->second;
                semSO = semaphores->find("SO")->second;
                semSE = semaphores->find("SE")->second;

                while (!m->gameFinished()) {
                    for (int i = 0; i < m->getListPlayers().size(); i++) {
                        Character p = m->getListPlayers()[i];
                        if(p.isOnNO() && !p.hasFinished()){
                            sem_wait(semNO); //Debut Zone critique
                            sem_t *near= nullptr;

                            if(p.nearSO())
                                near = semSO;
                            else if(p.nearNE())
                                near = semNE;
                            else if(p.nearSE())
                                near = semSE;
                            if(near!= nullptr)
                                sem_wait(near);

                            if (p.getX() <= 0 && p.getY() >= 60) {
                                m->removePlayer(i, p);
                            } else {
                                m->avancer(i, p);
                            }

                            if(near!= nullptr)
                                sem_post(near);
                            sem_post(semNO); //Fin Zone critique


                        }
                    }
                }
                break;
        }
    } else {
        cerr << "error in thread" << endl;
    }
}

void *moveNE(void *t_data) {
    //cout << "MoveNE" <<endl;
    if (t_data != NULL) {
        Motor *m = (Motor *) t_data;
        switch (m->getNumEtape()) {
            case 1:
                while (!m->gameFinished()) {
                    cout << "testNE" << endl;
                    for (int i = 0; i < m->getListPlayers().size(); i++) {
                        Character p = m->getListPlayers()[i];
                        if (p.getX() >= 255 && p.getY() < 64 && !p.hasFinished()) {
                            m->avancer(i, p);
                        }
                    }
                }
                break;
            case 2:
                map<string, sem_t *> *semaphores = m->getSemaphores();

                sem_t *semNO, *semNE, *semSO, *semSE;
                semNO = semaphores->find("NO")->second;
                semNE = semaphores->find("NE")->second;
                semSO = semaphores->find("SO")->second;
                semSE = semaphores->find("SE")->second;

                while (!m->gameFinished()) {
                    for (int i = 0; i < m->getListPlayers().size(); i++) {
                        Character p = m->getListPlayers()[i];
                        if(p.isOnNE() && !p.hasFinished()){
                            sem_wait(semNE); //Debut Zone critique
                            sem_t *near= nullptr;

                            if(p.nearSO())
                                near = semSO;
                            else if(p.nearNO())
                                near = semNO;
                            else if(p.nearSE())
                                near = semSE;
                            if(near!= nullptr)
                                sem_wait(near);

                            m->avancer(i, p);

                            if(near!= nullptr)
                                sem_post(near);
                            sem_post(semNE); //Fin Zone critique


                        }
                    }
                }
                break;
        }
    } else {
        cerr << "error in thread" << endl;
    }
}

void *moveSO(void *t_data) {
    //cout << "MoveSO" <<endl;
    if (t_data != NULL) {
        Motor *m = (Motor *) t_data;

        switch (m->getNumEtape()) {
            case 1:
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
                break;
            case 2:
                map<string, sem_t *> *semaphores = m->getSemaphores();

                sem_t *semNO, *semNE, *semSO, *semSE;
                semNO = semaphores->find("NO")->second;
                semNE = semaphores->find("NE")->second;
                semSO = semaphores->find("SO")->second;
                semSE = semaphores->find("SE")->second;

                while (!m->gameFinished()) {
                    for (int i = 0; i < m->getListPlayers().size(); i++) {
                        Character p = m->getListPlayers()[i];
                        if(p.isOnSO() && !p.hasFinished()){
                            sem_wait(semSO); //Debut Zone critique
                            sem_t *near= nullptr;

                            if(p.nearNE())
                                near = semNE;
                            else if(p.nearNO())
                                near = semNO;
                            else if(p.nearSE())
                                near = semSE;
                            if(near!= nullptr)
                                sem_wait(near);

                            if (p.getX() <= 0 && p.getY() <= 67) {
                                m->removePlayer(i, p);
                            } else {
                                m->avancer(i, p);
                            }

                            if(near!= nullptr)
                                sem_post(near);
                            sem_post(semSO); //Fin Zone critique


                        }
                    }
                }
                break;
        }
    } else {
        cerr << "error in thread" << endl;
    }
}

void *moveSE(void *t_data) {
    //cout << "MoveSE" <<endl;
    if (t_data != NULL) {
        Motor *m = (Motor *) t_data;

        switch (m->getNumEtape()) {
            case 1:
                while (!m->gameFinished()) {
                    cout << "test MoveSE" << endl;
                    for (int i = 0; i < m->getListPlayers().size(); i++) {
                        Character p = m->getListPlayers()[i];
                        if (p.getX() >= 255 && p.getY() > 63 && !p.hasFinished()) {
                            m->avancer(i, p);
                        }
                    }
                }
                break;
            case 2:
                map<string, sem_t *> *semaphores = m->getSemaphores();

                sem_t *semNO, *semNE, *semSO, *semSE;
                semNO = semaphores->find("NO")->second;
                semNE = semaphores->find("NE")->second;
                semSO = semaphores->find("SO")->second;
                semSE = semaphores->find("SE")->second;

                while (!m->gameFinished()) {
                    for (int i = 0; i < m->getListPlayers().size(); i++) {
                        Character p = m->getListPlayers()[i];
                        if(p.isOnSE() && !p.hasFinished()){
                            sem_wait(semSE); //Debut Zone critique
                            sem_t *near= nullptr;

                            if(p.nearNE())
                                near = semNE;
                            else if(p.nearNO())
                                near = semNO;
                            else if(p.nearSO())
                                near = semSO;
                            if(near!= nullptr)
                                sem_wait(near);

                            m->avancer(i, p);

                            if(near!= nullptr)
                                sem_post(near);
                            sem_post(semSE); //Fin Zone critique


                        }
                    }
                }
                break;
        }
    } else {
        cerr << "error in thread" << endl;
    }
}

void *movePerson(void *t_data) {
    cout << "movePerson" << endl;
    if (t_data != NULL) {
        thread_Struct *data =  (thread_Struct* ) t_data;
        int i = data->index;
        Motor *m = (data->m);
        Character c = m->getListPlayers()[i];

        while (!c.hasFinished()) {
            if (c.getX() <= 0 && c.getY() <= 67 && c.getY() >= 60) {
                m->removePlayer(i, c);
            }
            else {
                m->avancer(i, c);
            }
        }
        //int nbp = m->nbP();
        //cout <<  nbp << endl;

    }
}




Motor::Motor(int nbPl, int nbTd, bool nbMs, int numEtap) {
    nbPlayers = nbPl;
    nbThreads = nbTd;
    needMeasures = nbMs;
    plateau = Plateau();
    numEtape = numEtap;

    if(needMeasures){

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
   else{
    this->createPlayers();
    this->run();
    //this->test();
    }
}

void Motor::run() {

    if (nbThreads == 0) { // On peut enlever ce thread et lancer dans le main
        //Todo : creer le contexte
        pthread_t t0;
        pthread_create(&t0, NULL, moveAll, this);
        pthread_join(t0, NULL);
    }

    if (nbThreads == 1) {
        pthread_t t0;
        pthread_t t1;
        pthread_t t2;
        pthread_t t3;
        if(numEtape == 1) {
            pthread_create(&t0, NULL, moveNO, this); //s'occupe de la partie nord ouest
            pthread_create(&t1, NULL, moveNE, this); //s'occupe de la partie nord est
            pthread_create(&t2, NULL, moveSO, this); //s'occupe de la partie sud ouest
            pthread_create(&t3, NULL, moveSE, this); //s'occupe de la partie sud est
            pthread_join(t0, NULL);
            pthread_join(t1, NULL);
            pthread_join(t2, NULL);
            pthread_join(t3, NULL);
        }

        if(numEtape == 2) {

            sem_t sem_NO,sem_SE,sem_SO,sem_NE;
            sem_init(&sem_NO, 0, 1);
            sem_init(&sem_NE, 0, 1);
            sem_init(&sem_SO, 0, 1);
            sem_init(&sem_SE, 0, 1);

            map<string,sem_t*> sem;
            sem["NO"] = &sem_NO;
            sem["NE"] = &sem_NE;
            sem["SO"] = &sem_SO;
            sem["SE"] = &sem_SE;
            semaphores = &sem;


            pthread_create(&t0, NULL, moveNO, this); //s'occupe de la partie nord ouest
            pthread_create(&t1, NULL, moveNE, this); //s'occupe de la partie nord est
            pthread_create(&t2, NULL, moveSO, this); //s'occupe de la partie sud ouest
            pthread_create(&t3, NULL, moveSE, this); //s'occupe de la partie sud est

            pthread_join(t0, NULL);
            pthread_join(t1, NULL);
            pthread_join(t2, NULL);
            pthread_join(t3, NULL);

            sem_destroy(&sem_NO);
            sem_destroy(&sem_NE);
            sem_destroy(&sem_SO);
            sem_destroy(&sem_SE);

        }

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

    /*scout << index << " change from "<< p.getX() << "," << p.getY() << "to ";
    pt.print();
    cout <<  endl;*/

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

int Motor::getNumEtape() {
    return numEtape;
}

map<string, sem_t *> *Motor::getSemaphores() {
    return semaphores;
}
