#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_IN;
object chest;

void
reset_dwarf_room()
{
    /*

	if(!objectp(chest))
	{
	    chest = clone_object(EOBJ + "cave_chest");
	    chest->move(TO);
	}
    */
    return;
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");


    add_exit(IRON+ "cave","southeast",0);

    DARK;


    reset_dwarf_room();
}

string
short_descr()
{
    return "A small room within the hill";
}

string
long_descr()
{
    return "You stand in a small room that has been carved " +
    "out of the hill side. Clean and dry, this room is " +
    "designed to be used as a store room.\n";
}
