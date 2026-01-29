/* trade.c

   This is a standard trade object with some nice funktions.
   Made by Nick, the ever smiling.

   If you want to have a shop or a pub or anything that handles
   money you can include this object and configure it to your
   liking, if you don't settle with the default that is ofcourse.

   Keep on smiling, /Nick

   Typical use:

      inherit "trade.c";

      create_room() {
        config_default_trade();
        .... 
        rest of the create
      }

      then call:

   pay(int amount, object who_pays, string str, int test,
       object who_gets, string str2, int silent)
   give(int amount, object who_gets, string str, int test,
       object who_pays, int silent)

      Both functions return an array doubble size of money types
      with money data if they succeed. First part is money connected 
      to the buying/selling object and last part to this_object.

      If test then no money is being switch, you just get the array

      If there is a str it will be used to see what types of money
      the object wants to pay with, or what types the object wants.
      If str2 is used in pay() it will be used to determin how the
      buyer wants the change, if any.

      If there isn't the first object, this_player() is presumed.

      If the last object is not set, the money will be destructed if pay
      or created out of nowhere on give. If you want to give the money
      from an object, you better be sure the money is present in it.

      If silent flag is set there will be no writing from money moving
      routine if there is an error, i.e. the player can't hold all the
      coins the player is getting and drops some.

      You can call text() with the array from pay/give to get a
      configured text of what money have been in the transaction.
      Observe, text wants just one part of that array at a time.

   User functions in this object
   -----------------------------

   Arguments:     s = string, i=integer, o = object, a = array

   All set functions can be VBFC, and have corresponding query functions
   defined.

   All arrays should be in form: ({ copper, silver, gold, platinum })

   config_default_trade()     Will set up the default configuration for
	or                    trade. If you don't want to set all the
   default_config_trade()     set functions by yourself, call this one.
        both works :)         Se below on notes for about default trade.

   set_money_give_max(i)      Set max value of money the shop gives out.

   set_money_give_out(ai)     Set max money the shop gives of each type.

   set_money_give_reduce(ai)  Set how much on each type to reduce, setting
                              this for silver will give you a wider range of
                              copper coins given out that 0-11. if you reduce
                              silver with one, copper will be in 0-23 format.
                              If in the calculous it has arrived you would
                              get 10 silver coins and reduce is set to 5 you
                              would get 5 silver coins instead and the rest of
                              worth in copper coins.

   set_money_accept(ai)       Set what money we accept.

   set_money_greed_buy(i)     Set greed when person pays for a price, in %.
                              100 means the price in the pay() call will not
                              be changed. >100 will make the player pay more.

   set_money_greed_sell(i)    Set greed when person sells something, in %
                              100 means the price in the give() call will not
                              be changed. >100 will make the player get less.

   set_money_greed_change(i)  Set greed when the person is about to get change
                              100 means the change the person gets will not
                              be changed. >100 will make the player get less
                              change.

   set_money_values(ai)       Set values of each coin type (in cc ofcourse). Do
                              not change this if you haven't got good reasons.

   set_money_types(as)        Set the text strings for each type. Do not change
                              this if you haven't got VERY good reasons.

   pay(i, o, s, i, o, i)      Documented above. Only first i (price) is 
			      necessary.

   give(i, o, s, i, o, i)     Documented above. Only first i (price) is 
			      necessary.


   Play around with them, but not too much.

   Default trade is as follows:

     Max money given out in cc is 1000
     All types of greed is set to 100, which means the price in the calls will 
       be used.
     Types and values of the coins will be used as they are in /sys/money.h
     The trade object accepts all kinds of money
     The trade gives maximum out: 2 platinum, 20 gold, 400 silver and 10000 
       copper coins. Note that if you don't set the copper give out = to max 
       give out you might cut off the copper given out so buyer won't get the
       right money. You can ofcourse check yourself for this and take 
       apropriate action....
     The trade reduces the payout of coins with: 4 platinum, 6 gold, 4 silver
       and 0 copper coins. Note that if you reduce copper the buyer, or seller,
       will be given that amount short. One reason to reduce is that you will
       only pay out platinum coins if the seller hands you a very nice object
       with value > than your reduce factor on platinum, not just as quickly
       you get a value > the value of platinum.


   More functions to call are:

	my_money_merge(ai)     It merges the money in the array into a sum in
                               cc, it calculates with the values set by you.

	my_what_coins(o)       It returns an array of what coins the object
                               containes, needed if you use sepcial types.

	my_split_values(i)     It returns an array of the value splitted into
                               the different coin types.

	can_pay(i, o)	       Checks if the object can pay the price (integer
			       in cc) with the money the object carries.

	can_pay_arr(i, a)      Checks if the array can pay the price.

	want_to_pay(ai, s)     Reduces the array to the types specified in the
			       string

	we_accept(ai)	       Reduces the array to what coins we accept

	calc_change_str(ai ,s) Reduces an array to the types specified in the
			       string, all lesser types are intact.

	calc_change(i, ai, s)  Caluculates the change given back if one pays
			       the price (integer) with the array. The string
                               might tell us how the the change is wanted.

	reduce_coin(i, ai)     Reduces the array according to the price from 
			       the top.

	calc_coins(i, ai, s)   Reduces the array according to the price from
 			       bottom, and calls the calc_change() later with s.

	my_money_move(s, i, o, o) Moves money of type s and number i from first
			       object to the second object.

	text(ai)	       Returns a formated string describing the array
			       in words

	config_default_trade() Configurate the default trade settings.

	pay() and give()       Documented above.

        query_extra_money_holder(i, i, i) If there was an error when trying to
			       Move the money TO us from the player this
			       function is called with what type it was, the
			       amount and what error we got. It wants an object
			       in return, where to move the money instead.

*/

