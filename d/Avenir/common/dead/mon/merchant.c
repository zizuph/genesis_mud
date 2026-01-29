// -*-C++-*-
//              ~Avenir/common/holm/mon/merchant.c taken from:
// file name:   ~Avenir/common/dark/mon/merchant.c
// creator(s):   Lilith Aug 2014
// last update:  Lilith Aug 2021: Updated chats for Catacombs opening.
// purpose:     shop for Necronisi
// note:        Merchant's storeroom has a convinence function 
//              for wizards to determine where he is.
// bug(s):
#pragma strict_types

inherit "/std/monster";
inherit "/lib/shop";
inherit "/d/Avenir/inherit/intro";

#include <money.h>
#include <ss_types.h>
#include <composite.h>
#include "/d/Avenir/include/relation.h"
#include "../dead.h"

#define STRRM        "/d/Avenir/common/dead/path/m_store.c"
#define TROBY        MON + "merchant_porter"
#define MERCHANT     MON + "merchant"
#define MAX_STORE    200
#define SELL_PERIOD  1000.0
#define PONY_ABSENCE 20.0

static object to = this_object(),
               pony, store;

void
create_monster() 
{
    if ( !IS_CLONE )
        return;
  
    set_name("gulgarmesh");
    add_name("merchant");
    set_race_name("gnome");
    set_adj(({"dark-eyed", "congenial"}));
    set_title("ini Wer'a, Merchant Extraordinary");
    set_short("dark-eyed congenial gnome");
    set_long("@@my_long@@");
    set_gender(G_MALE);
  
    set_stats ( ({ 150,200,150,100,200,100 }) );
  
    set_skill(SS_DEFENCE,      100);
    set_skill(SS_AWARENESS,    100);
    set_skill(SS_UNARM_COMBAT, 100);
  
    add_prop(LIVE_I_SEE_DARK, 1);
    set_restrain_path(({ DEAD }));
    set_monster_home( PATH +"shore24");

    set_chat_time(10);
      add_chat("ItIsHardToMakeALivingHere.FewCustomers."+
          "TheyAllGetScaredOff.ExceptTheGoblins.");
      add_chat("ITradeWithAnyone.");
      add_chat("SomeDaysBusinessIsGood.OthersItIsNot.");
      add_chat("DoYouHaveSomethingYouWantToSell?IBuyAlmostAnything.");
      add_chat("NitikasCommandedMeHere.ButIAmAfraidMascarvinWillTake"
	      +"Notice.");
	  add_chat("IfYouHaveGraveGoodsIWillBuyThem.MyLordNitikasIs"
	      +"VeryInterestedInTheMoreUniqueAndBeautifulPieces.");
      add_chat("SomeValuableThingsCanBeFoundInTheCatacombs.");
      add_chat("DoWeChooseWhoWeServeOrDoTheyChooseUs?");
      add_chat("ItTookMeMonthsToTrainMyTrolobyNotToRunFromTheUndead"
	      +"InTheMarshes.");
      add_chat("IHaveACousinWorkingInTheUtterdark.HeIsBraveButI"
          +"AmBraver.");
      add_chat("TheArmyOfUndeadWaitsHere.TheOnesWhoDiedInShameAre"
	      +"Above.TheOnesWhoDiedInGraceAreBelow.");
      add_chat("AllIsGoodThatPleasesTheGods.");
      add_chat("@@store_chat@@");

    set_default_answer(VBFC_ME("what_me"));
    config_default_trade();
    set_money_give_max(3000);

    seteuid(getuid());
  
    set_store_room(STRRM);
    // tell the store room we're out and kicking
    STRRM->set_merchant(this_object()); 
  
    set_alarm(3.0, 0.0, "make_pony");
}

string
my_long()
{
    string  str;

    str = "He is "+ LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    if (TP->query_met(query_real_name()))
    {
        str = query_name() +
            " is "+ LANG_ADDART(implode(query_adjs()," ")) +
            " "+ query_race_name() +", presenting himself as:\n" +
            query_name();
        if (strlen(query_title()))
            str += " "+ query_title() +",";
        str += " "+ query_exp_title() +", male "+ 
            query_race_name() +".\n";
    }

     str += "He is from a family of well-known traveling merchants.\n"+
	     "His reddish hair is long and held in place by a braided "+
         "leather thong.\nHis dark eyes are nervously scanning "+
         "the area.\nHe is wearing a green belted short-coat and pair "+
		 "of lavender trews with a large codpiece.\n";
    return str;
}

