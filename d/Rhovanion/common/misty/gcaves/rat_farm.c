/*
 * Rat farm in Goblin caves
 * Milan March 1994
 * modified from:
 *  Shop in Minas Morgul
 *  Olorin, July 1993
 *  copied from:
 *  Bendar's General Store in Edoras
 *  rewritten by Olorin                   may 1993
 *  - use /lib/shop  - copied from ranger guild shop
 *  modified by Olorin                   feb 1993
 *  after ideas by Hamurabbi
 *  after the Hobbiton drug store by
 *                               Tricky, dec 1991
 */


inherit "/d/Rhovanion/common/misty/gcaves/room";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"

#define CAVE_DIR  (MISTY_DIR+"gcaves/")
#define PRICE     30
#define GAVE_RAT  "_player_gave_rhun_rat"

object ratkeeper;

void create_cave()
{
  config_default_trade();  /* Set up the trading system */

  set_short("Rat farm");
  set_long("You are at the end of the tunnel that burrow under the Misty "
    + "Mountains. It is very humid and the walls are damp with condensed "
    + "water.  You seriously hope that you are not lost because every "
    + "tunnel looks much the same as the last...\n"
    + "But this one is slightly different. There is a big cage here "
    + "full of rats. No wonder because one greedy goblin made rat "
    + "farm here. He trains rats to deliver messages and he hopes that "
    + "he can make living on it. He has put a poster which you "
    + "may be able to read.\n");

  add_item("poster","Maybe you are literate enough to read it.\n");
  add_cmd_item("poster","read","@@read_poster");
  add_item("cage","It is massive iron cage full of dirty rats.\n");
  add_item("rats","You see many black dirty rats inside the cage.\n");

  add_exit(CAVE_DIR+"t29", "east");
}

string read_poster()
{
  if(!CAN_SEE_IN_ROOM(TP)) return "It is too dark to see.\n";
  return "\n" +
         "          **********************************\n" +
         "          *                                *\n" +
         "          *  Nice rats for hire!           *\n" +
         "          *                                *\n" +
         "          *  Do you want to send message?  *\n" +
         "          *  Then this is unique chance    *\n" +
         "          *   for you!                     *\n" +
         "          *                                *\n" +
         "          *    Hire rat!!!                 *\n" +
         "          *                                *\n" +
         "          * Note: Prices may vary. Ask me! *\n" +
         "          *                                *\n" +
         "          **********************************\n\n";
}

void init()
{
    ::init();
    add_action("hire_rat", "hire");
    add_action("open_cage", "open");
    add_action("unlock_cage", "unlock");
    add_action("get_rat_from_cage", "get");
    add_action("get_rat_from_cage", "pick");
}

int get_rat_from_cage(string arg)
{
  if(!CAN_SEE_IN_ROOM(TP))
    NF("It is too dark to get things.\n");
  if((arg == "rat from cage") || (arg == "rats from cage") ||
     (arg == "all from cage"))
    NF("Cages are closed so you can't get to the rats.\n");
  return 0;
}

int open_cage(string arg)
{
  NF("It is too dark to see.\n");
  if(!CAN_SEE_IN_ROOM(TP)) return 0;
  NF("Open what?\n");
  if(!arg || (arg != "cage")) return 0;
  say(QCTNAME(TP)+" tries desperately open the locked cage but it "+
      "remains closed.\n");
  TP->catch_msg("You try desperately open the locked cage but it "+
                "remains closed.\n");
  if(ratkeeper && present(ratkeeper,TO))
  {
    ratkeeper->command("knee "+TP->query_real_name());
    ratkeeper->command("shout Don't mess with my cages!!!");
  }
  return 1;
}

int unlock_cage(string arg)
{
  NF("It is too dark to see.\n");
  if(!CAN_SEE_IN_ROOM(TP)) return 0;
  NF("Unlock what?\n");
  if(!arg) return 0;
  if(explode(arg+" "," ")[0] != "cage") return 0;
  say(QCTNAME(TP)+" tries unlock "+arg+" but it doesn't seem to work.\n");
  TP->catch_msg("You try to unlock "+arg+" but it doesn't seem to work.\n");
  if(ratkeeper && present(ratkeeper,TO))
  {
    ratkeeper->command("tackle "+TP->query_real_name());
    ratkeeper->command("shout I will really kill you!!!");
    ratkeeper->command("kill "+TP->query_real_name());
  }
  return 1;
}

