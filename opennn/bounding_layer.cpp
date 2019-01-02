/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   B O U N D I N G   L A Y E R   C L A S S                                                                    */
/*                                                                                                              */
/*   Artificial Intelligence Techniques SL                                                                      */
/*   artelnics@artelnics.com                                                                                    */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "bounding_layer.h"

namespace OpenNN
{

// DEFAULT CONSTRUCTOR

/// Default constructor. 
/// It creates a bounding layer object with zero bounding neurons.

BoundingLayer::BoundingLayer()
{
   set();
}


// BOUNDING NEURONS NUMBER CONSTRUCTOR

/// Bounding neurons number constructor. 
/// It creates a bounding layer with a given size. 
/// @param bounding_neurons_number Number of bounding neurons in the layer. 

BoundingLayer::BoundingLayer(const size_t& bounding_neurons_number)
{
   set(bounding_neurons_number);

   set_default();
}


// XML CONSTRUCTOR

/// XML constructor. 
/// It creates a bounding layer and loads its members from a XML document. 
/// @param bounding_layer_document TinyXML document with the member data. 

BoundingLayer::BoundingLayer(const tinyxml2::XMLDocument& bounding_layer_document)
{
   set(bounding_layer_document);
}


// COPY CONSTRUCTOR

/// Copy constructor. 
/// It creates a copy of an existing bounding layer object. 
/// @param other_bounding_layer Bounding layer to be copied.

BoundingLayer::BoundingLayer(const BoundingLayer& other_bounding_layer)
{
   set(other_bounding_layer);
}


// DESTRUCTOR

/// Destructor.
/// This destructor does not delete any pointer. 

BoundingLayer::~BoundingLayer()
{
}


// ASSIGNMENT OPERATOR

/// Assignment operator. 
/// It assigns to this object the members of an existing bounding layer object.
/// @param other_bounding_layer Bounding layer object to be assigned.

BoundingLayer& BoundingLayer::operator = (const BoundingLayer& other_bounding_layer)
{
   if(this != &other_bounding_layer) 
   {
      lower_bounds = other_bounding_layer.lower_bounds;
      upper_bounds = other_bounding_layer.upper_bounds;
      display = other_bounding_layer.display;
   }

   return(*this);
}


// EQUAL TO OPERATOR

// bool operator == (const BoundingLayer&) const method

/// Equal to operator. 
/// It compares this object with another object of the same class. 
/// It returns true if the members of the two objects have the same values, and false otherwise.
/// @ param other_bounding_layer Bounding layer to be compared with.

bool BoundingLayer::operator == (const BoundingLayer& other_bounding_layer) const
{
    if(lower_bounds == other_bounding_layer.lower_bounds
    && upper_bounds == other_bounding_layer.upper_bounds
    && display == other_bounding_layer.display)
    {
       return(true);
    }
    else
    {
       return(false);
    }
}


// bool is_empty() const method

/// Returns true if the size of the layer is zero, and false otherwise.

bool BoundingLayer::is_empty() const
{
   if(get_bounding_neurons_number() == 0)
   {
      return(true);
   }
   else
   {
      return(false);
   }
}

// const BoundingMethod& get_bounding_method() const method

/// Returns the method used for bounding layer.

const BoundingLayer::BoundingMethod& BoundingLayer::get_bounding_method() const
{
    return(bounding_method);
}

// string write_bounding_method() const method

/// Returns a string with the name of the method used for bounding layer.

string BoundingLayer::write_bounding_method() const
{
    if(bounding_method == Bounding)
    {
        return("Bounding");
    }
    else if(bounding_method == NoBounding)
    {
        return("NoBounding");
    }
    else
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: BoundingLayer class.\n"
               << "string write_bounding_method() const method.\n"
               << "Unknown bounding method.\n";

        throw logic_error(buffer.str());
    }
}


/// Returns the number of bounding neurons in the layer.

size_t BoundingLayer::get_bounding_neurons_number() const
{
   return(lower_bounds.size());
}


/// Returns the lower bounds values of all the bounding neurons in the layer.

