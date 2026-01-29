#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Inside the black house");
    set_long("You are inside the black house.\n"+
      "The interior of this building seems to match the outside quite well. "+
      "The walls, floor, ceiling and bed are all a dark black in color. "+
      "Whoever lives in here must have a strange taste for decor to have "+
      "made everything black.\n");

    add_item(({ "walls" }), "The walls have been painted black.\n");

    add_item(({ "floor" }), "The ground is covered with a black and "+
      "featureless carpet.\n");

    add_item(({ "ceiling" }), "It has also been painted black.\n");

    add_item(({ "bed" }), "A comfortable looking bed. Somehow it looks "+
      "rather sinister, being draped in such dark colors.\n");

    add_exit(CVAN + "wayfar/s1", "out");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(OBJ + "backpack");
	ob1->move(TO);
	ob1->add_prop(OBJ_I_HIDE, 40);
    }
}
