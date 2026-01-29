/* Tantallon by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_INSIDE;

create_tantallon_room()
{
    set_short("Small tent");
    set_long(BS(
    	"You are standing in a small and empty tent. There are two ways out " +
    	"of here, west or east." +
    	"", SL));

    add_exit(TDIR + "city2", "west", 0);
    add_exit(TDIR + "city3", "east", 0);

    reset_room();
}

reset_tantallon_room()
{
    if (!present("torch", TO))
	clone_object(OBJ + "torch")->move(TO);
}
