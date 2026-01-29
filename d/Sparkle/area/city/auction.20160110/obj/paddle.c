/*
 * /w/novo/open/auction/paddle.c
 *
 * This is the auction paddle that will allow players to bid and list
 * current auctions
 *
 * Created March 2008, by Novo
 *
 *
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/holdable_item";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <time.h>
#include <stdproperties.h>
#include "../defs.h"; 

//Prototypes
public int bid_items(string text);
public int list_items(string text);
public string mylong();

/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    
    set_name("paddle");
    
    add_name("_auction_paddle_");
    
    set_adj( ({ "black", "wooden" }) );
    
    set_long("@@mylong@@");

    add_prop(OBJ_M_NO_SELL,"You do not want others to bid for items that "
    + "you have to pay for, do you?\n");

    add_cmd_item( ({ "edge", "print", "fine print", 
                     "fine print on paddle" }),
              ({ "exa", "read" }),
       "Commands: <aulist> - see all open auctions\n" +
       "          <aulist #> - see details for a specific auction\n" +
       "          <aulist swords>  - see only sword auctions\n\n" +
       "          <aubid ### platinum on auction ###> - bid on an item\n"+
       "Note:     You must carry enough platinum to make your bid.\n"+
       "          If you have a credit, it will be used automatically.\n");

}

/* 
 * Function name: mylong
 * Description  : Custom description with paddle number
 */
public string mylong()
{
   int ranking=AUCTION_HOUSE->get_ranking(TP->query_real_name());
   return "This is a black wooden paddle with a large number "+
     ranking + " written in gold lettering on the front. Around the "+
     "edge of the paddle you see some fine print.\n";
}

/* 
 * Function name: init
 * Description  : Add paddle actions
 */
public void
init()
{
    ::init();

    add_action(bid_items, "aubid");
    add_action(list_items, "aulist");
} /* init */

/* 
 * Function name: bid_items
 * Description  : Handles the aubid command
 */

public int bid_items(string text)
{
    notify_fail("Bid how many platinum on which auction?\n");
    int aid;
    int bid;

    if (!stringp(text))
    {
        return 0;
    }

    if (!parse_command(text,({ }),
        "%d [platinum] 'on' [auction] %d",bid,aid) || bid<=0)
    {
        return 0;
    }
    
    mapping auction_data=AUCTION_HOUSE->get_auction(aid);

    if (member_array(aid,AUCTION_HOUSE->get_open_auction_ids())<0)
    {
        write("That is not a valid auction number.\n");
        return 1;
    }
    
    if (!mappingp(auction_data) || !m_sizeof(auction_data))
    {
        write("That is not a valid auction number.\n");
        return 1;
    }
    
    if (TP->query_real_name()==auction_data["seller"])
    {
        write("You cannot bid on your own auctions.\n");
        return 1;
    }

    int min_bid=max(max(auction_data["minimum_bid"],
        auction_data["current_bid"]*110/100),
        auction_data["current_bid"]+1);

    min_bid=min(min_bid,auction_data["maximum_bid"]);

    if (bid<min_bid)
    {
        write("You must bid at least "+min_bid+ 
        " platinum for that auction.\n");
        return 1;
    }

    
    if (auction_data["maximum_bid"])
    {
        bid=min(bid,auction_data["maximum_bid"]);
    }
    
    int credit=AUCTION_HOUSE->get_platinum_due(TP->query_real_name());
    
    int bid_credit=( auction_data["bidder"]==TP->query_real_name() ?
        auction_data["current_bid"] : 0);
    
    if (credit+bid_credit<bid)
    {
        int result=MONEY_MOVE(bid-credit-bid_credit,"platinum",TP,0);
        if (result)
        {
            write("You must carry "+(bid-credit-bid_credit)+ " platinum "+
                "for that bid.\n");
            return 1;
        }
        AUCTION_HOUSE->add_platinum_due(
                TP->query_real_name(),-credit);
    }
    else
    {
        AUCTION_HOUSE->add_platinum_due(
                TP->query_real_name(),-bid+bid_credit);
    }
    AUCTION_HOUSE->accept_bid(aid,bid,TP->query_real_name());
    
    write("Your bid of " + bid + " platinum for auction " + aid +
    " has been accepted.\n");

    if (credit+bid_credit<bid)
    {
        write("A little "+ (TP->query_alignment()>0 ? "brownie" : "demon" )
        + " appears, and takes "+(bid-bid_credit-credit) 
        + " platinum from you.\n");
    }
    return 1;
}

