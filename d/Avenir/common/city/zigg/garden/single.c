/*
 * Revisions:
 * 	Lucius, Jun 2017: Also made 'holdable'.
 *
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/commands";
inherit "/lib/holdable_item";

#include "zigg.h"
#include "flowers.h"
#include "/d/Avenir/include/deities.h"

#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <stdproperties.h>

#define TUCKED_SUBLOC  "__zigg_fl_tucked"

private static string type, colour;
private static int locked, no_meld, tucked;

private void make_offering(string kind, string col);


public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_slots(W_ANYH);
    set_name(({"flower","zigg::flower"}));

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);

    add_prop(OBJ_I_NO_SELL, 1);

}

public int
query_tucked(void)	{ return tucked; }

public int
toggle_tucked(void)	{ tucked = !tucked; }

public int
query_no_meld(void)	{ return no_meld; }

public void
set_no_meld(void)	{ no_meld = !no_meld; }

public string
query_flower(void)	{ return type; }

public string
query_colour(void)	{ return colour; }

public void
set_flower(string kind = 0, string col = 0)
{
    mixed *data;

    if (locked)
	return;

    locked = 1;

    if (!strlen(kind) || !m_flowers[kind])
	kind = one_of_list(m_indexes(m_flowers));

    type = kind;
    data = m_flowers[type];

    if (!strlen(col) || !IN_ARRAY(col, data[3]))
	col = one_of_list(data[3]);

    colour = col;

    set_name(data[0][0]);
    set_pname(data[0][1]);

    set_short("single "+ col +" "+ data[0][0]);
    set_pshort(col +" "+ data[0][1]);
    set_adj(({ "single", col }));

    set_long(data[1]);
    add_name("zigg::"+ type);
    
    int low, high;

    if (sscanf(data[4], "%d-%d", low, high) == 2)
    {
	low += random(++high - low);
	add_prop(OBJ_I_VALUE, low);
    }

    make_offering(kind, col);
}

public void
make_random(void)	{ set_flower("random"); }

private void
make_offering(string kind, string col)
{
    switch(kind)
    {
    case "poppy":
	add_prop(MIZRUN_OFFERING, 1);
	break;
    case "passionflower":
	add_prop(JAZUR_OFFERING, 1);
	break;
    case "rose":
	if (col == "black")
	    add_prop(JAZUR_OFFERING, 1);
	break;
    }
}

public void
hook_smelled(string str)
{
    write(m_flowers[type][2] + "\n");
}


public int
altar_special(object altar, object player)
{
    player->catch_msg("You place the " + query_short() + 
       " in front of the bowl as an offering to Mizrun.\n");
    tell_room(environment(player),
        QCTNAME(player) + " places a " + query_short() +
       " in front of the bowl of the altar.\n", player);
    altar->faerie_blessing(player);
    remove_object();
    return 1;
}

/* Handles merging of flowers. */
public void
force_heap_merge(void)
{
    object ob, *obs;
    object env = environment();

    if (!living(env))
	return;

    if (no_meld)
	return;

    /* Add to an existing bouquet. */
    if (objectp(ob = present("zigg::bouquet", env)) ||
	objectp(ob = present("zigg::posy", env)))
    {
	{
	    env->catch_tell("You add the "+ short() +
		" to your "+ ob->short() +".\n");
	}

	ob->moving();
	move(ob);
	ob->update_flowers();
	return;
    }

    /* Try to merge flowers together. */
    obs = FIND_STR_IN_OBJECT("zigg::flowers", env);
    obs = filter(obs, not @ &->query_no_meld());

    if (sizeof(obs) >= BOUQ_NUM)
    {
	if (query_interactive(env))
	{
	    env->catch_tell("You gather your "+
		COMPOSITE_DEAD(obs) +" together into a bouquet.\n");
	}

	/* Form a new bouquet. */
	ob = clone_object(BOUQUET);
    }
    else if (sizeof(obs) >= POSY_NUM)
    {
	if (query_interactive(env))
	{
	    env->catch_tell("You gather your "+
		COMPOSITE_DEAD(obs) +" together into a posy.\n");
	}

	/* Form a new posy. */
	ob = clone_object(POSY);
    }

    if (objectp(ob))
    {
	ob->moving();
	ob->move(env);
	obs->move(ob);
	ob->update_flowers();
    }
}

