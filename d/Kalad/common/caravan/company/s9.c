#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Intersection");
    set_long("You are at the intersection of two grand hallways.\n"+
      "The magnificent entrance hallway lies to your south. Lining it are "+
      "dozens of marble busts. Crossing east-west from here is a smaller "+
      "hallway, though no less grand.\n");

    add_item(({ "marble busts", "busts" }),
      "Dozens of them line the hallway to the south. Reading a few "+
      "inscriptions at the base of some busts you realize that each of them "+
      "depicts a former leader of the Trading Company.\n");

    add_exit(CVAN + "company/s8", "west");
    add_exit(CVAN + "company/s26", "south");
    add_exit(CVAN + "company/s10", "east");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "tcguard");
	ob1->move_living("M", this_object());
    }
}
