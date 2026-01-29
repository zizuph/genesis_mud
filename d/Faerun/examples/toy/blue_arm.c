/*
	*An arm part for a mechanical toy
	*Altrus, March 2005
*/

inherit "/std/object";
inherit "/cmd/std/command_driver";

#include "/d/Shire/sys/defs.h"
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

#define BLUE_PROP "_attached_arm_blue"
#define GREEN_PROP "_attached_arm_green"
#define RED_PROP "_attached_leg_red"
#define YELLOW_PROP "_attached_leg_yellow"
#define VIOLET_PROP "_attached_violet_head"

void create_object()
{
	set_name("arm");
	set_pname("arms");
	set_adj("blue");
	set_adj("jointed");
	set_short("blue jointed arm");
	set_pshort("blue jointed arms");
	set_long("It is a part of a toy. It looks like a small " +
	"jointed arm. You might try to 'affix' it to some other " +
	"piece.\n");
	
	
	add_prop(OBJ_I_WEIGHT, 20); 	
	add_prop(OBJ_I_VOLUME, 10);
	add_prop(OBJ_M_NO_STEAL, 0); 
	add_prop(OBJ_M_NO_DROP, "What?! Don't lose it, " +
	"you aren't done putting the toy together!\n");
	add_prop(OBJ_M_NO_GIVE, "What?! Don't lose it, " +
	"you aren't done putting the toy together!\n");
}

void init()
{
	add_action("affix_blue_arm", "affix");
}

int affix_blue_arm(string str)
{
	if(str == "blue arm" | str == "the blue arm" | str == "blue " +
		"jointed arm" | str == "the blue jointed arm")
	{
		
		if(TP->query_prop(GREEN_PROP))
		{
			TP->catch_msg("You affix the blue arm " +
			"to the metal body.\n");
			
			say(QCTNAME(TP) + " affixes one of the pieces " +
			"in " + HIS_HER(TP) + " hand to one of the other " +
			"pieces " + HE_SHE(TP) + " is holding.\n"); 
			
			TP->add_prop(BLUE_PROP, 1);
			remove_object();
		}
		
		else
		{
			TP->catch_msg("Hmm... Affixing the blue arm " +
			"right now doesn't appear to be the correct order " +
			"of assembly. Try working on a different part.\n");
		}
	}	
	
	else
	{
		TP->catch_msg("Affix what? The blue arm?\n");
	}
	
	return 1;
}

