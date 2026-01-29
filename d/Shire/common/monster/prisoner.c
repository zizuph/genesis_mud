/*
 *  The prisoner of the orcs
 *  Cloned by ~Shire/common/hobbiton/tent
 */

inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/language.h"
#include "/d/Shire/common/defs.h"

int tied_up;
void make_noise(object tp);

create_monster()
{
   seteuid(getuid());
   if (!IS_CLONE)
      return;

   set_name(({"_orc_prisoner_", "prisoner","human"}));
   set_adj(({"old","imprisoned"}));
   set_race_name("human"); 
   set_long(break_string(
     "You are looking at a poor human who was caught by the orcs and "
   + "kept by their leader for questioning. You wonder why, because "
   + "orcs are known not to waste time when it comes to killing.\n",70));

   add_item("bonds", "The old human is tied up with some bonds.\n");

   add_prop(CONT_I_WEIGHT,102000);  /* 102 Kg */
   add_prop(CONT_I_HEIGHT,183);     /* 183 cm */

            /* STR DEX CON INT WIS DIS */
   set_stats(({ 43, 21, 57, 21, 25, 99}));
   set_hp(10000); /* Heal fully */
   set_skill(SS_UNARM_COMBAT,20);
   set_skill(SS_DEFENCE,20);

   /* Actions */
   set_act_time(5);
   add_act("sigh");
   add_act("sniff");

   set_chat_time(5);
   add_chat("Please untie me!");
   add_chat("These bonds hurt!");

   /* Combat chat-strings */
   set_cchat_time(5);
   add_cchat("I am already almost dead!");
   add_cchat("Don't beat me, please!");
   add_cchat("Haven't I suffered enough?");

   add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet him */
}

init_living() {
   if (this_player()->query_npc())
      return;

   add_action("do_untie","untie");
   add_action("do_untie", "free");
   add_action("do_untie", "release");
   set_alarm(2.0,0.0, &make_noise(this_player()));
}

make_noise(tp) {
   int ran;

   ran = random(3);
   if (ran == 0)
      command("say Help at last!");
   else if (ran == 1)
      command("say Please help me!");
   else if (ran == 2)
      command("say The gods be praised, "
            + LANG_ADDART(tp->query_race()) + "!");

}

do_untie(str) {
   object tp;
   object orc_leader;

   if (id(str))
   {
      tp = this_player();
    if(present("_leader_orc_",ENV(TO)))
      {
         write("The orc leader won't let you near the prisoner.\n");
         return 1;
      }
      else
      {
         write("You untie the bonds and free the old human.\n");
         say(QCTNAME(tp) + " unties the bonds of the old human.\n");
         command("say I knew I could count on you, " + tp->query_race()
               + ".\n");

         /* Invent a new property to check if one has solved the quest */
         if (tp->query_prop("_freed_orc_prisoner_"))
         {
            command("say I am eternally grateful, " + tp->query_race() + ".");
            command("thank " + tp->query_real_name());
         }
         else
         {
            /* Property == 2 means she hasn't taken the book yet */
            tp->add_prop("_freed_orc_prisoner_",2); 

            command("say I will tell you the information they tried to "
                  + "get out of me.\n");
            command("whisper " + tp->query_real_name()
                  + " Go out, west and dig there.");
            command("whisper " + tp->query_real_name()
                  + " That is where I buried my treasure.");
         }
         command("say Now I have to run.");
         tell_room(environment(), "The old human runs away.\n");
         remove_object();
         return 1;
      }
   }
}

/* For the solamnic Knights */

query_knight_prestige() { return(-2); }
