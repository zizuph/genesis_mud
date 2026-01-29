/* Forest coded by Lord Rastlin */
/* modified by Teth, Feb.13,96  */

#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit FOROUTROOM;

object Grum, Hepp;

void
reset_solace_room()
{
    if (!Grum)
    {
    	Grum = clone_object(MONSTER + "grum");
    	Grum->move_living("xx", TO);
    	Grum->seq_new("do_thing");
    	Grum->seq_addfirst("do_thing","@@arm_me");
    }

    if (!Hepp)
    {
    	Hepp = clone_object(MONSTER + "hepp");
    	Hepp->move_living("xx", TO);
    	Hepp->seq_new("do_thing");
    	Hepp->seq_addfirst("do_thing","@@arm_me");
    }
}

void
create_solace_room()
{
    set_place(HILL);
    set_long_desc("You are in the goblin camp. This is the northeast " +
      "corner of the goblin encampment. Nestled in the " +
      "foothills of Sentinel Peaks, this rocky terrain is perfect goblin " +
      "habitat. This area is cleaner than most, with no litter " +
      "strewn about or half-eaten meat. There is a huge dark cave " +
        "to the north. The northeast trail continues into foothills " +
        "here, but also makes a branch into the cave. You can " +
        "leave this gruesome and smelly place by going northeast " +
        "or southwest.");
    add_item(({"cave", "dark cave", "huge cave", "huge dark cave"}), "It " 
     +"is a dark foreboding cave. A peculiar smell radiates from it, " +
      "somewhat different from the scent of goblins.\n");  

    add_exit(TDIR + "hill2", "southwest");
    add_exit(TDIR + "toedecave", "north");
    add_exit("/d/Krynn/tant/room/road1", "northeast", 0, 1);
   
    OUTSIDE;

    reset_room();

    set_alarm(1.0, 0.0, reset_room);
}
