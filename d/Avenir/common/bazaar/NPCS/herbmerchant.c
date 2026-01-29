#pragma strict_types
// creator(s):  Borrowed from Elessar's Herbalist (Elessar, July 17th 1992)
//              Updated for the Bazaar area by Ilyian (May 1995)
// last update: Lilith, Typed the functions and added some asks. May 97.
//              Denis, May'97: Regular updates: triggers and such.
// purpose:     To buy and sell herbs.
//              Herbmerchant for the Apothecary in the Bazaar
// modification log:
//   9 Sept 2002 - Manat - Added code for OBJ_M_NO_SELL and OBJ_M_NO_BUY
//   10 Nov 2007 Lucius: MASSIVE cleanup and recode, several enhancements
//                       fixes and whatnot.
//   02 Jul 2008 Lucius: Added munge() to gnomify proper names/nouns.
//   19 May 2021 Shanoga: Removed "herb_file" from add_herb as it was
//                        causing herbs to be saved with an underscore
//                        in the name and prevented players from buying
//                        the herbs. Using hname (query_herb_name).
//
// note:        Training routines removed.
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";
inherit "/lib/trade";

#include <cmdparse.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/relation.h"

#define HERBAL_SAVE     "/d/Avenir/common/bazaar/NPCS/merchant_herbs"
/* The maximum number of herbs herbalist will keep of one type */
#define MAX_HERBS 35
#define MAX_XFER              20  /* buy/sell <= 20 at a time */
#define MAX_XFER_WORD         "twenty"

private static string get_type, name;
private static int *money_arr, NUM = sizeof(MONEY_TYPES);
private static object given_herb;
private static mapping herbs = ([]);
public void   do_sell_all(object player);
public int    herb_filter(object ob);
public void   do_pay(object player, int price);
public void   restore_herbs();


public void
create_monster(void)
{
    if (!IS_CLONE)
	return;

    setuid();
    seteuid(getuid());

    set_name("shillish");
    add_name("herbalist");
    set_race_name("gnome");
    set_living_name("shillish");
    set_title("the Veteran Herbalist of Sybarus");
    set_adj("wide-eyed");
    add_adj("friendly");
    set_long("This little fellow smells strongly of mint and sage. "+
      "He seems to be quite knowledgeable in the field of Herblore. "+
      "You can buy and sell herbs with him.");

    set_stats(({ 55, 55, 60, 99, 98, 55 }));
    set_base_stat(SS_OCCUP, 75);
    refresh_living();

    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(CONT_I_WEIGHT,63000);
    add_prop(CONT_I_HEIGHT,174);

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

    restore_herbs();
}

public void
arm_me(void)
{
    clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);
    command("wear all");
}

public string
pouch_ask(void)
{
    command("say Havec Sackseller has a blue tent just south of the "+
      "entrance to Icky Bod's Pub. He sells pouches and other "+
      "things, like saddlebags and scrips.");

    return "";
}

public string
default_answer(void)
{
    command("emote looks around as though he is worried about something.");
    command("say I'mOnlyPermittedToDiscussHerbs!");
    return "";
}

public void
announce_selling(void)
{
    if (herbs)
	command("say IHaveHerbsForSaleTooWouldYouLikeSome?");
    else
	command("say IShouldGoAndSearchForMoreHerbs.");
}

/*
 * Function name: restore_herbs
 * Description  : restore our inventory of herbs
 */
 public void
 restore_herbs()
 {
     //Uncomment the next line, and comment out the line after that
     //to convert the herbalist_herbs.o file once we transfer. Load
     //and clone the herbalist (or update the room) and then do:
     //Call herbalist do_herb_save ... Now you can switch the comment
     //out again, or simply remove this.
     //restore_object(HERBAL_SAVE);
     herbs = restore_map(HERBAL_SAVE)["herbs"];
 }

private void
remove_herb(string str, string hname, int amount)
{
    herbs[hname][1] -= amount;

    if (herbs[hname][1] < 1)
    {
	if (amount == 1)
	    command("say Drat! ThatWasMyLast"+ CAP(str)+"!");
	else
	    command("say Drat! ThoseWereMyLast"+ CAP(LANG_PWORD(str)) +"!");

	command("sob");
	m_delkey(herbs, hname);
    }

    save_map( ([ "herbs" : herbs ]), HERBAL_SAVE );
}

