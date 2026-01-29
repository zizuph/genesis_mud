/*
 *  The mayor of Hobbiton, Bodo Proudfoot.
 */

#pragma save_binary

inherit "/std/monster";

#include "defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

do_bow(who);

do_smile(who);
do_re_frown(who);
do_re_nod(who);

create_monster()
{
   if (!IS_CLONE)
      return;
   set_name(({"mayor", "bodo proudfoot", "bodo"}));
   set_title("Proudfoot, the mayor of Hobbiton");
   set_race_name("hobbit"); 
   set_adj(({"important","looking"}));
   set_living_name("_hobbiton_mayor_");
   set_long("This person is the mayor of Hobbiton.\n");

            /* str dex con int wis dis */
   set_stats(({30, 35, 40, 27, 27, 27}));
   set_alignment(100);
   set_hp(10000); /* Heal fully */

   set_chat_time(5);
   add_chat("Welcome to our humble village!");
   add_chat("And isn't it a lovely day to go fishing?");
   add_chat("I heard there was some trouble at the water-mill.");
   add_chat("Have you seen young Frodo Baggins lately?");

   set_act_time(10);
   add_act("smile");
   add_act("giggle");
   add_act("chuckle");

   set_cact_time(10);
   add_cact("growl");
   add_cact("frown");
   add_cact("despair");

   set_cchat_time(5);
   add_cchat("No! Wait! I'm peaceful!");
   add_cchat("I will not tolerate this kind of behaviour!");
   add_cchat("Go away!");


   seteuid(getuid());
   clone_object(STAND_DIR + "hat")->move(this_object());
   command("wear hat");
}

add_introduces(string who)
{
   if (who) {
      who = lower_case(who);
      set_alarm(itof(3 + random(4)), 0.0, &do_bow(who));
      return 1;
   }
}

react_giggle(who,str) {
   if (who) {
      who = lower_case(who);
      set_alarm(itof(3 + random(4)), 0.0, &do_smile(who));
      return 1;
   }
}

react_frown(who,str) {
   if (who) {
      who = lower_case(who);
      set_alarm(itof(3 + random(4)), 0.0, &do_re_frown(who));
      return 1;
   }
}

react_nod(who,str) {
   if (who) {
      who = lower_case(who);
      set_alarm(itof(3 + random(4)), 0.0, &do_re_nod(who));
      return 1;
   }
}

do_bow(who) {
   object obj;

   if (obj = present(who, environment()))
   {
      command("bow to " + who);
      command("introduce myself");
   }
}

do_smile(who) {
   object obj;

   if (obj = present(who, environment()))
   {
      command("smile at " + who);
   }
}

do_re_frown(who) {
   object frownee;

   frownee = present(who, environment());
   if (frownee)
   {
      command("say Is something bothering you, " + frownee->query_nonmet_name()
             + "?");
   }
}

do_re_nod(who) {
   object noddee;
   int ran;

   if (noddee = present(who, environment()))
   {
      ran = random(6);
      if (ran == 0)
         command("say Ah, so you agree with me, " + noddee->query_nonmet_name()
             + "?");
      if (ran == 1)
         command("say I am glad someone also sees it that way!");
      if (ran == 2)
         command("pat " + who);
   }
}

public void
emote_hook(string emote, object who, string adj = 0)
{
    switch(emote)
    {
        case "giggle":
            react_giggle(who->query_real_name(), "");
            break;
        case "frown":
            react_frown(who->query_real_name(), "");
            break;
        case "nod":
            react_nod(who->query_real_name(), "");
            break;
    }
}
