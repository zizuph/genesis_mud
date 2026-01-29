/* Ashlar, 21 Aug 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit SEWER_BASE;

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "This is a tunnel in the sewers beneath Neraka. " +
    "The tunnel is wide enough for four men to walk abreast, and it " +
    "is just as high. " + water_desc() + "The tunnel leads southeast, " +
    "while to the northeast it ends in a wall where a spillway " +
    "chute is emptying a trickle of water into the tunnel.\n";
}

void
create_neraka_room()
{
    set_short("in the sewers");
    set_long("@@long_descr");

    add_lsewer_items();
    add_item(({"chute","spillway","spillway chute"}),
    "The chute slants strongly upwards, and a trickle of water runs " +
    "through it, emptying out in the tunnel.\n");
    add_item(({"trickle","trickle of water"}),
    "It is just a small trickle, but it seems marginally less dirty " +
    "than the water that is already collected at the bottom of the " +
    "tunnel.\n");
    add_cmd_item(({"chute","spillway","spillway chute","through chute",
    "through spillway","through spillway chute"}),
    ({"enter","crawl","climb"}),
    ({"@@too_small","@@too_small","@@too_small"}));

    add_lsewer_herbs();
    remove_prop(ROOM_I_LIGHT);

    reset_room();

    add_exit(NSEWER + "s2", "southeast");
}

string
too_small()
{
    return "The spillway chute is far too tight for you to fit in there.\n";
}
