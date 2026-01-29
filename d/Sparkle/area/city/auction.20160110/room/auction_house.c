/*
 *  /w/novo/open/auction/auction_house.c
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
 */
#pragma  strict_types

inherit "/std/room";


#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>

#include "./quest.h"


//Prototypes
public mapping get_auction(int auction_id);
public void end_auction(int auction_id);
public void delete_auction(int auction_id);

public void add_platinum_due(string name,int count);
public int * get_open_auction_ids();
public int * get_closed_auction_ids();
public int * get_won_auction(string name);
public object get_auction_item(int auction_id);

public void auction_countdown();
private void reload_auctions();

public int update(string text);


//Auction related variables
int * Unloaded_auctions;
int countdown_alarm;
mapping Auction_items=([ ]);


void
create_room()
{
    ::create_room();
    
    set_short("Inside the Auction House");
    
    set_long("@@mylong@@");
    
    
    add_prop(ROOM_M_NO_ATTACK,"The guards eye you, indicating that "
    + "there is to be no fighting in here.\n");

    add_prop(ROOM_M_NO_MAGIC,"The guards eye you, indicating that "
    + "there is to be no magic in here.\n");
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_current.txt");
    
    add_prop(ROOM_M_NO_STEAL,"The two guards are watching much too closely"
    + " for you to take anything.\n");

    add_prop(ROOM_I_LIGHT, ALWAYS_LIGHT);
    add_prop(ROOM_I_INSIDE,1);
    
    setuid();
    seteuid(getuid());
    
    Unloaded_auctions=get_open_auction_ids()+get_closed_auction_ids();
// Temporarily closed. /Mercade, 27 dec 2015
//    set_alarm(2.0,0.0,reload_auctions);
//    countdown_alarm=set_alarm(3600.0,3600.0,auction_countdown);
    
    reset_room();
    
    add_item( ({ "guards", "guard", "dwarven guards" }),
      "Two strong dwarven guards stand at the exit to the tent. They "+
      "notice you watching them and stare back.\n");
      
    add_item( ({ "podium" }),
      "At the front of the tent is a podium where the auctioneer "+
      "stands.\n");

    add_item( ({ "benches", "wooden benches", "oak benches", "bench" }),
      "@@benchdesc@@");

    add_cmd_item( ({ "benches", "wooden benches","oak benches",
                     "bench", "down" }),
                  ({ "sit" }),
                    "You sit on the bench briefly to rest.\n");

    add_item( ({ "counter", "wooden counter","barrier" }),
      "This counter serves as a place to exchange the money and items, "+
      "as well as a barrier blocking access to the back room.\n");

    add_item( ({ "back room", "dark opening", "opening", "store room" }),
      "This is the entrance to the store room, intended only for the "+
      "auctioneer. You think you hear snoring from the back.\n");
        
    add_item( ({ "tent", "burlap", "tent poles", "poles", "cloth"
            , "room", "folds" }),
      "Tent poles hold folds of burlap high above your head.\n");

    add_item( ({ "entrance", "front entrance", "exit" }),
          "This is the entrance you came through.\n");

    add_exit("/d/Sparkle/area/city/rooms/streets/market_square", "out");
}

/*
 * Function name:        reset_room
 * Description  :        Clones the auctioneer that manages all the work
 *
 */
public void reset_room()
{
    ::reset_room();

// Temporarily closed. /Mercade, 27 dec 2015
return;
    
    if (!Auctioneer)
    {
        Auctioneer=clone_object(NPC_DIR+"auctioneer");
        Auctioneer->move(this_object());
        if (sizeof(Unloaded_auctions))
        {
            Auctioneer->set_occupied();
        }
    }
}


/*
 * Function name:        get_countdown_seconds
 * Description  :        Returns the number of seconds till the next one
 *                       hour countdown. All auctions use the same  one
 *                       hour counter.
 *
 */
public int get_countdown_seconds()
{
    return ftoi(get_alarm(countdown_alarm)[2]);
}

/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    
    add_action(start,"start");
    add_action(start,"begin");
    add_action(exchange,"exchange");
    add_action(accept,"accept");
    add_action(accept,"take");
    add_action(call,"bark");
    add_action(call,"call");
    add_action(stand,"stand");
    add_action(update,"update");

} /* init */


/*
 * Function name:        mylong
 * Description  :        long description for the room
 */