#pragma save_binary

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"

#define TP this_player()
#define NUM num_of_types
#define NF(str) notify_fail(str)

#define MONEY_GIVE_MAX     1000
  /* Good thing to set the copper max to this give max so no money will be lost
  */
  /*                          copper  silver  gold  platinum                */
#define MONEY_GIVE_OUT     ({ 10000,    400,    3,    0 }) 
#define MONEY_GIVE_REDUCE  ({     0,      4,   50,    8 })
#define MONEY_ACCEPT       ({     1,      1,    1,    1 })

/* How greedy are we? 100 will give original price. */
/* The higher the number the less to the liking of  */
/* our fellow mortal player. */
#define MONEY_GREED_BUY     100
#define MONEY_GREED_SELL    100
#define MONEY_GREED_CHANGE  100 

/* move_coins() i money.c doesn't work for me. */
#define M_MONEY_MOVE(str,num, from, to) my_money_move(str, num, from, to)
/* If you use own values on the types this must be in the calculations. */
#define M_MONEY_MERGE(arr) my_money_merge(arr)
/* If you use own types this must be in the calculations. */
#define M_MONEY_COINS(ob) my_what_coins(ob)

/* A way to get around the error I get useing check_call */
#define CC(xxx) this_object()->check_call(xxx)

static mixed money_give_max;
static mixed *money_give_out;
static mixed *money_give_reduce;
static mixed *money_accept;
static mixed money_greed_buy;
static mixed money_greed_sell;
static mixed money_greed_change;
static mixed *money_values;
static mixed *money_types;

static int num_of_types;
    /* Used with NUM instead of the earlier formula there.*/
    /* Holds the number of coin types.*/

/*
 * Function name: set.... and query ....
 * Description:   A lot of sets and querys for global variables used.
 */

