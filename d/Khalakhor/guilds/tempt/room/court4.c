/**********************************************************************
 * - court4.c                                                       - *
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
#define BOARD_DIR "/d/Khalakhor/guilds/tempt/log/board_data"
void
create_khalakhor_room()
{
	object bb;
	config_room("lush courtyard");
	set_up_fruits(0, ({"grape", "raspberry", "blackberry"}));
	add_my_desc(lay_desc, this_object());	
	add_item(({"courtyard"}), query_long);
	add_item(({"southwest", "northeast", "north", "northwest", "east"}),
	"There is intricately woven grape vines in that direction.\n");
	add_item(({"west"}),
	"The courtyard continues in that direction.\n");
	add_item(({"south"}),
	"There is a fountain in that direction.\n");
	add_item(({"southeast" }),
	"There is a garden in that direction.\n");

	add_exit("court3", "west");
	add_exit("garden1", "south");
	add_exit("garden2", "southeast");
	
	add_fail("auto", "Grape vines block your way.\n");
	
	setuid();
	seteuid(getuid());
	bb = clone_object("/std/board");
	bb->set_board_name(BOARD_DIR);
	bb->set_num_notes(30);
	bb->set_silent(0);
	bb->set_show_lvl(0);
	bb->move(this_object(), 1);	
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