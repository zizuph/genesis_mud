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
      "You stand on a cobbled path that runs to the northeast and " +
      "east, as well as leading south to the local post office.\n");
    add_item(({"community","iron delving","dwarven community"}),
      "You stand in the dwarven community of Iron Delving, the home " +
      "of the hill dwarves of Estwilde.\n");
    add_item(({"small building","post office"}),
      "To your south is a small stone building that is used " +
      "as the local post office. Here, pigeons are sent to " +
      "other offices around the realms.\n");

    add_exit("/d/Ansalon/guild/neidar/rooms/post","south",0);
    add_exit(IRON + "forge","southwest",0);
    add_exit(IRON + "r14","east",0);
    add_exit(IRON + "r8","northeast",0);
    add_exit("/d/Ansalon/guild/shieldbearers/joinroom2", "west", 0);
    
    add_cmd_item(({"water","stream","from stream"}),"drink","@@drink_water");

    reset_dwarf_room();
}

string
short_descr()
{
    return "On a cobbled path before a small stone post office";
}

string
long_descr()
{
    return "You stand on a cobbled path at the edge " +
    "of the dwarven community of Iron Delving. To your south " +
    "is a small building of stone, the local post office, " +
    "where the sound of pigeons can be heard coming from. " +
    "There is a small clearing west from here.\n";
}
