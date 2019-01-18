/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   L O S S   I N D E X   C L A S S   H E A D E R                                                              */
/*                                                                                                              */
/*   Artificial Intelligence Techniques SL                                                                      */
/*   artelnics@artelnics.com                                                                                    */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __LOSSINDEX_H__
#define __LOSSINDEX_H__

// System includes

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

#include "data_set.h"

#include "neural_network.h"

// TinyXml includes

#include "tinyxml2.h"

namespace OpenNN
{
/// This class represents the concept of error term. 
/// A error term is a summand in the loss functional expression.

class LossIndex
{

public:

   // DEFAULT CONSTRUCTOR

   explicit LossIndex();

  /// ownership not passed
   // NEURAL NETWORK CONSTRUCTOR

  /// ownership not passed
   explicit LossIndex(NeuralNetwork*);

   // DATA SET CONSTRUCTOR

  /// ownership not passed
   explicit LossIndex(DataSet*);

   // NEURAL NETWORK AND DATA SET CONSTRUCTOR
  /// ownership not passed
   explicit LossIndex(NeuralNetwork*, DataSet*);

   explicit LossIndex(NeuralNetwork&, DataSet&);

   // XML CONSTRUCTOR

   explicit LossIndex(const tinyxml2::XMLDocument&);

   // COPY CONSTRUCTOR

   LossIndex(const LossIndex&);

   // DESTRUCTOR

   virtual ~LossIndex();

   // ASSIGNMENT OPERATOR

   LossIndex& operator = (const LossIndex&);

   // EQUAL TO OPERATOR

   bool operator == (const LossIndex&) const;

   enum RegularizationMethod{L1, L2, None};

   struct FirstOrderError
   {
       /// Default constructor.

       FirstOrderError(const size_t& parameters_number)
       {
           error = 0.0;
           gradient.set(parameters_number, 0.0);
       }

       virtual ~FirstOrderError()
       {
       }

       double error;
       Vector<double> gradient;
   };


   struct SecondOrderErrorTerms
   {
       /// Default constructor.

       SecondOrderErrorTerms(const size_t& parameters_number)
       {
           loss = 0.0;
           gradient.set(parameters_number, 0.0);
           Hessian_approximation.set(parameters_number, parameters_number, 0.0);
       }

       virtual ~SecondOrderErrorTerms()
       {
       }

       double loss;
       Vector<double> gradient;
       Matrix<double> Hessian_approximation;
   };


   // METHODS

   // Get methods

   /// Returns a pointer to the neural network object associated to the error term.

  /// ownership not passed
   inline NeuralNetwork* get_neural_network_pointer() const 
   {
        #ifdef __OPENNN_DEBUG__

        if(!neural_network_pointer)
        {
             ostringstream buffer;

             buffer << "OpenNN Exception: LossIndex class.\n"
                    << "NeuralNetwork* get_neural_network_pointer() const method.\n"
                    << "Neural network pointer is nullptr.\n";

             throw logic_error(buffer.str());
        }

        #endif

      return(neural_network_pointer);
   }

   /// Returns a pointer to the data set object associated to the error term.
  /// ownership not passed

   inline DataSet* get_data_set_pointer() const 
   {
        #ifdef __OPENNN_DEBUG__

        if(!data_set_pointer)
        {
             ostringstream buffer;

             cerr << "OpenNN Exception: LossIndex class.\n"
                    << "DataSet* get_data_set_pointer() const method.\n"
                    << "DataSet pointer is nullptr.\n";

             //throw logic_error(buffer.str());
        }

        #endif

      return(data_set_pointer);
   }

   const double& get_regularization_weight() const;
   const bool& get_display() const;

   bool has_neural_network() const;
   bool has_data_set() const;

  /// @{ Set methods
  /// ownership not passed

   void set();
   void set(NeuralNetwork*);
   void set(DataSet*);
   void set(NeuralNetwork*, DataSet*);
  /// @}
  
   void set(const LossIndex&);

  /// object ownership not passed
   void set_neural_network_pointer(NeuralNetwork*);

  /// object ownership not passed
   void set_data_set_pointer(DataSet*);

   void set_default();

