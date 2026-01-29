/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("in the Temple Square");
    set_extra_long("You are in the northwest part of the Temple Square. " +
        "The square stretches east and north of here. " +
        "Looking south, you see the " +
        "Temple of Takhisis that rises from the center of the square.");

    add_item_citywalls();
    add_item_street1();
    add_item_templesquare();

    add_exit(NINNER + "s5", "east");
    add_exit(NINNER + "s1", "north");
    add_exit(NINNER + "s2", "northeast");
    add_exit(NINNER + "s7", "southwest");

    add_prop(ROOM_I_HIDE, -1);
}


