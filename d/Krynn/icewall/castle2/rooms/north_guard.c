#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

object minotaur1, minotaur2, minotaur3, minotaur4, minotaur5;
object leader;

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
    if (!leader)
    {
	leader = clone_object(NPCK + "m_castle_mino.c");
	leader->move_living("xx", TO);
    }
}

void
create_icewall_room()
{
    set_short("North gate guardroom");
    set_long("@@long_descr");

    add_exit("tunnel_gate","south","@@south");
    add_exit("battlement7","up","@@up");

    add_item(({"stairway","stairs"}),"A circular stone staircase " +
     "situated at the north end of the chamber leads upwards, " +
     "towards the second level of the building.\n");

    set_tell_time(800);

    add_tell("You hear some footsteps above you, on the second floor " +
     "of the lower building.\n");

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
     "This is a spacious " +
     "chamber meant for guards both on and off duty. During " +
     "a siege, the room was meant to hold ready to use supplies, " +
     "such as full quivers, readied crossbows, and a back up stash " +
     "of swords, axes, polearms, and shields. Here, a guard could get " +
     "his wound tended and grab a pitcher of water before returning " +
     "up the circular staircase onto the roofed battlements above.\n\n" +
     "The new owner of the castle has set up a different " +
     "contingent of guards here, one that does not see the need for " +
     "such careful planning.\n");    

}


int
south()
{ 
  write("Squeezing through a half-opened door, you leave " +
   "the gateroom.\n");
  say(QCTNAME(TP) + " squeezes through a half-opened door.\n");
  return 0;
}

int
up()
{ 
  write("Trudging up the stone steps, you ascend the stairway.\n");
  say(QCTNAME(TP) + " trudges up the stone steps.\n");
  return 0;
}