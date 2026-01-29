/*
   Pax Tharkas, Low level, staircase to ground_level.

   stair_to_gl.c
   -------------

   Coded ........: 95/01/11
   By ...........: Jeremiah

   Latest update : 95/02/03
   By ...........: Jeremiah

*/


inherit "/d/Krynn/pax/tharkas/misc/Ilamp_base";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

void
create_pax_room()
{
   add_the_lamp();

   set_short("dark stairwell");
   set_long("@@room_descr");

   INSIDE;

   add_item(({"stair", "stairs"}), "These are solid stone stairs. It " +
            "looks as if the entire stair is carved out of one piece " +
            "of rock.\n");

   set_alarm(30.0,360.0,"do_flicker");

   add_exit(GROUND_LEVEL +"corridor5", "up",0,1);
   add_exit(LOW_LEVEL + "corridor5", "down",0);
} 


string
room_descr()
{
   return "You are standing in a dark narrow stairwell. The walls and " +
          "stairs look as if they were made of solid rock. There is a " +
          "small iron lamp hanging on the wall. " + 
          "There's a vague draft here, coming from above.\n";
}


void
do_flicker()
{
   tell_room(TO,"The light from the iron oil lamp flickers slightly.\n");
}

