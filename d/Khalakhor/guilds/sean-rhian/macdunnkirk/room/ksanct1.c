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
#include <stdproperties.h>

inherit ROOM+"ksanct";
object ped3, ped4; // this room has 2 pedestals


/* room definition */
void create_khalakhor_room() {
   set_short("Sanctuary of the kirk");
   set_long(
      "   You are in the southwestern corner of the sanctuary of the kirk, "+
      "standing beneath two of the great stained glass windows which "+
      "adorn the walls, one on the western and another on the southern. "+
      "A marble pedestal sits at the foot of each of the arched windows. "+
      "Looking out into the sanctuary, your attention is drawn to the "+
      "high altar a few paces away to the northeast, and further to the "+
      "great apse at the northern end of the sanctuary, housing the statue "+
      "of the towering angel.\n");
 
   setup_ksanct();
 
   add_item(({"window","windows"}),
      "There is one on the west wall and another on the south.\n");
   add_item(({"first window","west window","western window"}),
      &windesc(6));
   add_item(({"second window","south window","southern window"}),
      &windesc(2));
 
   add_exit("ksanct4", "north",0);
   add_exit("ksanct5", "northeast",0);
   add_exit("ksanct2", "east",0);
   ped3=make_ped(({"marble","marble","window","west","sculpted",SR_IRGALACH}));
   ped4=make_ped(({"marble","marble","window","south","sculpted",SR_AMBISARGUS}));
   add_prop(CANTICLE_ROOM,1);
}
 
// 2 pedestals in this room caues a bit of a situation, nothing
// we can't handle. Mask canticle chanted to take care of it.
void setup_chant(int pnum)
{
   if (pnum==3)
      { ped=ped3; add_prop(MY_CANT,7); add_prop(MY_CANDLE_HERB,"hawthorn"); }
   else
      { ped=ped4; add_prop(MY_CANT,4); add_prop(MY_CANDLE_HERB,"dandelion");}
}
 
void canticle_chanted(int cant, object tp)
{
   if (present(HM_CANDLE,ped3))    // candle on ped 3
      if (present(HM_CANDLE,ped4)) // candle on both pedestals
         if (cant==3)             // cant 3 chanted
            setup_chant(3);       // assume for candle on ped 3
         else                     // not chant 3
            setup_chant(4);       // assume for candle on ped 4
      else                        // candle on ped 3 only
         setup_chant(3);          // assume for candle on ped 3
   else                           // no candle on ped 3
      setup_chant(4);             // assume for candle on ped 4
   ::canticle_chanted(cant,tp);
}
