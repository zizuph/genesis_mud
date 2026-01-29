inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


#include "/d/Cirath/gcamp/defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    object npc = present ("gith", TO);
    if(!objectp(npc))
    {
       bring_room_mob("gith", GITH_NPC+"gith1",1,1);
    }
}


void
create_room()
 {
  set_short("Mountain Trail");
  set_long("Jagged mountains begin their thrust towards the "
  	+"heavens here.  Rocks litter the ground at the base "
  	+"of these massive granite teeth, while the desert "
  	+"has attempted to encroach as much as possible, but is "
  	+"held at bay by the howling winds that scream down from "
  	+"the peaks.  The combination of the cliffs to your north "
  	+"and the high dunes to your east, effectively block "
  	+"travel in those directions.  Southwards, the dry desert "
  	+"continues, eagerly waiting to suck the moisture from "
  	+"your body with its windblown kiss.\n");    
    add_item(({"mountains","mountain","ringing mountains","cliffs"}),
	   "This massive collection of mountains rises to your "
    	+"north and west.  There are tales of the creatures who "
    	+"live in these mountains.\n");
    add_item(({"dunes","dune"}),"The deep dunes ripple and writhe "
    	+"like struggling serpents in the harsh winds.  They make "
    	+"it impossible to go westwards.\n");
    add_item("rocks","They lay strewn about here, obvious remnants "
    	+"of the mountains breaking before the onslaught of the "
    	+"fierce desert winds.\n");
    add_exit(DESERT + "d20","east");
    add_exit(DESERT + "d15","southwest");
    add_exit(DESERT + "d16","south");
    add_exit(DESERT + "d17","southeast");
    set_alarm(1.0,0.0,"reset_room");
}

