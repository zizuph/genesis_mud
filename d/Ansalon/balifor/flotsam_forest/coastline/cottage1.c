#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>

inherit FOREST_IN;

object wiz;

void
reset_flotsam_room()
{
    if(!objectp(wiz))
    {
	wiz = clone_object(FNPC + "ferm");
	wiz->arm_me();
	wiz->move(TO);
    }
}

create_flotsam_room()
{
    set_short("A small cosy room inside the cottage");
    set_long("@@long_descr");

    add_item(({"interior of the cottage","cottage","room"}),
      "@@long_descr");
    add_item(({"cheery fire","fireplace","northern wall","fire"}),
      "A cheery fire burns in a fireplace on the northern " +
      "wall, casting a warm glow throughout the room.\n");
    add_item(({"wooden rocking-chair","rocking-chair","chair"}),
      "A wooden rocking-chair, comfortably positioned before " +
      "the fire.\n");
    add_item(({"door","mahogany door","large mahogany door"}),
      "A large mahogany door leads out of the cottage.\n");
    add_item(({"staircase","stairs"}),
      "A wooden staircase leads up to the second floor.\n");


    add_exit(CROOM + "road13","out",0);
    add_invis_exit("","up","@@climb_stairs");

    add_cmd_item(({"stairs","staircase"}),({"climb","go up"}),
      "@@up_stairs");


    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand within the interior of the small cottage. " +
    "A cheery fire burns in a fireplace on the northern wall, " +
    "casting a warm glow throughout the room. A wooden rocking-" +
    "chair sits before the fire. A staircase on the far side " +
    "of the room rises up to the second floor. A large mahogany " +
    "door to the south leads out.\n";
}

int
climb_stairs()
{
    write("You start walking up the staircase, but bump "+
      "into an invisible wall!\n");
    say(QCTNAME(TP)+ " tries to climb the stairway, but runs "+
      "into a mystical invisible wall!\n");
    return 1;
}

string
up_stairs()
{
    write("You start walking up the staircase, but bump " +
      "into an invisible wall!\n");
    say(QCTNAME(TP) + " tries to climb the stairway, but runs " +
      "into a mystical invisible wall!\n");
    return "";
}
