/* Ashlar, 30 Sep 97 */
/* THIS IS NOT THE STORE ROOM FOR THE SHOP! */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit TEMPLE_BASE;

#ifdef 0
object crate;
#endif

void
reset_neraka_room()
{
#ifdef 0
    setuid();
    seteuid(getuid());

    if (!objectp(crate))
    {
        crate = clone_object(NOBJ + "coatbox");
        crate->move(this_object(),1);
    }
#endif
}

string
long_descr()
{
    return "This is a store room in the lower level of the temple. Here " +
    "equipment used by the Priests of Takhisis can be stored, to allow " +
    "all members to share the equipment. Doorways lead southwest and " +
    "southeast.\n";
}

void
create_neraka_room()
{
    set_short("a store room within the temple");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"doorway","small doorway"}),
    "The doorway is decorated with a wooden frame painted white.\n");
    add_item(({"frame","wooden frame","white frame"}),
    "The frame is made of wood, but you cannot discern the type of " +
    "wood. The white paint contrasts nicely with the darker walls.\n");

    reset_room();

    add_exit(NTEMPLE + "start", "southwest");
    add_exit(NTEMPLE + "d2", "southeast");
}

