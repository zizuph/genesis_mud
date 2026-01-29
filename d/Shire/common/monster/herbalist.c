/*
* The Herb-master of the Shire.
* Borrowed from Elessar's Herbalist
* By Elessar, July 17th 1992.
* added training of herbalism, Olorin, Sep 1993
* The teaching routines were added following an example by Mortricia.
*/

inherit "/std/monster";
inherit "/lib/trade";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";
#include "/sys/money.h"
#include "/sys/stdproperties.h"
#include "/sys/language.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include <std.h>
#include "/d/Gondor/defs.h"
mixed *herbs;

void do_bow();
void remove_tmp_flag();
void intro_me();
void not_herb(mixed hf);
void give_back_immediately(mixed hf);
void test_identify(mixed h_arr);

#include "/d/Gondor/elessar/npc/herbalist.h"

#define HERBAL_SAVE "/d/Gondor/elessar/misc/herbalist_herbs"
#define LOG_REPORT_FILE "/d/Shire/log/herbs"
#define HERB_BOOK "/d/Gondor/common/library/books/herb-guide.txt"
#define MAX_HERBS 20 /* the maximum number of herbs Lothmir will keep of one type */
#define NUM sizeof(MONEY_TYPES)
#define CLOSED 0 

static string pay_type, get_type, coin_pay_text, coin_get_text, *sold_arr, log_str, book_str, name;
static int money_arr, closed, no_report_flag;
static object given_herb;

create_monster()
{
   if (!IS_CLONE)
      return;
   
   closed = CLOSED;
   
   set_name("tobold");
   add_name(({"herbalist","teacher"}));
   add_name("ranger");
   set_race_name("hobbit");
   set_living_name("tobold");
   set_title("the Herbalist");
   set_adj("old");
   set_adj("wise");
   set_long("@@long_func");
   set_stats(({ 55, 55, 60, 99, 98, 55 }));
   set_base_stat(SS_OCCUP, 75);
   set_hp(10000);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   add_prop(CONT_I_WEIGHT,63000);
   add_prop(CONT_I_HEIGHT,174);
   add_prop(OBJ_S_WIZINFO,"@@wizinfo");
   
   set_skill(81200, 60 + random(10));
   set_skill(81209, 60 + random(10));
   set_skill(SS_HERBALISM,96);
   set_skill(SS_UNARM_COMBAT,65);
   set_skill(SS_DEFENCE,52);
   create_skill_raise();
   set_up_skills();
   
   set_chat_time(7);
   add_chat("I am Tobold, the best herbalist in the Shire!");
   add_chat("You would not have any unknown herbs, would you?");
   add_chat("You know the old saying: There is an herb for every occasion.");
   add_chat("I think I have seen most herbs in the world by now.");
   add_chat("If you have an unknown herb, you can let me identify it for you.");
   add_chat("I still have not discovered the virtues of kingsfoil.");
   add_chat("You never know when a herb might come in handy.");
   add_chat("I've heard that the rangers have books on herbs in their library.");
   add_chat("The rangers are looking for help to write a book about herbs.");
   add_chat("Too bad that there is no book where to find which herbs in the Shire!");
   add_chat("If you ask me, I can tell you about herbs and lore.");
   set_cchat_time(2);
   add_cchat("But what have I ever done to hurt you?!?");
   add_cchat("I am a poor old man, my eyes are grey, my legs are old and bent!");
   add_cchat("Beware! Or I shall taunt you a second time!");
   set_act_time(4);
   add_act("@@announce_selling");
   set_cact_time(2);
   add_cact("brawl");
   
   trig_new("%s 'introduces' %s","react_introduce");
   trig_new("%s 'bows' %s","react_bow");
   set_default_answer(VBFC_ME("default_answer"));
   add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));
   add_ask(({"herblore","lore"}), VBFC_ME("ask_lore"));
   add_ask(({"garlic"}), VBFC_ME("ask_garlic"));
   add_ask(({"herbalism","lesson","lessons","train","training"}),
      "say Why don't you try to learn or improve?",1);
   config_default_trade();
   set_money_give_out(({ 10000,   700,  10,  10 }));
   set_money_give_reduce(({  0,     0,   0,   0 }));
   seq_new("do_things");
   seq_addfirst("do_things","@@arm_me","@@intro_me");
}

