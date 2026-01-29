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
      "   A small pointed archway leads out of the sanctuary of the kirk "+
      "to the north here at the northwest corner of the cavernous chamber. "+
      "One of the six great stained glass windows rises above you on the "+
      "western wall, dim sunlight filtering through its colorful mosaic. "+
      "A marble pedestal stands beneath the window next to the wall. A few "+
      "paces away to the southeast is the high altar of the kirk.\n");
   setup_ksanct();
   add_item("window",&windesc(5));
   add_item(({"arch","arcwhay","entrance"}),
      "A pointed arch marks the northeastern entrance of the sanctuary, "+
      "leading north into another part of the kirk.\n");
   add_item(({"angel","statue"}),
      "You can't see it this far north, it is set back in the apse to "+
      "the east.\n");
 
   add_exit("kanterm", "north",0);
   add_exit("ksanct8",   "east",0);
   add_exit("ksanct5",   "southeast",0);
   add_exit("ksanct4",   "south",0);
   ped = make_ped(({"marble","marble","window","west","sculpted",SR_CAMULOS}));
   add_prop(CANTICLE_ROOM,1);
   add_prop(MY_CANDLE_HERB,"hazelnut");
   add_prop(MY_CANT,6);
}
