#include "sync_car.h"

void station_init(struct station *station)
{
    pthread_mutex_init(&station->mutex, NULL);
    pthread_cond_init(&station->car_available, NULL);

    station->waiting_passengers = 0;
    station->car_present = 0;
}

void station_wait_for_car(struct station *station){
    pthread_mutex_lock(&station->mutex);

    station->waiting_passengers++;

    while (!station->car_present) {
        pthread_cond_wait(&station->car_available, &station->mutex);
    }

    station->waiting_passengers--;
    pthread_mutex_unlock(&station->mutex);

}