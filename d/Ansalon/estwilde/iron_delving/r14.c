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
      "A cobbled path leads off to the east and west, while to " +
      "the south it leads to the local store of Iron Delving.\n");
    add_item(({"local store","store","shop"}),
      "To your south stands a rather long building made " +
      "of stone. It is here where equipment and odds and " +
      "ends are sold and bought.\n");
    add_item("iron delving",
      "You stand in the dwarven community of Iron Delving, the " +
      "home of the hill dwarves of Estwilde.\n");

    add_exit(IRON + "shop","south",0);
    add_exit(IRON + "r11","east",0);
    add_exit(IRON + "r10","west",0);

    reset_dwarf_room();
}

string
short_descr()
{
    return "On a cobbled path before a shop in Iron Delving";
}

string
long_descr()
{
    return "You stand on a cobbled path before the " +
    "local store of Iron Delving, a shop that sells those " +
    "things needed to survive these harsh lands. The cobbled " +
    "path continues to the east and west.\n";
}
