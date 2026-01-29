/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("in the Temple Square");
    set_extra_long("You are in the north part of the Temple Square. " +
        "The square stretches west and south of here, while a street " +
        "leads off to the southeast. Looking south, you see the " +
        "Temple of Takhisis that rises from the center of the square.");

    add_item_citywalls();
    add_item_street1();
    add_item_templesquare();

    add_exit(NINNER + "r48", "southeast");
    add_exit(NINNER + "s2", "west");
    add_exit(NINNER + "s6", "south");
    add_exit(NINNER + "s5", "southwest");

    add_prop(ROOM_I_HIDE, -1);
}