public string
show_subloc(string sub, object on, object for_ob)
{
    if ((sub != TUCKED_SUBLOC) ||
	on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	return "";
    }

    if (on == for_ob)
	sub = "You have ";
    else
	sub = CAP(HE(on)) +" has ";

    sub += LANG_ADDART(short()) +" tucked behind "+
	(on == for_ob ? "your" : HIS(on)) +" ear.\n";

    return sub;
}

public int
tuck_flower(string str)
{
    object who, ob, *obs;

    if (tucked)
	return 0;

    if (!strlen(str))
	return NF("Tuck what?\n");

    obs = filter(all_inventory(ENV(TP)), living) + ({ TO });

    if (!parse_command(str, obs,
	    "[my] / [the] %o [behind] / [in] [my] [ear]", ob))
    {
	if (!parse_command(str, obs,
		"[my] / [the] %o [behind] / [in] %o [ear]", ob, who))
	{
	    return NF("Tuck what where?\n");
	}

	if (!living(who))
	    return NF("Tuck what where?\n");

	/* Can't tuck flowers to npc's */
	if (!query_interactive(who))
	{
	    write(who->query_The_name(TP) +" won't stand for that!\n");
	    return 1;
	}
    }

    if (ob != TO)
	return NF("Tuck what where?\n");

    if (!objectp(who))
	who = TP;

    if (objectp(ob = who->query_subloc_obj(TUCKED_SUBLOC)))
    {
	write("As much as you might like to, there is already "+
	    LANG_ADDART(ob->short()) +" tucked there.\n");
	return 1;
    }

    /* Self first, then target. */
    if (who == TP)
    {
	write("You tuck the "+ short() +" behind your ear.\n");
	say(QCTNAME(TP) +" tucks "+ HIS(TP) +" "+ short() +" "+
	    "behind "+ HIS(TP) +" ear.\n");
    }
    else
    {
	write("You tuck the "+ short() +" behind "+
	    who->query_the_possessive_name(TP) +" ear.\n");
	say(QCTNAME(TP) +" tucks "+ HIS(TP) +" "+ short() +" "+
	    "behind "+ QTPNAME(who) +" ear.\n", ({ TP, who }));
	who->catch_tell(TP->query_The_name(who) +" tucks "+ HIS(TP) +
	    " "+ short() +" behind your ear.\n");
    }

    /* Move before setting tucked. */
    move(who, "ear");

    set_no_meld();
    toggle_tucked();
    who->add_subloc(TUCKED_SUBLOC, TO);

    return 1;
}

public int
untuck_flower(string str)
{
    object ob, old;

    if (!tucked)
	return 0;

    if (!strlen(str))
	return NF("Untuck what?\n");

    if (!parse_command(str, ({ TO }),
	    "[my] / [the] %o [from] [behind] [my] / [me] [ear]", ob))
    {
	return NF("Untuck what from where?\n");
    }

    old = TP;
    set_this_player(ENV());

    write("You untuck the "+ short() +" from behind your ear.\n");
    say(QCTNAME(TP) +" untucks the "+ short() +" from behind "+
	HIS(TP) +" ear.\n");

    /* Check move before unsetting tucked. */
    if (tucked <= 1)
	move(TP);

    toggle_tucked();
    TP->remove_subloc(TUCKED_SUBLOC);

    set_this_player(old);

    return 1;
}

private static mixed *places = ({
	/* public only locations */
    ({
	"arm", "lips", "neck", "cheek", "chest", "shoulder",
	"tummy", "ear",
    }),
	/* public + hidden locations */
    ({
	"arm", "lips", "neck", "cheek", "chest", "shoulder",
	"tummy", "ear", "thigh", "bottom", "bosom", "cleavage", "calf",
    }),
	/* random default adverbs */
    ({
	"softly", "slowly", "gently", "tenderly",
	"sensually", "lingeringly", ".",
    }),
});

