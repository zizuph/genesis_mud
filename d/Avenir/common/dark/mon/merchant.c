// -*-C++-*-
// file name:   ~Avenir/common/dark/mon/merchant.c
// creator(s):  Boriska, 
//              /d/Genesis/doc/examples/trade/merchant.c 
//              (C) January 7th 1994 by Mercade
// last update: Jan 18, 1995 
//              Cirion, 051396 - Fixed some typos.
// purpose:     mobile shop for Avenir tunnels
// note:        Merchant's storeroom has a convinence function 
//              for wizards to determine where he is.
/*
 * Revisions:
 * 	Lucius, Jun 2017: Fix up the failure messages to be
 * 			  actual spoken messages.
 *  Lilith, May 2022: updated descs, chats, etc to reflect 
 *       his status as a banker.
 *
 */
inherit "/std/monster";
inherit "/lib/shop";
inherit "/d/Avenir/inherit/intro";

#include <money.h>
#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/merchant.h"

static object to = this_object(), pony, store;

string
my_long()
{
    string  str;

    str =  "He is "+ LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    str += "This fellow is a very dirty and very brave gnome.\n"+
	       "He looks like he's been conducting business with "+
	       "the denizens\nof the Underdark for a very, very long time.\n"+
           "You find yourself wondering when he last had a bath.\n"+
           "He has a knee-length grey wizard beard.\n"+ 
		   "He has a wild silvery walrus mustache.\n"+
           "He has wild black eyes that seem to be looking "+
           "everywhere at once.\n"+
           "He is wearing a sign around his neck that reads:\n"+
           "   Amblo's Bank of the Underdark.\n";
    return str;
}

void
create_monster() 
{
    if ( !IS_CLONE )
	return;

    set_name("amblo");
    add_name("merchant");
    set_race_name("gnome");
    set_adj(({"deal-making", "dirty"}));
    add_name(({"banker", "merchant"}));
	set_title("ini Hu'garen the Merchant Banker of the Underdark");
    set_long(my_long);
    set_gender(G_MALE);

    set_stats ( ({ 100,100,100,100,100,100 }) );

    set_skill(SS_DEFENCE,      100);
    set_skill(SS_AWARENESS,    100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_ACROBAT,      100);

    add_prop(LIVE_I_SEE_DARK, 2);
//    add_prop(OBJ_M_NO_MAGIC_ATTACK, "A dark aura flashes, protecting "+
//        "him from your magic.\n");

    //  set_random_move(120, 1);
    set_chat_time (3);
    add_chat("ItIsHardToFeedMyPonyInTheseTunnels.");
    add_chat("ITradeWithTheEntireWorld.");
    add_chat("MyGoodsAreMostlyWhatICanFindAroundHere.");
    add_chat("ThereAreHorribleThingsLivingDeepUnderGround.");
    add_chat("ICanHearThemDiggingTheirWayOut.");
    add_chat("WhenTheyBreakThroughWeAllWillDie.");
    add_chat("AllKindsOfFolkWanderAroundHere.BeCareful.");
    add_chat("IHopeThoseDeepOgresDon'tManageToGetOut.");
    add_chat("ICanMakeChangeIfYouNeedIt.");
    add_chat("IHaveExpandedMyServicesToIncludeBanking.");
    add_chat("AWealthOfSilverAndGoldAndGems!");
    add_chat("IAmTheOnlyOneWhoTradesWithTheOgres.");
    add_chat("IHaveLearnedALotAboutTheDeepOgres.");
    add_chat("IKeepThinkingIWillRetireSoonButWhoAmIKidding?");
    add_chat("@@store_chat@@");

    set_default_answer("say IAmTooBusyStayingAliveToAnswerQuestionsSorryNotSorry.", 1);
    config_default_trade();
    set_money_give_max(10000);

    seteuid(getuid());

    set_store_room(STORE);
    STORE->set_merchant(this_object()); // tell the store room we're out and kicking

    set_alarm(3.0, 0.0, "make_pony");
}

/* Get more attacks in */
void add_attacks()
{
    query_combat_object()->cb_set_attackuse(300);
}

string race_sound()
{
    string *sounds = ({ "babbles", "mutters", "murmurs", "sighs", "chats" });
    return one_of_list(sounds);
}

string store_chat()
{
    object *inv;
    string desc;

    if (!store || !sizeof(inv = all_inventory(store)))
    {
	command("say IWishIHadSomethingToSellButIDon't.");
	return "";
    }

    desc = inv[random(sizeof(inv))]->short();
    desc = implode(explode(desc, " "), ""); // Get rid of the spaces

    command("say IHaveAVeryNice"+desc+"ForSaleRealCheapDoYouWantToBuyIt?");
    return "";
}

private void make_pony()
{
    pony = clone_object(PONY);
    say("You hear a sound of horse hooves clicking against the rock.\n");
    pony->move_living("xx", environment());
    pony->set_merchant(to);
    command("cuddle pony");
    store = find_object(STORE);
    team_join(pony); 
}

void
init_living()
{
    ::init_living();
    init_shop();
}

/*
 * Function name: shop_hook_sold_items
 * Description:   Hook that is called when player sold something
 * Arguments:	  item - The item array player sold
 * Returns:	  1
 */
int
shop_hook_sold_items(object *item)
{
    write("You sold " + COMPOSITE_DEAD(item) + ".\n");
    say(QCTNAME(this_player()) + " sold " + QCOMPDEAD + ".\n");
    say(QCTNAME(to) + " loads " + QTNAME(pony)+" with the newly " +
      "bought item" + (sizeof(item) > 1 ? "s" : "" ) + ".\n");
    pony->command("grumble");
    return 1;
}

