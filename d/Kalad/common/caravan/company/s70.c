#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Council chamber platform");
    set_long("You are on top of the platform within the council chambers. "+
      "From here you have a commanding view of the entire chamber, which is "+
      "so huge that you cannot see the far end, which lies to the east. A "+
      "large stone podium is here, where someone could speak and possibly "+
      "be heard throughout the chamber. Stone steps lead down to the "+
      "northeast and southeast.\n");

    add_item(({ "podium" }), "It has been crafted out of solid marble and "+
      "has been shaped into a half-circle facing away from the rest of the "+
      "council chambers.\n");

    add_exit(CVAN + "company/s59", "northeast");
    add_exit(CVAN + "company/s58", "southeast");

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(NPC + "tccms");
	ob1->move_living("M", TO);
    }
}

void
init()
{
    ::init();
    write("You climb up to the dais.\n");
}
