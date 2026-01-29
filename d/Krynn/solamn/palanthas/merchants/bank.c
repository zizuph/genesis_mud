/* 
 * The bank in Palanthas
 *
 * Made by Nick
 */
#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/clubs/warfare/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

inherit MERCH_ROOMBASE;
inherit "/lib/bank";

#define STEEL_COIN   "/d/Krynn/common/warfare/rewards/krynn_steel_coin"
#define FEE 25

string
query_to_jail()
{
    return "north";
}

fee()
{
    set_bank_fee(FEE);
    config_trade_data();
    return;
}

string
standard_bank_sign()
{
    return "Our bank provides you with a cheap way to relieve " +
    "you of the burden of heavy coins and gems. For each " +
    "transaction we ask only a " +FEE+ "% fee.\n\nYou can:\n" +
    "   <account> [gems / banks]\n" +
    "   <deposit> [coins / gems]\n" +
    "   <minimize> coins\n" +
    "   <withdraw> <coins> [except for <coins>]\n" +
    "   <retrieve> [gems]\n" +
    "   <change> <type> coins to <type> coins\n\n" +
    "The Bank of Palanthas also provides safekeeping of " +
    "steel coins minted in Krynn. You can:\n\n" +
    "   <check> or <pcheck> safe-deposit box\n" +
    "   <bank> or <pbank> steel coins\n" +
    "   <draw> or <pdraw> steel coins\n\n";
}

/*
 * Function name: create_room
 * Description:   Set up default trade and configure it if wanted.
 */
void
create_palan_room()
{
    object xx;
    config_default_trade();
    set_short("The bank of Palanthas");
    set_long("This is the esteemed bank of Palanthas, where you " +
        "are able to exchange your hard-earned coins for a lighter " +
        "load, as long as you don't mind the 25% fee. There is a " +
        "small plaque on the wall.\n");
/*
    set_long("You are in the keep bank. Here a knight can exchange heavy " +
	     "coins into higher valued coins thus lowering the load to carry. " +
	     "However, we take a small fee for helping you: 15% of the value " +
	     "of the coins switched if you are a Knight of Solamnia, otherwise " +
	     "the fee is 25%. There is a small plaque on the wall.\n");
*/
    
    add_item("plaque",
	     "It contains instructions on how to exchange your money.\n");
    add_cmd_item("plaque", "read", "@@standard_bank_sign");
    
    config_trade_data();
    
    add_exit(MERCH + "m04", "north", 0, 0);

    xx = clone_object("/d/Genesis/obj/deposit");
    xx->set_bank_id(801, "Palanthas");
    xx->set_short("deposit");
    xx->set_no_show_composite(1);
    xx->set_sign_text(standard_bank_sign());
    xx->move(this_object());

}

change(string str)
{   
    fee();
    return ::change(str);
}

test(string str)
{
    fee();
    return ::test(str);
}

minimize(string str)
{
    fee();
    return ::minimize(str);
}

void
bank_hook_minimized(string pay_text, string got_text)
{
    say(QCTNAME(this_player()) + " minimized " +
	this_player()->query_possessive() + " coins.\n");
    write("You minimize " + pay_text + " and now have " + 
	  got_text + " on you.\n");
}

int
deposit_steel_coins(string str)
{
    object * oblist;
    object steel_coins;
    int coin_no;
    object player = this_player();

    if(!str)
    {
        notify_fail("Bank what? Your steel coins?\n");
        return 0;
    }

    oblist = PARSE_COMMAND(str, 0, "%i");

    if (!sizeof(oblist))
    {
        notify_fail("You have no steel coins to bank.\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("Bank what? Be more specific.\n");
        return 0;
    }

    if(!oblist[0]->id("_krynn_warfare_token"))
    {
        if(oblist[0]->id("coin"))
        {
            notify_fail("Your " +oblist[0]->short()+ " should " +
                "be deposited with the Gnomes of Genesis " +
                "rather than banked for safekeeping " +
                "here.\n");
            return 0;
        }

        notify_fail("You can only bank steel coins minted in " +
            "Krynn! The esteemed Bank of Palanthas does " +
            "not accept your " + oblist[0]->short()+ ".\n");
        return 0;
    }

    steel_coins = oblist[0];
   
    sscanf(str, "%d 'steel' 'coins'", coin_no);

    if(coin_no > steel_coins->num_heap())
    {
        notify_fail("You don't have " +coin_no+ " steel " +
            "coins to bank! You only have " +
            steel_coins->num_heap()+ ".\n");
        return 0;
    }  

    if(!coin_no)
    {
        notify_fail("How many do you want to deposit " +
            "of your " +steel_coins->num_heap()+ 
            " steel coins?\n");
        return 0;
    }

    write("You bank " +coin_no+ " steel coins with the esteemed " +
        "Bank of Palanthas for safekeeping.\n");
    say(QCTNAME(TP)+ " banks some steel coins with the Bank of " +
        "Palanthas for safekeeping.\n");

    steel_coins->reduce_heap_size(coin_no);
    CLUB_MANAGER->add_warfare_steel_coins_banked(TP, coin_no);
    return 1;
}

int
withdraw_steel_coins(string str)
{
    object * oblist;
    object steel_coins;
    int coin_no, banked_coins;
    object player = this_player();

    if(!str)
    {
        notify_fail("Draw what? Steel coins?\n");
        return 0;
    }
   
    sscanf(str, "%d 'steel' 'coins'", coin_no);

    if(!coin_no)
    {
        notify_fail("Draw how many steel coins?\n");
        return 0;
    }

    banked_coins = CLUB_MANAGER->query_warfare_steel_coins_banked(TP);

    if(!banked_coins)
    {
        notify_fail("You don't have any steel " +
            "coins in safekeeping here!\n");
        return 0;
    }

    if(coin_no > banked_coins)
    {
        notify_fail("You don't have " +coin_no+ " steel " +
            "coins in safekeeping here! You only " +
            "have " +banked_coins+ ".\n");
        return 0;
    }

    write("You draw " +coin_no+ " steel coins from the safekeeping " +
        "of the Bank of Palanthas.\n");
    say(QCTNAME(TP)+ " draws some steel coins from the safekeeping " +
        "of the Bank of Palanthas.\n");

    steel_coins = clone_object(STEEL_COIN);
    steel_coins->set_heap_size(coin_no);
    CLUB_MANAGER->add_warfare_steel_coins_banked(TP, -coin_no);
    steel_coins->move(TP, 1);
    return 1;
}

int
check_steel_coins(string str)
{
    int banked_coins;
    object player = this_player();

    if(!str || str != "safe-deposit box")
    {
        notify_fail("Check what? Safe-deposit box?\n");
        return 0;
    }

    banked_coins = CLUB_MANAGER->query_warfare_steel_coins_banked(TP);

    if(!banked_coins)
    {
        notify_fail("You don't have any steel coins in " +
            "safekeeping here!\n");
        return 0;
    }

    write("You check your safe-deposit box and note you have " +
        banked_coins+ " steel " + ((banked_coins == 1) ? "coin" : "coins") +
        " stored in safekeeping at the Bank of Palanthas.\n");
    say(QCTNAME(TP)+ " inquires on how many steel coins " +
        HE(player)+ " has in safekeeping at the Bank of Palanthas.\n");

    return 1;
}

/* 
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    add_action(deposit_steel_coins, "bank");
    add_action(withdraw_steel_coins, "draw");
    add_action(check_steel_coins, "check");

    add_action(deposit_steel_coins, "pbank");
    add_action(withdraw_steel_coins, "pdraw");
    add_action(check_steel_coins, "pcheck");

    bank_init();
} /* init */
