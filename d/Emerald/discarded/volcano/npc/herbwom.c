// Herb woman for Native Camp
// She sells and buys herbs....
// Maybe she can sell mild potions (?)

inherit "/std/monster";
inherit "/lib/trade";
inherit "/lib/guild_support";
#include "/sys/money.h"
#include "/sys/stdproperties.h"
#include "/sys/language.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include <std.h>
#define TO 	this_object()
#define VNPC "/d/Emerald/mountain/volcano/npc/"
#define HERBAL_SAVE	VNPC + "herbal_save"
#define TP	this_player()
mixed *herbs;

#define MAX_HERBS 15         /* the maximum number of herbs herbalist will
                                keep of one type */
#define NUM sizeof(MONEY_TYPES)

static string pay_type, get_type, coin_pay_text, coin_get_text, *sold_arr,
             log_str, book_str, name;
static int money_arr, closed, no_report_flag;
static object given_herb;

create_monster()
{
	set_name("marie");
	add_name("woman");
	add_name("herbalist");
	set_race_name("human");
	set_gender(G_FEMALE);
	set_short("small woman");
	set_adj("merry");
	set_long("This woman appears to be skilled in " +
	"the use and identification of herbs.  If you havea  herb, " +
	"she would most likely want to purchase it from you.  From time to time, " +
	"she will also have herbs for sale. Type 'buy herbs' to get a list available for sale.\n");
   set_stats(({ 55, 55, 60, 99, 98, 55 }));
   set_hp(10000);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   add_prop(CONT_I_WEIGHT,63000);
   add_prop(CONT_I_HEIGHT,174);

   set_skill(SS_HERBALISM,96);
   set_skill(SS_UNARM_COMBAT,65);
   set_skill(SS_DEFENCE,52);

	set_chat_time(7);
	add_chat("How can I help you?");
	add_chat("Do you have any herbs for me?");

   set_act_time(4);
   add_act("@@announce_selling");

   config_default_trade();
   set_money_give_out(({ 10000,   700,  10,  10 }));
   set_money_give_reduce(({  0,     0,   0,   0 }));

}

init_living()
{
   ::init_living();
   add_action("buy","buy",0);
   add_action("sell","sell",0);
   no_report_flag = 0;
}



buy(str)
{
   int n;
   seteuid(getuid(TO));
   str = lower_case(str);
   if (str == "herbs" || str == "herb" || !str) {
      write("The herbalist says: ");
      if (!herbs) {
	write("I am sorry, I have no more Herbs for sale.\n");
         command("sigh");
         return 1;
       }
	write("I have:\n");
      while (n<sizeof(herbs)/4) {
         write("  "+herbs[n*4+2]+" "+LANG_PWORD(herbs[n*4])+
               " for "+herbs[n*4+3]+" coppers each.\n");
         n++;
       }
      command("smile absent "+TP->query_real_name());
      return 1;
   }
   /* In case the player wanted to actually buy one of the herbs */
   n = 0;
   say(QCTNAME(TP)+" asks the herbalist for a "+str+"-herb.\n",TP);
   write("The herbalist starts looking through his herb-storage.\n");
   say("The herbalist starts looking through his herb-storage.\n");
   while (n<sizeof(herbs)/4) {
      if (str == herbs[n*4] || str == LANG_PWORD(herbs[n*4])) {
         do_buy(n);
         return 1;
}
      n++;
   }
	command("say I'm sorry, " +
      ((TP->query_gender() == G_MALE) ? "Sir" : "Ma'am")+
	", but i have no " + LANG_PWORD(str)+".\n");
   return 1;
}

do_buy(int n)
{
   object herb;
   if (can_afford(herbs[n*4+3])) {
      if (!(herb = clone_object(herbs[n*4+1]))) {
	command("say I'm sorry, I don't seem to have that.");
         return 1;
       }
      herb->move(TO);
      tell_room(environment(),"The herbalist picks up a herb from a "+
          "little pouch.\n");
	command("say I hope this will help you " +
         ((TP->query_gender() == G_MALE) ? "Sir" : "Ma'am")+"!");
      command("give "+herb->query_name()+" to "+TP->query_real_name());
      herbs[n*4+2] -= 1;
      if (herbs[n*4+2] <= 0) remove_herb(n);
   }
   else {
      command("frown");
	command("say I can not give you the herb if you can't afford the price.");
   }
   return 1;
}

