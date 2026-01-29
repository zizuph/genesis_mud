/* 
	*Fishing area room
	*Altrus, June 2005
*/
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/fishing/defs.h"

inherit "/std/room";
inherit AREA_ROOM;

void make_npcs();

object hobbit;

void create_area_room()
{
	areadesc = "small pond";
	area = "in";
	areaname = "the Marish";
	land = "Eriador";
	areatype = 0;
	extraline = "Tall cattails grow around an in the edge of the pond and various other water plants cling to the marshy ground. Insects are in abundance here, buzzing around in all directions. It feels calm here, a clamness that borders on the lazy, perfect for fishing.";
	
	add_std_herbs("marsh");
	
	add_exit(ROOM_DIR + "lake01", "east");

	reset_shire_room();
}

void reset_shire_room()
{
	make_npcs();
}

void make_npcs()
{
	if (!hobbit)
		hobbit = clone_object(NPC_DIR + "lucky_hobbit");
	if (!present(hobbit,this_object()))
		hobbit->move(this_object());
}
