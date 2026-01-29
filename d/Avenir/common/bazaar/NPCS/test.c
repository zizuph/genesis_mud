// creator(s):  Borrowed from Elessar's Herbalist (Elessar, July 17th 1992)
//              Updated for the Bazaar area by Ilyian (May 1995)
// last update: Lilith, Typed the functions and added some asks. May 97.
//              Denis, May'97: Regular updates: triggers and such.
// purpose:     To buy and sell herbs.
//              Herbmerchant for the Apothecary in the Bazaar
// modification log:
//   9 Sept 2002 - Manat - Added code for OBJ_M_NO_SELL and OBJ_M_NO_BUY
// note:        Training routines removed.
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";
inherit "/lib/trade";

# include "/d/Avenir/common/common.h"
# include <money.h>
# include <language.h>
# include <ss_types.h>
# include <std.h>
# include "/d/Avenir/include/relation.h"

mixed *herbs;

#define HERBAL_SAVE     "/d/Avenir/common/bazaar/NPCS/merchant_herbs"
#define LOG_REPORT_FILE "/d/Avenir/log/herbs"
#define MAX_HERBS 35    /* the maximum number of herbs herbalist will
                           keep of one type */
#define NUM sizeof(MONEY_TYPES)
#define CLOSED 0

static string pay_type, get_type, coin_pay_text, coin_get_text, *sold_arr,
             log_str, book_str, name;
static int money_arr, closed, no_report_flag;
static object given_herb;

void    give_back_immediately(mixed hf);
mixed   test_identify(mixed h_arr);
void    not_herb(mixed hf);

void    give_back_immediately(mixed hf);
void    restore_herbs();

void
create_monster()
{
    if (!IS_CLONE)
        return;

    closed = CLOSED;

    set_name("shillish");
    add_name("herbalist");
    set_race_name("gnome");
    set_living_name("shillish");
    set_title("the Veteran Herbalist of Sybarus");
    set_adj("wide-eyed");
    add_adj("friendly");
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

    set_chat_time(7);
    add_chat("IAmshillishAndIBuyAndSellHerbs.");
    add_chat("ICanIdentifyUnknownHerbsIfYouWant.");
    add_chat("IWonderIfMyBrotherIsOkInThoseDarkTunnels.");
    add_chat("I'veSeenAllTheHerbsThereAre.");
    add_chat("HerbsAreMyLife.");
    add_chat("SomeHerbsDoStrangeThings.");
    add_chat("HerbsHerbsHerbsHerbs.");
    add_chat("IAmSoHappyThatTheLordCommissionerLetUsExpandToSellOtherStuff.");
    add_chat("GreatMagicResidesInTheDepths.");
    add_chat("WeHaveExpandedTheApothecaryNow. ComeInsideAndSee.");
    add_chat("SometimesHerbsCanBeCompletelyUseless.");
    add_chat("IHopeThePunisherDosen'tShutMeDown.");
    add_chat("MaybeThereIsABookInTheBazaar'sLibraryAboutHerbs. MaybeNotThough.");
    add_chat("ThereIsNothingIDoNotKnow.");
    add_chat("IHeardThereWereHerbsThatCouldMakeYouBreatheUnderwater!Wow!");
    add_chat("We'llHaveAHealerHereSoon,AndAnAlchemist,too!");

    set_act_time(8);
    add_act("@@announce_selling");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask("[about] [herb] 'pouch' / 'pouches' / 'jar'",
        VBFC_ME("pouch_ask"));
    add_ask("[about] 'pub' / 'tent' / 'havec'",
        VBFC_ME("pouch_ask"));
    config_default_trade();
    set_money_give_out(({ 10000,   700,  10,  10 }));
    set_money_give_reduce(({  0,     0,   0,   0 }));
}

void
arm_me()
{
   seteuid(getuid(TO));
   clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);
   command("wear all");

   restore_herbs();
}

void
restore_herbs()
{
   seteuid(getuid(TO));
   restore_object(HERBAL_SAVE);
}

string
pouch_ask()
{
    command("say Havec Sackseller has a blue tent just south of the "+
        "entrance to Icky Bod's Pub. He sells pouches and other "+
        "things, like saddlebags and scrips.");
    return "";
}

string
default_answer()
{
   command("emote looks around as though he is worried about something.");
   command("say I'mOnlyPermittedToDiscussHerbs!");
   return "";
}

