#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <stdproperties.h>

inherit SANCTION_OUT;

void
create_sanction_room()
{
    set_short("Central pier in the harbour of Sanction");
    set_extra_long("These solidly built piers have been shattered " +
      "by the violent tremors from the erupting volcanoes. The " +
      "piers stretch northwest and southwest from here. To the " +
      "south stands a warehouse, and a pair of gates lead " +
      "east into Sanction proper. A sign hangs on the wall of " +
      "the warehouse.");

    add_item(({"gates","pair of gates","gate"}),
      "The pair of gates leading into Sanction are "+
      "presently standing open.\n");

    add_cmd_item("gates","close","The gates are secured in "+
      "place and cannot be closed.\n");

    add_item("warehouse",
      "The warehouse to the south is made of stone like most " +
      "warehouses here. A sign hangs on the wall of the warehouse.\n");
    add_item("wall","The wall has a sign upon it.\n");

    add_item("sign","@@read_sign");
    add_cmd_item("sign","read","@@read_sign");

    add_harbour_items();
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_exit(SCITY + "street1", "east", "@@no_go");
    add_exit(SCITY + "warehouse02", "south");
    add_exit(SCITY + "pier06", "southwest");
    add_exit(SCITY + "pier03", "northwest");
}

int
no_go()
{
    write("\nYou pass through the gates and into Sanction city.\n\n");
    return 0;
}

string
read_sign()
{
    return "The sign reads: Neraka-Sanction Trading Line. Goods " +
    "transported for minimal fees.\n";
}
