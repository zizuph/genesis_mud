inherit "/std/monster.c";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/prestige.h"

void introduce_me();
int intro_id;

void
create_monster()
{
   
   set_name("haestur");
   set_title("Havenstead, Owner and Proprietor of the Sleeping Fisherman");
   add_adj(({"tall","bald"}));
   set_long("This is Haestur, the owner and proprietor of the " +
      "Sleeping Fisherman Inn. He is a tall, middle-aged man " +
      "who is now almost completely bald. However, he always " +
      "seems to have a welcoming smile on his face for all of " +
      "his customers.\n");
   set_race_name("human");
   set_gender(0);
   add_act("smile all");
   add_act("emote washes his hands quickly.");
   add_act("emote picks up a log from the woodpile and puts it in the fireplace");
   add_act("emote begins to clean some mugs and plates.");
   add_act("emote quickly goes outside to pay a local fisherman for his catch.");
   add_act("emote points and the menu and says: Would you like to order anything?");
   add_act("emote wanders around to various tables, gathering up the dirty dishes.");
   add_act("emote runs into the kitchen for a moment before coming back to the bar.");
   add_act("emote pulls out a broom and starts to sweep the floor.");
   add_act("emote makes his way upstairs with fresh straw and blankets before swiftly returning.");
   add_act("emote gets a ladder and replaces a candle in the chandelier.");
   add_act("emote starts to cut up some potatoes to roast.");
   add_act("emote cleans the bar with a towel.");
   add_act("emote quickly grabs something from the kitchen.");
   add_act("emote eats some roasted potatoes.");
   add_act("scratch head thoughtfully");
   add_chat ("Welcome to the Sleeping Fisherman! Enjoy a bite " +
      "to eat, a mug to drink and a bed to sleep in for the night!");
   add_chat ("I have heard of some strange rumours, that people " +
      "have been attacked as they travelled east towards " +
      "the Greenway.");
   add_chat ("We have some wonderfully fresh fish here, exquistely prepared if " +
      "I do say so myself!");
   add_chat ("Opening this inn was the best decision I ever made!");
   add_chat ("I heard rumour that there might be some bandits nearby, be " +
      "careful as you travel!");
   add_chat ("Would you like some fish? Best you ever tasted!");
   add_chat ("My recipe for roasted taters has been a family secret for " +
      "generations! Or so my pappy told me.");
   add_chat ("Running an inn like this is a lot of work, but I love it!");
   
   set_act_time(4);
   set_chat_time(10);
   
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE, 100);

   set_stats(({ 120, 100, 140, 100, 100, 120}), 10);
   
   set_alignment(170);
   
   
   MAKE_MONEY;
   intro_id = 0;
}

void
add_introduced(string person)
{
   if (intro_id == 0) {
      intro_id = set_alarm(4.0,0.0, introduce_me);
   }
}

void
allow_introductions() 
{
   intro_id = 0;
}

void
introduce_me()
{
   command("introduce me");

   set_alarm(15.0, 0.0, allow_introductions);
}
