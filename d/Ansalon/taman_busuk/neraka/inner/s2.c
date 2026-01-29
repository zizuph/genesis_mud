/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("in the Temple Square");
    set_extra_long("You are in the north part of the Temple Square. " +
        "The square stretches east, west and south of here. " +
        "Looking south, you see the " +
        "Temple of Takhisis that rises from the center of the square. " +
        "To the north, an archway leads through the city wall.");

    add_item_citywalls();
    add_item_street1();
    add_item_templesquare();
    add_item("archway","The archway is the entrance to a short tunnel " +
        "through the city wall.\n");
    add_item(({"tunnel","short tunnel"}),
        "The short tunnel leads through the city wall.\n");

    add_exit(NINNER + "g6", "north");
    add_exit(NINNER + "s1", "west");
    add_exit(NINNER + "s3", "east");
    add_exit(NINNER + "s5", "south");
    add_exit(NINNER + "s4", "southwest");
    add_exit(NINNER + "s6", "southeast");

    add_prop(ROOM_I_HIDE, -1);
}


