#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("The Hallway");
    set_long("You are travelling down a hallway.\n"+
      "This passageway is utterly devoid of any furnishings whatsoever. "+
      "The only thing of note is the marble floor. The hallway continues to "+
      "the west and east.\n");

    add_item(({ "marble floor", "floor" }),
      "The ground is covered with marble tiles that are a brilliant white "+
      "color, so bright you feel you might be blinded if you stare too long "+
      "at them.\n");

    add_exit(CVAN + "company/s12", "west");
    add_exit(CVAN + "company/s14", "east");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "tcserv");
	ob1->move_living("M", TO);
    }
}
