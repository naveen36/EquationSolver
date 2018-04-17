//
// Created by Naveen Varma on 4/15/18.
//

#include "header.h"

int Equation:: split(string line)
{
    double sum_int=0;                                                                                           //sum of integers in the equation
    string match_pattern = "([[:s:]]+(?:[[:alpha:]]+|[[:digit:]]+))";                                           // Pattern to match variables or doubles
    regex e("[[:s:]]*[[:alpha:]]+[[:s:]]+="+match_pattern+"{1}(?:[[:s:]]+\\+"+ match_pattern +")*[[:s:]]*");    // Regex to match the pattern [alphabet][spaces][=][space][alphabet/digits][space][+]...
    if(!regex_match(line, e))                                                                                    // If no match exit as the input has error
    {
        return 0;
    }
    stringstream ss(line);
    string out_str;
    while(getline(ss,out_str,' '))                                                                              //split the string by skipping spaces
    {
        if(out_str.length()>0)
        {
            regex e("[[:digit:]]+");
            if(regex_match(out_str,e))                                                                          //check if it is a digit and add all digits
            {
                sum_int += stod(out_str);
            }
            else if (regex_match(out_str,regex("[[:alpha:]]+")))                                                //check if the value is a string
            {
                variable_set[out_str] = 1;
                equation_vector.push_back(out_str);
            }
        }
    }
    equation_vector.push_back(to_string(sum_int));                                                              //push the integer val to vector at the end
    set<string> s(equation_vector.begin(),equation_vector.end());
    if(s.size() != equation_vector.size())                                                                      //checks if same variable is present twice in the equation
    {
        return 0;
    }
    return 1;
}