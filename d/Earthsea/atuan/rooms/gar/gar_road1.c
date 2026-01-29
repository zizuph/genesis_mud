inherit "/d/Earthsea/std/room";


#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Earthsea/atuan/defs.h"

object fisherman;

void
create_earthsea_room()
{
	set_short("On a dirt track through the village of Gar.");
	set_long(BS("You are walking on a dirt track which runs slightly uphill to"+
		" the east. Two small wooden houses lie in that direction. The village square "+
		" lies southwest. Outside one of the"+
		" houses, lies a well tended flowerbed which is surrounded by a neat"+
		" wooden fence.  The houses themselves sit just off the track, and seem"+
		" to be in good repair.",70));

	add_item(({"track","dirt track","road"}),"The track runs from the town square"
	+ " up to two wooden houses.\n");
	add_item(({"town","village","gar"}),"Gar is little more than a collection"
	+ " of small houses spread across the shore here.\n  It is a place"
	+ " where only the simple things in life matter.\n");
	add_item(({"house","hut","houses"}),"The houses are well made from strong wood"
	+ " and look like they could stand up to the fierce weather sometimes"
	+ " encountered here. Smoke is rising slowly from a few of the chimneys.\n");
	add_item(({"bed","flowerbed"}),"The flowerbed contains a few hardy evergreens"+
		" which seem to be thriving on the salt air.\n");
	add_item(({"fence","neat fence"}),"Somebody has made a great effort to make"+
		" the house look more appealing by surrounding it with a small fence."+
		" There is an opening leading to the front door.\n");
	add_item(({"door","front door"}),"Why don't you get a little closer?\n");


add_exit(GAR + "gar_road2","east",0);
add_exit(GAR + "gar_square","southwest",0);


}




