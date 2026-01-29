#include "../default.h"
inherit CVAN_ROOM;

void reset_room();

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_hear_bell(1);

    set_short("Captain's Office");
    set_long("This spartan and almost completely unaddorned room is the "+
      "office of the city guard captain for the Caravan district. A large "+
      "redwood desk lies on the opposite side of the room. Besides the desk "+
      "the only other ornamentation in the room is a pair of steel longswords "+
      "mounted on the side wall. The only light-source comes from a pair of "+
      "lanterns mounted on the walls aside the desk.\n");

    add_item(({ "redwood desk", "desk" }),
      "It's a solid looking desk made from the hardy redwoods of the Hespyre "+
      "mountains. There are a few scraps of parchment scattered on the desk.\n");

    add_item(({ "steel longswords", "longswords" }),
      "Examining the pair closer you marvel at the fine craftsmanship of "+
      "the two weapons, clearly these belong to a great warrior.\n");

    add_item(({ "lanterns" }),
      "Small bronze lanterns that spread wan light across the room.\n");

    clone_object(CVAN + "door/idoor1")->move(TO);

    reset_room();
}

void
reset_room()
{
    object hahmal;
    if(!present("hahmal",TO))
    {
	seteuid(getuid(TO));
	hahmal = clone_object(NPC + "kcaptain");
	hahmal->arm_me();
	hahmal->move(this_object());
    }
}
