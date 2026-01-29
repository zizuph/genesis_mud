/*
 * Garden Room of the Elemental Garden of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "../defs.h"

inherit GARDEN_ROOM_BASE;

// Defines

// Prototypes

public void
create_garden_room()
{
    set_short("Inside a walled garden");
    set_long("This is the entrance of the walled garden surrounding the "
        + "Elemental Temple of Calia. To the north you see an ornate "
        + "entrance into the actual temple. To the south, you see the "
        + "exit that leads to the valley outside. The garden is in the "
        + "process of being prepared. You see evidence of some recent "
        + "work among the various gardening tools that are carefully "
        + "placed along the walls.\n\n");
                   
    try_item( ({ "north", "ornate entrance", "entrance", "temple" }),
        "The entrance to the temple looks to be composed of multiple "
      + "archs that reach as high as the height of 10 grown men. From here "
      + "you can see through the entrance into the large dome that "
      + "makes up the bulk of the Temple. You should head north for "
      + "a closer look into the Temple.\n");
    
    try_item( ({ "south", "south exit", "valley", "outside" }),
        "The walled garden has an exit to the south that leads out "
      + "to the luscious green valley outside. Somehow, despite the "
      + "constructed nature of the garden and Temple, it feels very "
      + "much like the whole area just *belongs*.\n");
      
    try_item( ({ "work", "recent work" }),
        "Someone has been tilling the soil and working towards making "
      + "this garden a place teeming with plant life.\n");

    add_exit(ELEMENTALIST_TEMPLE + "entrance", "north");
    add_exit(ELEMENTALIST_GARDEN + "garden_11f", "west", "@@cannot_enter_restrict_resource_banned",1, "@@cannot_see_restrict_resource_banned");
    add_exit(ELEMENTALIST_GARDEN + "garden_11h", "east", "@@cannot_enter_restrict_resource_banned",1, "@@cannot_see_restrict_resource_banned");
    add_exit(ELEMENTALIST_TEMPLE + "path3", "south");
}
