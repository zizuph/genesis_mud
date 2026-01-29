#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_hear_bell(1);

    set_short("Inside a Warehouse");
    set_long("It probably isn't a good idea for you to be in here. The "+
      "merchants and traders, whose goods are stored here would certainly "+
      "not hesitate in lynching you if they discovered you were here. All "+
      "around you are piles upon "+
      "piles of large wooden crates. Several small windows high up the walls "+
      "provide a dim light for the interior.\n");

    add_item(({ "piles", "pile", "large wooden crates", "large crates", "wooden crates", "crates", "crate" }),
      "Many of the crates are five, even six feet across. The majority "+
      "however are only three feet wide. You notice all of the crates here "+
      "are marked with the same symbol.\n");

    add_item(({ "symbol" }), "An image of a purple dragon on a white field is "+
      "marked on all the crates.\n");

    add_item(({ "small windows", "small window", "windows", "window" }), "They "+
      "are strategically placed high up the walls to discourage any would be "+
      "thieves from using them to gain access to the building.\n");

    add_item(({ "walls", "wall" }), "Plain and unaddorned, their only function is to hold the building up "+
      "and to prevent the elements from damaging the goods stored here.\n");

    add_exit(CVAN + "warehouse/yard2", "north");
}
