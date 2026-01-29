/* hall1.c in guild, made by Nick */

#include "/d/Krynn/common/defs.h"
#include "../knight/guild.h"
#include "../local.h"

inherit IN_BASE;

void load_board();

void
create_vin_room()
{
    set_short("The common board");
    set_long("You are standing in a strange looking room. You are not " +
         "entirely certain how you got here. There is nothing at all " +
         "in here but a common board, common for everyone in Genesis.\n");

    add_exit(VROOM + "startroom", "down", 0);
    add_exit(VROOM + "discuss", "discuss", 0);

    seteuid(getuid(TO));
    load_board();
}


void
load_board()
{
    object bb;

    seteuid(getuid(TO));
    bb = clone_object("/d/Genesis/obj/board");
    bb->move(this_object());
}
