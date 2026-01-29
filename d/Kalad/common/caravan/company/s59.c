#include "../default.h"
inherit CVAN_ROOM;

object ob1;
object ob2;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Council Chambers");
    set_long("You are inside the council chambers of the Trading Company.\n"+
      "You find yourself inside a massive room. To your south are several "+
      "finely crafted stone benches while just to the southwest is a high "+
      "platform. South from here is a large open space, apparently where "+
      "council members may stand to gain the full attention of anyone in "+
      "the room. High up on the ceiling are several chandeliers, providing "+
      "an even light over the entire room.\n");

    add_item(({ "benches" }), "The benches have been crafted from the purest "+
      "marble and as such, are quite beautiful. Each of the seats has a "+
      "wonderfully plush cushion on it.\n");

    add_item(({ "cushion" }), "It looks very soft and comfortable.\n");

    add_item(({ "platform" }), "A raised dias on the far west of this "+
      "massive room. A stone podium is at the forefront of it.\n");

    add_item(({ "chandeliers" }), "Delicate crystalline chandeliers that "+
      "tinkle ever so slightly, producing a soothing melody.\n");

    add_exit(CVAN + "company/s70", "platform");
    add_exit(CVAN + "company/s58", "south");
    add_exit(CVAN + "company/s60", "east");

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

    if(!ob2)
    {
	ob2 = clone_object(NPC + "tccm");
	ob2->move_living("M", TO);
	ob2->team_join(ob1);
    }
}
