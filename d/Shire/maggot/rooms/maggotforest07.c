
/* 
	*Small forest area near Maggot's field
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit BASE_FOREST;
inherit AREA_ROOM;

void create_area_room()
{
	areadesc = "dense thicket";
	area = "in";
	areaname = "the Marish";
	land = "Eriador";
	areatype = 0;
	extraline = "Through the breaks in the trees you can see " +
	"a field to the north. The undergrowth here is suprisingly " +
	"sparse, with most of the ground given to fungal growth.\n";
	
	set_add_forest();
	set_add_rtells_forest();
	
	add_std_herbs("forest");
	set_up_herbs( ({GONDOR_HERB_DIR + "astaldo", SHIRE_HERB_DIR + "bilberry", GONDOR_HERB_DIR + "suranie"}), ({"ground"}), 3); 
	add_exit(ROOM_DIR + "maggotforest03", "north");
	add_exit(ROOM_DIR + "maggotforest08", "west");
	add_exit(ROOM_DIR + "maggotforest06", "east");
}

