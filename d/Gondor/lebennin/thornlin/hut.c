#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");

#include <macros.h>
#include <stdproperties.h>

#include "locals.h"

object  mordor_spy,
wolf_dog;

int
leave_hut()
{
    write("You walk through the door, and step out into the light.\n");
    return 0;
}

void
reset_room()
{
    set_alarm(1.0, 0.0, "add_npcs");
}

void
add_npcs()
{
    if (!objectp(mordor_spy))
    {
	mordor_spy = clone_object(NPC_DIR + "mordor_spy");
	mordor_spy->arm_me();
	mordor_spy->move_living("from the void", TO);
    }
    if (!objectp(wolf_dog))
    {
	wolf_dog = clone_object(NPC_DIR + "wolf_dog");
	wolf_dog->move_living("from the void", TO);
    }
}

void
create_room()
{
    INSIDE;  /* This room is a inside room */
    set_short("A small cold hut");
    set_long(BSN("The hut is rather small. At the east wall there "
	+ "is an unmade bed. In the middle of the room is a table and "
	+ "the floor seems to be covered by straws."));

    add_item(({"bed","unmade bed"}),"It is an unmade bed, looking rather "+ 
      "dirty.\n");
    add_item("table","The table is made of beech. A mouldy bread lies on "+ 
      "the table.\n");
    add_item(({"bread", "mouldy bread", }),BSN(
	"Half a loaf of bread, covered with green and fluffy white mould. "
	+ "It does not look like it is fit for human consumption any "
	+ "more. You even start to shiver at the thought of eating it."));
    add_item("straws","The straws covering the floor seems to have been "+
      "here for ages.\n");
    add_item("floor","It looks like it hasn't been cleaned in a very "+
      "long time.\n");

    add_exit(THORN_DIR + "open_field","out","@@leave_hut",1);

    reset_room(); 
}

