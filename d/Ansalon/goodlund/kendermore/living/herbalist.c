/*
* Jessel of Kendermore
* Borrowed from Elessar's Herbalist
* By Elessar, July 17th 1992.
* added training of herbalism, Olorin, Sep 1993
* The teaching routines were added following an example by Mortricia.
* A Krynnish herbalist by Teth, October 21, 1996
* Borrowed by Gwyneth, May 20, 1999
*/

inherit "/lib/trade";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/std/act/domove";
inherit "/std/act/action";

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit M_FILE
#include <money.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include <std.h>
#include <macros.h>
mixed *herbs;

#define HERBAL_SAVE "/d/Ansalon/goodlund/kendermore/living/herbalist_herbs"
#define MAX_HERBS 25 /*the maximum number of herbs Jess will keep of one type*/
#define NUM sizeof(MONEY_TYPES)
#define CLOSED 0 
#define HERB_LIST ({"chantrelle","chokecherry","cladina","blueberry",\
    "hazelnut","onoclea","raspberry","sarsaparilla","saskatoon",\
    "tangleshoot","horsetail","amanita","dandelion","chicory","hawthorn",\
    "solinaith","jewelweed","cattail",})
#define LOTHMIR_S_HERB "_lothmir_s_herb"
#define LOTHMIR_S_HERB_SOLD "_lothmir_s_herb_sold"

static string pay_type, get_type, coin_pay_text, coin_get_text, *sold_arr, log_str, book_str, name;
static int money_arr, closed, no_report_flag;
static object given_herb;

create_krynn_monster()
{
   if (!IS_CLONE)
      return;
   
   closed = CLOSED;
   
   set_name("jessel");
   add_name(({"herbalist","teacher"}));
   add_name("collector");
   set_race_name("kender");
   set_living_name("jessel");
   set_title("Treeskipper of Kendermore");
   set_adj("green-fingered");
   add_adj("brown-skinned");
   set_long("@@long_func");
   set_gender(G_MALE);
   set_stats(({ 70, 55, 60, 99, 98, 55 }));
   set_introduce(1);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   add_prop(NPC_I_NO_LOOKS,1);

   add_prop(CONT_I_WEIGHT,60000);
   add_prop(CONT_I_HEIGHT,172);
   add_prop(OBJ_S_WIZINFO,"@@wizinfo");
   
   set_skill(SS_HERBALISM,96);
   set_skill(SS_UNARM_COMBAT,65);
   set_skill(SS_DEFENCE,52);
   create_skill_raise();
   set_up_skills();

   set_alignment(200);
   set_knight_prestige(-50);
   
   set_act_time(5);
   add_act("say There is an herb for every occasion!");
   add_act("say If you have an unknown herb, I might be able to identify " +
           "it.");
   add_act("say There's nothing finer than finding a new herb!");
   add_act("emote searches the ground for some herbs.");
   add_act("emote takes an herb to his nose and smells it.");
   add_act("bounce");
   add_act("emote starts sorting the herbs in his pouches.");
   add_act("@@announce_selling");
   add_act("emote eyes your pockets.");
   set_cact_time(2);
   add_cact("emote dodges out of the way of your attack.");
   add_cact("shout Help! I'm being attacked!");
   add_cact("say Didn't your mother teach you to be nice? Oh, that's " +
            "right! Ogres don't know how to be nice!");   
   set_default_answer(VBFC_ME("default_answer"));
   add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));
   add_ask(({"herbalism","lesson","lessons","train","training"}),
      "say Why don't you try to learn or improve? You might get lucky.",1);
   config_default_trade();
   set_money_give_out(({ 10000,   700,  10,  10 }));
   set_money_give_reduce(({  0,     0,   0,   0 }));
   seq_new("do_things");
   seq_addfirst("do_things","@@arm_me");
}

public void
add_introduced(string who)
{
    if (present(who, E(TO)))
	set_alarm(1.0, 0.0, &command("introduce me to " + who));
}


arm_me()
{
   restore_herbs();
    clone_object(KRARMOUR + "herb_gloves")->move(TO);
    clone_object(KOBJ + "cape")->move(TO);
    clone_object(KOBJ + "leggings")->move(TO);
    clone_object(KOBJ + "shirt")->move(TO);
    command("wear all");
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
   no_report_flag = 0;
}

announce_selling()
{
   if (herbs) command("say I have herbs for sale, for a pretty copper.");
   else command("say Someone borrowed all my herbs!");
}

