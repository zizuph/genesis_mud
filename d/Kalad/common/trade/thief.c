inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
create_monster()
{
   ::create_monster();
   set_name("thief");
   set_race_name("human");
   add_name("thief");
   add_adj("wiry");
   add_adj("sneaky");
   set_pshort("thieves");
   set_long("This sneaky human looks at you with greed evident in his eyes.\n");
   default_config_npc(75);
   add_speak("How about I stick my knife in you!!\n");
   set_skill(SS_DEFENCE,70);
   set_skill(SS_PARRY, 75);
   set_skill(SS_WEP_KNIFE,65);
   set_act_time(6);
   add_act("emote looks at your purse greedily.");
   add_act("emote grips the handle of his knife tightly.");
   add_act("emote looks around for the city guard.");
   add_act("emote smiles thinly.");
   add_act("emote grabs at your purse.");
   set_chat_time(6);
   add_cchat("RaaaaaarrrrggghH!");
   add_cchat("Feel my blade worm!");
   add_cchat("You will be the next victim of the Blackhands!");
   add_cchat("Why do you persist?");
   add_cchat("You can't beat a thief from the Blackhands!");
   set_cact_time(1);
   set_default_answer("I dont really have much to say.\n");
   ::create_monster();
   set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
   seteuid(getuid(TO));
   clone_object("/d/Kalad/common/trade/tsquare/obj/tdag")->move(TO);
   
   command("wield all");
}
