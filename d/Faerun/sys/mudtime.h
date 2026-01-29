/*
 * Defines for interfacing with the Faerun Time System (FTS)
 */
#ifndef __FAERUN_TIME_DEFS__
#define __FAERUN_TIME_DEFS__

/* Remember to update the path in domain_link.c */
#define CLOCK           ("/d/Faerun/lib/clock")

/*
 * To get a standard reading.
 */
#define TIME            CLOCK->query_time()
#define TIME24          CLOCK->query_time(1)

/*
 * To get a fancy text reading.
 */
#define TIME_DESC       CLOCK->query_time_desc(0,0)
#define TIME_DESC_LONG  CLOCK->query_time_desc(0,0)
#define TIME_DESC_ROOM  CLOCK->query_time_room_desc(0,0)
#define LIGHT_DESC      CLOCK->query_light_type()
#define DAY_PART        CLOCK->query_part_of_day()
#define HORIZION_DESC   CLOCK->query_horizon()

/*
 * To register items.
 */
#define TIME_EVENT(X)   CLOCK->add_event(X)

/*
 * What stage are we in?
 */
#define IS_NIGHT        CLOCK->query_night()
#define IS_DAY          (CLOCK->query_night() == 0)

/*
 * What hour are we in?
 */
#define HOUR            CLOCK->query_hour()
#define HOUR12          CLOCK->query_hour(1)


#endif /* __FAERUN_TIME_DEFS__ */
