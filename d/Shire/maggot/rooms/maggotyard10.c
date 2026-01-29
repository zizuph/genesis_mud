
/* 
	*A yard, just outside farmer Maggot's house
	*Altrus, 
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit BASE_YARD;
inherit AREA_ROOM;

public void
create_area_room()
{
	areadesc = "orderly yard";
	area = "of a quaint house in";
	areaname = "the Marish";
	land = "Eriador";
	areatype = 0;
	extraline = "There is a small flower garden bordering the house, " +
	"filling the air with floral and herbal fragances. Small trees border " +
	"the fringes of the yard. Northeast is an old barn. ";
	
	set_add_yard();
	set_add_rtells_yard();
	
	add_std_herbs("meadow");
	
	add_exit(ROOM_DIR + "maggotyard04", "west");
	add_exit(ROOM_DIR + "maggotyard11", "east");
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}

