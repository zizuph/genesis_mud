/* Ashlar, 21 Oct 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit INNER_OUT;

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "You are standing on a large balcony on the upper level " +
    "of the temple. To the south, a doorway leads into the temple. " +
    "From this vantage point you have a good view of the north part " +
    "of the city. Directly below you is the Temple Square and " +
    "the entrance to the temple.\n";
}

void
create_neraka_room()
{
    set_short("on a balcony");
    set_long("@@long_descr");

    add_item("doorway","The doorway to the north leads south into the " +
    "temple.\n");
    add_item("city","You see the city spread out before you. Quite a " +
    "sight.\n");
    add_item(({"square","temple square","entrance"}),
    "Looking down, you see the Temple Square in all its splendour.\n");

    reset_room();

    add_exit(NTEMPLE + "u3", "south");
    // hidden exits to make shout work on the temple plaza
    add_exit(NINNER + "s1", "", 1, 1, 1);
    add_exit(NINNER + "s2", "", 1, 1, 1);
    add_exit(NINNER + "s3", "", 1, 1, 1);
    add_exit(NINNER + "s4", "", 1, 1, 1);
    add_exit(NINNER + "s5", "", 1, 1, 1);
    add_exit(NINNER + "s6", "", 1, 1, 1);
}


