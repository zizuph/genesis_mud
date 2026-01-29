/*
 * /d/Genesis/obj/deposit_lib.c
 *
 * This is the deposit of the Gnomes of Genesis. It is a bank that can save
 * money for players. To offer the service, just clone this object into your
 * bank room and everything will be taken care of.
 *
 * Coded by Tintin, 1992
 *
 * Version 2.0 by Mercade, July 1995
 */

#pragma no_clone
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#define DEPOSIT_CC   "cc"
#define DEPOSIT_SC   "sc"
#define DEPOSIT_GC   "gc"
#define DEPOSIT_PC   "pc"
#define DEPOSIT_TIME "tm"
#define DEPOSIT_FEE  "fd"

#define DEPOSIT_INDICES ({ DEPOSIT_CC, DEPOSIT_SC, DEPOSIT_GC, DEPOSIT_PC })

#include <macros.h>
#include <money.h>
#include <stdproperties.h>

/*
 * Global variables.
 */
static private string  terms;
static private int     fee;
static private string *money_types;
static private string  accounts;
static private string  coin_file;

/*
 * Prototypes
 */
int account(string str);
int deposit(string str);
int read(string str);
int withdraw(string str);

/*
 * Function name: create_object
 * Description  : This function is called to create the strongroom.
 */
nomask void
create_object() 
{
    set_name("strongroom");
    add_name("deposit");
    add_name("hut");

    add_adj("merchant");
    add_adj("money");

    set_short("strongroom");
    set_long("It is a small fort-like hut. It has an opening protected " +
	"with steel bars and a large sign. Behind the opening there is " +
	"a bored templar.\n");

    add_item( ({ "sign", "large sign" }),
	"A large sign with large, bold letters at the top and a lot " +
	"of fine print at the bottom.\n");

    add_item( ({ "bars", "bar", "steel bars", "steel bar" }),
    	"The steel bars look like they will not bulge even under great " +
    	"pressure.\n");
    add_item( ({ "opening" }),
	"It is the counter, protected by steel bars. Behind it you find a " +
	"grumpy templar.\n");

    add_prop(OBJ_M_NO_GET, "It is not just a strongroom, it is a very heavy " +
	"strongroom as well. No way you can lift it, oh macho one.\n");

    this_object()->create_deposit();

    setuid();
    seteuid(getuid());
}

/*
 * Function name: init
 * Description  : This function is called to add the actions to the player
 *                when he enters the room the strongroom is in.
 */
void
init() 
{
    ::init();

    add_action(account,  "account");
    add_action(deposit,  "deposit");
    add_action(read,     "read");
    add_action(withdraw, "withdraw");
}

/*
 * Function name: enter_env
 * Description  : If we enter a room, let people know that we are here.
 * Arguments    : object dest - the destination of the strongroom.
 *                object old  - where we came from.
 */
void
enter_env(object dest, object old)
{
    dest->add_my_desc("There is a merchant's deposit here.\n",
	this_object());
}

/*
 * Function name: leave_env
 * Description  : The strongroom leaves a room, so remove our add-desc.
 * Arguments    : object old  - the room we leave.
 *                object dest - the destination of the strongroom.
 */
void
leave_env(object old, object dest)
{
    old->remove_my_desc(this_object());
}

/*
 * Function name: set_fee
 * Description  : Set the dayly fee in coins of the lowest denomination.
 * Arguments    : int coins - the fee.
 */
void
set_fee(int coins)
{
    fee = coins;
}

/*
 * Function name: set_terms
 * Description  : Set the terms of the deposit.
 * Arguments    : string text - the terms.
 */
void
set_terms(string text)
{
    terms = text;
}

/*
 * Function name: set_accounts
 * Description  : Set the module that stores the accounts.
 * Arguments    : string file - the filename of the module.
 */
void
set_accounts(string file)
{
    accounts = file;
}

/*
 * Function name: set_money_types
 * Description  : Set the array with the names of the money types. The
 *                smallest denomination first.
 * Arguments    : string *types - the types of money.
 */
void
set_money_types(string *types)
{
    money_types = types;
}

/*
 * Function name: set_coin_file
 * Description  : Set the file that is used for coins.
 * Arguments    : string file - the filename.
 */
