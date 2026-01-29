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
    return "This is a wide hallway on the main level of the temple. " +
    "The hallway leads south and branches off to the east and west. " +
    "To the north, a pair of double doors lead out of the temple.\n";
}

void
create_neraka_room()
{
    set_short("wide hallway at the entrance to the temple");
    set_long("@@long_descr");

    add_temple_items();
    add_item("hallway","@@long_descr");
    add_item(({"pair of double doors","doors","door","double doors"}),
    "The large iron doors stand open, allowing you to exit the temple " +
    "if you wish.\n");

    reset_room();

    add_exit(NTEMPLE + "m2", "west");
    add_exit(NTEMPLE + "m3", "east");
    add_exit(NTEMPLE + "m6", "south");
    add_exit(NINNER + "s5", "north", "@@exit_temple");
}

int
exit_temple()
{
    write("You leave the temple and step out on the Temple Square.\n");
    return 0;
}
