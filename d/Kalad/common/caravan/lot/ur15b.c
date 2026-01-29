#include "../default.h"
inherit CVAN_ROOM;

object ob1;
object ob2;
object ob3;
object ob4;
object ob5;
object ob6;

#define HOBBIT	(NPC + "tkhslave")
#define GNOME	(NPC + "tkgslave")
#define ELF	(NPC + "tkeslave")

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    add_prop(ROOM_I_LIGHT, 0);

    set_short("Slave Pen");
    set_long("This damp and dismal room is littered with feces. From the "+
      "shackles on the walls this place must be some sort of slave pen, where "+
      "prisoners are kept by the evil Knights of Thanar. A dim light can be "+
      "seen to the west.\n");

    add_item(({ "feces" }), "The solid waste of human beings. It is littered "+
      "all across the ground.\n");

    add_item(({ "shackles" }), "Tight-fitting metal bands used to hold the "+
      "slaves to the wall. They look a bit rusty.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur15", "west");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(HOBBIT);
	ob1->move_living("M",TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(HOBBIT);
	ob2->move_living("M",TO);
    }

    if(!ob3)
    {
	ob3 = clone_object(GNOME);
	ob3->move_living("M",TO);
    }

    if(!ob4)
    {
	ob4 = clone_object(GNOME);
	ob4->move_living("M",TO);
    }

    if(!ob5)
    {
	ob5 = clone_object(ELF);
	ob5->move_living("M",TO);
    }

    if(!ob6)
    {
	ob6 = clone_object(ELF);
	ob6->move_living("M",TO);
	tell_room(TO, "A pitiful moan attracts your attention to a group of "+
	  "slaves in the corner.\n");
    }
}