void
set_coin_file(string file)
{
    coin_file = file;
}

/*
 * Function name: read
 * Description  : Called when the player wants to read the text on the sign.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
read(string str)
{
    if ((str == "sign") ||
        (str == "large sign"))
    {
	write("The sign reads:\n\n" +
	    "Merchants of Tyr strongroom money deposit\n" +
	    "- asbolutely safe\n" +
	    "- friendly service\n" +
	    "- available everywhere\n" +
	    "- all important places anyway\n" +
	    "- low fees\n" +
	    "After that there is a lot of fine print regulating the terms " +
	    "of deposit.\n");

	return 1;
    }

    if ((str == "print") ||
    	(str == "fine print") ||
    	(str == "terms"))
    {
	write(terms);
	return 1;
    }

    notify_fail("If you want to read, you should find something readable.\n");
    return 0;
}

/*
 * Function name: print_account
 * Description  : Print the contents of an account the the player:
 * Arguments    : mapping acc - the account to print.
 */
static void
print_account(mapping acc)
{
    write(sprintf("%7d %s coins\n", acc[DEPOSIT_PC], money_types[3]));
    write(sprintf("%7d %s coins\n", acc[DEPOSIT_GC], money_types[2]));
    write(sprintf("%7d %s coins\n", acc[DEPOSIT_SC], money_types[1]));
    write(sprintf("%7d %s coins\n", acc[DEPOSIT_CC], money_types[0]));

    if (acc[DEPOSIT_FEE])
    {
	write(sprintf("\n%7d %s coins due in fees\n", acc[DEPOSIT_FEE],
	    money_types[0]));
    }
}

/*
 * Function name: fee_time
 * Description  : This function return the amount of days that the player
 *                owed fee for in total. Hobbits enjoy the special rate.
 * Arguments    : int - the time() the player has manipulated the account.
 * Returns      : int - the number of days extra due.
 */
static int
fee_time(int start_time)
{
    start_time = ((time() - start_time) / 86400) + 1; 
    start_time = ((start_time <= 7) ? start_time : 7) + (start_time - 7) / 7;
    
    if (start_time > 2)
    {
	return start_time;
    }
    if (this_player()->query_race_name() != "hobbit")
    {
	return start_time;
    }
    return 2;
}

/*
 * Function name: deposit
 * Description  : This function is called when the player wants to make
 *                a deposit.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
deposit(string str)
{
    mapping acc;
    int     amount;
    int     coin_index;
    int     days;
    string  user;
    string  coin_type;
    string  dummy;

    if (this_player()->query_wiz_level())
    {
    	notify_fail("There is no need for you to deposit money.\n");
    	return 0;
    }

    if (!strlen(str))
    {
	notify_fail("You have to deposit a sum to open the account\n");
	return 0;
    }
    
    if (!parse_command(str, ({ }), "%d %w %s", amount, coin_type, dummy))
    {
	notify_fail("The templar says: You have to specify amount and cointype!\n");
	return 0;
    }

    if (!amount)
    {
	write("No amount\n");
	return 1;
    }

    if (amount < 1)
    {
	write("You can't deposit negative coins.\n");
	write("If you want to withdraw use that option.\n");
	return 1;
    }

    if ((coin_index = member_array(coin_type, money_types)) < 0)
    {
	write("The templar says: There is no such official money type.\n");
	return 1;
    }

    /* If you want to make some checks before the player deposits any money,
     * you should define the function no_deposit_possible() and if the
     * function returns true, this means that no deposit is possible. You
     * should print your own error message.
     */
    if (this_object()->no_deposit_possible())
    {
        return 1;
    }

    if (MONEY_MOVE(amount, coin_type, this_player(), 0))
    {
	write("You don't have that much money!\n");
	return 1;
    }

    user = this_player()->query_real_name();
    acc = accounts->query_account(user);
    if (!mappingp(acc) || !m_sizeof(acc))
    {
	acc = ([ DEPOSIT_CC  : 0,
		 DEPOSIT_SC  : 0,
		 DEPOSIT_GC  : 0,
		 DEPOSIT_PC  : 0,
		 DEPOSIT_TIME: time(),
		 DEPOSIT_FEE : 0 ]);
    }

    if ((time() - acc[DEPOSIT_TIME]) > 300)
    {
	acc[DEPOSIT_FEE] += (fee_time(acc[DEPOSIT_TIME]) * fee);
	acc[DEPOSIT_TIME] = time();
    }

    acc[DEPOSIT_INDICES[coin_index]] += amount;

    write("Your total account now amounts to:\n");
    print_account(acc);
    say(QCTNAME(this_player()) +
	" deposits some coins in the care of the Merchants of Tyr.\n");
    
    /* Save the account. */
    accounts->set_account(user, acc);
    
    return 1;
}

