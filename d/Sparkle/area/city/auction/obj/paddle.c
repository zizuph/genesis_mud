/*
 * This is the auction paddle that will allow players to bid and list
 * current auctions
 *
 * Created March 2008, by Novo
 *
 * Revisions:
 *   2020-05: Lucius
 *   - Added 'aulist me/mine'.
 *   - Reformat code, obsolete code removal.
 *   - Add notification and version handling.
 *   2020-06: Lucius
 *   - Added 'aurlist' to reverse sort output
 *   - Added several wizard commands
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/holdable_item";

#include <files.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "../defs.h";

// Variables
public int version = 3;
public int no_notify = 0;


public int
query_no_notify(void)
{
    return no_notify;
}

public string
fine_print(void)
{
    string base =
	"Commands: <aulist>   - see all open auctions\n" +
	"          <aurlist>  - display results reversed\n\n" +
	"          <aulist #> - see details for a specific auction\n\n" +
	"          <aulist me / mine> - see only your auctions\n\n" +
	"          <aulist swords>    - see only sword auctions\n\n" +
	"          <aubid ### platinum on auction ###> - bid on an item\n\n" +
	"          <aunotify> [on | off] - listen for auctions\n\n" +
	"          <aulist help>  - see full help\n\n" +
	"Note:     You must carry enough platinum to make your bid, unless\n" +
    "          it is 250 platinum or higher.\n" +
    "          If you do not carry enough for a larger bid, it will be\n" +
    "          automatically deducted from your bank account.\n" +
	"          If you have a credit, it will be used automatically.\n";

    if (this_player()->query_wiz_level())
    {
	base += "\nAdditional Wizard Commands:\n"+
	    "          <aulist seller>        - see open auctions sellers\n" +
	    "          <aulist seller ###>    - see all ###'s auctions\n" +
	    "          <aulist closed>        - see all closed auctions\n" +
	    "          <aulist closed seller> - see closed auctions sellers\n" +
	    "          <autele ah / am>       - teleport to auction house or master\n" +
	    "\n";
    }

    return base;
}

/*
 * Function name: create_object
 * Description  : set up the object
 */
public void
create_object()
{
    setuid();
    seteuid(getuid());

    set_name("paddle");
    add_name("_auction_paddle_");
    set_adj( ({ "black", "wooden", "auction" }) );

    set_long("@@mylong@@");
    set_short("black wooden paddle");

    add_prop(OBJ_M_NO_INS,   1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, "You do not want others to bid for items that "
             + "you have to pay for, do you?\n");

    add_cmd_item( ({ "edge", "print", "fine print",
                     "fine print on paddle" }),
                  ({ "exa", "read" }), fine_print);
}

/*
 * Function name: mylong
 * Description  : Custom description with paddle number
 */
public string
mylong()
{
    int ranking = AUCTION_HOUSE->get_ranking(TP->query_real_name());
    return "This is a black wooden paddle with a large number " +
           ranking + " written in gold lettering on the front. Around the " +
           "edge of the paddle you see some fine print.\n";
}

/*
 * Function name: print_list_help
 * Description  : prints the list help command
 */
public int
print_list_help()
{
    TP->more(
        "aulist [imbued|unimbued] [type|#] \n" +
        "         [with (imbue strength|imbue type) imbuments] \n" +
        "         [(under|over) price] [between pricelow and pricehigh]\n" +
        "\n" +
        "imbued/unimbued\n" +
        "     - if present, only return items that are/aren't imbued \n" +
        "type\n" +
        "  #  - auction item id\n" +
        "     - a weapons type\n" +
        "           sword\n" +
        "           polearm\n" +
        "           axe\n" +
        "           club\n" +
        "           missile weapon\n" +
        "           javelin\n" +
        "     - an armour type\n" +
        "           body armour\n" +
        "           chest armour\n" +
        "           head armour\n" +
        "           leg armour\n" +
        "           arm armour\n" +
        "           hand armour\n" +
        "           foot armour\n" +
        "      - imbuement stones\n" +
        "           stones\n" +
        "           \n" +
        "with (description) imbuements\n" +
        "ie    with sage imbuements\n" +
        "      with faint imbuements\n" +
        "      with silvery faint imbuements\n" +
        "      with quartz imbuements\n" +
        "\n" +
        "over/under/between\n" +
        "ie    under 50\n" +
        "      over 20\n" +
        "      between 40 and 120\n" );
    return 1;
}

