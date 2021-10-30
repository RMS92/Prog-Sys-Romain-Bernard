/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.hpp
 */

#pragma once

#include <iostream>
#include <chrono>
#include <thread>

#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"
#include "../Random.hpp"

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons
{
public:
    // Le constructeur de ProdOrCons peut être utilisé pour Producer
    using ProdOrCons::ProdOrCons;

    void operator()() override
    {
        // TODO : déposer dans box nb_messages nombres entiers positifs avec attente
        // aléatoire entre chaque. Afficher des messages pour suivre l'avancement.
        using milliseconds = std::chrono::duration<int, std::milli>;

        for (int i = 0; i < nb_messages_; i++)
        {
            int alea = random_engine_();

            box_.put(alea);

            osyncstream(std::cout) << "Le producteur " << name_ << " envoie le message: " << alea << "\n";

            std::this_thread::sleep_for(milliseconds{random_engine_()});
        }
    }
};
