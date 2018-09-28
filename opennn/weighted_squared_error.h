/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   W E I G H T E D   S Q U A R E D   E R R O R    C L A S S   H E A D E R                                     */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artificial Intelligence Techniques SL                                                                      */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __WEIGHTEDSQUAREDERROR_H__
#define __WEIGHTEDSQUAREDERROR_H__

// System includes

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <limits>
#include <math.h>

// OpenNN includes

#include "error_term.h"
#include "data_set.h"

// TinyXml includes

#include "tinyxml2.h"

namespace OpenNN
{

/// This class represents the mean squared error term. 
/// The mean squared error measures the difference between the outputs from a neural network and the targets in a data set. 
/// This functional is used in data modeling problems, such as function regression, 
/// classification and time series prediction.

class WeightedSquaredError : public ErrorTerm
{

public:

   // DEFAULT CONSTRUCTOR

   explicit WeightedSquaredError();

   // NEURAL NETWORK CONSTRUCTOR
  /// ownership not passed

   explicit WeightedSquaredError(NeuralNetwork*);

   // DATA SET CONSTRUCTOR
  /// ownership not passed

   explicit WeightedSquaredError(DataSet*);

   // GENERAL CONSTRUCTOR
  /// ownership not passed

   explicit WeightedSquaredError(NeuralNetwork*, DataSet*);

   // XML CONSTRUCTOR

   explicit WeightedSquaredError(const tinyxml2::XMLDocument&);

   // COPY CONSTRUCTOR

   WeightedSquaredError(const WeightedSquaredError&);

   // DESTRUCTOR

   virtual ~WeightedSquaredError();

   // STRUCTURES


   // METHODS

   // Get methods

   double get_positives_weight() const;
   double get_negatives_weight() const;

   double get_normalization_coefficient() const;

   // Set methods

   // Checking methods

   void check() const;

   // Objective methods

   void set_default();

   void set_positives_weight(const double&);
   void set_negatives_weight(const double&);

   void set_normalization_coefficient(const double&);

   void set_weights(const double&, const double&);

   void set_weights();

   void set_normalization_coefficient();

   double calculate_positives_loss() const;
   double calculate_negatives_loss() const;

   double calculate_error() const;
   double calculate_error(const Vector<double>&) const;
   double calculate_selection_error() const;

   double calculate_error(const double&) const;
   double calculate_error(const Vector<double>&, const double&) const;
   double calculate_selection_error(const double&) const;

   Vector<double> calculate_output_gradient(const Vector<double>&, const Vector<double>&) const;
   Matrix<double> calculate_output_Hessian(const Vector<double>&, const Vector<double>&) const;

   Vector<double> calculate_output_gradient(const Vector<double>&, const Vector<double>&, const double&) const;
   Vector<double> calculate_gradient_with_normalization(const double&) const;

   FirstOrderPerformance calculate_first_order_loss() const;
   SecondOrderPerformance calculate_second_order_loss() const;

   // Objective terms methods

   Vector<double> calculate_terms() const;
   Vector<double> calculate_terms(const Vector<double>&) const;

   Matrix<double> calculate_terms_Jacobian() const;

   FirstOrderTerms calculate_first_order_terms() const;

   string write_error_term_type() const;

   // Serialization methods

  /// ownership passed - use delete to destroy
   tinyxml2::XMLDocument* to_XML() const;   
   void from_XML(const tinyxml2::XMLDocument&);

   void write_XML(tinyxml2::XMLPrinter&) const;
   //void read_XML(   );

//   string write_information() const;

   string object_to_string() const;

private:

   /// Weight for the positives for the calculation of the error.

   double positives_weight;

   /// Weight for the negatives for the calculation of the error.

   double negatives_weight;

   /// Coefficient of normalization for the calculation of the training error.

   double normalization_coefficient;
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
