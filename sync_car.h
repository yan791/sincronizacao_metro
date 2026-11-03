#ifndef SYNC_CAR_H
#define SYNC_CAR_H

#include <pthread.h>

struct station {
    pthread_mutex_t mutex;
    int waiting_passengers;
};

void station_init(struct station *station);

#endif