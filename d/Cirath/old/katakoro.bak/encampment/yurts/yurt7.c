/* Clothworker's Yurt
 * Chaos, 5 April 1995
 */

inherit "/std/room";

#include "/d/Cirath/defs.h"
#include "/d/Cirath/common/mobber.h"

#define PATH "/d/Cirath/katakoro/"

void
create_room()
{
   bring_room_mob("clothworker",PATH+"NPC/clothworker",1,1);
    set_short("Clothworker's yurt");
    set_long("This yurt is home to a clothworker, or more specifically "+
	"a felt worker. Though, capable of working with other forms of "+
	"cloth, there is a great abundance of felt lying around ready "+
	"to be made into rugs for various uses.  There are also some "+
	"unfinished kalats lying about, but it is obvious that those "+
	"are secondary to the felt.\n");

    add_item(({"felt","rugs"}),"These felt rugs, when complete will be "+
	"used in the building of more yurts for various members of the "+
	"tribe.  Some have been pounded with chalk to give them a "+
	"somewhat white look, others have been left in thier natural "+
	"state of black.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PATH+"encampment/camp12","out");
}
