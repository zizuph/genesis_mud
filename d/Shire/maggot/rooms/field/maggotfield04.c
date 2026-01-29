
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
	"in a row of planted turnips on the south edge of " +
	"the field. A grove of trees are growing near the edge of " +
	"the field south of here.";
	
	set_add_field();
	set_add_trees();
	set_add_rows_south();
	set_add_rtells();
	
	add_exit(FIELD_DIR + "maggotfield03", "east");
	add_exit(FIELD_DIR + "maggotfield05", "west");
	add_exit(FIELD_DIR + "maggotfield10", "north", 0, 3, 1);
	add_exit(FIELD_DIR + "null_room", "south", "@@no_exit@@", 0, 1);
	reset_shire_room();
}

void reset_shire_room()
{
	
}

int no_exit()
{
        write("The forest is much too dense to enter here.\n");
        return 1;
}
