/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way, at the Temple Square");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads south, while to the northwest it " +
        "opens up to the Temple Square.");

    add_item_citywalls();
    add_item_street1();
    add_item(({"square","temple square"}),"You cannot see much of it from " +
        "this vantage point.\n");

    add_exit(NINNER + "r47", "south");
    add_exit(NINNER + "s3", "northwest");
}


