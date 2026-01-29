/**********************************************************************
 * - garden1.c                                                      - *
 * - Garden in the temple of Oenghus.                               - *
 * - Created by Damaris@Genesis 03/2006                             - *
 **********************************************************************/
#pragma strict_types
#include "../guild.h"
inherit GUILD_ROOM;
inherit FRUIT_PICK;
#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"
inherit GUILD_ROOM;
#include "laying.c"
void
create_khalakhor_room()
{
	config_room("flourishing garden");
	set_up_fruits(0, ({"grape", "raspberry", "blackberry"}));
	add_my_desc(lay_desc, this_object());	
	add_item(({"northeast", "southeast"}),
	"There is intricately woven grape vines in that direction.\n");
	add_item(({"southwest", "north", "south", "northwest"}),
	"The courtyard is in that direction.\n");
	add_item(({"east","west"}),
	"There is a garden in that direction.\n");

	add_exit("court4", "north");
	add_exit("court8", "south");	
	add_exit("garden", "west");
	add_exit("garden2", "east");
	add_exit("court3", "northwest");
	add_exit("court7", "southwest");
	
	add_fail("auto", "Grape vines block your way.\n");

}

void
hook_smelled(string str)
{
	if (!strlen(str) || parse_command(str, ({}), "[the] 'air'"))
	{
		write("The air is filled with sweet berries and "+
		"succulent grapes.\n");
		return;
	}
   
} 
 
void
init()
{
	::init();
	init_fruit();
	init_lay();
}
