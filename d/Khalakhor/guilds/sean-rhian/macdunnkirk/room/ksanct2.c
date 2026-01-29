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
inherit  ROOM+"ksanct";
 
/* room definition */
void create_khalakhor_room() {
   object ped;
   set_short("Sanctuary of the kirk");
   set_long(
      "   You are standing at the entrance of the central sanctuary of the "+
      "kirk, a beautifully ornate, cavernous chamber which spreads out "+
      "before you to the north. Large stained glass windows line the "+
      "eastern, western and southern walls of the sanctuary, one here "+
      "directly above the entrance to the south, their mosaics "+
      "depicting sacred persons. The high altar of the kirk stands in the "+
      "center of the chamber just to the north. A large domed apse off the "+
      "north end of the sanctuary houses a towering statue of an angel, "+
      "whose gaze falls on all that occurs here. "+
      "Hundreds of candles flickering in chandeliers suspended from the "+
      "vaults of the sanctuary ceiling fill the chamber with a soft light. "+
      "A large pointed arch marks the main entrance of the sanctuary to "+
      "the south, while you see smaller entrances at the north end on "+
      "either side of the apse. There is a marble pedestal standing here "+
      "before the window above the entrance.\n");
 
   setup_ksanct();
   add_item("window",&windesc(3));
 
   add_exit("ksanct5", "north",0);
   add_exit("kfoyer",  "south",0);
   add_exit("ksanct3", "east",0);
   add_exit("ksanct1", "west",0);
   ped = make_ped(({"marble","marble","window","south","sculpted",SR_SEANCHAN_TOR}));
   add_prop(CANTICLE_ROOM,1);
   add_prop(MY_CANDLE_HERB,"holly berry");
   add_prop(MY_CANT,5);
}
