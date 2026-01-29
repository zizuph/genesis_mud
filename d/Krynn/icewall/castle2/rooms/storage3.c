#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;


object thanoi1, thanoi2, thanoi3, thanoi4, leader;

public void
reset_icewall_room()
{
    if (!thanoi1)
    {
	thanoi1 = clone_object(NPCK + "castle_thanoi.c");
	thanoi1->move_living("xx", TO);
    }
    if (!thanoi2)
    {
	thanoi2 = clone_object(NPCK + "castle_thanoi.c");
	thanoi2->move_living("xx", TO);
    }
    if (!thanoi3)
    {
	thanoi3 = clone_object(NPCK + "castle_thanoi.c");
	thanoi3->move_living("xx", TO);
    }
    if (!thanoi4)
    {
    if (random(2))
    {
	thanoi4 = clone_object(NPCK + "castle_thanoi.c");
	thanoi4->move_living("xx", TO);
    }
    }
    if (!leader)
    {
	leader = clone_object(NPCK + "m_castle_thanoi.c");
	leader->move_living("xx", TO);
    }
}


void
create_icewall_room()
{
    set_short("West part of a L-shaped storage room");
    set_long("@@long_descr");


    add_exit("storage1","east","@@east");

    add_item(({"piles","furs","straw"}),"Definitely for the Thanoi " +
     "to sleep on... And do whatever else pleases them. The " +
     "smell is horrible.\n");

    set_tell_time(800);

    add_tell("A horrible smell wafts from the heaps of fur and " +
     "straw on the floor.\n");
    add_tell("From behind the southern wall you hear some muted sounds... " +
     "as if a drunken laughter?\n");

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
    "You stand at the west blind end of the castle storage room. " +
    "Here, long ago, rested " +
    "everything from spare chairs to fresh sheets and many " +
    "other odds and ends required to properly run every day life. " +
    "However, now the room has been stripped bare, and serves a " +
    "different purpose. Scattered haphazardously around the room " +
    "are piles of straw, furs, and rags. The undeniable proof can " +
    "be found in the smell - someone has organised sleeping " +
    "quarters for the thanoi here...\n");
    

}


int
east()
{ 
  write("Stepping carefully around the smelly heaps, you make your " +
   "way towards the middle part of the storage room.\n");
  say(QCTNAME(TP) + " carefully steps around the smelly heaps.\n");
  return 0;
}