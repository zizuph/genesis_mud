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
 
/* room definition */
void create_khalakhor_room() {
   object ped;
   set_short("Sanctuary of the kirk");
   set_long(
      "   You are standing in the norteastern corner of the sanctuary, "+
      "beneath another of the great windows of the kirk. A small pointed "+
      "archway leads north out of the sanctuary into another chamber. "+
      "You see the high altar of the kirk in the center of the sanctuary "+
      "to the southwest, and a marble pillar standing at the foot of the "+
      "great window next to the wall. To the west is the entrance to the "+
      "apse which houses the statue of the angel, hidden from view from "+
      "this angle.\n");
   setup_ksanct();
   add_item("window",&windesc(7));
   add_item(({"arch","arcwhay","entrance"}),
      "A pointed arch marks the northeastern entrance of the sanctuary, "+
      "leading north into another part of the kirk.\n");
   add_item(({"angel","statue"}),
      "You can't see it this far north, it is set back in the apse to "+
      "the east.\n");
 
   add_exit("ktabernacle","north",0);
   add_exit("ksanct8",   "west",0);
   add_exit("ksanct5",   "southwest",0);
   add_exit("ksanct6",   "south",0);
   ped = make_ped(({"marble","marble","window","east","sculpted",SR_ARGANTE}));
   add_prop(CANTICLE_ROOM,1);
   add_prop(MY_CANDLE_HERB,"honeysuckle");
   add_prop(MY_CANT,1);
}
