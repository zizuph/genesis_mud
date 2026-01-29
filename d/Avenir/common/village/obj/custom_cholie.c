// -*-C++-*-
// file name: 	  /d/Avenir/common/village/obj/custom_cholie.c
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
   "bandeau"     : ({ "bandeau",
	"This is a rather simple undergarment worn "+
	"by women to support their breasts. It consists of a band "+
	"of cloth two hand-spans wide with laces used to tighten "+
	"it once it has been wrapped around the bare torso. Though "+
	"it is usually worn under other garments, it is also worn "+
	"as a top covering by female guards and warriors in "+
	"the practice arena."
   }),
   "blouse"      : ({ "blouse",
	"This blouse is a light, loose, long-sleeved "+
	"garment for the upper body."
   }),
   "bodice"      : ({ "bodice",
	"This bodice is a close-fitting garment forming "+
	"the upper part of a woman's dress, or a portion of it, "+
	"usually tied with laces to ensure a snug fit."
   }),
   "cholie"      : ({ "cholie",
	"It is made to fit snugly, clinging to shoulders "+
	"and breasts while leaving the midriff bare. The sleeves "+
	"are short, ending just above the elbow."
   }),
   "camise"      : ({ "camise",
	"This is a loose, sleeveless shirt similar to a "+
	"tunic, but not as long."
   }),
   "camisole"    : ({ "camisole",
	"This short, sleeveless undergarment is also "+
	"known as an underbodice. It is usually made of a fine "+
	"material that will not irritate the skin when worn "+
	"beneath bodices, shirtwaists, and other, tight-fitting "+
	"garments."
   }),
   "shirt"       : ({ "shirt",
	"This garment extends from the shoulders to "+
	"the waist or hips. Its fit is neither loose nor snug, "+
	"and it is often worn tucked into the waistband of trousers "+
	"and skirts."
   }),
   "shirtwaist"  : ({ "shirtwaist",
	"This is a lightweight, sleeved blouse "+
	"with buttons down the front, designed to be tucked into "+
	"the waistband of trousers or skirts."
   }),
   "underbodice" : ({ "underbodice",
	"The underbodice is a short, sleeveless "+
	"garment usually made of a fine, soft fabric that will not "+
	"irritate the skin when worn beneath bodices, shirtwaists, "+
	"and other, tight-fitting raiments."
   }),
]);  

private string
long_desc(void)
{
    return "This garment was designed especially for the female "+
	"figure by the Sybarun clothiers of House Cimron. The "+
	style +" has been crafted from "+ fabric_type[fabric][1] +
	" and dyed "+ colour +". "+ style_desc[style][1] +" "+
	fabric_type[fabric][2] +"\n";
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
