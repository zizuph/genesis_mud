#include "../default.h"
inherit CVAN_ROOM;

#include <filter_funs.h>

object ob1;
object ob2;
object ob3;
object ob4;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("A hallway in the underground lair");
    set_long("You are travelling down a hallway.\n"+
      "This is a grand hallway, built entirely of sturdy, stone blocks. "+
      "Lining the side walls are rows of stands where several torches have "+
      "been placed. Lit passages lead towards the west and east from here.\n");

    add_item(({ "walls", "wall" }),
      "The walls, along with the rest of the passageway are made entirely "+
      "of solid granite blocks, mortared together to provide additional "+
      "support.\n");

    add_item(({ "torches" }),
      "Standard torches, the kind you find in your general store. They have "+
      "been mounted on torch stands which line the side walls of this "+
      "hallway.\n");

    add_item(({ "stands" }),
      "They line the hallway and currently have torches mounted on them.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur7", "west");
    add_exit(CVAN + "lot/ur11", "east");

    clone_object(CVAN + "door/urdoor")->move(TO);
    clone_object(CVAN + "door/urdoor6")->move(TO);

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "lknight2_new");
	ob1->arm_me();
	ob1->move_living("M",TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(NPC + "lknight2_new");
	ob2->arm_me();
	ob2->move_living("M",TO);
    }

    if(!ob3)
    {
	ob3 = clone_object(NPC + "lknight2_new");
	ob3->arm_me();
	ob3->move_living("M",TO);
    }

    if(!ob4)
    {
	ob4 = clone_object(NPC + "lknight2_new");
	ob4->arm_me();
	ob4->move_living("M",TO);
	ob1->team_join(ob2);
	ob1->team_join(ob3);
	ob1->team_join(ob4);
	tell_room(TO, "Several killer knights of Thanar arrive at their guard posts.\n");
    }
}
