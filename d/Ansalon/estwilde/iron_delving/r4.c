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

    add_item(({"large valley","large hills","hills"}),
      "You stand in a large valley that is well sheltered " +
      "and protected by two steep hills.\n");
    add_item("grass",
      "The grass that grows here, while still somewhat brown, " +
      "is quite a lot lusher than that grass that grows out on " +
      "the plains of Estwilde.\n");

    add_exit(IRON + "r3","west",0);
    add_exit(IRON + "r5","northeast",0);
    add_exit(IRON + "r6","southeast",0);
    add_exit(IRON + "r7","east",0);

    reset_dwarf_room();
}

string
short_descr()
{
    return "A hill-enclosed valley";
}

string
long_descr()
{
    return "You stand in a large valley between two large hills. " +
    "The ground here is covered with short browny-green grass, " +
    "and slopes down to the southeast. The sound of a bubbling " +
    "stream comes from the southeast. A passage through " +
    "the hills is to your west." +
    "\n";
}
