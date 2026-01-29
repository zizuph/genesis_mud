#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

void reset_room();

void
create_room()
{
    set_short("South end of main cavern");

    set_long(BS("You are at the southern end of a vast natural cavern.  " +
     	 "Total chaos reigns as hundreds of gnomes build, adjust, and " +
      	"argue about contraptions of all shapes and sizes.  At several " +
      	"levels along the cavern walls you notice holes leading to " +
      	"more work rooms.  Catapults seem the most common device on " +
      	"the cavern floor.  The chamber extends to the north, while a " +
      	"tunnel leads southwest from here.", 70));
    INSIDE;
    LIGHT;
    
    add_item(({"cavern", "cave", "caves"}),
	"Formed through natural erosion, this cavern is hundreds of " +
	"meters long and\nabout thirty meters high.  It is fairly narrow " +
	"along its length, though it\nis wider higher up.\n");
    add_item(({"catapult", "catapults", "gnomeflinger", "gnomeflingers"}),
      	"Though few are actually fully assembled, the cavern contains " +
	"dozens of these\ndevices.  Everywhere you look catapults are being " +
	"tested, adjusted,\ndisassembled, built, or several of these all at " +
	"once.  Funny, gnomes don't\nlook very warlike.\n");
    add_item(({"hole", "holes"}),
    	"Gnomes mill in and out of them. Inside, there are even more than " +
    	"out here. They flutter around so fast you barely can follow their " +
    	"movements.\n");
    add_cmd_item("hole", "enter", "Just the moment you advanced, a gnome " +
   	"entered the hole from the other side blocking your path. You back " +
   	"out.\n");
    
    add_exit(TDIR + "cavern3", "southwest", 0);
    add_exit(TDIR + "cavern5", "north", 0);
    reset_room();
}

void
fillit()
{
    int i, num;

    num = random(5) + 1;
    for (i = 0; i < num; i++)
	clone_object(STAND_DIR+"gnome/monster/gnome")->move_living("xxx", TO);

}

string area() { return "Inthemaincaverns"; }
void reset_room() { if (!present("emong", TO)) set_alarm(1.0, -1.0,"fillit"); }
string wayout() { return "north southwest"; }
string tohelp() { return "north"; }
string fromhelp() { return "southwest"; }
