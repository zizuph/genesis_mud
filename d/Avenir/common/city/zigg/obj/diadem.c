/*
 * A socketed diadem that can hold standard gems.
 */
#pragma no_inherit
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include "zigg.h"
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>

#define STD_ADJS  ({ "fine-linked", "silver" })
#define GEM_ADJS  ({ j_colour, jewel, "jeweled" })

private static string jewel, j_colour, j_path;

public string
socket_desc(void)
{
    if (strlen(jewel))
    {
	return "The socketed silver toroid currently holds "+
	    LANG_ADDART(j_colour +" "+ jewel +" snugly inside it.\n");
    }

    return "The socketed silver toroid is currently empty.\n";
}

public string
links_desc(void)
{
    string str;

    if (strlen(jewel))
    {
	str = " which currently holds "+
	    LANG_ADDART(j_colour +" "+ jewel) +".\n";
    }
    else
	str = ", which is currently unadorned.\n";

    return "The silver links are exceptionally delicate in appearance "+
	"though they seem to be sturdy enough for daily wear upon your "+
	"brow. Suspended from the front is a toroid of silver"+ str;
}

private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_keep(1);

    set_name("diadem");
    add_name("zigg::diadem", 1);
    set_long("You should not see this text.\n");
    set_adj( STD_ADJS );
    set_short(0);

    add_item( ({ "socket", "toroid", "silver toroid" }), &socket_desc());
    add_item( ({ "links", "fine links", "silver links" }), &links_desc());

    config_wearable_item(A_BROW, 1, 1, 0);

    add_prop(OBJ_M_NO_SELL, "The diadem is much to valuable to sell.\n");
    add_prop(OBJ_M_NO_STEAL, 1);

    jewel = j_colour = j_path = "";
}

/* Customized long description. */
public varargs mixed
long(string str, object looker)
{
    if (strlen(str))
	return ::long(str, looker);
    else if (strlen(jewel))
	str = LANG_ADDART(j_colour +" "+ jewel);

    return "This diadem is a handsome piece of craftwork made of fine, silver "+
	"links. Light scintillates over its smooth surface and refracts back "+
	"in shimmering waves. Suspended by an even finer linked chain of "+
	"silver at the front is a silver toroid. "+ (strlen(str) ?
	    "Firmly embedded within the toroid is "+ str :
	    "Looking closer, you see that the toroid is actually a socket "+
	    "meant for holding gems") + ".\n";
}

/* Used to filter proper gems. We already know these objects
 * are held by the player, since we only grabbed their first
 * level of inventory.
 */
public int
gem_filter(object gem)
{
    return gem->query_gem();
}

/* Called from f_place() to update gem heapsize later, as earlier won't work. */
private void
update_gems(object gem)
{
    gem->set_heap_size(gem->num_heap() - 1);
}

/* Place a gem in the diadem's socket. */
static int
f_place(string str)
{
    int sz;
    string tmp;
    object *arr;

    if (!strlen(str))
	return NF("Place what in the diadem's socket?\n");

    /* Check input. */
    if (!parse_command(str, all_inventory(this_player()),
	    "[the] %i 'in' [the] 'diadem' / 'socket' / 'toroid'", arr))
    {
	return NF("Place what in the diadem's socket?\n");
    }

    /* Search input for gems. */
    arr = NORMAL_ACCESS(arr, "gem_filter", this_object());

    /* We need precisely ONE gem. */
    if (!(sz = sizeof(arr)))
    {
	return NF("Place what in the diadem's socket?\n");
    }
    else if (sz > 2)
    {
	write(CAP(LANG_THESHORT(TO)) +
	    " can only hold one gem at a time.\n");
	return 1;
    }
    else if (objectp(wearer))
    {
	write("You cannot do that while you are wearing it!\n");
	return 1;
    }
    else if (strlen(jewel))
    {
	write("But the diadem is already socketed with a jewel.\n");
	return 1;
    }

    str = arr[0]->query_prop(HEAP_S_UNIQUE_ID);

    /* See if it's a proper gem. */
    if (!strlen(str) || (sscanf(str, "_gem_%s_%s", jewel, j_colour) != 2))
    {
	/* Zero these out; just in case. */
	jewel = j_colour = j_path = "";

	write("You twist and turn, push at and prod, but you cannot "+
	    "seem to get "+ LANG_THESHORT(arr[0]) +
	    " to fit in the socketed toroid.\n");
	say(QCTNAME(TP) + " fiddles around with "+ LANG_ADDART(arr[0]) +
	    " and "+ HIS(TP) +" "+ LANG_SHORT(TO) +".\n");
    }
    else
    {
	/* The gem fits! */
	write("You orientate "+ LANG_THESHORT(arr[0]) +" over the "+
	    "socketed toroid and give a gentle push, feeling it settle "+
	    "securely in place.\n");
	say(QCTNAME(TP) +" takes "+ LANG_ADDART(LANG_SHORT(arr[0])) +
	    " and inserts it into the hanging pendant of "+ HIS(TP) +" "+
	    LANG_SHORT(TO) +".\n");

	/* Update variables and remove gem. */
	j_path = MASTER_OB(arr[0]);
	set_alarm(0.5, 0.0, &update_gems(arr[0]));

	/* Update adjectives to show jeweled state. */
	remove_adj( query_adjs() );
	set_adj( GEM_ADJS );
	set_short(0);
    }

    return 1;
}