/* 
 * Function name: list_item
 * Description  : Handles the <aulist auction 123> command
 */
public int list_item(int id)
{
    notify_fail("List which auction?\n");
  
    mapping auction_data=AUCTION_HOUSE->get_auction(id);

    if (!m_sizeof(auction_data))
    {
        return 0;
    }
    object item=AUCTION_HOUSE->get_auction_item(id);

    string format="%-12s %=-64s\n";
    
    write(sprintf(format,
          "Auction number",
          ""+id));
    if (objectp(item))
    {
        write(sprintf(format,
        "Object",
        item->short(0,TP)));
        write(sprintf(format,
        "Description",
        item->long(0,TP)));
        write(sprintf(format,
        "Weight",item->appraise_weight(0)));
        write(sprintf(format,
        "Volume",item->appraise_volume(0)));
        write(sprintf(format,
        "Store Price",item->appraise_value(0)));
        
        if (strlen(item->appraise_light(0)))
        {
            write(sprintf(format,
                "Light",appraise_light(0)));
        }

        if (item->check_recoverable() == 1)
        {
            write(sprintf(format,
            "Recoverable",
            "It seems to be able to last a while."));
        }
    }
    else
    {
        write(sprintf(format,
        "Short",
        "Unknown"));
        write(sprintf(format,
        "Long",
        "Unknown"));
    }
    string buyer,seller;
    buyer="-";
    seller="-";
    if (auction_data["public"] || TP->query_wiz_level())
    {
        seller=capitalize(auction_data["seller"]);
        if (seller!=capitalize(auction_data["bidder"]))
        {
            buyer=capitalize(auction_data["bidder"]);
        }
    }
    if (auction_data["bidder"]==TP->query_real_name())
    {
        buyer="You";
    }    
    if (auction_data["seller"]==TP->query_real_name())
    {
        seller="You";
    }    
    write(sprintf(format,
        "High Bidder",buyer));

    write(sprintf(format,
        "Seller",seller));

    write(sprintf(format,
        "Current bid ",
        max(auction_data["minimum_bid"],auction_data["current_bid"])
        +" platinum"));

    if (auction_data["maximum_bid"])
    {
    write(sprintf(format,
        "Maximum bid ",auction_data["maximum_bid"]+" platinum"));
    }
    
    int countdown_time=AUCTION_HOUSE->get_countdown_seconds();
    write(sprintf(format,
          "Remaining",
          CONVTIME(countdown_time+3600*auction_data["hours"]))) ;
    return 1;
}

/*
 * Function name:        imbuement_description
 * Description  :        Get an imbuements description
 */
public string *imbuement_description(object item)
{
  string* result = ({});

  if (objectp(item) && item->has_imbue_shadow())
  {
    string itemDescription = item->query_all_imbued_indications();
    if (strlen(itemDescription))
    {
      foreach (string part : explode(itemDescription, ".\n"))
      {
        result += ({sprintf("%' '6s%s\n", "", part)});
      }
    }
  } 
  
  return result;
} /* imbuement_description */

/*
 * Function name:        item_condition_description
 * Description  :        Get an items condition description
 */
public string *item_condition_description(object item)
{
  string* result = ({});

  if (objectp(item))
  {    
    if (IS_WEAPON_OBJECT(item))
    {
      if ((item->query_dull() - item->query_repair_dull()) > 0 || 
          (item->query_corroded() - item->query_repair_corr()) > 0)
      {
        result+=({sprintf("%' '6s%s\n", "", item->wep_condition_desc())});
      }
    }
    
    if (IS_ARMOUR_OBJECT(item) && (item->query_condition() - item->query_repair() ))
    {
      result+=({sprintf("%' '6s%s\n", "", item->arm_condition_desc())});
    }
  }
  
  return result;
} /* item_condition_description */

/* 
 * Function name: list_items
 * Description  : Handles the aulist command
 */
