inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Cirath/common/teamer.h"

create_room()
{
   bring_room_team(KAT_DIR+"npc/guard",1,3);
 
   set_short("Barbarian camp");
   set_long("This is the outer border of the encampment.  Scattered "+
	"about this area are the guards as well as the men in charge "+
	"of the livestock that is grazing nearby.  Stubby grass has "+
	"begun breaking through the pitted crust of old snow, and the "+
	"ground is beginning to thaw and become muddy.\n");

  add_exit(PATH + "encampment/camp22","east");  
  add_exit(PATH + "desert/waste1","south");

}
  
