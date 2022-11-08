/** Copyright (c) 2019-2022  Elias Fernandez
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
#pragma once
#ifndef EGTTOOLS_FINITEPOPULATIONS_ANALYTICAL_PAIRWISECOMPARISON_HPP
#define EGTTOOLS_FINITEPOPULATIONS_ANALYTICAL_PAIRWISECOMPARISON_HPP

#include <egttools/Distributions.h>
#include <egttools/SeedGenerator.h>
#include <egttools/Types.h>

#include <egttools/finite_populations/Utils.hpp>
#include <egttools/finite_populations/games/AbstractGame.hpp>
#include <stdexcept>

#if defined(_OPENMP)
#include <egttools/OpenMPUtils.hpp>
#endif

namespace egttools::FinitePopulations::analytical {
    /**
     * @brief Provides analytical methods to study evolutionary dynamics in finite populations
     * with the Pairwise Comparison rule.
     */
    class PairwiseComparison {
    public:
        /**
         * @brief Implements methods to study evolutionary dynamics in finite populations with the
         * Pairwise Comparison rule.
         *
         * This class implements a series of analytical methods to calculate the most relevant indicators
         * used to study the evolutionary dynamics in finite populations with the Pairwise Comparison
         * rule.
         *
         * This class requires a @param population_size to indicate the size of the population in which
         * the evolutionary process takes place, as well as a @param game which must be an object
         * inheriting from `egttools.games.AbstractGame`, and which contains a method to calculate
         * the fitness of a strategy, given a population state (represented as the counts of each
         * strategy in the population).
         *
         * @param population_size : size of the population
         * @param game : Game object.
         */
        PairwiseComparison(int population_size, egttools::FinitePopulations::AbstractGame &game);

        ~PairwiseComparison() = default;

        /**
         * @brief computes the transition matrix of the Markov Chain which defines the population dynamics.
         *
         * It is not advisable to use this method for very large state spaces since the memory required
         * to store the matrix might explode. In these cases you should resort to dimensional reduction
         * techniques, such as the Small Mutation Limit (SML).
         *
         * @param beta : intensity of selection
         * @param mu : mutation rate
         * @return SparseMatrix2D containing the transition probabilities from any population state to another.
         * This matrix will be of size nb_states x nb_states.
         */
        SparseMatrix2D calculate_transition_matrix(double beta, double mu);

        /**
         * @brief Calculates the gradient of selection without mutation for the given state.
         *
         * This method calculates the gradient of selection (without mutation), which is, the
         * most likely direction of evolution of the system.
         *
         * @param beta : intensity of selection
         * @param state : VectorXui containing the counts of each strategy in the population
         * @return Vector of nb_strategies dimensions containing the gradient of selection.
         */
        Vector calculate_gradient_of_selection(double beta, const Eigen::Ref<const VectorXui> &state);

        //        Vector calculate_gradient_of_selection(const Eigen::Ref<const Matrix2D> &transition_matrix,
        //                                               const Eigen::Ref<const Vector> &stationary_distribution,
        //                                               const Eigen::Ref<const VectorXui> &state);

        // setters
        void update_population_size(int population_size);
        void update_game(egttools::FinitePopulations::AbstractGame &game);

        // getters
        [[nodiscard]] int nb_strategies() const;
        [[nodiscard]] int64_t nb_states() const;
        [[nodiscard]] int population_size() const;
        [[nodiscard]] const egttools::FinitePopulations::AbstractGame &game() const;

    private:
        int population_size_, nb_strategies_;
        int64_t nb_states_;
        egttools::FinitePopulations::AbstractGame &game_;

        /**
         * @brief calculates a transition probability.
         *
         * This method calculates the transition probability from the current @param state
         * to a new state containing one more @param increasing_strategy and one less
         * @param decreasing_strategy.
         *
         * @param decreasing_strategy : index of the strategy that will decrease
         * @param increasing_strategy : index of the strategy that will increase
         * @param beta : intensity of selection
         * @param state : Vector containing the counts of the strategies in the population
         * @return the transition probability
         */
//        inline double calculate_transition_(int decreasing_strategy, int increasing_strategy, double beta, double mu, VectorXui &state);

        inline double calculate_local_gradient_(int decreasing_strategy, int increasing_strategy, double beta, VectorXui &state);

        inline double calculate_fitness_(int &strategy_index, VectorXui &state);
    };
}// namespace egttools::FinitePopulations::analytical

#endif//EGTTOOLS_FINITEPOPULATIONS_ANALYTICAL_PAIRWISECOMPARISON_HPP
