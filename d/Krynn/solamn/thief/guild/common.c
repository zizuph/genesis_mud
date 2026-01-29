/* common board, 02/24/94, by Aridor */
/* Aug 27, 2018: Added no-scry protection in guild (Gorboth) */

#include "guild.h"

inherit ROOM_BASE

#include <stdproperties.h>

void load_board();


void
create_thief_room() 
{
  set_short("The common board");
  set_long("You are standing in a strange looking room. You are not " +
	   "entirely certain if you really got here up these stairs. " +
	   "There is nothing at all in here but a common board, common " +
	   "for everyone in Genesis.\n");
  
    add_exit(GUILDR + "start", "down");

    load_board();

    add_prop(ROOM_M_NO_SCRY, "Haze, and nothing more, is all that"
      + " appears.");

    INSIDE;
    LIGHT;

}

void
load_board()
{
    object bb;

    seteuid(getuid(TO));
    bb = clone_object("/d/Genesis/obj/board");
    bb->move(this_object());
}
