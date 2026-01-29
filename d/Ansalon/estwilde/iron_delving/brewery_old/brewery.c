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


    reset_dwarf_room();
}

string
short_descr()
{
    return "dwarven brewery";
}

string
long_descr()
{
    return "You stand in huge room below ground level at the back " +
    "of a dwarven tavern. Huge wooden barrels stand on solid racks, " +
    "storing various kinds of dwarven ales and spirits. Busy dwarves " +
    "rush past you, focused on their job of making the finest dwarven " +
    "brews in Ansalon!\n";
    "\n";
}
