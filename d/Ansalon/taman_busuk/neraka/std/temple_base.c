/*
 *    The base file for the temple of Takhisis inside rooms
 *
 *    sewer_base.c
 *    ------------
 *
 *    Coded .........: 97/09/30
 *    By ............: Ashlar
 *
 *    Latest update .: 97/09/30
 *    By ............: Ashlar
 *
 *
 *    Notes ..:
 *
 *    Changes :
 *
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include DL_CLOCK

/* Inherit the Ansalon room */
inherit AR_FILE

#include "clone_npc.c"
#include "/d/Krynn/common/herbsearch.h"

#define KRHERB "/d/Krynn/common/herbs/"

#define CREATE "create_neraka_room"
#define RESET  "reset_neraka_room"

string extra_long_desc;

add_garden_herbs()
{
    set_up_herbs(({KRHERB + "angeltear", KRHERB + "brownslime",
    KRHERB + "greenslime", KRHERB + "skullcap"}),
    ({"wall","walls","blocks","stone blocks"}));
}

void
add_temple_items()
{
}

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    call_other(TO, CREATE);
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    set_searched(0);
    call_other(TO, RESET);
}

