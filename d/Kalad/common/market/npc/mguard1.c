/*                                         */
/*      A typical Market guardsman.       */
/*                                         */
/*                  -Rico 20.12.94         */
/*                                         */

inherit "/d/Kalad/std/monster.c";

#include "/d/Kalad/defs.h"

#include <ss_types.h>
#include <macros.h>
#include <money.h>

void arm_me();

create_monster()
{
   ::create_monster();
   
   set_name(({ "guard", "guardsman" }));
   set_race_name("human");
   set_adj(({ "experienced", "bored" }));
   set_adj(({ "experienced", "stern", "rough" }));
   
   set_long("This guardsman looks like he could cut you to "+
      "ribbons in the blink of an eye.  He has no fear in "+
      "his eyes, his stern face shows no kindness, neither "+
      "does it show any malice, though.  You probably "+
      "shouldn't try his patience.\n");

   set_gender(G_MALE);  /* Make this particular guard male.  */
   
   set_stats(({ 75, 70, 70, 45, 45, 80 }));
   /*  High dis to compliment his description. */
   set_hp(1800);
   set_alignment(0);  /* This is standard, just for ref. */
   
   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_BLIND_COMBAT, 30);
   set_skill(SS_DEFENCE, 70);
   set_skill(SS_PARRY, 70);
   set_skill(SS_WEP_SWORD, 70);
   set_skill(SS_AWARENESS, 20);

   set_random_move(90);
   
   set_chat_time(3);
   add_chat("Don't be causin any trouble here abouts, pal.\n");
   add_chat("Got a spare smoke?\n");
   add_chat("Anybody causes any trouble and I'll tear em limb "+
      "from limb....slowly.\n");
   add_chat("I need a raise.\n");
   
   set_cchat_time(5);
   add_cchat("Now why'd you have to piss me off?\n");
   add_cchat("I'm gonna cut you to ribbons...\n");
   add_cchat("Ask for mercy and I might spare yer miserable "+
      "existence.\n");
   add_cchat("I told ya not to cause trouble...\n");
   
   set_act_time(4);
   add_act("sigh tiredly");
   add_act("snarl");
   add_act("growl menacingly");
   add_act("spit");
   add_act("yawn");
   add_act("stretch");

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

   obj = clone_object(KALDORO(wep/gsword1));
   obj -> move(this_object());

   command("wield all");

   obj = clone_object(KALDORO(arm/gmail1));
   obj -> move(this_object());
   obj = clone_object(KALDORO(arm/gshield1));
   obj -> move(this_object());

   command("wear all");

   MONEY_MAKE_SC(random(50))->move(TO, 1);
   MONEY_MAKE_CC(random(85))->move(TO, 1);
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
      command("emote grits his teeth in an effort to die honorably.");
   }
}

