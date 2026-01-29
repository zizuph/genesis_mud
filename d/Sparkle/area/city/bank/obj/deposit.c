/*
 * Sparkle Bank Deposit
 *
 * This deposit adds additional functionality on top of the default
 * gnomish deposit.
 *
 * Created by Aeg, April 2011
 */
 
#pragma strict_types

#include <macros.h>
#include <money.h>

inherit "/d/Genesis/obj/deposit";

/*
 * Function name: create_object
 * Description: Creates the strongroom with customized settings
 */
public void
create_object()
{
	::create_object();
	
	
	set_long("Well, it is more of a strongbox... Regardless coins are "
		+ "secured behind the teller stand. It is clear that "
		+ "few coins and gems are kept here, because deposits and "
		+ "withdrawals "
		+ "can be seen travelling to and from the central vaults in "
		+ "the glass tubes above. The left tube is connected directly "
		+ "to the strongbox.\n");
		
	remove_item("letters");
	remove_item("print");
	remove_item("terms");
	remove_item("instructions");
	remove_item("gnome");
	remove_item("bars");
	remove_item("opening");
	remove_name("hut");

}

/*
 * Function name: deposit
 * Description  : The player wants to make a deposit.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
public int
deposit(string str)
{
    tell_room(environment(this_object()), "" + QTNAME(this_player()) 
	+ " approaches the teller stand.\n", 0, this_player());
    return ::deposit(str);
}

/*
 * Function name: read
 * Description  : Called when the player wants to read the text on the sign.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
public int
read(string str)
{
    if (IN_ARRAY(str, ({ "sign", "large sign" }) ))
    {
        return 0;
    }
    
    return ::read(str);
}



/*
 * Function name: deposit_coins
 * Description  : Called to process the deposit of coins.
 * Arguments    : int *coins - the array of coins to be deposited.
 * Returns      : int 1/0 - success/failure.
 */
public int
deposit_coins(int *coins)
{
    
    return ::deposit_coins(coins);
}
