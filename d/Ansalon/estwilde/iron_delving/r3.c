#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/guild/dwarf/guild.h"

inherit DWARF_OUT;
object d1, d2;

void
reset_dwarf_room()
{
    if(!objectp(d1))
    {
	d1 = clone_object(LIVING + "dwarf_guard");
	d1->arm_me();
	d1->move(TO);
    }
    if(!objectp(d2))
    {
	d2 = clone_object(LIVING + "dwarf_guard02");
	d2->arm_me();
	d2->move(TO);
    }
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

    add_exit(IRON + "r2","southwest",0);
    add_exit(IRON + "r4","east","@@go_east");

    reset_dwarf_room();
}

int
go_east()
{
    if(objectp(d1) || objectp(d2))
    {

	if(TP->query_race_name() == "goblin" ||
           TP->query_race_name() == "minotaur" ||
           TP->query_race_name() == "ogre" ||
           TP->query_prop(DWARF_ENEMY))
	{
	    if(!CAN_SEE(d1, TP) && !CAN_SEE(d2, TP))
	    {
	       write("While the guards can't see you, you find the pass too narrow " +
                     "to sneak past without alerting them.\n");
	       return 1;
	    }

	    write("The dwarf guards stop you from going east.\n");
	    return 1;
	}

	if(BANISHED(TP))
	{
	    if(!CAN_SEE(d1, TP) && !CAN_SEE(d2, TP))
	    {
	       write("While the guards can't see you, you find the pass too narrow " +
                     "to sneak past without alerting them.\n");
	       return 1;
	    }

	    d1->command("spit");
	    d2->command("say You ain't going that way chum!");
	    return 1;
	}
	return 0;
    }
    return 0;
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
