#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_OUT;

void
reset_dwarf_room()
{
    return;
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"cobbled path","path"}),
      "A cobbled path, crafted with the skill and care found " +
      "in all dwarven craftsmen.\n");
    add_item(({"tavern","dwarven tavern","stone building","building"}),
      "Rising to your east is a stone building, the tavern " +
      "of Iron Delving. Being the only tavern in this small " +
      "community, it is not named, and is simply referred " +
      "to be the locals as 'The Tavern'.\n");
    add_item(({"iron delving","community"}),
      "You stand in the dwarven community of Iron Delving, " +
      "home to the Hill Dwarves of Estwilde.\n");

    add_exit(IRON + "tavern","east",0);
    add_exit(IRON + "r9","north",0);
    add_exit(IRON + "r11","south",0);

    reset_dwarf_room();
}

string
short_descr()
{
    return "Before a dwarven tavern in Iron Delving";
}

string
long_descr()
{
    return "You are standing before a dwarven tavern that " +
    "rises to the east of a cobbled path in the middle of the community " +
    "of Iron Delving. The cobbled path continues to your " +
    "north and south.\n";
}
