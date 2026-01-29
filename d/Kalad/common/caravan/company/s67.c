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
    set_long("You are travelling along a hallway.\n"+
      "This passage, unlike the others on this floor is not devoid of "+
      "furnishings. On the western side of the hallway are several paintings "+
      "of people. The eastern side is also similarly decorated, except "+
      "with several plaques instead of paintings. The passageway continues "+
      "to the north and south.\n");

    add_item(({ "paintings" }), "Each masterfully painted picture depicts a "+
      "man of regal and haughty bearing. You realize that all the paintings "+
      "are of this one man, except that each one is of him in a different "+
      "perspective.\n");

    add_item(({ "plaques" }), "Burnished bronze plaques that have writing "+
      "on them. It seems to be written in some old language, because you "+
      "understand very little of it. All that you can decipher is something "+
      "about rulership.\n");

    add_exit(CVAN + "company/s62", "north");
    add_exit(CVAN + "company/s54", "south");

    clone_object(CVAN + "door/tcdoor8")->move(TO);

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
