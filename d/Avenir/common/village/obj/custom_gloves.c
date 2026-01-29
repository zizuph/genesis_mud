// -*-C++-*-
// file name: 	  /d/Avenir/common/village/obj/custom_gloves.c
// creator(s):	  Lilith Jan 2004
// last update:	  
// 		Lucius Oct 2008: Massive cleanup / rewrite.
//
// purpose:         
// note:      
// bug(s):
// to-do: add emotes like click heels together
#pragma strict_types

#include "custom.h"
inherit CUSTOM_BASE;

public static string size;

public void set_size(string str)	{ size = mystr(str); }
public string query_size(void)		{ return size;       }

mapping style_desc = ([       
   "gloves"  : ({ "glove",
	"They are a fitted covering for the hands "+
	"with a separate sheath for each finger and the thumb."
   }),
   "mittens" : ({ "mitten",
	"They are coverings for the hands that encase "+
	"the thumb separately and the four fingers together."
   }),
]);

public string
long_desc(void)
{
    string str = "These "+ style +" have been crafted from "+
	fabric_type[fabric][1] +" and dyed "+ colour +". "+
	style_desc[style][1] +" They mold the hands perfectly "+
       "and fit snugly";

    switch(size)
    {
        case "small":
        case "short":
        case "low":
            str += " to just past the wrist. ";
            break;
        case "medium":
            str += " from the wrist to the middle of the forearm. ";
            break;
        case "large":
        case "long":
        case "high":
            str += " from the wrist to just below the elbow. ";
            break;
	default:
	    str +=". ";
	    break;
    }

    return str + "These "+ style +" are very elegant and the height "+
	"of fashion. They are an example of fine sybarite "+
	"craftsmanship.\n";
}

private string
short_desc(void)
{
    if (!strlen(size))
	return "pair of "+ colour +" "+ fabric +" "+ style;
    else
	return "pair of "+ size +" "+ colour +" "+ fabric +" "+ style;
}

public void
create_tailored(void)
{
    ::create_tailored();
    set_adj(({ size, colour, fabric }));        
    add_name(({ style, style_desc[style][1] }));     
}
  
public void
create_object(void)
{
    ::create_object();
    config_wearable_item(A_HANDS, 1, 15, this_object());
    set_name("gloves");
}

public int
remove(object ob)
{
    ob = query_worn();

    tell_object(ob, "You pull the "+ short() +" off your "+
        "hands, one finger at a time.\n");
    say(QCTNAME(ob) +" pulls the "+ short() +" off "+ POSSESS(ob) +
        " hands, one finger at a time.\n");

    return 1;
}

public void
custom_recover(string arg)
{
    sscanf(arg, "#Z#%s#", size);
}

public string
query_custom_recover(void)
{
    return "#Z#" + size + "#";
}
