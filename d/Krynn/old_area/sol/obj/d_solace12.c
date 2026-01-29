/* A door in Solace, coded by Nick
 * adapted by Dorak 14-04-94
 * a door that looks and acts like a bush
 * it is for room solace13.c
 */

inherit "/d/Krynn/solace/village/obj/d_solace9";
#include "/d/Krynn/common/defs.h"
#include "../local.h"

create_door()
{
    ::create_door();

    set_other_room(TDIR + "solace9");
}
