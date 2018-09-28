/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   T R A I N I N G   S T R A T E G Y   C L A S S   H E A D E R                                                */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artificial Intelligence Techniques SL                                                                      */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __TRAININGSTRATEGY_H__
#define __TRAININGSTRATEGY_H__

// System includes

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <limits>
#include <cmath>
#include <ctime>

#ifdef __OPENNN_MPI__
#include <mpi.h>
#endif
// OpenNN includes

#include "loss_index.h"

#include "training_algorithm.h"

#include "random_search.h"
#include "evolutionary_algorithm.h"

#include "gradient_descent.h"
#include "conjugate_gradient.h"
#include "quasi_newton_method.h"
#include "levenberg_marquardt_algorithm.h"

#include "newton_method.h"

// TinyXml includes

#include "tinyxml2.h"

namespace OpenNN
{

/// This class represents the concept of training strategy for a neural network. 
/// A training strategy is composed of three training algorithms:
/// <ul>
/// <li> Initialization training algorithm.
/// <li> Main training algorithm.
/// <li> Refinement trainining algorithm.
/// </ul> 
   
class TrainingStrategy
{

public:

   // DEFAULT CONSTRUCTOR

   explicit TrainingStrategy();

   // GENERAL CONSTRUCTOR
  /// ownership not passed
   explicit TrainingStrategy(LossIndex*);

   explicit TrainingStrategy(LossIndex&);

   // XML CONSTRUCTOR

   explicit TrainingStrategy(const tinyxml2::XMLDocument&);

   // FILE CONSTRUCTOR

   explicit TrainingStrategy(const string&);

   // DESTRUCTOR

   virtual ~TrainingStrategy();

  TrainingStrategy(const TrainingStrategy&)=delete;
  TrainingStrategy& operator=(const TrainingStrategy&)=delete;
  
   // ENUMERATIONS

    /// Enumeration of all the available types of training algorithms.

    enum InitializationType
    {
       NO_INITIALIZATION,
       RANDOM_SEARCH,
       EVOLUTIONARY_ALGORITHM,
       USER_INITIALIZATION
    };

    /// Enumeration of all the available types of training algorithms.

    enum MainType
    {
       NO_MAIN,
       GRADIENT_DESCENT,
       CONJUGATE_GRADIENT,
       NEWTON_METHOD,
       QUASI_NEWTON_METHOD,
       LEVENBERG_MARQUARDT_ALGORITHM,
       USER_MAIN
    };

    /// Enumeration of all the available types of training algorithms.

    enum RefinementType
    {
       NO_REFINEMENT,
       //NEWTON_METHOD,
       USER_REFINEMENT
    };


   // STRUCTURES 

   /// This structure stores the results from the training strategy.
   /// They are composed of the initialization, refinement and training algorithms results. 

   struct Results
   {
        /// Default constructor.

        explicit Results();
     Results(Results&&)=default;

        /// Destructor.

        virtual ~Results();

        void save(const string&) const;

        /// Pointer to a structure with the results from the random search training algorithm.

     std::unique_ptr<RandomSearch::RandomSearchResults> random_search_results_pointer;

        /// Pointer to a structure with the results from the evolutionary training algorithm.

        std::unique_ptr<EvolutionaryAlgorithm::EvolutionaryAlgorithmResults> evolutionary_algorithm_results_pointer;

        /// Pointer to a structure with the results from the gradient descent training algorithm.

        std::unique_ptr<GradientDescent::GradientDescentResults> gradient_descent_results_pointer;

        /// Pointer to a structure with the results from the conjugate gradient training algorithm.

        std::unique_ptr<ConjugateGradient::ConjugateGradientResults> conjugate_gradient_results_pointer;

        /// Pointer to a structure with the results from the quasi-Newton method training algorithm.

        std::unique_ptr<QuasiNewtonMethod::QuasiNewtonMethodResults> quasi_Newton_method_results_pointer;

        /// Pointer to a structure with the results from the Levenberg-Marquardt training algorithm.

        std::unique_ptr<LevenbergMarquardtAlgorithm::LevenbergMarquardtAlgorithmResults> Levenberg_Marquardt_algorithm_results_pointer;

