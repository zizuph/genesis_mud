/*
	*An leg part for a mechanical toy
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
	set_name("leg");
	set_pname("legs");
	set_adj("yellow");
	set_adj("jointed");
	set_short("yellow jointed leg");
	set_pshort("yellow jointed legs");
	set_long("It is a part of a toy. It looks like a small " +
	"jointed leg. You might try to 'insert' it to some other " +
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
	add_action("insert_yellow_leg", "insert");
}

int insert_yellow_leg(string str)
{
	if(str == "yellow leg" | str == "the yellow leg" | str == "yellow " +
		"jointed leg" | str == "the yellow jointed leg")
	{
		
		if(TP->query_prop(RED_PROP))
		{
			TP->catch_msg("You insert the yellow leg " +
			"into the metal body.\n");
			
			say(QCTNAME(TP) + " inserts one of the pieces " +
			"in " + HIS_HER(TP) + " hand into one of the other " +
			"pieces " + HE_SHE(TP) + " is holding.\n"); 
			
			TP->add_prop(YELLOW_PROP, 1);
			remove_object();
		}
		
		else
		{
			TP->catch_msg("Hmm... Inserting the yellow leg right " +
			"right now doesn't appear to be the correct order " +
			"of assembly. Try working on a different part.\n");
		}
	}	
	
	else
	{
		TP->catch_msg("Insert what? The yellow leg?\n");
	}
	
	return 1;
}

