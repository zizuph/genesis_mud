// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/worn/menscarf.c
// creator(s):	  Lilith 10 July 1997
// last update:	  Lilith 04 Sept 1997
// 		  Lucius May 2007: Cleanups and fixes
// 		  Lucius Oct 2008: More cleanups / refactoring.
//
// purpose:       This is a scarf from the men's tailor.
//                It can be worn as a cravat.
// note:          It is used both in custom-tailor and shop.  
// bug(s):
// to-do:
#pragma strict_types

#include "mencloth.h"
inherit MENCLOTH_BASE;

static string
long_desc(void)
{
    string str;

    if (!strlen(desc))
    {
	str = "This scarf has been crafted from "+
	    type +" and dyed "+ colour; 
    }
    else
    {
        str = "This scarf has been crafted from "+
	    type +", dyed "+ colour +", and is "+
	    "quite "+ desc;
    }

    return  str +". "+ fabric_type[type][2] + " It can be worn "+
	"around the neck as a cravat.\nAn engraved copper plate "+
	"has been riveted into the inseam.\n";
}

static string
short_desc(void)
{
    if (!query_worn())
        return colour + " "+ type +" scarf";
    else
        return colour + " "+ type +" cravat";
}

public void
create_tailored(void)
{
    ::create_tailored();
    add_name("cravat");
}

public void
create_object(void)
{
    ::create_object();
    config_wearable_item(A_NECK, 1, 15, TO);
    set_name("scarf");
}

public int
wear(void)
{
    write("You drape the " + short() + " around your neck and "+
        "tie it as a cravat.\n");
    say(QCTNAME(TP) + " drapes a " + short() + " around "+ 
        POSSESS(TP) +" neck and ties it as a cravat.\n");

    set_short(short_desc);
    return 1;
}

public int
remove(void)
{
    set_short(short_desc);
    return 1;
}
