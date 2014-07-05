//============================================================================
// Name        : test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "BBBiolib.h"
#include <sys/time.h>
#include <fstream>
#include <string>

using namespace std;


int fstreamtest ()
{
 std::fstream fs;

 fs.open("/sys/kernel/debug/omap_mux/gpmc_ad4");
 fs << "7";
 fs.close();
 fs.open("/sys/class/gpio/export");
 fs << "32";
 fs.close();
 fs.open("/sys/class/gpio/gpio32/direction");
 fs << "out";
 fs.close();
 fs.open("/sys/class/gpio/gpio32/value");
 fs << "1"; // "0" for off
 fs.close();
 // select whether it is on, off or flash

 timeval startTime , endTime ;
     gettimeofday(&startTime, NULL);

     int loop = 0 ;
     while ( loop < 10000 )
     {
		fs.open("/sys/class/gpio/gpio32/value");
		fs << "1"; // "0" for off
		fs.close();
		fs.open("/sys/class/gpio/gpio32/value");
		fs << "0"; // "0" for off
		fs.close();
     	++loop ;
     }

     gettimeofday(&endTime, NULL);

     long seconds , useconds ;
     double duration ;
     seconds  = endTime.tv_sec  - startTime.tv_sec;
     useconds = endTime.tv_usec - startTime.tv_usec;

     duration = seconds + useconds/1000000.0;

     cout << "duration = " << duration << endl ;


 return 0;
}



int bbiotest ()
{

	cout << "1" << endl ;
    iolib_init();
    cout << "2" << endl ;
    iolib_setdir(8,11, BBBIO_DIR_IN);
    cout << "3" << endl ;
    iolib_setdir(8,12, BBBIO_DIR_OUT);
    cout << "4-2" << endl ;
/***/
    int del;

    while(1)
    {
        if (is_high(8,11))
        {
            del=100; // fast speed
        }
        if (is_low(8,11))
        {
            del=500; // slow speed
        }

        pin_high(8,12);
        iolib_delay_ms(del);
        pin_low(8,12);
        iolib_delay_ms(del);

    }
/*****
    timeval startTime , endTime ;
    gettimeofday(&startTime, NULL);

    int loop = 0 ;
    while ( loop < 10000 )
    {
    	pin_high(8,12);
    	pin_low(8,12);
    	++loop ;
    }

    gettimeofday(&endTime, NULL);

    long seconds , useconds ;
    double duration ;
    seconds  = endTime.tv_sec  - startTime.tv_sec;
    useconds = endTime.tv_usec - startTime.tv_usec;

    duration = seconds + useconds/1000000.0;

    cout << "duration = " << duration << endl ;
// ******/

    iolib_free();
	return 0;
}


int main() {
	cout << "!!!Hello beaglebone!!!" << endl; // prints !!!Hello World!!!

//    fstreamtest () ;
    bbiotest () ;

	return 0 ;
}
