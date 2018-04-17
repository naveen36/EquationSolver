//
// Created by Naveen Varma on 4/15/18.
//

#include "header.h"
string output_file = "EquationSolver_output.txt";

void Equation :: compute(unsigned long int dim_m,unsigned long int nnz)
{
    ublas::compressed_matrix<double , ublas::column_major, 0>  ublas_matrix(dim_m, dim_m, nnz); //size of the equation (row,column,non zero elements)
    ublas::vector<double> output_vector(dim_m);                                                 //input number of equations(dim_m) to the ublas vector
    int vector_count = 0;                                                                       //count to get the x coordinate of 2d ublas_matrix;
    ofstream output;

    for(auto iterator = equations_set.begin();iterator!= equations_set.end();iterator++)        //iterate the vector of vector<string> to push the values onto ublas matrix for evaluation
    {
        vector<string> test = *iterator;
        auto euqation_itr = test.begin();                                                       //iterator for vector<string>
        ublas_matrix(vector_count,variable_set[*euqation_itr]) = 1;                             //Coefficient of 1st element of vector is always 1 as equation is of the for a = b + c + ..
        euqation_itr++;
        for(;euqation_itr != test.end()-1;euqation_itr++)
        {
            ublas_matrix(vector_count,variable_set[*euqation_itr]) = -1;                         //Coefficients of the subsequent variables is always -1
        }

        output_vector(vector_count) = stoul(*(euqation_itr));                                    //Adds the constant value to the output vector for evaluation
        vector_count++;
    }

    ublas::permutation_matrix<size_t> pm(ublas_matrix.size1());                                  //permutation matrix is setup for Ax = b computation
    lu_factorize(ublas_matrix, pm);
    try
    {
        lu_substitute(ublas_matrix, pm, output_vector);                                          //computation of the output matrix
        throw 1;
    }
    catch (int c)
    {
        double inf = std::numeric_limits<double>::infinity();
        int count = 0;
        for(auto iterator = variable_set.begin();iterator != variable_set.end();iterator++)
        {
            double out = output_vector(count);
            if(out == inf) {                                                                      //checks for unsolvable systems
                input_to_output();
                return;
            }
            iterator->second = out;                                                               //stores the output vector in map
            count++;
        }
        output.open(output_file);
        for(auto iterator = variable_set.begin();iterator != variable_set.end();iterator++)
        {
            cout<<iterator->first<<" = "<<iterator->second<<endl;
            output<<iterator->first<<" = "<<iterator->second<<endl;
        }
    }
    catch(std::exception const &e)                                                              //catches exceptions from boost library
    {
        input_to_output();
        return;
    }
    return;
}