/*
 * Function name: shop_hook_bought_items
 * Description:   Called when player has bought something
 * Arguments:	  arr - The array of objects
 * Returns: 	  1
 */
int
shop_hook_bought_items(object *arr)
{
    say(QCTNAME(TO) + " unloads "
      + (sizeof(arr) <= 1 ? "something" : "some things")
      + " from " + QTNAME(pony) + ".\n");
    write("You bought " + COMPOSITE_DEAD(arr) + ".\n");
    say(QCTNAME(TP) + " bought " + QCOMPDEAD + ".\n");
    pony->command("stretch");
    return 1;
}

/*
 * Function name: shop_hook_value_no_match
 * Description:   Called if there were no match with what the player asked
 *		  about
 * Arguments:     str - The string player asked about
 * Returns:	  0
 */
int
shop_hook_value_no_match(string str)
{
    command("say Sorry,IHaveNo'" + implode(explode(CAP(str), " "), " ") 
      + "'YouAreTalkingAbout.");
    return NF("");
}

/*
 * Function name: shop_hook_list_empty_store
 * Description:   If the storeroom is empty when the player wants a list
 *		  of its items
 * Arguments:	  str - If player specified string
 */
void
shop_hook_list_empty_store(string str)
{
    if (!present(pony, ENV(TO)) || pony->query_no_show())
    {
	command("say MyPonyIsNotHere,SoIHaveNowhereToStoreGoods!");
	NF("");
	return;
    }

    say(QCTNAME(TO) + " checks through the packs on " + QTNAME(pony)
      + " but comes up emptyhanded.\n");
    pony->command("shrug");
    command("say IHaveNothingLeftToSell!");
    NF("");
}

/*
 * Function name: shop_hook_list_no_match
 * Description:   Called if player specified the list and no matching
 *		  objects where found
 * Arguments:	  str - The string he asked for
 * Returns:	  0
 */
int
shop_hook_list_no_match(string str)
{
    if (!present(pony, ENV(TO)) || pony->query_no_show())
    {
	command("say MyPonyIsNotHere,SoIHaveNowhereToStoreGoods!");
	return NF("");
    }

    pony->command("shrug");
    command("say SorryICannotFindAny'"+str+ "'!");
    return NF("");
}

/*
 * This function is called from add_action(.., "read"), but since we
 * are not in a shop, we do not have a sign with instructions either.
 * This blocks that function.
 */
int
do_read(string str)
{
    return 0;
}

/*
 * Function name: shop_hook_allow_sell
 * Description:	  If you want to do more testing on objects the player intend
 *		  to sell.
 * Argument:	  ob - The object player wants to sell
 * Returns:	  1 if we allow player to sell the object (default)
 */
int
shop_hook_allow_sell(object ob)
{
    if (!present(pony, ENV(TO)) || pony->query_no_show())  // no pony 'present'
    {
	command("say MyPonyIsGoneICannotBuyAnything.");
	return 0;
    }

    // check the store room and disable selling if it is full
    if ( sizeof(all_inventory(store)) >= MAX_STORE )
    {
	pony->command("cry");
	command("say SorryMyPonyCannotCarryAnyMore.ComeBackLater.");
	return 0;
    }

    return 1;
}

void
do_die(object killer)
{
    if (!pony->query_no_show() || !present(pony, ENV(TO)))  // pony is here.
    {
	say("Taking his last breath, "+QTNAME(TO)+" manages to "
	  +"free his pony and let him go.\n"+QCTNAME(pony)
	  +" runs away.\n");
    }

    pony->remove_object();
    store->set_merchant(0);  // remember the fact of merchant's death so
    // it will be cloned when his start room resets.
    ::do_die(killer);
}

private void gone()
{
    store->set_merchant(0);

    command("frown");
    command("say MyPonyIsGone,ThereIsNothingForMeToDoHere.");
    command("say GoAndFindAnotherFoolToTradeWithYou.");
    run_away();
    remove_object();
}

// called from do_die() in pony.
void pony_died()
{ 
    set_alarm(6.0, 0.0, gone);
}

int query_not_attack_me(object who, int aid)
{
    mixed comm;
	who->catch_msg(QCTNAME(this_object()) +" easily dips out of reach, "+
    "causing you to miss. How frustrating!\n");
	
	comm = (({"emote laughs as he skips aside.",
	"say NitikasHasBlessedMeSoYouShouldJustStop.",
    "emote is surrounded momentarily by a golden aura.",
    "say to "+ OB_NAME(who) +" YouKeepTryingToKillMeIWon't"+
    "TradeWithYouAnymore.",
	"say to "+ OB_NAME(who) +" YouWillEmbarassYourself"+
    "TryingToKillMe.JustGiveUp.TheOgresFinallyDid.",
    "say to "+ OB_NAME(who) +" YouShouldPickOnSomeoneYour"+
    "OwnSizeThenMaybeYouWillWin.",
    "say to "+ OB_NAME(who) +" ICanDoThisAllDayCanYou?",
    "emote dodges another attack.",
    "emote makes evading attacks look easy.",
    "say to "+ OB_NAME(who) +" ThereAreReasonsI'veManagedTo"+
    "LiveSoLongDownHere.",
    "say to "+ OB_NAME(who) +" You'reBoringMe.WouldYouStopAlready?",
    "yawn", "emote inspects his nails while he fights."
    }));	
	
    command(one_of_list(comm));
    return 1;
}