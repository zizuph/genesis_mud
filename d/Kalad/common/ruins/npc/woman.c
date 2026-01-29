inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include  "/sys/money.h"
#include "/sys/filter_funs.h"
create_monster()
{
   set_name("woman");
   add_name("female");
   set_name("female");
   add_name("woman");
   set_race_name("human");
   set_adj("cleaning");
   set_short("female human");
   set_long("This is an ordinary housewife.\n");
   set_gender(1);
   set_stats(({15,15,15,10,10,15}));
   set_alignment(10);
   set_act_time(3);
   add_act("smile");
   add_act("say What can i help you with?");
   add_act("say Can you please leave my house.");
   add_act("emote looks for the guards.");
   set_cact_time(3);
   add_cact("say What have i done to you?");
   add_cact("say GUARDS!!!");
   add_speak("I'm just a housewife.\n");
   set_knight_prestige(10);
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
   MONEY_MAKE_SC(random(10))->move(this_object(),1);
   MONEY_MAKE_CC(random(10))->move(this_object(),1);
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
     command("shout Help! Help! Some " + obj->query_race_name() + 
     " is trying to kill me!");
   }
}