long_func()
{
   string long_str;
   long_str = "This kender's eyes constantly dart across the ground as " +
   "if looking for something. He has the green stained fingers and dark " + 
   "tan of one who is foraging outside often. His light brown hair is " + 
   "tied up in a topknot and decorated with green leaves. " + 
   "He has the look of one who is very wise, but at the same " + 
   "time carefree. Perhaps he knows a great deal about herbs and plants. " +
   "If you give him an herb, he may identify it for you. He might also " + 
   "be persuaded to trade with you, or to share " + 
   "some of his knowledge with you. ";
   if (TP->query_wiz_level())
      return break_string(long_str+" Type 'stat herbalist' for more info.\n",75);
   return break_string(long_str+"\n",75);
}

wizinfo()
{
   int n;
   string str;
   if (!herbs) return "The herbalist has no herbs for sale now, tragic!.\n";
   str = "The herbalist has these herbs for sale:\n";
   while (n<sizeof(herbs)/4)
   {
      str = str+herbs[n*4]+": File "+herbs[n*4+1]+" - "+herbs[n*4+2]+" for sale, "+herbs[n*4+3]+" cc each.\n";
      n++;
   }
   str +=  "\n" +
   "If there should be due cause to stop the herbalist from teaching,\n"+
   "do so by typing:  Call remington close_open\n"+
   "This will temporarily prevent mortals from learning. After a\n"+
   "reboot, Remington will be open by default. Please send me some\n"+
   "mail if there is anything that needs to be fixed.\n\n  Teth.\n";
   return str;
}

buy(str)
{
   int n;
   seteuid(getuid(TO));
   str = lower_case(str);
  if (!CAN_SEE(TO, TP) || !CAN_SEE_IN_ROOM(TO))
  {
    command("say Uhmm, who's there? I can't see you! And I don't care to " +
            "deal with those types.");
    return 1;
  }
   if (str == "herbs" || str == "herb" || !str) {
      write("The herbalist says: ");
      if (!herbs) {
         write("I have no herbs for sale, someone must have borrowed " +
               "them!.\n");
         command("frown");
         return 1;
       }
      write("I have:\n");
      while (n<sizeof(herbs)/4) {
         write("  "+herbs[n*4+2]+" "+LANG_PWORD(herbs[n*4])+" for "+herbs[n*4+3]+" coppers each.\n");
         n++;
       }
      write("That is all.\n");
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
   command("say I'm sorry, "+
      ((TP->query_gender() == G_MALE) ? "my friend" : "my girl")+
      ", but I have no "+LANG_PWORD(str)+".\n");
   command("grin impishly");
   return 1;
}

do_buy(int n)
{
   object herb;
   if (can_afford(herbs[n*4+3])) {
      if (!(herb = clone_object(herbs[n*4+1]))) {
         command("say Hmm....it seems to have decayed...oh well!");
         command("giggle");
         return 1;
       }
      herb->move(TO);
      tell_room(environment(),"The herbalist picks up a herb from a little pouch.\n");
      command("say I hope it will be useful, "+
         ((TP->query_gender() == G_MALE) ? "my friend" : "little lady")+"!");
      command("give "+herb->query_name()+" to "+TP->query_real_name());
      herbs[n*4+2] -= 1;
      if (herbs[n*4+2] <= 0) remove_herb(n);
      save_object(HERBAL_SAVE);
   }
   else {
      command("frown");
      command("say Why do you even bother when you can't pay for it, "+
         ((TP->query_gender() == G_MALE) ? "boy" : "girl") + "?");
   }
   return 1;
}

can_afford(int price)
{
   if (sizeof(money_arr = pay(price, TP, 0, 0, 0, get_type)) == 1)
      return 0;
   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));
   write("You pay Remington the Herbalist.\n");
   if (coin_get_text)
      write("You get "+coin_get_text+" back.\n");
   return 1;
}

