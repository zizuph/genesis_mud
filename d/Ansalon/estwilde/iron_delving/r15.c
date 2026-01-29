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
      "You stand on a cobbled path before a small stone house.\n");
    add_item(({"town","iron delving","community"}),
      "Iron Delving, the dwarven community where many " +
      "of the hill dwarves of Estwilde reside.\n");
    add_item(({"small stone building","stone building",
	"building","roof","thatched roof","house",
	"stone house","small stone house"}),
      "To your southwest rises a small stone house " +
      "with a thatched roof. It looks well-maintained.\n");

    add_exit(IRON + "house","southwest",0);
    add_exit(IRON + "r11","north",0);

    reset_dwarf_room();
}

int
closed()
{
    write("The door to the house is closed at the moment. Come back later.\n");
    return 1;
}

string
short_descr()
{
    return "On a cobbled path before a small stone house";
}

string
long_descr()
{
    return "You stand on a cobbled path in the " +
    "dwarven community of Iron Delving. " +
    "To your southwest stands a small stone house with " +
    "a thatched roof, while the path continues back to " +
    "the middle of the town to your north.\n";
}
