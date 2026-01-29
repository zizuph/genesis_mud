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

    set_short("Inside the red house");
    set_long("You enter the red house.\n"+
      "You find yourself in a small room with little in the way of "+
      "furnishings. Some red drapes frame the windows while the floor is "+
      "covered by a red carpet. There is a small bed in the corner.\n");

    add_item(({ "drapes" }), "They are the same brick color as the outside "+
      "of this building.\n");

    add_item(({ "windows" }), "You can see out into the street through them.\n");

    add_item(({ "floor" }), "Its a bit cluttered with several items, there "+
      "is a pile of rags in the corner.\n");

    add_item(({ "carpet" }), "A cheap carpet, probably bought from some "+
      "travelling merchant. It is an unusually dark red in color.\n");

    add_item(({ "bed" }), "A small, yet cosy-looking bed. It doesn't look "+
      "like anyone has slept in there for awhile.\n");

    add_exit(CVAN + "wayfar/s1", "out");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(OBJ + "chair");
	ob1->move(TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(OBJ + "lbag");
	ob2->move(TO);
	ob2->add_prop(OBJ_I_HIDE, 30);
    }
}
