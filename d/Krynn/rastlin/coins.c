/* 
  /std/coins.c

  This is the heap object for coins.

*/
#pragma save_binary

inherit "/d/Krynn/rastlin/heap";
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include <macros.h>
#include <std.h>

static string           coin_type;   /* The type of coin see above */
static mapping		log_limit;    /* The limit for logging coins */

/*
 * Prototypes
 */

void set_coin_type(string str);

/*
 * Description: Called when creation of coins.
 */
public void
create_coins()
{
    set_name("coin");
    set_pname("coins");
    set_heap_size(1);
    set_coin_type(MONEY_TYPES[0]);
}

public nomask void
create_heap()
{
    log_limit = mkmapping(MONEY_TYPES, ({ 4000, 2000, 20, 10 }));
    add_prop(OBJ_M_NO_SELL, 1);
    create_coins();
    if (!query_prop(HEAP_S_UNIQUE_ID))
	set_coin_type(MONEY_TYPES[0]);
}

public nomask
reset_heap() { this_object()->reset_coins(); }

/*
 * Coins are autoloading
 */
string
query_auto_load()
{
    add_prop(OBJ_I_NO_DROP, 1); /* Destruct coins when saving */
    call_out("rem_drop_prop", 1); /* If not saved allow drop again */
    return MASTER + ":" + num_heap() + "," + coin_type;
}

void rem_drop_prop() { remove_prop(OBJ_I_NO_DROP); }

/* 
 * Called when autoloading
 */
void
init_arg(string arg)
{
    int sum;
    string ct;

    if (sscanf(arg, "%d,%s", sum, ct) == 2)
    {
	set_heap_size(sum);
	set_coin_type(ct);
    }
}

public varargs string
short()
{
    string str;
    
    if (!strlen(query_prop(HEAP_S_UNIQUE_ID)))
    {
	call_out("remove_object", 1);
	return "ghost coins";
    }
    if (coin_type != "")
	str = " ";
    else
	str = "";
    if (num_heap() < 1) return 0;
    if (num_heap() < 2) return "a" + str + coin_type + " coin";
    
    if (num_heap() < 12) 
	return LANG_WNUM(num_heap()) + str + coin_type + " coins";
    
    if (this_player() && this_player()->query_stat(SS_INT) / 2 > num_heap())
	return num_heap() + str + coin_type + " coins";

    return (num_heap() < 1000 ? "many" : "a huge heap of")
	+ str + coin_type + " coins";
}

varargs public mixed
long()
{
    /* It is a heap of ...
     */
    if ((num_heap() < 2) || (num_heap() >= 1000))
	return "It is " + short() + ", it looks like good money.\n";
    else
	return "There are " + short() + ", they look like good money.\n";
}

/*
 * Description: Set the type of coins we have here.
 */
void  
set_coin_type(string str)
{
    int ix;

    mark_state();
    if (coin_type)
    {
	remove_name(coin_type + " coin");
	remove_adj(coin_type);
    }
    ix = member_array(str, MONEY_TYPES);
    coin_type = str;
    if (ix >= 0)
    {
	add_prop(HEAP_I_UNIT_VALUE, MONEY_VALUES[ix]);
	add_prop(HEAP_I_UNIT_WEIGHT, MONEY_WEIGHT[ix]);
	add_prop(HEAP_I_UNIT_VOLUME, MONEY_VOLUME[ix]);
    }
    
    add_prop(HEAP_S_UNIQUE_ID, "_coin_" + coin_type);
    add_name(coin_type + " coin");
    set_adj(coin_type);
    update_state();
}

/*
 * Description: Return what type of coins we have.
 */
string query_coin_type() { return coin_type; }

void
config_split(int new_num,mixed orig)
{
    ::config_split(new_num, orig);
    set_coin_type(orig->query_coin_type());
}

string
stat_object()
{
    string str;

    str = ::stat_object();

    str += "Coin type: " + coin_type + "\n";

    return str;
}

/*
 * Description: Make sure moving of money is logged if the amount is
 * larger than a certain amount.
 */
varargs public int
move(mixed dest, mixed subloc)
{
    object eto = environment(this_object());
    int rval;
    
    rval = ::move(dest, subloc);
    if (num_heap() > log_limit[coin_type])
	SECURITY->log_syslog("MONEY_LOG", ctime(time()) +
			     ": [" +
			     num_heap() + " " + coin_type + "] " +
			     (eto ? file_name(eto) + "[" +
			      (living(eto) ?
			       capitalize(eto->query_real_name()) +
			       ":" : "") + "EUID " +
			      geteuid(eto) + "] " : "void") +
			     "-> " +
			     (dest ? file_name(dest) + "[" +
			      (living(dest) ?
			       capitalize(dest->query_real_name()) +
			       ":" : "" ) + "EUID " +
			      geteuid(dest) + "]\n" : "void"));

    return rval;
}
