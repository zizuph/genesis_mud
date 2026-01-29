/* Kirk of Port City - Sanctuary
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/5/97      Zima        Created
**
*/
/* inherits/includes */
#include "defs.h"
inherit ROOM+"ksanct";
#include <macros.h>
#include <stdproperties.h>
 
/* room definition */
void create_khalakhor_room() {
   object ped;
   set_short("Sanctuary of the kirk");
   set_long(
      "   You are standing along the middle of the east wall of the sanctuary, "+
      "below one of the six great stained glass windows which cast dim "+
      "beams of color on the smooth floor, mixed with the light from the "+
      "candles of the chandeliers above. To the west is the high altar of "+
      "the kirk, while a marble pedestal stands beneath the window next "+
      "to the wall.\n");
 
   setup_ksanct();
 
   add_item("window",&windesc(8));
 
   add_exit("ksanct9", "north",0);
   add_exit("ksanct5", "west",0);
   add_exit("ksanct3", "south",0);
   ped = make_ped(({"marble","marble","window","east","sculpted",SR_SECHNASACH}));
   add_prop(CANTICLE_ROOM,1);
   add_prop(MY_CANDLE_HERB,"blueberry");
   add_prop(MY_CANT,8);
}
