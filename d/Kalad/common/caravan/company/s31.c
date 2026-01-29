#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Archway");
    set_long("This section of the hallway is lined with potted plants of "+
      "various kinds. To the east, an open archway leads outside of the "+
      "Company building into what looks like a courtyard. The hallway, "+
      "which stretches to the north and south is tiled in marble.\n");

    add_item(({ "plants" }), "Healthy and robust flowering plants, they are "+
      "set inside brown earthenware pots.\n");

    add_item(({ "pots" }), "Large containers made of fired earth. These are "+
      "what the plants have been planted in.\n");

    add_item(({ "marble" }), "The ground is covered in brilliant white "+
      "marble tiles that are so bright you are nearly blinded by looking at "+
      "them.\n");

    add_exit(CVAN + "company/s14", "north");
    add_exit(CVAN + "company/s16", "east");
    add_exit(CVAN + "company/s32", "south");

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

void
init()
{
    ::init();
    write("The smell of fresh roses wafts from the east.\n");
}
