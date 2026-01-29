/* A valley in the southern Blackwall mountains.
   Code (c) 2000 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include <stdproperties.h>
#include "/d/Emerald/sys/weather.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    ::create_valley_room();
    
    set_short("Wide valley in the Blackwall mountains.");
    set_em_long("In a wide valley in the southern portion of the "+
		"Blackwall mountains. A few small, isolated mountains "+
		"lie to the south of the valley while taller, steeper and "+
		"more foreboding peaks are commonplace to the north. The "+
		"valley rises and narrows to the west, while it descends "+
		"towards a lush forest to the southeast.\n");
 
    add_prop(ROOM_I_HIDE, 20);

    set_highvalley_room();

    add_item(({"mountains", "blackwall", "Blackwall", "blackwall mountains",
		 "tall peaks", "range", "main range"}),
	     "Tall peaks of black rock make up the Blackwall mountains. "+
	     "The main range is north of here, while only a few small "+
	     "mountains lie to the south.\n");

    add_item(({"small mountains", "isolated mountains"}),
	     "A few isolated, relatively small mountains lie to the south "+
	     "of the valley.\n");

    add_item(({"forest", "fringe", "southeastern fringe"}),
	     "An vast expanse of lush forest lines the southeastern fringe "+
	     "of the mountains and is just barely visible from here.\n");

    remove_item("sky");
    add_item(({"sky"}),
	     "Much of the sky is obscured by the mountains which surround "+
	     "the valley. " + WEATHER_DESC_SKY + "\n"); 
	    	     
    add_item(({"rocks", "rock", "black rock"}),
	     "The mountains are made of a coal-black basalt.\n");

    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_45", "southeast", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_43", "west", 0, 4);
}

/* This sterile area has no particular smell to it, therefor the
   default valley function is masked with a blank one. */

public void
hook_smelled(string arg)
{
}






