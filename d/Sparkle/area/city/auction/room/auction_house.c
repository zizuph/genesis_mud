/*
 *  /d/Sparkle/area/city/auction/room/auction_house.c
 *
 *  This is the auction house. All data manager calls are here.
 *  If you want to find out anything about auction status, look here.
 *  This can create new auctions, end auctions, and manages the credits
 *  That the player is owed.
 *
 *  Created March 2008, by Novo
 *
 *  Changes
 *  2010-02-04 - Cotillion
 *  - Made room always light
 *
 *  2020-07 - Lucius
 *  - Cleanups & obsolete code removal.
 */
#pragma  strict_types

inherit "/std/room";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>

#include "./quest.h"


public object* auction_event_listeners = ({});

//Prototypes
public mapping get_auction(int auction_id);
public void end_auction(int auction_id);
public void delete_auction(int auction_id);

public void add_platinum_due(string name, int count);

public int *get_won_auction(string name);
public object get_auction_item(int auction_id);
public void end_auction_check();

public static int end_auction_alarm;

/*
 * Function name:        create_room
 * Description  :        Sets room attributes
 */
public void
create_room()
{
    setuid();
    seteuid(getuid());

    ::create_room();

    set_short("Inside the Auction House");

    set_long("@@mylong@@");

    add_prop(ROOM_M_NO_ATTACK, "The guards eye you, indicating that "
             + "there is to be no fighting in here.\n");

    add_prop(ROOM_M_NO_MAGIC, "The guards eye you, indicating that "
             + "there is to be no magic in here.\n");
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_current.txt");

    add_prop(ROOM_M_NO_STEAL, "The two guards are watching much too closely"
             + " for you to take anything.\n");

    add_prop(ROOM_I_LIGHT, ALWAYS_LIGHT);
    add_prop(ROOM_I_INSIDE, 1);

    end_auction_alarm = set_alarm(60.0, 0.0, end_auction_check);

    add_item( ({ "guards", "guard", "dwarven guards" }),
              "Two strong dwarven guards stand at the exit to the tent. They " +
              "notice you watching them and stare back.\n");

    add_item( ({ "podium" }),
              "At the front of the tent is a podium where the auctioneer " +
              "stands.\n");

    add_item( ({ "benches", "wooden benches", "oak benches", "bench" }),
              "@@benchdesc@@");

    add_cmd_item( ({ "benches", "wooden benches", "oak benches",
                     "bench", "down" }),
                  ({ "sit" }),
                  "You sit on the bench briefly to rest.\n");

    add_item( ({ "counter", "wooden counter", "barrier" }),
              "This counter serves as a place to exchange the money and items, " +
              "as well as a barrier blocking access to the back room.\n");

    add_item( ({ "back room", "dark opening", "opening", "store room" }),
              "This is the entrance to the store room, intended only for the " +
              "auctioneer. You think you hear snoring from the back.\n");

    add_item( ({ "tent", "burlap", "tent poles", "poles", "cloth"
                 , "room", "folds" }),
              "Tent poles hold folds of burlap high above your head.\n");

    add_item( ({ "entrance", "front entrance", "exit" }),
              "This is the entrance you came through.\n");

    add_exit("/d/Sparkle/area/city/rooms/streets/market_square", "out");

    reset_room();
}

/*
 * Function name:        reset_room
 * Description  :        Clones the auctioneer that manages all the work
 */
public void
reset_room()
{
    ::reset_room();

    if (!Auctioneer) {
        Auctioneer = clone_object(NPC_DIR + "auctioneer");
        Auctioneer->move(this_object());
    }
}

/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(start, "start");
    add_action(start, "begin");
    add_action(exchange, "exchange");
    add_action(accept, "accept");
    add_action(accept, "take");
    add_action(call, "bark");
    add_action(call, "call");
    add_action(stand, "stand");
} /* init */

/*
 * Function name:        mylong
 * Description  :        long description for the room
 */
public string
mylong()
{
    return
        "This tent is designed to hold a large number of people for the " +
        "purpose of holding auctions. The room is quite spacious, with " +
        "poles lifting the tent high above your head. " +
        "Large wooden benches are lined " +
        "up to face a podium. Near the back of the tent stands a " +
        "wooden counter, and behind it is a dark opening in the tent. " +
        "Two burly dwarven guards stand by the front entrance." +
        (present("_auction_case_", TO) ? " Glass cases lined up against " +
         "the side of the tent hold the items for sale." : "") + "\n";
}

