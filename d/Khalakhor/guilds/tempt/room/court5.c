/**********************************************************************
 * - court5.c                                                       - *
 * - Courtyard in the temple of Oenghus.                            - *
 * - Created by Damaris@Genesis 03/2006                             - *
 **********************************************************************/
#pragma strict_types
#include "../guild.h"
inherit GUILD_ROOM;
inherit FRUIT_PICK;
#include <macros.h>
#include <stdproperties.h>
#include "laying.c"
void
create_khalakhor_room()
{
	config_room("thriving courtyard");
	set_up_fruits(0, ({"grape", "raspberry", "blackberry"}));
	add_my_desc(lay_desc, this_object());	
	add_item(({"courtyard"}), query_long);
	
	add_item(({"north", "west", "south", "southwest", "northwest", "southeast"}),
	"There is intricately woven grape vines in that direction.\n");
	add_item(({"east"}),
	"The courtyard continues in that direction.\n");
	add_item(({"northeast"}),
	"The entrance is in that direction.\n");
	
	add_exit("court6", "east");
	add_exit("entrance", "northeast");
	
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

public void
init()
{
	::init();
	init_fruit();
	init_lay();
}
