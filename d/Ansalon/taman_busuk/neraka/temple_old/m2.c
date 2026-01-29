/* Ashlar, 21 Oct 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit TEMPLE_BASE;

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "You stand at the base of a large staircase leading down to " +
    "the south. The steps of the staircase are made of black marble, " +
    "and well polished.\n";
}

void
create_neraka_room()
{
    set_short("base of a staircase leading down");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"base","staircase"}),
    "The staircase leads down to the south. The steps are made of black " +
    "marble which is well polished, and the railings are carved with " +
    "ornamental figures.\n");

    add_item(({"steps","marble","black marble"}),
    "The steps are made of fine black marble, and are well polished. " +
    "You guess they are quite slick.\n");

    add_item("railings","The railings at the sides of the staircase " +
    "are carved with ornamental figures.\n");

    add_item(({"figures","ornaments","ornamental figures"}),
    "The ornamental figures are of many different kinds, none easily " +
    "recognisable.\n");

    reset_room();

    add_exit(NTEMPLE + "m1", "east");
    add_exit(NTEMPLE + "m4", "west");
    add_exit(NTEMPLE + "d7", "down");
    add_exit(NTEMPLE + "d7", "south", 0, 1, 1);
}


