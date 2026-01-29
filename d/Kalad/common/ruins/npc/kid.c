inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include  "/sys/money.h"
#include "/sys/filter_funs.h"
create_monster()
{
   set_name("kid");
   add_name("child");
   set_race_name("human");
   set_adj("little");
   set_short("little kid");
   set_long("This is the child of a common man..\n");
   set_gender(1);
   set_stats(({10,10,10,5,5,10}));
   set_alignment(10);
   set_act_time(3);
   add_act("grin");
   add_act("say Do you want to play?");
   add_act("say My daddy cleans the streets.");
   add_act("emote searches for his toys.");
   set_cact_time(3);
   add_cact("say Mommy? Help me!");
   add_cact("say I want my daddy!!!");
   add_speak("The small man from Kabal knows everything.\n");
   set_knight_prestige(20);
   set_alarm(1.0,0.0,"arm_me");
   trig_new("%w 'smashes' 'your' %s", "react_smash");
}
void
arm_me()
{
   object wep,arm;
   seteuid(getuid(this_object()));
/*
   arm = clone_object("/d/Kalad/common/zhent/arm/");
   arm -> move(this_object());
   command("wear all");
   wep = clone_object("/d/Kalad/common/zhent/wep/");
   wep -> move(this_object());
   command("wield all");
*/
   MONEY_MAKE_SC(random(5))->move(this_object(),1);
   MONEY_MAKE_CC(random(7))->move(this_object(),1);
}
int
react_smash(string who, string dummy){
   if(who){
      who = lower_case(who);
    set_alarm(3.0,0.0,"return_smash",who);
      return 1;
   }
}
void
return_smash(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("shout Ouch! Stop hurting me!!");
   }
}