public string mylong()
{
    return
    "This tent is designed to hold a large number of people for the "+
    "purpose of holding auctions. The room is quite spacious, with "+
    "poles lifting the tent high above your head. "+
    "Large wooden benches are lined "+
    "up to face a podium. Near the back of the tent stands a "+
    "wooden counter, and behind it is a dark opening in the tent. "+
    "Two burly dwarven guards stand by the front entrance."+ 
    (present("_auction_case_", TO) ? " Glass cases lined up against "+
    "the side of the tent hold the items for sale." : "") + "\n" +
// Temporarily closed. /Mercade, 27 dec 2015
    "\nThere is a ribbon across the room, reading \"Closed while the sheriff investigates potential improprieties\".\n";
}

/*
 * Function name:        get_platinum_due
 * Description  :        Returns how much platinum the auction house owes
 *                       the player
 *
 */
public int get_platinum_due(string name)
{
    return AUCTION_MASTER->get_info(OWED, name);
}

/*
 * Function name:        add_platinum_due
 * Description  :        Updates the amount owing by the auction house
 *
 */
public void add_platinum_due(string name,int count)
{

    write_file(CASH_LOG,
            sprintf("%s %-14s due %5d platinum\n",
            ctime(time()),
            name,
            count));

    int current_due=get_platinum_due(name);
    
    if (!intp(current_due))
    {
        current_due=0;
    }
    current_due+=count;
    if (count<0)
    {
        count=0;
    }
    if (current_due!=0)
    {
        AUCTION_MASTER->set_info(OWED,name,current_due);
    }
    else
    {
        AUCTION_MASTER->remove_info(OWED,name);
    }
}

public int update(string text)
{
    if (!TP->query_wiz_level())
    {
        return 0;
    }
    object * cases=filter(all_inventory(TO),&->is_auction_container());
    
    if (cases && sizeof(cases))
    {
        write("A gnome runs into the room, pushing all the valuable cases "
        + "into the store room, saving them from your destruction!\n");
        cases->move(STORE_ROOM);
        Unloaded_auctions=get_open_auction_ids()+get_closed_auction_ids();
    
        set_alarm(2.0,0.0,reload_auctions);
    }
    return 0;
}

/*
 * Function name:        get_new_auction_number
 * Description  :        Returns a new unique auction number
 *                       the player
 *
 */
private int get_new_auction_number()
{
    int auction_number=
        AUCTION_MASTER->get_info(AUCTIONS,"latest");
    if (intp(auction_number))
    {
        auction_number++;
    }
    else
    {
        auction_number=1;
    }

    AUCTION_MASTER->set_info(AUCTIONS, "latest" , auction_number);
    return auction_number;    
}


/*
 * Function name:        create_auction
 * Description  :        Returns a new unique auction number
 *                       the player
 *
 */
public mapping create_auction(object auction_item, int min_bid, 
                              int max_bid,int is_public,int hours,
                              string seller,int deposit)
{
    if (!objectp(auction_item))
        return ([ ]);
        
    int auction_number=get_new_auction_number();
    mapping auction_data = ([ ]);
    
    auction_data+=([ "minimum_bid" : min_bid ]);
    auction_data+=([ "maximum_bid" : max_bid ]);
    auction_data+=([ "hours" : hours ]);
    auction_data+=([ "seller" : seller]);
    auction_data+=([ "public" : is_public]);
    auction_data+=([ "id" : auction_number ]);
    auction_data+=([ "bidder" : seller ]);
    auction_data+=([ "current_bid" : deposit ]);

    if (auction_item->check_recoverable(0))
    {
        auction_data+=(["recover_string" : auction_item->query_recover()]);
    }
    else
    {
        auction_data+=(["recover_string" : 0 ]);
    }

    if (auction_item->query_auto_load())
    {
        auction_data+=(["autoload_string" : 
        auction_item->query_auto_load()]);
    }
    else
    {
        auction_data+=(["autoload_string" : 0 ]);
    }

    AUCTION_MASTER->set_info(AUCTIONS,""+auction_number,auction_data);
    
    write_file(AUCTION_LOG,
        sprintf("%s auction %5d started, item %30s price %5d/%5d by %s\n",           
        ctime(time()),
        auction_number,
        auction_item->short(0,TP),
        auction_data["minimum_bid"],
        auction_data["maximum_bid"],
        auction_data["bidder"]));

    
    int * ids=get_open_auction_ids();
    ids += ({ auction_number });
    
    AUCTION_MASTER->set_info(AUCTIONS,"open",ids);
    
    Auction_items[auction_number]=auction_item;

    object master_paddle=find_object(PADDLE);
    
    if (objectp(master_paddle))
    {    
        foreach (object paddle : object_clones(master_paddle))
        {
            environment(paddle)->catch_tell("Your "+paddle->short()+
            " hums for a moment as "+
            LANG_ADDART(auction_item->short())+" goes on sale.\n");
        }
    }
    return auction_data;    

}

