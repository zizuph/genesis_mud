/*
 * /w/novo/open/auction/auction_container.c
 *
 * This is the container used to hold the actual items for auction.
 * There will be one case per open auction, at any time.
 *
 *
 * Created March 2008, by Novo
 *
 *
 */
#pragma strict_types

inherit "/std/receptacle";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

int Auction_number;
int Hours_remaining;



public void
create_receptacle()
{


    set_name("case");
    
    add_name("_auction_case_");

    set_adj( ({ "large", "glass", "closed", "auction" }) );

    set_short("glass case");

    set_long("@@mylong@@");
     
    add_item( ({"marble pedestal","pedastal" }),
    "The pedestal supports the glass case, holding it at chest height.\n");

    add_item( ({"lock","clasp","gold lock","gold clasp" }),
    "A small lock and clasp keep this case from being opened.\n");

    add_prop(OBJ_M_NO_GET, "The guards at the entrance will not allow "
    + "you to take this.\n");

    add_prop(CONT_I_TRANSP,1);

    add_prop(CONT_I_LOCK, 1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 10000);

    set_no_pick();
    
  
    set_no_show_composite(1);

}

/* 
 * Function name: set_auction
 * Description  : Set the auction number for this case.
 */

public void set_auction(int number)
{
	if (Auction_number)
	{
		remove_adj(LANG_NUM2WORD(Auction_number));
		remove_adj(""+Auction_number);
	}
	if (number)
	{
		add_adj(LANG_NUM2WORD(number));
		add_adj(""+number);
	}
	set_short("auction "+ number + " case");
	Auction_number = number;
}

/* 
 * Function name: get_auction
 * Description  : Get the auction number for this case.
 */
public int get_auction()
{
    return Auction_number;
}

/* 
 * Function name: is_auction_container
 * Description  : Easy filter to determine auction cases
 */
public int is_auction_container()
{
    return 1;
}

/* 
 * Function name: mylong
 * Description  : Long desc of the case
 */
public string mylong()
{
    return "This is a large glass case" +
    (Auction_number? " for auction "+ Auction_number : "" ) +
    " set atop a marble pedestal. " +
    "There is a gold clasp at the top with a small gold lock.\n";
}

/*
 * Function name: do_default_open
 * Arguments  : str - the rest of the command line by the mortal
 * Returns   : 1 = success, 0 = failure.
 */
public int
do_default_open(string str)
{
    int result = ::do_default_open(str);
    if (result)
    {
        add_adj("open");
        remove_adj("closed");
    }
    return result;
}

/*
 * Function name: do_default_close
 * Arguments  : str - the rest of the command line by the mortal
 * Returns   : 1 = success, 0 = failure.
 */
public int
do_default_close(string str)
{
    int result = ::do_default_close(str);
    if (result)
    {
        add_adj("closed");
        remove_adj("open");
    }
    return result;
}

