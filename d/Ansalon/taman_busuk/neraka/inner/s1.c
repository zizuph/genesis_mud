/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("in the Temple Square");
    set_extra_long("You are in the northwest part of the Temple Square. " +
        "The square stretches east and south of here. " +
        "Looking south, you see the " +
        "Temple of Takhisis that rises from the center of the square.");

    add_item_citywalls();
    add_item_street1();
    add_item_templesquare();

    add_exit(NINNER + "s2", "east");
    add_exit(NINNER + "s4", "south");
    add_exit(NINNER + "s5", "southeast");

    add_prop(ROOM_I_HIDE, -1);
}