private int
can_afford(int price)
{
    if (sizeof(money_arr = pay(price, TP, 0, 0, 0, get_type)) == 1)
	return 0;

    string coin_pay_text = text(exclude_array(money_arr, NUM, NUM * 2 - 1));
    string coin_get_text = text(exclude_array(money_arr, 0, NUM - 1));

    write("You pay "+ coin_pay_text +".\n");

    if (strlen(coin_get_text))
	write("You get "+ coin_get_text +" back.\n");

    return 1;
}

private string
munge(string str)
{
    string *sarr = explode(str, " ");

    if (sizeof(sarr) < 2)
	return CAP(str);

    return implode(map(sarr, capitalize), "");
}

private int
do_buy(string str, string hname, int amount)
{
    object herb;
    mixed herbmsg;

    if (!objectp(herb = clone_object(herbs[hname][0])))
    {
	command("say Hmm....I'mReallySorry - ItSeemsToHaveDecayed...");
	command("cry");
	return 1;
    }

    if (strlen(herbmsg = herb->query_prop(OBJ_M_NO_BUY)))
    {
	string *tmparr = explode(lower_case(herbmsg), " ");
	tmparr -= ({ "", " ", 0 });
	tmparr = map(tmparr, capitalize);
	herbmsg = implode(tmparr, "");

	herb->remove_object();
	command("say ICouldn'tSellThatHerbToYou. " + herbmsg + ".");
	return 1;
    }
    else if (herbmsg)
    {
	herb->remove_object();
	command("say ICouldn'tSellThatHerbToYou. It'sForASpecialCustomer.");
	return 1;
    }

    if (amount > herbs[hname][1])
	amount = herbs[hname][1];

    if (!can_afford(amount * herbs[hname][2]))
    {
	command("say WhyDoYouAskWhenYouCannotAffordIt?");
	command("frown");
	return 1;
    }

    int count = amount;
    object *moved, *sold = ({ herb });
    while (--count > 0)
	sold += ({ clone_object(herbs[hname][0]) });

    moved = filter(sold, not @ &->move(TP));

    command("emote picks up "+ (sizeof(sold) > 1 ?
	    "some herbs" : "an herb") + " from a little pouch.");
    command("say IHopeItWillBeUseful,"+
	(TP->query_gender() == G_MALE ? "Sir" : "Ma'am")+ "!");

    if (sizeof(moved))
    {
	write(TO->query_The_name(TP) +" hands you "+
	    COMPOSITE_DEAD(moved) +".\n");
	say(QCTNAME(TO) +" gives "+ QCOMPDEAD +" to "+
	    QTNAME(TP) +".\n");
    }
    
    if (sizeof(sold -= moved))
    {
	sold->move(ENV(TO));
	command("say YouCannotSeemToHoldThemAll!");
	command("emote sets "+ COMPOSITE_DEAD(sold) +
	    " on the ground.");
    }

    remove_herb(str, hname, amount);
    return 1;
}

