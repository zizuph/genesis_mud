#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

object ob, granite_wall;
object wthanoi;

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

    granite_wall = clone_object(OBJK + "granite_wall.c");
    granite_wall->move(TO); 

    set_short("Behind the turn");
    set_long("@@long_descr");


    add_exit("storage2","north","@@north");
    add_exit("storage4","south","@@south",1,1);

    add_item(({"piles","furs","straw"}),"Definitely for the Thanoi " +
     "to sleep on... And do whatever else pleases them. The " +
     "smell is horrible.\n");
    add_item(({"marks","scratch marks"}), "The scratch marks " +
     "show that the Thanoi tried repeatedly " +
     "to push the granite wall aside... you wonder why.\n");

    set_tell_time(800);

    add_tell("A horrible smell wafts from the heaps of fur and " +
     "straw on the floor.\n");
    add_tell("From behind the strange wall you hear some muted sounds... " +
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
    "Just a few meters behind the turn, the stone corridor " +
    "has been blocked off with a smooth as silk, solid granite " +
    "wall. Although you can see no see no cement at all, the " +
    "wall fits perfectly into the corridor. " +
    "Scattered haphazardly behind the turn of the corridor " +
    "are piles of straw, furs, and rags. The undeniable proof can " +
    "be found in the smell - someone has organized sleeping " +
    "quarters for the thanoi here...\n");
    

}


int
north()
{ 
  write("Stepping carefully around the smelly heaps, you walk " +
   "back into the storage room.\n");
  say(QCTNAME(TP) + " carefully steps around the smelly heaps.\n");
  return 0;
}

int
south()
{ 
  write("Try as you might - and as several Thanoi tried before " +
   "- you simply hit your head on the granite wall and move no " +
   "further.\n");
  say("Maybe presuming its an illusion, " + QTNAME(TP) +
   " tries to walk further south, through the granite wall, " +
   "but simply hits " + HIS(TP)	+ " head on it.\n");
  return 1;
}


int
push(string str)
{
    if(str != "granite wall")
      {
        notify_fail("Push which wall?\n");
        return 0;
      }

    write("With all your strength, you attempt to push the " +
      "granite wall aside, but just as countless Thanoi before you, " +
      "you fail miserably. Are you sure you want to break through?\n");
    say(QCTNAME(TP) + " attempts to budge the granite wall out of " +
      "the way, but fails miserably.\n");

    return 1;
}

int
brk(string str)
{
    if(str == "through granite wall" || str == "through thick wall" || str == "through thick granite wall")
      {
    write("With a roar of frustrated rage, you attempt to " +
      "break your way through the granite wall. Without success, " +
      "of course, though you manage to earn yourself a bruise " +
      "or two.\n");
    say("With a roar of frustrated rage, " + QTNAME(TP) + " " +
      "attempts to break " + HIS(TP) + " way through the granite wall. " +
      "Without success, of course, though " + HE(TP) + " manages to " +
      "collect a large bruise.\n");
    TP->heal_hp(-50); 
    return 1;
      }

    notify_fail("Break through which wall?\n");
    return 0;

}


void
init()
{
    ::init();

    add_action(push, "push");
    add_action(brk,"break");
}   