remove_herb(int n)
{
   command("say Hmmpf. That was my last "+herbs[n*4]+".");
   command("say I guess I will have to go borrow some more!");
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
      command("think");
      return 1;
   }
   herb = present(str,TP);
   if (!function_exists("create_herb",herb)) {
      command("say I am mainly interested in herbs " +
         ((TP->query_gender() == G_MALE) ? "my friend" : "my lady")+".");
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
          case 0: command("say Indeed, " +
            LANG_ADDART(herb->query_herb_name()) + "!"); break;
         case 1: command("say I'm surprised that you of all people managed " +
                         "to find " +
            herb->query_herb_name()+"!"); break;
         case 2: command("say Hmm...oh yes! " + 
            capitalize(LANG_ADDART(herb->query_herb_name()))+"!"); break;
         case 3: command("say Most interesting! " +
            capitalize(LANG_ADDART(herb->query_herb_name()))+"!"); break;
       }
   }
   else {
      command("gasp");
      command("say By Reorx! This is unknown to me!");
      command("blush");
      command("say 40 years of gathering herbs, but yet another unknown "
         +herb->query_name()+"!");
      command("think");
      command("say I'll pay you "+herb->query_herb_value()+" coppers for this, "+
         ((TP->query_gender() == G_MALE) ? "my good friend" : "my lady") +"!");
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

string
close_open()
{
   if(closed)
     {
       closed = 0;
       return " *** Jessel is now ready to teach! *** \n";
     }
   closed = 1;
   return " *** Jessel will not teach anymore now! *** \n";
}

int
query_closed() { return closed; }


public void
not_herb(mixed hf)
{
   command("say I only collect herbs!");
   switch(random(4)) {
      case 0: command("say Why should I care about a silly "+
         hf[0]->query_name()+"?"); break;
      case 1: command("say I am too busy to be disturbed with "
         +LANG_PWORD(hf[0]->query_name())+", "+hf[1]->query_race_name()+"."); break;
      case 2: command("say I am an herbalist, "+hf[1]->query_race_name()+
         ", not a pawnshop owner! Try two streets down."); break;
      case 3: command("say This is rather boring to me, "+
         ((TP->query_gender() == G_MALE) ? "mister" : "madam")+"."); break;
   }
   command("give "+hf[0]->query_name()+" to "+hf[1]->query_real_name());
}

give_back_immediately(mixed hf)
{
   command("say Please wait till I am finished with this other herb, "+
      ((hf[1]->query_gender() == G_MALE) ? "my friend" : "my lady")+".");
   command("give "+hf[0]->query_name()+" to "+
      hf[1]->query_real_name());
}

public int
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
      id_str = "I'm not surprised you couldn't get this one.";
      break;
      case 3: command("frown");
      id_str = "I've seen this one a lot. Why couldn't you figure it out?";
      break;
      case 4: command("smile");
      id_str = "Ah - I can't blame you for not recognizing this one.";
      break;
      case 5: command("smile");
      id_str = "Exciting! This one is hard to tell from some others.";
      break;
      case 6: command("think");
      id_str = "My dear friend - you need to be quite skilled to identify this one.";
      break;
      case 7: command("think");
      id_str = "Oh! Can it really be...? Ah...yes it is.";
      break;
      case 8: command("gasp");
      id_str = "By Reorx!! This is one of the most difficult herbs!";
      break;
      case 9: command("gasp");
      id_str = "Oh dear. Not even I am sure about this....but..it must be.";
      break;
      case 10: command("boggle");
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
      case 10: command("boggle");
      find_str = "I cannot believe it! You have actually found it! I have only "+
      "read about this in old books of herblore!";
   }
   command("say "+break_string(find_str,75));
   if (given_herb->do_id_check(TO))
      command("say "+given_herb->query_id_long());
   else command("say It is unknown to me what the effect of this "+given_herb->query_name()+" is.");
   command("give "+given_herb->query_name()+" to "+player->query_real_name());
   command("say I hope you found my information useful, "+
      ((player->query_gender()==G_MALE) ? "my friend" : "my girl")+".");
   command("smile merrily");
   given_herb = 0;
   return 1;
}

string
ask_herbs()
{
   command("say Herbs?");
   command("say Well, I know most of them!");
   command("smile knowingly");
   command("say Well, I'll buy them off you, or sell you some if you want.");
   command("say If you have an unknown herb, I may identify");
   command("say it for you, if you give it to me.");
   return "";
}

string
default_answer()
{
   command("say Stop mumbling, I can't understand a word you're saying! ");
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

string
missing_herb()
{
  string *missing;
  int i;

  missing = ({});
  for(i = 0; i < sizeof(HERB_LIST); i++)
  {
    if(member_array(HERB_LIST[i],herbs) == -1)
      missing += ({ HERB_LIST[i] });
  }
  if(!sizeof(missing)) return 0;
  return missing[random(sizeof(missing))];
}

void
tell_herb(object player)
{
  string sherb;

  TO->command("hmm");
  TO->command("peer " + player->query_name());
  TO->command("say Why should I teach you anything?");
  TO->command("say I'm a busy kender!");
  sherb = missing_herb();
  if(!sherb) return 0;
  TO->command("say On the other hand, I need "+sherb+".");
  TO->command("say Sell me some, and I will teach you one lesson.");
  TP->add_prop(LOTHMIR_S_HERB,sherb);
}

/*
 * Function name: sk_hook_raise_rank
 * Description:   The player trains and pays, write something
 * Arguments:     snum  - The skill he trained
 *                to_lev - Wich level he reached
 *                cost   - How much he payed
 */
void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;

    rank = sk_rank(to_lev);


    write(process_string(QCTNAME(TO))+" teaches you " + sk_tdesc[snum][0] + ".\n");
    write("You achieve the rank of " + rank + ".\n");
    LSAY(process_string(QCTNAME(TO)) + " teaches ", " " + sk_tdesc[snum][1] +
      " and helps him to reach the rank of " + rank + ".");
}

