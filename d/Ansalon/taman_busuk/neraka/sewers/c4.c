/* Ashlar, 21 Aug 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <ss_types.h>

inherit SEWER_BASE;

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "This is a dark hallway among the crypts below Neraka. " +
    "The air is dry and dusty, with a faint hint of something " +
    "unpleasant. The hallway continues north and south.\n";
}

void
create_neraka_room()
{
    set_short("in a dark hallway");
    set_long("@@long_descr");

    add_crypt_items();
    add_item("hallway","@@long_descr");

    remove_prop(ROOM_I_LIGHT);

    add_exit(NSEWER + "c6", "north");
    add_exit(NSEWER + "c2", "south");

    reset_room();
}