arm_me()
{
   object arm;
   seteuid(getuid(TO));
   arm = clone_object("/d/Gondor/elessar/obj/arm/green_cloak");
   arm->move(TO);
   command("wear cloak");
   restore_herbs();
}

restore_herbs()
{
   seteuid(getuid(TO));
   restore_object(HERBAL_SAVE);
}

init_living()
{
   ::init_living();
   init_skill_raise();
   add_action("buy","buy",0);
   add_action("sell","sell",0);
   add_action("do_report","report");
   no_report_flag = 0;
}

announce_selling()
{
   if (herbs) command("say I have herbs for sale too, would you like some?");
   else command("say I should go and search for more herbs.");
}

long_func()
{
   string long_str;
   long_str = "This is Tobold, the herb-master of the Shire. He is said to "+
   "know a great deal about herbs and plants and their virtues. If you give "+
   "him a herb, he will try to identify it for you. He might also have some "+
   "herbs to sell, and will tell you what he has if you 'buy herbs'. If you "+
   "have herbs to sell, Tobold will probably be happy to buy it. " +
   "Sometimes he even teaches his skill to others, but he might " +
   "ask a favour of you before he reveals parts of his wisdom. ";
   if (TP->query_wiz_level())
      return break_string(long_str+" Type 'info herbalist' for more info.\n",75);
   return break_string(long_str+"\n",75);
}

wizinfo()
{
   int n;
   string str;
   if (!herbs) return "The herbalist has no herbs for sale now.\n";
   str = "The herbalist has these herbs for sale:\n";
   while (n<sizeof(herbs)/4)
   {
      str = str+herbs[n*4]+": File "+herbs[n*4+1]+" - "+herbs[n*4+2]+" for sale, "+herbs[n*4+3]+" cc each.\n";
      n++;
   }
   str +=  "\n" +
   "If there should be due cause to stop the herbalist from teaching,\n"+
   "do so by typing:  Call tobold close_open\n"+
   "This will temporarily prevent mortals from learning. After a\n"+
   "reboot, Lothmir will be open by default. Please send me some\n"+
   "mail if there is anything that needs to be fixed.\n\n  Dunstable.\n";
   return str;
}

buy(str)
{
   int n;
   seteuid(getuid(TO));
   str = lower_case(str);
   if (str == "herbs" || str == "herb" || !str) {
      write("The herbalist says: ");
      if (!herbs) {
         write("I'm sorry, I have no more herbs for sale.\n");
         command("sigh");
         return 1;
       }
      write("I have:\n");
      while (n<sizeof(herbs)/4) {
         write("  "+herbs[n*4+2]+" "+LANG_PWORD(herbs[n*4])+" for "+herbs[n*4+3]+" coppers each.\n");
         n++;
       }
      write("That was all.\n");
      command("smile "+TP->query_real_name());
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
   command("say I'm deeply sorry, "+
      ((TP->query_gender() == G_MALE) ? "sir" : "my lady")+
      ", but I have no "+LANG_PWORD(str)+".\n");
   command("sigh");
   return 1;
}

do_buy(int n)
{
   object herb;
   if (can_afford(herbs[n*4+3])) {
      if (!(herb = clone_object(herbs[n*4+1]))) {
         command("say Hmm....I'm deeply sorry - it seems to have decayed...");
         command("frown");
         return 1;
       }
      herb->move(TO);
      tell_room(environment(),"The herbalist picks up a herb from a little pouch.\n");
      command("say I hope it will be useful, "+
         ((TP->query_gender() == G_MALE) ? "sir" : "mylady")+"!");
      command("give "+herb->query_name()+" to "+TP->query_real_name());
      herbs[n*4+2] -= 1;
      if (herbs[n*4+2] <= 0) remove_herb(n);
      save_object(HERBAL_SAVE);
   }
   else {
      command("frown");
      command("say Why do you ask when you cannot afford it, "+
         ((TP->query_gender() == G_MALE) ? "mister" : "madam") + "?");
   }
   return 1;
}

can_afford(int price)
{
   if (sizeof(money_arr = pay(price, TP, 0, 0, 0, get_type)) == 1)
      return 0;
   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));
   write("You pay Tobold the Herbalist.\n");
   if (coin_get_text)
      write("You get "+coin_get_text+" back.\n");
   return 1;
}