/*
 * Function name:        accept_bid
 * Description  :        Updates the auction with a new bid. If the bid
 *                       is invalid, it will not be updated. Note: The
 *                       actual money for the bid is not removed here.
 * Returns      :        0 for success, 1+ for not                       
 *
 */
public int accept_bid(int auction_id,int bid,string bidder)
{
    mapping auction_data=get_auction(auction_id);
    if (!auction_data || !m_sizeof(auction_data))
        return 1;
    if (bid<auction_data["minimum_bid"])
        return 2;
    if (bidder==auction_data["seller"])
        return 3;
    if (bid<=auction_data["current_bid"])
        return 4;
    if (auction_data["hours"]<0)
        return 5;
        
    int max_bid=auction_data["maximum_bid"];
    
    if (max_bid && max_bid<bid)
    {
        bid=max_bid;
    }

    int current_bid=auction_data["current_bid"];
    
    if (auction_data["bidder"]==bidder)
    {
        current_bid=0;
    }
    
    if (current_bid)
    {
        object player=find_player(auction_data["bidder"]);
        if (objectp(player))
        {
            player->catch_tell("Your black paddle shakes suddenly.\n");
        }
        
        add_platinum_due(auction_data["bidder"],current_bid);
    }
    
    Auctioneer->add_waiting(auction_data["bidder"]);
    
    auction_data+=([ "bidder" : bidder ]);
    auction_data+=([ "current_bid" : bid ]);
    
    
    AUCTION_MASTER->set_info(AUCTIONS,""+auction_id,auction_data);

    write_file(BID_LOG,
            sprintf("%s %-14s bid %5d auction %d\n",
            ctime(time()),
            bidder,
            bid,
            auction_id));
    
    if (bid==max_bid)
    {
        end_auction(auction_id);
    }
    return 0;
        
}

/*
 * Function name:        end_auction
 * Description  :        Ends the auction, if the time is up (or we hit a
 *                       maximum bid). The auction will be moved to the
 *                       closed auction list
 *
 */
public void end_auction(int auction_id)
{
    mapping auction_data=get_auction(auction_id);
    
    if (!mappingp(auction_data))
    {
        return;
    }
    if (!m_sizeof(auction_data))
    {
        return;
    }
    
    if (auction_data["hours"]>=0 && 
        auction_data["current_bid"]!=auction_data["maximum_bid"])
        return;


    int bid=max(auction_data["current_bid"] * (100-AUCTION_FEE_PERCENT)/100,1);
    
    if (auction_data["seller"]!=auction_data["bidder"])
    {
        add_platinum_due(auction_data["seller"],bid);
        Auctioneer->add_waiting(auction_data["seller"]);
        object player=find_player(auction_data["seller"]);
        if (objectp(player))
        {
            player->catch_tell("Your black paddle vibrates quickly.\n");
        }

        string short=get_auction_item(auction_id)->short();
        short=implode(explode(short," "),"");  
        int old_price=
            AUCTION_MASTER->get_info(PRICES,short);
        if (old_price)
        {
            old_price=(auction_data["current_bid"]+old_price*5)/6;
        }
           else
        {
            old_price=auction_data["current_bid"];
        }
        AUCTION_MASTER->set_info(PRICES,short,old_price);

    }
    
    AUCTION_MASTER->set_info(AUCTIONS,"open",
        get_open_auction_ids() - ({ auction_id }));

    AUCTION_MASTER->set_info(AUCTIONS,"closed",
        get_closed_auction_ids() + ({ auction_id }));


    write_file(AUCTION_LOG,
            sprintf("%s auction %5d ended, winner %12s bid %5d\n",
            ctime(time()),
            auction_id,
            auction_data["bidder"],
            auction_data["current_bid"],
            get_auction_item(auction_id)->short()));

    write_file(SELLER_LOG,ctime(time())+" - "+
      capitalize(auction_data["bidder"]) + " paid " + 
      auction_data["current_bid"] + " pc for "+
      LANG_ADDART(get_auction_item(auction_id)->short()) +
      " from "+ capitalize(auction_data["seller"])
      + " (" + auction_id + ")\n");
      

    Auctioneer->add_waiting(auction_data["bidder"]);
    object player=find_player(auction_data["bidder"]);
    if (objectp(player))
    {
        player->catch_tell("Your black paddle dances in your hands.\n");
    }
    
}

