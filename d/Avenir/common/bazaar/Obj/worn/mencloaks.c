// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/worn/cloak.c
// creator(s):	  Lilith 10 July 1997
// last update:	  Lilith 04 Sept 1997
// 		  Lucius May 2007: Cleanups and fixes
// 		  Lucius Oct 2008: More cleanups / refactoring.
//
// purpose:       This is a cloak from the men's tailor.
// note:          It is used both in custom-tailor and shop.  
// bug(s):
// to-do:
#pragma strict_types

#include "mencloth.h"
inherit MENCLOTH_BASE;

public int
wear(void)
{
    write("The "+ short() +" swirls around you as as you drape "+
	"it over your shoulders and fasten it at the neck.\n");

    say(QCTPNAME(TP) +" "+ short() +" swirls as around "+
	OBJECTIVE(TP) +" as "+ PRONOUN(TP) +" drapes it over "+
	POSSESS(TP) +" shoulders and fastens it at "+ POSSESS(TP) +
	" neck.\n");

    return 1;
}

/*
 * Add/mask emotions to make them more fun!
 */
public int
do_bow(string str)
{
    if (!query_worn())
        return 0;

    if (!strlen(str))
    {
        write("You spread wide the folds of your "+ short() +
            " and bow with the flourish of a courtier.\n");
        allbb(" spreads wide the folds of "+ POSSESS(TP) +
            " "+ short() +" and bows with the flourish of "+
            "a courtier.");
	return 1;
    }

    object *oblist = parse_this(str, "[to] / [before] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Bow to <whom>?\n");
	return 0;
    }

    actor("You spread wide the folds of your "+ short() +
        " and bow to", oblist, " with the flourish "+
        "of a courtier.");
    all2actbb(" spreads wide the folds of "+ POSSESS(TP) +" "+ short()
        +" and bows to", oblist, " with the flourish of a "+
        "courtier.");
    targetbb(" spreads wide the folds of "+ POSSESS(TP) +" "+ short()
        +" and bows before you with the flourish of a courtier.", 
        oblist);

    return 1;
}

public int
dance(string str)
{
    if (!query_worn())
        return 0;

    if (!strlen(str))
    {
        write("You hold your hands up as though dancing with an "+
	    "invisible partner, making your "+ short() +" swirl and "+
	    "sway.\n");
	all("'s cloak swirls about "+ OBJECTIVE(TP) +" as "+
	    PRONOUN(TP) +" dances with an imaginary partner.");
	return 1;
    }

    object *oblist = parse_this(str, "[with] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Dance with whom?\n");
	return 0;
    }

    actor("You sweep", oblist, " gallantly into your arms and dance "+ 
        OBJECTIVE(oblist[0]) +" briskly about, sending your "+ short() +
        " swirling behind you.");
    all2act(" gallantly sweeps", oblist, " away to dance, "+ short() +
        " swirling behind "+ OBJECTIVE(TP) +".");
    target(" gallantly sweeps you off to dance, "+ POSSESS(TP) +" "+ 
        short() +" swirling behind "+ OBJECTIVE(TP) +".", oblist);

    return 1;
}

public void
init(void)
{
   ::init();
   
   if (environment() != this_player())
       return;

   add_action(dance,"dance");
   add_action(do_bow, "bow");
}

static string
long_desc(void)
{
    string str;

    if (!strlen(desc))
    {
	str = "This "+ substyle +" has been crafted from "+
	    type +" and dyed "+ colour;
    }
    else
    {
	str = "This "+ substyle +" has been crafted from "+
	    type +", dyed "+ colour +", and is quite "+ desc;
    }

    return str +". "+ fabric_type[type][2] +" A huge quantity of "+
	type +" has gone into the making of this marvellous garment.\n"+
	"An engraved copper plate has been riveted into the inseam.\n";
}

static string
short_desc(void)
{
    if (!strlen(desc))
	return colour +" "+ type +" "+ substyle;
    else
	return desc +" "+ colour +" "+ type +" "+ substyle;
}

public void
create_tailored(void)
{
    if (!strlen(substyle))
	substyle = one_of_list(cloaks);

    ::create_tailored();
}

public void
create_object(void)
{
    ::create_object();
    config_wearable_item(A_ROBE, 1, 15, TO);
    set_name("cloak");
}