/*
 * Function name:        get_platinum_due
 * Description  :        Returns how much platinum the auction house owes
 *                       the player
 */
public int
get_platinum_due(string name)
{
    return AUCTION_DATA_STORE->get_owed(name);
}


public void
add_auction_event_listener(object obj)
{
    auction_event_listeners = auction_event_listeners - ({ 0 });
    auction_event_listeners += ({ obj });
}

public void
remove_auction_event_listener(object obj)
{
    auction_event_listeners = auction_event_listeners - ({ 0 });
    auction_event_listeners -= ({ obj });
}

/*
 * Function name:        add_platinum_due
 * Description  :        Updates the amount owing by the auction house
 */
public void
add_platinum_due(string name, int count)
{
    write_file(CASH_LOG, sprintf("%s %-14s due %5d platinum\n",
	    ctime(time()), name, count));

    int current_due = get_platinum_due(name);

    if (!intp(current_due))
        current_due = 0;

    current_due += count;

    if (count < 0)
        count = 0;

    if (current_due != 0) {
        AUCTION_DATA_STORE->set_owed(name, current_due);
    } else {
        AUCTION_DATA_STORE->set_owed(name, 0);
    }
}

/*
 * Function name:        create_auction
 * Description  :        Returns a new unique auction number
 *                       the player
 */
public mapping create_auction(object auction_item, int min_bid,
    int max_bid, int is_public, int hours, string seller, int deposit)
{
    if (!objectp(auction_item))
        return ([ ]);

    mapping auction_data = AUCTION_DATA_STORE->create_auction(is_public,
	auction_item, min_bid, max_bid, hours, seller, deposit);

    if (mappingp(auction_data))
    {
        write_file(AUCTION_LOG,
	    sprintf("%s %-14s %i started, item %30s price %5d/%5d\n",
		ctime(time()), auction_data["bidder"], auction_data["id"],
		auction_data["short"], auction_data["minimum_bid"],
		auction_data["maximum_bid"]));

        object master_paddle = find_object(PADDLE);

        if (objectp(master_paddle))
	{
	    foreach(object paddle: object_clones(master_paddle))
	    {
		if (paddle->query_no_notify())
		    continue;

                environment(paddle)->catch_tell("Your "+ paddle->short() +
		    " hums for a moment as " + LANG_ASHORT(auction_item) +
		    " goes on sale.\n");
            }
        }
    }

    auction_data = secure_var(auction_data);
    
    foreach (object listener : auction_event_listeners)
    {
        if (objectp(listener))
            listener->notify_auction_created(auction_data);
    }
    return auction_data;
}

/*
 * Function name:        accept_bid
 * Description  :        Updates the auction with a new bid. If the bid
 *                       is invalid, it will not be updated. Note: The
 *                       actual money for the bid is not removed here.
 * Returns      :        0 for success, 1+ for not
 */
public int
accept_bid(int auction_id, int bid, string bidder)
{
    mapping auction_data = get_auction(auction_id);
    int now = time();

    if (!auction_data || !m_sizeof(auction_data))
        return 1;

    if (bid < auction_data["minimum_bid"])
        return 2;

    if (bidder == auction_data["seller"])
        return 3;

    if (bid <= auction_data["current_bid"])
        return 4;

    if (auction_data["auction_end"] <= now)
        return 5;

    int max_bid = auction_data["maximum_bid"];
    int current_bid = auction_data["current_bid"];

    if (max_bid && max_bid < bid)
        bid = max_bid;

    if (auction_data["bidder"] == bidder)
        current_bid = 0;

    if (current_bid)
    {
        object player = find_player(auction_data["bidder"]);

        if (objectp(player))
            player->catch_tell("Your black paddle shakes suddenly.\n");

        add_platinum_due(auction_data["bidder"], current_bid);
    }

    Auctioneer->add_waiting(auction_data["bidder"]);

    auction_data += ([ "bidder" : bidder ]);
    auction_data += ([ "current_bid" : bid ]);
    AUCTION_DATA_STORE->update_auction_bid(auction_id, bidder, bid);

    write_file(BID_LOG, sprintf("%s %-14s bid %5d auction %d\n",
	    ctime(time()), bidder, bid, auction_id));

    if (bid == max_bid)
        end_auction(auction_id);

    return 0;
}

