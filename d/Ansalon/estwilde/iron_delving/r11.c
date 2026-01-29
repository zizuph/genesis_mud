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

    add_item(({"cobbled path","path"}),
      "You stand upon a cobbled path that heads to your " +
      "southeast towards a large hall, as well as branching " +
      "off in just about every other direction " +
      "except northeast and southwest.\n");
    add_item(({"settlement","dwarven settlement","buildings",
	"stone buildings","iron delving"}),
      "You stand in the dwarven settlement of Iron Delving, a " +
      "small community consisting of a number of " +
      "well-crafted stone buildings.\n");
    add_item(({"hills","valley","hill enclosed valley"}),
      "The community of Iron Delving is situated in the " +
      "valley created by two great hills in the middle " +
      "of Estwilde.\n");
    add_item(({"large stone hall","stone hall","hall"}),
      "Down the path to your southeast is a large stone " +
      "hall, the Hall of the Thane of the Neidar Clan.\n");

    add_exit(IRON + "r8","northwest",0);
    add_exit(IRON + "r16","southeast",0);
    add_exit(IRON + "r15","south",0);
    add_exit(IRON + "r13","east",0);
    add_exit(IRON + "r14","west",0);
    add_exit(IRON + "r12","north",0);

    reset_dwarf_room();
}

string
short_descr()
{
    return "A cobbled path in the middle of Iron Delving";
}

string
long_descr()
{
    return "You are standing on a cobbled path in " +
    "the dwarven settlement of Iron Delving, situated " +
    "in a hill-enclosed valley somewhere in the middle " +
    "of the rugged lands of Estwilde. The path " +
    "leads southeast towards a large stone hall, " +
    "while it also branches off to the northeast, " +
    "east, west, north and south.\n";
}
