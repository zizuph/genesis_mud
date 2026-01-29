#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    add_prop(OBJ_I_HAS_FIRE, 1);

    set_short("The Wizard's Workroom");
    set_long("You enter a huge room filled with dozens and dozens of "+
      "books, all carefully stacked in wooden bookshelves. The floor is "+
      "covered with a huge rug. Gazing up at the ceiling you see a sight "+
      "most horrible to behold.\n"+
      "An enormous fire.\n");

    add_item(({ "books" }), "There are dozens, perhaps hundreds of books "+
      "located all over this room, carefully placed inside wooden "+
      "bookshelves. All the books seem to glow ever so slightly.\n");

    add_item(({ "bookshelves" }), "Made out of the redwoods of the Hespyre "+
      "Mountains, they look to be quite sturdy, despite their aged "+
      "appearance.\n");

    add_item(({ "floor" }), "Looking beneath the huge rug, you see the faint "+
      "outline of a small trap door. It looks like you might be able to go "+
      "down through it.\n");

    add_item(({ "rug" }), "A majestic rug that depicts a graceful woodland "+
      "setting, with elves and other forest creatures playing in the "+
      "radiant sunshine.\n");

    add_item(({ "ceiling" }), "A horrific scene has been painted onto the "+
      "flat-rock ceiling. A terrible scene from the forest is shown, in "+
      "which a man dressed in the blackest of robes is setting fire to the "+
      "trees and is viciously killing anything that moves, including forest "+
      "animals, elven men and women, and even their innocent children.\n");

    add_item(({ "fire" }), "A huge blazing fire that reaches almost to the "+
      "ceiling. Strangely enough, there are no embers or other sparks of fire "+
      "flying from it.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur12c", "down");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "tknight");
	ob1->move_living("M", TO);
	tell_room(TO, "The stench of rotting flesh and decay pervades the room.\n");
    }
}

void
init()
{
    ::init();
    write("Searing heat assaults you!\n");
}
