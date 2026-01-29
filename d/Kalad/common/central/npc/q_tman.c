inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define RAG "/d/Kalad/common/central/obj/q_rag"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("hyuk");
   add_name("keeper");
   set_race_name("human");
   set_adj("mentally");
   add_adj("unbalanced");
   set_long("This strange-looking individual paces back and forth "+
      "across the room, shaking his hands as if he suffered from a palsy. "+
      "Every once in awhile he stops and stares at the bell.\n");
   set_stats(({25,20,15,20,20,30}));
   set_alignment(100);
   set_skill(SS_DEFENCE,10);
   set_act_time(3);
   add_act("emote stares at the bell.");
   add_act("say The bell must be cleaned!");
   add_act("shiver");
   add_act("say Woe is me! The bell must be cleaned!");
   add_act("emote madly rushes at you and begs you to clean the bell!");
   set_cact_time(3);
   add_cact("emote starts to drool.");
   add_act("grin crazily");
   add_speak("You must help me polish the bell!\n");
   set_title("the Keeper of the Bell Tower of Kabal");
   set_knight_prestige(-1);
   set_default_answer("The human says: No time! Must get the bell cleaned!\n");
   trig_new("%w 'polishes' 'the' 'great' 'bronze' 'bell.\n' %s","react_bell");
   set_alarm(1.0,0.0,"stuff");
}
void
stuff()
{
   object it;
   seteuid(getuid(TO));
   it = clone_object(RAG);
   it -> move(TO);
   MONEY_MAKE_CC(random(10))->move(TO,1);
}
int
react_bell(string who, string dummy)
{
   // Added hint so the the NPC acts if he cant see the player.
   // 26/6-2021 Meton
   if(who =="Someone")
   {
      command("say What is happening!?");
   }
   if(who)
   {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_bell",who);
      return 1;
   }
}

/* Ensure we really die! */
void
suicide()
{
    command("scream");

    set_hp(0);
    do_die(this_object());
}

void
return_bell(string who)
{
   object obj;
   int ran;

   if(obj = present(who, environment()))
   {
      command("cackle insanely");
      command("say Finally! Someone to help me clean the bell!");
      command("emote helps you clean the bell by jumping up onto your " +
         "shoulders and wiping the bell with a rag.");
      command("say Bye! I'm going to jump off the roof now!");
      command("say Oops, here you go, I won't be needing this anymore!");
      command("give rag to " + (obj->query_real_name()));
      command("wave " + (obj->query_real_name()));
      command("ne");
      command("jump");

      set_alarm(2.0, 0.0, &suicide());
   }

}
void
attacked_by(object ob)
{
   ::attacked_by(ob);
   command("scream");
   command("shout I'm gonna jump off the roof now!");
   command("ne");
   command("jump");

   set_alarm(2.0, 0.0, &suicide());
}
