/* Outdoors in Waymeet
 * Raymundo, Jan 2020
 */
 
#pragma save_binary
#pragma strict_types

#include "defs.h"
#include "/d/Shire/eastroad/western/local.h"
inherit WAYM_LIB_DIR + "base_waymeet.c";



void reset_shire_room();

void
create_waymeet_room()
{
	extraline = ("North of here are some gentle rolling hills, "
		+ "indicative of hobbit smials. Further in the distance, "
		+ "to the northwest and northeast you see fields, where "
		+ "the hobbits grow vegetables. To the south is the "
		+ "Great East Road, which would take you all the way "
		+ "to Bree! What an adventure (by Shire standards)!\n");
	
	add_item( ({"smial", "smials"}), "The smials are a little ways "
		+ "north of here. They look peaceful and clean, at least "
		+ "at a distance.\n");
	add_item( ({"vegetables", "vegetable"}), "You'd have to go "
		+ "to the fields to see what type of vegetable the hobbits "
		+ "grow.\n");
	add_item( ({"east road", "great east road"}), 
		"A mighty highway, the Great East Road connects the Shire to the "
		+ "rest of Middle Earth!\n");
	add_item( "middle earth", "Middle Earth is only... well... "
		+ "everything! Look around you! All of it is Middle Earth!\n");
	add_item( "bree", "Bree is a far distance east. For a hobbit, it "
		+ "would be quite a large adventure.\n");
	add_street(1);
	
	add_exit(WAYM_STREET_DIR + "street_1", "northwest", gravel_sound, 0, 0);
	add_exit(WAYM_STREET_DIR + "street_6", "north", gravel_sound, 0, 0);
	add_exit(EAST_R_DIR + "er12", "south", gravel_sound, 0, 0);
	
}
void
reset_shire_room()
{
	
}

void
init()
{
	::init();
	

}