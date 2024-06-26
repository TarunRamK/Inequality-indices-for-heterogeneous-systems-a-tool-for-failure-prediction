#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "bijun_find_cri_value.h"


void main()
{
  int b_runs, num_fib_now;
  float load_percent_now, temp, cri_value;

  //  *# Note: As of now, this code can take Beta values as integers only.*#
  //  *#We can change the code easily to accomidate float for beta.#*
  printf("Enter Number of fibres for all the runs: ");    //number of runs for each beta value
  scanf("%d", &num_fib_now);

  printf("Enter cri_value: ");    //number of runs for each beta value
  scanf("%f", &cri_value);

  printf("Enter load percent for all the runs: ");    //number of runs for each beta value
  scanf("%f", &load_percent_now);

  printf("temperature: ");    //number of runs for each beta value
  scanf("%f", &temp);

  printf("Enter Number of runs: ");    //number of runs for each beta value
  scanf("%d", &b_runs);


  float sq_sum=0.0;  //used in finding root mean square (rms) value.


  int rt=1;

    int beta_count=1;                               //used to keep track of number of runs completed for the same beta value
    while(beta_count<=b_runs)                       //while loop to run several times (i.e., b_runs times) for the same beta
    {





    //##########  This part of code is used to create a Folder (inside another #####
    //##########  folder named "Files") with the current time as the its name. #####
    int hours, minutes, seconds, day, month, year;
    time_t now = time(&now);
    struct tm *local = localtime(&now);

    hours = local->tm_hour;          // get hours since midnight (0-23)
    minutes = local->tm_min;         // get minutes passed after the hour (0-59)
    seconds = local->tm_sec;         // get seconds passed after minute (0-59)

    day = local->tm_mday;            // get day of month (1 to 31)
    month = local->tm_mon + 1;       // get month of year (0 to 11)
    year = local->tm_year + 1900;    // get year since 1900

    char dirname[110] = "";                      //used in creating directory and files
    sprintf(dirname,"Files/Detailed Data/%04d_%02d_%02d_%02d_%02d_%02d_rt%d", year, month, day, hours, minutes, seconds, rt);

    mkdir("Files", 0777);
    mkdir("Files/Detailed Data", 0777);
    mkdir("Files/Time Rate Data", 0777);
    mkdir(dirname, 0777);                                          //creating the directory to store the file

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    /* using nano-seconds instead of seconds */
    srand((time_t)ts.tv_nsec);             //for using rand() in finding probability


    char somechar[10];                           //used to store temporary information to write the data to the files

    FILE *filePointer1;                                      //used to store the memory location of the file
    char model_file[121] = "";
    sprintf(model_file,"%s/model.txt", dirname);
    filePointer1 = fopen(model_file, "w");    //creating the file with name model.txt


    int num_fib=num_fib_now;              //number of fibres for the model
    float thresold_list[num_fib];         //creating an array whose length is num_fib
    float rr=0.0;                         //initilizing a varible rr which will be used to store random number between 0 and 1

    for(int i=0; i<=num_fib; i++)         //creating the model with num_fib fibres and writing the model to the file "model.txt"
    {   
        thresold_list[i]=cri_value;        //creates a fibre with threshold strength using rr and stores it in threshold_list[i]

        //note that p(x) = 10 ^ (-beta*x)

        sprintf(somechar, "%f", rr);                  //converting data to string to write data to the file
        fputs(somechar, filePointer1);                //writing data to the file


        fputs(" ", filePointer1);

        sprintf(somechar, "%f", thresold_list[i]);   //converting data to string to write data to the file
        fputs(somechar, filePointer1);               //writing data to the file

        fputs("\n", filePointer1);                   //going to the next line
    }

    fclose(filePointer1);                            //closes the file

    printf("Model Created!!! Number of Fibres: %d\n",num_fib);





    float thresold_list_copy[num_fib];              //used to store copy of the model (threshold_list)

    for(int i=0; i<=num_fib; i++)                   //copies threshold_list to threshold_list_copy
    thresold_list_copy[i]=thresold_list[i];


    float inv_cri_stress=cri_value;




    for(int i=0; i<=num_fib; i++)           //passing thresold_list to cri_finding function alters the model
    thresold_list[i]=thresold_list_copy[i]; //so thresold_list is loaded with data from thresold_list_copy

    float load_percent=load_percent_now;          //fraction of load to test the model
    float inv_stress=load_percent*inv_cri_stress; //amount of load to test the model

    float tot_stress = inv_stress*(float)num_fib;

    float c=(float)1;

    int time=0;                 //used to measure time
    int broke_count=0;          //to count the number of fibres broken for the present time
    int pre_broke_count=0;      //to remember the number of fibres broken for previous time
    int broke_rate=0;           //used to measure rate at which fibres are breaking for each time
    float prob;                 //used in finding the probablility of a fibre breaking because of noise

    int time_list[100000];         //used to store time
    int broke_count_list[100000];  //used to store number of fibres broke for each time
    int broke_rate_list[100000];   //used to store rate at which fibres are breaking for each time

    time_list[0]=0;                     //assigning the initial value for all the arrays
    broke_count_list[0]=broke_count;
    broke_rate_list[0]=0;
    int cri_count=0;
    float num=0;
    float cri_stress_found=0.0;
    //for(int i=0;i<num_fib_now; i++)
    //printf("%f\n", thresold_list[i]);

    int stable_count=0; 
    while(broke_count<num_fib)          //Running till all the fibres are broken
    {
        

        inv_stress=tot_stress/(float)(num_fib-broke_count); //stress on each fibre

        for(int i=0; i<num_fib;i++)                        //checking a single fibres in each iteration
        {
            if(thresold_list[i]>0.0)                        //checking if the fibre is not already broken
            {
                if(thresold_list[i]<=inv_stress)             //checking if the fibre will break under the stress
                {
                    thresold_list[i]=0.0;                   //changing the status of the fibre to "broken"
                    broke_count++;                          //increasing the count of broken fibres
                }

                if(thresold_list[i]>inv_stress)    //checking if the fibre won't under stress to check
                {                                  //if it break because of noise
                    prob=(inv_stress/thresold_list[i])*exp(  -(1.0/temp) * ( (thresold_list[i]/inv_stress)  -1.0 )  ); //probability that a fibre breaks due to
                    prob=prob;
                    //printf("%f %f %f", thresold_list[i], inv_cri_stress, prob);                                                          //noise t and convert it into percentages
                    //prob = c * e ^ { [-1/t] * [ (sigma/sigmaC) -1 ] }

                    num = (double)rand() / (double)RAND_MAX;                     //creating a random number between 0 and 100
                    //printf(" %f", num);
                    if(num<prob)                                   //checking if random percent is bigger than probablity of breaking
                    {
                        thresold_list[i]=0.0;                      //changing the status of the fibre to "broken"
                        broke_count++;                             //increasing the count of broken fibres
                        //printf(" broke");
                    }
                }
                //printf("\n");


            }
        }

        //printf("%d: %d\n", time, broke_count);
        time++;                                        //increasing time
        broke_rate=broke_count-pre_broke_count;        //calculating broke rate

        time_list[time]=time;                          //adding time to time_list
        broke_count_list[time]=broke_count;            //adding broke_count to broke_count_list
        broke_rate_list[time]=broke_rate;              //adding the present broke_rate to broke_rate_list

        if(broke_count>=num_fib)                        //checking if the bundle failed
        {
            printf("inv stress : %f\n",inv_stress);
            printf("The system has failed with broke count: %d\n",broke_count);
            cri_count++;
            break;
        }
        if(broke_count!=pre_broke_count)
        {
            stable_count=0;
        }

        if(broke_count==pre_broke_count)               //checking if the bundle is stable by check
        {                                              //present and previous number of broken fibres
            stable_count++;
            if(stable_count==10000000000)                      //check if the system is stable for too long (i.e., for 1000 tries)
            {
                printf("inv stress : %f\n",inv_stress);
                printf("The system is way too stable with broke count: %d\n",broke_count);
                break;
            }
        }

        //printf("Running\n");
        //printf("Broke Count: %d/%d    (pre_broke_count: %d)\n", broke_count, num_fib, pre_broke_count);

        pre_broke_count=broke_count;   //changing the number of previous broke_count to
    }                                  //remember for the next iteration of while loop


    for(int i=0; i<=time; i++)
    {
        printf("%d  %d  %d\n",time_list[i], broke_count_list[i], broke_rate_list[i]);
    }


    FILE *filePointer2;                                      //used to store the memory location of the file
    char time_rate_file_name[125] = "";
    sprintf(time_rate_file_name,"%s/time_rate.txt", dirname);
    filePointer2 = fopen(time_rate_file_name, "w");    //creating the file with name time_rate.txt
    char line_p1[5];
    char line_p2[7];
    FILE *filePointer4;
    char time_stamp[40]="";
    sprintf(time_stamp,"%04d_%02d_%02d_%02d_%02d_%02d_rt%d", year, month, day, hours, minutes, seconds, rt);
    char time_rate_file[70]="";
    sprintf(time_rate_file,"Files/Time Rate Data/%s.txt", time_stamp);
    filePointer4 = fopen(time_rate_file, "w");

    for(int i=0; i<=time; i++)                         //code from here is just to store the values in file "time_rate.txt"
    {
        sprintf(line_p1, "%d", i);
        fputs(line_p1, filePointer2);
        sprintf(line_p1, "%d", i);
        fputs(line_p1, filePointer4);

        fputs(" ", filePointer2);
        fputs(" ", filePointer4);

        sprintf(line_p2, "%d", broke_rate_list[i]);
        fputs(line_p2, filePointer2);
        sprintf(line_p2, "%d", broke_rate_list[i]);
        fputs(line_p2, filePointer4);

        fputs("\n", filePointer2);
        fputs("\n", filePointer4);
    }

    fclose(filePointer2);
    fclose(filePointer4);
    
    int fail_time=time_list[time];      //failure time
    int min_rate=broke_rate_list[1];    //used to find minimum rate
    int min_time=0;                     //used to find minimum time

    for(int i=2; i<=(time-1); i++)      //calculating the ratio of t_c and t_min (i.e., t_c/t_min)
    {
        if(broke_rate_list[i]<min_rate)
        {
            min_time=time_list[i];
            min_rate=broke_rate_list[i];
        }
    }

    float ratio_list[b_runs];
    float ratio=((float)fail_time/(float)min_time);    //finding the ratio
    printf("Fail time: %d, Min time: %d, ratio (fail/min): %f\n", fail_time, min_time, ratio);
    ratio_list[beta_count-1] = ratio; //storing all the ratios from the present beta of the present execution in the array ratio_list


    FILE *filePointer3;
    filePointer3 = fopen("Files/average_of_ratios.txt", "a");
    char line2_p1[320]  = "";
    char line2_p2[10] = "";
    char line2_p3[10] = "";
    char line2_p4[10] = "";


    sprintf(line2_p1, "%f", cri_value);
    fputs(line2_p1, filePointer3);

    fputs(" ", filePointer3);

    sprintf(line2_p2, "%f", ratio);
    fputs(line2_p2, filePointer3);

    fputs(" ", filePointer3);

    sprintf(line2_p3, "%d", num_fib_now);
    fputs(line2_p3, filePointer3);

    fputs(" ", filePointer3);

    sprintf(line2_p3, "%f", temp);
    fputs(line2_p3, filePointer3);

    fputs(" ", filePointer3);

    sprintf(line2_p4, "%f", load_percent);
    fputs(line2_p4, filePointer3);

    fputs(" ", filePointer3);

    fputs(time_stamp, filePointer3);

    fputs("\n", filePointer3);

    fclose(filePointer3);

    beta_count++;

    sq_sum = sq_sum + pow(ratio,2); //used to find sum of squares of ratio to calculate rms value

    rt+=1;
    }

    float ms = sq_sum/b_runs;       //finding the mean of squares of ratios

    float rms = sqrt(ms);           //taking square root of ms to find rms value

    printf("RMS: %f", rms);

    char line2_p6[15]="";


    printf("\n");
    printf("\n");
}


//rr=2*ran2(&sd)-1;
//thr[i]=pow(10,-1*beta*rr);
