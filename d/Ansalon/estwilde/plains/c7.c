#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_IN;

#define GEM_DIR "/d/Genesis/gems/obj/"

object chest, shield, golem, diamond, peridot,
peridot2, peridot3, agate;

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
	shield = clone_object(EOBJ + "/armour/teregul_shield");
	shield->move(chest, 1);
	diamond = clone_object(GEM_DIR + "diamond");
	diamond->move(chest, 1);
	peridot = clone_object(GEM_DIR + "peridot");
	peridot2 = clone_object(GEM_DIR + "peridot");
	peridot3 = clone_object(GEM_DIR + "peridot");
	peridot->move(chest, 1);
	peridot2->move(chest, 1);
	peridot3->move(chest, 1);
	agate = clone_object(GEM_DIR + "agate");
	agate->move(chest, 1);
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

    add_exit(ROOM + "c4","east","@@go_east");

    reset_dwarf_room();
}

int
go_east()
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
