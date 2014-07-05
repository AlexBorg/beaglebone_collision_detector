#include <iostream>
#include <sys/time.h>
#include <fstream>
#include <string>
#include <native/task.h>

#define TASK_PRIO  99 /* Highest RT priority */
#define TASK_MODE  0  /* No flags */
#define TASK_STKSZ 0  /* Stack size (use default one) */

using namespace std ;

void thread2 (void *cookie)
{
  int loop = 0 ;
  while ( loop < 10 ) {
    ++loop
    cout << "thread2 loop " << loop << endl ;
    sleep ( 1 ) ;
  }
}

void thread3 (void *cookie)
{
  int loop = 0 ;
  while ( loop < 10 ) {
    ++loop
    cout << "thread3 loop " << loop << endl ;
    sleep ( 1 ) ;
  }
}

int main () {
  cout << "hello world" << endl ;
  int err ;
  RT_TASK thread2_desc ;
  err = rt_task_create(&thread2,
                     "thread 2",
                     TASK_STKSZ,
                     TASK_PRIO,
                     TASK_MODE);
  if (!err)
    rt_task_start(&thread2_desc,&thread2,NULL);

  RT_TASK thread3_desc ;
  err = rt_task_create(&thread3,
                     "thread 3",
                     TASK_STKSZ,
                     TASK_PRIO,
                     TASK_MODE);
  if (!err)
    rt_task_start(&thread3_desc,&thread3,NULL);

  int loop = 0 ;
  while ( loop < 10 ) {
    ++loop
    cout << "main thread loop " << loop << endl ;
    sleep ( 1 ) ;
  }

  return 0 ;
}
