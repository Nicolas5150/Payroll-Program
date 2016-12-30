//  Created by Nicolas Emery on 12/6/14.
//  COP 3223 - 0002
//  Assignment 5 - (Assignment5.c)
//  Copyright (c) 2014 Nicolas Emery. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>

#define MaxLen 30
#define EmpSize 20

struct Employee{
    char First[MaxLen];
    char Last[MaxLen];
    double PayPerHr;
    double Gross;
    double Taxes;
    double HrsinWeek;
    double NetPay;
};

int main()
{
    FILE* FP1;
    FILE* FP2;
    FP1 = fopen("clock.txt", "r");
    FP2 = fopen("out.txt", "w");
    
    int nEmployees, i, k, LargestLoop, m, ThisWeek;
    struct Employee EmployeeList[EmpSize];
    
    char EmployeeFirst[MaxLen], EmployeeLast[MaxLen];
    float HrIn=0, HrOut=0, MinIn=0, MinOut =0;
    
    // scan in the amount of employees
    fscanf(FP1, "%d", &nEmployees);
    // loop through emplyees varying by nEmployees
    for(i=0; i<nEmployees; i++)
    {
        // scanning in each employees last, first and pay pushed by the above for loop
        fscanf(FP1, "%s %s %lf", EmployeeList[i].Last, EmployeeList[i].First, &EmployeeList[i].PayPerHr);
    }//end for loop nEmployees
    
    // scan in the amount of weeks to come
    fscanf(FP1, "%d", &k);
    // for loop to control the amouth of times the rest of the code will cycle through due to k (how many weeks)
    for(LargestLoop = 0; LargestLoop < k; LargestLoop++)
    {
        // scan how many enteries for this week
        fscanf(FP1, "%d", &m);
        // for loop to scan in each time that emloyees name and time worked
        for(ThisWeek = 0; ThisWeek < m; ThisWeek++)
        {
            fscanf(FP1, "%s %s %f %f %f %f", EmployeeFirst, EmployeeLast, &HrIn, &MinIn, &HrOut, &MinOut);
            // loop to compare the employees just scanned in to the ones already in the array structure
            for(i=0; i<nEmployees; i++)
            {
                if(strcmp(EmployeeList[i].First, EmployeeFirst) == 0 && strcmp(EmployeeList[i].Last, EmployeeLast) == 0)
                    EmployeeList[i].HrsinWeek += (((HrOut*60 + MinOut) - (HrIn*60 + MinIn))/60);
            }// end for loop i aka. strcmp employee
        }//end for loop ThisWeek
        
        // pay for the week
        for(i=0; i<nEmployees; i++)
        {
            if(EmployeeList[i].HrsinWeek > 40)
            {
                EmployeeList[i].Gross += (EmployeeList[i].HrsinWeek - 40) * 1.5 * EmployeeList[i].PayPerHr +40 * EmployeeList[i].PayPerHr;
                EmployeeList[i].Taxes += (EmployeeList[i].HrsinWeek - 40) * EmployeeList[i].PayPerHr * .3 + 4  * EmployeeList[i].PayPerHr;
            }//end if for overtime gross pay and tax
            else
            {
                EmployeeList[i].Gross += (EmployeeList[i].HrsinWeek * EmployeeList[i].PayPerHr);
                EmployeeList[i].Taxes += ((EmployeeList[i].HrsinWeek * EmployeeList[i].PayPerHr)*.1);
            }//end else regular time
        }//end for loop paying employees (getting gross pay)
        
        // for loop zeroing out the weekly hours
        for(i=0; i<nEmployees; i++)
        {
            EmployeeList[i].HrsinWeek =0;
        }//end for zeroing out hours
    }//end for loop LarestLoop
    // for loop calulating EmployeeList NetPay
    for(i=0; i<nEmployees; i++)
    {
        EmployeeList[i].NetPay = (EmployeeList[i].Gross - EmployeeList[i].Taxes);
    }// end for loop EmployeeList NetPay
    
    fprintf(FP2, "Number of Employees: %d \n\n", nEmployees);
    for(i=0; i<nEmployees; i++)
    {
        fprintf(FP2, "W2 Form \n ------ \n");
        fprintf(FP2, "Name: %s %s \n", EmployeeList[i].Last, EmployeeList[i].First);
        fprintf(FP2, "Gross Pay: %.2lf\n", EmployeeList[i].Gross);
        fprintf(FP2, "Taxes Withheld: %.2lf\n", EmployeeList[i].Taxes);
        fprintf(FP2, "Net Pay: %.2lf\n\n", EmployeeList[i].NetPay);
    }//end for loop printing to output file "W2 form"
    
    fclose(FP1);
    fclose(FP2);
}//end main