public int
stroke_flower(string str)
{
    int attr;
    object who, *obs;
    string adj = one_of_list(({"delicate", "soft", "silken",}));
    string verb = query_verb(), where, *how;

    if (!strlen(str))
	return NF(CAP(verb) +" what?\n");

    /* Check if we mean us. */
    if (!parse_command(str, ({ TO }),
	    "[my] / [the] %o %s", who, str) || (who != TO))
    {
	return NF(CAP(verb) +" with what?\n");
    }

    /* Parse an adverb */
    how = parse_adverb_with_space(str, one_of_list(places[2]), 0);

    if (!strlen(how[0]))
	return NF(CAP(verb) +" what where?\n");

    who = 0;
    obs = filter(all_inventory(ENV(TP)), living);

    /* Check syntax and validity. */
    if (!parse_command(how[0], obs,
	    "[over] / [against] / [along] %o %s", who, where) &&
	!parse_command(how[0], ({ }),
	    "[over] / [against] / [along] [my] %s", where) &&
	!IN_ARRAY(where, places[1]))
    {
	return NF(CAP(verb) +" what [how] where?\n");
    }

    /* Check who is who */
    if (objectp(who))
    {
	if (!living(who))
	    return NF(CAP(verb) +" what [how] on who's where?\n");

	/* Leave npc's alone. */
	if (!query_interactive(who))
	{
	    write(who->query_The_name(TP) +" won't stand for that!\n");
	    return 1;
	}
    }
    else
    {
	who = TP;
    }

    obs = ({ who });

    /* First pass: Convert words to appropriate ones. */
    switch(where)
    {
    case "chest":
	if (who->query_gender() == G_FEMALE)
	    where = one_of_list(({ "bosom", "cleavage" }));
	break;
    case "bosom":
    case "cleavage":
	if (who->query_gender() != G_FEMALE)
	    where = "chest";
	break;
    }

    if (verb == "stroke")
	verb = "stroking";
    else
	verb += "ing";

    str   = how[1];
    attr  = ACTION_CONTACT | ACTION_MACTIVITY | ACTION_INTIMATE;

    /* Second pass: Print messages. */
    switch(where)
    {
    case "lips":
	/* Fallthru */
    case "cheek":
	if (who == TP)
	{
	    write("You brush the "+ short() +" against your "+ where +
		", "+ verb +" it"+ str +" with the petals.\n");
	    allbb(" brushes "+ HIS(TP) +" "+ short() +" against "+
		HIS(TP) +" "+ where +".", str, attr);
	}
	else
	{
	    actor("You brush your "+ short() +" against", obs, "'s "+
		where +", "+ verb +" it"+ str +" with the petals.");
	    all2actbb(" brushes "+ HIS(TP) +" "+ short() +" against", obs,
		"'s "+ where +".", str, attr);
	    target(" brushes "+ HIS(TP) +" "+ short() +" against your "+
		where +", "+ verb +" it"+ str +" with the petals.",
		obs, str, attr);
	}
	break;
    case "bottom":
	if (who == TP)
	{
	    write("You slide the "+ short() +" along your "+ where +
		","+ str +" "+ verb +" the "+ adj +" petals over it.\n");
	    allbb(" slides "+ HIS(TP) +" "+ short() +" along "+ HIS(TP) +
		" "+ where +".", str, attr);
	}
	else
	{
	    actor("You slide your "+ short() +" along", obs, "'s "+ where +
		","+ str +" "+ verb +" the "+ adj +" petals over it.");
	    all2actbb(" slides "+ HIS(TP) +" "+ short() +" along", obs,
		"'s "+ where +".", str, attr);
	    target(" slides "+ HIS(TP) +" "+ short() +" along your "+
		where +","+ str +" "+ verb +" the "+ adj +" petals "+
		"over it.", obs, str, attr);
	}
	break;
    case "neck":
	/* Fallthru */
    case "shoulder":
	if (who == TP)
	{
	    write("You trace the "+ short() +" along the curve of your "+
		where +","+ str +" "+ verb +" it with the "+ adj +" petals.\n");
	    allbb(" traces "+ HIS(TP) +" "+ short() +" along the curve of "+
		HIS(TP) +" "+ where +".", str, attr);
	}
	else
	{
	    actor("You trace your "+ short() +" along the curve of", obs,
		"'s "+ where +","+ str +" "+ verb +" it with the "+ adj +
		" petals.");
	    all2actbb(" traces "+ HIS(TP) +" "+ short() +" along the curve "+
		"of", obs, "'s "+ where +".", str, attr);
	    target(" traces "+ HIS(TP) +" "+ short() +" along the curve of "+
		"your "+ where +","+ str +" "+ verb +" it with the "+ adj +
		" petals.", obs, str, attr);
	}
	break;
    case "calf":
	if (who == TP)
	{
	    write("You run the "+ short() +" along the back of your "+ where +
		","+ str +" "+ verb +" it with the soft petals.\n");
	    allbb(" runs "+ HIS(TP) +" "+ short() +" along the back of "+
		HIS(TP) +" "+ where +".", str, attr);
	}
	else
	{
	    actor("You run your "+ short() +" along the back of", obs, "'s "+
		where +","+ str +" "+ verb +" it with the soft petals "+
		"until you reach the back of "+ HIS(obs[0]) +" knee.");
	    all2actbb(" runs "+ HIS(TP) +" "+ short() +" along the back of",
		obs, "'s "+ where +".", str, attr);
	    target(" runs "+ HIS(TP) +" "+ short() +" along the back of your "+
		where +","+ str +" "+ verb +" it with the soft petals "+
		"until it tickles the back of your knee.",
		obs, str, attr);
	}
	break;
    case "arm":
	/* Fallthru */
    case "thigh":
	if (who == TP)
	{
	    write("You run the "+ short() +" along your "+ where +
		","+ str +" "+ verb +" it with the soft petals.\n");
	    allbb(" runs "+ HIS(TP) +" "+ short() +" along "+ HIS(TP) +
		" "+ where +".", str, attr);
	}
	else
	{
	    actor("You run your "+ short() +" along", obs, "'s "+ where +
		","+ str +" "+ verb +" it with the soft petals.");
	    all2actbb(" runs "+ HIS(TP) +" "+ short() +" along", obs,
		"'s "+ where +".", str, attr);
	    target(" runs "+ HIS(TP) +" "+ short() +" along your "+
		where +","+ str +" "+ verb +" it with the soft petals.",
		obs, str, attr);
	}
	break;
    case "chest":
	/* Fallthru */
    case "bosom":
	/* Fallthru */
    case "cleavage":
	if (who == TP)
	{
	    write("You pass the "+ short() + str +" over your "+
		where +", "+ verb +" your skin with the "+ adj +" petals.\n");
	    allbb(" passes "+ HIS(TP) +" "+ short() + str +" over "+
		HIS(TP) +" "+ where +".", str, attr);
	}
	else
	{
	    actor("You pass your "+ short() + str +" over", obs,
		"'s "+ where +", "+ verb +" "+ HIS(who) +" skin with the "+
		"delicate petals.");
	    all2actbb(" passes "+ HIS(TP) +" "+ short() + str +" over",
		obs, "'s "+ where +".", str, attr);
	    target(" passes "+ HIS(TP) +" "+ short() +" over your "+ where +
		", "+ verb +" your skin with the "+ adj +" petals.",
		obs, str, attr);
	}
	break;
    default:
	write("You may caress or stroke the following places with your "+
	    "flower:\n    "+ COMPOSITE_WORDS(places[0]) +"\n");
	return 1;
    }

    return 1;
}

public void
leave_env(object from, object to)
{
    if (tucked)
    {
	tucked++;
	untuck_flower(OB_NAME(TO));
    }

    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}

public void
init(void)
{
    ::init();

    if (ENV() != TP)
	return;

    add_action(   tuck_flower, "tuck"   );
    add_action( untuck_flower, "untuck" );
    add_action( stroke_flower, "stroke" );
    add_action( stroke_flower, "caress" );
    add_action(   help_flower, "help"   );
}
