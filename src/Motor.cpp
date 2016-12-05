/*****************************************************************
 * Motor.cpp
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/

#include <iostream>
#include <vector>
#include "Motor.h"
#include <unistd.h>

using namespace std;


void *moveAll(void *t_data) {

  if (t_data != NULL) {
    Motor *m = (Motor *) t_data;
    while (!m->gameFinished()) {

      for (int i = 0; i < m->getListPlayers().size(); i++) {
        Character p = m->getListPlayers()[i];
        if (!p.hasFinished()) {
          m->avancer(i, p);
          if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 64) {
            m->removePlayer(i, p);
          }
        }
      }
    }
  } else {
    cerr << "error in thread" << endl;
  }

}

void *moveNO(void *t_data) {
  if (t_data != NULL) {
    Motor *m = (Motor *) t_data;
    switch (m->getNumEtape()) {
      case 1:
        while (!m->gameFinished()) {
          for (int i = 0; i < m->getListPlayers().size(); i++) {
            Character p = m->getListPlayers()[i];

            if(p.getX() >= 0 && p.getX() <= 255 && p.getY() >= 0 && p.getY() <= 63 && !p.hasFinished()){
              m->avancer(i, p);
              if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 64) {
                m->removePlayer(i, p);
              }
            }
          }
        }
        break;
      case 2:{
        map<string, sem_t *> *semaphores = m->getSemaphores();

        sem_t *semNO, *semNE, *semSO, *semSE;
        semNO = semaphores->find("NO")->second;
        semNE = semaphores->find("NE")->second;
        semSO = semaphores->find("SO")->second;
        semSE = semaphores->find("SE")->second;

        while (!m->gameFinished()) {
          for (int i = 0; i < m->getListPlayers().size(); i++) {
            Character p = m->getListPlayers()[i];
            if (p.isOnNO() && !p.hasFinished()) {
              sem_wait(semNO); //Debut Zone critique
              sem_t *near = nullptr;

              if (p.nearSO())
                near = semSO;
              else if (p.nearNE())
                near = semNE;
              else if (p.nearSE())
                near = semSE;
              if (near != nullptr)
                sem_wait(near);
              m->avancer(i, p);
              if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 64) {
                m->removePlayer(i, p);
              }

              if (near != nullptr)
                sem_post(near);
              sem_post(semNO); //Fin Zone critique


            }
          }
        }
        m->getBarrier()->await();
      }
        break;
        case 3: {
                Monitor *monitor = m->getMonitor();
                pair<pthread_mutex_t, pthread_cond_t> monitorZoneNO = monitor->zoneNO;

                while (!m->gameFinished()) {
                    for (int i = 0; i < m->getListPlayers().size(); i++) {
                        Character p = m->getListPlayers()[i];
                        if (p.isOnNO() && !p.hasFinished()) {
                            //Verrouillage de la zone
                            pthread_mutex_lock(&(monitorZoneNO.first));

                            while (!(monitor->availableZoneNO)) {
                                pthread_cond_wait(&(monitorZoneNO.second), &(monitorZoneNO.first));
                            }
                            pthread_cond_signal(&(monitorZoneNO.second));

                            pair<pthread_mutex_t, pthread_cond_t> *near;

                            if (p.nearSO()) {
                                near = &(monitor->zoneSO);
                                pthread_mutex_lock(&(near->first));

                                while (!(monitor->availableZoneSO)) {
                                    pthread_cond_wait(&(near->second), &(near->first));
                                }
                                pthread_cond_signal(&(near->second));
                            } else if (p.nearNE()){
                                near = &(monitor->zoneNE);
                            pthread_mutex_lock(&(near->first));

                            while (!(monitor->availableZoneNE)) {
                                pthread_cond_wait(&(near->second), &(near->first));
                            }
                            pthread_cond_signal(&(near->second));
                            }
                            else if (p.nearSE()) {
                                near = &(monitor->zoneSE);
                                pthread_mutex_lock(&(near->first));

                                while (!(monitor->availableZoneSE)) {
                                    pthread_cond_wait(&(near->second), &(near->first));
                                }
                                pthread_cond_signal(&(near->second));
                            }

                            m->avancer(i, p);
                            if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 64) {
                              m->removePlayer(i, p);
                            }

                            //Deverouillage
                            if (near != nullptr)
                                pthread_mutex_unlock(&(near->first));
                            pthread_mutex_unlock(&(monitorZoneNO.first));
                        }
                    }
                }
                m->getBarrier()->await();
            }
                break;
    }
  } else {
    cerr << "error in thread" << endl;
  }
}

void *moveNE(void *t_data) {

  if (t_data != NULL) {
    Motor *m = (Motor *) t_data;
    switch (m->getNumEtape()) {
      case 1:
        while (!m->gameFinished()) {

          for (int i = 0; i < m->getListPlayers().size(); i++) {
            Character p = m->getListPlayers()[i];
            
            if(p.getX() >= 256 && p.getX() <= 511 && p.getY() >= 0 && p.getY() <= 63 && !p.hasFinished()){
              m->avancer(i, p);
              if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 64) {
                m->removePlayer(i, p);
              }
            }
          }
        }
        break;
      case 2:{
        map<string, sem_t *> *semaphores = m->getSemaphores();

        sem_t *semNO, *semNE, *semSO, *semSE;
        semNO = semaphores->find("NO")->second;
        semNE = semaphores->find("NE")->second;
        semSO = semaphores->find("SO")->second;
        semSE = semaphores->find("SE")->second;

        while (!m->gameFinished()) {
          for (int i = 0; i < m->getListPlayers().size(); i++) {
            Character p = m->getListPlayers()[i];
            if (p.isOnNE() && !p.hasFinished()) {
              sem_wait(semNE); //Debut Zone critique
              sem_t *near = nullptr;

              if (p.nearSO())
                near = semSO;
              else if (p.nearNO())
                near = semNO;
              else if (p.nearSE())
                near = semSE;
              if (near != nullptr)
                sem_wait(near);
              m->avancer(i, p);
              if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 64) {
                m->removePlayer(i, p);
              }

              if (near != nullptr)
                sem_post(near);
              sem_post(semNE); //Fin Zone critique


            }
          }
        }
        m->getBarrier()->await();
      }
        break;
        case 3: {
                Monitor *monitor = m->getMonitor();
                pair<pthread_mutex_t, pthread_cond_t> monitorZoneNE = monitor->zoneNE;

                while (!m->gameFinished()) {
                    for (int i = 0; i < m->getListPlayers().size(); i++) {
                        Character p = m->getListPlayers()[i];
                        if (p.isOnNE() && !p.hasFinished()) {
                            //Verrouillage de la zone
                            pthread_mutex_lock(&(monitorZoneNE.first));

                            while (!(monitor->availableZoneNE)) {
                                pthread_cond_wait(&(monitorZoneNE.second), &(monitorZoneNE.first));
                            }
                            pthread_cond_signal(&(monitorZoneNE.second));

                            pair<pthread_mutex_t, pthread_cond_t> *near;

                            if (p.nearSO()) {
                                near = &(monitor->zoneSO);
                                pthread_mutex_lock(&(near->first));

                                while (!(monitor->availableZoneSO)) {
                                    pthread_cond_wait(&(near->second), &(near->first));
                                }
                                pthread_cond_signal(&(near->second));
                            } else if (p.nearNO()){
                                near = &(monitor->zoneNO);
                                pthread_mutex_lock(&(near->first));

                                while (!(monitor->availableZoneNO)) {
                                    pthread_cond_wait(&(near->second), &(near->first));
                                }
                                pthread_cond_signal(&(near->second));
                            }
                            else if (p.nearSE()) {
                                near = &(monitor->zoneSE);
                                pthread_mutex_lock(&(near->first));

                                while (!(monitor->availableZoneSE)) {
                                    pthread_cond_wait(&(near->second), &(near->first));
                                }
                                pthread_cond_signal(&(near->second));
                            }

                            m->avancer(i, p);

                            if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 64) {
                              m->removePlayer(i, p);
                            }

                            //Deverouillage
                            if (near != nullptr)
                                pthread_mutex_unlock(&(near->first));
                            pthread_mutex_unlock(&(monitorZoneNE.first));
                        }
                    }
                }
                m->getBarrier()->await();
            }
                break;
    }
  } else {
    cerr << "error in thread" << endl;
  }
}

void *moveSO(void *t_data) {

  if (t_data != NULL) {
    Motor *m = (Motor *) t_data;

    switch (m->getNumEtape()) {
      case 1:
        while (!m->gameFinished()) {
          for (int i = 0; i < m->getListPlayers().size(); i++) {
            Character p = m->getListPlayers()[i];

            if(p.getX() >= 0 && p.getX() <= 255 && p.getY() >= 64 && p.getY() <= 127 && !p.hasFinished()){
              m->avancer(i, p);
              if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 64) {
                m->removePlayer(i, p);
              }
            }
          }
        }
        break;
      case 2:{
        map<string, sem_t *> *semaphores = m->getSemaphores();

        sem_t *semNO, *semNE, *semSO, *semSE;
        semNO = semaphores->find("NO")->second;
        semNE = semaphores->find("NE")->second;
        semSO = semaphores->find("SO")->second;
        semSE = semaphores->find("SE")->second;

        while (!m->gameFinished()) {
          for (int i = 0; i < m->getListPlayers().size(); i++) {
            Character p = m->getListPlayers()[i];
            if (p.isOnSO() && !p.hasFinished()) {
              sem_wait(semSO); //Debut Zone critique
              sem_t *near = nullptr;

              if (p.nearNE())
                near = semNE;
              else if (p.nearNO())
                near = semNO;
              else if (p.nearSE())
                near = semSE;
              if (near != nullptr)
                sem_wait(near);

              m->avancer(i, p);
              if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 64) {
                m->removePlayer(i, p);
              }

              if (near != nullptr)
                sem_post(near);
              sem_post(semSO); //Fin Zone critique


            }
          }
        }
        m->getBarrier()->await();
      }
        break;
        case 3: {
                Monitor *monitor = m->getMonitor();
                pair<pthread_mutex_t, pthread_cond_t> monitorZoneSO = monitor->zoneSO;

                while (!m->gameFinished()) {
                    for (int i = 0; i < m->getListPlayers().size(); i++) {
                        Character p = m->getListPlayers()[i];
                        if (p.isOnSO() && !p.hasFinished()) {
                            //Verrouillage de la zone
                            pthread_mutex_lock(&(monitorZoneSO.first));

                            while (!(monitor->availableZoneSO)) {
                                pthread_cond_wait(&(monitorZoneSO.second), &(monitorZoneSO.first));
                            }
                            pthread_cond_signal(&(monitorZoneSO.second));

                            pair<pthread_mutex_t, pthread_cond_t> *near;

                            if (p.nearNE()) {
                                near = &(monitor->zoneNE);
                                pthread_mutex_lock(&(near->first));

                                while (!(monitor->availableZoneNE)) {
                                    pthread_cond_wait(&(near->second), &(near->first));
                                }
                                pthread_cond_signal(&(near->second));
                            } else if (p.nearNO()){
                                near = &(monitor->zoneNO);
                                pthread_mutex_lock(&(near->first));

                                while (!(monitor->availableZoneNO)) {
                                    pthread_cond_wait(&(near->second), &(near->first));
                                }
                                pthread_cond_signal(&(near->second));
                            }
                            else if (p.nearSE()) {
                                near = &(monitor->zoneSE);
                                pthread_mutex_lock(&(near->first));

                                while (!(monitor->availableZoneSE)) {
                                    pthread_cond_wait(&(near->second), &(near->first));
                                }
                                pthread_cond_signal(&(near->second));
                            }

                            m->avancer(i, p);
                            if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 64) {
                              m->removePlayer(i, p);
                            }

                            //Deverouillage
                            if (near != nullptr)
                                pthread_mutex_unlock(&(near->first));
                            pthread_mutex_unlock(&(monitorZoneSO.first));
                        }
                    }
                }
                m->getBarrier()->await();
            }
                break;
    }
  } else {
    cerr << "error in thread" << endl;
  }
}

void *moveSE(void *t_data) {

  if (t_data != NULL) {
    Motor *m = (Motor *) t_data;

    switch (m->getNumEtape()) {
      case 1:
        while (!m->gameFinished()) {

          for (int i = 0; i < m->getListPlayers().size(); i++) {
            Character p = m->getListPlayers()[i];


            if(p.getX() >= 256 && p.getX() <= 511 && p.getY() >= 64 && p.getY() <= 127 && !p.hasFinished()){
              m->avancer(i, p);
              if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 64) {
                m->removePlayer(i, p);
              }
            }
          }
        }
        break;
      case 2:{
        map<string, sem_t *> *semaphores = m->getSemaphores();

        sem_t *semNO, *semNE, *semSO, *semSE;
        semNO = semaphores->find("NO")->second;
        semNE = semaphores->find("NE")->second;
        semSO = semaphores->find("SO")->second;
        semSE = semaphores->find("SE")->second;

        while (!m->gameFinished()) {
          for (int i = 0; i < m->getListPlayers().size(); i++) {
            Character p = m->getListPlayers()[i];
            if (p.isOnSE() && !p.hasFinished()) {
              sem_wait(semSE); //Debut Zone critique
              sem_t *near = nullptr;

              if (p.nearNE())
                near = semNE;
              else if (p.nearNO())
                near = semNO;
              else if (p.nearSO())
                near = semSO;
              if (near != nullptr)
                sem_wait(near);

              m->avancer(i, p);
              if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 64) {
                m->removePlayer(i, p);
              }

              if (near != nullptr)
                sem_post(near);
              sem_post(semSE); //Fin Zone critique


            }
          }
        }
        m->getBarrier()->await();
      }
        break;
        case 3: {
                Monitor *monitor = m->getMonitor();
                pair<pthread_mutex_t, pthread_cond_t> monitorZoneSE = monitor->zoneSE;

                while (!m->gameFinished()) {
                    for (int i = 0; i < m->getListPlayers().size(); i++) {
                        Character p = m->getListPlayers()[i];
                        if (p.isOnSE() && !p.hasFinished()) {
                            //Verrouillage de la zone
                            pthread_mutex_lock(&(monitorZoneSE.first));

                            while (!(monitor->availableZoneSE)) {
                                pthread_cond_wait(&(monitorZoneSE.second), &(monitorZoneSE.first));
                            }
                            pthread_cond_signal(&(monitorZoneSE.second));

                            pair<pthread_mutex_t, pthread_cond_t> *near;

                            if (p.nearNE()) {
                                near = &(monitor->zoneNE);
                                pthread_mutex_lock(&(near->first));

                                while (!(monitor->availableZoneNE)) {
                                    pthread_cond_wait(&(near->second), &(near->first));
                                }
                                pthread_cond_signal(&(near->second));
                            } else if (p.nearNO()){
                                near = &(monitor->zoneNO);
                                pthread_mutex_lock(&(near->first));

                                while (!(monitor->availableZoneNO)) {
                                    pthread_cond_wait(&(near->second), &(near->first));
                                }
                                pthread_cond_signal(&(near->second));
                            }
                            else if (p.nearSO()) {
                                near = &(monitor->zoneSO);
                                pthread_mutex_lock(&(near->first));

                                while (!(monitor->availableZoneSO)) {
                                    pthread_cond_wait(&(near->second), &(near->first));
                                }
                                pthread_cond_signal(&(near->second));
                            }

                            m->avancer(i, p);
                            if (p.getX() <= 0 && p.getY() >= 60 && p.getY() <= 64) {
                              m->removePlayer(i, p);
                            }

                            //Deverouillage
                            if (near != nullptr)
                                pthread_mutex_unlock(&(near->first));
                            pthread_mutex_unlock(&(monitorZoneSE.first));
                        }
                    }
                } 
                m->getBarrier()->await();
            }
                break;
    }
  } else {
    cerr << "error in thread" << endl;
  }
}

void *movePerson(void *t_data) {
  if (t_data != NULL) {
    thread_Struct *data = (thread_Struct *) t_data;
    int i = data->index;
    Motor *m = (data->m);
    Character c = m->getListPlayers()[i];
    while (!c.hasFinished()) {
      map<string, sem_t *> sems;
      Monitor *monitor = m->getMonitor();
      if (m->getNumEtape() == 2)
        sems = m->lockAround(c);

      if(m->getNumEtape()==3){
                pthread_mutex_lock(&(monitor->mutex));
                while(!(monitor->availableCharacter)){
                    pthread_cond_wait(monitor->cond, &(monitor->mutex));
                    pthread_cond_signal(monitor->cond);
                }          

            }


      m->avancer(i, c);
      if (c.getX() <= 0 && c.getY() >= 60 && c.getY() <= 64) {
        m->removePlayer(i, c);
      }
      if (m->getNumEtape() == 2)
        m->unlockSemList(sems);
      if(m->getNumEtape()==3){
                pthread_mutex_unlock(&(monitor->mutex));
            }

    }
    if (m->getNumEtape() == 2 || m->getNumEtape() == 3) {
            m->getBarrier()->await();
        }
  }
}


Motor::Motor(int nbPl, int nbTd, bool nbMs, int numEtap) {
  nbPlayers = nbPl;
  nbThreads = nbTd;
  needMeasures = nbMs;
  plateau = Plateau();
  numEtape = numEtap;

  if (needMeasures) {
    printf("\n");

    for (int i = 0; i < 5; i++) {
      cout << "Debut du " << i+1 << endl;
      time_t startTime;
      time(&startTime);

      this->createPlayers();
      clock_t start_t;
      clock_t end_t;

      start_t = clock();
      this->run();
      end_t = clock();
      measuresTab[i] = ((float) (end_t - start_t)) / CLOCKS_PER_SEC;
      time_t endTime;
      time(&endTime);
      timeMeasures[i] = difftime(endTime, startTime);
      cout << "Fin du " << i+1 << endl << endl;
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

    for (int i = 1; i < 5; i++) {
      if (max < measuresTab[i])
        indiceMax = i;
      if (min > measuresTab[i])
        indiceMin = i;

      if (maxTime < timeMeasures[i])
        indiceMaxTime = i;
      if (minTime > timeMeasures[i])
        indiceMinTime = i;
    }

    for (int i = 0; i < 5; i++) {
      if (i != indiceMax && i != indiceMin)
        moyenne = moyenne + measuresTab[i];

      if (i != indiceMaxTime && i != indiceMinTime)
        moyenneTime = moyenneTime + timeMeasures[i];
    }

    moyenne = moyenne / 3;
    moyenneTime = moyenneTime / 3;

    printf("Moyennes des mesures:\n");
    printf("Temps d'execution moyen ---> %.3f s.\n", moyenne);
    printf("Temps de réponse moyen ---> %.3f s.\n", moyenneTime);

  } else {
    this->createPlayers();
    this->run();
  }
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

    if (numEtape == 1) {
      pthread_create(&t0, NULL, moveNO, this); //s'occupe de la partie nord ouest
      pthread_create(&t1, NULL, moveNE, this); //s'occupe de la partie nord est
      pthread_create(&t2, NULL, moveSO, this); //s'occupe de la partie sud ouest
      pthread_create(&t3, NULL, moveSE, this); //s'occupe de la partie sud est
      pthread_join(t0, NULL);
      pthread_join(t1, NULL);
      pthread_join(t2, NULL);
      pthread_join(t3, NULL);
    }

    if (numEtape == 2) {

      sem_t sem_NO, sem_SE, sem_SO, sem_NE;
      sem_init(&sem_NO, 0, 1);
      sem_init(&sem_NE, 0, 1);
      sem_init(&sem_SO, 0, 1);
      sem_init(&sem_SE, 0, 1);

      map<string, sem_t *> sem;
      sem["NO"] = &sem_NO;
      sem["NE"] = &sem_NE;
      sem["SO"] = &sem_SO;
      sem["SE"] = &sem_SE;
      semaphores = &sem;

      barrier = new SynchroBarrier(4);

      pthread_create(&t0, NULL, moveNO, this); //s'occupe de la partie nord ouest
      pthread_create(&t1, NULL, moveNE, this); //s'occupe de la partie nord est
      pthread_create(&t2, NULL, moveSO, this); //s'occupe de la partie sud ouest
      pthread_create(&t3, NULL, moveSE, this); //s'occupe de la partie sud est

      barrier->block();


      sem_destroy(&sem_NO);
      sem_destroy(&sem_NE);
      sem_destroy(&sem_SO);
      sem_destroy(&sem_SE);

    }

    if (numEtape == 3) {
            barrier = new SynchroBarrier(4);
            monitor = new Monitor();
            pthread_create(&t0, NULL, moveNO, this); //s'occupe de la partie nord ouest
            pthread_create(&t1, NULL, moveNE, this); //s'occupe de la partie nord est
            pthread_create(&t2, NULL, moveSO, this); //s'occupe de la partie sud ouest
            pthread_create(&t3, NULL, moveSE, this); //s'occupe de la partie sud est

            barrier->block();
        }

  }

  if (nbThreads == 2) {
    vector<pthread_t> allThreads;
    int n = getListPlayers().size();
    int i = 0;

    if (numEtape == 2 || numEtape == 3) {
            barrier = new SynchroBarrier(n);
    }

        if(numEtape==3){
            pthread_mutex_t lock;
            pthread_mutex_init(&lock, NULL);
            pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

            monitor = new Monitor(&cond,lock);
        }

    vector<thread_Struct> alldata;

     while (i < n) {
        struct thread_Struct data = {this, i};
        alldata.push_back(data);
        i++;
     }

    i=0;
    while (i < n) {
      pthread_t tmp;
      pthread_create(&tmp, NULL, movePerson, (void *) &alldata[i]);
      allThreads.push_back(tmp);
      i++;
    }

    if (numEtape == 1) {


            int a = allThreads.size();
            int j = 0;
            while (j < a) {
                pthread_join(allThreads[j], NULL);
                j++;
            }
        }
        if (numEtape == 2 || numEtape == 3) {
            barrier->block();
        }
  }

}

void Motor::createPlayers() {
  this->removeAllPlayers();
  for (int i = 0; i < this->nbPlayers; i++) {
    srand( time(NULL) );
    int randX = rand() % 512;
    int randY = rand() % 128;

    while (!plateau.addPlayer(randX, randY)) {
      randX = rand() % 512;
      randY = rand() % 128;

    }
    Character c(randX, randY);
    listPlayers.push_back(c);

  }
}

void Motor::removePlayer(int i, Character &c) {
  c.finish();
  this->listPlayers[i] = c;
  this->plateau.removePlayer(c.getX(), c.getY());
}


void Motor::printAllPlayers() {
  for (vector<Character>::iterator it = this->listPlayers.begin(); it != this->listPlayers.end(); ++it)
    it->print();
}

int Motor::nbP() {
  int j = 0;
  for (int i = 0; i < getListPlayers().size(); i++) {
    Character c = getListPlayers()[i];
    if (!c.hasFinished())
      j++;
  }
  return j;
}

bool Motor::gameFinished() {

  for (int i = 0; i < getListPlayers().size(); i++) {
    Character c = getListPlayers()[i];
    if (!c.hasFinished())
      return false;
  }
  return true;
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
  Point pt = changePosition(p.getX(), p.getY());
  if (this->plateau.movePlayer(p.getX(), p.getY(), pt.getX(), pt.getY())) {
    p.move(pt);
  }
  listPlayers[index] = p;
}

Point Motor::changePosition(int x, int y) {
  int LockD = 0;
  int LockH = 0;
  int LockV = 0;

  if ((y < (plateau.getHeigth() - plateau.getOpenHeigthWall1()) / 2 && x < plateau.getWidthLastWall())
      || (y < (plateau.getHeigth() - plateau.getOpenHeigthWall2()) / 2 && x >= plateau.getWidthLastWall())) {
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
  } else  {
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
}

void Motor::test() {

  Point pt = changePosition(363, 68);

  cout << pt.getX() << endl;
  cout << pt.getY() << endl;

}

int Motor::getNumEtape() {
  return numEtape;
}

map<string, sem_t *> *Motor::getSemaphores() {
  return semaphores;
}

map<string, sem_t *> Motor::lockAround(Character character) {
  map<string, sem_t *> sems;
  int tmpX = character.getX() - 1;
  if (tmpX < 0) tmpX = 0;
  int tmpY = character.getY() - 1;
  if (tmpY < 0) tmpY = 0;

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      int newX = tmpX + j;
      int newY = tmpY + i;
      if (newX > 511) newX = 511;
      if (newY > 127) newY = 127;

      sem_t *tmpMutex = plateau.getCase(newX, newY).mutex;
      string s = newX + "," + newY;
      if (sems.find(s)->second != tmpMutex) {
        sems[s] = tmpMutex;
        sem_wait(tmpMutex);
      }
    }
  }
  return sems;
}

void Motor::unlockSemList(map<string, sem_t *> sems) {
  for (auto &kv : sems) {
    sem_post(kv.second);
  }
}

SynchroBarrier *Motor::getBarrier() {
    return barrier;
}

Monitor *Motor::getMonitor() {
    return monitor;
}
