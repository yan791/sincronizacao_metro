#include "sync_car.h"

void station_init(struct station *station)
{
    pthread_mutex_init(&station->mutex, NULL);
    pthread_cond_init(&station->car_available, NULL);
    pthread_cond_init(&station->all_boarded, NULL);
    
    station->waiting_passengers = 0;
    station->car_present = 0;
    station->seats_available = 0;
    station->passengers_released = 0;
    station->passengers_boarded = 0;
}

void station_wait_for_car(struct station *station){
    
    pthread_mutex_lock(&station->mutex);
    station->waiting_passengers++;

    while (!station->car_present || station->seats_available == 0) {
        pthread_cond_wait(&station->car_available, &station->mutex);
    }

    station->waiting_passengers--;
    station->seats_available--;
    station->passengers_released++;
    pthread_cond_signal(&station->all_boarded);
    pthread_mutex_unlock(&station->mutex);
}
void station_load_car(struct station *station, int count)
{
    if (count < 0){
        count = 0;
    }

    pthread_mutex_lock(&station->mutex);

    station->car_present = 1;
    station->seats_available = count;

    pthread_cond_broadcast(&station->car_available);

    while (station->seats_available > 0 && station->waiting_passengers > 0) {
    pthread_cond_wait(&station->car_available, &station->mutex);
}

    station->car_present = 0;

    pthread_mutex_unlock(&station->mutex);
}
void station_on_board(struct station *station)
{
    pthread_mutex_lock(&station->mutex);
    station->passengers_boarded++;

    pthread_cond_signal(&station->all_boarded);
    pthread_mutex_unlock(&station->mutex);
}