const Vector<double>& BoundingLayer::get_lower_bounds() const
{
   return(lower_bounds);               
}


/// Returns the lower bound value of a single bounding neuron.
/// @param i Index of bounding neuron. 

double BoundingLayer::get_lower_bound(const size_t& i) const
{
   // Control sentence(if debug)

   #ifdef __OPENNN_DEBUG__

   const size_t bounding_neurons_number = get_bounding_neurons_number();

   if(i >= bounding_neurons_number)
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n" 
             << "double get_lower_bound(const size_t&) const method.\n"
             << "Index must be less than number of bounding neurons.\n";

	  throw logic_error(buffer.str());
   }

   #endif

   return(lower_bounds[i]);
}


/// Returns the upper bounds values of all the bounding neurons in the layer.

const Vector<double>& BoundingLayer::get_upper_bounds() const
{
   return(upper_bounds);               
}


/// Returns the upper bound value of a single bounding neuron.
/// @param i Index of bounding neuron. 

double BoundingLayer::get_upper_bound(const size_t& i) const
{
   // Control sentence(if debug)

   #ifdef __OPENNN_DEBUG__

   const size_t bounding_neurons_number = get_bounding_neurons_number();

   if(bounding_neurons_number == 0)
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n" 
             << "double get_upper_bound(const size_t&) const method.\n"
             << "Number of bounding neurons is zero.\n";

	  throw logic_error(buffer.str());
   }
   else if(i >= bounding_neurons_number)
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n" 
             << "double get_upper_bound(const size_t&) const method.\n"
             << "Index must be less than number of bounding neurons.\n";

	  throw logic_error(buffer.str());
   }

   #endif

   return(upper_bounds[i]);
}


/// Returns the lower bounds and the upper bounds of all the bounding neurons.
/// The format is a vector of pointers to vectors of size two. 
/// The first element contains the lower bound values.
/// The second element contains the upper bound values.

Vector< Vector<double>* > BoundingLayer::get_bounds()
{
   return {&lower_bounds, &upper_bounds};
}


/// Sets the number of bounding neurons to be zero.
/// It also sets the rest of memebers to their default values. 

void BoundingLayer::set()
{
   bounding_method = Bounding;

   lower_bounds.set();
   upper_bounds.set();

   set_default();
}


/// Resizes the bounding layer.
/// It also sets the rest of memebers to their default values. 
/// @param new_bounding_neurons_number Size of the bounding layer. 

void BoundingLayer::set(const size_t& new_bounding_neurons_number)
{
   lower_bounds.set(new_bounding_neurons_number);
   upper_bounds.set(new_bounding_neurons_number);

   set_default();
}


/// Sets the bounding layer members from a XML document.
/// @param bounding_layer_document Pointer to a TinyXML document containing the member data.

void BoundingLayer::set(const tinyxml2::XMLDocument& bounding_layer_document)
{
    set_default();

   from_XML(bounding_layer_document);
}


/// Sets the members of this object to be the members of another object of the same class.
/// @param other_bounding_layer Object to be copied. 

void BoundingLayer::set(const BoundingLayer& other_bounding_layer)
{
   lower_bounds = other_bounding_layer.lower_bounds;

   upper_bounds = other_bounding_layer.upper_bounds;

   display = other_bounding_layer.display;
}


/// Sets a new bounding method.
/// @param new_method New bounding method.

void BoundingLayer::set_bounding_method(const BoundingMethod& new_method)
{
    bounding_method = new_method;
}


/// Sets a new bounding method.
/// @param new_method_string New bounding method string.

void BoundingLayer::set_bounding_method(const string& new_method_string)
{
    if(new_method_string == "NoBounding")
    {
        bounding_method = NoBounding;
    }
    else if(new_method_string == "Bounding")
    {
        bounding_method = Bounding;
    }
    else
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: BoundingLayer class.\n"
               << "void set_bounding_method(const string&) method.\n"
               << "Unknown bounding method: " << new_method_string << ".\n";

        throw logic_error(buffer.str());
    }
}


