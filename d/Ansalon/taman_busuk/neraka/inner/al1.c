/* Ashlar, 6 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("in a small alley");
    set_extra_long("You are standing in a small alley. To the west, " +
        "the city wall rises high above. The alley leads east out " +
        "to the street, and to the south is what looks like a warehouse.");

    add_item_citywalls();
    add_item_street1();
    add_item("alley","The alley is filled with dirt and litter, and " +
        "more, judging by the smell.\n");
    add_item(({"dirt","litter"}),"You don't want to mess with that mess.\n");
    add_item("warehouse","The warehouse is large and made of wood. Above " +
        "the door is painted in crude letters, 'Private, keep out'.\n");
    add_item("door","The door leads south into the warehouse.\n");

    add_exit(NINNER + "r9", "east");
    add_exit(NINNER + "ware1", "south");
}


