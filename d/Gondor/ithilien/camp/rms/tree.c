#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>


public void
create_gondor()
{
    set_short("a tree");
    set_long("You are high up in the tree.  " +
      "The leaves and branches move slightly in the wind, " +
      "a subtle reminder of your unnatural distance from the " +
      "ground.  " +
      "Returning to the forest floor would not be difficult, " +
      "as there are plenty of branches in the immediate area.  " +
      "\n");

    add_item(({"grass","ground","trail"}),"The ground is " +
      "far below you, making you a little unsure whether " +
      "climbing up here was a good idea.  " +
      "\n");

    add_item(({"tree","trees"}),"You are in one of the larger trees " +
      "in this area, though there are plenty of trees nearby.\n");

/*
    add_item(({"nearby tree","nearby trees"}),
      "The closest tree has many branches that stretch " +
      "close to you.\n");
*/


    add_item(({"branches","branch"}),"The branches are very " +
      "thick and concealing.\n");
    add_prop(ROOM_I_INSIDE, 0);
    add_exit(CAMP_ROOM_DIR + "trail4","down");

}

