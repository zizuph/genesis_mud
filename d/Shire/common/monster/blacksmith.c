/*
 *  The blacksmith, who can sell some swords and perhaps slightly
 *  improve weapons.
 *  Cloned by both ~Shire/common/hobbiton/forge and ~Genesis/start/hobbit/v/forge
 *
 *  2005/01/28 ? - Last update
 *  2011/07/18 Lavellan - Fixed reset, race, sell-fail adding to sold list,
 *      trigs->hooks, removed unused features
 */

inherit "/std/monster";
inherit "/lib/trade";

#include "defs.h"
#include "tobacco.h"
#include "/sys/money.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

#define MY_KNIFE  (STAND_WEAPON + "sell_knife")
#define MY_AXE    (STAND_WEAPON + "sell_axe")
#define MY_SWORD  (STAND_WEAPON + "sell_sword")
#define MY_SHOVEL (STAND_OBJ + "shovel")

string pay_type, get_type, coin_pay_text, coin_get_text, *sold_arr;
int *money_arr;

void return_sigh(object who);
void return_smile(object who);

create_monster()
{
   if (!IS_CLONE)
      return;

   set_name(({"smith","hobbit","blacksmith"}));
   //set_race_name("blacksmith"); 
   set_short("blacksmith");
   set_race_name("hobbit");
   set_living_name("_blacksmith_");
   //set_long(break_string(
   set_long(
      "This is the blacksmith of Hobbiton. Hobbits are known to be "
    + "very bad with tools and machinery, and even dislike them, but "
//    + "this fellow is an exception to that rule.\n",70));
    + "this fellow is an exception to that rule.\n");

   add_prop(CONT_I_WEIGHT,40000);   /* 40 Kg */
   add_prop(CONT_I_HEIGHT,82);      /* 82 cm */
   add_prop(LIVE_I_NEVERKNOWN,1);

            /* str dex con int wis dis */
   set_stats(({ 22, 27, 23, 12, 14, 12}));
   set_skill(SS_UNARM_COMBAT, 70);
   set_skill(SS_DEFENCE, 47);
//   set_pick_up(75);
    clone_tobacco();

   set_aggressive(0);
   set_attack_chance(0);

   set_chat_time(5 + random(6));
   add_chat("Can I be of any help to you?");
   add_chat("Phoooey! It is hot in here...");

   set_cchat_time(3 + random(6));
   add_cchat("Ha! You chose the wrong one to attack!");
   add_cchat("Please wait a moment or I will get really mad!");
   add_cchat("Who do you think you are?!?");

   /* Triggers */
   //trig_new("%s 'smiles' %s", "react_smile");
   //trig_new("%s 'sighs' %s", "react_sigh");

   /* Set up the trading system */
   config_default_trade();
                         /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,   100, 100,  100 })); /* Max_pay   */
   set_money_give_reduce(({     0,     0,   0,    0 })); /* Threshold */

   reset_monster();
   enable_reset();
}

reset_monster() {
   sold_arr = ({ });
}

init_living() {
   add_action("do_buy","buy",0);
/*
   add_action("do_wax","wax",0);
*/
   /*   Never implemented? - Lavellan
   add_action("do_sharpen","sharpen",0);
   add_action("do_straighten","straighten",0);
   add_action("do_harden","harden",0);
   */
}

/********************************************************************
 *
 * Player commands
 */

#define KNOWN_RACES ({ "dwarf","elf","gnome","goblin","hobbit","human" })

#define RACE_KNIFE_TXT ({ "good enough", \
			  "a little too small", \
			  "just about the right size", \
			  "too delicate", \
			  "especially made", \
			  "perhaps too small" })

#define RACE_AXE_TXT ({ "especially made", \
			"a bit clumsy", \
			"probably the right size", \
			"made", \
			"probably too hard to handle", \
			"good enough" })

#define RACE_SWORD_TXT ({ "a little too big", \
			  "just about the right size", \
			  "too delicate", \
			  "especially made", \
			  "too big", \
			  "especially made" })

