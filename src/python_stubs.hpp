/** Copyright (c) 2020-2021  Elias Fernandez
  *
  * This file is part of EGTtools.
  *
  * EGTtools is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * EGTtools is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with EGTtools.  If not, see <http://www.gnu.org/licenses/>
*/

#include <egttools/Types.h>

#include <egttools/finite_populations/behaviors/AbstractCRDStrategy.hpp>
#include <egttools/finite_populations/behaviors/AbstractNFGStrategy.hpp>
#include <egttools/finite_populations/games/AbstractGame.hpp>

namespace stubs {

    using PayoffVector = egttools::FinitePopulations::PayoffVector;
    using GroupPayoffs = egttools::FinitePopulations::GroupPayoffs;

    class PyAbstractGame : public egttools::FinitePopulations::AbstractGame {
    public:
        /* Inherit the constructors */
        using egttools::FinitePopulations::AbstractGame::AbstractGame;

        /* Trampoline (need one for each virtual function) */
        void play(const egttools::FinitePopulations::StrategyCounts &group_composition,
                  PayoffVector &game_payoffs) override {
            PYBIND11_OVERRIDE_PURE(
                    void,                                      /* Return type */
                    egttools::FinitePopulations::AbstractGame, /* Parent class */
                    play,                                      /* Name of function in C++ (must match Python name) */
                    group_composition, game_payoffs            /* Argument(s) */
            );
        }

        /* Trampoline (need one for each virtual function) */
        const GroupPayoffs &calculate_payoffs() override {
            PYBIND11_OVERRIDE_PURE(
                    GroupPayoffs &,                            /* Return type */
                    egttools::FinitePopulations::AbstractGame, /* Parent class */
                    calculate_payoffs                          /* Name of function in C++ (must match Python name) */
                                                               /* Argument(s) */
            );
        }

        /* Trampoline (need one for each virtual function) */
        double calculate_fitness(const size_t &player_type, const size_t &pop_size,
                                 const Eigen::Ref<const egttools::VectorXui> &strategies) override {
            PYBIND11_OVERRIDE_PURE(
                    double,                                    /* Return type */
                    egttools::FinitePopulations::AbstractGame, /* Parent class */
                    calculate_fitness,                         /* Name of function in C++ (must match Python name) */
                    player_type, pop_size, strategies          /* Argument(s) */
            );
        }

        /* Trampoline (need one for each virtual function) */
        [[nodiscard]] size_t nb_strategies() const override {
            PYBIND11_OVERRIDE_PURE(
                    size_t,                                    /* Return type */
                    egttools::FinitePopulations::AbstractGame, /* Parent class */
                    nb_strategies                              /* Name of function in C++ (must match Python name) */
                                                               /* Argument(s) */
            );
        }

        /* Trampoline (need one for each virtual function) */
        [[nodiscard]] std::string toString() const override {
            PYBIND11_OVERRIDE_PURE_NAME(
                    std::string,                               /* Return type */
                    egttools::FinitePopulations::AbstractGame, /* Parent class */
                    "__str__",                                 /* Python name */
                    nb_strategies                              /* Name of function in C++ (must match Python name) */
                                                               /* Argument(s) */
            );
        }

        /* Trampoline (need one for each virtual function) */
        [[nodiscard]] std::string type() const override {
            PYBIND11_OVERRIDE_PURE(
                    std::string,                               /* Return type */
                    egttools::FinitePopulations::AbstractGame, /* Parent class */
                    nb_strategies                              /* Name of function in C++ (must match Python name) */
                                                               /* Argument(s) */
            );
        }

        /* Trampoline (need one for each virtual function) */
        [[nodiscard]] const GroupPayoffs &payoffs() const override {
            PYBIND11_OVERRIDE_PURE(
                    GroupPayoffs &,                            /* Return type */
                    egttools::FinitePopulations::AbstractGame, /* Parent class */
                    payoffs                                    /* Name of function in C++ (must match Python name) */
                                                               /* Argument(s) */
            );
        }

        /* Trampoline (need one for each virtual function) */
        [[nodiscard]] double payoff(size_t strategy,
                                    const egttools::FinitePopulations::StrategyCounts &group_composition) const override {
            PYBIND11_OVERRIDE_PURE(
                    double,                                    /* Return type */
                    egttools::FinitePopulations::AbstractGame, /* Parent class */
                    payoff,                                    /* Name of function in C++ (must match Python name) */
                    strategy, group_composition                /* Argument(s) */
            );
        }

        /* Trampoline (need one for each virtual function) */
        void save_payoffs(std::string file_name) const override {
            PYBIND11_OVERRIDE_PURE(
                    void,                                      /* Return type */
                    egttools::FinitePopulations::AbstractGame, /* Parent class */
                    payoff,                                    /* Name of function in C++ (must match Python name) */
                    file_name                                  /* Argument(s) */
            );
        }
    };

    class PyAbstractNFGStrategy : public egttools::FinitePopulations::behaviors::AbstractNFGStrategy {
    public:
        /* Inherit the constructors */
        using egttools::FinitePopulations::behaviors::AbstractNFGStrategy::AbstractNFGStrategy;

        /* Trampoline (need one for each virtual function) */
        size_t get_action(size_t time_step, size_t action_prev) override {
            PYBIND11_OVERRIDE_PURE(
                    size_t,                                                      /* Return type */
                    egttools::FinitePopulations::behaviors::AbstractNFGStrategy, /* Parent class */
                    get_action,                                                  /* Name of function in C++ (must match Python name) */
                    time_step, action_prev                                       /* Argument(s) */
            );
        }

        /* Trampoline (need one for each virtual function) */
        std::string type() override {
            PYBIND11_OVERRIDE_PURE(
                    std::string,                                                 /* Return type */
                    egttools::FinitePopulations::behaviors::AbstractNFGStrategy, /* Parent class */
                    type                                                         /* Name of function in C++ (must match Python name) */
                                                                                 /* Argument(s) */
            );
        }

        /* Trampoline (need one for each virtual function) */
        bool is_stochastic() override {
            PYBIND11_OVERRIDE_PURE(
                    bool,                                                        /* Return type */
                    egttools::FinitePopulations::behaviors::AbstractNFGStrategy, /* Parent class */
                    is_stochastic                                                /* Name of function in C++ (must match Python name) */
                                                                                 /* Argument(s) */
            );
        }
    };

    class PyAbstractCRDStrategy : public egttools::FinitePopulations::behaviors::AbstractCRDStrategy {
    public:
        /* Inherit the constructors */
        using egttools::FinitePopulations::behaviors::AbstractCRDStrategy::AbstractCRDStrategy;

        /* Trampoline (need one for each virtual function) */
        int get_action(size_t time_step, int action_prev) override {
            PYBIND11_OVERRIDE_PURE(
                    int,                                                         /* Return type */
                    egttools::FinitePopulations::behaviors::AbstractCRDStrategy, /* Parent class */
                    get_action,                                                  /* Name of function in C++ (must match Python name) */
                    time_step, action_prev                                       /* Argument(s) */
            );
        }

        /* Trampoline (need one for each virtual function) */
        std::string type() override {
            PYBIND11_OVERRIDE_PURE(
                    std::string,                                                 /* Return type */
                    egttools::FinitePopulations::behaviors::AbstractCRDStrategy, /* Parent class */
                    type                                                         /* Name of function in C++ (must match Python name) */
                                                                                 /* Argument(s) */
            );
        }
    };

}// namespace stubs