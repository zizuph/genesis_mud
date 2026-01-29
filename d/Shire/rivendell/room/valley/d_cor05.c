/*
 * Downstairs corridor
 * By Finwe, February 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;
 
void
create_house_room()
{
    set_short("A downstairs corridor");
    set_long("You stand in a corridor in the center of the " +
        "house. The corridor is large, serving as a meeting " +
        "place for residents of the valley. The walls are " +
        "decorated with a large mural. A large " +
        "staircase leads upstairs.\n");
 
    add_item(({"pillars", "square pillars", "square wooden pillars"}),
        "The pillars are carved from thick trees. They are squared " +
        "and are set into the walls. The pillars are expertly " +
        "decorated with carved leaves.\n");
    add_item("staircase",
        "The staircase is made of stained oak. It is large " +
        "and leads upstairs.\n");
    add_item(({"mural", "large mural"}),
        "The mural depicts the First-born. Some look as if they " +
        "are awakening while others stand near by. The First-" +
        "born are on the shores of a beautiful bay, bathed in " +
        "starlight.\n");
    add_item(({"bay", "beautiful bay", "cuivenen"}),
        "The bay is a deep azure color, situated on the east " +
        "side of a large body of water and situated near a " +
        "large mountain range.\n");
    add_item(({"mountains", "mountain range", "large mountain range",
            "orocarni mountains", "orocarni"}),
        "They are large and reddish in color and are to the " +
        "east of the bay.\n");
    add_item(({"first-born", "first born", "elves"}),
        "They are elves; fair to behold, ageless, and look as " +
        "if they just awoke from a great sleep. They are " +
        "painted with such realism that they look lifelike.\n"); 
    add_item(({"staircase railing", "railing"}),
        "The railing is crafted of stained oak. Each rail is " +
        "a carved tree supporting the banister.\n");
    add_item("banister",
        "The banister is made of stained oak and is " +
        "polished smooth. It is supported by an intricately " +
        "carved railing.\n");
    set_extra_wall("The walls are decorated with a large mural.\n"); 
 
    add_exit(VALLEY_DIR + "d_cor08", "south");
    add_exit(VALLEY_DIR + "d_cor06", "east");
    add_exit(VALLEY_DIR + "u_cor05", "up");
}
 