remove_herb(int n)
{
   command("say Hmmpf. That was my last "+herbs[n*4]+".");
   command("say I guess I will have to go searching again.");
   herbs = exclude_array(herbs, n*4, n*4+3);
   return 1;
}

sell(str)
{
   object herb;
   int price, asked_for, hn;
   asked_for = 0;
   if (!str || !present(str,TP)) {
      command("say What do you want to sell?");
      command("chuckle");
      return 1;
   }
   herb = present(str,TP);
   if (!function_exists("create_herb",herb)) {
      command("say I am only interested in herbs, "+
         ((TP->query_gender() == G_MALE) ? "sir" : "mylady")+".");
      return 1;
   }
   /* added for training, Olorin */
   if(TP->query_prop(LOTHMIR_S_HERB) == herb->query_herb_name())
      {
      asked_for = 1;
      TP->add_prop(LOTHMIR_S_HERB,LOTHMIR_S_HERB_SOLD);
   }
   if (herb->do_id_check(TO)) {
      price = herb->query_herb_value()/2;
      switch(random(4)) {
         case 0: command("say I'm amazed, it is " +
            LANG_ADDART(herb->query_herb_name()) + "!"); break;
         case 1: command("say Oh dear, if it isn't a genuine "+
            herb->query_herb_name()+"!"); break;
         case 2: command("say Hmm...oh yes! " + 
            capitalize(LANG_ADDART(herb->query_herb_name()))+"!"); break;
         case 3: command("say Most interesting! " +
            capitalize(LANG_ADDART(herb->query_herb_name()))+"!"); break;
       }
   }
   else {
      command("gasp");
      command("say By the Holy Beard of Eru! This is unknown to me!");
      command("blush");
      command("say 87 years of gathering herbs, but yet another unknown "
         +herb->query_name()+"!");
      command("think");
      command("say I'll pay you "+herb->query_herb_value()+" coppers for this, "+
         ((TP->query_gender() == G_MALE) ? "sir" : "my lady") +"!");
      price = herb->query_herb_value();
   }
   if((hn = member_array(herb->query_herb_name(),herbs)) > -1)
      {
      if(herbs[hn+2] > MAX_HERBS)
         {
         price = price/2;
         command("say I cannot give you the full price for the " +
            herb->query_herb_name() + ".");
         command("say I already have " + LANG_WNUM(herbs[hn+2]) + " of the same.");
      }
   }
   do_pay(TP, price);
   add_herb(herb);
   if(asked_for)
      {
      command("say I will now teach you, if you ask me to.");
      asked_for = 0;
   }
   remove_call_out("ask_help_herb_book");
    set_alarm((5+random(10)),0.0, &ask_help_herb_book(TP));
   return 1;
}

