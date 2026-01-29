#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

create_room()
{
    set_short("Third floor guard room");
    set_long(BS("This is one of the small guard stations located on the " +
      	"upper floors.  In the event of intrusion or (more likely) a " +
      	"disaster with one of their experiments, gnomes come here for help." +
      	"  A pole extends down from the ceiling through the floor here.", 70));


    INSIDE;
    LIGHT;
    add_item(({"cavern", "cave", "caves"}), "A small gnome-made chamber" +
	" connected to the first floor passages.\n");
    add_item("pole", "A slippery pole which extends all the way to the" +
	" ground floor!  Pillows lie\naround the base.\n");

    add_cmd_item(({"down", "down pole", "pole"}), "slide", "@@slide");
    add_cmd_item(({"up", "up the pole", "pole"}), "climb", "You are "
	+ "already on the highest level.\n");

    add_exit(TDIR + "cavern33", "south", 0);
    reset_room();
}

reset_room() { if (!present("guard", TO)) fillit(); }

slide()
{
    write("You slide down the pole to the ground floor!  Wheeeeee...\n");
    TP->move_living("down the pole", TDIR + "guard0");
    return "You stand up and dust yourself off...\n";
}

wayout() { return "south"; }
tohelp() {  return  "done"; }
fromhelp() { return "south"; }

fillit()
{
    int i;
    for (i = 0; i < 2; i++)
	clone_object(MON + "guard")->move_living("xxx", TO);
}
