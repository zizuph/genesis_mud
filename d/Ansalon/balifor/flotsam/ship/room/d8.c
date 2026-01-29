#include "/d/Ansalon/balifor/flotsam/ship/local.h"
#include <stdproperties.h>

#include "/d/Ansalon/common/defs.h"
inherit "/d/Krynn/std/deck";

object p1, p2;

void
reset_deck()
{
    seteuid(getuid(TO));
    if(!objectp(p1))
    {
	p1 = clone_object(FNPC + "pirate2");
	p1->arm_me();
	p1->move(TO);
    }

    if(!objectp(p2))
    {
	p2 = clone_object(FNPC + "pirate4");
	p2->arm_me();
	p2->move(TO);
    }
}

void
create_deck()
{

    set_short("Before some stairs to the upper bow deck");
    set_long("You stand at the fore of the main deck of the " +
      "Golden Lion, before a set of wooden stairs that lead " +
      "up to the upper bow deck, where the ballista of this " +
      "ship is positioned.\n");

    add_item(({"stairs","wooden stairs"}),
      "This set of wooden stairs lead up to the upper bow deck " +
      "of this ship.\n");
    add_item(({"ship","Golden Lion","golden lion"}),
      "You stand upon the main deck of the Golden Lion, a fit " +
      "and trim ship that sails these dangerous seas.\n");
    add_item(({"main deck","deck"}),"You stand upon the main " +
      "deck of the ship. It is somewhat wet from sea water " +
      "splashing over the side of the ship.\n");
    add_item(({"upper bow deck","bow deck","ballista"}),
      "Above you is the upper bow deck, raised above the " +
      "main deck so that the ships lethal ballista can do " +
      "its job without hindrance.\n");

    add_exit("d6","aft",0);
    add_exit("u1","up",0);
    reset_deck();
}

sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship rocks violently to the tune of the turbulent waters.\n";
}

