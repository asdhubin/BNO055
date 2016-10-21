#include <unistd.h>
#include <iostream>
#include <signal.h>
#include "bno055.hpp"

#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<sstream>
#include<cmath>

using namespace std;

//convert float numbers to a string
std::string float_to_str(float number1,float number2,float number3){
    std::ostringstream buff;
    buff<<number1<<" "<<number2<<" "<<number3<<"\n\r";
    return buff.str();
}


int shouldRun = true;

void sig_handler(int signo)
{
  if (signo == SIGINT)
    shouldRun = false;
}


int main(int argc, char **argv)
{
  signal(SIGINT, sig_handler);
//! [Interesting]

  // Instantiate an BNO055 using default parameters (bus 0, addr
  // 0x28).  The default running mode is NDOF absolute orientation
  // mode.
  upm::BNO055 *sensor = new upm::BNO055();

  // First we need to calibrate....
  cout << "First we need to calibrate.  4 numbers will be output every"
       << endl;
  cout << "second for each sensor.  0 means uncalibrated, and 3 means"
       << endl;
  cout << "fully calibrated."
       << endl;
  cout << "See the UPM documentation on this sensor for instructions on"
       << endl;
  cout << "what actions are required to calibrate."
       << endl;
  cout << endl;

  // do the calibration...
  while (shouldRun && !sensor->isFullyCalibrated())
    {
      int mag, acc, gyr, sys;
      sensor->getCalibrationStatus(&mag, &acc, &gyr, &sys);

      cout << "Magnetometer: " << mag
           << " Accelerometer: " << acc
           << " Gyroscope: " << gyr
           << " System: " << sys
           << endl;

      sleep(1);
    }

  cout << endl;
  cout << "Calibration complete." << endl;
  cout << endl;

  /*----------------------------------------------------*/
  //create a socket
    int sock;
    struct sockaddr_in server;
    //char message[1000] , server_reply[2000];
    float message[3];
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    /*Attention! Please check the IP and port. */
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");
  //create a socket done
  /*----------------------------------------------------*/

  // now output various fusion data every 250 milliseconds
  while (shouldRun)
    {
      float w, x, y, z;
      sensor->update();
      sensor->getEulerAngles(&x, &y, &z);
      cout << "Euler: Heading: " << x
           << " Roll: " << y
           << " Pitch: " << z
           << " degrees"
           << endl;

      message[0]=x;meesage[1]=y;message[2]=z;
      //strcpy(message,float_to_str(x,y,z).c_str());//float to string
      if( send(sock , message , sizeof(float)*3, 0) < 0){  //send data
                puts("Send failed");
                return 1;
      }

      usleep(40000);//25Hz
    }

//! [Interesting]

  cout << "Exiting..." << endl;

  delete sensor;

  return 0;
}