void
init_living()
{
   ::init_living();
   add_action("buy","buy",0);
    add_action("buy", "list",0);
   add_action("sell","sell",0);
   no_report_flag = 0;
}

void
announce_selling()
{
   if (herbs) command("say IHaveHerbsForSaleTooWouldYouLikeSome?");
   else command("say IShouldGoAndSearchForMoreHerbs.");
}
string
long_func()
{
   string long_str;
   long_str = "This little fellow smells strongly of mint and sage. He seems "+
              "to be quite knowledgeable in the field of Herblore. You "+
              "can buy and sell herbs with him.";
   if (TP->query_wiz_level())
       return break_string(long_str+" Type 'stat herbalist' for more info.\n",75);
   return break_string(long_str+"\n",75);
}
string
wizinfo()
{
   int n;
   string str;

   if (!herbs)
       return "Shillish has no herbs for sale now.\n";
   str = "Shillish has these herbs for sale:\n";
   while (n<sizeof(herbs)/4)
   {
   str = str+herbs[n*4]+": File "+herbs[n*4+1]+" - "+herbs[n*4+2]+" for sale,"+
      herbs[n*4+3]+" cc each.\n";
      n++;
   }
   str +=  "\n" + "\n\n /Iliyian.\n";
   return str;
}

int
remove_herb(int n)
{
   command("say Drat! ThatWasMyLast"+capitalize(herbs[n*4])+"!");
   command("sob");
   herbs = exclude_array(herbs, n*4, n*4+3);
   return 1;
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
           else
               if(n == s/4-1)
                   herbs = herbs[0..s-5];
           else
               herbs = herbs[0..n*4-1] + herbs[(n+1)*4..s-1];
           return 1;
        }
        n++;
    }
    return 0;
}

can_afford(int price)
{
   if (sizeof(money_arr = pay(price, TP, 0, 0, 0, get_type)) == 1)
      return 0;
   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));
   write("You pay Shillish.\n");
   if (coin_get_text)
      write("You get "+coin_get_text+" back.\n");
   return 1;
}

int
do_buy(int n)
{
   object herb;
   mixed herbmsg;
   string tmpmsg, *tmparr;

   if (can_afford(herbs[n*4+3]))
   {
      if (!(herb = clone_object(herbs[n*4+1])))
      {
         command("say Hmm....I'mReallySorry - ItSeemsToHaveDecayed...");
         command("cry");
         return 1;
      }
      herbmsg = herb->query_prop(OBJ_M_NO_BUY);

      if (stringp(herbmsg))
      {
         tmpmsg = herbmsg;
         tmpmsg = lower_case(tmpmsg);
         tmparr = explode(tmpmsg, " ") - ({ "", " ", 0 });
         tmparr = map(tmparr, capitalize);
         tmpmsg = implode(tmparr, "");
         command("say ICouldn'tSellThatHerbToYou." + tmpmsg + ".");
         herb->destroy();
         return 1;
      }
      if (intp(herbmsg) && herbmsg != 0)
      {
         command("say ICouldn'tSellThatHerbToYou.It'sForASpecialCustomer.");
         herb->destroy();
         return 1;
      }

      herb->move(TO);
      tell_room(environment(),"The herbalist picks up a herb from a "+
          "little pouch.\n");
      command("say IHopeItWillBeUseful,"+
         ((TP->query_gender() == G_MALE) ? "Sir" : "Ma'am")+"!");
      command("give "+herb->query_name()+" to "+TP->query_real_name());
      herbs[n*4+2] -= 1;
      if (herbs[n*4+2] <= 0) remove_herb(n);
      save_object(HERBAL_SAVE);
   }
   else
   {
      command("frown");
      command("say WhyDoYouAskWhenYouCan'tAffordIt?");
   }
   return 1;
}

