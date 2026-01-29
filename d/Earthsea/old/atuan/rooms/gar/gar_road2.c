inherit "/d/Earthsea/std/room";


#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Earthsea/atuan/defs.h"

object fisherman;

void
create_earthsea_room()
{
	set_short("On a dirt track through the village of Gar.");
	set_long(BS("You are at the end of a dirt track. The house with the fence"+
		" lies southeast. You are at a higher point now, and can look down at"+
		" the tranquil village. A few villagers can be seen going about their"+
		" business, and you can see the light glinting off the tops of the waves"+
		" as they crash onto the beach. The small house to the north backs onto"+
		" a cliff providing a magnificent view of the misty mountains of Karego-At"+
		" a short distance across the ocean.",70));
		 

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
	add_item(({"door","front door"}),"The door is wide open, and has a horseshoe"+
		" pinned above it.\n");
	add_item(({"shoe","horseshoe"}),"It is a worn iron horseshoe, the traditional"+
		" symbol for luck.\n");
	add_item(({"mountains","misty mountains"}),"The mountains on the island of"+
		" Karego-At rise high about the clouds.  It is rumoured that stange creatures"+
		" of darkness live at the tops.\n");
	add_item(({"cliff","view"}),"@@breath_away");
		
	
add_exit(GAR + "gar_road1","west",0);
add_exit(GAR + "gar_house2","southeast",0);
add_exit(GAR + "gar_house1","north",0);

}


breath_away()
{
	TP->catch_msg("The view is magnificent, and it takes your breath away.\n");
	tell_room(ENV(TP), QCTNAME(TP) + " has his breath taken away by the view.\n",
	  ({TP}));

	return "";
}