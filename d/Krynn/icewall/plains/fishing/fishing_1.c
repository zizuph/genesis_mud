/*Created by Macker 07/14/94*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
	set_short("Path to Fishing Area");
        set_long(
		"You are on a path leading from the village. The village is southwest, and " +
		"to the northeast you can see what looks like a frozen pond.\n");

	add_item( ({"ground", "snow", "ice", "path", "road"}),
		"It is white and cold. What did you expect?\n");

	add_item( ({"pond", "frozen pond", "frozen over pond", "fishing area"}),
		"The frozen pond to your northeast must be where the ice folk go to fish.\n");

	add_item("village", "The village is to your soutwest. Why don't you go check it out?\n");

add_exit(FISHING + "fishing_2.c", "northeast");

add_exit(ICE_PLAINS + "village/" + "village_4.c", "southwest");
        }
