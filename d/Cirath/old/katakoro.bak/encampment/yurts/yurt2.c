/* Beadworker's Yurt
 * Chaos, 5 April 1995
 */

inherit "/std/room";
#include "/d/Cirath/defs.h"
#include "/d/Cirath/common/mobber.h"
#define PATH "/d/Cirath/katakoro/"

void
create_room()
{
   bring_room_mob("beadworker",PATH+"NPC/beadworker",1,1);

    set_short("Beadworker's yurt");
    set_long("This yurt is home to a beadworker.  All manner of beads and "+
	"carvings are scattered about the yurt in various stages of "+
	"completion.  The yurt is also littered with the shavings that "+
	"result from the beadworkers craft.\n");

    add_item(({"beads","carvings"}),"These beads and carvings are the work "+
	"of a master, unusual if one considers these people as "+
	"uncivilized barbarians.  Each work is different, even two nearly "+
	"identical beads have an individual personality, as if it were "+
	"carved for a special purpose.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PATH+"encampment/camp3","out");
}
