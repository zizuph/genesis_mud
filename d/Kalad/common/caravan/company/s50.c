#include "../default.h"
inherit CVAN_ROOM;

#define GUARD	(NPC + "tcguard")

object ob1;
object ob2;
object ob3;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Trading room");
    set_long("You've entered a spacious room.\n"+
      "This room is furnished with a large circular table with several "+
      "chairs surrounding it. There is also a large rug covering the floor. "+
      "Gazing at the walls you see several posters posted upon them.\n");

    add_item(({ "table" }), "A wooden table with a diameter of some eight "+
      "feet. A deck of cards is lying on top of it.\n");

    add_item(({ "deck", "cards" }), "An ordinary set of playing cards, probably "+
      "used by the guards to pass the time.\n");

    add_item(({ "chairs" }), "What the guards sit on, of course.\n");

    add_item(({ "rug" }), "A huge rug that nearly covers all of this room's "+
      "floor. It is decorated with a strange weaving pattern that you "+
      "cannot recognize.\n");

    add_item(({ "walls" }), "Just bare stone, a few posters are hanging upon "+
      "them.\n");

    add_item(({ "posters" }), "They all portray individuals wanted by the "+
      "Trading Company for some offense committed against them, whether "+
      "imaginary or not. You clearly see the print at the bottom which says "+
      "that all such individuals are to be slain.\n");

    clone_object(CVAN + "door/tcdoor1")->move(TO);

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "tctrader");
	ob1->move_living("M",TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(GUARD);
	ob2->move_living("M",TO);
    }

    if(!ob3)
    {
	ob3 = clone_object(GUARD);
	ob3->move_living("M",TO);
	ob1->team_join(ob2);
	ob1->team_join(ob3);
    }
}