void set_money_give_max(mixed i) { money_give_max = i; }
void set_money_give_out(mixed a) { money_give_out = a; }
void set_money_give_reduce(mixed a) { money_give_reduce = a; }
void set_money_accept(mixed a) { money_accept = a; }
void set_money_greed_buy(mixed i) { money_greed_buy = i; }
void set_money_greed_sell(mixed i) { money_greed_sell = i; }
void set_money_greed_change(mixed i) { money_greed_change = i; }
void set_money_values(mixed a) { money_values = a; }
void set_money_types(mixed a)
{
    money_types = a;
    num_of_types = sizeof(a);
}

int query_money_give_max() { return CC(money_give_max); }
int query_money_greed_buy() { return CC(money_greed_buy); }
int query_money_greed_sell() { return CC(money_greed_sell); }
int query_money_greed_change() { return CC(money_greed_change); }

mixed
query_money_types(int i)
{
    if ((i >= 0) && (i < NUM))
	return CC(money_types[i]); 
    else
	return money_types;
}

mixed
query_money_give_out(int i)
{ 
    if ((i >= 0) && (i < NUM))
	return CC(money_give_out[i]);
    else
	return money_give_out;
}

mixed
query_money_give_reduce(int i)
{
    if ((i >= 0) && (i < NUM)) 
	return CC(money_give_reduce[i]); 
    else
	return money_give_reduce;
}

mixed
query_money_accept(int i)
{
    if ((i >= 0) && (i < NUM))
	return CC(money_accept[i]); 
    else
	return money_accept;
}

mixed
query_money_values(int i)
{
    if ((i >= 0) && (i < NUM))
	return CC(money_values[i]); 
    else
	return money_values;
}

/*
 * Functione name: query_extra_money_holder
 * Description:    If the money from the player couldn't be moved to
 *                 the object specified move it to the object returned
 *                 from here instead. Redefine this function if you have
 *                 a trader that might have to drop some coins and you
 *                 you want to keep track of everything.
 * Arguments:      i - number of the money type we tried to move
 *                 sum - the amount we tried to move
 *                 error - the error code we got when we tried
 * Returns:        nothing - destruct the money
 */

varargs mixed
query_extra_money_holder(int type, int sum, int error) { return ; }

/*
 * Function name: my_money_merge
 * Description:   Calculates the worth of an array of coins in cc.
 * Arguments:     arr - the array to calculate
 * Returns:       Sum in cc.
 */
int
my_money_merge(int *arr)
{
    int v, i;
    
    if (sizeof(arr) != NUM)
	return 0;
    
    for (v = 0, i = 0; i < NUM; i++)
	v += arr[i] * query_money_values(i);

    return v;
}

/*
 * Function name: my_what_coins
 * Description:   Finds out what of the cointypes a certain object contains.
 *                Works even if you have special types, I hope :)
 * Argument:      ob: The object in which to search for coins
 * Returns:       Array: ( num copper, num silver, num gold, num platinum )
 *                or the way you defined the types.....
 */
int *
my_what_coins(object ob)
{
    object cn;
    int i, *nums;
    string *ctypes;

    ctypes = query_money_types(-1);
    nums = allocate(NUM);

    for (i = 0; i < NUM; i++)
    {
        cn = present(ctypes[i] + " coin", ob);
        if (!cn)
        {
            nums[i] = 0;
            continue;
        }
        else
            nums[i] = cn->num_heap();
    }
    return nums;
}

/*
 * Function name: my_split_values
 * Description:   Splits a 'copper' value into the types you are using
 * Argument:      value - value in copper coins
 * Returns:       the array
 */
int *
my_split_values(int value)
{
    int *arr, i, coin_val;

    arr = allocate(NUM);

    for (i = 0; i < NUM; i++)
    {
	coin_val = query_money_values(NUM - i - 1);
        while(value >= coin_val)
        {
            arr[NUM - i - 1]++;
            value -= coin_val;
        }
    }

    return arr;
}

/*
 * Function name: can_pay
 * Description:   check if ob can pay the price
 * Arguments:     price - the price to pay
 *                ob - the object who should pay
 * Returns:       1 - can pay, 0 - can't
 */
