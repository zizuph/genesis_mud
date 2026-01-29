#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

void reset_room();

void
create_room()
{
    set_short("Convenience Guild Lab");

    set_long(BS("Amidst huge piles of broken springs and wood and " +
      	"metal shavings you see a few gnomes puttering with several " +
      	"arcane contraptions.  This is the Convenience Guild lab, " +
      	"dedicated to improving the quality of life of the average " +
     	"gnome.  The machine in the gnomish cafeteria and the early " +
      	"work on the gnomeflingers are but a few of their triumphs.", 70));

    INSIDE;
    LIGHT;
    add_exit(TDIR + "cavern32", "southeast", 0);
    add_exit(TDIR + "guard3", "north", 0);
    reset_room();
}

void
reset_room()
{
    if (!present("emong", TO))
	set_alarm(1.0, -1.0, "fillit");
    if (!present("helmet", TO))
	clone_object(OBJ + "lhelmet")->move(TO);
}

string wayout() { return "southeast north"; }
string tohelp() { return "north"; }
string fromhelp() { return "southeast"; }
string area() { return "Hereonthisfloor"; }

void
fillit()
{
    int i;
    for (i = 0; i < 2; i++)
        clone_object(MON + "gnome")->move_living("xxx", TO);
}