/// Sets new lower bounds for all the neurons in the layer.
/// @param new_lower_bounds New set of lower bounds for the bounding neurons. 

void BoundingLayer::set_lower_bounds(const Vector<double>& new_lower_bounds)
{
   // Control sentence(if debug)

   #ifdef __OPENNN_DEBUG__

   const size_t bounding_neurons_number = get_bounding_neurons_number();

   if(new_lower_bounds.size() != bounding_neurons_number)
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n"
             << "void set_lower_bounds(const Vector<double>&) method.\n"
             << "Size must be equal to number of bounding neurons number.\n";

	  throw logic_error(buffer.str());
   }

   #endif

   // Set lower bound of bounding neurons

   lower_bounds = new_lower_bounds;
}


/// Sets a new lower bound for a single neuron.
/// This value is used for unscaling that variable so that it is not less than the lower bound. 
/// @param index Index of bounding neuron.
/// @param new_lower_bound New lower bound for the neuron with index i.

void BoundingLayer::set_lower_bound(const size_t& index, const double& new_lower_bound)
{
   const size_t bounding_neurons_number = get_bounding_neurons_number();

   // Control sentence(if debug)

   #ifdef __OPENNN_DEBUG__

   if(index >= bounding_neurons_number)
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n"
             << "void set_lower_bound(const size_t&, const double&) method.\n"
             << "Index of bounding neurons must be less than number of bounding neurons.\n";

	  throw logic_error(buffer.str());
   }

   #endif

   if(lower_bounds.size() != bounding_neurons_number)
   {
      lower_bounds.set(bounding_neurons_number, -numeric_limits<double>::max());
   }

   // Set lower bound of single neuron

   lower_bounds[index] = new_lower_bound;
}


/// Sets new upper bounds for all the bounding neurons.
/// These values are used for unscaling variables so that they are not greater than the upper bounds. 
/// @param new_upper_bounds New set of upper bounds for the layer.

void BoundingLayer::set_upper_bounds(const Vector<double>& new_upper_bounds)
{
   // Control sentence(if debug)

   #ifdef __OPENNN_DEBUG__

   const size_t bounding_neurons_number = get_bounding_neurons_number();

   if(new_upper_bounds.size() != bounding_neurons_number)
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n"
             << "void set_upper_bound(const Vector<double>&) method.\n"
             << "Size must be equal to number of bounding neurons.\n";

	  throw logic_error(buffer.str());
   }

   #endif

   // Set upper bound of neurons

   upper_bounds = new_upper_bounds;
}


/// Sets a new upper bound for a single neuron.
/// This value is used for unscaling that variable so that it is not greater than the upper bound. 
/// @param index Index of bounding neuron.
/// @param new_upper_bound New upper bound for the bounding neuron with that index.

void BoundingLayer::set_upper_bound(const size_t& index, const double& new_upper_bound)
{
   const size_t bounding_neurons_number = get_bounding_neurons_number();

   // Control sentence(if debug)

   #ifdef __OPENNN_DEBUG__

   if(index >= bounding_neurons_number)
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n"
             << "void set_upper_bound(const size_t&, const double&) method.\n"
             << "Index of bounding neuron must be less than number of bounding neurons.\n";

	  throw logic_error(buffer.str());
   }

   #endif

   if(upper_bounds.size() != bounding_neurons_number)
   {
      upper_bounds.set(bounding_neurons_number, numeric_limits<double>::max());
   }

   // Set upper bound of single bounding neuron

   upper_bounds[index] = new_upper_bound;
}


/// Sets both the lower bounds and the upper bounds of all the neurons in the layer.
/// The format is a vector of two real vectors.
/// The first element must contain the lower bound values for the bounding neurons.
/// The second element must contain the upper bound values for the bounding neurons.
/// These values are used for unscaling variables so that they are neither less than the lower bounds nor greater than the upper bounds. 
/// @param new_bounds New set of lower and upper bounds.