do_buy(str) {
   int i;
   object weap;
   string item;

   if (!str)
      return 0;

 /*   Check if the player defines what she wants to pay with
  *   and what you would like in return.
 */
   if (sscanf(str, "%s for %s and get %s",item,pay_type,get_type) != 3)
   {
      get_type = "";
    /* Hmmm... Maybe she only wishes to pay with a certain type */
      if (sscanf(str, "%s for %s", item, pay_type) != 2)
      {
         pay_type = "";
         item = str;
      }
   }

   item = lower_case(item);
   if (item != "knife" && item != "axe" && item != "sword" && item != "shovel")
   {
      command("say I don't have any " + item + " for sale, "
            + this_player()->query_race() + ".");
      return 1;
   }
   if (member_array(str, sold_arr) >=0)
      command("say Sorry, I have sold all " + LANG_PWORD(item) + "!");
   else
   {
      if ((i = member_array(this_player()->query_race(),KNOWN_RACES)) < 0)
         i = 2;		/* Equal the player to a gnome if unknown race */

      if (item=="knife" &&
          can_afford(MY_KNIFE->query_prop(OBJ_I_VALUE)*2,item))
      {
         command("say Here you go, this is a good, sharp knife.");
         weap = clone_object(MY_KNIFE);
         weap->move(this_object());
         command("give " + weap->query_name() + " to "
               + this_player()->query_real_name());
         command("drop " + weap->query_name()); /* Drop if give went wrong */
         command("say To me it seems " + RACE_KNIFE_TXT[i] + " for you.");
         sold_arr += ({ item });
      }
      else if (item == "axe" &&
               can_afford(MY_AXE->query_prop(OBJ_I_VALUE)*2,item))
      {
         command("say Here you have a sturdy axe.");
         weap = clone_object(MY_AXE);
         weap->move(this_object());
         command("give " + weap->query_name() + " to "
               + this_player()->query_real_name());
         command("drop " + weap->query_name());
         //"It must have been probably the right size for you"?? No. - Lavellan
         //command("say It must have been " + RACE_AXE_TXT[i] + " for you.");
         command("say I'd say it's " + RACE_AXE_TXT[i] + " for you.");
         sold_arr += ({ item });

      }
      else if (item == "sword" &&
               can_afford(MY_SWORD->query_prop(OBJ_I_VALUE)*2,item))
      {
         command("say You are now the owner of this mediocre sword.");
         weap = clone_object(MY_SWORD);
         weap->move(this_object());
         command("give " + weap->query_name() + " to "
               + this_player()->query_real_name());
         command("drop " + weap->query_name());
         command("say It seems to be " + RACE_SWORD_TXT[i] + " for you.");
         sold_arr += ({ item });
      }
      else if (item == "shovel" &&
               can_afford(MY_SHOVEL->query_prop(OBJ_I_VALUE)*2,item))
      {
         command("say Aaah, going to do some digging, eh?");
         weap = clone_object(MY_SHOVEL);
         weap->move(this_object());
         command("give " + weap->query_name() + " to "
               + this_player()->query_real_name());
         command("drop " + weap->query_name());
         command("say There you go.");
         sold_arr += ({ item });
      }
   }
   return 1;
}

/*
 *  Test if this_player can afford the price, and perform
 *  the money transactions.
 */
can_afford(price, weap) {
 /* Try to take the money */
   if (sizeof(money_arr = pay(price, this_player(), pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 2)
      {
         command("say You have not got any " + pay_type
          + " coins, " + this_player()->query_race()
          + ".");
         return 0;
      }
      if (money_arr[0] == 1)
      {
         command("say I think that " + weap + " is too "
          + "expensive to pay for in " + pay_type + " coins only, "
          + this_player()->query_race() + ".");
         return 0;
      }
      else
      {
         command("say I think that " + weap + " too expensive for you, "
          + this_player()->query_race() + ".");
         return 0;
      }
   }

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   write("You buy the " + weap + " and pay " + coin_pay_text + ".\n");
   if (coin_get_text)
      write("You get " + coin_get_text + " back.\n");
   return 1;
}

/*do_straighten(str) {
   object weapon;
   if(!str || !(weapon = present(str,this_player())))
      return 0;
   command("say I don't feel like straightening any weapons right now!");
   return 1;
}

do_sharpen(str) {
   object weapon;
   if(!str || !(weapon = present(str,this_player())))
      return 0;
   command("say I am sorry, I cannot do that now!");
   return 1;
}

do_harden(str) {
   object weapon;
   if(!str || !(weapon = present(str,this_player())))
      return 0;
   command("say I am sorry, I do not have the proper tools!");
   return 1;
}*/

/********************************************************************
 *
 *  Some feelings to make the blacksmith more vivid.
 *  The feelings are split in two parts: the part that is called by
 *  a trigger function, and a part that is called after a random time.
 *  This is done to get a feeling of reality in the game.
 */

/*react_sigh(who, dummy) {
   if (who) {
      who = lower_case(who);
      set_alarm(itof(4 + random(9)), 0.0, &return_sigh(who));
      return 1;
   }
}*/

return_sigh(who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Why are you depressed, " + obj->query_nonmet_name()
               + "?");
      if (ran == 1)
         command("comfort " + who);
      if (ran == 2)
         command("say Is life tough for you, " + obj->query_race()
               + "?");
   }
}

/*react_smile(who, dummy) {
   if (who) {
      who = lower_case(who);
      set_alarm(itof(4 + random(9)), 0.0, &return_smile(who));
      return 1;
   }
}*/

return_smile(who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Life is great, isn't it, " + obj->query_nonmet_name()
               + "?");
      if (ran == 1)
         command("smile at " + who);
      if (ran == 2)
         command("say It is great to see you smiling, " + obj->query_race()
               + ".");
   }
}

public void
emote_hook(string emote, object actor, string adverb = 0)
{
    string who = lower_case(actor->query_real_name());
    if (emote == "smile")
        set_alarm(itof(4 + random(9)), 0.0, &return_smile(who));
    else if (emote == "sigh")
        set_alarm(itof(4 + random(9)), 0.0, &return_sigh(who));
}

public void
emote_hook_onlooker(string emote, object actor, string adverb, object *oblist,
    int cmd_attr)
{
    emote_hook(emote, actor);
}

/* This is for the solamnic Knights */
/* I see no reason why they shouldn't kill him but he's not evil */
/* Give him a low prestige value */

//query_knight_prestige() { return(0); } 

// It's hardly knightly to kill random citizens... - Lavellan
query_knight_prestige() { return(-1); } 

