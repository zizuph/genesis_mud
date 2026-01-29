#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_IN;
object dwarf, cabinet, chest, rack;

void
reset_dwarf_room()
{
    if(!objectp(cabinet))
    {
	cabinet = clone_object(EOBJ + "cabinet");
	cabinet->move(TO);
    }
    if(!objectp(chest))
    {
	chest = clone_object(EOBJ + "armour_chest");
	chest->move(TO);
    }
    if(!objectp(rack))
    {
	rack = clone_object(EOBJ + "weapon_rack");
	rack->move(TO);
    }

    /*
	if(!objectp(dwarf))
	{
	    dwarf = clone_object(LIVING + "sorter");
	    dwarf->move(TO);
	}
    */
    return;
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"plain room","room","store room"}),
      "@@long_descr");

    add_exit(IRON + "board","south",0);

    reset_dwarf_room();
}

string
short_descr()
{
    return "Storeroom in the Hall of Warriors";
}

string
long_descr()
{
    return "This small, plain room is the store room " +
    "for the clan warriors equipment. An exit leads " +
    "out of here to the south.\n";
}