void BoundingLayer::set_bounds(const Vector< Vector<double> >& new_bounds)
{
   // Control sentence(if debug)

   #ifdef __OPENNN_DEBUG__

   const size_t size = new_bounds.size();

   const size_t bounding_neurons_number = get_bounding_neurons_number();

   if(size != 2)
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n"
             << "void set_bounds(const Vector< Vector<double> >&) method.\n"
             << "Number of rows must be 2.\n";

	  throw logic_error(buffer.str());
   }
   else if(new_bounds[0].size() != bounding_neurons_number
        && new_bounds[1].size() != bounding_neurons_number)
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n"
             << "void set_bounds(const Vector< Vector<double> >&) method.\n"
             << "Number of columns must be equal to number of bounding neurons.\n";

	  throw logic_error(buffer.str());
   }

   #endif

   // Set lower and upper bounds of bounding neurons

   set_lower_bounds(new_bounds[0]);
   set_upper_bounds(new_bounds[1]);
}


/// Sets a new display value.
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.

void BoundingLayer::set_display(const bool& new_display)
{
   display = new_display;
}


/// Sets the members to their default values:
/// <ul>
/// <li> Display: True. 
/// </ul>

void BoundingLayer::set_default()
{
   display = true;

   bounding_method = Bounding;
}


/// Removes a given bounding neuron from the bounding layer.
/// @param index Index of neuron to be pruned.

void BoundingLayer::prune_bounding_neuron(const size_t& index)
{
    // Control sentence(if debug)

    #ifdef __OPENNN_DEBUG__

    const size_t bounding_neurons_number = get_bounding_neurons_number();

    if(index >= bounding_neurons_number)
    {
       ostringstream buffer;

       buffer << "OpenNN Exception: BoundingLayer class.\n"
              << "void prune_bounding_neuron(const size_t&) method.\n"
              << "Index of bounding neuron is equal or greater than number of bounding neurons.\n";

       throw logic_error(buffer.str());
    }

    #endif

    lower_bounds.erase(lower_bounds.begin() + static_cast<long>(index));
    upper_bounds.erase(upper_bounds.begin() + static_cast<long>(index));
}


/// Initializes the lower and upper bounds of all the bounding neurons with random values.

void BoundingLayer::initialize_random()
{
   Vector<double> random_vector(4);
   random_vector.randomize_normal();

   sort(random_vector.begin(), random_vector.end());

   lower_bounds.randomize_uniform(random_vector[0], random_vector[1]);
   upper_bounds.randomize_uniform(random_vector[2], random_vector[3]);

   if(rand()%2)
   {
       set_bounding_method("Bounding");
   }
   else
   {
       set_bounding_method("NoBounding");
   }
}


/// Calculates the outputs from the bounding layer for a set of inputs to that layer.
/// @param inputs Set of inputs to the bounding layer.

Matrix<double> BoundingLayer::calculate_outputs(const Matrix<double>& inputs) const
{
   // Control sentence(if debug)

   #ifdef __OPENNN_DEBUG__

   const size_t inputs_size = inputs.size();

   const size_t bounding_neurons_number = get_bounding_neurons_number();

   if(inputs_size != bounding_neurons_number) 
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n"
             << "Matrix<double> calculate_outputs(const Matrix<double>&) const method.\n"
             << "Size of inputs must be equal to number of bounding neurons.\n";

	  throw logic_error(buffer.str());
   }   

   #endif

   if(bounding_method == NoBounding)
   {
       return(inputs);
   }
   else if(bounding_method == Bounding)
   {
       return(inputs.calculate_lower_upper_bounded(lower_bounds, upper_bounds));
   }
   else
   {
       ostringstream buffer;

       buffer << "OpenNN Exception: BoundingLayer class.\n"
              << "Matrix<double> calculate_outputs(const Matrix<double>&) const method.\n"
              << "Unknown bounding method.\n";

       throw logic_error(buffer.str());
   }

   return Matrix<double>();
}  


/// Returns the derivatives of the outputs with respect to the inputs.
/// @param inputs Set of input values to the bounding layer. 

