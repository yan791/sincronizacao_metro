#include "sync_car.h"

void station_init(struct station *station)
{
    pthread_mutex_init(&station->mutex, NULL);
    station->waiting_passengers = 0;
}