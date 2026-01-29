// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/worn/menpants.c
// creator(s):	  Lilith 10 July 1997
// last update:	  Lilith 04 Sept 1997
// 		  Lucius May 2007: Cleanups and fixes
// 		  Lucius Oct 2008: More cleanups / refactoring.
//
// purpose:       This is a pair of pants from the men's tailor.
// note:          It is used both in custom-tailor and shop.  
// bug(s):
// to-do:
#pragma strict_types

#include <adverbs.h>
#include "mencloth.h"
inherit MENCLOTH_BASE;

static string
long_desc(void)
{
    string str;

    if (!strlen(desc))
    {
	str = "This pair of "+ substyle +" has been sewn "+
	    "from "+ type +" and dyed "+ colour; 
    }
    else
    {
        str = "This pair of "+ substyle +" has been sewn "+
	    "from "+ type +", dyed "+ colour +", and is quite "+ desc;
    }

    return  str +". "+ fabric_type[type][2] + " These "+ substyle +
	" seem to be the ultimate in comfort and style.\n"+
	"An engraved copper plate has been riveted into the inseam.\n";
}

static string
short_desc(void)
{
    if (!strlen(desc))
	return "pair of "+ colour + " "+ type +" "+ substyle;
    else
	return desc +" pair of "+ colour + " "+ type +" "+ substyle;
}

static string
pshort_desc(void)
{
    if (!strlen(desc))
        return "pairs of "+ colour + " "+ type +" "+ substyle;
    else
        return desc +" pairs of "+ colour + " "+ type +" "+ substyle;
}

public void
create_tailored(void)
{
    if (!strlen(substyle))
	substyle = one_of_list(pants);

    ::create_tailored();
    set_pshort(pshort_desc);
}

public void
create_object(void)
{
    ::create_object();
    config_wearable_item(A_LEGS, 1, 15, TO);
    set_name("pants");
}

/*
 * Add/mask emotions to make them more fun!
 * fart, grovel, squirm, wiggle
 */
public int
fart(string str)
{
    if (!query_worn())
        return 0;

    if (stringp(str))
    {
	notify_fail("Fart how?\n");
	return 0;
    }

    write("Fortunately for you, the "+ short() +" muffles the "+
        "sound of your fart. Now, if only you could do something "+
        "about the smell!\n");
    say("An odd, unpleasant smell emantates from "+ QTNAME(TP) +".\n");
    return 1;
}

public int
grovel(string str)
{
    if (!query_worn())
        return 0;

    object *oblist = parse_this(str, "[to] / [for] / [before] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Grovel in front of whom?\n");
        return 0;
    }

    actor("You resist the urge to fall to the ground in front of", 
        oblist, ", knowing that you will dirty the knees of your "+
        short() +".");
    all2actbb(" overcomes the urge to fall to the ground and "+
        "grovel in front of", oblist,".");
    target(" overcomes the urge to fall to the ground and grovel "+
        "in front of you.", oblist);

    return 1;
}

public int
squirm(string str)
{
    if (!query_worn())
        return 0;

    str = check_adverb_with_space(str, "uncomfortably");
    if (str == NO_ADVERB_WITH_SPACE)
    {
	notify_fail("Squirm how?\n");
	return 0;
    }

    write("You squirm" + str + " in your "+ short() +".\n");
    all(" squirms" + str + " in "+ POSSESS(TP) +" "+ short() +".", str);
    return 1;
}

public int
wiggle(string str)
{
    if (!query_worn())
        return 0;

    str = check_adverb_with_space(str, BLANK_ADVERB);
    if (str == NO_ADVERB_WITH_SPACE)
    {
	notify_fail("Wiggle how?\n");
	return 0;
    }

    write("You wiggle your bottom" + str + " in your "+ short() +".\n");
    allbb(" wiggles " + this_player()->query_possessive() +
	  " bottom" + str + " in "+ POSSESS(TP) +" "+ short() +".", str);
    return 1;
}

public void
init(void)
{
   ::init();
   
   if (environment() != this_player())
       return;

   add_action(fart,"fart");
   add_action(grovel, "grovel");
   add_action(squirm, "squirm");
   add_action(wiggle, "wiggle");
}
