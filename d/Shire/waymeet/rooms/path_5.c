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

    extraline = "You're standing on a path just north of a farmhouse, "
		+ "and south of the path between Waymeet and the fields.";

    add_item(({"surroundings","expanse","plain","shire"}),
      "The Shire is an expanse of plains, with the occasional village "
      +"or cultivated field, where the hobbits till the rich soil of the "
      +"Shire.\n");
    add_item(({"path"}),
        "This is a simple dirt path leading north toward Waymeet and south "
		+ "to the farmhouse.\n");
	add_item( ({"house", "farmhouse", "farm"}), "Strangely, for the Shire, there is "
		+ "a farmhouse built on top of a little hill right in front of you. Smoke "
		+ "rises from the chimney. The windows are open, letting in fresh air. And "
		+ "the door even looks unlocked.\n");
	add_item( ({"smoke", "chimney"}), "The smoke drifts from the chimney "
		+ "lazily up toward the "
		+ "clouds, making the farmhouse seem warm and inviting.\n");
	add_cmd_item("door", "knock", "You knock on the door, but then feel silly. "
		+ "It's unlocked. Just go in!\n");
	add_item("door", "The door is painted yellow. It looks very hobbitish, "
		+ "somehow, even though this farmer built his house above ground. It's "
		+ "unlocked, so you can probalby just go in.\n");
	add_item( ({"window", "windows"}), "The windows are open, letting in fresh "
		+ "air.\n");
	add_item( ({"air", "fresh air"}), "You're joking, right? You can't see air. "
		+ "But you can smell it.\n");
	add_cmd_item( ({"air", "fresh air"}), "smell", "You breathe in through your "
		+ "nose. The air smells fresh.\n");

    reset_shire_room();

	add_exit(WAYM_ROOM_DIR + "path_4", "north", 0,0,1);
	add_exit(WAYM_ROOM_DIR + "farmhouse", "in");
}

void reset_shire_room()
{
    
}