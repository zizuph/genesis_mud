inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/d/Shire/common/make_money.h"
#include "/sys/macros.h"


void
create_monster()
{
   set_name("farmer");
   set_living_name("_farmerjones_");
   add_name("farmerjones");
   set_race_name("hobbit");
   add_adj(({"broad","strong-armed"}));
   set_long("This farmer is pretty young, really, 50 or so "+
   "in hobbit years. His skin is dark for a hobbit, probably "+
   "from the sun, and his face is gaunt and tired-looking, "+
   "as if he has had a hard life.\n");

   set_alignment(100 + random(150));
   set_whimpy(10);
   set_stats(({60,100,70,20,50,60}));
   set_skill(SS_WEP_KNIFE, 50 + random(20));
   set_skill(SS_DEFENCE, 45 + random(20));
   set_skill(SS_PARRY, 30 + random(15));
   set_skill(SS_UNARM_COMBAT, 60 + random(12));

   MAKE_MONEY;
   add_prop(LIVE_I_NEVERKNOWN, 1); /* Don't wanna know him */

   set_chat_time(6);
   add_chat("Boy, you can't just grind grain anywhere, you have to take it to Hobbiton.");
   add_chat("Working the fields is hard, but I am harder.");
   add_chat("Where's my wife gotten off to?");
   add_chat("I raise cattle and reap the harvest of the land.");
   add_chat("Sometimes, I like a nice pipeful of Toby's best.");

   set_act_time(10);
   add_act("emote stretches out his short tired legs.");
   add_act("yawn tir");
   add_act("smile ten");
   add_act("twiddle");

   add_ask(({"hay","for hay","about hay"}),VBFC_ME("ask_hay"));
   add_ask(({"grain","flour","about grain","about flour"}),VBFC_ME("ask_grain"));

}

string
ask_hay()
{
   command("say Hay's for horses, grass is cheaper!");
   command("laugh");
   command("say Well, if you want some, feel free to get all ");
   command("say you want. But, I appreciate your asking.");
   TP->add_prop("_i_asked_for_my_hay_", 1);

   return "";

}
string
ask_grain()
{
   command("smile .");
   command("say Well...");
   command("say If you had some, I'd say it could be milled in ");
   command("say Hobbiton.");
   command("say But I have no need of such places.");
   command("say I feed my grain directly to the cows.");
   command("grin");

   return "";
}
