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
    "   The powerful and enchanting gaze of the figure depicted in the "+
      "stained glass window before you seems to penetrate into your "+
      "inner soul. You are standing beneath the window, along the western "+
      "wall of the sanctuary, where a marble pedestal stands. Looking "+
      "north you see the towering statue of the angel which stands guard "+
      "in the domed apse. The high altar of the kirk is just a few paces "+
      "to the east in the center of the cavernous chamber.\n");
 
   setup_ksanct();
 
   add_item("window",&windesc(4));
 
   add_exit("ksanct7", "north",0);
   add_exit("ksanct5", "east",0);
   add_exit("ksanct1", "south",0);
   ped = make_ped(({"marble","marble","window","west","sculpted",SR_KESAIR}));
   add_prop(CANTICLE_ROOM,1);
   add_prop(MY_CANDLE_HERB,"shamrock");
   add_prop(MY_CANT,3);
}
