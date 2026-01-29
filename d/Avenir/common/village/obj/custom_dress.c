// -*-C++-*-
// file name: 	  /d/Avenir/common/village/obj/custom_dress.c
// creator(s):	  Lilith Feb 2004
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
   "caftan"   : ({ "caftan",
	"This caftan is a long gown with sleeves reaching "+
	"below the hands. It is generally fastened at the waist or "+
	"hips by a belt or sash."
   }),
   "chemise"  : ({ "chemise",
	"This chemise is a loose-fitting, sleeveless dress "+
	"that hangs straight from the shoulders without any tailoring "+
	"at the waist. It ends just below the knee."
   }),
   "dress"    : ({ "dress",
	"This dress is a one-piece garment with a skirt and "+
	"bodice. The bodice is form-fitting, while the skirt flows "+
	"freely from the waist to the knee."
   }),
   "frock"    : ({ "frock",
	"This frock is a one-piece garment with a skirt and "+
	"bodice. The bodice clings to the torso, forming a vee at the "+
	"waist, while the skirt is slightly tailored and ends at mid-"+
	"thigh."
   }),
   "gown"     : ({ "gown",
	"This is the most formal of all dresses. It is a long, "+
	"flowing garment with a fitted bodice. The gown has small cap "+
	"sleeves that leave the upper arms bare. The wide, bell-shaped "+
	"skirt flows from waist to ankle, swaying with every movement "+
	"of the wearer."
   }),
   "peignoir" : ({"peignoir",
	"This is a woman's loose-fitting dressing gown, "+
	"for wearing before or after sleeping. It is generally made "+
	"of a soft, lightwight material that is sensuous to the touch."
   }),
   "pinafore" :  ({"pinafore" ,
	"This is a sleeveless dress resembling an apron. "+ 
	"It is generally worn over other items of clothing, such as a "+
	"skirt and blouse."
   }),
   "shift"    : ({ "shift",
	"This shift is a loose-fitting, sleeveless dress that "+
	"hangs straight from the shoulders. This dress is without a "+
	"bodice or waist and ends just above the knee. It is particularly "+
	"flattering to women with girlish figures."
   }),
   "skirt"    : ({ "skirt",
	"This is a skirt which cinches at the waist and billows slightly "+
	"as it descends, the hem stopping at the knee to form a classic A "+
	"shape."
   }),
   "smock"    : ({ "smock",
	"This is an angle-length loose dress. It is very comfort"+
	"able and usually worn at home or work, rather than as public "+  
	"attire."
   }),
   "tunic"    : ({ "tunic",
	"This is a garment that can be worn by both sexes. It "+
	"is made without sleeves, and reaches to the knees. It is generally "+
	"worn confined at the waist by a girdle or belt."
   }),
]);  

private string
long_desc(void)
{
    string str;

    if (style == "tunic")
    {
	str = "This "+ short() +" was designed by the Sybarun clothiers "+
	    "of House Cimron.";
    }
    else
    {
	str = "This "+ short() +" was designed especially for the "+
	    "female figure by the Sybarun clothiers of House Cimron.";
    }

    return str +" The "+ style +" has been crafted from "+
	fabric_type[fabric][1] +" and dyed "+ colour +". "+
	style_desc[style][1] +" "+ fabric_type[fabric][2] +"\n";
}

public void
create_tailored(void)
{
    ::create_tailored();
    set_adj(({ desc, colour, fabric }));        
    add_name(({ style, style_desc[style][0] }));     

    if (style == "skirt")
	set_slots(A_WAIST);
}
  
public void
create_object(void)
{
    ::create_object();
    config_wearable_item(A_TORSO, 1, 15, this_object());
}
