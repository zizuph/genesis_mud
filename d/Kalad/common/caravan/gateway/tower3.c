#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Tower");
    set_long("This is the top of the guard tower, from here you get an "+
      "excellent view of the city of Kabal, which spreads out to the "+
      "southwest of you. Dominating your view to the northeast, east and "+
      "southeast are the dark, towering peaks of the Hespyre mountains, "+
      "which serve to block off Kabal from the rest of Kalad. A wooden "+
      "hatch covers the staircase leading down.\n");

    add_item(({ "city", "kabal" }),
      "The massive city spreads out to the southwest, near the center of "+
      "the city you see a large bell tower.\n");

    add_item(({ "hespyre mountains", "mountains" }),
      "You see a large mountain chain that stretches out of sight far to "+
      "the north and south. You can see extensive forests covering the "+
      "slopes of the mountain chain.\n");

    add_item(({ "wooden hatch", "hatch" }), "It covers the staircase, "+
      "preventing the elements from lashing out at the tower's interior.\n");

    add_exit(CVAN + "gateway/tower2", "down");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "kguard");
	ob1->arm_me();
	ob1->move_living("M",TO);
	tell_room(TO, "The wooden hatch opens and a guardsman of Kabal arrives.\n");
    }
}
