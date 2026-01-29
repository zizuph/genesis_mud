	inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
create_monster()
{
   ::create_monster();
   set_name("lars");
   set_race_name("human");
   add_name("thief");
   add_adj("shifty-eyed");
   add_adj("scrawny");
   set_short("shifty-eyed scrawny thief");
   set_pshort("shifty-eyed scrawny thieves");
   set_long("This guy watches you with a slight smile. He is "+
   "very skinny looking, as if he hasn't eaten in months. His "+
   "eyes are sharp, and he squints slightly, looking from side "+
   "to side.\n");
   set_stats(({50,110,50,50,90,60}));
   add_speak("You are getting closer to your death...\n");
   set_skill(SS_DEFENCE,70);
   set_skill(SS_PARRY, 75);
   set_skill(SS_WEP_KNIFE,85);
   set_act_time(6);
   add_act("emote grips the handle of his knife tightly.");
   add_act("emote smiles thinly.");
   add_act("say Beware of the those who carry the Black Rose!");
   add_act("scratch chin");
   add_act("say I hate guard duty...all those purses I am missing out in "+
   "cutting...");
   set_chat_time(6);
   add_cchat("RaaaaaarrrrggghH!");
   add_cchat("Feel my blade worm!");
   add_cchat("You will be the next victim of the Shadow Walkers!");
   add_cchat("Why do you persist?");
   add_cchat("You can't beat a thief from the Shadow Walkers!");
   set_cact_time(1);
   set_title("the Feared Arsonist");
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
   object bomb;
   seteuid(getuid(TO));
   clone_object("/d/Kalad/common/trade/tsquare/obj/tdag")->move(TO);
   clone_object("/d/Kalad/common/guilds/shadow_walkers/silk_tunic")->move(TO);
   clone_object("/d/Kalad/common/trade/tsquare/obj/cloak")->move(TO);
   clone_object("/d/Kalad/common/trade/cliffside/obj/zboots")->move(TO);   
   bomb = clone_object("/d/Kalad/common/guilds/shadow_walkers/fire_bomb");
   bomb->set_fire_str(200);
   bomb->move(TO);
   command("wield all");
   command("wear all");
}

void
do_die(object ob)
{
    command("emote hisses: You will pay!!");
    command("ignite bottle");
    command("drop bottle");
    ::do_die(ob);
}
