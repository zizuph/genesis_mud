/*
 * Filename: 	/d/Genesis/wiz/guildhall.c
 * Description: This room holds the guild board, for discussion of
 *				guild related things.
 *
 */
#pragma save_binary

#include "default.h"
#include </secure/std.h>

void
create_room()
{
	object board;

	set_short("Wizard Guild Discussion room");
	set_long(
           "Wizard guild discussion room.\n" +
           "This magnificent guildhall is where wizards come\n"
         + "together to discuss new developments in guilds.\n"
	);
	add_exit(THIS_DIR + "green", "east");
/*        add_exit(THIS_DIR+"guildmaster", "west"); */

	board = load_board("guild");
	board->set_num_notes(99);

	add_default_exits();
}
