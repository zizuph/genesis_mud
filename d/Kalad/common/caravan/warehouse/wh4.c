#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_hear_bell(1);

    set_short("Inside a Warehouse");
    set_long("You find yourself in a great enclosed space, the interior "+
      "of one of the huge warehouses lining Warehouse Lane. This must be "+
      "where the merchants and traders of the city store their trading "+
      "goods. In nearly every direction you turn are piles upon "+
      "piles of large wooden crates. Several small windows high up the walls "+
      "provide a dim light for the interior.\n");

    add_item(({ "piles", "pile", "large wooden crates", "large crates", "wooden crates", "crates", "crate" }),
      "Many of the crates are five, even six feet across. The majority "+
      "however are only three feet wide. You notice all of the crates here "+
      "are marked with the same symbol.\n");

    add_item(({ "symbol" }), "An image of a gauntleted fist surrounded in "+
      "flame is marked on all the crates.\n");

    add_item(({ "small windows", "small window", "windows", "window" }), "They "+
      "are strategically placed high up the walls to discourage any would be "+
      "thieves from using them to gain access to the building.\n");

    add_item(({ "walls", "wall" }), "Plain and unaddorned, their only function is to hold the building up "+
      "and to prevent the elements from damaging the goods stored here.\n");

    add_exit(CVAN + "warehouse/yard4", "north");
}
