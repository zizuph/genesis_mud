/*                                        */
/*    This is a typical Market guard.     */
/*                                        */
/*                    -Rico 13.12.94      */
/*                                        */

inherit "/d/Kalad/std/monster.c";

#include "/d/Kalad/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <money.h>

void arm_me();

create_monster()
{
   ::create_monster();

   set_name(({ "guard", "guardswoman" }));
   set_race_name("human");
   set_adj(({ "fearless", "stern" }));

   set_long("This guardswoman looks like she could cut you to "+
      "ribbons in the blink of an eye.  She has no fear in "+
      "her eyes, her stern face shows no kindness, neither "+
      "does it show any malice though.  You probably shouldn't "+
      "try her patience.\n");

   set_gender(G_FEMALE);  /* Make this particular guard female. */
   
   set_stats(({ 65, 75, 70, 45, 45, 80 })); 
        /* High dis to complement his description. */
   set_hp(1800);
   set_alignment(0);  /* This is standard, just shown for ref. */
   
   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_BLIND_COMBAT, 40);
   set_skill(SS_DEFENCE, 70);
   set_skill(SS_PARRY, 70);
   set_skill(SS_WEP_SWORD, 70);

   set_random_move(90);

   set_chat_time(3);
   add_chat("Don't be causin any trouble here abouts.\n");
   add_chat("got a spare smoke?\n");
   add_chat("Anybody causes any trouble and I'll cut em to "+
      "ribbons!\n");
   add_chat("I need a raise.\n");

   set_cchat_time(5);
   add_cchat("Now why'd you have to piss me off?\n");
   add_cchat("I'm gonna cut you to ribbons...\n");
   add_cchat("Ask for mercy and I might spare yer miserable "+
       "existence.\n");
   add_cchat("I told ya not to cause trouble...\n");

   set_act_time(4);
   add_act("sigh tiredly");
   add_act("emote blinks.");
   add_act("growl menacingly");
   add_act("yawn");
   add_act("stretch");

   set_cact_time(3);
   add_cact("growl");
   add_cact("spit");
   
   trig_new("%w 'smashes' 'your' %s", "react_smash");
   trig_new("%w 'hurts' 'your' 'very' 'bad' %s", "react_smash");

   set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
   object obj;
   
   setuid();
   seteuid(getuid());
   
   obj = clone_object(KALDORO(wep/gsword1.c));
   obj -> move(this_object());

   command("wield all");

   obj = clone_object(KALDORO(arm/gmail1.c));
   obj -> move(this_object());
   
   obj = clone_object(KALDORO(arm/gshield1.c));
   obj -> move(this_object());

   command("wear all");

   MONEY_MAKE_CC(random(45))->move(TO, 1);
   MONEY_MAKE_SC(random(45))->move(TO, 1);
}

int
react_smash(string who, string dummy)
{
   if(who)
   {
      who = lower_case(who);
      set_alarm(3.0, 0.0, "return_smash", who);
      return 1;
   }
}

void
return_smash(string who)
{
   object obj;
   int ran;

   if(obj = present(who, environment()))
   {
      command("say Damn you, " + obj->query_nonmet_name() + "!");
      command("emote grits her teeth in an effort to die honorably.");
   }
}