int
can_pay(int price, object ob)
{
    if (!ob)
	ob = TP;
    if (!ob)
	return 0;
    return price <= M_MONEY_MERGE(M_MONEY_COINS(ob));
}

/*
 * Function name: can_pay_arr
 * Description:   check if the array is enough to pay the price
 * Arguments:     price - the price to pay
 *                arr - the array holding the coins
 * Returns:       1 - can pay, 0 - can't
 */
int
can_pay_arr(int price, int *arr)
{
    return price <= M_MONEY_MERGE(arr);
}

/*
 * Function name: want_to_pay
 * Description:   Check the string and sort out what types of coins to pay with
 *                or better to work with
 * Arguments:     str - string describing the coins object wants to work with
 *                arr - the array holding the coins
 * Returns:       The array depending on what object wants to work with
 */
int *
want_to_pay(int *arr, string str)
{
    string *m_names;
    int i, *tmp_arr, j;
    
    if (!str || (str == ""))
	return arr;
    
    tmp_arr = allocate(NUM);
    m_names = explode(str, " ");

    for (i = 0; i < sizeof(m_names); i++)
	for (j = 0; j < NUM; j++)
	    if (m_names[i] == query_money_types(j))
		tmp_arr[j] = 1;

    for (i = 0; i < NUM; i++)
	arr[i] = arr[i] * tmp_arr[i];

    return arr;
}

/*
 * Function name: we_accept
 * Description:   Compare array with what money we accept
 * Arguments:     arr - the array holding the coins
 * Returns:       The array depending on what we accept
 */
int *
we_accept(int *arr)
{
    int i;
    for(i = 0; i < NUM; i++)
	if (!query_money_accept(i) && arr[i]) {
	    NF("No " + query_money_types(i) + " coins accepted.\n");
	    arr[i] = 0;
	}
    return arr;
}

/*
 * Function name: calc_change_str
 * Description:   Consider what coins the object wants to be payed in
 * Arguments:     arr - the array holding the coins
 *                str - the string describing what types the object wants
 * Returns:       The array depending on what object wants
 */
int *
calc_change_str(int *arr, string str)
{
    int i, j, k, *tmp_arr;
    string *m_names;
    
    m_names = explode(str, " ");
    tmp_arr = allocate(NUM);

    for (i = 0; i < sizeof(m_names); i++)
	for (j = 0; j < NUM; j++)
	    if (m_names[i] == query_money_types(j))
		for (k = j; k >= 0; k--)
		    tmp_arr[k] = 1;

    for (i = 0; i < NUM; i++)
	arr[i] = arr[i] * tmp_arr[i];

    return arr;
}

/*
 * Function name: calc_change
 * Description:   Check what change to give the object considered the price
 *                and what is about to be payed. If no array then it's a sale
 *                and the changed is based on the price alone.
 * Arguments:     arr - the array describing what we already pays
 *                str - the string describing what types the object wants
 *                price - the price in cc
 * Returns:       The array holding the coins the object should be given
 */
int *
calc_change(int price, int *arr, string str)
{
    int *c_arr, new_price, i, sum, *tmp_arr, max, old;

    c_arr = allocate(NUM);
    if (price < 0)
	return c_arr;
    if (arr) /* No greed on change if this isnt change */
        new_price = (M_MONEY_MERGE(arr) - price) * 100 /
	    query_money_greed_change();
    else
	new_price = price;

    if (str && (str != "")) /* If specified how to get change */
	tmp_arr = calc_change_str(query_money_give_out(-1)+({}), str);
    else
	tmp_arr = query_money_give_out(-1);

    /* this is done once to reduce effect if random give max. */  
    max = query_money_give_max();
    if (new_price > 0)
	for(i = NUM - 1; i >= 0; i--)
	    if (new_price >= query_money_values(i) && tmp_arr[i])
	    {
		sum = new_price / query_money_values(i);
    /* This is to allow only high prices to pay platinum */
		sum -= query_money_give_reduce(i);
		if (sum > tmp_arr[i])
		    sum = tmp_arr[i];
		if (sum > 0)
		{
		    c_arr[i] = sum;
                    if (M_MONEY_MERGE(c_arr) > max)
    /* Don't give more than the max */
                        c_arr[i] = (max - old) / query_money_values(i);
		    new_price -= c_arr[i] * query_money_values(i);
                    old = M_MONEY_MERGE(c_arr);
                }
    }

    return c_arr;
}