        /// Pointer to a structure with results from the Newton method training algorithm.

        std::unique_ptr<NewtonMethod::NewtonMethodResults> Newton_method_results_pointer;

  };

   // METHODS

   // Checking methods

   void check_loss_index() const;
   void check_training_algorithms() const;

   // Initialization methods

   void initialize_random();

   // Get methods
  /// ownership not passed
   LossIndex* get_loss_index_pointer() const;

   bool has_loss_index() const;

  /// @{ ownership not passed
   RandomSearch* get_random_search_pointer() const;
   EvolutionaryAlgorithm* get_evolutionary_algorithm_pointer() const;

   GradientDescent* get_gradient_descent_pointer() const;
   ConjugateGradient* get_conjugate_gradient_pointer() const;
   QuasiNewtonMethod* get_quasi_Newton_method_pointer() const;
   LevenbergMarquardtAlgorithm* get_Levenberg_Marquardt_algorithm_pointer() const;

   NewtonMethod* get_Newton_method_pointer() const;
  /// @}

   const InitializationType& get_initialization_type() const;
   const MainType& get_main_type() const;
   const RefinementType& get_refinement_type() const;

   string write_initialization_type() const;
   string write_main_type() const;
   string write_refinement_type() const;

   string write_initialization_type_text() const;
   string write_main_type_text() const;
   string write_refinement_type_text() const;

   const bool& get_display() const;

   // Set methods

  /// ownership not passed
   void set();
   void set(LossIndex*);
   virtual void set_default();

#ifdef __OPENNN_MPI__
  /// ownership not passed
   void set_MPI(LossIndex*, const TrainingStrategy*);
#endif

   void set_loss_index_pointer(LossIndex*);

   void set_initialization_type(const InitializationType&);
   void set_main_type(const MainType&);
   void set_refinement_type(const RefinementType&);

   void set_initialization_type(const string&);
   void set_main_type(const string&);
   void set_refinement_type(const string&);

   void set_display(const bool&);

   // Pointer methods

   void destruct_initialization();
   void destruct_main();
   void destruct_refinement();

   // Training methods

   // This method trains a neural network which has a loss functional associated. 

   void initialize_layers_autoencoding();

   void perform_training(Results&);
  Results&& perform_training(void) {
    Results r;
    perform_training(r);
    return std::move(r);
  }
  
   // Serialization methods

   string object_to_string() const;

   void print() const;

  /// ownership passed -- use delete to destroy
   tinyxml2::XMLDocument* to_XML() const;   
   void from_XML(const tinyxml2::XMLDocument&);   

   void write_XML(tinyxml2::XMLPrinter&) const;
   //void read_XML(   );

   void save(const string&) const;
   void load(const string&);

protected:

   /// Pointer to an external loss functional object.

   LossIndex* loss_index_pointer;

   /// Pointer to a random search object to be used for initialization in the training strategy.

    RandomSearch* random_search_pointer;

    /// Pointer to a evolutionary training object to be used for initialization in the training strategy.

    EvolutionaryAlgorithm* evolutionary_algorithm_pointer;

    /// Pointer to a gradient descent object to be used as a main training algorithm.

    GradientDescent* gradient_descent_pointer;

    /// Pointer to a conjugate gradient object to be used as a main training algorithm.

    ConjugateGradient* conjugate_gradient_pointer;

    /// Pointer to a quasi-Newton method object to be used as a main training algorithm.

    QuasiNewtonMethod* quasi_Newton_method_pointer;

    /// Pointer to a Levenberg-Marquardt algorithm object to be used as a main training algorithm.

    LevenbergMarquardtAlgorithm* Levenberg_Marquardt_algorithm_pointer;

    /// Pointer to a Newton method object to be used for refinement in the training strategy.

    NewtonMethod* Newton_method_pointer;

   /// Type of initialization training algorithm. 

   InitializationType initialization_type;

   /// Type of main training algorithm. 

   MainType main_type;

   /// Type of refinement training algorithm. 

   RefinementType refinement_type;

   /// Display messages to screen.

   bool display;

};

}

#endif


// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2018 Artificial Intelligence Techniques, SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

