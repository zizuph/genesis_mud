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
object ped6, ped7; // this room has 2 pedestals
 
/* room definition */
void create_khalakhor_room() {
   set_short("Sanctuary of the kirk");
   set_long(
      "   You are standing beneath two of the great stained glass windows "+
      "which adorn the walls of the kirk, one on the east and one "+
      "on the south, gazing out at the cavernous sanctuary from its "+
      "southeastern corner. The high altar of the kirk is a few steps to "+
      "the northwest, protectingly watched by the great angel which stands "+
      "in the apse on the north end. There are two pedestals on the floor "+
      "here, one below each of the arched windows.\n");
 
   setup_ksanct();
   add_item(({"window","windows"}),
      "There is one on the east wall and another on the south.\n");
   add_item(({"first window","east window","eastern window"}),
      &windesc(9));
   add_item(({"second window","south window","southern window"}),
      &windesc(1));
 
   add_exit("ksanct6", "north",0);
   add_exit("ksanct5", "northwest",0);
   add_exit("ksanct2", "west",0);
   ped6=make_ped(({"marble","marble","window","south","sculpted",SR_RHIANNON}));
   ped7=make_ped(({"marble","marble","window","east", "sculpted",SR_RAGALLACH}));
   add_prop(CANTICLE_ROOM,1);
}
 
// 2 pedestals in this room caues a bit of a situation, nothing
// we can't handle. Mask canticle chanted to take care of it.
void setup_chant(int pnum)
{
   if (pnum==6)
      { ped=ped6; add_prop(MY_CANT,2); add_prop(MY_CANDLE_HERB,"lilac");}
   else
      { ped=ped7; add_prop(MY_CANT,9); add_prop(MY_CANDLE_HERB,"fireweed");}
}
 
void canticle_chanted(int cant, object tp)
{
   if (present(HM_CANDLE,ped6))   // candle on ped 6
      if (present(HM_CANDLE,ped7))// candle on both pedestals
         if (cant==6)             // cant 6 chanted
            setup_chant(6);       // assume for candle on ped 6
         else                     // not chant 6
            setup_chant(7);       // assume for candle on ped 7
      else                        // candle on ped 6 only
         setup_chant(6);          // assume for candle on ped 6
   else                           // no candle on ped 6
      setup_chant(7);             // assume for candle on ped 7
   ::canticle_chanted(cant,tp);
}
