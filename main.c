//
//  main.c
//  ME-30 Final Project - Arduino .txt to Matlab .csv file converter
//
//  Created by Jacob Byerline on 12/9/17.
//  Copyright © 2017 Jacob Byerline, Charles Ho, and Collin Rikkelman. All rights reserved.
//

#include <stdio.h>
// Defines Structure and declares variables to use throughout any function
struct Record
{
    int time;
    double pot;
    double temperature;
    double light;
    int sw0;
    int sw1;
    int sw2;
    int sw3;
};

//Defines function readFile and calls out variables, structure, and files to be used in readFile

int readFile(FILE *infile, struct Record *data){
    // Scans the infile and looks for "(statement)" then returns 1
    if (fscanf(infile,"Press and release switch 0 Release switch 0 ---------------------------\n"))
    {
        return 1;
    }
    
    // Scans infile for "(statement)" after the initial scan above
    // Finds 8 numbers located in specified locations and stored them in data
    // Reassigns the numbers from data to specified variable
    // Then returns 0
    else if(fscanf(infile,
                   "time: %d ms\npotentiometer: %lf\ntemperature: %lf\nlight: %lf\nswitch0: %d\nswitch1: %d\nswitch2: %d\nswitch3: %d\n---------------------------\n",
                   &data->time, // data's address gets linked to time, data gives its value to time
                   &data->pot, // data's address gets linked to pot, data gives its value to pot
                   &data->temperature, // etc. It's like data scans through and gives values to each variable
                   &data->light,
                   &data->sw0,
                   &data->sw1,
                   &data->sw2,
                   &data->sw3) == 8) //Only if it finds 8 values then it returns 0
    {
        return 0;
    }
    //Once the end of the file is reached, returns 1
    else if (fscanf(infile,"ENDENDENDENDENDENDENDENDENDENDENDENDENDEND"))
    {
        return 1;
    }
    //If anything, non specified is found in the file, return 1
    else
    {
        return 1;
    }
}

int main(void){
    
    // Defines the input and output files as well as their file paths
    FILE *infile = fopen("/Users/jacobbyerline/Documents/San Jose/ME30/Programs/ME30 Final/input.txt", "r");
    FILE *outfile = fopen("/Users/jacobbyerline/Desktop/outfile.csv","w");
    
    // Calls for the structure
    struct Record data;
    
    // Prints header to file (note the commas seperate the words in the outfile because it's CSV)
    fprintf(outfile, "Time,Potentiometer,Temperature,Light,SW0,SW1,SW2,SW3\n");
    
    // Allows for 251 iterations of the if statement to account for 250 enteries
    for(int i = 0; i < 251; i++)
    {
        // If value returned from the function readFile is 0, then prints out variables from structure in the specified format
        if (readFile(infile, &data) == 0)
        {
            fprintf(outfile, "%d,%lf,%lf,%lf,%d,%d,%d,%d\n",
                    data.time, // because the variables time, pot, etc., is assigned from data's address, it's referred to as "data.variableName"
                    data.pot,
                    data.temperature,
                    data.light,
                    data.sw0,
                    data.sw1,
                    data.sw2,
                    data.sw3);
        }
        // If value returned from the function readFile is not 0 (i.e. in context with this code, if it's 1 or non specified), then do nothing -- trash it, because it's useless
        else if(readFile(infile, &data) != 1){
        }
    }
    // Closes infile and outfile
    fclose(infile);
    fclose(outfile);
}

