inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by mhyrkhaan */

void
create_monster()
{
   ::create_monster();
   set_name("dargoth");
   add_name("cook");
   set_race_name("goblin");
   set_adj("fat");
   add_adj("sweaty");
   set_long("This is the Cook and waiter for the Lone Wolf Inn. He "+
   "will get you what you need and happily take your money. He is fat "+
   "and sweaty, but an excelent cook.\n");
   set_stats(({150,150,150,150,150,200}));
   set_title("Darkspawn, Retired of the Dark Alliance and caretaker of the Lone Wolf");
   set_skill(SS_WEP_SWORD,50);
   set_skill(SS_WEP_CLUB,50);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,90);
   add_prop(LIVE_I_SEE_DARK,5);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(CONT_I_WEIGHT,100000);
   add_prop(CONT_I_VOLUME,100000);
   set_act_time(7);
   add_act("emote sniffs the air curiously, and says: Whats burning?");
   set_act_time(5);
   add_act("emote wipes the counter as he gazes past you into the "+
   "training area.");
   add_act("smote smiles, revealing yellow jagged teeth.");
   add_act("whispers: ya know, I hear the thanar are getting stronger, that's "+
   "not good for us.");
}