/*
 * Function name: bid_items
 * Description  : Handles the aubid command
 */
public int
bid_items(string text)
{
    int aid, bid;

    if (!strlen(text))
        return notify_fail("Bid how many platinum on which auction?\n");

    if (!parse_command(text, ({ }),
	    "%d [platinum] 'on' [auction] %d ", bid, aid))
    {
        return notify_fail("Syntax is: aubid <amount> on <auction>\n");
    }

    if (bid <= 0)
    {
	write("The minimum bid amount is 1 platinum.\n");
	return 1;
    }

    mapping auction_data = AUCTION_DATA_STORE->get_auction(aid);

    if (!mappingp(auction_data) || !m_sizeof(auction_data))
    {
        write("That is not a valid auction id.\n");
        return 1;
    }

    if (TP->query_real_name() == auction_data["seller"])
    {
        write("You cannot bid on your own auctions.\n");
        return 1;
    }

    if (auction_data["auction_end"] < time())
    {
        write("That auction is already closed.\n");
        return 1;
    }

    int min_bid = min(auction_data["current_bid"] * 110 / 100,
            auction_data["current_bid"] + 100);
    min_bid = max(min_bid, auction_data["minimum_bid"]);
    min_bid = max(min_bid, auction_data["current_bid"] + 1);

    if (auction_data["maximum_bid"]) {
        min_bid = min(min_bid, auction_data["maximum_bid"]);
    }

    if (bid < min_bid)
    {
        write("You must bid at least " + min_bid +
	    " platinum for that auction.\n");
        return 1;
    }

    if (auction_data["maximum_bid"]) {
        bid = min(bid, auction_data["maximum_bid"]);
    }
    string name = TP->query_real_name();

    int credit = AUCTION_HOUSE->get_platinum_due(name);
    int bid_credit = (auction_data["bidder"] == name ?
                      auction_data["current_bid"] : 0);
                      
    int onhand_platinum = MONEY_COINS(TP)[MONEY_PC_INDEX];

    if (credit + bid_credit < bid)
    {
        int bank_platinum = 0;
        if (bid >= 250)
        {
          if (GOG_ACCOUNTS->load_account(name))
          {
              int* coins = GOG_ACCOUNTS->query_account_coins(name);
              bank_platinum = coins[MONEY_PC_INDEX];
          }
        }
        
        if (onhand_platinum + bank_platinum + credit + bid_credit < bid)
        {
            if (bid >= 250)
            {
                write("You must carry or have in your bank account " 
                    + (bid - credit - bid_credit) +
		            " platinum for that bid.\n");
            }
            else
            {
                write("You must carry " + (bid - credit - bid_credit) +
		            " platinum for that bid.\n");
            }
            return 1;

        }
        
        if (credit + bid_credit + onhand_platinum >= bid)
        {
            MONEY_MOVE_PC(bid - credit - bid_credit, TP, 0);
        }
        else
        {
            MONEY_MOVE_PC(onhand_platinum, TP, 0);
            GOG_ACCOUNTS->remove_money(name, MONEY_PC_INDEX, 
                bid - credit - bid_credit - onhand_platinum);
        }

        AUCTION_HOUSE->add_platinum_due(TP->query_real_name(), -credit);
    }
    else
    {
        AUCTION_HOUSE->add_platinum_due(TP->query_real_name(),
	        -bid + bid_credit);
    }

    AUCTION_HOUSE->accept_bid(aid, bid, TP->query_real_name());

    write("Your bid of " + bid + " platinum for auction " + aid +
          " has been accepted.\n");

    if (credit + bid_credit < bid)
    {
        if (credit + bid_credit + onhand_platinum >= bid)
        {
        write("A little " + (TP->query_alignment() > 0 ? "brownie" : "demon")
              + " appears, and takes " + (bid - bid_credit - credit)
              + " platinum from you.\n");
        }
        else
        {
            if (onhand_platinum > 0)
            {
                write("A little " + (TP->query_alignment() > 0 
                    ? "brownie" : "demon")
                    + " appears, and takes " + (onhand_platinum)
                    + " platinum from you.  ");
                write("The remaining " + 
                    (bid - bid_credit - credit - onhand_platinum)
                    + " platinum were deducted from your bank account.\n");
            }
            else
            {
                write("You have no platinum on hand, so the " 
                    + (bid - bid_credit - credit - onhand_platinum)
                    + " platinum were deducted from your bank account.\n");
            }
        }
    }

    return 1;
}

