/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   C O N D I T I O N S   L A Y E R   C L A S S   H E A D E R                                                  */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artificial Intelligence Techniques SL                                                                      */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __CONDITIONSLAYER_H__
#define __CONDITIONSLAYER_H__

// System includes

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

// TinyXml includes

#include "tinyxml2.h"

namespace OpenNN
{

/// This class represents a layer of conditions. 
/// Conditions are used to ensure that given outputs are provided for given inputs. 
/// Note that this is quite a difficult topic in the field of neural networks. 

class ConditionsLayer
{

public:

   // DEFAULT CONSTRUCTOR

   explicit ConditionsLayer();

   // INPUTS-CONDITIONS NUMBER CONSTRUCTOR

   explicit ConditionsLayer(const size_t&, const size_t&);

   // XML CONSTRUCTOR

   explicit ConditionsLayer(const tinyxml2::XMLDocument&);

   // COPY CONSTRUCTOR

   ConditionsLayer(const ConditionsLayer&);

   // DESTRUCTOR

   virtual ~ConditionsLayer();

   // ASSIGNMENT OPERATOR

   ConditionsLayer& operator =(const ConditionsLayer&);

   // EQUAL TO OPERATOR

   bool operator ==(const ConditionsLayer&) const;

   // ENUMERATIONS

   /// Enumeration of available methods for applying conditions.
   
   enum ConditionsMethod{NoConditions, OneCondition, TwoConditions, UserConditionsMethod};

   // GET METHODS

   const size_t& get_external_inputs_number() const;
   const size_t& get_conditions_neurons_number() const;

   const ConditionsMethod& get_conditions_method() const;
   string write_conditions_method() const;

   const Vector<double>& get_external_input_values() const;
   const double& get_external_input_value(const size_t&) const;
   
   const Matrix<double>& get_output_values() const;
   const double& get_output_value(const size_t&, const size_t&) const;

   const bool& get_display() const;

   // SET METHODS

   void set();
   void set(const size_t&, const size_t&);
   void set(const ConditionsLayer&);

   void set_external_inputs_number(const size_t&);
   void set_conditions_neurons_number(const size_t&);

   void set_conditions_method(const ConditionsMethod&);
   void set_conditions_method(const string&);

   void set_external_input_values(const Vector<double>&);
   void set_external_input_value(const size_t&, const double&);
   
   void set_output_values(const Matrix<double>&);
   void set_output_value(const size_t&, const size_t&, const double&);

   void set_display(const bool&);

   void set_default();

   // Conditions 

   void initialize_random();

   void check() const;

   // Particular solution

   /// Returns the particular solution for applying boundary conditions.
   virtual Vector<double> calculate_particular_solution(const Vector<double>&) const;

   /// Returns the particular solution Jacobian for applying boundary conditions.
   virtual Matrix<double> calculate_particular_solution_Jacobian(const Vector<double>&) const;

   virtual Vector< Matrix<double> > calculate_particular_solution_Hessian_form(const Vector<double>&) const;

   // Homogeneous solution

   /// Returns the homogeneous solution for applying boundary conditions.
   virtual Vector<double> calculate_homogeneous_solution(const Vector<double>&) const;

   /// Returns the homogeneous solution Jacobian for applying boundary conditions.
   virtual Matrix<double> calculate_homogeneous_solution_Jacobian(const Vector<double>&) const;

   virtual Vector< Matrix<double> > calculate_homogeneous_solution_Hessian_form(const Vector<double>&) const;

   Vector<double> calculate_outputs(const Vector<double>&, const Vector<double>&) const;

   Matrix<double> calculate_Jacobian(const Vector<double>&, const Vector<double>&, const Matrix<double>&) const;

   Vector< Matrix<double> > calculate_Hessian_form(const Vector<double>&, const Vector<double>&) const;

   // One condition methods

   Vector<double> calculate_one_condition_particular_solution(const Vector<double>&) const;
   Matrix<double> calculate_one_condition_particular_solution_Jacobian(const Vector<double>&) const;
   Vector< Matrix<double> > calculate_one_condition_particular_solution_Hessian_form(const Vector<double>&) const;

   Vector<double> calculate_one_condition_homogeneous_solution(const Vector<double>&) const;
   Matrix<double> calculate_one_condition_homogeneous_solution_Jacobian(const Vector<double>&) const;
   Vector< Matrix<double> > calculate_one_condition_homogeneous_solution_Hessian_form(const Vector<double>&) const;

   // Two conditions methods

   Vector<double> calculate_two_conditions_particular_solution(const Vector<double>&) const;
   Matrix<double> calculate_two_conditions_particular_solution_Jacobian(const Vector<double>&) const;
   Vector< Matrix<double> > calculate_two_conditions_particular_solution_Hessian_form(const Vector<double>&) const;

   Vector<double> calculate_two_conditions_homogeneous_solution(const Vector<double>&) const;
   Matrix<double> calculate_two_conditions_homogeneous_solution_Jacobian(const Vector<double>&) const;
   Vector< Matrix<double> > calculate_two_conditions_homogeneous_solution_Hessian_form(const Vector<double>&) const;

   // Expression methods

   virtual string write_particular_solution_expression(const Vector<string>&, const Vector<string>&) const;
   virtual string write_homogeneous_solution_expression(const Vector<string>&, const Vector<string>&) const;

   string write_one_condition_particular_solution_expression(const Vector<string>&, const Vector<string>&) const;
   string write_one_condition_homogeneous_solution_expression(const Vector<string>&, const Vector<string>&) const;
   
   string write_two_conditions_particular_solution_expression(const Vector<string>&, const Vector<string>&) const;
   string write_two_conditions_homogeneous_solution_expression(const Vector<string>&, const Vector<string>&) const;

   string write_output_expression(const Vector<string>&, const Vector<string>&, const Vector<string>&, const Vector<string>&) const;

   string write_expression(const Vector<string>&, const Vector<string>&, const Vector<string>&) const;

   // Serialization methods

   string object_to_string() const;

  /// ownership passed
   tinyxml2::XMLDocument* to_XML() const;
   void from_XML(const tinyxml2::XMLDocument&);

   void write_XML(tinyxml2::XMLPrinter&) const;
   //void read_XML(   );

protected:

   /// Number of inputs to the conditions layer. 
   /// This will be the number of inputs to the neural network. 

   size_t external_inputs_number;

   /// Number of conditions neurons.
   /// This will be the number of outputs from the neural network. 

   size_t conditions_neurons_number;

   /// Conditions method(one or two conditions).

   ConditionsMethod conditions_method;

   /// Independent values of the conditions.

   Vector<double> external_input_values;

   /// Dependent values of the conditions.

   Matrix<double> output_values;

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

