/* Outdoors in Waymeet
 * Raymundo, Jan 2020
 */
 
#pragma save_binary
#pragma strict_types

#include "defs.h"
#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>

inherit WAYM_LIB_DIR + "base_waymeet.c";


int is_toy = 1;

void reset_shire_room();

void
create_waymeet_room()
{
	extraline = ("Here the street curves gently to the east. To the "
		+ "north is a very large smial, or at least it seems to be "
		+ "very large from the outside. You see toys scattered about "
		+ "in the grass, looking almost like an entire toybox was "
		+ "upended here.\n");
		
	add_item("grass", "Grass lines the street. It's green and not too "
		+ "very tall, perhaps ankle high on a hobbit. You notice that "
		+ "some of the grass has been trampled down in the shap of a "
		+ "paw print. Toys are scattered every which way.\n");
		
	add_item( ({"print", "paw", "paw print", "paw prints", "prints"}),
		"The paw prints look like they came from a very, very big dog.\n");
	add_item( ({"toy", "toys", "horse", "wooden horse", "doll", "ball"}),
		"In the grass you see many different types of toys, including a "
		+ "wooden horse, a doll, and even a ball. It looks like the kids "
		+ "had a lot of fun out here!\n");
		
		add_prop(OBJ_S_SEARCH_FUN, "search_toys");
		
	add_smial("h_1_1");
	add_street(0);
	add_dogs();
	
	
	add_exit(WAYM_STREET_DIR + "street_2", "south", gravel_sound, 0, 0);
	add_exit(WAYM_STREET_DIR + "street_4", "east", gravel_sound, 0, 0);
}
void
reset_shire_room()
{
	is_toy = 1;
}

void
init()
{
	::init();
	

}

string
search_toys(object me, string arg)
{
	if(arg != "toys")
		return "";
	if(is_toy == 1)
	{
		is_toy = 0;
		say(QCTNAME(TP) + " finds a wooden horse in the toys!\n");
		object horse;
		horse = clone_object(WAYM_OBJ_DIR + "wooden_horse");
		horse->move(TP);
		return("You find a wooden horse in the toys!\n");
	}
	else
		return "";
}