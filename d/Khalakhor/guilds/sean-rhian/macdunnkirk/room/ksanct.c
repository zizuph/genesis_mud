/* Kirk of Port City - Sanctuary Base Room
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 7/20/97     Zima        Created - inherited by ksanctX.c
** 3/7/98      Zima        Added support for pedestal creation
** 5/28/98     Zima        Added support for canticles to be sung
**
*/
/* inherits/includes */
inherit "/d/Khalakhor/std/room";
#include "defs.h"
#include "kwin.h"
#include <macros.h>
#include <stdproperties.h>
private string query_no_scry(); 
object ped;
 
/*
** windesc() - returns complete description of a kirk window
*/
string windesc(int i) {
   string desc;
   if (i==3)
      desc="This window is unique amongst the windows of the kirk, "+
           "made in the shape of a large circle, unlike the tall "+
           "pointed arches elsewhere. It is set high in the wall above "+
           "the main entrance of the sanctuary. ";
   else
      desc="It is a tall thin window made of stained glass, rising "+
           "to a pointed arch at the top. ";
   desc=desc+WINDESC[i]+"\n";
   return desc;
}
 
/*
** setup_ksanct() - common add_items of kirk sanctuary rooms
*/
void setup_ksanct() {
   INSIDE;
   add_prop(ROOM_M_NO_SCRY, query_no_scry);
   add_prop(SR_K1SECURE,1); // security area of the kirk
   add_item(({"chamber","sanctuary"}),
      "You are standing at its entrance.\n");
   add_item(({"wall","walls"}),
      "The walls of the sanctuary are made of massive, smooth stones like "+
      "the entire kirk. Large stained glass windows adorn the western, "+
      "eastern and southern sides of the chamber.\n");
   add_item("apse",
      "It is a semi-circular, domed extension on the far north end of the "+
      "sanctuary, its walls decorated with various figures and symbols. "+
      "It houses a statue of a great angel. You could get a better look "+
      "if you walked up to it to the north.\n");
   add_item(({"angel","statue"}),
      "Housed in the apse on the far north end of the sanctuary, the "+
      "towering statue of an angel dominates the sanctuary, his eyes "+
      "gazing out over the splendor of the sanctuary. You could get a "+
      "better look at it if you went closer.\n");
   add_item("altar",
      "It is a large marble altar standing in the very center of the "+
      "sanctuary, an ornate flat top balanced on top of a thick cylindrical "+
      "pedestal set into the floor. You can get a better look if you got "+
      "closer.\n");
   add_item(({"windows","mosaic","mosaics","sacred persons"}),
      "There are nine large stained glass windows, three on each of the "+
      "eastern, western and southern walls. They are made of colorful "+
      "mosaics of glass and depict what must be holy persons and symbols. "+
      "You can get a closer look at each one by approaching and examining "+
      "each one.\n");
   add_item("ceiling",
      "The ceiling is divided into nine dome-like vaults, three by three, "+
      "detailed with gold ornamentation, each with a chandelier hanging "+
      "from its central point. It rises high above you, like the ceiling "+
      "of a large cavern.\n");
   add_item("chandeliers",
      "Nine chandeliers suspended from the vaults of the ceiling of the "+
      "sanctuary give light to the chamber with their hundreds of "+
      "flickering candles. One is directly above you.\n");
   add_item(({"chandelier","chain","candles","light"}),
      "Suspended by a thick gold chain from the central point of the "+
      "vaulted ceiling high above you is an ornate chandelier filled with "+
      "dozens of burning candles, their graceful flickering flames filling "+
      "the chamber with a subtle light.\n");
   add_item(({"arch","entrance","entrances"}),
      "A large arch rises to a point in the middle of the southern wall of "+
      "the sanctuary, marking the main entrance from the south. On the "+
      "far north end you see two smaller entrances on either side of the "+
      "apse.\n");
}
 
/* room definition */
void create_khalakhor_room() {
   set_short("Kirk Sanctuary Base Room");
   set_long("Kirk Sanctuary Base Room");
}
 
/*
** make_ped - creates and configs a pedestal in a sanctuary room
*/
object make_ped(string* parms) {
   /* parms as expected by ped_config in pedestal object */
   ped = clone_object(SR_OBJ+"pedestal");
   ped->ped_config(parms);
   ped->move(this_object());
   return ped;
}
 
/*
** cwc_match - do the canticle, window an candle match?
*/
int cwc_match(int cant, object candle)
{
   //if candle matters, must have correct herb in candle
   if ((objectp(candle))&&
      (query_prop(MY_CANDLE_HERB) != (candle->query_herb())))
      return 0;
 
   // must chant correct canticle
   if (query_prop(MY_CANT) != cant) return 0;
 
   // ok, there is a match
   return 1;
}
 
/*
** resp_chant - give response to aspirant's chant
*/
void resp_chant(int cant, object pend, object tp)
{
   object candle;
 
   // lit handmade candle should be on pedestal here
   if (!(objectp(ped) && (ENV(ped)==TO))) return;
   candle=present(HM_CANDLE,ped);
   if (!(objectp(candle) && (candle->query_lit(0)))) return;
 
   // aspirant should be here with his pendant & have said right chant
   if (objectp(tp) && (ENV(tp)==TO) && objectp(pend) && (ENV(pend)==tp) &&
      cwc_match(cant,candle))
      {
      tell_room(TO,"The "+(candle->short())+" flickers and shines "+
                   "brightly.\n");
      pend->report_correct_chant(cant,tp);
      }
   else
      {
      tell_room(TO,"There is a sudden cold breeze which blows out the "+
                   (candle->short())+".\n");
      candle->extinguish_me();
      }
}
 
/*
** canticle_chanted - invoked when player chants, by sr/book/canticles.c
*/
void canticle_chanted(int cant, object tp)
{
   object pendant = present(SHAM_PENDANT,tp); // player must be aspirant
   if (objectp(pendant))
      set_alarm(7.0,0.0,&resp_chant(cant,pendant,tp));
}
private string
query_no_scry()
{
  string *messages = ({
        "Ancient blessings prevent this action.",
        "Ancient blessings prevent your efforts.",
        "Ancient blessings foil this action.",
        "Ancient blessings foil this attempt.",
        "Ancient blessings foil your efforts.",
        "Ancient blessings avert this action.",
        "Ancient blessings thwart this attempt.",
        "Ancient blessings stop your efforts.",
        "Archaic blessings prevent this action.",
        "Traditional blessings prevent this attempt.",
        "Divine blessings prevent your efforts.",
        "Celestial blessings foil this action.",
        "Divine blessings foil this attempt.",
        "Divine blessings foil your efforts.",
                        });

  return messages[random(sizeof(messages))];
}