Matrix<double> BoundingLayer::calculate_derivatives(const Matrix<double>& inputs) const
{
   const size_t points_number = inputs.get_rows_number();
   const size_t bounding_neurons_number = get_bounding_neurons_number();

   const Matrix<double> outputs = calculate_outputs(inputs);

   Matrix<double> derivatives(points_number, bounding_neurons_number);

   for(size_t i = 0; i < points_number; i++)
   {
   for(size_t j = 0; j < bounding_neurons_number; j++)
   {
      if(outputs(i,j) <= lower_bounds[j] || outputs(i,j) >= upper_bounds[j])
      {           
         derivatives(i,j) = 0.0;
	  }
      else
      {
         derivatives(i,j) = 1.0;
      }
   }
   }

   return(derivatives);
}


/// Returns the second derivatives of the outputs with respect to the inputs.
/// @param inputs Set of input values to the bounding layer. 

Matrix<double> BoundingLayer::calculate_second_derivatives(const Matrix<double>& inputs) const
{
   ostringstream buffer;

   const size_t points_number = inputs.get_rows_number();
   const size_t bounding_neurons_number = get_bounding_neurons_number();

   const Matrix<double> outputs = calculate_outputs(inputs);

   for(size_t i = 0; i < bounding_neurons_number; i++)
   {
      if(fabs(outputs[i] - lower_bounds[i]) < numeric_limits<double>::epsilon())
      {
         buffer << "OpenNN Exception: BoundingLayer class.\n"
                << "Matrix<double> calculate_outputs(const Matrix<double>&) const method.\n"
                << "Output is equal to lower bound. The bounding function is not differentiable at this point.\n";

	     throw logic_error(buffer.str());
      }
      else if(fabs(outputs[i] - upper_bounds[i]) < numeric_limits<double>::epsilon())
      {
         buffer << "OpenNN Exception: BoundingLayer class.\n"
                << "Matrix<double> calculate_outputs(const Matrix<double>&) const method.\n"
                << "Output is equal to upper bound. The bounding function is not differentiable at this point.\n";

	     throw logic_error(buffer.str());
      }
   }

   const Matrix<double> second_derivatives(points_number, bounding_neurons_number, 0.0);

   return(second_derivatives);
}


/// Arranges a "Jacobian matrix" from a vector of derivatives.
/// The Jacobian matrix is composed of the partial derivatives of the layer outputs with respect to the layer inputs. 
/// @param derivatives Vector of outputs-inputs derivatives of each bounding neuron. 

Matrix<double> BoundingLayer::calculate_Jacobian(const Vector<double>& derivatives) const
{   
   const size_t bounding_neurons_number = get_bounding_neurons_number();

   // Control sentence(if debug)

   #ifdef __OPENNN_DEBUG__

   const size_t derivatives_size = derivatives.size();

   if(derivatives_size != bounding_neurons_number) 
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n"
             << "Matrix<double> calculate_Jacobian(const Vector<double>&) method.\n"
             << "Size of derivatives must be equal to number of bounding neurons.\n";

	  throw logic_error(buffer.str());
   }   

   #endif

   Matrix<double> Jacobian(bounding_neurons_number, bounding_neurons_number, 0.0);
   Jacobian.set_diagonal(derivatives);

   return(Jacobian);
}  


/// Arranges a "Hessian form" vector of matrices from a vector of derivatives.
/// The Hessian form is composed of the second partial derivatives of the layer outputs with respect to the layer inputs. 

Vector< Matrix<double> > BoundingLayer::calculate_Hessian(const Vector<double>&) const
{
   const size_t bounding_neurons_number = get_bounding_neurons_number();

   Vector< Matrix<double> > bounded_Hessian(bounding_neurons_number);

   for(size_t i = 0; i < bounding_neurons_number; i++)
   {
      bounded_Hessian[i].set(bounding_neurons_number, bounding_neurons_number, 0.0);
   }

   return(bounded_Hessian);
}


/// Returns a string with the expression of the lower and upper bounds functions.