/*
 * Function name: reduce_coins
 * Description:   Reduce from top of array cosidering the price
 * Arguments:     arr - the array holding the coins
 *                price - the price to pay
 * Returns:       The array object should pay, reduced
 */
int *
reduce_coins(int price, int *arr)
{
    int *pay_arr, i, new_price, dummy;
    
    pay_arr = allocate(NUM);
    new_price = price; /* Keep orignial price intact */

    for (i = NUM - 1; i >= 0; i--)
    {  
    /* Now it could be possible that all lesser coins not will be needed. */
	if (new_price > query_money_values(i) * arr[i])
	{
    /* Ok, we can count off that part from the price */  
	    new_price -= arr[i] * query_money_values(i);
	    pay_arr[i] = arr[i];
	}
	else  /* Maybe we can count away a few coins? */
	   if (new_price > 0)
	    {
    /* Now only this much was needed */
		pay_arr[i] = new_price / query_money_values(i);
		if (price <= M_MONEY_MERGE(pay_arr))
		    break;
		pay_arr[i]++;                /* Nope one more was needed */
		new_price -= pay_arr[i] * query_money_values(i);
	    }
	    else
		break;
    }
    
    /* This _could_ be a very good reduced array if my thinking was right */
    return pay_arr;
}

/*
 * Function name: calc_coins
 * Description:   Reduce from bottom of array cosidering the price
 * Arguments:     arr - the array holding the coins
 *                price - the price to pay
 *                str - a string describing how object wants to get change
 * Returns:       The array object should pay, reduced
 */
int *
calc_coins(int price, int *arr, string str)
{
    int *new_arr, *pay_arr, i, new_price;

    new_arr = allocate(NUM);
    new_price = price; /* Keep orignial price intact */

    for (i = 0; i < NUM; i++)
    {   /* Get an array with the lesser coin types needed */
	new_arr[i] = arr[i];
	
	if (new_price > query_money_values(i) * arr[i])
    /* Ok, we can count out that part from the price */
	    new_price -= arr[i] * query_money_values(i);
	else
	    break;
    }

    /* Reduce to the minimum you have to give away */
    pay_arr = reduce_coins(price, new_arr);

    return pay_arr + calc_change(price, pay_arr, str);
}

/*
 * Function name: my_money_move
 * Description:   Moves the money indicated from object indicated to object
 *                indicated
 * Arguments:     str - the type of coins to move
 *                num - the amount to move
 *                from - where to take money, if 0 money is created
 *                to - where to put the money, if 0 money is destroyed
 * Returns:       0 on sucess, else the error number from move() or -1
 */
int
my_money_move(string str, int num, object from, object to)
{
    object cn, cf;
    int max;

    if (!str || (num <= 0 )) /* Only positive and existing money */
	return -1;

    if (from)
    {
	cf = present(str + " coin", from);
	if (cf && function_exists("create_heap", cf) != "/std/coins")
	    cf = 0;
    }
    else
	cf = MONEY_MAKE(num, str);

    if (!cf || !(max = cf->num_heap()) || num > max )
	return -1;   /* Not enough money to move */

    if (to)
    {
	if (num < max)
	    cf->split_heap(num);
	return cf->move(to);
    }

    if (!to && num < max)
	cf->set_heap_size(max-num);
    else
	cf->remove_object();

    return 0;
}

