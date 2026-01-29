/* Ashlar, 4 Oct 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include "../guild/guild.h"

inherit TEMPLE_BASE;

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "This is a vast, empty chamber. The only discernible feature " +
    "is the pair of large doors to the north. Even though you can see " +
    "a bit in here, the darkness around you press in, as if trying to " +
    "smother you.\n";
}

void
create_neraka_room()
{
    set_short("in a dark chamber");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"doors","pair of doors"}),
    "The doors are made of bronze, and looks quite heavy.\n");
    add_cmd_item(({"doors","pair of doors"}),
    "open","You do not have the strength to open them completely, but " +
    "you could probably open them far enough to go north if you wanted " +
    "to.\n");

    add_item("darkness","The darkness seems oppressive, almost malevolent. " +
    "It is obvious you are not welcome in here.\n");

    add_prop(ROOM_I_LIGHT, -3);

    reset_room();

    add_exit(NTEMPLE + "d13", "north");
}

