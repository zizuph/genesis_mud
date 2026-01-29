/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_INSIDE;

create_tantallon_room()
{
    object door;

    set_short("Down a hole");
    set_long(BS(
    	"You are down a hole. You feel something very evil present above you. " +
	"There is a small hole in the ceiling but you aren't sure what awaits " +
	"there. Perhaps it's better to go back north, out from here." +
	"", SL));

    add_exit(TDIR + "tent10", "up", 0);
    add_exit(TDIR + "hole20", "north", 0);

    DARK;
}
