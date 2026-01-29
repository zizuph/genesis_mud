/*
   /d/Kalad/sys/time.h
   
   Macros to provide access to Kalad's clock.

   Fysix@Genesis, Oct 1997
 */
#ifndef _KALAD_TIME_DEF
#define _KALAD_TIME_DEF

        // Kalad's clock
#define CLOCK     "/d/Kalad/obj/clock"

        // 24 hour time
#define TIME      CLOCK->query_time()
        // 1 = day, 0 = night
#define DAY       CLOCK->query_day()
        // what hour is it? (1 .. 12)
#define HOUR      CLOCK->query_hour()
        // Is it raining?
        // 0 = no rain, 1 = rain, 2 = a lot of rain
#define RAIN      CLOCK->query_rain()

        // The maximum value of RAIN
#define MAX_RAIN  2

        // Add this property to the room if it's
        // impossible to tell the time
#define ROOM_M_CANNOT_TELL_TIME

#endif
