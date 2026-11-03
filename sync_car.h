#ifndef SYNC_CAR_H
#define SYNC_CAR_H

#include <pthread.h>

struct station {
    pthread_mutex_t mutex;
    pthread_cond_t car_available;
    int waiting_passengers;
    int car_present;
    int seats_available;
};

void station_init(struct station *station);
void station_wait_for_car(struct station *station);
void station_load_car(struct station *station, int count);
#endif