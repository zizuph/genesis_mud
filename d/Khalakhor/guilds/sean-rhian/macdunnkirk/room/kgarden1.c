/* Kirk of Port City - Abbey garden
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/18/98     Zima        Created
** 6/18/98     Zima        Ability to open gate added
**
*/
#include "defs.h"
#include "/d/Khalakhor/guilds/sean-rhian/lib/zdoor.h"
#define  OPATH MACDUNN_DIR+"room/road_3_7"
inherit  SR_LIB+"zindoor";
inherit  ROOM+"kgardbase";
 
//
// create_khalakhor_room
//
void create_khalakhor_room()
{
   setup_garden_room();
   set_long((query_std_long())+"There is a gate in the fence here leading "+
            "out of the garden into the street to the south.\n");
   add_item(({"lock","bolt"}),
      "The lock on the gate is a bolt lock which doesn't require a key "+
      "but can only be locked and unlocked from this side.\n");
 
   add_exit("kgarden3","north");
 
   setup_indoor("south", OPATH, ({"gate"}),
      "The gate is constructed the same as the fence into which it is "+
      "hinged. Overgrown with ivy, it looks like it doesn't get much use."+
      " It has a bolt action lock on it.",
      "ivy-covered gate", 0, BOLTABLE, CLOSED, 100);
}
 
void init()
{
   ::init();
   add_indoor_actions();
}