/*
 * Function name:        delete_auction
 * Description  :        Wipes all recode of the auction from the manager.
 *                       This is typically called only after the auction
 *                       item has been picked up.
 *
 */
public void delete_auction(int auction_id)
{
    int * aids=get_closed_auction_ids();
 
    if (member_array(auction_id,aids)>=0)
    {
        aids-=({ auction_id });
        AUCTION_MASTER->set_info(AUCTIONS,"closed", aids);
    }
    
    AUCTION_MASTER->remove_info(AUCTIONS,""+auction_id);
}

/*
 * Function name:        cancel_auction
 * Description  :        This cancels the auction, stopping all bidding.
 *                       There is no cleanup of the auction item, which
 *                       will remain in the auction house.
 *
 */
public void cancel_auction(int auction_id)
{
    mapping auction_data=get_auction(auction_id);
    
    if (!m_sizeof(auction_data))
    {
        return;
    }
    
    if (auction_data["current_bid"]>=auction_data["minimum_bid"])
    {
        add_platinum_due(auction_data["bidder"],auction_data["current_bid"]);
    }

    AUCTION_MASTER->set_info(AUCTIONS,"open",
        get_open_auction_ids() - ({ auction_id }));
        
    delete_auction(auction_id);
}

/*
 * Function name:        get_average_selling_price
 * Description  :        This returns the going selling price for an
 *                       item.
 * Returns      :        The number of platinum the item sold for, or 0
 *                       if unknownthe 
 *
 */
public int get_average_selling_price(string short)
{
    if (!stringp(short))
      return 0;
    short=implode(explode(short," "),"");  
    return AUCTION_MASTER->get_info(PRICES,short);
}    


/*
 * Function name:        get_open_auction_ids
 * Description  :        Returns the list of open auction numbers
 *
 */
public int * get_open_auction_ids()
{
    int * result=
    AUCTION_MASTER->get_info(AUCTIONS,"open");
    if (!pointerp(result))
    {
        return ({ });
    }
    return result;
}


/*
 * Function name:        get_closed_auction_ids
 * Description  :        Returns the list of closed auction numbers
 *
 */
public int * get_closed_auction_ids()
{
    int * result=
    AUCTION_MASTER->get_info(AUCTIONS,"closed");
    if (!pointerp(result))
    {
        return ({ });
    }
    return result;
}



/*
 * Function name:        get_auction
 * Description  :        Returns a mapping containing the current
 *                       auction details
 *
 */
public mapping get_auction(int auction_id)
{
    
    int * auction_ids=get_open_auction_ids();
    
    if (member_array(auction_id,auction_ids)>=0)
    {
        return AUCTION_MASTER->get_info(AUCTIONS,""+auction_id);
    }
    
    auction_ids=get_closed_auction_ids();
    if (member_array(auction_id,auction_ids)>=0)
    {
        return AUCTION_MASTER->get_info(AUCTIONS,""+auction_id);
    }
    return ([ ]);
}

/*
 * Function name:        get_won_auction
 * Description  :        Returns a list of the auction IDs won by 
 *                       the player
 *
 */
