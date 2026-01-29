inherit "/d/Earthsea/std/room";


#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Earthsea/atuan/defs.h"

object fisherman;

void
create_earthsea_room()
{
	set_short("Gar Town Square");
	set_long(BS("You are standing in the middle of Gar Village. A well worn"+
		" sandstone road runs through the village east-west, and a dirt track"+
		" leads northeast up along the cliff toward two houses. The dock lies"+
		" west and you can see the sunlight glinting off the tops of the waves"+
		" as they break on the beach to your south.  Further along the road as it"+
		" leaves the village, you notice a large orchard and beyond that the rolling"+
		" desolate hills of Atuan.",70));
	

	add_item(({"road","sandstone","sandstone road","smooth sandstone"}),"The road"
	+ " has been made up of many thousands of sandstone rocks, all worn"
	+ " smooth by years of use.\n");
	add_item(({"track","dirt track"}),"The track runs uphill along the edge of the cliff"
	+ " toward two houses at the top which overlook the sea.\n");
	add_item(({"town","village","gar"}),"Gar is little more than a collection"
	+ " of small houses spread across the shore here.\n  It is a place"
	+ " where only the simple things in life matter.\n");
	add_item(({"dock"}),"The dock leads out into the sea a short distance.  There"
	+ " are no boats there at the moment although you can see white sails out to sea.\n");
	add_item(({"house","hut","houses"}),"The houses are well made from strong wood"
	+ " and look like they could stand up to the fierce weather sometimes"
	+ " encountered here. Smoke is rising slowly from a few of the chimneys.\n");

add_exit(GAR + "gar_pier1","west",0);
add_exit(GAR + "gar_road3","east",0);
add_exit(GAR + "gar_road1","northeast",0);
add_exit(GAR + "gar_beach1","south",0);
reset_room();

}


reset_room()
{
if (!fisherman)
        {
fisherman = clone_object(LIVING + "fisherman1");
fisherman->move_living("xxx", TO);
        }
}


