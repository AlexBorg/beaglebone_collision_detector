#include <iostream>
#include <sys/time.h>
#include <fstream>
#include <string>
#include <unistd.h>
#include <native/task.h>
#include <native/queue.h>

#include "opencv2/opencv.hpp"
#include "cv.h"

#define TASK_PRIO  99 /* Highest RT priority */
#define TASK_MODE  0  /* No flags */
#define TASK_STKSZ 0  /* Stack size (use default one) */

using namespace std ;

// simple thread operation.
// it receives data from a queue, casts it to an opencv data type and prints data from it.
void thread2 (void *cookie)
{
  RT_QUEUE first_queue ;
  int err = rt_queue_bind (&first_queue, "first queue", TM_INFINITE) ;

  cout << "thread2 got queue" << endl ;
  int loop = 0 ;
  void* msg ;
  size_t len ;
  while ( loop < 10 ) {
    ++loop ;
    cout << "thread2 loop " << loop << endl ;
    len = rt_queue_receive ( &first_queue , &msg , TM_INFINITE ) ;
    if ( len == 0 )
      continue ;
    CvMat* img_ptr ;
    memcpy ( &img_ptr , msg , len ) ;
    cout << "recv dimention " << img_ptr -> width << "x" << img_ptr -> height << endl ;
  }
}

// simple example thread operation. it just prints the loop count and sleeps 
void thread3 (void *cookie)
{
  int loop = 0 ;
  while ( loop < 10 ) {
    ++loop ;
    cout << "thread3 loop " << loop << endl ;
    sleep ( 1 ) ;
  }
}

int main () {
  cout << "hello world" << endl ;
  int err ;

  // create a queue.
  // TODO: Borg: Because we are all in the same executable, would it be easier to mutex
  //   a standard queue?
  RT_QUEUE first_queue ;
  err = rt_queue_create (&first_queue, "first queue", 100, Q_UNLIMITED, Q_FIFO | Q_SHARED) ;
  
  // create thread example.
  // TODO: Borg: replace with an object that owns it's own thread. We will have to pass
  // the queue to that object.
  RT_TASK thread2_desc ;
  err = rt_task_create(&thread2_desc,
                     "thread 2",
                     TASK_STKSZ,
                     TASK_PRIO,
                     TASK_MODE);
  if (!err)
    rt_task_start(&thread2_desc,&thread2,NULL);

  RT_TASK thread3_desc ;
  err = rt_task_create(&thread3_desc,
                     "thread 3",
                     TASK_STKSZ,
                     TASK_PRIO,
                     TASK_MODE);
  if (!err)
    rt_task_start(&thread3_desc,&thread3,NULL);


  //test read input images
  const char* imgfilename1 = "tsukuba1color.png" ;
  const char* imgfilename2 = "tsukuba2color.png" ;
  cv::Mat img1 = cv::imread(imgfilename1, CV_LOAD_IMAGE_COLOR);
  cv::Mat img2 = cv::imread(imgfilename2, CV_LOAD_IMAGE_COLOR);

  int loop = 0 ;
  while ( loop < 10 ) {
    ++loop ;
    cout << "main thread loop " << loop << endl ;
    CvMat* img_ptr = cvLoadImageM(imgfilename1, CV_LOAD_IMAGE_COLOR); // simulate new image
    cout << "send dimention " << img_ptr -> width << "x" << img_ptr -> height << endl ;
    int msg_sz = sizeof ( CvMat* ) ;
    // push the pointer to the queue. we no longer have ownership of the pointer
    rt_queue_write (  &first_queue , &img_ptr , msg_sz , Q_NORMAL );
    sleep ( 1 ) ;
  }
  
  rt_queue_write (  &first_queue , NULL , 0 , Q_NORMAL ); // empty message to signal end


  return 0 ;
}


