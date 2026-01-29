#pragma strict_types
// file name:   purse.c
// creator(s):  Zielia + Lucius 2007
// last update:
// purpose:  To provide an alternative to the RMC purses without the
//		club extras.
// note:     Based on the RMC purse, without all the hassle.
/*
 * Revisions:
 * 	Lucius, Jun 2017: Modified auto open/close to only work if we
 * 			  are going to try to move something.
 * 			  Also added 'ploot' command.
 *
 */
inherit "/d/Genesis/std/pack";
inherit "/lib/keep";

#include "../bazaar.h"

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>

#define SUBLOC		"_zigg_purse_"
#define WT 		purse[padj][0]
#define MAX_WT  	purse[padj][1]
#define VOL 		purse[padj][2]
#define MAX_VOL 	purse[padj][3]
#define REDUCE	 	purse[padj][4]
#define VALUE	 	purse[padj][5]

private static mapping purse = ([
		       /*  wt , max wt,   vol, max vol, reduce,  val */
	     "small" : ({  100,  10000,   100,    2000,   250,   200 }),
	    "medium" : ({  300,  20000,   300,    4000,   500,   300 }),
	     "large" : ({  500,  30000,   500,    6000,  1000,   400 }),
	      "huge" : ({  700,  40000,   700,    8000,  1500,   600 }),
	  "enormous" : ({  900,  50000,   800,   10000,  2000,   800 }),
	"exorbitant" : ({ 1100,  60000,  1100,   12000,  2500,  1000 }),
]);

private static object worn;
private static int amount, autofill, locked, news = -1;
private static string jewel, material, what, gemfile, gemid, padj;


/* For filtering purposes. */
public nomask int
avenir_money_purse(void)	{ return 1; }

/* Displays the help file. */
private string
read_tag(void)
{
    TP->more(read_file(OBJ + "purse.hlp"));
    return "";
}

/* Number of gems made into us. */
public int
query_gem_amount(void)		{ return amount; }

/* The filepath to the original gem. */
public string
query_gem_file(void)		{ return gemfile; }

/* The unique heap id of the original gem. */
public string
query_gem_id(void)		{ return gemid; }

/* The type / name of the original gem. */
public string
query_gem_type(void)		{ return jewel; }

/* The material of this purse. */
public string
query_material(void)		{ return material; }

/* Sets our particular (if not peculiar) properties. */
private void
make_purse(void)
{
    string *arr, str = " ";

    if (locked)
	return;

    locked = 1;

    switch(amount)
    {
    case   0..99:  padj = "small";	break;
    case 100..199: padj = "medium";	break;
    case 200..299: padj = "large";	break;
    case 300..399: padj = "huge";	break;
    case 400..499: padj = "enormous";	break;
	// 500 or greater
    default:       padj = "exorbitant";	break;
    }

    /* For the short, just the jewel name. */
    if (sizeof(arr = explode(jewel, " ")) > 1)
	str += arr[-1..][0];
    else
	str += jewel;

    str += "-covered";
    what = "The finest quality "+ material +" is beaded with "+
	    LANG_NUM2WORD(amount) +" "+ jewel +" jewels. ";

    set_short(padj + str +" purse");
    set_pshort(padj + str +" purses");
    set_adj(({ padj, material }));
    add_adj(arr + ({ "unworn" }));
    set_long("This is "+ LANG_ADDART(padj) +", finely crafted, "+ material +
	" money-purse useful for carrying coins and gems in opulent "+
	"fashion. "+ what +"A sturdy drawstring allows the purse to open "+
	"and close, while another cord can be used to securely fashion it "+
	"to wrist or belt. A small tag has been sewn to an inside seam.\n");

    add_prop(OBJ_I_VALUE, VALUE);

    add_prop(CONT_I_WEIGHT, WT,);
    add_prop(CONT_I_MAX_WEIGHT, MAX_WT);
    add_prop(CONT_I_REDUCE_WEIGHT, REDUCE);

    add_prop(CONT_I_VOLUME, VOL);
    add_prop(CONT_I_MAX_VOLUME, MAX_VOL);
    add_prop(CONT_I_REDUCE_VOLUME, REDUCE);
}

public int
setup_purse(string mat, object ob)
{
    if (!strlen(mat) || !objectp(ob))
	return 0;

    if (locked)
	return 0;

    material = mat;

    amount  = ob->num_heap();
    jewel   = ob->singular_short();
    gemid   = ob->query_prop(HEAP_S_UNIQUE_ID);
    gemfile = MASTER_OB(ob);

    make_purse();
    return 1;
}

