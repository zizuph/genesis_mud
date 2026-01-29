/* The prisoner in the goblin caves near the Great Kalad Waste */
/* by Antharanos */
/* 
 * /d/Kalad/common/wild/pass/npc/prisoner.c
 * Purpose    : A kabal guard help prisoner by the goblins
 * Located    : /d/kalad/common/wild/pass/goblin/jail_cell
 * Created By : Antharanos ??.??.??
 * Modified By: 
 * 2017-06-04 Malus: Corrected messaging
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
object prisoner;
create_monster()
{
   ::create_monster();
   set_name("derwin");
   add_name("guard");
   set_race_name("human");
   set_adj("kabal");
   set_short("kabal guard");
   set_long("A tall, dark-haired man whose job is to insure the safety "+
      "of the great city of Kabal. Unfortunately for him, he was captured "+
      "by the Red Hand goblin tribe and has been languishing in this jail "+
      "cell for ages.\n");
   set_stats(({80,70,70,55,55,60}));
   set_alignment(300);
   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_DEFENCE, 75);
   set_skill(SS_AWARENESS,30);
   set_act_time(6);
   add_act("peer all");
   add_act("groan");
   set_cact_time(3);
   add_cact("moan");
   add_cact("say Why are you doing this?");
   add_cact("emote almost collapses from exhaustion.\n");
   add_speak("I've been rotting here for so long now, I wish I was "+
      "strong enough to destroy these accursed chains.\n");
   set_knight_prestige(-3);
   set_title("the Guardsman");
   set_default_answer("say I'm sorry, I didn't "+
      "understand that last question.", 1);
   add_ask(({"captain"}),"say That would be Hahmal.", 1);
   add_ask(({"quest"}),"say What quest?", 1);
   add_ask(({"task"}),"say What task? Before I was "+
      "captured, my task was to patrol the Caravan Route.", 1);
   add_ask(({"caravan route","route"}),"say That's the "+
      "city of Kabal's link with the interior of Kalad.", 1);
   add_ask(({"interior"}),"say I know nothing of what "+
      "lies there.", 1);
   add_ask(({"help"}),"say I'd greatly appreciate it "+
      "if someone freed me, perhaps you could do so.", 1);
   add_ask(({"freedom","chains","chain","how"}),
      "say If you are strong enough, perhaps you could destroy the "+
      "chains that hold me here.", 1);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("say Villanous retch! Die!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
destroy(string s)
{
    if(s!="chains"&&s!="chain"&&s!="the chains"&&s!="the chain") {
        notify_fail("Destroy what?\n");
        return 0;
    }
    seteuid(getuid(TO));
    TP->catch_msg("You attempt to break the chains.\n");
    if(TP->query_base_stat(SS_STR) > 80)
    {
        write("You broke the chains!\n");
        say(QCTNAME(TP) + " broke the chains!\n");
        write("The kabal guard thanks you" +
                " profusely and rushes out of the jail cell.\n");
        say("The kabal guard thanks " + QCTNAME(TP) + 
                " profusely and rushes out of the jail cell.\n");
        if(!TP->test_bit("Kalad",0,11)) {
            TP->add_exp(2000);
            TP->set_bit(0,11);
            TP->catch_msg("You feel more experienced!\n");
        }
        if(prisoner = present("derwin",environment(TP)));
        {
           prisoner -> remove_object();
        }
    } else {
        write("Nothing seems to happen.\n");
    }
   return 1;
}

init_living()
{
   ::init_living();
   add_action("destroy","destroy");
}
