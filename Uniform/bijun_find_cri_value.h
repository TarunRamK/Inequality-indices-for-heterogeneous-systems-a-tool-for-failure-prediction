#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

bool is_broke(float num_fib, float thrs_list[], float test_cri)
{   
    float tot_stress=test_cri*num_fib;
    int broke_count    = 0;
    int pre_broke_count= 0;
    while(broke_count<num_fib)          //Running till we get a result
    {
        float inv_stress;
        inv_stress=tot_stress/(float)(num_fib-broke_count); //stress on each fibre
        for(int i=0; i<=num_fib; i++)                        //checking a single fibres in each iteration
        {
            if(thrs_list[i]>0.0)                        //checking if the fibre is not already broken
            {
                if(thrs_list[i]<inv_stress)             //checking if the fibre will break under the stress
                {
                    thrs_list[i]=0.0;                   //changing the status of the fibre to "broken"
                    broke_count++;                          //increasing the count of broken fibres
                }
            }
        }

        if (broke_count==num_fib)
        return true;

        if (broke_count==pre_broke_count)
        return false;

        pre_broke_count=broke_count;
    }
}






float bijun_cri_finding(float avg_val, float devi, int num_fib, float thresold_list[])
{
    float thresold_list_copy2[num_fib];                       ////creating a copy
    for(int i=0; i<=num_fib; i++)
    thresold_list_copy2[i]=thresold_list[i];


    float cri_stress_found=0.0;
    float epsol=0.000001;
    float test_cri = avg_val;
    bool not_found = true;
    bool test = true;
    int run=1;

    while(not_found)
    {   
        for(int i=0; i<num_fib; i++)
        thresold_list[i] = thresold_list_copy2[i];


        test = is_broke(num_fib, thresold_list, test_cri);
        for(int i=0; i<num_fib; i++)
        thresold_list[i] = thresold_list_copy2[i];

        //if (run<=100){
        //printf("Run No: %d, test_cri: %f ", run, test_cri);
        //printf("broke: %s\n", test ? "true " : "false ");}
        //run++;

        if(test==true)
        {
            bool check1 = is_broke(num_fib, thresold_list, test_cri-epsol);
            for(int i=0; i<num_fib; i++)
            thresold_list[i] = thresold_list_copy2[i];

            if(check1==false)
            {
                cri_stress_found=test_cri;
                not_found=false;
                return cri_stress_found;
            }

            test_cri = test_cri-devi;
            devi = devi/2.0;
            continue;
        }

        if(test==false)
        {
            bool check2 = is_broke(num_fib, thresold_list, test_cri+epsol);
            for(int i=0; i<num_fib; i++)
            thresold_list[i] = thresold_list_copy2[i];


            if(check2==true)
            {
                cri_stress_found=test_cri+epsol;
                not_found=false;
                return cri_stress_found;
            }

            test_cri = test_cri+devi;
            devi = devi/2.0;
            continue;
        }
    }

    return cri_stress_found;
}