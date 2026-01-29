
/* 
	*Maggot's turnip field in the Marish
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"

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
	"in a row of planted turnips in the midst of " +
	"the field.";
	
	set_add_field();
	set_add_rows_middle();
	set_add_rtells();
	
	add_exit(FIELD_DIR + "maggotfield16", "east");
	add_exit(FIELD_DIR + "maggotfield18", "west");
	add_exit(FIELD_DIR + "maggotfield23", "north", 0, 3, 1);
	add_exit(FIELD_DIR + "maggotfield11", "south", 0, 3, 1);
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}