public int
buy(string str)
{
    if (!strlen(str))
	return NF(CAP(query_verb()) +" what?\n");

    if (!CAN_SEE_IN_ROOM(TO))
    {
	command("say BringInSomeLightFirst. ICannotSeeAThing!\n");
	return 1;
    }

    if (!CAN_SEE(TO, TP))
    {
	command("say ICannotDealWithThoseICannotSee!");
	return 1;
    }

    if (IS_INFIDEL(TP))
    {
	command("emote blinks rapidly.");
	command("say IAmNotPermittedToTradeWithYou!");
	return 1;
    }

    str = lower_case(str);

    if (query_verb() == "list")
    {
	string *arr = ({ });;

	if (!m_sizeof(herbs))
	{
	    command("say I'mSorryIHaveNoMoreHerbsForSale!");
	    command("sigh");
	    return 1;
	}

	if ((str != "herb") && (str != "herbs"))
	{
        string hname = str;
        //string hname = implode(explode(str, " "), "_");

	    if (!herbs[hname])
	    {
		command("say IDon'tHaveAny"+ munge(str) +"!");
		return 1;
	    }

	    arr = ({ hname });
	}
	else
	{
	    arr = sort_array(m_indexes(herbs));
	}

	command("say IHave...");

	foreach(string key : arr)
	{
	    int amt = herbs[key][1];
	    string name = implode(explode(key, "_"), " ");
	    write(sprintf("  %3d %-s for %d coppers each.\n",
		    amt,
		    (amt > 1 ? LANG_PWORD(name) : name),
		    herbs[key][2]));
	}

	if (sizeof(arr) > 50)
	    command("pant breathlessly");
	else
	    command("smile absent "+ OB_NAME(TP));

	return 1;
    }

    string hname = "";
    int amount = 1;

    if (sscanf(str, "%d %s", amount, hname) != 2)
    {
	if (sscanf(str, "all %s", hname))
	    amount = 999;
    }

    if (strlen(hname))
	str = hname;
    hname = str; //hname = implode(explode(str, " "), "_");

    if (hname == "herbs")
    {
	command("say YouDon'tWantToBuyAllMyHerbs,DoYou?");
	command("say MaybeYouShouldAskForAListOfHerbsToHelpYouChoose.");
	return 1;
    }    
    
    if (!herbs[hname])
    {
	command("say ButIDon'tEvenHaveAny"+ munge(str) +"InStock!");
	command("bounce anxiously");
	return 1;
    }

    say(QCTNAME(TP)+" asks "+ QTNAME(TO) +" for an herb.\n");
    command("emote starts looking through his herb-storage.");

    if (do_buy(str, hname, amount))
	return 1;

    command("say I'mDeeplySorry,"+ (TP->query_gender() == G_MALE ?
	    "Sir" : "Ma'am")+ ",ButIHaveNoneOfThose.");
    command("sigh heartbrokenly");
    return 1;
}

private void
add_herb(object herb_ob)
{
    string hname, herb_file;
    int    i, n, amount;
    mixed *hdata;

    if (!objectp(herb_ob))
    {
        return;
    }

    hname = herb_ob->query_herb_name();
    herb_file = MASTER_OB(herb_ob);
    amount = herb_ob->num_heap() || 1;

    if (pointerp(hdata = herbs[hname]))
    {
		// Some herb files had an invalid filename - replace it.
		// This may help if the herb was moved as well.
        hdata[0] = herb_file;
        hdata[1] += amount;

        if (IS_HEAP_OBJECT(herb_ob))
        {
            herb_ob->restore_heap();
            herb_ob->set_heap_size(herb_ob->num_heap() - amount);
        }
        else
        {
            herb_ob->remove_object();
        }

        return;
    }

    command("say Excellent!IHadRunOutOf " + hname + ".");
    hdata = allocate(3);
    hdata[0] = herb_file;
    hdata[1] = amount;
    hdata[2] = herb_ob->query_herb_value();
    herbs[hname] = hdata;

    if (IS_HEAP_OBJECT(herb_ob))
    {
        herb_ob->restore_heap();
        herb_ob->set_heap_size(herb_ob->num_heap() - amount);
    }
    else
    {
        herb_ob->remove_object();
    }
    save_map( ([ "herbs" : herbs ]), HERBAL_SAVE );
}

