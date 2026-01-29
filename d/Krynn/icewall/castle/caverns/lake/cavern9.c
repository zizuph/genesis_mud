/*Created by Stevenson*/

/* potential quest here with the myst. Here is the idea, find a small
box and place a lit torch into it. this will attract the spirit of
the kender.  Who knows.  maybe it will work.
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
inherit ICEINROOM;

static int spirit_here = 1;
object eel;

void reset_icewall_room()
{
   if (!objectp(eel))
   {
      eel = clone_object(ICE_CAST_M+"eel");
      eel->move(TO);
   }
   spirit_here = 1;
}

void kender_quest(object who)
{
   object box;
   if (!objectp(who)) return; 
   if (who->test_bit("Krynn",2,19)) return; /* already did quest */
   if (spirit_here && (box = P("kender_box",who)) != 0)
   {
      if (P("ember",box) && !P("mist",box))
      {
         spirit_here = 0;
         write("The mist begins to come to life. It coalesces into "
            + "the shape of a small kender.\nSensing a very warm and "
            + "intriguing box in your possession, the spirit approaches you "
            + "with a look of appreciation on its face.\n"
            + "With a quick, fluid motion, the spirit enters the box "
            + "and whispers to you: Please take me from this place. "
            + "Your heart will tell you where to "
            + "go.\nAs suddenly as it appeared, the spirit returns to "
            + "its mist-form.\n");
         say("The strange mist begins to swirl and change into the "
            + "shape of a kender.\n"
            + "The spirit approaches " + QTNAME(who) + " and vanishes.\n");
         clone_object(ICE_CAST_O+"kender_spirit")->move(box);
       }
   }
}

void enter_inv(object who, object from)
{
   ::enter_inv(who, from);
   if (living(who)) set_alarm(1.0, 0.0, &kender_quest(who));
}

void create_icewall_room()
{
   set_short("Edge Of Lake");
   set_long(
      "You see a chilling mist hovering over the surface of the lake "
      +"here. What causes it is a mystery. The cavern ends abruptly to "
      +"the west but the lake is east of you. "
      +"\n");
   
   add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
   add_item("mist","Legend has it that the first Kender to discover "
      + "this place died by freezing to death. The mist is actually his "
      + "frozen spirit seeking a warm place to rest."
      + "\n");
   add_item("cavern","The rocky wall is directly west of you.\n");
   add_item("wall","It is rough and bumpy.\n");
   add_item("lake","The lake spreads out to the east of you.\n");
   
   add_exit(CAVE + "cavern1.c", "southeast");
   
   reset_icewall_room();
}
