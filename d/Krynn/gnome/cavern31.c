#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

void reset_room();

void
create_room()
{
    set_short("Landing on the third floor");

    set_long(BS("You are on the landing of the third floor.  A tunnel " +
      	"leads west into the cavern wall.  Below you hundreds of gnomes " +
      	"bustle about.", 70));

    INSIDE;
    LIGHT;
    add_item(({"cave", "caves", "tunnel"}), "Hewn out of the solid rock, " +
	"this tunnel is one of the gnomish\nresearch labs.  It extends a " +
	"long way from the main cavern.\n");
    add_exit(TDIR + "cavern32", "west", 0);
    reset_room();
}

void
reset_room()
{
    if (!present("emong", TO))
	set_alarm(1.0, -1.0, "fillit", random(3) + 1);
    if (!present("gauntlets", TO))
	clone_object(OBJ + "gauntlets")->move(TO);
}

string wayout() { return "west"; }
string tohelp() { return "west"; }
string fromhelp() { return "done"; }
string area() { return "Hereonthisfloor"; }

void
fillit(int num)
{
    int i;
    for (i = 0; i < num; i++)
        clone_object(MON + "gnome")->move_living("xxx", TO);
}

