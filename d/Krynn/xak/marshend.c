/* Xak Tsorath coded by Percy */

#include "xlocal.h"
inherit MARSHBASE

void
create_marsh() 
{
    set_long("You are in the cursed lands, a truly dismal place in"
	     + " every sense of the word. All around you is a seemingly"
	     + " endless marsh swamp except to the southwest where you can"
	     + " see a trail leads out of the marsh and up through a range"
	     + " of mountains. Danger seems to ooze from the swamp's nauseous"
	     + " surface.\n");
    
    add_exit(TDIR + "marsh7.c", "east", "@@cross", 5);
    add_exit(TDIR + "trail.c", "southwest", 0);
}


