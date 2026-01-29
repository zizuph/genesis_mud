/* Outdoors in Waymeet
 * Raymundo, Jan 2020
 */
 
#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit WAYM_LIB_DIR + "base_waymeet.c";



void reset_shire_room();

void
create_waymeet_room()
{
	extraline = ("You are midway on the western side of residential "
		+ "part of Waymeet. There is a smial to your west. You can "
		+ "see more smials to the north and east, but they're too "
		+ "far away to get a detailed view. You see some paw prints "
		+ "in the grass.\n");
		
	add_item("grass", "Grass lines the street. It's green and not too "
		+ "very tall, perhaps ankle high on a hobbit. You notice that "
		+ "some of the grass has been trampled down in the shap of a "
		+ "paw print.\n");
		
	add_item( ({"print", "paw", "paw print", "paw prints", "prints"}),
		"The paw prints look like they came from a very, very big dog.\n");
	
	add_smial("h_5_1");
	add_street(0);
	add_dogs();
	
	add_exit(WAYM_STREET_DIR + "street_3", "north", gravel_sound, 0, 0);
	add_exit(WAYM_STREET_DIR + "street_1", "south", gravel_sound, 0, 0);
	add_exit(WAYM_STREET_DIR + "street_5", "east", gravel_sound, 0, 0);
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