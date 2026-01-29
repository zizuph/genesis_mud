/*
    Roundabout in the west of Calia, from which paths run off
    to Gelan, Argos, the docks of Calia and Mount Kyrus.

    Digit 02 FEB 95
    Modified, Maniac, 10.5.95, 23/5/95
    Added Deck description, exit to depot to Argos, Zima, 9/29/95

    Introduced check to protect Calians and their team-mates. If 
    they are still here five seconds after entering here and they 
    are in danger, the guard pulls them in, otherwise the check
    is repeated every five seconds until there is no-one to 
    protect. Most of the code for this is in check_out.c. Maniac, 6/7/00

*/

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "road.h"
#include "/d/Calia/mountain/special/enter_west.c"


int
message()
{
#ifndef GELAN_ROAD_CLOSED
    return 0;
#endif
    write("Sorry, Gelan is closed for an hour or two for " +
        "reconstruction.\n");
    return 1;
}

void
create_room()
{
    set_short("A large roundabout");
    set_long("You find yourself at a large roundabout, at the centre " +
      "of which is an immense boulder. Roads and paths run off the " +
      "roundabout to the north, south, east and west, while to the " +
      "northwest you see a large training hall and to the southwest "+
      "a deck walled by tall pillars. The well kept road " +
      "running north leads to the mighty gates of Gelan, capital of " +
      "Calia, which you are quite close to now. To the west lie the busy " +
      "docks of Calia - you can feel the fresh, invigorating sea breeze " +
      "from that direction. The east path leads off the roundabout into " +
      "a dense forest, while to the south a cobbled road leads out " +
      "across open countryside towards Mount Kyrus and the Crystalline " +
      "Palace of Caliana, home of the Calian Warriors.\n");
 
    add_item(({"hall", "training hall", "large training hall", "large hall"}),
            "The large training hall is the Adventurer's Guild of Calia.\n");
    add_item(({"road", "roads"}), "A well kept road runs off north " +
            "from the roundabout, towards the nearby gates of Gelan, " +
            "while a cobbled road runs off to the south into the " +
            "countryside.\n");
    add_item(({"well kept road", "north road", "north branch"}),
            "A well kept road runs off north from the roundabout, " +
            "towards the nearby gates of Gelan.\n");
    add_item(({"cobbled road", "south road", "south branch"}),
            "A cobbled road runs off to the south into the " +
            "open countryside, towards Mount Kyrus and the " +
            "Crystalline Palace of Caliana, home of the Calian " +
            "Warriors.\n");
    add_item(({"path", "paths", "east path"}),
            "A path runs off to the east into a dense forest.\n");
    add_item(({"roundabout", "large roundabout"}), "A wide circular road " +
        "around an immense boulder, with branches running off it to the " +
        "north, south, east and west.\n");
    add_item("boulder", "@@boulder_desc");
    add_item(({"Gelan", "gelan", "town"}),
        "This is a great and beautiful town, capital of Calia, surrounded "+
        "by a stone wall.\n");
 
    add_item(({"deck","depot"}),
       "It is a large rectangular deck which sits in the southwestern "+
       "corner of the road. It is walled by a line of pillars on its "+
       "four sides.\n");
    add_item("pillars",
       "The pillars are set around the edges of the rectangular deck "+
       "to the southwest, enclosing the open-air area which has no "+
       "roof.\n");

    add_exit(ROAD + "adv_guild", "northwest");
    add_exit(ARGOS_DEPOT,      "southwest");
    add_exit(ROAD + "road18","south");
    add_exit(ROAD + "road20","west");
    add_exit(GELAN_ROAD, "north", "@@message");
    add_exit(ARGOS_PATH, "east");
}


/*
 * Function:    enter_inv
 * Description: called when an object enters this room. This 
 *              instance checks whether Calians need protecting
 *              in combat. 
 */ 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 
    enter_calian_protection_room(ob, from); 
}


void
init()
{
    ::init();
    add_action("enter_door", "knock");
}
