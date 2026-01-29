#include "../default.h"
inherit CVAN_ROOM;

#define AXEMAN	(NPC + "tcguard1")

object ob1;
object ob2;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("The Grand Hallway");
    set_long("You are walking along the grand hallway.\n"+
      "This magnificent passageway, which stretches to the north and south "+
      "is lined by dozens of marble busts. The floor is also made of marble "+
      "and looks to have been meticulously polished.\n");

    add_item(({ "busts" }),
      "Dozens of them line the entire hallway. Reading the inscriptions "+
      "at the base of a few busts you come to realize that each of them "+
      "depicts a former leader of the Trading Company.\n");

    add_exit(CVAN + "company/s9", "north");
    add_exit(CVAN + "company/s37", "south");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(AXEMAN);
	ob1->move_living("M", TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(AXEMAN);
	ob2->move_living("M", TO);
	ob1->team_join(ob2);
    }
}
