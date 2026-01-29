/*
 * http://www.ostrich.com/feather/featherguide.html
 * http://www.tonyhill.net/productCat43986.ctlg
 *
 * SYNTAX:
 *
 *   stroke [my | desc] feather [adj] [who | my] <location>
 *   caress [my | desc] feather [adj] [who | my] <location>
 *   tickle [my | desc] feather [adj] [who | my] <location>
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/commands";
inherit "/lib/keep";

#include "zigg.h"

#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <stdproperties.h>

#define COST   200  /* Base cost */
#define EXTRA  200  /* Randomized additional cost */

private static string adj, type, colour = one_of_list(({
    "burgandy", "purple", "royal blue", "teal", "red", "black",
    "fuschia", "white", "plum",
}));

private static mapping types = ([
      "ostrich" : ({ "plume", "plumes", ({ "long", "fluffy", }),
		"Ostrich plumes are dyed a variety of colours, this one "+
	  "is %s. These feathers also tend to be longer and are "+
	  "usually wide and fluffy, with extremely soft barbs to "+
	  "both tickle and pleasure.", }),
      "peacock" : ({ "feather", "feathers", ({ "soft", "delicate", }),
     		"The train feathers of peacocks are prized for their "+
	  "decorative qualities. This one, however, has been chosen "+
	  "due to its extra delicateness and placed into service as a "+
	  "tickling feather. Its stem has been dyed %s and the eye at "+
	  "the center is a deep iridescent blue surrounded by gold.", }),
     "pheasant" : ({ "feather", "feathers", ({ "long", "pointed", }),
     		"This is the tail feather from one of a select variety "+
	 "of pheasant. They are slender and long, with a degree of "+
	 "stiffness not common to tickling feathers. Their tips, however, "+
	 "are pointed and soft whilst remaining firm, allowing for more "+
	 "strategic tickling from a distance or simply to get at those "+
	 "harder to reach places. The normally drab colour of this feather "+
	 "has been bleached out and replaced with a %s dye.", }),
]);

private void
config_feather(void)
{
    string str;

    if (!strlen(type))
	type = one_of_list(m_indexes(types));

    if (!strlen(adj))
	adj = one_of_list(types[type][2]);

    set_adj(({ adj, colour, type, "sybarun", "ziggurat"}));

    str = types[type][0];
    set_name(str, 1);
    set_short(adj +" "+ colour +" "+ type +" "+ str);

    str = types[type][1];
    set_pname(str);
    set_pshort(adj +" "+ colour +" "+ type +" "+ str);

    set_long(sprintf(types[type][3] + " Lightly etched into "+
	    "the shaft of this feather are the words "+
	    "\"help feather\".\n", colour));
}

