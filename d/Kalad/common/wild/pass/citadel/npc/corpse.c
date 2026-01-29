/* By Korat
 * Sept. 1996
 * A corpse that can be found in the cellar.
 *
*/
inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"

void
create_monster()
{
   ::create_monster();
   set_name("body");
   set_race_name("human");
   set_adj("dying");
   set_long("It is a dying body of a human. It cannot cling much longer "+
      "to life, something the diminnishing colour of the face tells you.\n");

   /* blow on it, and it dies */
   set_stats(({1,1,10,1,1,1}));
   set_alignment(0);
   set_knight_prestige(0);
   set_act_time(30);
   add_act("slightly twitches one of its fingers.");
   set_default_answer(VBFC_ME("answer"));
   add_prop(NPC_M_NO_ACCEPT_GIVE,"Give something to a corpse??");
   set_alarm(300.0,0.0,"kill_me");
}

/* this corpse may respond */
string
answer()
{
   if (!random(3))
   {
      tell_room(E(TO),"The lips of the corpse seems to move!\n");
      write("You bend down to catch any words coming from this "+
         "almost dead human.\n");
      return "k ... i ... l ... ... l ... ... m ... e ... ehhh ... \n";
   }
   
   if (!random(3))
   {
      tell_room(E(TO),"The lips of the dying human seems to move once more, "+
         "using its last strenght.\n");
      set_alarm(2.0,0.0,"kill_me");

      /* we return a hint of the dangers here */
      return "po ... ois ... ohhn ... ... bew ... a ... r ... ... "+
         "ss ... achhh ... rificed ... ww ... ronggly ... \n";
   }

   return "The dying human doesn't reply.\n";
}

void
kill_me()
{
   TO->command("emote whispers weakly: ... be sure ... ... or ... ... die ...");
   TO->set_hp(0);
   do_die(TO);
}

