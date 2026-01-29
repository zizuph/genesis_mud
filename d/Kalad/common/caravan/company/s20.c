#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Hallway");
    set_long("You are travelling down a hallway.\n"+
      "This passageway is empty of any furnishings. The only thing of real "+
      "note is the marble floor and the door to the north. The hallway "+
      "continues to the west and east.\n");

    add_item(({ "marble floor", "floor" }), "The floor is such a brilliant "+
      "white in color that looking at it for more than a few moments could "+
      "blind you.\n");

    add_exit(CVAN + "company/s21", "west");
    add_exit(CVAN + "company/s19", "east");

    clone_object(CVAN + "door/dhdoor")->move(TO);

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "tcguard");
	ob1->move_living("M", TO);
    }
}
