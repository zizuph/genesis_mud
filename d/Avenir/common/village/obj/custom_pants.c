// -*-C++-*-
// file name: 	  /d/Avenir/common/village/obj/custom_pants.c
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
   "bloomers"   : ({ "bloomers",
	"These are loose-fitting, roomy trousers that end "+
	"in a ruffle just above the knee."
   }),
   "drawers"    : ({ "drawers",
	"These are loose-fitting, roomy trousers that end "+
	"in a ruffle just above the knee."
   }),
   "harem"      : ({ "harem pants",
	"These trousers are loose-fitting from waist "+
	"to thigh, tapering to fit snugly below the knee to the ankle."
   }),
   "jodhpurs"   : ({ "jodhpurs",
	"These trousers flare at hip and thigh, and are "+
	"tailored at the knee. They end at the calves, and are usually "+
	"worn with boots."
   }),
   "knickers"   : ({ "knickers",
	"These knickers are form-fitting trousers ending "+
	"at the knee."
   }), 
   "pants"      : ({ "pants",
	"These pants extend from the waist to the ankle, "+
	"covering each leg separately."
   }),
   "pantaloons" : ({"pantaloons",
	"These pants extend from the waist to the ankle, "+
	"covering each leg separately."
   }),
   "slacks"     : ({ "slacks",
	"These are loose-fitting trousers with wide legs."
   }),
   "trousers"   : ({ "trousers",
	"These trousers extend from the waist to the ankle, "+
	"covering each leg separately."
   }), 
]);

private string
long_desc(void)
{
    return "This garment was designed by the Sybarun clothiers of "+
	"House F'niel. The "+ style_desc[style][0] +" have been crafted "+
	"from "+ fabric_type[fabric][1] +" and dyed "+ colour +". "+
	style_desc[style][1] +" "+ fabric_type[fabric][2] +"\n";
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
}
  
public void
create_object(void)
{
    ::create_object();
    config_wearable_item(A_LEGS, 1, 15, this_object());
    set_name("pants");
}
