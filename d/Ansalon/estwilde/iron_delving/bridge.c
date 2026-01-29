#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_OUT;

#include "river_drink.h"

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

object d1;

void
reset_dwarf_room()
{
    if(!objectp(d1))
    {
	d1 = clone_object(LIVING + "dwarf_guard02");
	d1->arm_me();
	d1->move(TO);
    }
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"sturdy bridge","wood","bridge"}),
      "You are standing on a sturdy bridge made of " +
      "wood by dwarven craftsmen. You doubt this thing " +
      "would break under anything less than a giant, " +
      "and a heavy one at that.\n");
    add_item(({"stream","bubbling stream"}),
      "A bubbling stream flows under the bridge.\n");
    add_item(({"dwarven community","community","buildings",
	"stone buildings"}),
      "To your southeast are a number of stone buildings " +
      "that make up the dwarven community of Iron Delving.\n");

    add_exit(IRON + "r7","northwest",0);
    add_exit(IRON + "r8","southeast",0);

    add_prop(LIVE_I_CAN_FISH, "freshwater");

    add_cmd_item(({"stream","from stream","water"}),"drink","@@drink_water");

    reset_dwarf_room();
}

string
short_descr()
{
    return "a sturdy bridge over a bubbling stream";
}

string
long_descr()
{
    return "You stand upon a sturdy bridge of wood that runs " +
    "over a bubbling stream. To your southeast the " +
    "bridge ends, and a small dwarven community " +
    "begins.\n";
}
