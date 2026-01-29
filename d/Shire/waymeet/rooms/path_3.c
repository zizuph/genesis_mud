/*
    /d/Shire/waymeet/rooms/path_2.c

    Path in Waymeet
    Perrigrine, February 2019
*/

#pragma save_binary
#pragma strict_types

#include "defs.h"
#include "/d/Shire/eastroad/western/local.h"

inherit EAST_ROAD;

void reset_shire_room();

void create_er_room()
{

    area = "near"; /* Distance from areaname */
    areaname = "Waymeet";
    land = "the Shire";
    areatype = 11;
    areadesc = "field";

    extraline = "This path leads to the farm east of the " +
        "village of Waymeet.";

    add_item(({"surroundings","expanse","plain","shire"}),
      "The Shire is an expanse of plains, with the occasional village "
      +"or cultivated field, where the hobbits till the rich soil of the "
      +"Shire.\n");
    add_item(({"path"}),
        "This is a simple dirt path leading to the fields.\n");
    add_item(({"field", "fields"}),
        "These farm fields provide food for the village of Waymeet.\n");
    add_item( ({"farm", "farmhouse", "farm house", "house"}), "You see "
        + "a thin trail of smoke heading up toward the clouds. It "
        + "originates from somewhere southeast of you. There's probably "
        + "a farmhouse there, and that's probably the smoke from their "
        + "chimney!\n");
    add_item("smoke", "The smoke trails its way up toward the clouds like "
        + "a cat's tail, flicking this way and that, always in motion.\n");
    add_item( ({"southeast", "southeast of here"}), "You see smoke rising "
        + "above the trees to the southeast.\n");
    add_item( ({"tree", "trees"}), "Trees grow thick along the southern "
        + "side of the path, providing protection from the wind, as well "
        + "as privacy.\n");
    add_item( ({"private", "privacy"}), "Well, it wouldn't be very private "
        + "if you could examine it, would it?\n");
    reset_shire_room();
    
    set_no_exit_msg("southeast", "The trees are too thick to the southeast. "
        + "You can't go that direction.\n");
    add_exit(WAYM_ROOM_DIR + "path_4","east");
	add_exit(WAYM_STREET_DIR + "street_6", "west");
}

void reset_shire_room()
{
    
}