public int list_items(string text)
{

  int id;

  if (strlen(text) && parse_command(text,({ TO }),"[auction] %d",id))
  {
    return list_item(id);
  }

  string * lines=({ });

  int * auctionids=AUCTION_HOUSE->get_open_auction_ids();
  
  lines+=({ sprintf("%'-'79s\n","") });
  lines+=({ sprintf("%|79s","----- Available auctions -----\n") });
  lines+=({ sprintf("%'-'79s\n","") });
  
  lines+=({ "\n" });
  
  lines+=({ sprintf("%-5s %-19s %-12s %-11s %-8s %-20s\n",
        "Num",
        "Auction Item",
        "High Bidder",
        "Seller",
        "Bid(Max)",
        "Time Left") });

  lines+=({ sprintf("%'='79s\n","") });
  
  object * selected=AUCTION_HOUSE->get_auction_items();
  
  if (strlen(text))
  {
    selected=FIND_STR_IN_ARR(text,selected);
  }
      
  int countdown_time=AUCTION_HOUSE->get_countdown_seconds();

  int index=0;
  
  foreach (int aid: auctionids)
  {
    object item=AUCTION_HOUSE->get_auction_item(aid);
    index++;  
    string name;
    if (objectp(item))
    {
        name=item->short(0,TP);
        if (item->check_recoverable())
        {
            name="*"+name;
        }
    }
    else
    {
        name="Unavailable";
    }

    //Filter out if we only want certain items
    if (strlen(text) && member_array(item,selected)<0)
    {
        continue;    
    }    
    
    mapping auction_data=AUCTION_HOUSE->get_auction(aid);
    string buyer,seller;
    buyer="-";
    seller="-";
    if (auction_data["public"] || TP->query_wiz_level())
    {
        seller=capitalize(auction_data["seller"]);
        if (seller!=capitalize(auction_data["bidder"]))
        {
            buyer=capitalize(auction_data["bidder"]);
        }
    }
    if (auction_data["bidder"]==TP->query_real_name())
    {
        buyer="You";
    }    
    if (auction_data["seller"]==TP->query_real_name())
    {
        seller="You";
    }    
    
    string time_left=CONVTIME(
                countdown_time+3600*auction_data["hours"]);
                
    lines+=({ sprintf("%-5d %=-18s  %-12s %-11s %-=8s %=-19s\n",
        aid, 
        name, 
        buyer, 
        seller,
        max(auction_data["minimum_bid"],auction_data["current_bid"])+"p\n("
        + (auction_data["maximum_bid"] ? (auction_data["maximum_bid"] + "p") : "-") + ")",
        time_left) });
      
    lines+=( item_condition_description(item) );
    lines+=( imbuement_description(item) );
    lines+=({ "\n" });
  }  

  lines+=({ sprintf("%'='79s\n","") });
  
  lines+=({ sprintf("%|79s\n",
      "* = This item seems to last a while.") });
  
  lines+=({ sprintf("%|79s\n",
      "There " + (sizeof(auctionids)==1 ? "is" : "are" ) + " currently "
      +sizeof(auctionids)+(sizeof(auctionids)==1 ? " item" : " items" )
      +" up for bid") });
      
  
  int * ids=AUCTION_HOUSE->get_won_auction(TP->query_real_name());
  if (sizeof(ids))
  {
      lines+=({ sprintf("%|79s\n",
      "There are items awaiting you at the auction house.\n") });
  }
  int credit=AUCTION_HOUSE->get_platinum_due(TP->query_real_name());
  if (credit)
  {
      lines+=({ sprintf("%|79s\n",
      "You currently have " + credit + " platinum in credit at "+
      "the auction house.\n") });
  }
  lines+=({ sprintf("%'-'79s\n","") });

  TP->more(implode(lines,""),0,0);
  return 1;
}


/* This paddle is designed to auto-load */
public string
query_auto_load(void)
{
    return MASTER+":";
}


/* Remove this object if it is not in a living's hands */
public void test_remove()
{
    if (!environment(this_object()))
    {
        remove_object();
        return;
    }
    if (!environment(this_object())->query_prop(LIVE_I_IS))
    {
        remove_object();
        return;
    }
}



/* This is required for holdable_item */
public void leave_env(object from, object to)
{
    holdable_item_leave_env(from,to);
    if (!to->query_prop(LIVE_I_IS))
    {
        set_alarm(120.0,0.0,test_remove);
    }
    ::leave_env(from,to);   
}