int
buy(string str)
{
   int n;
   seteuid(getuid(TO));


    if (!CAN_SEE(this_object(), this_player()))
    {
        command("say Interesting, indeed, that a spirit of "+
            "air would speak with me.");
        command("say I cannot deal with those I cannot see!");
        return 1;
    }

    if (IS_INFIDEL(this_player()))
    {
        command("say I am not permitted to trade with you.");
        command("say Leave me, or I will call the guards.");
        return 1;
    }

   str = lower_case(str);

   if (str == "herbs" || str == "herb" || !str)
   {
      write("The herbalist says: ");
      if (!herbs)
      {
          command("say I'mSorryIHaveNoMoreHerbsForSale!");
          command("sigh");
          return 1;
      }
      write("IHave:\n");
      while (n<sizeof(herbs)/4)
      {
         write("  "+herbs[n*4+2]+" "+LANG_PWORD(herbs[n*4])+
               " for "+herbs[n*4+3]+" coppers each.\n");
         n++;
      }
      write("ThatWasAll.\n");
      command("smile absent "+TP->query_real_name());
      return 1;
   }
   /* In case the player wanted to actually buy one of the herbs */
 
    if (query_verb() == "list")
    {
        return 1;
    }
 
   n = 0;
   say(QCTNAME(TP)+" asks the herbalist for a "+str+"-herb.\n",TP);
   write("The herbalist starts looking through his herb-storage.\n");
   say("The herbalist starts looking through his herb-storage.\n");
   while (n<sizeof(herbs)/4)
   {
      if (str == herbs[n*4] || str == LANG_PWORD(herbs[n*4])) 
      {
         do_buy(n);
         return 1;
      }
      n++;
   }
   command("say I'mDeeplySorry,"+
      ((TP->query_gender() == G_MALE) ? "Sir" : "Ma'am")+
      ",ButIHaveNo"+LANG_PWORD(str)+".\n");
   command("sigh heartbrokenly");
   return 1;
}

