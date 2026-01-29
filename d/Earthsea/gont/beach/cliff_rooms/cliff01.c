/*
 * Cliff on Gont beach
 * By Finwe
 * May 1997
 */

#pragma strict_types
#pragma no_clone

#include <stdproperties.h>
#include "default.h"


inherit CLIFFS_ROOM;

#define CLIFFTOP "/d/Earthsea/gont/gont_city/rooms/e_cliff3"

public void
create_cliffs()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("The side of a cliff");
    set_long("You stand at the north end of the cliffs. "+
	"Standing tall and proud, they are like sentinels facing the "+
	"challenge from the sea. The cliffs are formed from weathered "+
	"granite and limestone, veined with streaks of black and gray. The "+
	"mighty cliffs act as a barrier to the island as they " +
	"defiantly rise out of the depths of the ocean. " +
	"Centuries of constant wind has left the face of the " +
	"cliffs covered with niches and cracks. Overhead, " +
	"screeching seabirds fly to and from as they navigate " +
	"around the cliffs. A path leads southeast along the "+
	"cliff and down to the beach. A stairway crudely "+
	"carved from granite leads up to the top of the cliff.\n");

    add_exit(CLIFFTOP, "up");
    add_exit(BEACH_DIR + "beach02", "down");
    add_exit("cliff03", "southeast");
}
