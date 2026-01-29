#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

void reset_room();

void
create_room()
{
    set_short("Northern end of main cavern");

    set_long(BS("You are at the northern end of a vast natural cavern. " +
      	"Gnomish inventions of many types can be seen to the south amidst " +
      	"crowds of busy little engineers.  Some of the gnomish living " +
      	"quarters are off to the north and west from here, along with their " +
      	"cafeteria and a few other conveniences.", 70));

    INSIDE;
    LIGHT;
    add_item(({"cavern", "cave", "caves"}),
	"Formed through natural erosion, this cavern is hundreds of " +
	"meters long and\nabout thirty meters high.  It is fairly " +
	"narrow along its length, though it\nis wider higher up.\n");
    add_exit(TDIR + "cavern7", "south", 0);
    add_exit(TDIR + "cavern9", "north", 0);
    add_exit(TDIR + "living1", "west", 0);
    reset_room();
}

void
reset_room()
{
    if (!present("emong", TO)) set_alarm(1.0, -1.0, "fillit", random(3) + 1);
}

void
fillit(int num)
{
    clone_object(MON + "gnome")->move_living("xxx", TO);
    if (--num > 0)
        set_alarm(itof(random(50)), -1.0, "fillit", num);
}

string area() { return "Inthemaincaverns"; }
string wayout() { return "north south"; }
string tohelp() { return "north"; }
string fromhelp() { return "south"; }

