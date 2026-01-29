/* Forge Wagon
 * Chaos, 5 April 1995
 */

inherit "/std/room";

#include "/d/Cirath/defs.h"
#include "/d/Cirath/common/mobber.h"

#define PATH "/d/Cirath/katakoro/"

void
create_room()
{
    
   bring_room_mob("smith",PATH+"NPC/smith",1,1);

    set_short("Forge Wagon");
    set_long("This large wagon carries a huge forge, "+
	"possibly for when the Khahan's army is on the move. There are "+
	"several items lying about that would suggest that this forge "+
	"is under nearly constant use and even now a thin trail of smoke "+
	"lazily drifts upward from the coals.  To the south is a yurt, "+
	"which could possibly be where the smith lives.\n");

  add_exit(PATH + "encampment/yurts/yurt9","south");  
  add_exit(PATH + "encampment/camp15","east");

}
