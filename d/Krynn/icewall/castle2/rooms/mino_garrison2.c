#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

object minotaur1, minotaur2, minotaur3, minotaur4, minotaur5;
object minotaur6, minotaur7, leader, hrunie;

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
    if (!hrunie)
    {
	hrunie = clone_object(NPCK + "hrun.c");
	hrunie->move_living("xx", TO);
    }
}

void
create_icewall_room()
{

    set_short("Garrison barracks, north end");
    set_long("@@long_descr");

    add_exit("mino_garrison","south");

    add_item(({"bunks","fur bunks"}),"Large, spartan, functional, " +
     "and evenly set apart. One could use the same words to " +
     "describe the entire race. A single large bunk has been " +
     "set apart from rest.\n");
    add_item("large bunk","This large bunk is situated under the " +
     "north wall, as far from the exit as possible. Around it, " +
     "on all sides, free space has been left. By the several " +
     "trophies hung on the wall above the bunk, you get the " +
     "impression that someone important quarters here.\n");
    add_item("trophies","Most prominent is the huge head of a " +
     "white polar bear. Its open mouth presents an array of broken " +
     "teeth, and the skull has been caved in on one side. Whoever " +
     "could smash a bear in such fashion truly deserves a title " +
     "of a warrior born.\n");
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
     "Right now, however, it contains many fur bunks and " +
     "an impressive array of heavy weaponry. Under the north " +
     "wall a large, isolated bunk has been set. On the wall above " +
     "it, several trophies hang. You're deep inside a minotaur barrack!\n");
}
      