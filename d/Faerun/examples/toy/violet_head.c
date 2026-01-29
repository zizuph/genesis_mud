/*
	*A head piece of a mechanical toy
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
	set_name("head");
	set_pname("heads");
	set_adj("round");
	set_short("round violet head");
	set_pshort("round violet heads");
	set_long("It is a piece of a toy. You might try to " +
	"'secure' it on another piece of the toy. It looks " +
	"like it might be a head.\n");
	
		
	add_prop(OBJ_I_WEIGHT, 20); 	
	add_prop(OBJ_I_VOLUME, 10);
	add_prop(OBJ_M_NO_STEAL, 0); 	

}

void init()
{
	add_action("secure_violet_head", "secure");
}

int secure_violet_head(string str)
{
	if(str == "violet head" | str == "the violet head" | str == "round " +
		"violet head" | str == "the round violet head")
	{
		if(TP->query_prop(BLUE_PROP))
		{
			TP->catch_msg("You secure the violet head " +
			"to the top of the metal body.\n");
			
			say(QCTNAME(TP) + " secures one of the pieces " +
			"in " + HIS_HER(TP) + " hand on one of the other " +
			"pieces " + HE_SHE(TP) + " is holding.\n"); 
			
			TP->add_prop(VIOLET_PROP, 1);
			remove_object();
		}
		
		else
		{
			TP->catch_msg("Hmm... Securing the violet head " +
			"right now doesn't appear to be the correct order " +
			"of assembly. Try working on a different part.\n");
		}
	}
	
	else
	{
		TP->catch_msg("Secure what? The violet head?\n");
	}
	
	return 1;
}

