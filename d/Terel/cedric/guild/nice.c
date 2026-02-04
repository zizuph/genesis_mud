#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"

#define BBOARD          CEDRICDIR+"guild/board.c"

/*
 * The Minstrel Guild Headquarters: 'Nice' Room
 * There is nothing in this room but beauty and music.
 * Cedric 1/93
 */

void
init()
{
    ::init();
    add_action("do_listen", "listen");
}

void
create_room()
{
    set_short("Inside the Minstrels Guild");
    set_long(BS("Upon a cursory examination, you find the room "
    + "nearly empty.  Yet, something dances at the edge of your "
	+ "perception.  You realize this is a shrine of sorts, a shrine to "
	+ "music.  A magical light permeates the room.  You think the "
	+ "light moves in time with the music of the spheres, a music "
	+ "that you can't quite hear. Yet the music is there, stunning "
	+ "in its completeness, a truly angelic harmony. With its"
    + " wholeness, comes your own.  Praised be the ancient songs!  "
    + "If you wish you may choose to pause here and listen.\n"));

    add_exit("/d/Terel/guilds/minstrels/room/hall", "north");
    //add_exit(GUILD+"hall", "north");
    add_exit(GUILD+"courtyard", "south");
    add_exit(GUILD+"post", "east");
    add_exit(GUILD+"banquet", "west");
}

int
do_listen()
{
    TP()->catch_msg(BS("At first you have trouble distinguishing the various "
    + "harmonies.  As your mind attunes itself to the music you begin "
	+ "to pick out the various instruments.  Strings, horns and "
	+ "the voices of angels fill you with peace and understanding.  "
	+ "You feel as though they were singing for you alone, a feeling "
	+ "which you find somehow comforting.\n"));
	return 1;
}