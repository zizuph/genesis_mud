/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("in the Temple Square");
    set_extra_long("You are in the east part of the Temple Square. " +
        "The square stretches southwest and north of here. " +
        "Looking west, you see the " +
        "Temple of Takhisis that rises from the center of the square.");

    add_item_citywalls();
    add_item_street1();
    add_item_templesquare();

    add_exit(NINNER + "s20", "southwest");
    add_exit(NINNER + "s22", "north");

    add_prop(ROOM_I_HIDE, -1);
}


