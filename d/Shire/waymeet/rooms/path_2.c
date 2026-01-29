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

    extraline = "This path leads to the farm west of the " +
        "village of Waymeet.";

    add_item(({"surroundings","expanse","plain","shire"}),
      "The Shire is an expanse of plains, with the occasional village "
      +"or cultivated field, where the hobbits till the rich soil of the "
      +"Shire.\n");
    add_item(({"path"}),
        "This is a simple dirt path leading to the fields.\n");
    add_item(({"field", "fields"}),
        "These farm fields provide food for the village of Waymeet.\n");

    reset_shire_room();

    add_exit(WAYM_ROOM_DIR + "path_1","west");
	add_exit(WAYM_STREET_DIR + "street_1", "east");
}

void reset_shire_room()
{
    
}