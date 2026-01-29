/*
   Pax Tharkas, Ground level, Smelting cavern and mill.

   mill_cavern2.c
   --------------

   Coded ........: 95/03/03
   By ...........: Jeremiah

   Latest update : 95/07/28
   By ...........: Jeremiah

   Added some add_items, Teth, April 25, 1996
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
   set_short("End cavern");
   set_long("You are standing at the east end of a large cave. There is " +
            "a large hole in the ceiling in the far end of the cave. To " +
            "the left of you, huge vats sit atop large fires. Great " +
            "bellows feed air to these fires of burning coal. Sulphurous " +
            "smoke belches from the large vats, in great yellow clouds, " +
            "filling the cave ceiling with low hanging clouds. Gully " +
            "dwarves scramble to and fro in their usual hectic manner.\n");

   INSIDE;
	
   add_item("hole", "A large hole in the cave ceiling. It looks like " +
            "a vertical shaft leading upwards, to the surface of the " +
            "mountain.\n");

   add_item(({"vats", "huge vats", "blackened pots", "pots", "iron pots",
            "blackened iron pots"}), "These are blackened iron pots, " +
            "sitting atop large fires.\n");

   add_item(({"bellows", "great bellows"}), "Operated by the gully " +
            "dwarves, these are used to increase the flames beneath the " +
            "vats.\n");

   add_item(({"gully dwarves", "dwarves"}), "They scurry about doing the " +
            "best they can to serve their enslaver.\n");

   add_item(({"clouds", "hanging clouds", "great clouds", "yellow clouds",
            "great yellow clouds", "low clouds", "low hanging clouds"}),
            "These clouds give the air in here a hazy look, and are most " +
            "likely the source of the sulfur smell that reaches your nose.\n");

   add_item(({"smoke", "sulphurous smoke"}), "The smoke reeks with the " +
            "rotten-egg smell of sulfur.\n");

   set_tell_time(40);
   add_tell("Crash! A batch of red rock falls through the " +
       "hole in the ceiling. A group of gully dwarves fiercely " +
       "attacks the red rock with hammers, and smash the rock into " +
       "gravel.\n");
   add_tell("You hear a metallic ringing sound, echoing " +
       "throughout the cave, as the gully dwarves fiercely hammers " +
       "away on the red rock.\n");
   add_tell("A group of gully dwarves carries pulverized red rock " +
       "across the cave, and drops it into the huge vats.\n");
   add_tell("A group of gully dwarves piles coal onto the large " +
       "fires. Clouds of yellow smoke belches from the vats.\n");

   add_exit(COURT_YARD + "mill_cavern1", "west", 0);
}




