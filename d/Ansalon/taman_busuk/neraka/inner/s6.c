/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("in the Temple Square");
    set_extra_long("You are in the northeast part of the Temple Square. " +
        "The square stretches west and north of here and brances off " +
        "to the southeast. " +
        "Looking south, you see the " +
        "Temple of Takhisis that rises from the center of the square.");

    add_item_citywalls();
    add_item_street1();
    add_item_templesquare();

    add_exit(NINNER + "s5", "west");
    add_exit(NINNER + "s3", "north");
    add_exit(NINNER + "s2", "northwest");
    add_exit(NINNER + "s27", "southeast");

    add_prop(ROOM_I_HIDE, -1);
}


