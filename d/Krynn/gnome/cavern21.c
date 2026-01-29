#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

void reset_room;

void
create_room()
{
    set_short("Landing for the second floor");

    set_long(BS("You are on the landing for the second floor.  A tunnel " +
      	"leads west into the cavern wall.  Below you hundreds of gnomes " +
        "mill about.", 70));

    add_item(({"cavern", "cave", "caves"}), "Formed through natural erosion," +
	" this cavern is hundreds of meters long and\nabout thirty meters" +
	" high.  It is fairly narrow along its length, though it\nis wider" +
	" higher up.  You stand on a projection partway up the side.");

    INSIDE;
    LIGHT;
    add_exit(STAND_DIR + "gnome/cavern22", "west", 0);
    reset_room();
}

void
reset_room() { if (!present("emong", TO)) set_alarm(1.0, -1.0,"fillit"); }

string wayout() { return "west"; }
string tohelp() { return "west"; }
stringfromhelp() { return "done"; }
string area() { return "Hereonthisfloor"; }

void
fillit()
{
    int i;
    for (i = 0; i < 2; i++)
        clone_object(MON + "gnome")->move_living("xxx", TO);
}
