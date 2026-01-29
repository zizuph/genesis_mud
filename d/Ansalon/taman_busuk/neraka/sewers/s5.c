/* Ashlar, 21 Aug 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit SEWER_BASE;

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "This is a tunnel in the sewers beneath Neraka. " +
    "The tunnel is wide enough for four men to walk abreast, and it " +
    "is just as high. " + water_desc() + "The tunnel leads east and " +
    "west, though to the west part of the ceiling has collapsed and " +
    "a large mound of rubble blocks the way. There is an opening in " +
    "the north wall.\n";
}

void
create_neraka_room()
{
    set_short("in the sewers");
    set_long("@@long_descr");

    add_lsewer_items();
    add_item(({"mound","rubble","large mound","mound of rubble"}),
    "The mound of rubble completely blocks the tunnel to the west, " +
    "nothing larger than a rat could pass, if even that.\n");
    add_item("north wall","There is an opening in the north wall.\n");
    add_item("opening","It leads north and downwards. It is not large, " +
    "but you think you could fit through it.\n");

    add_cmd_item("opening","enter","@@enter_opening");

    add_lsewer_herbs();
    remove_prop(ROOM_I_LIGHT);

    reset_room();

    add_exit(NSEWER + "s6", "east");
    add_exit(NSEWER + "c7", "north", "@@go_north", 0);
}

int
go_north()
{
    write("You enter the opening and promptly slide down a slick " +
    "shaft into a crypt below.\n");
    return 0;
}

string
enter_opening()
{
    TP->command("$north");
    return "";
}
