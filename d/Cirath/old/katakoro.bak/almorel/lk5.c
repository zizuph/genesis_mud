/*
	Asmodean, March 19, 1995
	LK5 - Property of Cirath Domain
*/

#include "almorel.h"

inherit LAKE_MASTER;

void
create_lakeside()
{
    set_short("Lakeside street");
    set_long("The street here comes to an end in a circle. Scattered "+
	"in a seemingly random pattern around the circle are large, "+
	"two-story log houses. The bottom story of each of the houses "+
	"contains many hollowed out portions and double-gates, leading "+
	"you to believe that the bottom floors of the houses are "+
	"actually barns. Beyond the string of barns the massive "+
	"protecting wall of Almorel looms in the mist.\n\n");

    add_exit(ALMOREL+"lk4","southeast");
}
