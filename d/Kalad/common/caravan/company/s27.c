#include "../default.h"
inherit CVAN_ROOM;

object ob1;
object ob2;
object ob3;
object ob4;

#define GUARD	(NPC + "tcguard")

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Barracks");
    set_long("You've reached the sleeping area of the guardsmen.\n"+
      "In this part of the barracks you can see many beds set in orderly "+
      "rows. At the base of each of the beds is a small chest. However, "+
      "what really catches your attention are the racks mounted on the "+
      "walls, which are filled with weapons and armour.\n");

    add_item(({ "beds" }), "They look rather uncomfortable, but then again, "+
      "a warriors life isn't easy so the Company guardsmen must be used to "+
      "sleeping on these.\n");

    add_item(({ "chest", "chests" }), "This must be where the guards store "+
      "their personal belongings. They are all locked and shut.\n");

    add_item(({ "racks" }), "Wooden supports holding up various weapons and "+
      "pieces of armor on the walls.\n");

    add_item(({ "weapons" }), "Many kinds are visible, though halberds are "+
      "most common. They are all securely tied to the racks.\n");

    add_item(({ "armour" }), "Suits of bronze platemail hang on the racks, "+
      "you try to get a closer look by taking one down but find they "+
      "are securely tied down.\n");

    add_exit(CVAN + "company/s36", "south");

    reset_room();
}

void
reset_room()
{
    if (!ob1 || !ob2 || !ob3 || !ob4)
    {
	ob1 = clone_object(GUARD);
	ob1->move_living("M", TO);
	ob2 = clone_object(GUARD);
	ob2->move_living("M", TO);
	ob3 = clone_object(GUARD);
	ob3->move_living("M", TO);
	ob4 = clone_object(GUARD);
	ob4->move_living("M", TO);
	ob1->team_join(ob2);
	ob1->team_join(ob3);
	ob1->team_join(ob4);
    }
}
