/*
 * MR1.c 
 * Ruins of Kamesh
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("An overgrown path among ruined buildings");
    set_long("  You are standing on a small path which at one point in "+
	     "its history may have been a large road. There is so much "+
	     "overgrowth and clusters of weeds on the road now that it "+
	     "barely resembles a path. Were it not for the neat rows of "+
	     "ruined buildings on either side, you might not notice that "+
	     "it was a path. The buildings would have been enormous in "+
	     "their prime. All of them are stone constructions that are "+
	     "missing roofs and some are missing entire portions of walls. "+
	     "One of the buildings on the east side of the road is tall "+
	     "and narrow, several stories of it seem to be intact. The path "+
	     "continues further into the ruins to the west along what could "+
	     "have been a main street, and branches north and south of "+
	     "here.\n"+
	     "There is a shattered doorway leading east.\n\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"road", "path", "down", "ground", "overgrowth", "weeds",
		"bushes"}),
	     "The path beneath you is covered in weeds and bushes. It "+
	     "at one point could have been a large, busy road through "+
	     "this monastery, possibly for wagon and carriage traffic. Now, "+
	     "it is nothing more than a narrow patch of worn dirt and "+
	     "pebbles scattered amidst bushes and weeds.\n");

    add_item( ({"doorway", "shattered doorway", "east"}),
	     "The shattered doorway is the entrance into the tall, narrow "+
	     "building to the east. Several of this building's stories "+
	     "seem to be intact, though its roof is long since gone.\n");

    add_item( ({"building", "east building", "tall building", 
		"narrow building", "bell tower", "belltower", "tower"}),
	     "The building on the east side of the road looks vaguely "+
	     "like another kind of building you have seen before. After "+
	     "looking at its construction and mentally filling in the "+
	     "holes in the sides and roof of the building, it looks like "+
	     "it could be some kind of a bell tower. There are actually "+
	     "a few pieces of wood hanging from the huge circular hole "+
	     "(or perhaps window?) at the top where the bell could be.\n");

    add_item( ({"wood", "circular hole", "pieces of wood", "window"}),
	     "You can't quite make out any details of the circular hole "+
	     "in the side of the building. It could have been some kind "+
	     "of window. There are several pieces of wood dangling from "+
	     "some unseen tether in the stone, but you can't make out the "+
	     "details from here.\n");

    add_item( ({"buildings", "ruins", "ruined buildings", "rows",
		"neat rows"}),
	     "The ruined buildings are everywhere. It is hard to "+
	     "picture a mental image of what this eerie place may have "+
	     "looked like centuries ago in its prime, but you can gather "+
	     "enough from the surroundings that it was astounding. The "+
	     "construction is on a much grander scale than most of "+
	     "the temples or monasteries of current design.\n");

    add_exit(MONKRUIN_DIR + "coast9", "north");
    add_exit(MONKRUIN_DIR + "mr2", "south");
    add_exit(MONKRUIN_DIR + "bt1", "east");
    add_exit(MONKRUIN_DIR + "mr4", "west");
}

    
