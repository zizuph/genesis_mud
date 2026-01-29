#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/std/room";

void reset_room();

void
create_room()
{
    set_short("Outside the Gnomish Industries Explosives Lab");
    set_long(BS("This room stands just east of the " +
    	"Explosives Development Center of Gnomish Industries.  " +
    	"Testing for the structural integrity of the " +
    	"bedrock has already taken place, and the gnomes are "+
    	"confident their work here will in no way endanger "+
    	"the rest of the caves or the surface of Krynn " +
    	"in this area...", 70));
//    add_exit(TDIR + "cavern16", "enter", 0,1,1);
	add_exit(TDIR + "explosive/room/expl1","west", 0);
    add_exit(TDIR + "cavern14", "east", 0);
    add_exit(TDIR + "guard1", "north", 0);
    INSIDE;
    LIGHT;
    reset_room();
}

void
reset_room() { if (!present("emong", TO)) set_alarm(1.0, -1.0, "fillit"); }

string wayout() { return "east north"; }
string tohelp() { return "north"; }
string fromhelp() { return "east"; }
string area() { return "Hereonthisfloor"; }

void
fillit()
{
    int i;
    for (i = 0; i < 2; i++)
	clone_object(MON + "gnome")->move_living("xxx", TO);
}
