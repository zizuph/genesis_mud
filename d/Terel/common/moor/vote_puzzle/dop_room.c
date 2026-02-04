/*
    Modified: Jan 2021, by Lucius
        - Some code reformatting and fixup long() for exit counting.
*/
inherit "/std/room";
     
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"
#include "../local.h"

public string
num_exits(void)
{
    if (sizeof(room_exits))
        return "one exit";
    else
        return "no exits";
}

public void
create_room()
{
    set_short("cell");
    set_long("You are in an empty cell with @@num_exits@@!\n");

    add_item(({"chain", "chains"}), 
	"The chains are thick and they look rather heavy and very strong.\n");

    add_prop(ROOM_I_INSIDE, 0);
    reset_room();
}

public void
make_an_exit()
{
    add_exit("../hills/path03", "out", 0);
    set_alarm(20.0, -1.0, "reset_room");
}
