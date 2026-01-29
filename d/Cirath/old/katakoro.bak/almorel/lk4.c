/*
	Asmodean, March 19, 1995
	LK4 - Property of Cirath domain.
*/

#include "Lakes.h"

#include "almorel.h"

inherit LAKE_MASTER;

void
create_lakeside()
{
   set_short("Lakeside street");
   set_long("The street here is dangerously close to the shore of "+
	"The Lake of Mist. The snow-packed and ice-slick street also "+
	"banks slightly in the direction of the lake, making it quite "+
	"easy for someone to slip into the water. All of the houses "+
	"along the street have double-walled weather protection facing "+
	"the lake. To the east, through the bank of fog covering the "+
	"lake, the dark shadow of the tower of Raumkreml looms over "+
        "the steaming water. To the southeast, people mill about on "+
	"the bridge crossing from the shore to the tower of Raumkreml.\n\n");

    add_exit(ALMOREL+"bg","southeast");
    add_exit(ALMOREL+"lk5","northwest");
}
