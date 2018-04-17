
#include "header.h"


Equation::Equation(char* name)                                                      //constructor that check if the file is valid or not
{
    file_name = name;
    ifstream infile(file_name);
    if (!infile.is_open())
    {
        cout<<"Error while opening the file, please check the path to file!"<<endl; //Error while opening file
    }
    else if(infile.bad())
    {
        input_to_output();                                                          //Error while reading file
    }
}

int Equation :: parse_input()
{
    ifstream infile(file_name);
    string line;
    while (std::getline(infile, line))
    {
        regex e("[[:s:]]*");
        if(!regex_match(line,e))                                                    //Check if a line is empty or just spaces and skip that
        {
            equation_vector.clear();
            if(split(line))
            {
                number_equations++;
            }
            else
            {
                input_to_output();                                                  //split failed due to invalid structure of equations
                return 0;
            }
            coefficients += equation_vector.size()-1;
            equations_set.push_back(equation_vector);
        }
    }
    return 1;
}

void Equation :: evaluate()
{
    unsigned long int dim_m = variable_set.size();                                  //dimensions of ublas matrix for Ax = b system. Dimensions of "A".
    unsigned long int nnz = coefficients;                                           // nnz - Non zero elements for sparse matrix
    unsigned long int  index_map=0;                                                 //map "value" to update the index
    for(auto it = variable_set.begin();it != variable_set.end();it++)               //key in the map is mapped to index
    {
        it->second = index_map;
        index_map++;
    }
    if(dim_m != number_equations)
    {
        input_to_output();                                                          //number of variables != number of equations. So the equation is not solvable, print the input file
        return;
    }
    else
    {
        compute(dim_m,nnz);
    }
    return;
}

int main(int argc,char* argv[]) {
    if(argc < 2)
    {
        cerr<<" Input format: "<< argv[0]<< " FileName"<<endl;
    }
    char* arg = argv[1];
    Equation eq(arg);
    if(eq.parse_input())
    {
        eq.evaluate();
    }

    return 0;
}