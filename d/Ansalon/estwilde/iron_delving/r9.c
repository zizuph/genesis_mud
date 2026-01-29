#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_OUT;

#include "river_drink.h"

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
      "A cobbled path, crafted by dwarven hands, runs beside " +
      "a bubbling stream.\n");
    add_item(({"bubbling stream","stream"}),
      "A bubbling stream runs from a great rent in the hillside " +
      "to your northeast, running past you to your southwest.\n");
    add_item(({"rent","great rent","hillside","hill-face",
	"steep hill-face"}),
      "To your northeast rises the steep side of one of the " +
      "hills of this valley. A great rent has been torn in its " +
      "side, reminding you of a nasty wound. Out of the rent " +
      "pours a bubbling stream, running past you to the southwest.\n");
    add_item(({"community","iron delving"}),
      "Iron Delving, the dwarven community you now stand in.\n");
    add_item(({"small clearing","clearing"}),
      "A small clearing just below the steep hill-face is to your " +
      "northeast.\n");

    add_exit("/d/Ansalon/guild/neidar/rooms/train","northeast",0);
    add_exit(IRON + "r12","south",0);
    add_exit(IRON + "r8","southwest",0);

    add_cmd_item(({"stream","from stream","water"}),"drink","@@drink_water");

    reset_dwarf_room();
}

string
short_descr()
{
    return "On a cobbled path on the bank of a bubbling stream";
}

string
long_descr()
{
    return "You are standing on a cobbled path that runs beside a " +
    "bubbling stream in the dwarven community of Iron " +
    "Delving. The cobbled path bends here to the south, " +
    "while also travelling to the southwest. To your northeast " +
    "is a small clearing before a steep hill-face.\n";
}
