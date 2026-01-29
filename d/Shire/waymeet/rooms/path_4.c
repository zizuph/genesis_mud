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
        "This is a simple dirt path leading east to the fields and south to the farm.\n");
    add_item(({"field", "fields"}),
        "These farm fields provide food for the village of Waymeet.\n");
	add_item( ({"farm", "farms"}), "South of here is a small farmhouse. Smoke rises "
		+ "from the house's chimney, so there must be someone home.\n");
	add_item( ({"house", "farmhouse"}), "Strangely, for the Shire, there is "
		+ "a farmhouse built on top of a little hill just to the south. There "
		+ "is smoke coming from its chimney.\n");
	add_item( ({"smoke", "chimney"}), "The smoke drifts from the chimney "
		+ "lazily up toward the "
		+ "clouds, making the farmhouse seem warm and inviting.\n");

    reset_shire_room();

	add_exit(WAYM_FIELD_DIR + "e_field01","east");
	add_exit(WAYM_ROOM_DIR + "path_3", "west");
	add_exit(WAYM_ROOM_DIR + "path_5", "south", 0,0,1);
}

void reset_shire_room()
{
    
}