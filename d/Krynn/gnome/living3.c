#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

create_room()
{
    set_short("Future gnomish living quarters");

    set_long(BS("This area is being widened to house the gnomish families " +
      	"coming out of Mount Nevermind to work here.  For now it is dusty " +
      	"and unfinished.", 70));

    add_item(({"tunnel", "cave"}), "Hewn out of the rock, the tunnel " +
	"walls curve and meet above your head.");
    INSIDE;
    LIGHT;
    add_exit(TDIR + "living2", "south", 0);
    add_exit(TDIR + "cafeteria", "east", 0);
    add_exit(TDIR + "living4", "northeast", 0);
}

area() { return "Inthelivingquarters"; }
wayout() { return "northeast south"; }
tohelp() { return "northeast"; }
fromhelp() { return "south"; }

