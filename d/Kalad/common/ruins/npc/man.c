inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include  "/sys/money.h"
#include "/sys/filter_funs.h"
create_monster()
{
   set_name("man");
   set_race_name("human");
   set_adj("common");
   set_short("normal man");
   set_long("This is a normal man from Zhentil Keep.\n");
   set_gender(0);
   set_stats(({20,20,20,15,15,20}));
   set_alignment(10);
   set_act_time(3);
   add_act("grin");
   add_act("say Leave my house.");
   add_act("say I don't believe i invited you in.");
   add_act("emote scratches his head.");
   set_cact_time(3);
   add_cact("say DIE WORM!");
   add_cact("say I think you made a mistake.");
   add_speak("Why should i tell you anything?.\n");
   set_knight_prestige(20);
   set_alarm(1.0,0.0,"arm_me");
   trig_new("%w 'smashes' 'your' %s", "react_smash");
}
void
arm_me()
{
   seteuid(getuid(this_object()));
   MONEY_MAKE_SC(random(15))->move(this_object(),1);
   MONEY_MAKE_CC(random(20))->move(this_object(),1);
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
	command("shout You bastard!!");
   }
}