/* Basic creation. */
public void
create_pack(void)
{
    setuid();
    seteuid(getuid());

    set_keep(1);
    set_mass_storage(1);

    set_name(({ "purse", "money-purse" }));
    set_short("broken purse");
    set_long("A plain, busted money-purse.\n");

    add_item(({"tag", "purse tag"}), read_tag);
    add_cmd_item(({"purse"}), "help", read_tag);
    add_cmd_item(({"help"}), "purse", read_tag);

    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL,  1);

    set_alarm(1.0, 0.0, &remove_name("pack"));
}

// Masked to return real_short
public string
vbfc_short(object pobj)
{
    if (!objectp(pobj))
        pobj = previous_object(-1);

    if (!this_object()->check_seen(pobj) ||
        !CAN_SEE_IN_ROOM(pobj))
    {
        return "something";
    }

    return real_short(pobj);
}

private static mapping trim = ([
	     "small" : "spangled",
	    "medium" : "decorated",
	     "large" : "adorned",
	      "huge" : "bedecked",
	  "enormous" : "studded",
	"exorbitant" : "covered",
]);

/* Show our worn subloc (at all times). */
public string
show_subloc(string subloc, object carrier, object for_obj)
{
//   if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
//      return "";

   if (for_obj == carrier)
       subloc = "You wear ";
   else
       subloc = CAP(carrier->query_pronoun()) +" wears ";

   subloc += LANG_ADDART(padj) +" "+ material +" purse ";
   subloc += trim[padj] +" with "+ LANG_PWORD(jewel) +".\n";

   return subloc;
}

/* This prevents manually inserting objects which aren't
 * coins or gems into the purse.
 */
public int
prevent_enter(object ob)
{
    /* Not a coin or gem... prevent. */
    if (!ob->query_coin_type() && !ob->query_gem())
    {
	write("The "+ LANG_SHORT(ob) +" does not belong in your "+
	    real_short() +".\n");
	return 1;
    }

    return 0;
}

/* The argument to "pfill" / "pempty" is passed through
 * here before hitting the item_filter below. This allows
 * selective customization of storage/retrieval of items.
 */
private void
check_what(string str)
{
    what = "";

    if (!strlen(str))
	return;

    str = lower_case(str);

    switch(str)
    {   /* Aliases. */
    case "c":	what = "copper coins";    break;
    case "s":	what = "silver coins";    break;
    case "g":	what = "gold coins";      break;
    case "p":	what = "platinum coins";  break;
    case "t":	what = "sybarun coins";   break;
    case "m":	what = "gems"; 		  break;

       /* Passthru */
    default: what = str; break;
    }
}

/* Call when using mass-storage to determing what to stuff inside us.
 * Our purses over-ride this as we allow only coins and gems.
 * But we also want to allow for more flexible use of the commands
 * to allow for more controlled storing/retrieving.
 */
private int
item_filter(object ob)
{
    int gem = ob->query_gem();
    string coin = ob->query_coin_type();

    /* Not a coin or gem... skip. */
    if (!coin && !gem)
	return 0;

    /* Can't see. */
    if (!ob->check_seen(TP))
	return 0;

    /* Not filtering further. */
    if (!strlen(what))
	return 1;

    /* Default aliases. */
    switch(what)
    {
    case "coin":
    case "coins":
	return strlen(coin);

    case "gem":
    case "gems":
	return gem;
    }

    /* Try expensive parse. */
    return parse_command(what, ({ ob }), "%o", ob);
}

/* Our shortcut "popen" command. */
public varargs int
f_popen(string str, int silent)
{
    str = real_short();

    if (!query_prop(CONT_I_CLOSED))
	return NF("The " + str + " is already open.\n");

    remove_prop(CONT_I_CLOSED);

    write("You open the " + str + ".\n");

    if (!silent)
	say(QCTNAME(TP) + " opens the " + str + ".\n");

    return 1;
}

/* Our shortcut "pclose" command. */
public varargs int
f_pclose(string str, int silent)
{
    str = real_short();

    if (query_prop(CONT_I_CLOSED))
	return NF("The " + str + " is already closed.\n");

    add_prop(CONT_I_CLOSED, 1);

    write("You close the " + str + ".\n");

    if (!silent)
	say(QCTNAME(TP) + " closes the " + str + ".\n");

    return 1;
}

/*
 * fill_me_pack() & empty_me_pack() are
 * masked to allow for custom auto open/close.
 *
 * pack_fail() is an altered version of the
 * pack_fill_fail() / pack_empty_fail() functions.
 */
public int
pack_fail(void)
{
    if (environment(this_object()) != this_player())
    {
	write("You need to get the " + short() + " first.\n");
	return 1;
    }
    /*
     * We do not check CLOSED state as we will
     * automatically open as-needed.
     */
    return 0;
}

