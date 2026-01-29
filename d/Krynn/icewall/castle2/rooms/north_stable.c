#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

object minotaur1, minotaur2, minotaur3, minotaur4;
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
    if (!leader)
    {
	leader = clone_object(NPCK + "m_castle_mino.c");
	leader->move_living("xx", TO);
    }
}

void
create_icewall_room()
{
    set_short("North stable staircase");
    set_long("@@long_descr");

    add_exit("stable","south","@@south");
    add_exit("battlement3","up","@@up");

    add_item(({"stairway","stairs"}),"A circular stone staircase " +
     "situated in the middle of this small chamber leads upwards, " +
     "towards the second level of the building.\n");
  add_item(({"passageway","passageways"}),"Wide passageway " +
     "leads south towards what was long ago the castle's stable. " +
     "You see nothing special about it.\n");

    set_tell_time(900);

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
     "This small chamber contains only the spiral staircase " +
     "leading up to the battlements. It purpose its simple - " +
     "to facilitate quick access to battlements on the castle's " +
     "west side for troops waiting in the courtyard, or in the " +
     "garrison area. Thanks to the staircase, the west wall can be " +
     "reinforced without soldiers pushing through around the " +
     "whole battle line, and most likely disorganising defence " +
     "there. A wide passageway leads south, into the stable\n");    

}


int
south()
{ 
  write("You head for the wide passageway.\n");
  say(QCTNAME(TP) + " heads for the wide passageway.\n");
  return 0;
}

int
up()
{ 
  write("Trudging up the stone steps, you ascend the stairway.\n");
  say(QCTNAME(TP) + " trudges up the stone steps.\n");
  return 0;
}