public void
create_object(void)
{
    set_name(({"feather","zigg::feather"}));

    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, COST + random(EXTRA));

    set_keep(1);
    config_feather();	
		
	if (IS_CLONE)
      set_item_expiration();  	

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
f_caress(string str)
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

    /* Get the proper -ing form. */
    switch(verb)
    {
    case "stroke":  verb  = "stroking";  break;
    case "tickle":  verb  = "tickling";  break;
    default:        verb += "ing";       break;
    }

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
		", "+ verb +" it"+ str +" with the edges.\n");
	    allbb(" brushes "+ HIS(TP) +" "+ short() +" against "+
		HIS(TP) +" "+ where +".", str, attr);
	}
	else
	{
	    actor("You brush your "+ short() +" against", obs, "'s "+
		where +", "+ verb +" it"+ str +" with the edges.");
	    all2actbb(" brushes "+ HIS(TP) +" "+ short() +" against", obs,
		"'s "+ where +".", str, attr);
	    target(" brushes "+ HIS(TP) +" "+ short() +" against your "+
		where +", "+ verb +" it"+ str +" with the edges.",
		obs, str, attr);
	}
	break;
    case "bottom":
	if (who == TP)
	{
	    write("You slide the "+ short() +" along your "+ where +
		","+ str +" "+ verb +" the "+ adj +" edges over it.\n");
	    allbb(" slides "+ HIS(TP) +" "+ short() +" along "+ HIS(TP) +
		" "+ where +".", str, attr);
	}
	else
	{
	    actor("You slide your "+ short() +" along", obs, "'s "+ where +
		","+ str +" "+ verb +" the "+ adj +" edges over it.");
	    all2actbb(" slides "+ HIS(TP) +" "+ short() +" along", obs,
		"'s "+ where +".", str, attr);
	    target(" slides "+ HIS(TP) +" "+ short() +" along your "+
		where +","+ str +" "+ verb +" the "+ adj +" edges "+
		"over it.", obs, str, attr);
	}
	break;
    case "neck":
	/* Fallthru */
    case "shoulder":
	if (who == TP)
	{
	    write("You trace the "+ short() +" along the curve of your "+
		where +","+ str +" "+ verb +" it with the "+ adj +" edges.\n");
	    allbb(" traces "+ HIS(TP) +" "+ short() +" along the curve of "+
		HIS(TP) +" "+ where +".", str, attr);
	}
	else
	{
	    actor("You trace your "+ short() +" along the curve of", obs,
		"'s "+ where +","+ str +" "+ verb +" it with the "+ adj +
		" edges.");
	    all2actbb(" traces "+ HIS(TP) +" "+ short() +" along the curve "+
		"of", obs, "'s "+ where +".", str, attr);
	    target(" traces "+ HIS(TP) +" "+ short() +" along the curve of "+
		"your "+ where +","+ str +" "+ verb +" it with the "+ adj +
		" edges.", obs, str, attr);
	}
	break;
    case "calf":
	if (who == TP)
	{
	    write("You run the "+ short() +" along the back of your "+ where +
		","+ str +" "+ verb +" it with the soft edges.\n");
	    allbb(" runs "+ HIS(TP) +" "+ short() +" along the back of "+
		HIS(TP) +" "+ where +".", str, attr);
	}
	else
	{
	    actor("You run your "+ short() +" along the back of", obs, "'s "+
		where +","+ str +" "+ verb +" it with the "+ adj +" edges "+
		"until you reach the back of "+ HIS(obs[0]) +" knee.");
	    all2actbb(" runs "+ HIS(TP) +" "+ short() +" along the back of",
		obs, "'s "+ where +".", str, attr);
	    target(" runs "+ HIS(TP) +" "+ short() +" along the back of your "+
		where +","+ str +" "+ verb +" it with the "+ adj +" edges "+
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
		","+ str +" "+ verb +" it with the soft edges.\n");
	    allbb(" runs "+ HIS(TP) +" "+ short() +" along "+ HIS(TP) +
		" "+ where +".", str, attr);
	}
	else
	{
	    actor("You run your "+ short() +" along", obs, "'s "+ where +
		","+ str +" "+ verb +" it with the "+ adj +" edges.");
	    all2actbb(" runs "+ HIS(TP) +" "+ short() +" along", obs,
		"'s "+ where +".", str, attr);
	    target(" runs "+ HIS(TP) +" "+ short() +" along your "+
		where +","+ str +" "+ verb +" it with the "+ adj +" edges.",
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
		where +", "+ verb +" your skin with the "+ adj +" edges.\n");
	    allbb(" passes "+ HIS(TP) +" "+ short() + str +" over "+
		HIS(TP) +" "+ where +".", str, attr);
	}
	else
	{
	    actor("You pass your "+ short() + str +" over", obs,
		"'s "+ where +", "+ verb +" "+ HIS(who) +" skin with the "+
		"delicate edges.");
	    all2actbb(" passes "+ HIS(TP) +" "+ short() + str +" over",
		obs, "'s "+ where +".", str, attr);
	    target(" passes "+ HIS(TP) +" "+ short() +" over your "+ where +
		", "+ verb +" your skin with the "+ adj +" edges.",
		obs, str, attr);
	}
	break;
    case "tummy":
	if (who == TP)
	{
	    write("You slide the "+ short() + str +" over your "+
		where +", "+ verb +" your skin with the "+ adj +" edges.\n");
	    allbb(" slides "+ HIS(TP) +" "+ short() + str +" over "+
		HIS(TP) +" "+ where +".", str, attr);
	}
	else
	{
	    actor("You slide your "+ short() + str +" over", obs,
		"'s "+ where +", "+ verb +" "+ HIS(who) +" skin with the "+
		"soft edges.");
	    all2actbb(" slides "+ HIS(TP) +" "+ short() + str +" over",
		obs, "'s "+ where +".", str, attr);
	    target(" slides "+ HIS(TP) +" "+ short() +" over your "+ where +
		", "+ verb +" your skin with the "+ adj +" edges.",
		obs, str, attr);
	}
	break;
    default:
	write("You may caress or stroke the following places with your "+
	    "feather:\n    "+ COMPOSITE_WORDS(places[0]) +"\n");
	return 1;
    }

    return 1;
}

public int
f_help(string str)
{
    if (str != "feather")
	return notify_fail("Help with what? Your feather?\n");

    write("The feather takes 3 simple commands, which are "+
	"near identical in result:\n\n"+
	"  * caress <feather> [over/against/along] <my|whose> <where>\n"+
	"  * stroke <feather> [over/against/along] <my|whose> <where>\n"+
	"  * tickle <feather> [over/against/along] <my|whose> <where>\n"+
	"");

    return 1;
}

public void
init(void)
{
    ::init();

    if (ENV() != TP)
	return;

    add_action( f_caress, "stroke" );
    add_action( f_caress, "caress" );
    add_action( f_caress, "tickle" );
    add_action(   f_help, "help"   );
}

public string
query_recover(void)
{
    return MASTER + ":" + query_item_expiration_recover() +
        "#!"+ type +"!"+ adj +"!"+ colour +"!#";
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
    remove_adj(({ adj, colour }));

    sscanf(arg, "%s#!%s!%s!%s!#%s", arg,
        type, adj, colour, arg);

    config_feather();
}
