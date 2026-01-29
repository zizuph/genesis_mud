inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/money.h"
/* basics by Antharanos, modified by Korat */
   create_monster()
{
   ::create_monster();
   set_name("officer");
   add_name("militia officer");
   set_race_name("human");
   set_adj("militia");
   add_adj("officer");
   set_long("This man is an excellently trained elite guard, paid to "+
      "protect the plaza and the streets around it."+
      " He also commands the guardsmen.\n");
   set_stats(({80,100,95,60,60,80}));
   set_alignment(0);
   set_skill(SS_WEP_SWORD,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,60);
   set_skill(SS_AWARENESS,60);
   set_skill(SS_2H_COMBAT,70);
   set_aggressive(0);
   set_act_time(12);
    add_act(({"say I expect you to be peaceful here in the plaza "+
      "area!","emote salutes you."}));
   add_act(({"say Well, don't just stand here! Move on...","smirk"}));
   add_act(({"emote adjusts his armours.","sigh relieved"}));
   set_cact_time(6);
   add_cact("say How dare you to attack me! It will mean your death!");
   add_cact("say You shouldn't have disturbed us. It will mean your "+
      "death!");
   add_cact(({"say Wanna taste something sweet?",
      "emote licks his sword, tasting the blood.","grin"}));
    add_cact("emote thinks hard about how pleased the Lord will be "+
      "when he can report to have killed some ruffians.");
   set_knight_prestige(0);
   set_default_answer("All I know is that I have a job to do.\n");
   add_speak("Nice chatting with you, but I have work to do.\n");
}
void
arm_me()
{
   object wep, arm;
   seteuid(getuid(this_object()));
   arm = clone_object("/d/Kalad/common/central/arm/militia_plate");
   arm -> move(this_object());
   arm = clone_object("/d/Kalad/common/central/arm/militia_helm");
   arm -> move(TO);
   command("wear all");
   wep = clone_object("/d/Kalad/common/central/wep/militia_sword");
   wep -> move(this_object());
   command("wield all");
   MONEY_MAKE_GC(random(5))->move(this_object(),1);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("grin");
      command("say Ahhh, finally....");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
