/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"

/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons
{
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Consumer
    using ProdOrCons::ProdOrCons;

    void operator()() override
    {
        // TODO : déposer dans box nb_messages nombres entiers positifs avec attente
        // aléatoire entre chaque. Afficher des messages, via un osyncstream,
        // pour suivre l'avancement.
        using milliseconds = std::chrono::duration<int, std::milli>;

        for (int i = 0; i < nb_messages_; i++)
        {
            osyncstream(std::cout) << "Le consommateur " << name_ << " lit le message: " << box_.get() << "\n";

            std::this_thread::sleep_for(milliseconds{random_engine_()});
        }
    }
};