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
    add_item(({"ancient stone walls","stone walls","walls"}),
      "Ancient walls of stone rise to a low ceiling in this "+
      "cairn.\n");
    add_item(({"ceiling","low ceiling"}),
      "Just above your head is the ceiling of the cairn. It is "+
      "low, typical of dwarven design.\n");
    add_item(({"cairn","ancient dwarven cairn","dwarven cairn",
	"large chamber","chamber"}),
      "You stand within the resting place of a dwarven warrior "+
      "of the Neidar clan.\n");
    add_item(({"floor","dust"}),
      "The floor here is covered with dust. You doubt anyone has "+
      "been here for a long time.\n");
    add_item(({"dwarven markings","markings","floor"}),
      "@@read_markings");
    add_item("passages","Passages lead off to the north, "+
      "south, east and west into the gloom from here.\n");

    DARK;

    add_exit(ROOM + "c3","east",0);
    add_exit(ROOM + "c5","north",0);
    add_exit(ROOM + "c6","south",0);
    add_exit(ROOM + "c7","west",0);

    reset_dwarf_room();
}

string
read_markings()
{
    if(TP->query_race_name() == "dwarf")
    {
	write("The dwarven markings to the west and south "+
	  "indicate there is some danger in those "+
	  "directions.\n");
	say(QCTNAME(TP)+ " examines the dwarven markings "+
	  "expertly.\n");
	return "";
    }
    write("You are unable to make out what the dwarven "+
      "markings mean, but you have a funny feeling that at least one of them " +
      "would mean danger in that direction.\n");
    say(QCTNAME(TP)+ " looks at the dwarven markings uncertainly.\n");
    return "";
}

string
short_descr()
{
    return "a large chamber within an ancient dwarven cairn";
}

string
long_descr()
{
    return "You stand within a large chamber within "+
    "a dwarven cairn. Dust of the ages lies thick "+
    "on the floor here, undisturbed for many years. "+
    "Four passages lead out of this chamber. You notice dwarven markings "+
    "have been carved on the floor before each exit. "+
    "\n";
}
