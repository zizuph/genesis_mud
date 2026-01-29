/*
   Pax Tharkas, Ground level, Smelting cavern and mill.

   mill_cavern1.c
   --------------

   Coded ........: 95/03/03
   By ...........: Jeremiah

   Latest update : 95/04/04
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXINROOM;

void
create_pax_room()
{
   set_short("Inside cavern");
   set_long("You are standing just inside a large cave. The cave " +
            "continues east, deeper into the mountain. The cave " +
            "is lit by a flickering red light, coming from the east, " +
            "giving the walls an appearance as if they were glowing. " +
            "Acrid, sulphurous smoke billows into the cave, from the " +
            "east, hanging like low yellowish clouds under the " +
            "domelike cave ceiling. The air in here is hot and " +
            "dry.\n");
	
   INSIDE;
 
   add_item(({"wall", "walls"}), "Stone walls, given a glowing " +
            "appearance by the red flickering light coming from " +
            "the east end of the cave.\n");

   add_item(({"smoke", "cloud", "clouds"}), "Acrid, sulphurous " +
            "smoke, coming from the east end of the cave, hanging " +
            "like low yellow clouds under the domelike cave ceiling.\n");

   add_item(({"light", "red light"}), "A flickering red-orange light " +
            "coming from the east end of the cave.\n");

   set_tell_time(40);
   add_tell("Suddenly you hear a loud crash!, like rock hitting " +
       "hard onto rock.\n");
   add_tell("You hear a metallic ringing sound, echoing throughout " +
       "the cave.\n");
   
   add_exit(COURT_YARD + "mill_cavern2", "east", 0);
   add_exit(COURT_YARD + "court_yard2", "west", 0);
}

