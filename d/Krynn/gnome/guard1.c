#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
#include <ss_types.h>

inherit "/d/Krynn/std/room";

create_room()
{
    set_short("First floor guard room");
    set_long(BS("This is one of the small guard stations located on the " +
      	"upper floors.  In the event of intrusion or (more likely) a " +
      	"disaster with one of their experiments, gnomes come here for help." +
      	"  A pole extends through the floor and ceiling here.", 70));

    INSIDE;
    LIGHT;
    add_item(({"cavern", "cave", "caves"}), "A small gnome-made chamber " +
	"connected to the first floor passages.\n");
    add_item("pole", "A slippery pole which extends all the way up to " +
	"the third floor!  Pillows lie around the base one floor down.\n");

    add_cmd_item(({"down", "down pole", "pole"}), "slide", "@@slide");
    add_cmd_item(({"up", "up the pole", "pole"}), "climb", "@@climb");

    add_exit(TDIR + "cavern15", "south", 0);
    reset_room();
}

reset_room()
{
    if (!present("guard", TO)) fillit();
}

slide()
{
    write("You slide down the pole to the ground floor!  Wheeeeee...\n");
    TP->move_living("down the pole", TDIR + "guard0");
    return "You stand up and dust yourself off...\n";
}

wayout() { return "south"; }
tohelp() { return "done"; }
fromhelp() { return "south"; }

fillit()
{
    int i;
    for (i = 0; i < 2; i++)
	clone_object(MON + "guard")->move_living("xxx", TO);
}

climb()
{
    if (random(50) < TP->query_skill(SS_CLIMB))
    {
        write("You manage to climb the pole!\n");
        TP->move_living("climbing the pole", TDIR + "guard2");
        return 1;
    }
    write("You try but fail to climb the pole and slide all the way down.\n");
    say(QCTNAME(TP) + " tries in vain to climb the pole.\n");
    TP->move_living("sliding down the pole", TDIR + "guard0");
    return 1;
}
