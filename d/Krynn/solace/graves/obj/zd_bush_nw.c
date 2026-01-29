/* A door in the Solace Graveyard
 * zd_bush_nw.c
 * Dorak 07-04-95
 * a door that looks and acts like a bush
 */

inherit "/d/Krynn/solace/graves/obj/zd_bush_se";
#include "/d/Krynn/common/defs.h"
#include "../zlocal.h"

create_door()
{
    ::create_door();

    set_other_room(TDIR + "zo_grave2");
}
