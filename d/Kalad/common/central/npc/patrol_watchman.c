/*
 * /d/Kalad/common/central/npc/patrol_watchman.c
 * Purpose    : A wandering herald.
 * Located    :
 * Created By : Korat
 * Modified By: Rico 8.Mar.97
 *              Fysix, Feb 1998, debugged and recoded
 */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include "default.h"
#include "/d/Kalad/sys/time.h"
#include <money.h>

int    last_hour;
string text;

void
create_kalad_monster()
{
   set_name("hammer");
   add_name("watch-man");
   set_race_name("human");
   set_adj("City of Kabal");
   add_adj("watchman");
   set_long("This man walks the streets of kabal, where he "+
      "announces the time and the latest news of the city.\n");

   set_stats(({ 40, 57, 63, 65, 43, 34 }));

   set_alignment(500);
   set_knight_prestige(-5);
   set_title("the Watchman of Kabal");
   set_default_answer("All I know is that I have a job to do.\n");
   add_speak("Nice chatting with you, but I have work to do.\n");

   set_skill(SS_WEP_POLEARM, (random(30) + 5));
   set_skill(SS_BLIND_COMBAT, 20);
   set_skill(SS_DEFENCE, (random(30) + 5));

   set_cact_time(6);
   add_cact("say How dare you to attack me! It will mean your death!");
   add_cact("say You shouldn't have disturbed us. It will mean your " +
      "death!");
   set_act_time(10);
   add_act("@@test_bell@@");

   set_random_move(5);

   add_equipment(({
      CENTRAL + "arm/patrol_robe",
      CVAN + "obj/oil_lamp",
      CVAN + "obj/oilflask",
      CENTRAL + "wep/pole",
      }));
   set_alarm(3.0, 0.0, &command("fill lamp with oil"));
   MONEY_MAKE_SC(random(5))->move(this_object(), 1);

   text = "and the chairman of the Council of Lords is still "+
          "reported to be sick.";

   last_hour = HOUR;
}

/* Function: react_bell
 * Purpose : Give the watchman some news to tell.
 * Returns : command to give with add_act.
 */
string
react_bell()
{
   string txt;

   switch (random(11))
   {
      case 0..4:
         txt = "and allllllll's well!";
         break;

      case 5:
         txt = "and the High Lord seeks Dernen's head!";
         break;

      case 6:
         txt = "and I need a raise!";
         break;

      case 7:
         txt = text;
         break;

      case 8:
         txt = "and Mrs. Sandours just gave birth to a baby boy!";
         break;

      case 9:
         txt = "and the missing caravan was found.. hijacked!";
         break;

      case 10:
         txt = "and the price of bread just rose with 2 coppers!";
         break;

      case 11:
         txt = "and the ship from Cove just arrived!";
         break;

      default:
         break;
   }

   return "shout It is " + HOUR + " o'clock, " + txt;
}

void
new_event(string str)
{
   text = str;
}

/* Function: test_bell
 * Purpose : Check the time in Kabal.
 * Returns : string for add_act
 */
string
test_bell()
{
   if ((HOUR == 1 && last_hour == 12) || HOUR > last_hour)
   {
      last_hour = HOUR;
      return react_bell();
   }

   return "";
}