public void
fill_me_pack(void)
{
    int flag = 0;
    object *conts, *moved;

    if (pack_fail())
	return;

    conts = filter(all_inventory(this_player()), item_filter);

    if (sizeof(conts))
	flag = f_popen("", 1);

    moved = filter(conts, not @ &->move(this_object()));
    pack_fill_hook(moved);

    if (flag)
	f_pclose("", 1);
}

public void
empty_me_pack(void)
{
    int flag;
    object *conts, *moved;

    if (pack_fail())
	return;

    conts = filter(all_inventory(this_object()), item_filter);
    if (sizeof(conts))
	flag = f_popen("", 1);

    moved = filter(conts, not @ &->move(this_player()));
    pack_empty_hook(moved);

    if (flag)
	f_pclose("", 1);
}

/* Our shortcut "pfill" command.
 * We also handle toggling "auto-fill".
 */
public int
f_pfill(string str)
{
    if (str == "auto")
    {
	if (autofill = !autofill)
	{
	    write("The "+ real_short() +
		" will auto-fill upon awakening.\n");
	}
	else
	{
	    write("The "+ real_short() +
		" will *not* auto-fill upon awakening.\n");
	}

	return 1;
    }

    check_what(str);
    fill_me_pack();
    return 1;
}

/* Our shortcut "pempty" command. */
public int
f_pempty(string str)
{
    check_what(str);
    empty_me_pack();
    return 1;
}

/* Assign [bogus] values to coin-types for sorting. */
private static mapping val_map = ([
	 "sybarun" : 100,
	"platinum" :  50,
	    "gold" :  25,
	  "silver" :  10,
	  "copper" :   5,
]);

/* Sorts our items for more effective viewing. */
private int
sort_purse(object *one, object *two)
{
    string a = one[0]->query_coin_type(),
	   b = two[0]->query_coin_type();

    /* coin && not-coin */
    if (a && !b)
	return -1;

    /* not-coin && coin */
    if (!a && b)
	return 1;

    /* coin vs. coin */
    if (a && b)
    {
	int v_a = val_map[a],
	    v_b = val_map[b];

	/* sort coins based on value */
	if (v_a < v_b)
	    return -1;

	if (v_a > v_b)
	    return 1;

	return 0;
    }

    /* sort gems alphabetically (by colour) */
    a = one[0]->singular_short();
    b = two[0]->singular_short();

    if (a < b)
	return -1;

    if (a > b)
	return 1;

    return 0;
}

/* Prints out a more descriptive inventory view. */
private void
print_items(string *arr, object who, int flag)
{
    int total = 0, sz = sizeof(arr);

    if (!sz)
	return;

    if (flag)
	what = "C * O * I * N * S";
    else
	what = "G * E * M * S";

    who->catch_tell(sprintf(
	"  %'#'74s\n  # %|6s # %|24s ## %|6s # %|24s #\n  %'#'74s\n  ",
	"", "AMOUNT", what, "AMOUNT", what, "" ));

    foreach(string row : arr)
    {
	who->catch_tell(row);

	if (++total >= sz)
	{
	    if (total % 2)
		who->catch_tell(sprintf("#%8s|%26s#\n", "", ""));
	    else
		who->catch_tell("\n");

	    break;
	}

	if (!(total % 2))
	    who->catch_tell("\n  ");
    }
}

/* The main code that decides just what it is we look like
 * on the inside...  just a hint, it's prettier than the code.
 */
public void
describe_contents(object who, object *obarr)
{
    int coins;
    string *sarr;
    mixed *sorted;

    who->catch_tell(show_sublocs(who));

    if (!sizeof(obarr))
    {
	who->catch_tell("The "+ real_short() +" is empty.\n");
	return;
    }

    sarr   = ({ });
    sorted = unique_array(obarr, "singular_short");
    sorted = sort_array(sorted, sort_purse);

    foreach(object *arr : sorted)
    {
	int num = arr[0]->num_heap();

	/* Just in case */
	if (num == 0)
	    continue;

	if (!arr[0]->query_gem())
	    ++coins;

	sarr += ({ sprintf("# %,6.6d | %-24.24s #", num,
		(num > 1 ? arr[0]->plural_short() :
		    arr[0]->singular_short())) });
    }

    who->catch_tell("The "+ real_short() + " contains:\n");

    if (coins)
	print_items(sarr[..(coins - 1)], who, 1);

    if (coins < sizeof(sarr))
	print_items(sarr[coins..], who, 0);

    who->catch_tell(sprintf("  %'#'74s\n", ""));
}