/*
 * Function name: account
 * Description  : When the player wants to know the amount on his account,
 *                this is the command to use.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
account(string str)
{
    mapping acc;
   
    if (strlen(str))
    {
    	notify_fail("Accounts what?\n");
    	return 0;
    }

    acc = accounts->query_account(this_player()->query_real_name());

    if (!mappingp(acc) || !m_sizeof(acc))
    {
    	notify_fail("The templar says: Sorry, but you do not seem to have " +
    	    "an account with us.\n");
	return 0;
    }

    if ((time() - acc[DEPOSIT_TIME]) > 300)
    {
        acc[DEPOSIT_FEE] += (fee_time(acc[DEPOSIT_TIME]) * fee);
    }

    write("You have placed the following money in our trust:\n");
    print_account(acc);
    say(QCTNAME(this_player()) + " informs about " +
	this_player()->query_possessive() +
	" account at the Merchant Deposit of Tyr.\n");
    return 1;
}

/*
 * Function name: remove_fee
 * Description  : This function removes the fee from the account.
 * Arguments    : mapping - the account to remove the fee from.
 * Returns      : mapping - the account minus the fee.
 */
static mapping
remove_fee(mapping acc)
{
    int *list;
    int  index;
    int  amount = acc[DEPOSIT_FEE];
    int  max = sizeof(money_types);

    list = ({ MONEY_VALUES[0] * acc[DEPOSIT_CC],
	      MONEY_VALUES[1] * acc[DEPOSIT_SC],
	      MONEY_VALUES[2] * acc[DEPOSIT_GC],
	      MONEY_VALUES[3] * acc[DEPOSIT_PC] });

    /* If the account is not big enough to pay the fee, clear the account. */
    if ((list[0] + list[1] + list[2] + list[3]) <= amount)
    {
    	return ([ DEPOSIT_PC : 0,
    		  DEPOSIT_GC : 0,
    		  DEPOSIT_SC : 0,
    		  DEPOSIT_CC : 0 ]);
    }

    for (index = 0; index < max; index++)
    {
        if (amount <= list[index])
        {
            list[index] -= amount;
            break;
        }
        else
        {
            amount -= list[index];
            list[index] = 0;
        }
    }

    amount = 0;
    for (index = max - 1; index >= 0; index--)
    {
        list[index] += amount;
        amount = list[index] % MONEY_VALUES[index];
        list[index] = list[index] / MONEY_VALUES[index];
    }
 
    return ([ DEPOSIT_PC  : list[3],
    	      DEPOSIT_GC  : list[2],
    	      DEPOSIT_SC  : list[1],
    	      DEPOSIT_CC  : list[0],
    	      DEPOSIT_FEE : 0,
    	      DEPOSIT_TIME: acc[DEPOSIT_TIME] ]);
}

/*
 * Function name: make_coins
 * Description  : 
 */

