inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
create_monster()
{
   ::create_monster();
    set_name("regols");
   set_race_name("human");
   add_name("trainer");
   add_adj("tall");
   add_adj("lanky");
   set_short("tall lanky thief trainer");
   set_long("This thief is very tall, and he seems well versed in the "+
   "arts of terroris amd thievery.\n");
   set_stats(({80,100,80,50,70,80}));
   set_skill(SS_DEFENCE,70);
   set_skill(SS_PARRY, 75);
   set_skill(SS_WEP_KNIFE,85);
   set_act_time(6);
   add_act("emote shows a novice how to mix ingredients right.");
   add_act("emote shows a novice how to steal correctly.");
    add_act("say Careful! Watch for their eyes, they tell you if "+
   "they are distracted enought...");
   add_act("say Dont touch so hard!");
   add_act("emote shows a novice how to look for quality in objects.");
   set_chat_time(6);
   add_cchat("RaaaaaarrrrggghH!");
   add_cchat("Feel my blade worm!");
   add_cchat("You will be the next victim of the Shadow Walkers!");
   add_cchat("Why do you persist?");
   add_cchat("You can't beat a thief from the Shadow Walkers!");
   set_cact_time(1);
   set_title("the Knight of the Streets");
   set_default_answer("I dont really have much to say.\n");
   add_ask(({"zintra","black rose"}),"They are the ones who truely "+
   "run things...the Shadow Lords follow them, they are darker and "+
   "more evil than I have ever known!\n");
   add_ask("shadow lords","They are the heads of the Shadow Walkers.\n");
   add_ask("shadow walkers","That is us, we are those who walk "+
   "in the shadows.\n");
   ::create_monster();
}

void
arm_me()
{
   seteuid(getuid(TO));
   clone_object("/d/Kalad/common/trade/tsquare/obj/tdag")->move(TO);
   clone_object("/d/Kalad/common/guilds/shadow_walkers/silk_tunic")->move(TO);
   clone_object("/d/Kalad/common/trade/tsquare/obj/cloak")->move(TO);
   clone_object("/d/Kalad/common/trade/cliffside/obj/zboots")->move(TO);   
   command("wield all");
   command("wear all");
}