string BoundingLayer::write_expression(const Vector<string>& inputs_name, const Vector<string>& outputs_name) const
{
    ostringstream buffer;

   buffer.precision(10);

   if(bounding_method == Bounding)
   {
       const size_t bounding_neurons_number = get_bounding_neurons_number();

       for(size_t i = 0; i < bounding_neurons_number; i++)
       {
           buffer << outputs_name[i] << " = max(" << lower_bounds[i] << ", " << inputs_name[i] << ")\n";
           buffer << outputs_name[i] << " = min(" << upper_bounds[i] << ", " << inputs_name[i] << ")\n";
       }
   }
   else
   {
       buffer << "";
   }

   return(buffer.str());
}


/// Returns a string with the expression of the lower and upper bounds functions.

string BoundingLayer::write_expression_php(const Vector<string>& inputs_name, const Vector<string>& outputs_name) const
{
    ostringstream buffer;

   buffer.precision(10);

   if(bounding_method == Bounding)
   {
       const size_t bounding_neurons_number = get_bounding_neurons_number();

       for(size_t i = 0; i < bounding_neurons_number; i++)
       {
           buffer << outputs_name[i] << " = max(" << lower_bounds[i] << ", " << inputs_name[i] << ");\n";
           buffer << outputs_name[i] << " = min(" << upper_bounds[i] << ", " << inputs_name[i] << ");\n";
       }
   }
   else
   {
       buffer << "";
   }

   return(buffer.str());
}


/// Returns a string representation of the current bonding layer object.

string BoundingLayer::object_to_string() const
{
   ostringstream buffer;

   buffer << "Bounding layer\n" 
          << "Lower bounds: " << lower_bounds << "\n"
          << "Upper bounds: " << upper_bounds << "\n"
          << "Display: " << display << "\n";

   return(buffer.str());
}


// tinyxml2::XMLDocument* to_XML() const method

/// Serializes the bounding layer object into a XML document of the TinyXML library.
/// See the OpenNN manual for more information about the format of this document.

tinyxml2::XMLDocument* BoundingLayer::to_XML() const
{
    tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

    ostringstream buffer;

    tinyxml2::XMLElement* bounding_layer_element = document->NewElement("BoundingLayer");

    document->InsertFirstChild(bounding_layer_element);

    // Scaling neurons number

    tinyxml2::XMLElement* size_element = document->NewElement("BoundingNeuronsNumber");
    bounding_layer_element->LinkEndChild(size_element);

    const size_t bounding_neurons_number = get_bounding_neurons_number();

    buffer.str("");
    buffer << bounding_neurons_number;

    tinyxml2::XMLText* size_text = document->NewText(buffer.str().c_str());
    size_element->LinkEndChild(size_text);

    for(size_t i = 0; i < bounding_neurons_number; i++)
    {
        tinyxml2::XMLElement* item_element = document->NewElement("Item");
        item_element->SetAttribute("Index",static_cast<unsigned>(i+1));

        bounding_layer_element->LinkEndChild(item_element);

        // Lower bound

        tinyxml2::XMLElement* lower_bound_element = document->NewElement("LowerBound");
        item_element->LinkEndChild(lower_bound_element);

        buffer.str("");
        buffer << lower_bounds[i];

        tinyxml2::XMLText* lower_bound_text = document->NewText(buffer.str().c_str());
        lower_bound_element->LinkEndChild(lower_bound_text);

        // Upper bound

        tinyxml2::XMLElement* upper_bound_element = document->NewElement("UpperBound");
        item_element->LinkEndChild(upper_bound_element);

        buffer.str("");
        buffer << upper_bounds[i];

        tinyxml2::XMLText* upper_bound_text = document->NewText(buffer.str().c_str());
        upper_bound_element->LinkEndChild(upper_bound_text);
    }

    // Bounding method

    tinyxml2::XMLElement* method_element = document->NewElement("UseBoundingLayer");
    bounding_layer_element->LinkEndChild(method_element);

    if(bounding_method == Bounding)
    {
        buffer.str("");
        buffer << 1;
    }
    else if(bounding_method == NoBounding)
    {
        buffer.str("");
        buffer << 0;
    }
    else
    {
        buffer << "OpenNN Exception: BoundingLayer class.\n"
               << "void write_XML(tinyxml2::XMLPrinter&) const method.\n"
               << "Unknown bounding method type.\n";

        throw logic_error(buffer.str());
    }

    tinyxml2::XMLText* method_text = document->NewText(buffer.str().c_str());
    method_element->LinkEndChild(method_text);
//   // Display
//   {
//      tinyxml2::XMLElement* display_element = document->NewElement("Display");
//      bounding_layer_element->LinkEndChild(display_element);

//      buffer.str("");
//      buffer << display;

//      tinyxml2::XMLText* display_text = document->NewText(buffer.str().c_str());
//      display_element->LinkEndChild(display_text);
//   }

   return(document);
}

