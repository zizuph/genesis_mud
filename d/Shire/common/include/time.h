/*
 * time.h
 *
 * This file defines ranges for time periods.
 *
 * For instance:
 *
 * switch (clock->query_hour())
 * {
 *     case EARLY_NIGHT:
 *	   .
 *	   .
 * }
 *
 */


#ifndef _time_h_
#define _time_h_ 

#define EARLY_NIGHT	21..24
#define LATE_NIGHT	0..4
#define EARLY_MORNING	5..7
#define MORNING 	8..11
#define NOON		12
#define AFTERNOON	13..16
#define EVENING 	17..20

#define T_NIGHT 	"night"
#define T_DAY		"day"

#define T_MOON		"moon"

#define T_EARLY_NIGHT	"early night"
#define T_LATE_NIGHT	"late night"
#define T_EARLY_MORNING "early morning"
#define T_MORNING	"morning"
#define T_AFTERNOON	"afternoon"
#define T_EVENING	"evening"

#ifndef CLOCK
#define CLOCK           "/d/Gondor/common/obj/clock"
#endif

#endif