/*
 * Function name: sk_hook_write_header
 * Description:   Write the header to the improve or learn list
 * Arguments:     lessons - How many steps we are talking about
 */
void
sk_hook_write_header(int lessons)
{
    if (!lessons)
        lessons = 1;
    TO->command("say These are the skills in which I can teach you");
    TO->command("say " + LANG_WNUM(lessons) +  (lessons == 1 ? " lesson" : " lessons") + " or more.");
    write("  Skill:                Cost:      "+
          "Next level:           Max level:\n"+
          "--------------------------------------"+
          "--------------------------------------\n");
}
/*
 * Function name: sk_hook_no_list_learn
 * Description:   No more unknown skills for the player in this guild
 * Returns:       1
 */
int
sk_hook_no_list_learn()
{
    TO->command("say I cannot teach you any new skill!");
    TO->command("say You might try to improve skills that you have.");
    TO->command("say Or you will have to seek other teachers elsewhere.");
    return 1;
}

/*
 * Function name: sk_hook_no_list_improve
 * Description:   No more skills that the player can improve
 * Returns:       1
 */
int
sk_hook_no_list_improve()
{
    TO->command("say There are no skills that I can teach you anymore.");
    TO->command("say Perhaps you would feel like learning a new skill?");
    TO->command("say Or you will have to seek other teachers elsewhere.");
    return 1;
}

/*
 * Function name: sk_hook_improved_max
 * Description:   Player can't improve this skill any higer
 * Arguments:     skill - The skill player wanted to improve
 * Returns:       0
 */
int
sk_hook_improved_max(string skill)
{
    NF("You cannot raise this skill any further here, you have to\n" +
      "seek knowledge elsewhere.\n");
    return 0;
}

/*
 * Function name: sk_improve
 * Description:   Function called when player tries to do the improve command
 * Arguments:     str - The rest of the command player made
 * Returns:       1/0
 */
int
sk_improve(string str)
{
  string *tmp;
  int steps, success, old_skill;

  if(TP->query_skill(SS_HERBALISM) > 10)
  {
    if(!TP->query_prop(LOTHMIR_S_HERB))
    {
      tell_herb(TP);
      return 1;
    }
    if(TP->query_prop(LOTHMIR_S_HERB) != LOTHMIR_S_HERB_SOLD)
    {
      TO->command("say Go and bring me some " +TP->query_prop(LOTHMIR_S_HERB) + ".");
      TO->command("say Sell me that herb, and I'll teach you something.");
      TO->command("say Understand?");
      TO->command("eyebrow " + TP->query_name());
      return 1;
    }
  }

/* Lothmir teaches only one level at a time */
  if(str)
  {
    tmp = explode(str, " ");
    if (sscanf(tmp[sizeof(tmp) - 1], "%d", steps) == 1 && sizeof(tmp) > 1)
    {
      TO->command("say I teach only one lesson at a time.");
      TO->command("say Don't be so hasty, my friend!");
      TO->command("say It took me a long time to learn what I know!");
      TO->command("smile " + TP->query_name());
      return 1;
    }
  }

  success = 0;
  old_skill = TP->query_skill(SS_HERBALISM);
  success = ::sk_improve(str);
  if(success && TP->query_skill(SS_HERBALISM) > old_skill)
    TP->remove_prop(LOTHMIR_S_HERB);
  return success;
}

public void
enter_inv(object herb, object from)
{
   int ran;

   ::enter_inv(herb, from);

   if (!from) return;
   
   if (!function_exists("create_herb",herb)) {
      set_alarm(1.0, 0.0, &not_herb( ({ herb, from }) ));
      return;
   }
   
   if (given_herb) {
      set_alarm(1.0, 0.0, &give_back_immediately( ({ herb, from }) ));
      return;
   }
   
   set_alarm(5.0, 0.0, &test_identify( ({ herb, from }) ));
}

public void
do_die(object killer)
{
    command("remove cape");
    ::do_die(killer);
}

