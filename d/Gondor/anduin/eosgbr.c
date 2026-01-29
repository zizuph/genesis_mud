/*
 * anduin/eosgbr.c
 */
#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");
#include <stdproperties.h>

void
create_room()
{
    set_short("On the River Anduin close to Eastern Osgiliath");
    set_long("You are on the river Anduin close to its eastern bank. The " +
        "ruins of an ancient stone bridge are standing like a smashed rock " +
        "on the bank, surrounded by the sad remains of once proud " +
        "houses and streets.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
