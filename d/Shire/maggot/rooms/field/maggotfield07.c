
/* 
	*Maggot's turnip field in the Marish
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"

#define NPC_BLOCK "_cant_go_there"

inherit BASE_COMMON;
inherit AREA_ROOM;

void create_area_room()
{
	areadesc = "large turnip field";
	area = "in";
	areaname = "the Marish";
	land = "Eriador";
	areatype = 0;
	extraline = "There are probably more turnips here than " +
	"in the whole of the Shire. Best not pick them, farmers " +
	"can be quite protective of their crops! You are standing " +
	"in a row of planted turnips on the east edge of " +
	"the field. There is a hedge-lined lane just east of here.";
	
	add_item(({"lane", "road", "path", "ruts"}), "It is rutted, " +
	"with grass is growing between the ruts and on either " +
	"side of the lane.\n");
	
	set_add_field();
	set_add_rows_middle();
	set_add_rtells();
		
	add_exit(ROOM_DIR + "maggotlane05", "east", "@@npc_block@@");
	add_exit(FIELD_DIR + "maggotfield08", "west");
	add_exit(FIELD_DIR + "maggotfield13", "north", 0, 3,1);
	add_exit(FIELD_DIR + "maggotfield01", "south", 0, 3,1);
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}

int npc_block()
{
        if(this_object()->query_prop(NPC_BLOCK))
	{
		write("Stay in your field!\n");
	        return 1;
	}
	
	return 0;
}
