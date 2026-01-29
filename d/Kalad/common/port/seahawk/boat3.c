#include "../default.h"
inherit PORT_ROOM;

#include <ss_types.h>
#define HARD_TO_MOVE 10
#define DAMAGE 50
string long;
#define TOUR PORT + "npc/tourist"
object ob1;
object ob2;
object ob3;
object ob4;
object ob5;

void
create_port_room()
{
     /*always do this*/
    set_short("The very center of the Seahawk");
    set_long("This is the very center of the Seahawk, and obviously the "+
      "area with the most activity. Before you rises the main mast of the "+
      "ship, from which the billowing white sails flutter. At the peak of "+
      "the mast is perched a crow's nest.\n");
    set_time_desc("A crowd of tourists wanders about you.\n","A few "+
      "people are passing by.\n");
    add_item(({"main mast","mast"}),"A large wooden mast that rises "+
      "high up into the air. At its very peak, past the billowing sails, "+
      "you can make out a crow's nest.\n");
    add_item(({"billowing white sails","billowing sails","white sails","sails","sail"}),
      "Great cloth canvases that catch the sea-blown wind in them, causing "+
      "them to stretch full out. Quite an impressive sight.\n");
    add_item(({"crow's nest","nest"}),"A small wooden platform that "+
      "sits a few dozen feet up in the air. Back in the Seahawk's heyday, "+
      "lookouts would use it to search for any possible dangers to the "+
      "ship, whether in the form of marauding pirates or shallow waters.\n");
    add_item(({"tourists","tourist","crowd"}),"A diverse group of "+
      "people, most of whom are foreigners such as yourself, since noone "+
      "native to Kabal would be even remotely interested in this ship.\n");
    add_item(({"people"}),"A small group of individuals that have "+
      "used this off-hour time to take a look at the historic Seahawk.\n");

    add_exit(PORT + "seahawk/boat9", "west");
    add_exit(PORT + "seahawk/boat1", "north");
    add_exit(PORT + "seahawk/boat4", "east");
    add_exit(PORT + "seahawk/boat7", "south");
    add_exit(PORT + "seahawk/mast1", "up","@@move",1,2);
    reset_room();
}

move()
{
    if(TP->query_skill(SS_CLIMB) < random(HARD_TO_MOVE))
    {
	write("You start to climb up the main mast...\n");
	write("You slip and fall!\n");
	write("You hit the deck with a resounding THUD!\n");
	TP->heal_hp(-DAMAGE);
	say(QCTNAME(TP) + " starts to climb up the mast...\n");
	say(QCTNAME(TP) + " slips and falls!\n");
	say(capitalize(TP->query_pronoun() + " hits the deck with a resounding THUD!\n"));
	if(TP->query_hp() <= 0)
	    TP->do_die(TO);
	return 1;
    }

    write("You manage to climb up the main mast.\n");
    say(QCTNAME(TP) + " manages to climb up the main mast.\n");
    return 0;
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/tour_guide");
	ob1 -> move_living("xxx",TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(TOUR);
	ob2 -> move_living("xxx",TO);
    }

    if(!ob3)
    {
	ob3 = clone_object(TOUR);
	ob3 -> move_living("xxx",TO);
    }

    if(!ob4)
    {
	ob4 = clone_object(TOUR);
	ob4 -> move_living("xxx",TO);
    }

    if(!ob5)
    {
	ob5 = clone_object(TOUR);
	ob5 -> move_living("xxx",TO);
	ob1 -> team_join(ob2);
	ob1 -> team_join(ob3);
	ob1 -> team_join(ob4);
	ob1 -> team_join(ob5);
    }
}