/*
 * Function name: change_money
 * Description:   Do the moves described in the array between us and the player
 * Arguments:     arr - the array holding the coins, twice as big as number of
 *		        money types, first part is from
 *                from - the one who pays and later gets change if any
 *                to - where to move the money and take change from, or 0
 *                silent - No error code written if set
 * Returns:       > 0 The error from a move() or
 *		  -1 when the money were not to be found in the specified
 *		     object. This also happens if the players has false money.
 *                These codes are multiplied with 10 if the error took place
 *                   when we tried to take money from the player. Also we break
 *                   the transaction if there was an error here.
 *
 *                -10 if the array was of wrong size.
 */
varargs int
change_money(int *arr, object from, object to, int silent)
{
    int i, error1, error2, move_error;

    move_error = 0;

    if (sizeof(arr) != NUM * 2)  /* Not a valid array to change money. */
	return -10;

    for (i = 0; i < NUM; i++) /* Get money from the buyer. */
	if (arr[i] && (error1 = M_MONEY_MOVE(query_money_types(i),
		 arr[i], from, to)))
	{
	    error2 = M_MONEY_MOVE(query_money_types(i), arr[i],
		 from, query_extra_money_holder(i, arr[i], error1));
	    if (error2 != 0)
	    {
		if (!silent && (error2 < 0))
		    write("Error when taking money from the player,\n" +
		        "are there false money around?\n");
/*
   There shouldn't be any errors from move since the environment should be a 
   room, if however a move error has arrived we don't print any text.
   Nor is there a warning if we drop the money on the floor.
*/
		return error2 * 10;
	    }
	}

    for (i = NUM; i < 2 * NUM; i++) /* Give back the change if any. */
	if (arr[i] && (error1 = M_MONEY_MOVE(query_money_types(i-NUM),
		 arr[i], to, from)) && from)
	{
	    error2 = M_MONEY_MOVE(query_money_types(i - NUM),
				 arr[i], to, environment(from));

            if ((move_error == 0) && (error1 != 0))
		move_error = error1;
	
	    if (!silent && error1)
	    {
		/* move error detected */
		write("You drop some of the change.\n");
		say(QCTNAME(from) + " drops some money.\n");
		silent = 1;
	    }
	    else  if (!silent && (error2 < 0))
	    {
		write("Error: No money found in the from object (us), "+
		    "no money given.\n");
		silent = 1;
	    }

            if (error2 < 0)
		move_error = error2;

	}
    /* There shouldnt be an error if noone has messed around with the coins */
    return move_error;
}

/*
 * Function name: text
 * Description:   Generates a text string from the array describing the coins
 * Arguments:     arr - the array holding the coins to describe
 */
mixed
text(int *arr)
{
    string *t_arr, coin_str;
    int i, j;
    
    if (sizeof(arr) < NUM)  /* Not a valid array. */
	return ;

    t_arr = ({});

    for (i = NUM - 1; i >= 0; i--)
	if (arr[i] > 0)
	{
	    j += arr[i]; /* Total number of coins */
	    t_arr += ({ arr[i] + " " + query_money_types(i) });
	}

    coin_str = " coin";
    if (j > 1)
	coin_str += "s";

    j = sizeof(t_arr);

    if (j < 1)
	return;

    if (j == 1)
	return t_arr[0] + coin_str;
    else
	return implode(t_arr[0 .. j - 2], ", ") + " and " +
	       t_arr[j - 1] + coin_str;
}

/*
 * Function name: config_default_trade
 * Description:   Configure the default settings, must be done if not all
 *                set functions are going to be called from the outside
 */
