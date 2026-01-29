
/* Re Albi village. Village's path V.
 * Coded by Marisol (12/5/97)
 * Modified by Marisol (07/28/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1997 */

#pragma strict_types
#pragma no_clone
#include "/sys/stdproperties.h"
#include "/d/Emerald/sys/macros.h"
#define DOOR DOORS+"shop_door_out.c"
#define BUXOM OV_VILLAGE_NPC +"villager01"
#include "defs.h"
inherit OV_VILLAGE;

object buxom;

void
reset_room()
{
  if (!objectp (buxom))
   {
    buxom= clone_object(BUXOM);
    buxom-> move(TO);
   }
}


object door;
void

create_ov_room()
{

    set_long("A village's path in Ovejuno. The villagers are "+
        "going about their business. From the south, the smell of "+
        "cooked food drifts from the village's pub. To the north, "+
        "there is a building with a small wooden sign hanging "+
        "in the entrance.\n");

    add_item("villagers",
        "The villagers of Ovejuno are a dignified lot. They are "+
        "not rich but are proud of their simple life. Although they are "+
        "terrified by the dark menace of the Elven castle outside the "+
        "village. Rumors of curses and haunted souls run wild among "+
        "the villagers. Few want to work there and wish the elves will "+
        "go away. They are mostly goat herders and farmers. They dress "+
        "with simple clothes of earthy colors.\n");

    add_item("building",
        "This is a two-story building made of wood. It has a small "+
        "wooden sign in the entrance. Look like the first floor "+
        "is some sort of store and the second floor is where the "+
        "owner lives with his family.\n");

    add_item("pub",
        "This is The Drunkard Ram, the village's only pub. It is "+
        "a two-story structure like the building across the street. "+
        "The smell of roast meat wafts from the pub's open door, "+
        "inviting any bystander to enter and satisfy hunger and "+
        "thirst.\n");

    add_item(({"sign", "wooden sign"}),
        "It is a wooden sign that reads: General Store.\n");

    add_cmd_item(({"sign", "wooden sign"}), ({"read", "exa", "examine"}),
        "It is a wooden sign that reads: General Store.\n"); 
        
reset_room();

door = clone_object(DOOR);
door->move(TO);

    add_exit("pub_ov.c", "south");
    add_exit("village_ov06", "east");
    add_exit("village_ov04", "west");

}                                                                     