void reset_room()
{
  if(ratkeeper)
  {
    if(present(ratkeeper,TO)) return;
    ratkeeper->command("shout Ohh... nearly forgot my rats!");
    ratkeeper->move_living("runs away.",TO);
    tell_room(TO, QCTNAME(ratkeeper)+" rushes in.\n");
    ratkeeper->command("say Are my rats O.K.?");
    return;
  }
  ratkeeper = clone_object(NPC_DIR + "goblins/ratkeeper.c");
  ratkeeper->arm_me();
  ratkeeper->move(TO,1);
  tell_room(TO, QCTNAME(ratkeeper)+" rushes in.\n");
  ratkeeper->command("say Back in bussiness...");
}

int check_ratkeeper()
{
  object enemy;
  string who;

  if (ratkeeper && present(ratkeeper,TO))
  {
    who = TP->query_nonmet_name();
    if(ratkeeper->query_introduced(TP))
       who = TP->query_name();
    if(enemy = ratkeeper->query_attack())
    {
      if(enemy == TP)
      {
        ratkeeper->command("say Now you want to hire something? Wait till "+
                        "I kill you!");
        ratkeeper->command("ponder stupid "+who);
      }
      else
      {
        ratkeeper->command("say Please "+who+"! You must wait untill I kill "+
                        "this coward "+enemy->query_nonmet_name()+"! "+
                        "Maybe you can help me too?");
        ratkeeper->command("wink "+TP->query_name());
      }
      return 0;
    }
    else
      return 1;
  }
  else
  {
    TP->catch_msg("There is no ratkeeper here, so you can't do that!\n");
    return 0;
  }
}

int check_intro()
{
  if(ratkeeper->query_introduced(TP)) return 1;
  ratkeeper->command("say If you want hire something then you should at "+
                     "least introduce yourself!");
  ratkeeper->command("say Yes you bastard! I mean you "+
                      TP->query_nonmet_name()+"!");
  return 0;
}

int check_light()
{
  if(CAN_SEE_IN_ROOM(ratkeeper)) return 1;
  ratkeeper->command("say I am sorry "+TP->query_name()+" but I can't work "+
                  "when I can't see.");
  ratkeeper->command("sigh");
  return 0;
}

int query_hire_price(object who)
{
   int bargain;

   bargain = TP->query_skill(SS_TRADING);
   if(bargain > 30) bargain = 30;
   bargain = 115 - bargain;

   if(TP->query_race_name() == "goblin")
     return ((PRICE * bargain * 85) / 10000);
   return ((PRICE * bargain * 120) / 10000);
}

int hire_rat(string arg)
{
  int price, *arr, error, num;
  object post_rat;

  NF("Hire what?\n");
  if(arg != "rat") return 0;

  if(!check_ratkeeper()) return 1;
  if(!check_intro()) return 1;
  if(!check_light()) return 1;

  if((TP->query_prop(GAVE_RAT) == 1) && (!TP->test_bit("Rhovanion",0,11)))
  {
    ratkeeper->command("say I am short of rats now... Need some fresh blood.");
    ratkeeper->command("say Bring me one fresh rat and I will hire you more.");
    ratkeeper->command("say Best rats for training are around sea of Rhun.");
    ratkeeper->command("say And when you are there you may help my nephew. "+
                       "He will reward you for that.");
    return 1;
  }

  price = query_hire_price(TP);
  num = sizeof(query_money_types());

  if (sizeof(arr = pay(price, TP, "", 0, 0, "")) == 1)
  {
    ratkeeper->command("say You must have money first "+TP->query_name()+
                    " and only then you can hire my nice rats.");
    return 1;
  }
  if (error = arr[sizeof(arr) - 1])
  {
    if (error < -1)
    {
      ratkeeper->command("say You are carrying magic money "+QCNAME(TP)+
                      ", no deal!");
      return 1;
    }
  }
  TP->catch_msg("You give "+text(arr[0 .. num - 1])+" to "+
                QTNAME(ratkeeper)+".\n");
  say(QCTNAME(TP)+" gives "+text(arr[0 .. num - 1])+" to "+
      QTNAME(ratkeeper)+".\n");
  if (text(arr[num .. 2 * num - 1]))
  {
    TP->catch_msg("He gives you "+text(arr[num .. 2 * num - 1])+" back.\n");
    say(QCTNAME(ratkeeper)+" gives "+text(arr[num .. 2 * num - 1])+" to "+
        QTNAME(TP)+".\n");
  }
  TP->catch_msg(QCTNAME(ratkeeper)+
                " gets a rat from the cage and gives it to you.\n");
  say(QCTNAME(ratkeeper)+" gets a rat from cage and gives it to "+
      QTNAME(TP)+".\n");

  post_rat = clone_object(NPC_DIR+"post_rat");
  if (post_rat->move(TP))
  {
    post_rat->move(TO);
    ratkeeper->command("say Seems that you can't hold it.");
    ratkeeper->command("comfort "+TP->query_name());
  }
  if(!TP->query_prop(GAVE_RAT)) TP->add_prop(GAVE_RAT,1);
  return 1;
}
