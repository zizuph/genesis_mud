// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/worn/menshirts.c
// creator(s):	  Lilith 10 July 1997
// last update:	  Lilith 04 Sept 1997
// 		  Lucius May 2007: Cleanups and fixes
// 		  Lucius Oct 2008: More cleanups / refactoring.
//
// purpose:       This is a shirt from the men's tailor.
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
	str = "This "+ substyle +" has been cleverly cut "+
	    "from "+ type +" and dyed "+ colour;
    }
    else
    {
        str = "This "+ substyle +" has been cleverly cut "+
	    "from "+ type +", dyed "+ colour +
	    ", and is quite "+ desc;
    }

    return str +". "+ fabric_type[type][2] + " This "+ substyle +
	" is the most comfortable fashion statement you'll ever "+
	"wear.\nAn engraved copper plate has been riveted into "+
	"the inseam.\n";
}

static string
short_desc(void)
{
    if (!strlen(desc))
        return colour + " "+ type +" "+ substyle;
    else
        return desc +" "+ colour + " "+ type +" "+ substyle;
}

public void
create_tailored(void)
{
    if (!strlen(substyle))
	substyle = one_of_list(shirts);

    ::create_tailored();
    add_name("blouse");
}

public void
create_object(void)
{
    ::create_object();
    config_wearable_item(A_TORSO, 1, 15, TO);
    set_name("shirt");
}

/*
 * Add/mask emotions to make them more fun!
 * flex, comfort
 */
public int
comfort(string str)
{
    if (!query_worn())
        return 0;

    object *oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Comfort whom?\n");
	return 0;
    }

    actor("You comfort", oblist, " against the softness of your "+
        short() +".");
    all2act(" comforts", oblist, " against the softness of "+ POSSESS(TP)
        +" "+ short() +".");
    target(" comforts you against the softness of "+ POSSESS(TP) +
        " "+ short() +".", oblist);

    return 1;
}

public int
flex(string str)
{
    if (!query_worn())
        return 0;

    str = check_adverb_with_space(str, "impressively");
    if (str == NO_ADVERB_WITH_SPACE)
    {
	notify_fail("Flex your muscles how?\n");
	return 0;
    }

    write("You flex your muscles" + str + ", straining the fabric "+
        "of your "+ short() +".\n");
    allbb(" flexes " + this_player()->query_possessive() + " muscles" 
        + str +", straining the fabric of "+ 
        this_player()->query_possessive() +" "+ short() +".", str);

    return 1;
}

public void
init(void)
{
   ::init();

   if (environment() != this_player())
       return;

   add_action(flex,"flex");
   add_action(comfort, "comfort");
}