/*
 * Function name:        end_auction
 * Description  :        Ends the auction, if the time is up (or we hit a
 *                       maximum bid). The auction will be moved to the
 *                       closed auction list
 */
public void
end_auction(int auction_id)
{
    mapping auction_data = get_auction(auction_id);
    int now = time();

    if (!mappingp(auction_data))
        return;

    if (!m_sizeof(auction_data))
        return;

    if (auction_data["auction_end"] > now &&
	auction_data["current_bid"] != auction_data["maximum_bid"])
        return;

    if (auction_data["auction_end"] > now)
        AUCTION_DATA_STORE->update_auction_end(auction_id, now - 60);

    int bid = max(auction_data["current_bid"] * (100 - AUCTION_FEE_PERCENT) / 100, 1);

    if (auction_data["seller"] != auction_data["bidder"])
    {
        add_platinum_due(auction_data["seller"], bid);
        Auctioneer->add_waiting(auction_data["seller"]);

        object player = find_player(auction_data["seller"]);
        if (objectp(player))
            player->catch_tell("Your black paddle vibrates quickly.\n");

        string short = auction_data["short"];
        short = implode(explode(short, " "), "");

        int old_price = AUCTION_DATA_STORE->get_price(short);
        if (old_price) {
            old_price = (auction_data["current_bid"] + old_price * 5) / 6;
        } else {
            old_price = auction_data["current_bid"];
        }

        AUCTION_DATA_STORE->set_prices(short, old_price);
    }

    write_file(AUCTION_LOG,
	sprintf("%s auction %5d ended, winner %12s bid %5d\n",
	    ctime(time()), auction_id, auction_data["bidder"],
	    auction_data["current_bid"], auction_data["short"]));

    write_file(SELLER_LOG, ctime(time()) + " - " +
	capitalize(auction_data["bidder"]) + " paid " +
	auction_data["current_bid"] + " pc for " +
	LANG_ADDART(auction_data["short"]) +
	" from " + capitalize(auction_data["seller"])
	+ " (" + auction_id + ")\n");

    Auctioneer->add_waiting(auction_data["bidder"]);

    object player = find_player(auction_data["bidder"]);
    if (objectp(player))
        player->catch_tell("Your black paddle dances in your hands.\n");
    
    auction_data = secure_var(auction_data);
    
    foreach (object listener : auction_event_listeners)
    {
        if (objectp(listener))
            listener->notify_auction_ended(auction_data);
    }
}

/*
 * Function name:        delete_auction
 * Description  :        Wipes all recode of the auction from the manager.
 *                       This is typically called only after the auction
 *                       item has been picked up.
 */
public void
delete_auction(int auction_id)
{
    AUCTION_DATA_STORE->remove_auction("" + auction_id);
}

/*
 * Function name:        cancel_auction
 * Description  :        This cancels the auction, stopping all bidding.
 *                       There is no cleanup of the auction item, which
 *                       will remain in the auction house.
 */
public void
cancel_auction(int auction_id)
{
    mapping auction_data = get_auction(auction_id);

    if (!m_sizeof(auction_data))
        return;

    if (auction_data["current_bid"] >= auction_data["minimum_bid"])
        add_platinum_due(auction_data["bidder"], auction_data["current_bid"]);

    delete_auction(auction_id);
}

/*
 * Function name:        get_average_selling_price
 * Description  :        This returns the going selling price for an
 *                       item.
 * Returns      :        The number of platinum the item sold for, or 0
 *                       if unknownthe
 */
public int
get_average_selling_price(string short)
{
    if (!stringp(short))
        return 0;

    short = implode(explode(short, " "), "");
    return AUCTION_DATA_STORE->get_price(short);
}

/*
 * Function name:        get_auction
 * Description  :        Returns a mapping containing the current
 *                       auction details
 */
