// -*-C++-*-
// file name: 	  /d/Avenir/common/village/obj/custom_vest.c
// creator(s):	  Lilith Jan 2004
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
   "waist-coat" : ({ "waist-coat",
	"A waist-coat is a sleeveless coat or vest, "+
	"lined in high-quality satin. "+
	"It is a garment worn over a shirt and under a coat. "+
	"It covers the waist, extending no lower than the hips, "+
	"and is usually worn by men."
   }),
   "vest"       : ({ "vest",
	"This vest is a collarless, sleeveless garment. "+
	"It is usually worn over a shirt, and covers the upper "+
	"part of the body to just below the waist. It is lined "+
	"in dark silk."
   }),
   "singlet"    : ({ "singlet",
	"A singlet is a simple, sleeveless garment. "+
	"It resembles a waist-coat without the lining and fancy "+
	"stitching."
   }),
]);

private string
long_desc(void)
{
    return "This garment is carefully made by the tailors of "+
	"House Wer'a. The "+ style +" has been dyed "+ colour +
	" and is made of "+ fabric_type[fabric][1] +". "+
	fabric_type[fabric][2] +" "+ style_desc[style][1] +"\n";
}

public void
create_tailored(void)
{
    ::create_tailored();
    set_adj(({ desc, colour, fabric }));        
    add_name(({ style, style_desc[style][1] }));     
}
  
public void
create_object(void)
{
    ::create_object();
    config_wearable_item(A_TORSO, 1, 15, this_object());
}