/*
 * Function name: list_items
 * Description  : Handles the aulist command
 */
public int
list_items(string text)
{
    int wiz = TP->query_wiz_level();

    if (text == "help")
    {
        print_list_help();
        return 1;
    }

    if (!strlen(text)) {
        text = "open auctions";
    } else if (parse_command(text, ({}), "'me' / 'mine'")) {
        text = "owner auctions";
    } else if (wiz && text == "seller") {
        text = "open seller auctions";
    } else if (wiz && wildmatch("seller *", text)) {
	text = lower_case(text);
    } else if (wiz && text == "closed") {
        text = "closed auctions";
    } else if (wiz && text == "closed seller") {
        text = "closed seller auctions";
    } else {
        text = "auction " + text;
    }

    return AUCTION_DATA_STORE->view_auction(text,
	query_verb() == "aurlist");
}

/*
 * Function name: toggle_notify
 * Description  : Handles the aunotify command
 */
public int
toggle_notify(string str)
{
    if (!strlen(str))
    {
	write("New auction notifications are: "+
	    (no_notify ? "disabled" : "enabled") +".\n");
    }
    else if (str == "on" || str == "enable")
    {
	if (!no_notify)
	{
	    write("You are already attentive to auctions.\n");
	}
	else
	{
	    no_notify = !no_notify;
	    write("You are now listening for new auctions.\n");
	}
    }
    else if (str == "off" || str == "disable")
    {
	if (no_notify)
	{
	    write("You are already ignoring auctions.\n");
	}
	else
	{
	    no_notify = !no_notify;
	    write("You are now ignoring new auctions.\n");
	}
    }
    else
    {
	notify_fail("Syntax: aunotify [on | off]\n");
	return 0;
    }

    return 1;
}

public int
wiz_tele(string str)
{
    string where;

    if (str == "ah")
	where = AUCTION_HOUSE;
    else if (str == "am")
	where = AUCTION_DATA_STORE;
    else
    {
	notify_fail("Syntax: autele <ah / am>\nWhere 'ah' is the "+
	    "Auction House, and 'am' is the Auction Master.\n");
	return 0;
    }

    if (TP->move_living("X", where, 1, 0))
    {
	write("Problems arose, attempt manual teleport to:\n\t"+
	    where +"\n");
    }

    return 1;
}

/*
 * Function name: init
 * Description  : Add paddle actions
 */
public void
init(void)
{
    ::init();

    add_action(bid_items, "aubid");
    add_action(list_items, "aulist");
    add_action(list_items, "aurlist");
    add_action(toggle_notify, "aunotify");

    if (environment()->query_wiz_level())
    {
	add_action(wiz_tele, "autele");
    }
}

/* This paddle is designed to auto-load */

public void
version_check(void)
{
    object who = environment();

    if (!objectp(who) || !query_interactive(who))
	return;

    who->catch_tell("\nThe writing around the edge of the "+
	short() +" glows brightly for a moment.\n\n");
}

public void
init_arg(string arg)
{
    int ver;
    if (sscanf(arg, "#V:%d#N:%d", ver, no_notify) == 2) {
	if (ver < version) {
	    set_alarm(3.0, 0.0, version_check);
	}
    }
}

public string
query_auto_load(void)
{
    return MASTER + ":" +
	"#V:" + version +
	"#N:" + no_notify +
	"#";
}

/* Remove this object if it is not in a living's hands */
public void
test_remove(void)
{
    if (!environment()->query_prop(LIVE_I_IS))
        remove_object();
}

/* This is required for holdable_item */
public void
leave_env(object from, object to)
{
    holdable_item_leave_env(from, to);

    if (!to->query_prop(LIVE_I_IS)) {
        set_alarm(5.0, 0.0, test_remove);
    }

    ::leave_env(from, to);
}
