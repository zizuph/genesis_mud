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
    set_short("Middle part of a L-shaped storage room");
    set_long("@@long_descr");


    add_exit("huge_warehouse","down","@@draft");
    add_exit("inner_courtyard","north"); 
    add_exit("storage2","east","@@east");
    add_exit("storage3","west","@@west");

    add_item(({"piles","furs","straw"}),"Definitely for the Thanoi " +
     "to sleep on... And do whatever else pleases them. The " +
     "smell is horrible.\n");
    add_item(({"old stairway","stone stairway","stairway"}),"Old " +
     "stone blocks cemented together in a spiral fashion, leading " +
     "down into shadowy depths. Though old, the stairway looks solid " +
     "enough to support you.\n");
    add_item(({"door","north door"}),"Ripped from its hinges, the " +
     "west door no longer protects the room from the everlasting " +
     "winter. You see no reason for such action... what you see " +
     "through the door, however, is a courtyard with a beautiful " +
     "fountain.\n");
    add_item("wall","Which wall do you wish to examine?\n");
    add_item("south wall","A normal looking wall, dividing the lower " +
     "garrison building from the higher main structure.\n");

    set_tell_time(800);

    add_tell("A horrible smell wafts from the heaps of fur and " +
     "straw on the floor.\n");
    add_tell("You think you've heard something from other side " +
     "of the south wall... drunken laughter, perhaps?\n");
    add_tell("A cold draft raises from the opening in the floor.\n");

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
    "You stand in the middle of the castle storage room. " +
    "It runs in the east-west direction, with a right angle " +
    "turn at its eastern end. Here, long ago, rested " +
    "everything from spare chairs to fresh sheets and many " +
    "other odds and ends required to properly run every day life. " +
    "However, now the room has been stripped bare, and serves a " +
    "different purpose. Scattered haphazardously around the room " +
    "are piles of straw, furs, and rags. The undeniable proof can " +
    "be found in the smell - someone has organised sleeping " +
    "quarters for the thanoi here...\nThe door " +
    "leading north to the courtyard has been knocked down and in " +
    "result frost lines every wall. From under the south wall, " +
    "directly opposite the west exit, a trapdoor has been " +
    "removed, revealing an old stone stairway. Your presume it " +
    "leads to the castle cellar, where wine and meats were stored.\n");
    

}

int
draft()
{
  write("As you head downwards, a cold draft awashes you.\n");

  return 0;
}           

int
east()
{ 
  write("Stepping carefully around the smelly heaps, you make your " +
   "way towards the east end of the storage room.\n");
  say(QCTNAME(TP) + " carefully steps around the smelly heaps.\n");
  return 0;
}

int
west()
{ 
  write("Stepping carefully around the smelly heaps, you make your " +
   "way towards the west end of the storage room.\n");
  say(QCTNAME(TP) + " carefully steps around the smelly heaps.\n");
  return 0;
}