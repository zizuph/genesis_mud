#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

void reset_room();

void
create_room()
{
    set_short("Middle of main cavern");

    set_long(BS("You are in the middle of a vast natural cavern.  " +
      	"Total chaos reigns as hundreds of gnomes build, adjust, and " +
      	"argue about contraptions of all shapes and sizes.  At several " +
      	"levels along the cavern walls you notice holes leading to " +
      	"more work rooms.  Just to the north you see some unusually " +
      	"complex looking catapults.", 70));

    INSIDE;
    LIGHT;
    add_item(({"cavern", "cave", "caves"}),
	"Formed through natural erosion, this cavern is hundreds of " +
	"meters long and\nabout thirty meters high.  It is fairly narrow " +
	"along its length, though it\nis wider higher up.\n");
    add_item(({"catapult", "catapults", "gnomeflinger", "gnomeflingers"}),
      	"Though few are actually fully assembled, the cavern contains " +
	"dozens of these\ndevices.  Everywhere you look catapults are " +
	"being tested, adjusted,\ndisassembled, built, or several of " +
	"these all at once.  Funny, gnomes don't\nlook very warlike.\n");

    add_exit(TDIR + "cavern4", "south", 0);
    add_exit(TDIR + "cavern6", "north", 0);
    add_exit(TDIR + "brim/bri_room", "east");
    reset_room();
}

void
reset_room()
{
    if (!present("emong", TO)) set_alarm(1.0, -1.0, "fillit", random(5) + 1);
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