// void write_XML(tinyxml2::XMLPrinter&) const method

/// Serializes the bounding layer object into a XML document of the TinyXML library without keep the DOM tree in memory.
/// See the OpenNN manual for more information about the format of this document.

void BoundingLayer::write_XML(tinyxml2::XMLPrinter& file_stream) const
{
   ostringstream buffer;

   file_stream.OpenElement("BoundingLayer");

   // Bounding neurons number

   file_stream.OpenElement("BoundingNeuronsNumber");

   const size_t bounding_neurons_number = get_bounding_neurons_number();

   buffer.str("");
   buffer << bounding_neurons_number;

   file_stream.PushText(buffer.str().c_str());

   file_stream.CloseElement();

   for(size_t i = 0; i < bounding_neurons_number; i++)
   {
       file_stream.OpenElement("Item");

       file_stream.PushAttribute("Index",static_cast<unsigned>(i+1));

       // Lower bound

       file_stream.OpenElement("LowerBound");

       buffer.str("");
       buffer << lower_bounds[i];

       file_stream.PushText(buffer.str().c_str());

       file_stream.CloseElement();

       // Upper bound

       file_stream.OpenElement("UpperBound");

       buffer.str("");
       buffer << upper_bounds[i];

       file_stream.PushText(buffer.str().c_str());

       file_stream.CloseElement();


       file_stream.CloseElement();
   }

   // Bounding method

   file_stream.OpenElement("UseBoundingLayer");

   if(bounding_method == Bounding)
   {
       buffer.str("");
       buffer << 1;
   }
   else if(bounding_method == NoBounding)
   {
       buffer.str("");
       buffer << 0;
   }
   else
   {
       file_stream.CloseElement();

       buffer << "OpenNN Exception: BoundingLayer class.\n"
              << "void write_XML(tinyxml2::XMLPrinter&) const method.\n"
              << "Unknown bounding method type.\n";

       throw logic_error(buffer.str());
   }

   file_stream.PushText(buffer.str().c_str());

   file_stream.CloseElement();

//   // Display

//   {
//      file_stream.OpenElement("Display");

//      buffer.str("");
//      buffer << display;

//      file_stream.PushText(buffer.str().c_str());

//      file_stream.CloseElement();
//   }

   file_stream.CloseElement();
}


/// Deserializes a TinyXML document into this bounding layer object.
/// @param document TinyXML document containing the member data.

