/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once

#include <array>
#include <algorithm>
#include <mutex>
#include <condition_variable>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre threads
 */
class MessageBox : public BasicMessageBox
{
public:
    void put(int message)
    {
        // TODO : ajouter les mecanismes de synchronisation
        // Producer
        {
            std::unique_lock<std::mutex> lock(data_mutex);
            while (data_available == 1)
            {
                cond_place_empty.wait(lock);
            }
            basic_put(message);
            data_available = 1;
            cond_place_full.notify_one();
        }
    }

    int get()
    {
        // TODO : ajouter les mecanismes de synchronisation
        // Consumer
        {
            std::unique_lock<std::mutex> lock(data_mutex);
            while (data_available == 0)
            {
                cond_place_full.wait(lock);
            }
            int message{basic_get()};
            data_available = 0;
            cond_place_empty.notify_one();
            return message;
        }
    }

private:
    // TODO : ajouter les objets de synchronisation
    std::condition_variable cond_place_empty, cond_place_full;
    std::mutex data_mutex;
    int data_available = 0;
};