public int * get_won_auction(string name)
{
    
    int * auction_ids=get_closed_auction_ids();
    
    if (!auction_ids)
    {
        return ({ });
    }
    
    int * won_auctions=({ });
    
    foreach (int aid : auction_ids)
    {
        mapping auction_data=get_auction(aid);
        if (!mappingp(auction_data))
            continue;
        
        if (auction_data["bidder"]==name)
        {
            won_auctions += ({ aid });
        }
    }
    return won_auctions;
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
    {
        return 0;
    }

    object ob; // auction item to be cloned

    // First check to see if this is a recoverable item
    string recover_string=auction["recover_string"];    
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
    string autoload_string=auction["autoload_string"];
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
 * Function name:        reload_auctions
 * Description  :        Loads the auctions after armageddon
 *                       
 *
 */
private nomask void reload_auctions()
{
    string  file;
    string  argument;
    object  ob;

    if (!sizeof(Unloaded_auctions))
    {
        Auctioneer->set_available();
        return;
    }
          
    int aid=Unloaded_auctions[0];

    Unloaded_auctions=Unloaded_auctions[1..];
    set_alarm(2.0, 0.0,reload_auctions);
    
    Auctioneer->command("whistle loudly");
    
    if (objectp(find_object(STORE_ROOM)))
    {
        object * prev_container=filter(
        all_inventory(find_object(STORE_ROOM)),
        &operator(==)(aid) @ &->get_auction());
        if (prev_container && sizeof(prev_container))
        {
            object * container_inventory = all_inventory(prev_container[0]);
            if (!sizeof(container_inventory))
            {
                ob = clone_auction_item(aid);
                if (!objectp(ob))
                {
                    // Object could not be cloned. Assume invalid auction,
                    // which should automatically get deleted by the call
                    // to clone_auction_item
                    return;
                }
            }
            else
            {
                ob = container_inventory[0];
            }
            Auction_items[aid] = ob;
            prev_container[0]->move(TO);
            tell_room(TO,"A spindly old gnome enters the tent, " +
            "pushing a marble pedestal with a large glass case on top. "+
            "Inside the case you can see "+LANG_ADDART(ob->short()) + 
            ".\n",
            ({ }), Auctioneer);
            return;
        }
    }

    ob = clone_auction_item(aid);
    if (!objectp(ob))
    {
        return;
    }

    tell_room(TO,"A spindly old gnome enters the tent, " +
    "pushing a marble pedestal with a large glass case on top. "+
    "Inside the case you can see "+LANG_ADDART(ob->short()) + ".\n",
    ({ }), Auctioneer);
    object container=clone_object(OBJ_DIR+"auction_container");
    container->move(TO);
    ob->move(container,1);
    if (!ob)
        if (sizeof(all_inventory(container)))
            ob = all_inventory(container)[0];

    container->set_auction(aid);

    Auction_items[aid]=ob;
    
    if (!ob->check_recoverable())
    {
        mapping auction = get_auction(aid);
        if (!mappingp(auction))
        {
            return;
        }
        auction["recover_string"] = 0;
        AUCTION_MASTER->set_info(AUCTIONS, "" + aid, auction);
    }
}

/*
 * Function name:        get_auction_item
 * Description  :        Returns the actual object being sold for auction
 *
 */
public object get_auction_item(int auction_id)
{
    return Auction_items[auction_id];
}

/*
 * Function name:        get_auction_items
 * Description  :        Returns an array of all items for auction
 *
 */
public mixed * get_auction_items()
{
    return m_values(Auction_items);
}


/*
 * Function name:        get_ranking
 * Description  :        Returns the ranking of the user - when they first
 *                       receive a paddle, they will receive a rank.
 *                       This number is shown on the paddle.
 *
 */
public int get_ranking(string name)
{
    int ranking=AUCTION_MASTER->get_info(RANKING,name);

    if (!intp(ranking) || !ranking)
    {
        ranking=AUCTION_MASTER->get_info(AUCTIONS,"latest_ranking");
        if (intp(ranking))
        {
            ranking++;
        }
        else
        {
            ranking=1;
        }
        AUCTION_MASTER->set_info(AUCTIONS, "latest_ranking" , 
            ranking);
        AUCTION_MASTER->set_info(RANKING, name , 
            ranking);
    }
    return ranking;
}

/*
 * Function name:        auction_countdown
 * Description  :        This is the countdown timer which is called
 *                       once an hour. It will end auctions are their
 *                       time runs out.
 *
 */
public void auction_countdown()
{
    foreach (int aid: get_open_auction_ids())
    {
        mapping auction_data=get_auction(aid);
        
        if (!objectp(get_auction_item(aid)))
        {
            cancel_auction(aid);
        }
        
        auction_data["hours"]--;
        
        AUCTION_MASTER->set_info(AUCTIONS,""+aid,auction_data);
        
        if (auction_data["hours"]<0)
        {
            end_auction(aid);
        }
        
    }
}


/*
 * Function name:        prevent_enter
 * Description  :        Keep active fights out of the auction
 */
public int
prevent_enter(object ob)
{
    if (!living(ob))
    {
      return 0;
    }
    
    if (!ob->query_relaxed_from_combat())
    {
      write("Your recent combat keeps you from entering.\n");  
      return 1;
    }
    
    return 0;
}

