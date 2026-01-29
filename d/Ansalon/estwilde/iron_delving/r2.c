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

    add_item(({"passage","wind-blown passage"}),
      "This narrow passage looks naturally made from what you " +
      "can tell.\n");
    add_item(({"hills","barren hills","hill","steep hills",
	"steep hill","rocky faces"}),
      "The steep rocky faces of two barren hills rise on either side " +
      "of you, making a natural passage.\n");
    add_item(({"vegetation","plants"}),
      "There is very little vegetation here, but those plants you do " +
      "notice look like they have been trampled frequently by heavy " +
      "booted individuals.\n");

    add_exit(IRON + "r1","northwest",0);
    add_exit(IRON + "r3","northeast",0);

    reset_dwarf_room();
}

string
short_descr()
{
    return "On a wind-blown path between two steep hills";
}

string
long_descr()
{
    return "You are walking along a narrow passage barely two feet across " +
    "between the steep and rocky faces of two barren hills. Little vegetation " +
    "grows here, but those plants that do show signs that this passage " +
    "is often used by heavy booted people.\n";
}
