/**********************************************************************
 * - court3.c                                                       - *
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
	config_room("flourishing courtyard");
	set_up_fruits(0, ({"grape", "raspberry", "blackberry"}));
	add_my_desc(lay_desc, this_object());	
	add_item(({"courtyard"}), query_long);
	
	add_item(({"southwest", "northeast", "north", "northwest"}),
	"There is intricately woven grape vines in that direction.\n");
	add_item(({"west","east"}),
	"The courtyard continues in that direction.\n");
	add_item(({"south"}),
	"The garden is in that direction.\n");
	add_item(({"southeast"}),
	"There is a fountain in that direction.\n");
	
	add_npc(NPC + "fia", 1);
	
	add_exit("garden", "south");
	add_exit("court4", "east");
	add_exit("court2", "west");
	add_exit("garden1", "southeast");
	
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