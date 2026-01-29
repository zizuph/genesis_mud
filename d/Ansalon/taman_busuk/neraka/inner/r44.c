/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads north and southwest, flanked on both " +
        "sides by the tall city walls.");

    add_item_citywalls();
    add_item_street1();

    add_exit(NINNER + "r43", "southwest");
    add_exit(NINNER + "r45", "north");
}


