/* Ashlar, 21 Aug 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <ss_types.h>

inherit SEWER_BASE;

string
long_descr()
{
    return "This is the top end of a staircase the leads down into " +
    "darkness. The ground here is dry and dusty, but you can still " +
    "smell the sewers.\n";
}

void
create_neraka_room()
{
    set_short("at the top end of a staircase");
    set_long("@@long_descr");

    add_crypt_items();

    remove_prop(ROOM_I_LIGHT);

    add_exit(NSEWER + "s3", "north");
    add_exit(NSEWER + "c1", "down");
}


