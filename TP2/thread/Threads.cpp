/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Threads.cpp
 * c++ -std=c++20 Threads.cpp -o Threads -lpthread
 */

#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

#include "../Random.hpp"
#include "../osyncstream.hpp"

#include "Producer.hpp"
#include "Consumer.hpp"
#include "MessageBox.hpp"

/*
 * Test avec 1 producteur et 1 consommateur
 */
int main()
{
    // Créer un générateur de nombres aléatoires
    Random generator{50};
    // Créer une boîte à lettres
    MessageBox messageBox;
    // Créer un producteur et un consommateur
    Producer producer1(0, messageBox, generator, 10);
    Producer producer2(1, messageBox, generator, 10);
    Producer producer3(2, messageBox, generator, 10);
    Producer producer4(3, messageBox, generator, 10);

    Consumer consumer1(0, messageBox, generator, 20);
    Consumer consumer2(1, messageBox, generator, 20);
    // Créer les threads correspondants
    std::thread p1(producer1);
    std::thread p2(producer2);
    std::thread p3(producer3);
    std::thread p4(producer4);

    std::thread c1(consumer1);
    std::thread c2(consumer2);
    // Attendre la fin des threads
    p1.join();
    p2.join();
    p3.join();
    p4.join();

    c1.join();
    c2.join();

    return 0;
}
