#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_IN;
object chest, d1;

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
    if(!objectp(d1))
    {
	d1 = clone_object(LIVING + "dwarf_guard");
	d1->arm_me();
	d1->move(TO);
    }
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item("opening",
      "An opening to the southeast leads out of this room.\n");
    add_item("passageway",
      "A passageway leads away to the northwest.\n");

    add_exit(IRON + "cave2","northwest","@@enter_store");
    add_exit(IRON + "r5","out",0);



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
    "out of the hill side. To the northwest a passageway " +
    "continues further into the hill, while to the southeast " +
    "an opening leads outside.\n";
}

int
enter_store()
{
    if(objectp(d1))
    {
	if(!P("ansalon_rune_object",TP)
	  && !TP->query_guild_member("Dwarven Warriors of the Neidar Clan"))
	{
	    write("You are stopped by the dwarven guard.\n");
	    say(QCTNAME(TP) + " is stopped from going northwest " +
	      "by the dwarven guard.\n");
	    return 1;
	}
	d1->command("nod respect " +TP->query_real_name());
	return 0;
    }
    return 0;
}
