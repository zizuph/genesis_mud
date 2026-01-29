/*
 *    The base file for the sewers of Neraka, and the crypts.
 *
 *    sewer_base.c
 *    ------------
 *
 *    Coded .........: 97/08/19
 *    By ............: Ashlar
 *
 *    Latest update .: 97/08/21
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

add_lsewer_herbs()
{
    set_up_herbs(({KRHERB + "angeltear", KRHERB + "brownslime",
	KRHERB + "greenslime", KRHERB + "skullcap"}),
      ({"wall","walls","blocks","stone blocks","tunnel","bottom"}));
}

void
add_lsewer_items()
{
    add_item(({"sewers","tunnel"}),"@@long_descr@@");
    add_item(({"floor","bottom","water"}),"@@water_desc@@\n");
    add_item(({"wall","walls"}),"The walls of the tunnel are made of grey " +
      "stone blocks on which various things grow.\n");
    add_item(({"blocks","stone blocks"}),"The stone blocks that make up " +
      "the walls of the sewer are host to a multitude of growing things.\n");
    add_item(({"ceiling"}),"The ceiling of the tunnel is lost in murky " +
      "darkness.\n");
}

add_crypt_items()
{
    add_item("floor",
      "The floor is paved with large stone blocks evenly placed.\n");
    add_item(({"blocks","stone blocks","large stone blocks"}),
      "The large stone blocks that make up both floor and walls of " +
      "these rooms are cut with great precision and placed evenly.\n");
    add_item(({"walls","wall"}),
      "The walls are made of large stone blocks evenly placed.\n");
    add_item(({"ceiling"}),"The ceiling is high here, and the " +
      "darkness seems much more compact there. You can not make out " +
      "much of the ceiling.\n");
}

string
water_desc()
{
    string str;

    switch(GET_SEASON)
    {
    case SPRING:
	str = "The bottom of the tunnel is covered with stagnant, " +
	"slimy water that reaches almost to your knees. ";
	break;
    case SUMMER:
	str = "The bottom of the tunnel is covered with stagnant, " +
	"slimy water that reaches above your ankles. ";
	break;
    case AUTUMN:
	str = "The bottom of the tunnel is covered with a layer " +
	"of stagnant, slimy water. ";
	break;
    case WINTER:
	str = "The bottom of the tunnel is covered with stagnant, " +
	"slimy water that reaches above your ankles. ";
	break;
    }

    return str;
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

