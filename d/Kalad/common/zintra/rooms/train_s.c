
/*
      This is the training room for the Order of Solomon.

      => Will be updated. <=             ~Rico 12.04.96
*/

inherit "/d/Kalad/room_std";
inherit "/lib/trade";
inherit "/lib/skill_raise";

#include "/d/Kalad/common/zintra/defs.h"
#include <ss_types.h>

#define MEMBER(ob)     ob->test_bit("Kalad", 0, 9)
#define ZSERVER        "/d/Kalad/common/zintra/specials/server"

void   set_up_skills();
string *train_text(int skill);

void 
create_room()
{
   set_short("A dimly lit chamber.");
   set_long("\n"+
      "This is the training area for Assassins of the Order of Kolnari.  "+
      "There various weapons of death strategically placed throughout the "+
      "chamber.  They are obviously for training purposes.  There is a "+
      "High BlackHand of Kolnari here.  He is willing to instruct you in "+
      "various arts of assassination.  "+
      "\n\n");

   add_item(({ "weapons", "weapons of death" }), "\n"+
      "Though well maintained, these deadly instruments are for training "+
      "purposes only.\n\n");

   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 1);

   add_exit(VILL_DIR + "b8", "southwest", 0);

   config_default_trade();

   set_up_skills();
}

init()
{
   ::init();

   init_skill_raise();
}

int
sk_query_max(int skill)
{
   return ::sk_query_max(skill);
}

void set_up_skills()
{
   create_skill_raise();

   sk_add_train(SS_THRUST train_text(SS_THRUST), "lunge", 100, 100, 2);
   sk_add_train(SS_ZKICK, train_text(SS_ZKICK), "smashing high kick", 100, 100,1);
   sk_add_train(SS_AWARENESS, train_text(SS_AWARENESS), "awareness", 0, 60);
   sk_add_train(SS_BLINDFIGHTING, train_text(SS_BLINDFIGHTING), "blindfighting", 0, 75);
   sk_add_train(SS_UNARM_COMBAT, train_text(SS_UNARM_COMBAT), "unarmed combat", 0, 90);
   sk_add_train(SS_DEFENSE, train_text(SS_DEFENSE), "defense", 0, 90);
   sk_add_train(SS_PARRY, train_text(SS_PARRY), "parry",0, 90);
   sk_add_train(SS_TRACKING, train_text(SS_TRACKING), "tracking",0, 50);
   sk_add_train(SS_WEP_KNIFE, train_text(SS_WEP_KNIFE), "knife",0, 90);
   sk_add_train(SS_WEP_AXE, train_text(SS_WEP_AXE), "axe",0, 90);
   sk_add_train(SS_2H_COMBAT, train_text(SS_2H_COMBAT), "two handed combat",0, 75);
}

string *train_text(int skill)
{
   string what, does, *text;

   switch (skill) 
   {
      case SS_THRUST:
         what = "lunge at an opponent";
         does = what;
      break;
   
      case SS_ZKICK:
         what = "throw a smashing high kick";
         does = what;
      break;

      case SS_UNARM_COMBAT:
         what = "fight whilst unarmed";
         does = what;
      break;

      case SS_AWARENESS:
         what = "be aware of your surroundings";
         does = what;
      break;

      case SS_BLINDFIGHTING:
         what = "fight in complete darkness";
         does = what;
      break;

      case SS_DEFENSE:
         what = "defend against attacks";
         does = what;
      break;

      case SS_PARRY:
         what = "parry against attacks";
         does = what;
      break;

      case SS_TRACKING:
         what = "interpret tracks";
         does = what;
      break;

      case SS_WEP_KNIFE:
         what = "fight wielding a knife";
         does = what;
      break;

      case SS_WEP_AXE:
         what = "fight wielding an axe";
         does = what;
      break;
 
      case SS_2H_COMBAT:
         what = "fight with two wielded weapons";
         does = what;
      break;

      default:
         what = "do nothing. THIS IS A BUG. Mail your guildmaster ASAP";
         does = "meditate";
      break;
   }

   text = ({ what, does });

   return text;
}

void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
   string rank, 
          long_str;

   rank = sk_rank(to_lev);

   this_player()->catch_msg("You improve your ability to " +
                             sk_tdesc[snum][0] + ".\n" +
                             "You achieve the rank of " +
                             rank + ".\n");

   long_str = " improves " + this_player()->query_possessive() +
              " ability to " + sk_tdesc[snum][1] + " and receives "+
              "the rank of " + rank + ".\n";

   say(({ break_string(this_player()->query_Met_name() + long_str, 76),
          break_string(capitalize(this_player()->query_unmet_name())+ 
          long_str, 76) }) );
}

int
sk_improve(string sk)
{
   if (!MEMBER(TP))
   {
      notify_fail("You are NOT an assassin.  You can't "+
         "train here.\n");

      if (sk)
         return 0;
 
      write("Only the members of the Order of Solomon may train here.\n");
   }

   if (ZSERVER->query_order_name(TP->query_real_name()) != "solomon")
   {
      notify_fail("You are not of the Order of Solomon.  You are not "+
         "permitted to train here.\n");

      return 0;
   }

   return ::sk_improve(sk);
}

