#include "default.h"
inherit CVAN_ROOM;

#define GG	(NPC + "gateguard")

object ob1;
object ob2;
object ob3;
object ob4;
object ob5;
object ob6;
object ob7;
object ob8;
object door;

void
create_cvan_room()
{
    set_short("The Caravan Gate");
    set_long("This is where Caravan Street leads "+
      "through the massive steel doors of the Caravan Gate, " +
      "leaving the city to the north. It also heads " +
      "south towards its distant terminus at the " +
      "southern end of the city. Gateway Lane crosses " +
      "Caravan Street here, following the city wall " +
      "east and west.\n"+
      "There is a gatehouse here.\n");

    add_item( ({ "gatehouse" }),
      "It is a large stone gatehouse, you can see two small windows "+
      "through which the guards watch passersby.\n");

    add_item( ({ "windows", "window" }),
      "Both windows are plain and unadorned, you cannot see into the "+
      "gatehouse due to the dark interior.\n");

    add_item(({ "large winch", "winch" }), "A large metal rod used to open up the "+
      "Caravan Gate.\n");

    add_exit(CVAN + "caravan/s1", "south");
    add_exit(CVAN + "gateway/s4", "west");
    add_exit(CVAN + "gateway/s5", "east");
    add_exit(CVAN + "caravan/gatehouse", "in");

    door = clone_object(CVAN + "door/cgdoor");
    door->move(TO);

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(NPC + "in_cggk");
	ob1->move_living("M",TO);
    }

    if (!ob2)
    {
	ob2 = clone_object(NPC + "cmilitia_cg");
	ob2->arm_me();
	ob2->move_living("M",TO);
    }

    if(!ob3)
    {
	ob3 = clone_object(GG);
	ob3->arm_me();
	ob3->move_living("M",TO);
    }

    if(!ob4)
    {
	ob4 = clone_object(GG);
	ob4->arm_me();
	ob4->move_living("M",TO);
    }

    if(!ob5)
    {
	ob5 = clone_object(GG);
	ob5->arm_me();
	ob5->move_living("M",TO);
    }

    if(!ob6)
    {
	ob6 = clone_object(GG);
	ob6->arm_me();
	ob6->move_living("M",TO);
    }

    if(!ob7)
    {
	ob7 = clone_object(GG);
	ob7->arm_me();
	ob7->move_living("M",TO);
    }

    if(!ob8)
    {
	ob8 = clone_object(GG);
	ob8->arm_me();
	ob8->move_living("M",TO);
	ob1->team_join(ob2);
	ob1->team_join(ob3);
	ob1->team_join(ob4);
	ob1->team_join(ob5);
	ob1->team_join(ob6);
	ob1->team_join(ob7);
	ob1->team_join(ob8);
	tell_room(TO, "A gatekeeper and a militiaman arrive at the Caravan Gate, "+
	  "accompanied by a troop of six elite guardsmen of Kabal.\n");
    }
}

int
block()
{
    write("The way is blocked by a barricade.\n");
    return 1;
}

int
crank(string str)
{
    if(!str || str != "winch")
    {
	notify_fail("Crank what?\n");
	return 0;
    }
    write("You try in vain to crank the winch, but realize you aren't well "+
      "trained enough to do so.\n");
    say(QCTNAME(TP) + " tries in vain to crank the winch but isn't "+
      "knowledgeable enough to work the door mechanism.\n");
    return 1;
}

int
climb(string what)
{
    NF("Climb what?\n");
    what = lower_case(what);
    if (!what || (what != "gate" && what != "gates" &&
	what != "door" && what != "doors" && what != "steel door" &&
	what != "steel door" && what != "caravan gate"))
    {
	return 0;
    }

    NF("But the gate is open! It would look kind of stupid to climb it now.\n");
    if (door->query_open())
    {
	return 0;
    }

    write("You climb over the gate with some difficulties.\n");
    TP->move_living("climbing over the gate.", CPASS + "w1", 1, 0);
    return 1;
}

void
init()
{
    ::init();
    AA(crank,crank);
    AA(climb,climb);
}
