#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

object minotaur1, minotaur2, minotaur3, minotaur4, minotaur5;
object minotaur6, minotaur7, leader;

public void
reset_icewall_room()
{
    if (!minotaur1)
    {
	minotaur1 = clone_object(NPCK + "castle_mino.c");
	minotaur1->move_living("xx", TO);
    }
    if (!minotaur2)
    {
	minotaur2 = clone_object(NPCK + "castle_mino.c");
	minotaur2->move_living("xx", TO);
    }
    if (!minotaur3)
    {
	minotaur3 = clone_object(NPCK + "castle_mino.c");
	minotaur3->move_living("xx", TO);
    }
    if (!minotaur4)
    {
	minotaur4 = clone_object(NPCK + "castle_mino.c");
	minotaur4->move_living("xx", TO);
    }
    if (!minotaur5)
    {
	minotaur5 = clone_object(NPCK + "castle_mino.c");
	minotaur5->move_living("xx", TO);
    }
    if (!minotaur6)
    {
	minotaur6 = clone_object(NPCK + "castle_mino.c");
	minotaur6->move_living("xx", TO);
    }
    if (!minotaur7)
    {
	minotaur7 = clone_object(NPCK + "castle_mino.c");
	minotaur7->move_living("xx", TO);
    }
    if (!leader)
    {
	leader = clone_object(NPCK + "m_castle_mino.c");
	leader->move_living("xx", TO);
    }

}

void
create_icewall_room()
{

    set_short("Garrison barracks, south end");
    set_long("@@long_descr");


    add_exit("courtyard_north","west","@@west");
    add_exit("mino_garrison2","north");

    add_item("doorway","The ironwood doorway to the barracks has " +
     "been repeatedly scratched and in places even deeply gauged " +
     "on the overhead part of the frame. You wonder how " +
     "many sets of minotaur horns partook in the destruction...\n");
    add_item(({"bunks","fur bunks"}),"Large, spartan, functional, " +
     "and evenly set apart. One could use the same words to " +
     "describe the entire race.\n");
    add_item(({"weaponry","heavy weaponry"}),"Huge axes, tesstos, " +
     "daggers the size of a broadsword, spiked and serrated " +
     "bucklers as well as massive warswords, all well cared for. " +
     "The minotaurs are renowned for their strength and skill, and " +
     "not many care to test their brutal abilities in battle.\n");

    set_tell_time(900);

    add_tell("Somewhere on the floor above you, heavy footsteps " +
     "resound.\n");

    reset_room();
}

void

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string

long_descr()

{ return ("" +
     "Long ago, this spacious room housed the castle's garrison. " +
     "Right now, however, it contains several fur bunks and " +
     "an impressive array of heavy weaponry. The room continues " +
     "further north, but even now it becomes clear that you have " +
     "stumbled right into the barracks of minotaurs!!\n");
}

int
west()
{ 
  write("Stepping through the scratched doorway, you exit the " +
    "barracks.\n");
  say(QCTNAME(TP) + " steps under the scratched doorway.\n");
  return 0;
}
      