#include "/d/Cirath/common/defs.h"
inherit "/std/room";
#include "wbt.h"

void
create_room()
{
	set_short("Entrance to the training hall");
   set_long("You have entered the large training hall used by "
	+"the adepts of the school to hone their skills.  The "
	+"noise level is amazing here; war-cries, the clattering "
	+"of weapon on weapon, regardless of what it is, it is loud. "
	+"Sturdy granite walls with no decoration surround the "
	+"room with scratches revealing what the room is used for.\n");
   add_item(({"wall","walls"}),"They look to be made of thick "
	+"granite and are only adorned with the scratches that "
	+"result from the untrained adepts taking wild swings "
	+"with their weapons.\n");
	
	INSIDE;

	add_exit(WWORK+"train2.c", "north", 0, 0);
	add_exit(WWORK+"hall2.c", "south", 0, 0);
	add_exit(WWORK+"train3.c", "west", 0, 0);
	add_exit(WWORK+"train4.c", "east", 0, 0);
}
