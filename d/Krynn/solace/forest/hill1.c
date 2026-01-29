/* Forest coded by Lord Rastlin */
/* modified by Teth, Feb.13,96  */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>

inherit FOROUTROOM;

#define BOTTLE    OBJ + "bottle"

int bottle_found;

void
create_solace_room()
{
    set_place(HILL);

    set_long_desc("You have entered a goblin camp. It is probably " +
      "the encampment for the goblins that patrol Solace. Nestled in the " +
      "foothills of Sentinel Peaks, this rocky terrain is perfect goblin " +
      "habitat. Signs of goblins are everywhere, whether it be litter " +
      "strewn about or half-eaten meat. There appear to be open caves " +
      "to the north and east. The northeast trail leads further into the " +
      "camp, while you can leave this gruesome and smelly place by going " +
      "southwest.");
    add_item(({"encampment", "camp"}), "You're standing in it. It's a " +
             "poorly fortified encampment.\n");
    add_item("litter", "Messy, messy! But it is typical of goblins to live " +
      "in filth and squalor. The litter mostly consists of rusting and " +
      "discarded metal items. Nothing too much of interest.\n");
    add_item(({"foothills","hills","mountain range","mountains",
               "Sentinel Peaks", "sentinel peaks", "Peaks", "peaks"}),
               "These surround you, giving the area a measure of " +
               "distinction.\n");
    add_item("terrain", "It is somewhat hilly, caused by this area's " +
             "location in the Sentinel Peaks mountain range.\n");
    add_item(({"meat", "half-eaten meat"}), "Maggot-infested and stomach-" +
      "wretching, no goblin would even consider eating it now!\n");
    add_item(({"cave", "caves"}), "They appear to be well-lit. Most " +
      "likely, they are the home of more goblins.\n");  
    add_search("litter",7,"find_bottle",1);

    add_exit(TDIR + "nforest4", "southwest");
    add_exit(TDIR + "hill2", "northeast");
    add_exit(TDIR + "hill4", "north");
    add_exit(TDIR + "hill5", "east");
   
    OUTSIDE;  /* An outside room */
   
    set_alarm(1.0,0.0,"reset_room");
}

void
reset_solace_room()
{
  {  bottle_found = 0;
  }

  {  if (!present("goblin"))
      clone_object(MONSTER + "goblin")->move_living("xx", TO);
  }
}

string
find_bottle(object who, string what)
{
    if (bottle_found)
    {
        return 0;
    }

    say(QCTNAME(who) + " discovers something among the litter.\n");
    clone_object(BOTTLE)->move(TO, 1);
    bottle_found = 1;

    return "You discover a broken bottle among the litter.\n";
}