public mapping
get_auction(int auction_id)
{
    return AUCTION_DATA_STORE->get_auction("" + auction_id);
}

/*
 * Function name:        get_won_auction
 * Description  :        Returns a list of the auction IDs won by
 *                       the player
 */
public int *
get_won_auction(string name)
{
    return AUCTION_DATA_STORE->get_won_auctions(name);
}

/*
 * Function name:        clone_auction_item
 * Description  :        Recreates the auction item from the auction entry.
 */
public object
clone_auction_item(int aid)
{
    string  file;
    string  argument;
    mapping auction = get_auction(aid);

    if (!mappingp(auction))
        return 0;

    object ob; // auction item to be cloned

    // First check to see if this is a recoverable item
    string recover_string = auction["recover_string"];

    if (stringp(recover_string))
    {
        if (sscanf(recover_string, "%s:%s", file, argument) != 2)
	{
            file = recover_string;
            argument = 0;
        }

	catch(ob = clone_object(file));

        if (!objectp(ob))
	{
            cancel_auction(aid);
            delete_auction(aid);
            return 0;
        }

        /* Note that we don't check for strlen() since we also want to call
        * init_recover() if the format is 'filename:'.
        */
        if (stringp(argument))
	{
            if (ob->init_recover(argument))
	    {
                ob->remove_object();
                cancel_auction(aid);
                delete_auction(aid);
                return 0;
            }
        }
    }

    // Next check if this is an autoload item
    string autoload_string = auction["autoload_string"];

    if (stringp(autoload_string))
    {
        if (sscanf(autoload_string, "%s:%s", file, argument) != 2)
	{
            file = autoload_string;
            argument = 0;
        }

	catch(ob = clone_object(file));

        if (!objectp(ob))
	{
            cancel_auction(aid);
            delete_auction(aid);
            return 0;
        }

        /* Note that we don't check for strlen() since we also want to call
        * init_recover() if the format is 'filename:'.
        */
        if (stringp(argument))
	{
            if (ob->init_arg(argument))
	    {
                ob->remove_object();
                cancel_auction(aid);
                delete_auction(aid);
                return 0;
            }
        }
    }

    // If it's neither recoverable nor autoload, then we delete the auction
    if (!stringp(recover_string) && !stringp(autoload_string))
    {
        cancel_auction(aid);
        delete_auction(aid);
        return 0;
    }

    return ob;
}

/*
 * Function name:        get_auction_item
 * Description  :        Returns the actual object being sold for auction
 */
public object
get_auction_item(int auction_id)
{
    return AUCTION_DATA_STORE->recreate_auction_item("" + auction_id);
}

/*
 * Function name:        get_ranking
 * Description  :        Returns the ranking of the user - when they first
 *                       receive a paddle, they will receive a rank.
 *                       This number is shown on the paddle.
 */
public int
get_ranking(string name)
{
    return AUCTION_DATA_STORE->ensure_ranking(name);
}

public int
end_finished_auctions()
{
    int latest_auction_end = time();
    int last_end_time = AUCTION_DATA_STORE->get_last_auction_end();

    foreach (int aid: AUCTION_DATA_STORE->get_closed_auction_ids())
    {
        mapping auction_data = get_auction(aid);

        if (mappingp(auction_data))
	{
            int auction_end = auction_data["auction_end"];

            if (auction_end > last_end_time)
	    {
                int current_bid = auction_data["current_bid"];
                int maximum_bid = auction_data["maximum_bid"];

                if (current_bid != maximum_bid) {
                    end_auction(aid);
                }
            }
        }
    }

    AUCTION_DATA_STORE->set_last_auction_end(latest_auction_end);
    return 1;
}

public void
end_auction_check()
{
    if (end_auction_alarm)
        remove_alarm(end_auction_alarm);

    end_finished_auctions();
    end_auction_alarm = set_alarm(60.0, 0.0, end_auction_check);
}

/*
 * Function name:        prevent_enter
 * Description  :        Keep active fights out of the auction
 */
public int
prevent_enter(object ob)
{
    if (!living(ob))
        return 0;

    if (!ob->query_relaxed_from_combat())
    {
        ob->catch_tell("Your recent combat keeps you from entering.\n");
        return 1;
    }

    return 0;
}