do_pay(object player, int price)
{
   object gc, sc, cc;
   int g, s, c;
   tell_room(environment(),"The herb-master counts some coins from a pouch.\n");
   g = price/144;
   s = (price - g*144)/12;
   c = price - g*144 - s*12;
   cc = MONEY_MAKE_CC(c);
   if (g) {
      gc = MONEY_MAKE_GC(g);
      write("The herbalist gives you "+g+" gold coins.\n");
      gc->move(TP);
   }
   if (s) {
      sc = MONEY_MAKE_SC(s);
      write("The herbalist gives you "+s+" silver coins.\n");
      sc->move(TP);
   }
   if (c) {
      cc = MONEY_MAKE_CC(c);
      write("The herbalist gives you "+c+" copper coins.\n");
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
   command("say Excellent! I had run out of "+LANG_PWORD(herb->query_herb_name())+".");
   if (!herbs) herbs = ({ herb->query_herb_name(), herb_file, 1, herb->query_herb_value() });
   else
      herbs += ({ herb->query_herb_name(), herb_file, 1, herb->query_herb_value() });
   herb->remove_object();
   save_object(HERBAL_SAVE);
   return 1;
}

enter_inv(herb, from)
{
   int ran;
   ::enter_inv(herb, from);
   if (!from) return;
   
   if (!function_exists("create_herb",herb)) {
   set_alarmv(1.0,0.0, &not_herb, ({ herb, from }));
      return;
   }
   if (given_herb) {
    set_alarmv(1.0,0.0, &give_back_immediately, ({herb,from}));
      return;
   }
   set_alarmv(5.0,0.0, &test_identify, ({herb, from}));
   return;
}

string
close_open()
{
   if(closed)
      {
      closed = 0;
      return " *** Tobold is now ready to teach! *** \n";
   }
   closed = 1;
   return " *** Tobold will not teach anymore now! *** \n";
}

int
query_closed() { return closed; }

not_herb(mixed hf)
{
   command("say I do not care for anything but herbs!");
   switch(random(4)) {
      case 0: command("say Why should I care about a silly "+
         hf[0]->query_name()+"?"); break;
      case 1: command("say I am too busy to be disturbed with "
         +LANG_PWORD(hf[0]->query_name())+", "+hf[1]->query_race_name()+"."); break;
      case 2: command("say I am a herbalist, "+hf[1]->query_race_name()+
         ", not a stupid pawnshop owner!"); break;
      case 3: command("say This is of no interest to me, "+
         ((TP->query_gender() == G_MALE) ? "mister" : "madam")+"."); break;
   }
   command("give "+hf[0]->query_name()+" to "+hf[1]->query_real_name());
}

give_back_immediately(mixed hf)
{
   command("say Please wait till I am finished with this other herb, "+
      ((hf[1]->query_gender() == G_MALE) ? "sir" : "my lady")+".");
   command("give "+hf[0]->query_name()+" to "+
      hf[1]->query_real_name());
}

test_identify(mixed h_arr)
   {
   object player;
   string id_str, find_str;
   given_herb = h_arr[0];
   player = h_arr[1];
   tell_room("The herbalist looks closely at the "+given_herb->query_name()+".\n");
   command("think");
   switch(given_herb->query_id_diff()/10) {
      case 0: command("laugh");
      id_str = "Even the children can recognize this one.";
      break;
      case 1: command("giggle");
      id_str = "Hmm...one of the easiest recognizable herbs.";
      break;
      case 2: command("giggle");
      id_str = "Ahh..a nice one. Some people often mistake this for another.";
      break;
      case 3: command("frown");
      id_str = "I've seen this one a lot. Easily mistaken though.";
      break;
      case 4: command("smile");
      id_str = "Ah - I can't blame you for not recognizing this one.";
      break;
      case 5: command("smile");
      id_str = "Exciting! This one is hard to tell from the Crimbul herb.";
      break;
      case 6: command("think");
      id_str = "My dear friend - you need to be quite skilled to identify this one.";
      break;
      case 7: command("think");
      id_str = "Oh! Can it really be...? Ah...yes it is.";
      break;
      case 8: command("gasp");
      id_str = "By the Holy Beard of Eru!! This is one of the most difficult herbs!";
      break;
      case 9: command("gasp");
      id_str = "Oh dear. Not even I am sure about this....but..it must be.";
      break;
      case 10: command("confused");
      id_str = "Impossible! Absolutely impossible! It just can't be...?!";
   }
   command("say "+id_str);
   switch(given_herb->query_find_diff()) {
      case 0: command("laugh");
      find_str = "Ah..this is as normal as ordinary grass.";
      break;
      case 1: command("giggle");
      find_str = "This one is quite a usual sight.";
      break;
      case 2: command("giggle");
      find_str = "Not so hard to find.";
      break;
      case 3: command("smile");
      find_str = "Interesting. Not everybody knows where to find this one.";
      break;
      case 4: command("smile");
      find_str = "Good work! This one is not easy to locate.";
      break;
      case 5: command("smile");
      find_str = "Ah! I guess you spent some time looking for this one!";
      break;
      case 6: command("think");
      find_str = "Hmmm. I wonder where you found this one?";
      break;
      case 7: command("whistle");
      find_str = "You must have been quite lucky to find this herb!";
      break;
      case 8: command("gasp");
      find_str = "I am absolutely astonished! This is extremely rare!";
      break;
      case 9: command("gasp");
      find_str = "How can this be?? I have only seen this herb about twice in my life!";
      break;
      case 10: command("confused");
      find_str = "I cannot believe it! You have actually found it! I have only "+
      "read about this in old books of herblore!";
   }
   command("say "+break_string(find_str,75));
   if (given_herb->do_id_check(TO))
      command("say "+given_herb->query_id_long());
   else command("say It is unknown to me what the effect of this "+given_herb->query_name()+" is.");
   command("give "+given_herb->query_name()+" to "+player->query_real_name());
   command("say I hope my information has been useful, "+
      ((player->query_gender()==G_MALE) ? "sir" : "mylady")+".");
   command("bow");
   given_herb = 0;
   return 1;
}

void
intro_me()
{
   if(TP)
      command("hail " + TP->query_real_name());
   else
      command("hail");
   command("say My name is Tobold Hornblower.");
   command("present me");
}

void
react_introduce()
{
   set_alarm(3.0,0.0, &intro_me());
}

void
do_bow()
{
   if(TP)
      command("bow " + TP->query_real_name());
   else
      command("bow");
   command("say What can I do for you?");
   command("say If you have an unknown herb, you can let me identify it for you.");
}

void
react_bow()
{
   set_alarm(3.0,0.0, &do_bow());
}

void
ask_help_herb_book(object player)
{
   command("Hmm");
   if(!present(player,ENV(TO)) || no_report_flag)
      return;
   command("Hmm");
   command("peer "+player->query_real_name());
   command("say The Rangers want to write a book about herbs in Middle-Earth ");
   command("say for some crazy reason. Who knows what these Ranger are up to?");
   command("sigh");
   command("say It should tell where one can find which herbs, ");
   command("say and other things about herbs. ");
   command("say You can contribute by reporting here where you found a herb.");
   command("say You can also <report> here if you are ");
   command("say interested in making a book out of all the reports!");
   no_report_flag = 1;
   remove_call_out("remove_tmp_flag");
   set_alarm(120.0,0.0, &remove_tmp_flag());
}

void remove_tmp_flag() { no_report_flag = 0; }

string
ask_herbs()
{
   command("say Herbs?");
   command("say Well, I know most of them!");
   command("say You can buy some from me, and I sell herbs, too!");
   command("say If you have an unknown herb, I can try to identify");
   command("say it for you, if you give it to me.");
   command("say If you want to learn about herblore, ask me about it.");
   return "";
}

string
ask_lore()
{
   command("say Herb lore?");
   command("say Well, there are only few who know as much about herbs as I do!");
   command("say But even I do not know all the places where herbs grow!");
   command("say You might check in the library in the rangers' guild.");
   command("say But the books there are ancient.");
   remove_call_out("ask_help_herb_book");
   set_alarm(10.0,0.0, &ask_help_herb_book(TP));
   return "";
}

string
default_answer()
{
   command("say I don't know what you are talking about!");
   return "";
}

int
write_more(string str)
{
   if(str == "**")
      {
      SECURITY->note_something(log_str, LOG_REPORT_FILE,3,ENV(TO));
      write_file(HERB_BOOK, book_str);
      write("Thanks for your contribution!\n");
   }
   else if(str == "~q")
      {
      write("Report aborted!\n");
   }
   else if(str == "~l")
      {
      write(log_str+"\n");
      input_to("write_more");
   }
   else
      {
      log_str += (str + "\n");
      book_str += (name + str + "\n");
      write("--> ");
      input_to("write_more");
   }
   return 1;
}


string
ask_garlic()
{
   command("say Garlic?");
   command("peer " + TP->query_real_name());
   command("hmm");
   command("say Well, if you meet some, you will recognize it from the stench.");
   command("say It's mainly used to flavour dishes, ");
   command("say but some rhymes of old claim that it has magical properties, ");
   command("say protecting against some kinds of undead.");
   command("shrug");
   command("say Well, I don't know if that's true.");
   return "";
}
void
set_up_skills()
{
   string me, ot;
   
   me = "to recognize and handle herbs and plants";
   ot = me;
   sk_add_train(SS_HERBALISM, ({me, ot}), 0, 0, 30);
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
