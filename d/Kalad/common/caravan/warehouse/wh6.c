#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_hear_bell(1);

    set_short("Inside a Warehouse");
    set_long("You are within a huge enclosed space, were it not for the "+
      "ceiling above, you might be fooled into believing that you are within "+
      "a gigantic box instead of a massive building, so great is the volume "+
      "of this structure. In every direction but up are a seemingly infinite "+
      "number of large wooden crates. Several small windows high up the walls "+
      "provide a dim light for the interior.\n");

    add_item(({ "large wooden crates", "large crates", "wooden crates", "crates", "crate" }),
      "Many of the crates are five, even six feet across. The majority "+
      "however are only three feet wide. You notice all of the crates here "+
      "are marked with the same symbol.\n");

    add_item(({ "symbol" }), "A naked skull writhed in purplish flames is "+
      "emblazoned upon every one of the crates.\n");

    add_item(({ "small windows", "small window", "windows", "window" }), "They "+
      "are strategically placed high up the walls to discourage any would be "+
      "thieves from using them to gain access to the building.\n");

    add_item(({ "walls", "wall" }), "Plain and unaddorned, their only function is to hold the building up "+
      "and to prevent the elements from damaging the goods stored here.\n");

    add_item(({ "ceiling" }), "Craning your neck back, you peer up above and "+
      "think you see a small skylight in the ceiling.\n");

    add_item(({ "skylight" }), "It is a small, glass window that gives you "+
      "a tiny view of the sky.\n");

    add_item(({ "sky" }), "It lies above.\n");

    add_exit(CVAN + "warehouse/yard6", "north");
}