/* Our shortcut "plook" command. */
public int
f_plook(string str)
{
    int flag = f_popen("", 1);

    show_visible_contents(TP);

    if (flag)
	f_pclose("", 1);

    return 1;
}

/* To be compatible (sorta) with other wearable stuff. */
public nomask object
query_worn(void)	{ return worn; }

/* Handle wearing this [unworn] purse. */
public mixed
command_wear(void)
{
    if (worn)
	return "You already wear the "+ short() +".\n";
    else
	worn = environment();

    if (worn->query_subloc_obj(SUBLOC))
	 return "You can only wear one at a time.\n";

    tell_object(worn,
	"You wear the "+ real_short() +".\n");
    tell_room(ENV(worn),
	QCTNAME(worn) +" wears the "+ real_short() +".\n",
	worn, worn);

    set_no_show_composite(1);
    worn->add_subloc(SUBLOC, TO);

    add_prop(OBJ_M_NO_GIVE, "You should remove it first.\n");
    add_prop(OBJ_M_NO_DROP, "You should remove it first.\n");

    add_adj("worn");
    remove_adj("unworn");

    return 1;
}

/* Our shortcut "pwear" command. */
public int
f_pwear(string str)
{
    mixed res;

    if (strlen(str))
	return NF("There is no argument, just \""+ query_verb() +"\".\n");

    res = command_wear();

    if (strlen(res))
	write(res);

    return 1;
}

/* Handle removing this [worn] purse. */
public mixed
command_remove(void)
{
    if (!worn)
	return "You aren't wearing the "+ real_short() +".\n";

    remove_prop(OBJ_M_NO_GIVE);
    remove_prop(OBJ_M_NO_DROP);

    set_no_show_composite(0);
    worn->remove_subloc(SUBLOC);

    tell_object(worn,
	"You remove your "+ real_short() +".\n");
    tell_room(ENV(worn),
	QCTNAME(worn) +" removes "+ worn->query_possessive() +" "+
	real_short() +".\n", worn, worn);

    add_adj("unworn");
    remove_adj("worn");

    worn = 0;
    return 1;
}

/* The shortcut "premove" command. */
public int
f_premove(string str)
{
    mixed res;

    if (strlen(str))
	return NF("There is no argument, just \""+ query_verb() +"\".\n");

    res = command_remove();

    if (strlen(res))
	write(res);

    return 1;
}

/* Don't tell others what was stored. */
public nomask void
pack_fill_hook(object *items)
{
    if (!sizeof(items))
    {
	write("You didn't put anything in the " + short() + ".\n");
	return;
    }

    write("You store " + COMPOSITE_ALL_DEAD(items) +
	" in the " + real_short() + ".\n");
    say(QCTNAME(TP) + " stores some items in " +
	TP->query_possessive() + " " + QSHORT(TO) + ".\n");
}

/* Don't tell others what was retrieved. */
public nomask void
pack_empty_hook(object *items)
{
    if (!sizeof(items))
    {
	write("You didn't retrieve anything from the " + short() + ".\n");
	return;
    }

    write("You retrieve " + COMPOSITE_ALL_DEAD(items) +
	" from the " + real_short() + ".\n");
    say(QCTNAME(TP) + " retrieves some items from " +
	TP->query_possessive() + " " + QSHORT(TO) + ".\n");
}

private static string *coins = ({ });

private int
loot_filter(object ob)
{
    int gem = ob->query_gem();
    string coin = ob->query_coin_type();

    /* Not a coin or gem... skip. */
    if (!coin && !gem)
	return 0;

    /* Can't see. */
    if (!ob->check_seen(TP))
	return 0;

    foreach(string type: coins)
    {
	if (ob->id(type))
	    return 1;
    }
    return 0;
}