string
what_me()
{
    switch(random(4))
    {
        case 0:
            command("say I am not permitted to answer that question.");
            break;
        case 1:
            command("say I buy and sell goods. That is the whole of my "+
                "knowledge");
            break;
        case 2:
            command("emote struggles to answer, but does not seem able "+
                "to get the words out.");
            break;
        case 3:
            command("say Would that I could, but I cannot say.");
            break;
    }
    return "";    
}
 
string race_sound()
{
  string  *sounds = ({ "babbles", "mutters", "sighs", "chatters" });
  return sounds[random(sizeof(sounds))];
}

string store_chat()
{
    object   *inv;
    string    desc;

    if (!store || !sizeof(inv = all_inventory(store)))
        return "IWishIHadSomethingToSellButIDon't.";

    desc = inv[random(sizeof(inv))]->short();
    desc = implode(explode(desc, " "), ""); // Get rid of the spaces
    return "IHaveAVeryNice"+desc+"ForSaleRealCheapDoYouWantToBuyIt?";
}

private void make_pony()
{
    pony = clone_object(TROBY);
    tell_room(ENV(TO), "You hear the sound of hooves pounding into soil.\n");
    pony->move_living("xx", environment());
    pony->set_merchant(to);
    to->command("emote takes the leash hanging from the troloby's "+
        "neck.");
    store = find_object(STRRM);
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
    to->command("emote loads his troloby with the newly " +
       "bought item" + (sizeof(item) > 1 ? "s" : "" ) + ".");
    pony->command("emote shifts under the new weight.");
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
    to->command("emote unloads "
        + (sizeof(arr) <= 1 ? "something" : "some things")
        + " from his troloby's pack.\n");
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
    NF("The gnome merchant says: Sorry,IHaveNo'" 
        + implode(explode(CAP(str), " "), " ") 
        + "'YouAreTalkingAbout.\n");
        return 0;
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
    if(!present(pony, ENV(TO)) || pony->query_no_show())
    {
        NF("The gnome merchant says: MyPonyIsNotHere,SoIHaveNowhereToStoreGoods!");
        return;
    }

    tell_room(ENV(to), "The gnome merchant checks through the packs on " 
        + QTNAME(pony) + " but comes up empty-handed.\n");
    NF("The gnome merchant says: IHaveNothingLeftToSell!\n");
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
        NF("The gnome merchant says: MyTrolobyIsNotHere,"+
            "SoIHaveNowhereToStoreGoods!HeWillBeBackSoonHe"+
			"IsGettingAFreshPack.");
        return 0;
    }

    NF("The gnome merchant says: SorryICannotFindAny" +str+ "!\n");
    return 0;
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
    if (!present(pony, ENV(TO)) || pony->query_no_show())  
    {
        NF("The gnome merchant says: MyTrolobyIsGoneICannotBuyAnything.\n");
        return 0;
    }
  
  // check the store room and disable selling if it is full
    if( sizeof(all_inventory(store)) >= MAX_STORE )
    {
        pony->command("groan");
        NF("The gnome merchant says: SorryMyTrolobyCannotCarryAny"+
            "More.JustAMinuteThatsAllINeed.\n");
        return 0;
    }

    return 1;
}

void
do_die(object killer)
{
    if (!pony->query_no_show() || !present(pony, ENV(TO)))  
    tell_room(ENV(to), "The gnomish merchant relinquishes his hold "+
        "the troloby's leash.\nThe troloby runs away.\n");

    pony->remove_object();
    store->set_merchant(0);  // remember merchant's death so it will 
                            // be cloned when his start room resets.
  ::do_die(killer);
}

// called from do_die() in pony.
void pony_died() 
{ 
    set_alarm (6.0, 0.0, "gone"); 
}

private void gone()
{
    store->set_merchant(0);
  
    command("frown");
    command("say MyTrolobyIsGone,ThereIsNothingForMeToDoHere.");
    command("say GoAndFindAnotherFoolToTradeWithYou.");
    run_away();
    remove_object();
}


