/**
 * Room in the Archer Guild
 *
 * Navarre November 23th 2007.
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../guild.h"
inherit "/d/Krynn/std/room";

void
reset_krynn_room()
{
}

void
create_krynn_room()
{

    set_long("You are walking high up in the trees. The branches have been bent and shaped to fit " +
             "the needs of the elves who live here. The area you are overlooking down on the ground " +
             "is surrounded by a thick wall of bushes and trees. This seems like a perfect place to " +
             "hideout or setup a camp.\n" +
             "Directly to your right is a camouflaged hut resting snugly between the trunks of two " +
             "enourmous trees.\n");

    set_short("You are walking high up in the trees");    
    add_item(({"tree", "big tree", "oak", "big oak"}), "There is a big tree in this room, climbing it will " +
                                                       "allow you to reach the ground safely.\n");
    add_item("area", "You see the qualinesti elves camping in the woods below you.\n");
    add_item(({"trees", "bushes"}), "Bushes and trees are everywhere in the forest " +
               "below you, they make this a well suited place to hide.\n");
    add_item(({"wall", "walls", "thick wall", "thick walls"}), "Walls of bushes and " +
               "trees makes it impossible to see far into the forest.\n");
 
    add_item("hideout", "The thick trees hides you well here.\n");
    add_item(({"camp", "below"}), "The qualinesti camp is down below.\n");
    add_item(({"hut", "camouflaged hut"}), "It is directly to your right.\n");

    OUTSIDE;
    add_exit(ROOMS + "hut_entrance", "east", 0);
    reset_room();
}


/**
 * The function that lets the player climb down to the ground
 */
int climb_down(string args)
{
    if(!args)
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if(args != "down" && args != "tree" && 
       args != "big tree" && args != "oak" &&
       args != "big oak" && args != "down the tree" &&
       args != "down tree" && args != "the tree")
    {
        notify_fail("Climb what? Down?\n");
        return 0;
    }
   TP->catch_tell("You climb down the tree.\n");
   tell_room(environment(TP), QCTNAME(TP)+" climbs down the tree.\n", TP);
   TP->move_living("M", JOINROOM, 1, 0);
   return 1;
}


public void init()
{
  ::init();
  add_action(climb_down, "climb");
}