public int
f_ploot(string str)
{
    int flag, lootg, lootc;
    mapping tmp = ([ ]);
    object where, *items = ({ });

    // Reset.
    coins = ({ });

    if (!strlen(str))
    {
	coins = ({ "platinum coin", "gold coin", "silver coin",
	   	   "copper coin", "sybarun coin", "gem" });
    }
    else foreach(string type: explode(lower_case(str), ""))
    {
	// No duplicate entries.
	if (tmp[type]) continue;
	else tmp[type] = 1;

	switch(type) {
	case "p": coins += ({ "platinum coin" });	break;
	case "g": coins += ({ "gold coin" });		break;
	case "s": coins += ({ "silver coin" });		break;
	case "c": coins += ({ "copper coin" });		break;
	case "t": coins += ({ "sybarun coin" });	break;
	case "m": coins += ({ "gem" });			break;
	}
    }

//dump_array(coins, "COINS: ");

    where = environment(this_player());
    items = filter(all_inventory(where), loot_filter);

    if (sizeof(items))
    {
//dump_array(items, "GROUND ");
	flag += f_popen("", 1);
	object *moved = filter(items, not @ &->move(this_object()));

	if (sizeof(moved))
	{
	    lootg++;
	    write("You get " + COMPOSITE_ALL_DEAD(moved) +" from the "+
		"ground and store them in the " + real_short() + ".\n");
	    say(QCTNAME(TP) + " grabs some items off the ground and "+
		"stores them in " + TP->query_possessive() + " " +
		QSHORT(TO) + ".\n");
	}
    }

    items = filter(filter(all_inventory(where), &->id("corpse")),
	&->check_seen(this_player()));

    if (sizeof(items))
    {
//dump_array(items, "CORPSE: ");
	foreach(object corpse: items)
	{
	    object *loot = filter(all_inventory(corpse), loot_filter);
	    if (!sizeof(loot))
		continue;

//dump_array(loot, "LOOT: ");
	    flag += f_popen("", 1);
	    object *moved = filter(loot, not @ &->move(this_object()));

	    if (sizeof(moved))
	    {
		lootc++;
		write("You get " + COMPOSITE_ALL_DEAD(moved) +" from "+
		    "the " + corpse->short() + ".\n");
	    }
	}

	if (lootc)
	{
	    write("You store the items inside your "+ real_short() +".\n");
	    say(QCTNAME(TP) + " grabs some items off the nearby "+
		(lootc > 1 ? "corpses" : "corpse") + " and stores them in "+
		TP->query_possessive() +" "+ QSHORT(TO) + ".\n");
	}
    }

    if (!lootg && !lootc)
	write("You found nothing to loot!\n");

    if (flag)
	f_pclose("", 1);

    return 1;
}

/* Cleanup on destruction if needed. */
public void
remove_object(void)
{
    command_remove();
    ::remove_object();
}

/* Make sure we are removed before being moved. */
public void
leave_env(object from, object to)
{
    command_remove();
    ::leave_env(from, to);
}

/* Add commands. */
public void
init(void)
{
    ::init();

    if (TP != ENV(TO))
	return;

    add_action(  f_ploot, "ploot"  );
    add_action(  f_pfill, "pfill"  );
    add_action( f_pempty, "pempty" );
    add_action(  f_popen, "popen"  );
    add_action( f_pclose, "pclose" );
    add_action(  f_plook, "plook"  );

    add_action(   f_pwear, "pwear"   );
    add_action( f_premove, "premove" );
}

public nomask void
print_news(void)
{
    object who = environment();
    who->catch_tell("\n\n!! Your "+ real_short(who) +" has been updated!\n"+
	"!! Check the new 'Looting' section of \"purse help\"!\n\n");
    news = 1;
}

/* We autoload, so no chance of recovery. */
public nomask string
query_recover(void)	{ return 0; }

/* Set us up for auto-loading. */
public nomask string
query_auto_load(void)
{
    return MASTER +":#!"+ amount +"!"+ jewel +"!"+
	material +"!"+ objectp(worn) +"!"+ autofill +"!"+
	query_prop(CONT_I_CLOSED) +"!"+ gemid +"!"+ gemfile +"!"+
	news +"!#";
}

/* Parse our auto-load settings. */
public nomask void
init_arg(string arg)
{
    int c, w;

    sscanf(arg, "%s#!%d!%s!%s!%d!%d!%d!%s!%s!%d!#", arg,
	amount, jewel, material, w, autofill, c, gemid, gemfile, news);

    make_purse();

    if (c == 1)
	add_prop(CONT_I_CLOSED, 1);

    if (w == 1)
	set_alarm(1.0, 0.0, command_wear);

    if (autofill)
	set_alarm(2.0, 0.0, f_pfill);

    if (news < 1)
	set_alarm(8.0, 0.0, print_news);
}

public string
stat_object(void)
{
    return ::stat_object() +
	"Amount:    "+ amount   +"\n"+
	"Material:  "+ material +"\n"+
	"Jewel:     "+ jewel    +"\n"+
	"Gem ID:    "+ gemid    +"\n"+
	"Gem File:  "+ gemfile  +"\n";
}

/* This prop is called at death before moving items.
 * We capture this event, and unconditionally add the
 * OBJ_I_NO_DROP property so that the purse will carry
 * over during re-incarnation and not get left behind
 * in the corpse.
 */
public void
add_prop_obj_o_looted_in_room(mixed val)
{
    add_prop(OBJ_M_NO_DROP, 1);
}
