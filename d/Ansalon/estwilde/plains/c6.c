#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <money.h>

inherit DWARF_IN;

object chest, potion, potion2, golem, money;

void
reset_dwarf_room()
{
    if(!objectp(golem))
    {
	golem = clone_object(LIVING + "stone_guardian");
	golem->move(TO);
    }

    if(!objectp(chest))
    {
	chest = clone_object(EOBJ + "cave_chest");
	chest->move(TO);
	potion = clone_object(EOBJ + "dwarf_potion");
	potion->move(chest, 1);
	potion2 = clone_object(EOBJ + "dwarf_potion");
	potion2->move(chest, 1);
	money = MONEY_MAKE_GC(100);
	money->move(chest, 1);
    }
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");
    add_item(({"ancient stone walls","stone walls","walls"}),
      "Ancient walls of stone rise to a low ceiling in this "+
      "cairn.\n");
    add_item(({"passageway","dead end"}),
      "You stand at the end of a passageway within a " +
      "dwarven cairn.\n");
    add_item(({"ceiling","low ceiling"}),
      "Just above your head is the ceiling of the cairn. It is "+
      "low, typical of dwarven design.\n");
    add_item(({"cairn","ancient dwarven cairn","dwarven cairn"}),
      "You stand within the resting place of a dwarven warrior "+
      "of the Neidar clan.\n");
    add_item(({"floor","dust"}),
      "The floor here is covered with dust. You doubt anyone has "+
      "been here for a long time.\n");

    DARK;

    add_exit(ROOM + "c4","north","@@go_north");

    reset_dwarf_room();
}

int
go_north()
{
    if(objectp(golem) && E(golem) == TO &&
      CAN_SEE(golem, TP))
    {
	write("The stone guardian won't let you pass.\n");
	return 1;
    }
    return 0;
}

string
short_descr()
{
    return "a dead end in an ancient dwarven cairn";
}

string
long_descr()
{
    return "You stand at the end of a passageway within " +
    "the ancient stone walls " +
    "of a dwarven cairn. Dust of the ages lies thick "+
    "on the floor here, undisturbed for many years. "+
    "\n";
}
