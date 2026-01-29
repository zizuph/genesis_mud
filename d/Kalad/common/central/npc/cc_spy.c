inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define QUEST_NAME "spyquest"
int kettle;
string long;
/* by Korat, parts borrowed from Antharanos */
create_monster()
{
   ::create_monster();
   set_name("shmion");
   add_name("spy");
   set_race_name("human");
   set_adj("silent");
   add_adj("sneaky");
   set_long("This is the City Councils intelligence officer. "+
      "He has the responsibility to make sure his employers "+
      "survives the political struggles of the City, and "+
      "to make some struggles too.\n");
   
   set_stats(({40,89,53,91,88,65}));
   set_alignment(0);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_AWARENESS,70);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_UNARM_COMBAT,60);
   
   add_prop(CONT_I_WEIGHT, 80000);  /* weights 80 kilo's */
   add_prop(CONT_I_HEIGHT, 180);
   set_hp(query_max_hp()); /* heal fully */
   set_title("The City Council intelligence officer");
   
   add_speak("I have a 'situation' on my hands. Maybe you can help me?\n");
   add_ask(({"situation","task","job","help"}),
      "The human says: Well, you see, my man has picked up "+
      "some rumours about the Lords cooking up problems. "+
      "I need some more... information. Ahh, I will say it plainly: Spy "+
      "on the Lords for me.\n");
   
   set_act_time(3);
   add_act(({"emote appraises you thoroughly.",
            "say Do you have some good info for me?",
            "smile hopefully"}));
   add_act("emote asks you: And where do you come from!");
   add_act("emote asks you: And who owns you!");
   add_act("emote asks you: And what can you do for me!");
   add_act("emote starts to leaf through the papers on his desk.");
   set_cact_time(1);
   add_cact("say You fool! You shall die now!");
   
   
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   set_knight_prestige(0);
   set_default_answer("The silent sneaky human says: In here I ask the "+
      "questions and you answer!\n");
   
}

void
arm_me()
{
   object wep, arm;
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/central/arm/spy_robe");
   arm -> move(TO);
   command("wear all");
}


public void
enter_inv(object ob, object from)
{
   object *content;
   if (MASTER_OB(ob) != "/d/Kalad/common/central/obj/spy_note")
      {
      ::enter_inv(ob, from);
      set_alarm(2.0,0.0,"drop_the_object",ob);
      return;
   }
   if (!interactive(from))
      return;
   else
      set_this_player(from);
   if (from->test_bit("Kalad", 1, 13))
      {
      write(query_The_name(from) + " peers at you and says: You have helped me enough; "+
         "I cannot accept more from you.\n");
      ob->remove_object();
      return;
   }
   ::enter_inv(ob, from);
   write("The human says: Ahh, now I understand!\n");
   command("emote gets a troubled look on his face.");
   TP->catch_msg("You feel more experienced.\n");
   TP->add_exp(1000);
   TP->set_bit(1,13);
   ob -> remove_object();
   seteuid(getuid(TO));
   log_file(QUEST_NAME, extract(ctime(time()),4,15) + " "+
      capitalize(TP->query_real_name()) + " rewarded with 1000 xp,"+
      "<"+TP->query_average_stat()+"> average stats.\n");
}


void
drop_the_object(object ob)
{
   command("scratch");
   if (MASTER_OB(ob) != "/d/Kalad/common/central/arm/spy_robe")
      command("drop "+ob->query_name());
}
