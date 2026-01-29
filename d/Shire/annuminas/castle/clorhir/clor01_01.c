#pragma strict_types;
#pragma save_binary;

inherit "/d/Shire/std/room";

#include "defs.h"
#include <formulas.h>
#include <money.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>

#define VIEWED_MOSAIC  "_viewed_mosaic_"

//** Prototypes **//

public void
create_shire_room()
{
  set_short("A ruined entryway");
  set_long("You stand in the middle of an ornate hallway. Statues line the walls. " +
           "A large mosaic sits in the middle of the floor, partially obscued by a " +
           "pile of rubble from the collapsed ceiling.\n");

   add_item(({"statue"}),
   "These are statues of warriors, dressed for battle.\n");

   add_item(({"statues"}),"The statues are dusty and haven't been cleaned for a " +
           "long time. Otherwise, your search reveals nothing special.\n");

   add_item("mosaic", "@@test_mosaic@@");
   add_item("center", "@@test_center@@");
   add_item(({"marks","scuff marks"}), "@@test_marks@@");

  add_prop(ROOM_I_INSIDE,1);
  
  reset_shire_room();
}

string
test_mosaic()
{
   TP->add_prop(VIEWED_MOSAIC, 1);
   return("This is a beautiful mosaic of blue and red tiles. " +
         "The tiles appear to start at the center and circle ever outward " +
         "in a geometric representation of infinity.\nThere are scuff " +
         "marks on the floor.\n");
}


string
test_center()
{
   if (TP->query_prop(VIEWED_MOSAIC))
      return ("Although abstract, you think the center " +
            "of the mosaic represents a heart. Half of the " +
            "heart is red, the other half blue.\n");
    else
      return "You see nothing special.\n";
}

string
test_marks()
{
    if (TP->query_skill(SS_TRACKING) <= 30)
    {
        return("The scuff marks appear to have come from an animal with claws.\n");
        say(QCTNAME(TP) + "kneels down and examines the floor closely.\n");
    }
    else if ((TP->query_skill(SS_TRACKING) > 30) && (TP->query_skill(SS_TRACKING) <= 40))

    {
        return("These are goblin tracks!\n");
        say(QCTNAME(TP) + "kneels down and examines the floor closely.\n");
    }
    else if (TP->query_skill(SS_TRACKING) > 50)
    {
        return("These are the tracks of very, very large goblins. Many, " +
        "many goblins have passed through this room, and often. The tracks " +
        "enter and exit a hole in the rubble. You're not sure that you want " +
        "to explore further on your own.\n");
        say(QCTNAME(TP) + "kneels down and examines the floor closely.\n");
    }
    else
    {
       return("You aren't sure what made these marks.\n");
    }
}
