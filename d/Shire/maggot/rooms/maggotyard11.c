
/* 
	*A yard, just outside farmer Maggot's house
	*Altrus, 
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit BASE_YARD;
inherit AREA_ROOM;

void create_area_room()
{
	areadesc = "path";
	area = "in front of a barn in";
	areaname = "the Marish";
	land = "Eriador";
	areatype = 0;
	extraline = "You are standing on a small dirt path. " +
	"A number of paces to the west a short house " +
	"stands in the middle of a well-kept yard. Small trees border " +
	"the fringes of the yard.";
	
	add_item(({"path", "dirt path"}), "It is hard packed from " +
	"heavy foot and hoof traffic.\n");
	
	set_add_yard();
	set_add_rtells_yard();
	
	add_std_herbs("meadow");
	
	add_exit(ROOM_DIR + "maggotbarn01", "north");
	add_exit(ROOM_DIR + "maggotyard10", "west");
		
	reset_shire_room();
}

void reset_shire_room()
{
	
}

