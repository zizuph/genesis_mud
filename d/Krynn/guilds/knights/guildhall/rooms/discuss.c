/* hall1.c in guild, made by Nick */

#include <std.h>
#include "/d/Krynn/common/defs.h"
#include "../../guild.h"

inherit IN_BASE;

void load_board();


void
create_vin_room()
{
    set_short("The Krynn discussion board");
    set_long("You are standing in a strange looking room. You are not " +
         "entirely certain how you got here. There is nothing at all " +
         "in here but a discussion board for the two domains Krynn and " +
         "Ansalon.\n");

    add_exit(VROOM + "common", "common", 0);

    seteuid(getuid(TO));
    load_board();
}


void
load_board()
{
    object bb = clone_object("/d/Krynn/common/obj/disc_board");
    bb->move(TO);
}

