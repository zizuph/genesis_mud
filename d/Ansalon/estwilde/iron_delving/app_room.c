#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_IN;

void
reset_dwarf_room()
{
    return;
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item("door","A door to the north has been cleverly " +
      "made so that only by pressing on the door in a " +
      "special way may one open it. You would say " +
      "no one short of a dwarf would be able to understand " +
      "the subtle fabrication of such a portal,\n");

    add_exit(IRON + "house","north",0);

    clone_object(EOBJ + "app_board")->move(TO,1);
    reset_dwarf_room();
}

string
short_descr()
{
    return "A small stone room at the back of the house";
}

string
long_descr()
{
    return "You are standing in a small stone room at the " +
    "back of a dwarven house. Here dwarves who have come " +
    "to visit Iron Delving may leave messages to clan " +
    "members, or where clan members may leave messages " +
    "for fellow dwarves. A door leads out to the north.\n";
    "\n";
}