/*
 * Function name: sell
 * Description  : handle attempts to sell herbs
 * Arguments    : string arg -- whatever the player typed
 * Returns      : 1 -- always
 */
 public int
 sell(string arg)
 {
     int price, asked_for, hn, amount;
     object herb_ob, *obj;
     mixed *hdata, nosell;
     string hname;
 
     tell_room(ENV(TO), QCTNAME(TP) + " murmurs something to " +
         QTNAME(TO)+".\n", TP);
 
     if (!CAN_SEE_IN_ROOM(TO))
     {
        command("say BringInSomeLightFirst. ICannotSeeAThing!\n");
        return 1;
     }

     if (!CAN_SEE(TO, TP))
     {
        command("say ICannotDealWithThoseICannotSee!");
        return 1;
     }

     if (IS_INFIDEL(TP))
     {
	    command("emote blinks rapidly.");
	    command("say IAmNotPermittedToTradeWithYou!");
	    return 1;
     }

     
     else if (!strlen(arg))
     {
         command("say WhatDoYouWantToSell?");
         command("giggly inan");
         return 1;
     }
 
     arg = lower_case(arg);
 
     if (arg == "all herbs" || arg == "all")
     {
         do_sell_all(TP);
         return 1;
     }
     else if (!sizeof(obj = FIND_STR_IN_ARR(arg, all_inventory(TP))))
     {
         command("say WhatDoYouWantToSell?");
         command("smile");
         return 1;
     }
     else if (!sizeof(obj = filter(obj, herb_filter)) ||
       (!objectp(herb_ob = obj[0])))
     {
         command("say YouHaveNoHerbOfThatKind, " +
             ((TP->query_gender() == G_MALE ? "Sir" : "Ma'am") +"!"));
         return 1;
     }
 
     tell_room(ENV(TO), QCTNAME(TP) + " offers an herb to " +
         QTNAME(TO) + ".\n", TP);
 
     nosell = herb_ob->query_prop(OBJ_M_NO_SELL);
     if (nosell)
     {
         if (stringp(nosell))
             write(nosell);
 
             command("say IDontWantToBuyThat. GoSomewhereElsePlease.");
             return 1;
     }
 
     hname = herb_ob->query_herb_name();
     amount = herb_ob->num_heap() || 1; 
     if (herb_ob->do_id_check(TO))
     {
         price = (herb_ob->num_heap() || 1) * herb_ob->query_herb_value() / 2;
 
         switch(random(4))
         {
         case 0: command("say I'mAmazedItIs" +
               munge(herb_ob->query_herb_name()) + "!");
             break;
         case 1: command("say OhMy,AReal"+
               munge(herb_ob->query_herb_name())+"!");
             break;
         case 2: command("say Hmm...Goody! A" +
               munge(herb_ob->query_herb_name())+"!");
             break;
         case 3: command("say Neat! A" +
               munge(herb_ob->query_herb_name())+"!");
             break;
         }
     }
     else
     {
         price = (herb_ob->num_heap() || 1) * herb_ob->query_herb_value();
 
        command("gasp");
	    command("say HoleyMoley!NeverSeenThisOneBefore!");
	    command("emote blinks rapidly.");
	    command("think");
	    command("say I'llPayYouMoreCoppersForThis,"+
	    (TP->query_gender() == G_MALE ? "Sir" : "Ma'am") +"!");
 
     }

     do_pay(TP, price);
     add_herb(herb_ob);
      
     return 1;
 }
 
 /*
  * Function name: do_sell_all
  * Description  : handle "sell all herbs"
  * Arguments    : object player -- the person selling
  */
 public void
 do_sell_all(object player)
 {
     object *herb_obs;
     mixed hdata;
     string hname, sherb;
     int total_price, price, hn, max_n, no_h, n, amount;
 
     herb_obs = filter(filter(all_inventory(player), herb_filter),
         &operator(==)(0) @ &->query_prop(OBJ_M_NO_SELL));
     no_h = sizeof(herb_obs);
 
     if (no_h <= 0)
     {
         command("say ButYouHaveNoHerbsToSell!");
         command("shrug");
         return;
     }
 
     tell_room(ENV(TO), QCTNAME(TP) + " offers some herbs to " +
         QTNAME(TO) + ".\n", TP);
     max_n = MIN(MAX_XFER, no_h);
     
     while (n < max_n)
     {
         hname = herb_obs[n]->query_herb_name();
         amount = herb_obs[n]->num_heap() || 1;
 
         if (herb_obs[n]->do_id_check(TO))
             price = amount * herb_obs[n]->query_herb_value() / 2;
         else
             price = amount * herb_obs[n]->query_herb_value();
 
         if (pointerp(hdata = herbs[hname]) && hdata[1] > MAX_HERBS)
             price = price / 2;
 
         command("say " + capitalize(LANG_WNUM(amount)) + " " + hname +
             " - " + price + " coppers.");
 
         total_price += price;
          
         add_herb(herb_obs[n]);
         n++;
     }
 
    do_pay(player, total_price);
 }
 
 /*
  * Function name: do_pay
  * Description  : Pay the player. Maybe this should be changed one of
  *                these days to something in /lib/trade.c.
  * Arguments    : object player -- person to pay
  *                int price -- price in coppers
  */
 public void
 do_pay(object player, int price)
 {
     string myname;
     object gc, sc, cc;
     int gold, silver, copper;
 
     command("emote counts some coins from a pouch.");
     gold = price / 144;
     silver = (price - (gold * 144)) / 12;
     copper = price - gold*144 - silver*12;
     cc = MONEY_MAKE_CC(copper);
     myname = TO->query_The_name(player);
 
     if (gold)
     {
         gc = MONEY_MAKE_GC(gold);
         write(myname + " gives you " + gold + " gold coins.\n");
         gc->move(TP, 1);
     }
     if (silver)
     {
         sc = MONEY_MAKE_SC(silver);
         write(myname+" gives you " + silver + " silver coins.\n");
         sc->move(TP, 1);
     }
     if (copper)
     {
         cc = MONEY_MAKE_CC(copper);
         write(myname+" gives you " + copper + " copper coins.\n");
         cc->move(TP, 1);
     }
 
     command("smile");
 }

 /*
 * Function name: herb_filter
 * Description  : decide if argument is a herb
 * Arguments    : object ob -- the object of interest
 * Returns      : 1 if is herb, 0 if not
 */