   void set_regularization_method(const RegularizationMethod&);
   void set_regularization_weight(const double&);

   void set_display(const bool&);

   // Loss methods

   double calculate_training_loss() const;
   double calculate_training_loss(const Vector<double>&) const;
   double calculate_training_loss(const Vector<double>&, const double&) const;

   // Loss gradient methods

   Vector<double> calculate_training_loss_gradient() const;

   // ERROR METHODS

   virtual double calculate_training_error() const = 0;
   virtual double calculate_selection_error() const = 0;
   virtual double calculate_training_error(const Vector<double>&) const = 0;
   virtual double calculate_batch_error(const Vector<size_t>&) const = 0;

   virtual double calculate_batch_error_cuda(const MultilayerPerceptron::Pointers&) const {return 0.0;}

   virtual Vector<double> calculate_training_error_gradient() const = 0;

   virtual Vector<double> calculate_batch_error_gradient(const Vector<size_t>&) const {return Vector<double>();}

   virtual Vector<double> calculate_batch_error_gradient_cuda(const MultilayerPerceptron::Pointers&) const {return Vector<double>();}

   virtual Vector<double> calculate_batch_error_terms(const Vector<size_t>&) const  {return Vector<double>();}
   virtual Matrix<double> calculate_batch_error_terms_Jacobian(const Vector<size_t>&) const  {return Matrix<double>();}

   virtual FirstOrderError calculate_batch_first_order_error(const Vector<size_t>&) const {return FirstOrderError(0);}

   virtual SecondOrderErrorTerms calculate_terms_second_order_loss() const {return SecondOrderErrorTerms(0);}

   // Regularization methods

   double calculate_regularization() const;
   Vector<double> calculate_regularization_gradient() const;
   Matrix<double> calculate_regularization_Hessian() const;

   double calculate_regularization(const Vector<double>&) const;
   Vector<double> calculate_regularization_gradient(const Vector<double>&) const;
   Matrix<double> calculate_regularization_Hessian(const Vector<double>&) const;

   // Serialization methods

   string object_to_string() const;

   tinyxml2::XMLDocument* to_XML() const;
   void from_XML(const tinyxml2::XMLDocument&);

   void write_XML(tinyxml2::XMLPrinter&) const;

   string write_error_term_type() const;

   string write_information() const;

   // Checking methods

   void check() const;

   // METHODS

  /// population dependent objective function support. Call this
  /// method with the population matrix prior to calling
  /// calculate_loss_for_individual. population must remain valid for
  /// all susequent calls of calculate_loss_for_individual
  virtual void start_loss_calculation(const Matrix<double>& population) {m_population=&population;}
  /// Return loss for inidvidual \a i in population set by previous call to start_loss_calculation
  virtual double calculate_loss_for_individual(size_t i) const {return calculate_training_loss(m_population->get_row(i));}

   double calculate_columns_product_sum(const Matrix<double>&, const size_t&, const Matrix<double>&, const size_t&) const;

   Matrix<double> calculate_rows_product(const Matrix<double>&, const Matrix<double>&, const size_t&) const;

   Vector< Matrix<double> > calculate_layers_delta(const Vector< Matrix<double> >&, const Matrix<double>&) const;

   Vector<double> calculate_layer_error_gradient(const Matrix<double>&, const Matrix<double>&) const;
   Vector<double> calculate_error_gradient(const Matrix<double>&, const Vector< Matrix<double> >&, const Vector< Matrix<double> >&) const;

   Matrix<double> calculate_layer_error_terms_Jacobian(const Matrix<double>&, const Matrix<double>&) const;
   Matrix<double> calculate_error_terms_Jacobian(const Matrix<double>&, const Vector< Matrix<double> >&, const Vector< Matrix<double> >&) const;

protected:

   // MEMBERS

   /// Pointer to a multilayer perceptron object.

   NeuralNetwork* neural_network_pointer;

   /// Pointer to a data set object.

   DataSet* data_set_pointer;

   RegularizationMethod regularization_method;

   double regularization_weight = 0.0;

   size_t batch_size = 1000;

   /// Display messages to screen. 

   bool display;
  const Matrix<double> *m_population=nullptr; // weak reference to an EA population
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
