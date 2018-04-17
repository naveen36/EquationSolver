//
// Created by Naveen Varma on 4/15/18.
//

#ifndef EquationSolver_HEADER_H
#define EquationSolver_HEADER_H
#ifndef BOOST_UBLAS_CHECK_ENABLE
#define BOOST_UBLAS_CHECK_ENABLE 0
#endif
#include <iostream>
#include<string>
#include<vector>
#include<cstdio>
#include<sstream>
#include<set>
#include<regex>
#include<fstream>
#include <fstream>
#include <iostream>
#include<map>
#include<algorithm>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/range/algorithm/find.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/vector_sparse.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
namespace ublas = boost::numeric::ublas;
using namespace std;


class Equation{
    unsigned long   number_equations = 0;                        //count the number of equations to validate if the system can be evaluated or not
    vector<string> equation_vector;                                 //equation vector saves the variable and values of the equation
    vector<vector<string>> equations_set;                           //stores all the available equations for evaluation
    map<string,double > variable_set;                               //map that carries all the unique variables of equations and the index
    unsigned long  coefficients = 0;                                //To count number of coefficients to be passed to the compressed_matrix
    char* file_name;                                                //input file name

public:
    Equation(char*);
    int parse_input();
    int split(string);
    void evaluate();
    void compute(unsigned long int,unsigned long int );
    void input_to_output()                          //function to print the input file to STDOUT in case of error
    {
        ifstream infile(file_name);

        string line;

        while (std::getline(infile, line))
        {
            cout<<line<<endl;

        }
    }
};


#endif //EquationSolver_HEADER_H