public int
herb_filter(object ob)
{
    return (IS_HERB_OBJECT(ob) &&
        strlen(ob->query_herb_name()) && ob->query_herb_value());
}

public void
init_living(void)
{
    ::init_living();

    add_action(  buy, "buy"  );
    add_action(  buy, "list" );
    add_action( sell, "sell" );
}

private void
not_herb(object item, object from)
{
    command("say IDon'tCareAboutAnythingButHerbs!");

    switch(random(4))
    {
    case 0: command("say WhyWouldIWantASilly"+
	  munge(item->query_name())+"?");
	break;
    case 1: command("say IAmTooBusyForAStupid"+
	  munge(LANG_PWORD(item->query_name()))+"," +
	  munge(from->query_race_name())+".");
	break;
    case 2: command("say IAmAHerbMerchant,"+
	  munge(from->query_race_name())+
	  ",NotAStupidPawnshopOwner!");
	break;
    case 3: command("say IDon'tWantThis"+
	  ((from->query_gender() == G_MALE) ? "Mister" : "Ma'am")+".");
	break;
    }

    command("give "+ OB_NAME(item) +" to "+ OB_NAME(from));
}

private void
give_back_immediately(object herb, object from)
{
    command("say PleaseWait'TillI'mDoneWithThisOtherHerb,"+
      (from->query_gender() == G_MALE ? "Sir" : "Ma'am")+".");
    command("give "+ OB_NAME(herb) +" to "+ OB_NAME(from));
}

private void
test_identify(object from)
{
    string id_str;

    if (!CAN_SEE(TO, from))
    {
	command("say Hey! WhereDidMyCustomerGo!?");
	command("peer wonderingly");
	command("drop "+ OB_NAME(given_herb));

	given_herb = 0;
	return;
    }

    switch(given_herb->query_id_diff() / 10)
    {
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

    command("say "+ id_str);
    command("emote starts to speak slowly and clearly, reciting from memory.");

    if (given_herb->do_id_check(TO))
	command("say "+ given_herb->query_id_long());
    else
	command("say IDoNotKnowWhatThisOneDoes.");

    command("give "+ OB_NAME(given_herb) +" to "+ OB_NAME(from));

    command("say IHopeIHaveBeenHelpful,"+
      (from->query_gender() == G_MALE ? "Sir" : "Ma'am")+".");

    command("bow");
    given_herb = 0;
}

public void
enter_inv(object herb, object from)
{
    ::enter_inv(herb, from);

    if (!living(from))
	return;

    if (!CAN_SEE(TO, from))
    {
	set_alarm(0.5, 0.0, &command("say WhoGaveMeThis!?"));
	set_alarm(1.0, 0.0, &command("peer wildly"));
	set_alarm(1.5, 0.0, &command("drop "+ OB_NAME(herb)));
	return;
    }

    if (!function_exists("create_herb", herb))
    {
	set_alarm(1.0, 0.0, &not_herb(herb, from));
	return;
    }

    if (given_herb)
    {
	set_alarm(1.0, 0.0, &give_back_immediately(herb, from));
	return;
    }

    given_herb = herb;
    set_alarm(1.0, 0.0, &command("emote looks closely at the "+
	herb->query_name() +"."));
    set_alarm(2.5, 0.0, &command("think"));
    set_alarm(5.0, 0.0, &test_identify(from));
}

public void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "bow")
    {
	command("bow " + actor->query_real_name());
	command("say HowCanIHelpYou?");
    }
}

