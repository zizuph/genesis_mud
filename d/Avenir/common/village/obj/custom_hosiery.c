// -*-C++-*-
// file name: 	  /d/Avenir/common/village/obj/custom_hosiery.c
// creator(s):	  Lilith FEB 2004
// last update:	  
// 		Lucius Oct 2008: Massive cleanup / rewrite.
//
// purpose:         
// note:      
// bug(s):
// to-do: add emotes 
#pragma strict_types

#include "custom.h"
inherit CUSTOM_BASE;

mapping style_desc = ([      
   "hose"      : ({ "hose",
	"They cover the body from the waist "+
	"down, fitting closely to each leg and covering the "+
	"feet entirely."
   }),
   "tights"    : ({ "tights",
	"They cover the body from the waist "+
	"down, fitting closely to each leg and covering the "+
	"feet entirely."
   }),
   "stockings" : ({ "stockings",
	"They are made cling to the "+
	"legs, covering the wearer from foot to mid-thigh and "+
	"held in place with lacy garters."
   }),
   "socks"     : ({ "socks",
	"They are a humbler version of the "+
	"stocking, fitting closely to the lower leg from foot "+
	"to just below the knee."
   }),
]);

private string
long_desc(void)
{
    return "These "+ style_desc[style][0] +" have been crafted from "+
	fabric_type[fabric][1] + " and dyed "+ colour +". "+
	style_desc[style][1] +" "+ fabric_type[fabric][2] +
	" This garment is a product of the Sybarun hosiers "+
	"of House Cimron.\n";
}

private string
short_desc(void)
{
    if (!strlen(desc))
        return "pair of "+ colour +" "+ fabric +" "+ style_desc[style][0];       
    else  
        return "pair of "+ desc +" "+ colour +" "+ fabric +" "+
	    style_desc[style][0];       
}

public void
create_tailored(void)
{
    ::create_tailored();
    set_adj(({ desc, colour, fabric }));        
    add_name(({ style, style_desc[style][0] }));     

    if (style == "stockings")
    {
	add_item(({"garter", "garters", "lacy garters" }),
	    "These lacy garters help hold the stockings in place.\n");
    }
}
  
public void
create_object(void)
{
    ::create_object();
    config_wearable_item(A_LEGS, 1, 15, this_object());
}
