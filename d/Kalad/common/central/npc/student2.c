/* a training gladiator */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/money.h"
/* by Korat */
create_monster()
{
   ::create_monster();
   set_name("porkin");
   set_race_name("dwarf");
   set_adj("tall");
   set_long("This man is a fairly fresh gladiator that has come here to train "+
      "in using his axe.\n");
   set_stats(({40,50,35,20,20,35}));
   set_alignment(0);
   set_skill(SS_WEP_AXE,25);
   set_skill(SS_UNARM_COMBAT,10);
   set_skill(SS_DEFENCE,30);
   set_skill(SS_PARRY,10);
   set_skill(SS_AWARENESS,5);
   set_act_time(4);
   add_act("emote tries to slash the wooden pole with a double strike.");
   add_act("swear");
   add_act(({"sob","say Why can't I get that strike right??!"}));
   add_act("emote hits the pole hard with his axe, but looses the grip on it. "+
      "The axe hits the wall hard. After some swearing he picks it up again.");
   add_act("emote swings his axe by purpose above the pole and tries to use the "+
      "momentum to swing around and slash the lower part of the pole, but he "+
      "looses his footing and falls down hard on the mat.\n");
   add_act("emote uses the flat side of his axe to club down on the pole, while "+
      "kicking hard with his right foot; and succeeds!"); 
   set_cact_time(1);
   add_cact("say Hey! This is a place for training!! Stop this.");
   add_cact(({"say you have got this all wrong!","emote tries to avoid your"+
            "hits.","scream"}));
   add_cact("say I will kill you! So you better leave now!");
   set_knight_prestige(0);
   set_title("the trainee Gladiator of Kalad");
   add_speak("Shut up will you? Im paying for this!\n");
   set_default_answer("Sorry, I am paying to train here...so don't disturb!\n");
   set_alarm(0.0,0.0,"arm_me");
}
void
arm_me()
{
   object wep,arm;
   seteuid(getuid(this_object()));
   arm = clone_object("/d/Kalad/common/central/arm/collar");
   arm -> move(TO);
   command("wear all");
   wep = clone_object("/d/Kalad/common/central/wep/wdaxe");
   wep -> move(this_object());
   command("wield all");
   MONEY_MAKE_CC(random(30))->move(this_object(),1);
}

