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




void reset_shire_room();

void
create_waymeet_room()
{
	extraline = ("The smial east of you looks run down and shabby. Overall, "
		+ "it is in a state of disrepair--not the disrepair you see when "
		+ "people don't care; just the kind of disrepair that occurs when "
		+ "there isn't enough money to fix things, and hasn't been for quite "
		+ "some time. Nevertheless, they have tried to make the place "
		+ "look nice, going so far as to plant some flowers next to the door. "
		+ "Past the smial to the east is a small path that leads to the "
		+ "fields. The fields seem to be planted with vegetables.\n");
	
	add_item( ({"flower", "flowers", "daisy", "daisies"}), "These are very nice "
		+ "daisies. They are planted in orderly rows and give a nice splash of "
		+ "color to the place.\n");
	add_item( "color", "The daisies come in many colors, pink, white, yellow... "
		+ "They're very nice.\n");
	add_cmd_item( ({"daisy", "daisies", "flower", "flowers"}), "pick", 
		"No! That would be too rude!\n");
	add_item("path", "The path leads east toward the fields.\n");
	add_street(1);
	add_smial("h_2_1");
	
	
	add_exit(WAYM_ROOM_DIR + "path_3", "east", 0,0,1);
	add_exit(WAYM_STREET_DIR + "street_1", "west", gravel_sound, 0, 0);
	add_exit(WAYM_STREET_DIR + "street_5", "north", gravel_sound, 0, 0);
	add_exit(WAYM_STREET_DIR + "street_7", "south", gravel_sound, 0,0);
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