int
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
int
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
   command("say Excellent!IHadRunOutOf"+
           capitalize(LANG_PWORD(herb->query_herb_name())) +".");

   if (!herbs) herbs = ({ herb->query_herb_name(), herb_file, 1,
           herb->query_herb_value() });
   else
      herbs += ({ herb->query_herb_name(), herb_file, 1,
          herb->query_herb_value() });
   herb->remove_object();
   save_object(HERBAL_SAVE);
   return 1;
}
int
sell(string str)
{
   object herb;
   int price, asked_for, hn;
   mixed herbmsg;
   string tmpmsg, *tmparr;

   asked_for = 0;

    if (!CAN_SEE(this_object(), this_player()))
    {
        command("say Interesting, indeed, that a spirit of "+
            "air would speak with me.");
        command("say I cannot deal with those I cannot see!");
        return 1;
    }
    if (IS_INFIDEL(this_player()))
    {
        command("say I am not permitted to trade with you.");
        command("say Leave me, or I will call the guards.");
        return 1;
    }


   if (!str || !present(str,TP)) {
      command("say WhatDoYouWantToSell?");
      command("giggly inan");
      return 1;
   }
   herb = present(str,TP);

   if (!function_exists("create_herb",herb)) {
      command("say IOnlyWantHerbs.");
      return 1;
   }
   herbmsg = herb->query_prop(OBJ_M_NO_SELL);
   if (stringp(herbmsg))
   {
      tmpmsg = herbmsg;
      tmpmsg = lower_case(tmpmsg);
      tmparr = explode(tmpmsg, " ") - ({ "", " ", 0 });
      tmparr = map(tmparr, capitalize);
      tmpmsg = implode(tmparr, "");
      command("say IDontWantToBuyThat." + tmpmsg + ".GoSomewhereElsePlease.");
      return 1;
   }
   else if (intp(herbmsg) && herbmsg != 0)
   {
      command("say IDontWantToBuyThat.GoSomewhereElsePlease.");
      return 1;
   }

   if (herb->do_id_check(TO)) {
      price = herb->query_herb_value()/2;
      switch(random(4)) {
         case 0: command("say I'mAmazedItIs" +
            capitalize(herb->query_herb_name()) + "!"); break;
         case 1: command("say OhMy,AReal"+
            capitalize(herb->query_herb_name())+"!"); break;
         case 2: command("say Hmm...Goody! A" +
            capitalize(herb->query_herb_name())+"!"); break;
         case 3: command("say Neat! A" +
            capitalize(herb->query_herb_name())+"!"); break;
       }
   }
   else {
      command("gasp");
      command("say HoleyMoley!NeverSeenThisOneBefore!");
      command("emote blinks rapidly.");
      command("think");
      command("say I'llPayYou"+herb->query_herb_value()+"CoppersForThis,"+
         ((TP->query_gender() == G_MALE) ? "Sir" : "Ma'am") +"!");
      price = herb->query_herb_value();
   }
   if((hn = member_array(herb->query_herb_name(),herbs)) > -1)
      {
      if(herbs[hn+2] > MAX_HERBS)
         {
         price = price/2;
         command("say ICan'tGiveYouFullPriceForThe" +
            capitalize(herb->query_herb_name()) + ".");
         command("say IAlreadyHave" + capitalize(LANG_WNUM(herbs[hn+2])) +
             "OfTheSame!");
      }
   }
   do_pay(TP, price);
   add_herb(herb);
   if(asked_for)
      {
      command("say ThankYou.");
      asked_for = 0;
   }
   return 1;
}
void
not_herb(mixed hf)
{
   command("say IDon'tCareAboutAnythingButHerbs!");
   switch(random(4)) {
      case 0: command("say WhyWouldIWantASilly"+
         capitalize(hf[0]->query_name())+"?"); break;
      case 1: command("say IAmTooBusyForAStupid"+
               capitalize(LANG_PWORD(hf[0]->query_name()))+"," +
               capitalize(hf[1]->query_race_name())+"."); break;
      case 2: command("say IAmAHerbMerchant,"+
         capitalize(hf[1]->query_race_name())+
         ",NotAStupidPawnshopOwner!"); break;
      case 3: command("say IDon'tWantThis"+
         ((TP->query_gender() == G_MALE) ? "Mister" : "Ma'am")+"."); break;
   }
   command("give "+hf[0]->query_name()+" to "+hf[1]->query_real_name());

}
void
give_back_immediately(mixed hf)
{
   command("say PleaseWait'TillI'mDoneWithThisOtherHerb,"+
      ((hf[1]->query_gender() == G_MALE) ? "Sir" : "Ma'am")+".");
   command("give "+hf[0]->query_name()+" to "+
      hf[1]->query_real_name());
}
int
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
          id_str = "EvenKidsRecognizeThisOne.";
          break;
      case 1: command("giggle");
          id_str = "Hmm...OneOfTheEasiestRecognizableHerbs.";
          break;
      case 2: command("giggle");
          id_str = "Ahh..ThisIsAGoodOne. SometimesPeopleThinkItIsSomethingElse.";
          break;
      case 3: command("frown");
          id_str = "I'veSeenThisOneALot. EasilyMistakenThough.";
          break;
      case 4: command("smile");
          id_str = "Ah - ICan'tBlameYouForNotRecognizingThisOne.";
          break;
      case 5: command("bounce");
          id_str = "Exciting! ThisOneIsHardToTellFromTheCrimbulHerb.";
          break;
      case 6: command("think");
          id_str = "MyDearFriend - YouNeedToBeQuiteSkilledToIdentifyThisOne.";
          break;
      case 7: command("smile excit");
          id_str = "Oh! CanItReallyBe...? Ah...YesItIs!";
          break;
      case 8: command("gasp");
          id_str = "ByTheSource! ThisIsAToughy!";
          break;
      case 9: command("gasp");
          id_str = "OhMyDear. NotEvenSureAboutThisOne. ButItMustBe.";
          break;
      case 10..20: command("jump");
          id_str = "Impossible! AbsolutelyImpossible! ItJustCan'tBe?!";
   }
   command("say "+id_str);
   command("emote starts to speak slowly and clearly, reciting from memory.");
   if (given_herb->do_id_check(TO))
      command("say "+given_herb->query_id_long());
   else command("say IDoNotKnowWhatThisOneDoes.");
   command("give "+given_herb->query_name()+" to "+player->query_real_name());
   command("say IHopeIHaveBeenHelpful,"+
      ((player->query_gender()==G_MALE) ? "Sir" : "Ma'am")+".");
   command("bow");
   given_herb = 0;
   return 1;
}
void
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
   return;
}
string
close_open()
{
   if(closed)
      {
      closed = 0;
      return " *** Shillish is now ready to teach! *** \n";
   }
   closed = 1;
   return " *** Shillist will not teach anymore now! *** \n";
}

int
query_closed() { return closed; }

public void
emote_hook(string emote, object actor, string adverb)

{
    if (emote == "bow")
    {
        command("bow " + actor->query_real_name());
        command("say HowCanIHelpYou?");
    }
}

void
remove_tmp_flag() { no_report_flag = 0; }

