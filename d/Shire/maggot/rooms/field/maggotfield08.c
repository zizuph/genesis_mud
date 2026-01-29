
/* 
	*Maggot's turnip field in the Marish
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

inherit BASE_COMMON;
inherit AREA_ROOM;

void make_npcs();

object maghob;
object dog1, dog2, dog3;

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
	"in a row of planted turnips in the midst of " +
	"the field.";
	
	set_add_field();
	set_add_rows_middle();
	set_add_rtells();
	
	add_exit(FIELD_DIR + "maggotfield07", "east");
	add_exit(FIELD_DIR + "maggotfield09", "west");
	add_exit(FIELD_DIR + "maggotfield14", "north", 0, 3, 1);
	add_exit(FIELD_DIR + "maggotfield02", "south", 0, 3, 1);
	
	reset_shire_room();
}

void reset_shire_room()
{
	make_npcs();
}

void make_npcs()
{
	if(!maghob)
	{
		maghob = clone_object(NPC_DIR + "farmer_maggot");
		maghob->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(maghob->query_nonmet_name()))+ " walks into the area.\n");
		maghob->set_restrain_path("/d/Shire/maggot/rooms/field");
		maghob->set_random_move(4);
	}
	
	if(!dog1)
	{
		dog1 = clone_object(NPC_DIR + "dog_grip");
		dog1->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(dog1->query_nonmet_name()))+ " warily stalks into view.\n");
		maghob->team_join(dog1);
	}
	
	if(!dog2)
	{
		dog2 = clone_object(NPC_DIR + "dog_fang");
		dog2->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(dog2->query_nonmet_name()))+ " warily stalks into view.\n");
		maghob->team_join(dog2);
	}
	
	if(!dog3)
	{
		dog3 = clone_object(NPC_DIR + "dog_wolf");
		dog3->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(dog3->query_nonmet_name()))+ " warily stalks into view.\n");
		maghob->team_join(dog3);
	}
}
