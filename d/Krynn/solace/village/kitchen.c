/* Solace coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit  SOLINROOM;

create_solace_room()
{
    set_short("kitchen");
    set_long(BS(
	"You are standing in the kitchen. Here all the wonderful spiced " +
	"potatoes are being made. But now little action is in here. In the " +
	"wooden floor there is a hole. It could be a good escape route once " +
	"trapped inside the inn." +
	"",70));

    add_item("hole", "You could probably jump down it but it's a long fall.\n");

    add_exit(TDIR + "inn", "north");
}

init()
{
    ::init();
    ADA("jump");
}

jump()
{
    write("You jump down the hole.\n");
    TP->move_living("through the hole", TDIR + "solace25");
    write("You managed the jump but don't make it a habit, you could\n" +
	"hurt yourself this way.\n");
    return 1;
}






