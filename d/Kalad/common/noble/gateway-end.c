/* This room was coded by Feofil */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void create_room()
{
	::create_room();
	set_short("On the intersection of Gateway Lane and End Street");
	set_long(BS("You are standing at the intersection of the Gateway "
+ "Lane and the End Street. This is the last point of Kabal to the northwest "
+ "direction. From this point the Market Street starts its way to the "
+ "southeast. It is the only noisy street in this district: farmers use it "
+ "to deliver different goods from the marketplace to noblemen residences. "
+ "The End Street heads to the south along the city's border.\n"));

	hear_bell = 2;                   /*  2 = outdoor, 1 = indoor */
   
	add_exit(NOBLE(gateway/s1),"east",0,0,-1);
	add_exit(NOBLE(market/s5),"southeast",0,0-1);
	add_exit(NOBLE(end/s6),"south",0,0,-1);

}