can_afford(int price)
{
   if (sizeof(money_arr = pay(price, TP, 0, 0, 0, get_type)) == 1)
      return 0;
   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));
	write("You pay the woman.\n");
   if (coin_get_text)
      write("You get "+coin_get_text+" back.\n");
   return 1;
}

remove_herb(int n)
{
	command("say That was my last " + capitalize(herbs[n*4])+".");
   herbs = exclude_array(herbs, n*4, n*4+3);
   return 1;
}

sell(str)
{
   object herb;
   int price, asked_for, hn;
   asked_for = 0;
   if (!str || !present(str,TP)) {
	command("say What was it you wanted to sell?");
      return 1;
   }
   herb = present(str,TP);
   if (!function_exists("create_herb",herb)) {
	command("say Sorry I only deal with herbs.");
      return 1;
   }

   if (herb->do_id_check(TO)) {
      price = herb->query_herb_value()/2;
      switch(random(4)) {
	case 0: command("say I am amazed, it is " +
            capitalize(herb->query_herb_name()) + "!"); break;
	case 1: command("say Oh my, a real " +
            capitalize(herb->query_herb_name())+"!"); break;
	case 2: command("say Goody! A " +
            capitalize(herb->query_herb_name())+"!"); break;
		case 3: command("say Neat! A " +
            capitalize(herb->query_herb_name())+"!"); break;
       }
   }
   else {
      command("gasp");
	command("say Holy Moley! I have never seen this one before!");
      command("emote blinks rapidly.");
      command("think");
	command("say I'll pay you " + herb->query_herb_value()+" coppers for this, " +
         ((TP->query_gender() == G_MALE) ? "Sir" : "Ma'am") +"!");
      price = herb->query_herb_value();
   }
   if((hn = member_array(herb->query_herb_name(),herbs)) > -1)
      {
      if(herbs[hn+2] > MAX_HERBS)
         {
         price = price/2;
		command("say I can't give you full price for the " + 
            capitalize(herb->query_herb_name()) + ".");
	command("say I already have " + capitalize(LANG_WNUM(herbs[hn+2])) + " of the same herb!");
      }
   }
   do_pay(TP, price);
   add_herb(herb);
   if(asked_for)
      {
      asked_for = 0;
   }
   return 1;
}

do_pay(object player, int price)
{
   object gc, sc, cc;
   int g, s, c;
   tell_room(environment(),"The herb merchant counts some coins "+
        "from a pouch.\n");
   g = price/144;
   s = (price - g*144)/12;
   c = price - g*144 - s*12;
   cc = MONEY_MAKE_CC(c);
   if (g) {
      gc = MONEY_MAKE_GC(g);
      write("The herb merchant gives you "+g+" gold coins.\n");
      gc->move(TP);
   }
   if (s) {
      sc = MONEY_MAKE_SC(s);
      write("The herb merchant gives you "+s+" silver coins.\n");
      sc->move(TP);
   }
   if (c) {
      cc = MONEY_MAKE_CC(c);
      write("The herb merchant gives you "+c+" copper coins.\n");
      cc->move(TP);
   }
   command("smile");
   return 1;
}

add_herb(object herb)
{
   string herb_file,trash;
   int n;
   seteuid(getuid(TO));
   sscanf(file_name(herb),"%s#%s",herb_file,trash);
   while (n<sizeof(herbs)/4) {
      if (herbs[n*4+1] == herb_file) {
         if(herbs[n*4+2] < MAX_HERBS) herbs[n*4+2] += 1;
         herb->remove_object();
         return 1;
       }
      n++;
   }
	command("say Excellent! I had run out of " +
           capitalize(LANG_PWORD(herb->query_herb_name())) +".");
   if (!herbs) herbs = ({ herb->query_herb_name(), herb_file, 1,
           herb->query_herb_value() });
   else
      herbs += ({ herb->query_herb_name(), herb_file, 1,
          herb->query_herb_value() });
   herb->remove_object();
   return 1;
}

enter_inv(herb, from)
{
   int ran;
   ::enter_inv(herb, from);
   if (!from) return;

   if (!function_exists("create_herb",herb)) {
      call_out("not_herb", 1, ({ herb, from }));
      return;
   }
   if (given_herb) {
      call_out("give_back_immediately", 1, ({ herb, from }));
      return;
   }
   call_out("test_identify", 5, ({ herb, from }));
   return;
}


int
query_closed() { return closed; }

