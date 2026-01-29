#include "../default.h"
inherit CVAN_ROOM;

object ob1;
object ob2;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_NO_TIME_DESC, 1);

    set_short("Auction Platform");
    set_long("You step up onto the platform, from here you get a commanding "+
      "view of the Slave Market's center. Although you are not that high up "+
      "you are at a level equal to the buildings surrounding the clearing, "+
      "forcing anyone down below to look up at you. There are some manacles "+
      "on the side. Some steps lead back down.\n");

    add_item(({ "buildings" }),
      "There are four buildings visible, all in the cardinal directions. The "+
      "building just north of here looks in slightly better condition than "+
      "the others.\n");

    add_item(({ "north building" }),
      "A unaddorned wooden building. You can't reach it from here though, "+
      "you'll have to go down first.\n");

    add_item(({ "manacles" }),
      "Sturdy iron restraints, they are chained to the platform to prevent "+
      "slaves from escaping during auction times.\n");

    add_exit(CVAN + "slave/s6", "down");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "sover");
	ob1->move_living("M", this_object());
    }

    if(!ob2)
    {
	ob2 = clone_object(NPC + "slave");
	ob2->move_living("M", this_object());
    }
}