void
config_default_trade()
{
    set_money_give_max(MONEY_GIVE_MAX);
    set_money_give_out(MONEY_GIVE_OUT);
    set_money_give_reduce(MONEY_GIVE_REDUCE);
    set_money_accept(MONEY_ACCEPT);
    set_money_greed_buy(MONEY_GREED_BUY);
    set_money_greed_sell(MONEY_GREED_SELL);
    set_money_greed_change(MONEY_GREED_CHANGE);
    set_money_values(MONEY_VALUES);
    set_money_types(MONEY_TYPES);
}

void
default_config_trade() { config_default_trade(); }

/*
 * Function name: pay
 * Description:   Let the first object pay the price to the second 
 *                object if not test
 * Arguments:     str - the string describing how first object wants to pay
 *                price - the price to pay
 *                ob - the object who should pay
 *                ob2 - the object who should get the money, 0 if none
 *                test - set if this is a test - no money being switched
 *                str2 - string describing how buyer wants the change
 * Returns:       An array describing the object payed and the change it got
 *                Unless something went wrong, then it returns:
 *                  0 - Noone to pay the price found
 *		    1 - The specified money is not enough to pay the price
 * 		    2 - Choosed to pay with money object haven't got
 * 		    3 - Haven't got enough money
 *  		    4 - Can' pay the price after we compare what player has
 * 		        to what we accept, i.e. can't pay in acceptable coins
 *                Also, the last item in the array holds error code from the
 *                money moving routine.
 *                  If > 0 then the player couldn't hold the money it
 * 		    was getting and dropped it.
 *                  If = -1 then one couldn't move the money from the object
 *                  that was specified.
 *                Normally you don't have to bother at all about this one.
 */
varargs int *
pay(int price, object ob, string str, int test, object ob2, string str2,
    int silent)
{
    int *arr, i;

    if (!ob)
	ob = TP;
    if (!ob)
    {
	NF("No buyer recorded.\n");
	return 0;  /* No buyer */
    }

    /* How greedy are we? The original price should be the value of object. */
    price = price * query_money_greed_buy() / 100;
    arr = M_MONEY_COINS(ob);

    if (str) /* Reduce money array to what we wants to pay with */
	arr = want_to_pay(arr, str);

    if (!can_pay_arr(price, arr))
    {
	if (str && (str != "") && M_MONEY_MERGE(arr))
	{
	    NF(break_string("You have to give me more coins to choose from, " +
               text(arr) + " is not enough to pay the price.\n", 70));
	    return ({ 1 });
	}
	else  if (str && (str != ""))
	{
	    NF("I believe you choosed to pay with money you don't carry.\n");
	    return ({ 2 });
	}
	NF("You haven't got enough money to pay the price.\n");
	return ({ 3 });
    }

    arr = we_accept(arr);   /* Reduce to what money we accept */

    /* Still can pay? If not we_accept() have set the NF call */
    if (!can_pay_arr(price, arr))
	return ({ 4 });

    if ((price == 0) && test) 
        arr = arr + calc_change(price, arr, str2);
    else
        arr = calc_coins(price, arr, str2);

    if (!test)
	arr += ({ change_money(arr, ob, ob2, silent) });

    return arr;
}

/*
 * Function name: give
 * Description:   Let the first object give the price to the second object if
 *		  not test
 * Arguments:     price - the price to give
 *                ob - the object who should pay
 *                ob2 - the object who should get the money, 0 if none
 *                test - set if this is a test - no money being switched
 *                str - string describing what money buy wants to get
 * Returns:       An array describing the object payed and the change it got
 */
varargs int *
give(int price, object ob, string str, int test, object ob2, int silent)
{
    int *arr, *tmp_arr, i;
    
    if (!ob && !test)
	ob = TP;
    if (!ob && !test) {
	NF("Nobody to give the money.\n");
	return 0;
    }

    tmp_arr = allocate(NUM);
    price = price * 100 / query_money_greed_sell();
    arr = calc_change (price, 0, str);
    arr = tmp_arr + arr;

    if (!test)
	arr += ({ change_money(arr, ob, ob2, silent) });

    return arr;
}