/*
 * Function name: withdraw
 * Description  : This fucntion is called whenever the player wants to
 *                withdwar some money from his/her account.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
withdraw(string str)
{
    mapping acc;
    int     amount;
    int     coin_index;
    int     num_coins;
    string  user;
    string  coin_type;
    string  dummy;
    object  money;

    if (!strlen(str))
    {
	notify_fail("The templar says: You have to state amount and coin " +
	    "type to withdraw.\n");
	return 0;
    }

    if (!parse_command(str, ({ }), "%d %w %s", amount, coin_type, dummy))
    {
	write("Bad coinage!\n");
	return 1;
    }

    if (!amount)
    {
	write("No amount\n");
	return 1;
    }

    if (amount < 1)
    {
	write("You may only withdraw positive numbers\n");
	write("If you want to deposit use that option.\n");
	return 1;
    }
	
    if ((coin_index = member_array(coin_type, money_types)) < 0)
    {
	write("The templar says: There is no such official money type.\n");
	return 1;
    }

    /* If you want to make some checks before the player withdraws any money,
     * you should define the function no_withdrawal_possible() and if the
     * function returns true, this means that no withdrawal is possible.
     * You should print your own error message.
     */
    if (this_object()->no_withdrawal_possible())
    {
    	return 1;
    }

    user = this_player()->query_real_name();
    acc = accounts->query_account(user);

    if (!mappingp(acc))
    {
	write("The templar says: Sorry, but you do not seem to have an " +
	    "account with us.\n");
	return 1;
    }
	
    if ((time() - acc[DEPOSIT_TIME]) > 300)
    {
	acc[DEPOSIT_FEE] += (fee_time(acc[DEPOSIT_TIME]) * fee);
	acc[DEPOSIT_TIME] = time();
    }

    acc = remove_fee(acc);

    write("The templar does some calculations on an abacus and writes " +
	"something with red ink in a huge ledger.\n");

    if ((!acc[DEPOSIT_PC]) &&
    	(!acc[DEPOSIT_GC]) &&
    	(!acc[DEPOSIT_SC]) &&
    	(!acc[DEPOSIT_CC]))
    {
	write("The templar says: The money deposited in your accout does " +
	    "not even cover our fee. I am forced to close your account " +
	    "and register you as having a low reliability. We do " +
	    "not like to deal with people who are not solvent!\n");

    	accounts->remove_account(user);
	return 1;
    }

    if (acc[DEPOSIT_INDICES[coin_index]] < amount)
    {
	write("The templar says: You don't have that many " + coin_type +
	    " coins deposited. After fee deduction you would have had the " +
	    "following money in your account:\n");
	print_account(acc);
	return 1;
    }

    if (objectp(money = present((coin_type + " coin"), this_player())))
    {
    	num_coins = money->num_heap();
    }
    else
    {
    	money = clone_object(coin_file);
    	money->set_coin_type(coin_type);
    	num_coins = 0;
    }

    if ((this_player()->query_prop(CONT_I_MAX_WEIGHT) -
    	this_player()->query_prop(OBJ_I_WEIGHT)) <
    	(amount * money->query_prop(HEAP_I_UNIT_WEIGHT)))
    {
    	amount = ((this_player()->query_prop(CONT_I_MAX_WEIGHT) -
    	    this_player()->query_prop(OBJ_I_WEIGHT)) /
    	    money->query_prop(HEAP_I_UNIT_WEIGHT));

    	if (amount <= 0)
    	{
    	    write("You are completely encumbered and cannot handle even a " +
    	    	"single coin extra. No money is withdrawn.\n");
    	    return 1;
    	}

    	write("You cannot carry that many " + coin_type +
    	    " coins. Therefore only " + amount + " " + coin_type +
    	    " coin" + ((amount == 1) ? "" : "s") +
    	    " will be paid out to you.\n");
    }

    money->set_heap_size(num_coins + amount);
    money->move(this_player());
    write("You are handed " + amount + " " + coin_type + " coin" +
    	((amount == 1) ? "" : "s") + ".\n");   

    acc[DEPOSIT_INDICES[coin_index]] -= amount;

    /* If there are coins left, save the account, else remove it. */
    if ((acc[DEPOSIT_PC]) ||
    	(acc[DEPOSIT_GC]) ||
    	(acc[DEPOSIT_SC]) ||
    	(acc[DEPOSIT_CC]))
    {
	accounts->set_account(user, acc);

     write("After deduction of the fee and the withdrawal of the coins, " +
	    "your account amounts to:\n");
	print_account(acc);
    }
    else
    {
    	accounts->remove_account(user);

    	write("The templar says: Since you no longer have any coins in our " +
    	    "trust, I shall close your account.\n");
    }

    write("The templar says: Thank you for putting your money in our trust.\n");
    say(QCTNAME(this_player()) + 
	" withdraws some coins from the Merchants of Tyr.\n");
    return 1;
}