not_herb(mixed hf)
{
	command("All I deal with is herbs.");
   switch(random(4)) {
	case 0: command("say Why would I want a " +
         capitalize(hf[0]->query_name())+"?"); break;
	case 1: command("say I am too busy for a " +
               capitalize(LANG_PWORD(hf[0]->query_name()))+"," +
               capitalize(hf[1]->query_race_name())+"."); break;
	case 3: command("say I don't want this " +
         ((TP->query_gender() == G_MALE) ? "Mister" : "Ma'am")+"."); break;
   }
   command("give "+hf[0]->query_name()+" to "+hf[1]->query_real_name());
}

give_back_immediately(mixed hf)
{
	command("say Please wait until I am done with this other herb, " +
      ((hf[1]->query_gender() == G_MALE) ? "Sir" : "Ma'am")+".");
   command("give "+hf[0]->query_name()+" to "+
      hf[1]->query_real_name());
}

test_identify(mixed h_arr)
   {
   object player;
   string id_str, find_str;
   given_herb = h_arr[0];
   player = h_arr[1];
   tell_room("The herbalist looks closely at the "+
               given_herb->query_name()+".\n");
   command("think");
   switch(given_herb->query_id_diff()/10) {
      case 0: command("laugh");
	id_str = "This one is easy.";
      break;
      case 1: command("giggle");
	id_str = "Ahh this one is a snap";
      break;
      case 2: command("giggle");
	id_str = "A goodone, easily mistaken for something else though.";
      break;
      case 3: command("frown");
	id_str = "I've seen this one a lot. But its easy to mistake.";
      break;
      case 4: command("smile");
	id_str = "I can't blame you for not recognizing this one.";
      break;
      case 5: command("bounce");
      id_str = "Exciting! ThisOneIsHardToTellFromTheCrimbulHerb.";
      break;
      case 6: command("think");
      break;
	id_str = "You have to be quite skilled to identify this one.";
      case 7: command("smile excit");
	id_str = "Oh! Is it really ....? Ah ... Yes it is!";
      break;
      case 8: command("gasp");
	id_str = "This is a tough one.";
      break;
      case 9: command("gasp");
	id_str = "I am not even sure about this one, but it must be.";
      break;
      case 10: command("jump");
	id_str = "Impossible! It just can't be?!";
   }
   command("say "+id_str);
   switch(given_herb->query_find_diff()) {
      case 0: command("smile brief");
	find_str = "This is very ordianry.";
      break;
	find_str = "This one is very common.";
      case 1: command("giggle inane");
      break;
      case 2: command("giggle inane");
	find_str = "This is not too hard to find.";
      break;
      case 3: command("smile madly");
	find_str = "Not everyone knows where to find this one.";
      break;
      case 4: command("smile");
	find_str = "this is a tough one to find.";
      break;
      case 5: command("smile");
	find_str = "It must have taken you a while to find this.";
      break;
      case 6: command("think");
	find_str = "Where on earth did you find this one?";
      break;
      case 7: command("whistle");
	find_str = "You got lucky finding this one.";
      break;
      case 8: command("gasp");
	find_str = "This is very rare!";
      break;
      case 9: command("gasp");
	find_str = "Wow I have only seen this twice in my life!";
      break;
      case 10: command("confused");
	find_str = "I can't believe you found this. I have only read about it!";
   }
   command("say "+break_string(find_str,75));
   command("emote starts to speak slowly and clearly, reciting from memory.\n");
   if (given_herb->do_id_check(TO))
      command("say "+given_herb->query_id_long());
	else command("say I do not know what this one does.");
   command("give "+given_herb->query_name()+" to "+player->query_real_name());
	command("say I hope I have been helpful " +
      ((player->query_gender()==G_MALE) ? "Sir" : "Ma'am")+".");
   given_herb = 0;
   return 1;
}

void
intro_me()
{
	command("say My name is Marie.");
}

void
react_introduce()
{
   call_out("intro_me",3);
}


int
remove_herb_from_list(string herb)
{
   int n, s;

   n = 0;
   s = sizeof(herbs);

   while(n<s/4)
   {
      if (herb == herbs[n*4] || herb == LANG_PWORD(herbs[n*4]))
         {
         if(n == 0)
            herbs = herbs[4..s-1];
         else if(n == s/4-1)
            herbs = herbs[0..s-5];
         else
            herbs = herbs[0..n*4-1] + herbs[(n+1)*4..s-1];
         return 1;
         }
      n++;
   }
   return 0;
}


