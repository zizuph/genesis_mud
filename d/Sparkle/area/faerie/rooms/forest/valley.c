/*
 * The mountain road between Sparkle and Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit FOREST_BASE;

#define ORC_VALLEY  "/d/Genesis/start/human/wild2/orc_vall3"

string statue_check();

string extra_line = "";
int eyes = 0; // 0 = no eyes, 1 = left eye, 2 = right eye, 3 = both eyes full 
int statue_fixed = 0;   // 0 = fixed, 1 = fixed and statue gone

void
create_forest_room()
{
    set_short("A hidden valley in the mountains");
    set_long(s_desc_sky_outside_sky() + " The valley is surrounded by tall mountains. Trees have overgrown the valley, hiding almost everything in it. A collapsed building stands in the clearing with a stone statue. " + extra_line + "\n");

    add_item(({"building", "ruined building", "collapsed building"}),
        "The building looks like it was once an important place. It lies in ruins with trees growing out of it. The stones that were used in the building have fallen over and broken. " + statue_check() + "\n");
    add_item(({"stones", "broken stones", "stone blocks"}),
        "The stone blocks look like they were once perfectly squared They once were part of a grand building. Now they have fallen over, and are cracked and broken.\n");
    add_item(({"valley"}),
        "This is a wide area somewhere in the mountains. It appears that at one time it was the meeting place of a civilization long gone. A collapsed building is all that remains and a stone statue standing in the center of the valley.\n");
    add_item(({"statue"}),
        "@@statue_long@@\n");
    

    set_add_valley();
    add_std_herbs("forest");
    reset_room();

    add_exit(ORC_VALLEY,  "east");
    add_exit(FOREST_DIR + "mtroad02", "west");
}

public void
init()
{
    ::init();

}
void
reset_room()
{
}


string statue_long()
{
   string statuelong;
   
   statuelong = ("The statue seemingly carved from the wall itself."
         + " It is of a man kneeling, with his arms outstretched"
         + " and a peaceful expression on his face. ");
   
   if (eyes == 1)
   {
      
      statuelong += ("There is a faint light from the statues"
            + " head and you notice that there is an empty"
            + " eyesocket. The other holds a green gem which"
            + " is radiating the light. ");
   }
   
   else
   {

      statuelong += ("There is a strong light radiating from"
            + " the statue's head and you notice that both"
            + " eyesockets contain a glowing gems.");
   
   return statuelong;
    }
}


string statue_check()
{
    switch(statue_fixed)
    {
        case 0:
        {
            return " A broken statue lies in the center of the ruined building.";
            break;
        }
        case 1:
        {
            return "" ;
            break;
        }
    }
}
