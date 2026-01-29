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

/* Prototypes */
public void        create_object();
public int         deposit(string str);
public int         read(string str);
public string      convert_number_to_string(int num);
public int         deposit_coins(int *coins);
public void        tube_action(int *coins, int going_up);



/*
 * Function name: create_object
 * Description: Creates the strongroom with customized settings
 */
public void
create_object()
{
        ::create_object();


        set_long("Coins are secured behind the teller stand. It is clear that "
                + "few coins are kept here, because deposits and withdrawals "
                + "can be seen traveling to and from the central vaults in "
                + "the glass tubes above.\n");

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

public string
convert_number_to_string(int num)
{
    switch (num)
    {
    case 0:
        return "zero";
    
    case 1..5:
        return LANG_NUM2WORD(num);
    
    default:
        return "many";
    }
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
    
    int num_copper = coins[0];
    int num_silver = coins[1];
    int num_gold = coins[2];
    int num_platinum = coins[3];
    
    set_alarm(1.0, 0.0, &tube_action(coins, 1));

    return ::deposit_coins(coins);
}


/*
 * Function name:        tube_action
 * Description  :        have the tubes move some coins around
 * Arguments    :        int coins    - array of the coin amounts
 *                       int going_up - true if the coins should go
 *                                      up rather than down the tube.
 */
public void
tube_action(int *coins, int going_up)
{
    string   which_direction = ((going_up) ? "ascend"  : "descend");
    string   which_tube      = ((going_up) ? "right"   : "left");
    string   which_exit      = ((going_up) ? "ceiling" : "floor");
    string  *coin_types      = ({ "copper", "silver", "gold", "platinum" });
    string   plural          = "";
    int      i = 0;
    string   action_txt      = "";

    foreach(int coin_type : coins)
    {
        if (coin_type)
        {
            if (coin_type > 1)
            {
                plural = "s";
            }

            action_txt += 
                capitalize(convert_number_to_string(coin_type))
              + coin_types[i]
              + " "
              + which_direction + plural
              + " the "
              + which_tube + " tube and "
              + which_direction + plural
              + " into the " + which_exit + ".\n";
        }

        plural = "";
        i++;
    }

    tell_room(environment(this_object()), action_txt);
} /* tube_action */