/* Remove a gem from the diadem's socket. */
static int
f_remove(string str)
{
    string tmp;
    object gem;

    if (!strlen(str))
	return NF("Remove what from the diadem's socket?\n", 1);

    if (!parse_command(str, ({ }),
	    "[the] %s 'from' [the] 'diadem' / 'socket' / 'toroid'", tmp))
    {
	return NF("Remove what from the diadem's socket?\n");
    }

    if (!IN_ARRAY(tmp, ({ "gem", "jewel", jewel, j_colour +" "+ jewel })))
	return NF("Remove what from the diadem's socket?\n");

    if (objectp(wearer))
    {
	write("You cannot do that while you are wearing it!\n");
	return 1;
    }
    else if (!strlen(jewel))
    {
	write(CAP(LANG_THESHORT(TO)) +" does not seem to contain "+
	    LANG_ADDART(tmp) +".\n");
	return 1;
    }

    if ((file_size(j_path + ".c") < 1) ||
	!objectp(gem = clone_object(j_path)) || !gem->query_gem())
    {
	/* Could not clone the gem, oh well. */
	write("You carefully extract the "+ jewel +" but it "+
	    "slips from your fingers then shatters.\n");
	say(QCTNAME(TP) +" extracts "+ LANG_ADDART(jewel) +" from "+
	    HIS(TP) +" diadem but it slips and shatters.\n");
    }
    else  /* Here we make sure we retrieve the correct gem. */
    {
	str = 0;
	tmp = gem->query_prop(HEAP_S_UNIQUE_ID);

	/* If it's a proper gem, configure it (if necessary).
	 * This has to be done before it's moved and merged with
	 * pre-existing gems of the (possibly) wrong type/colour.
	 */
	if ((sscanf(tmp, "_gem_%s_%s", tmp, str) == 2) &&
	    strlen(str) && (str != j_colour))
	{
	    /* Remove old colour adjective and add new. */
	    gem->remove_adj(str);
	    gem->set_adj(j_colour);
	    /* Update the description. */
	    gem->set_short(j_colour +" "+ gem->query_name());
	    gem->set_pshort(j_colour +" "+ gem->query_pname());
	    /* Update the gem's unique id. */
	    gem->add_prop(HEAP_S_UNIQUE_ID, "_gem_"+ tmp +"_"+ j_colour);
	}

	/* Now, lets try to move it to the player. */
	if (gem->move(TP))
	{
	    /* Could not move gem to player. */
	    gem->remove_object();

	    write("As carefully as you can, you remove the "+ jewel +
		" from the diadem but it slips from your fingers "+
		"and shatters.\n");
	    say(QCTNAME(TP) +" extracts "+ LANG_ADDART(jewel) +" from "+
		HIS(TP) +" diadem but it slips and shatters.\n");
	}
	else
	{
	    /* Gem extracted and moved, we are all done. */
	    write("With practiced skill you extract the "+ jewel +" from "+
		"the diadem's socket.\n");
	    say(QCTNAME(TP) +" manages to extract "+ LANG_ADDART(jewel) +
		" from "+ HIS(TP) +" diadem.\n");
	}
    }

    /* Remove jeweled state and update the short. */
    remove_adj( query_adjs() );
    set_adj( STD_ADJS );
    set_short(0);

    /* Zero out the variables. */
    jewel = j_colour = j_path = "";

    return 1;
}

/* Custom recover string. */
public string
query_recover(void)
{
    return MASTER +":"+ query_keep_recover() +
	"*" +jewel +";"+ j_colour +";"+ j_path +"*";
}

/* Parse custom recover string. */
public void
init_recover(string arg)
{
    init_keep_recover(arg);
    sscanf(arg, "%s*%s;%s;%s*%s",
	arg, jewel, j_colour, j_path, arg);

    if (strlen(jewel))
    {
	/* Update adjectives to show jeweled state. */
	remove_adj( STD_ADJS );
	set_adj( GEM_ADJS );
	set_short(0);
    }

    will_not_recover = (random(100) < RECOVERY_LOST);
}

/* Add actions to the player. */
public void
init(void)
{
    ::init();

    /* Don't bother if player isn't holding it. */
    if (environment() != this_player())
	return;

    add_action(  f_place, "place"  );
    add_action(  f_place, "insert" );
    add_action( f_remove, "remove" );
}

/* Needed masks for wearable items. */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}