void BoundingLayer::from_XML(const tinyxml2::XMLDocument& document)
{
    ostringstream buffer;

    const tinyxml2::XMLElement* bounding_layer_element = document.FirstChildElement("BoundingLayer");

    if(!bounding_layer_element)
    {
        buffer << "OpenNN Exception: BoundingLayer class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "BoundingLayer element is nullptr.\n";

        throw logic_error(buffer.str());
    }

    // Bounding neurons number

    const tinyxml2::XMLElement* bounding_neurons_number_element = bounding_layer_element->FirstChildElement("BoundingNeuronsNumber");

    if(!bounding_neurons_number_element)
    {
        buffer << "OpenNN Exception: BoundingLayer class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "BoundingNeuronsNumber element is nullptr.\n";

        throw logic_error(buffer.str());
    }

    const size_t bounding_neurons_number = static_cast<size_t>(atoi(bounding_neurons_number_element->GetText()));

    set(bounding_neurons_number);

    unsigned index = 0; // size_t does not work

    const tinyxml2::XMLElement* start_element = bounding_neurons_number_element;

    for(size_t i = 0; i < lower_bounds.size(); i++)
    {
        const tinyxml2::XMLElement* item_element = start_element->NextSiblingElement("Item");
        start_element = item_element;

        if(!item_element)
        {
            buffer << "OpenNN Exception: BoundingLayer class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Item " << i+1 << " is nullptr.\n";

            throw logic_error(buffer.str());
        }

        item_element->QueryUnsignedAttribute("Index", &index);

        if(index != i+1)
        {
            buffer << "OpenNN Exception: BoundingLayer class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Index " << index << " is not correct.\n";

            throw logic_error(buffer.str());
        }

        // Lower bound

        const tinyxml2::XMLElement* lower_bound_element = item_element->FirstChildElement("LowerBound");

        if(lower_bound_element)
        {
            if(lower_bound_element->GetText())
            {
                lower_bounds[index-1] = atof(lower_bound_element->GetText());
            }
        }

        // Upper bound

        const tinyxml2::XMLElement* upper_bound_element = item_element->FirstChildElement("UpperBound");

        if(upper_bound_element)
        {
            if(upper_bound_element->GetText())
            {
                upper_bounds[index-1] = atof(upper_bound_element->GetText());
            }
        }
    }

    // Use bounding layer
    {
        const tinyxml2::XMLElement* use_bounding_layer_element = bounding_layer_element->FirstChildElement("UseBoundingLayer");

        if(use_bounding_layer_element)
        {
            size_t new_method = static_cast<size_t>(atoi(use_bounding_layer_element->GetText()));

            if(new_method == 1)
            {
                bounding_method = Bounding;
            }
            else if(new_method == 0)
            {
                bounding_method = NoBounding;
            }
            else
            {
                buffer << "OpenNN Exception: BoundingLayer class.\n"
                       << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                       << "Unknown bounding method.\n";

                throw logic_error(buffer.str());
            }
        }
    }

      // Control sentence 
//      {
//         const char* text = bounding_layer_element->GetText();     

//         const string string(text);

//         if(string != "BoundingLayer")
//         {
//            ostringstream buffer;

//            buffer << "OpenNN Exception: BoundingLayer class.\n" 
//                   << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
//                   << "Unkown root element: " << text << ".\n";

//   	        throw logic_error(buffer.str());
//         }
//      }

//  // Lower bounds
//  {
//     const tinyxml2::XMLElement* lower_bounds_element = document.FirstChildElement("LowerBounds");

//     if(lower_bounds_element)
//     {
//        const char* lower_bounds_text = lower_bounds_element->GetText();

//        if(lower_bounds_text)
//        {
//           Vector<double> new_lower_bounds;
//           new_lower_bounds.parse(lower_bounds_text);

//           try
//           {
//              set_lower_bounds(new_lower_bounds);
//           }
//           catch(const logic_error& e)
//           {
//              cerr << e.what() << endl;
//           }
//        }
//     }
//  }

//  // Upper bounds
//  {
//     const tinyxml2::XMLElement* upper_bounds_element = document.FirstChildElement("UpperBounds");

//     if(upper_bounds_element)
//     {
//        const char* upper_bounds_text = upper_bounds_element->GetText();

//        if(upper_bounds_text)
//        {
//           Vector<double> new_upper_bounds;
//           new_upper_bounds.parse(upper_bounds_text);

//           try
//           {
//              set_upper_bounds(new_upper_bounds);
//           }
//           catch(const logic_error& e)
//           {
//              cerr << e.what() << endl;
//           }
//        }
//     }
//  }

//  // Display
//  {
//     const tinyxml2::XMLElement* display_element = document.FirstChildElement("Display");

//     if(display_element)
//     {
//        string new_display_string = display_element->GetText();

//        try
//        {
//           set_display(new_display_string != "0");
//        }
//        catch(const logic_error& e)
//        {
//           cerr << e.what() << endl;
//        }
//     }
//  }
}

}

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
