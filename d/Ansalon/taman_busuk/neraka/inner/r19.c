/* Ashlar, 19 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads northeast and southwest, flanked on " +
        "the northwest side by the tall city walls, and on the southeast " +
        "side by a huge arena.");

    add_item_citywalls();
    add_item_street1();
    add_item(({"arena","huge arena","arena of death"}),
        "The huge arena lies to the southeast, built against the city " +
        "wall.\n");

    add_exit(NINNER + "r18", "southwest");
    add_exit(NINNER + "r20", "northeast");
}


