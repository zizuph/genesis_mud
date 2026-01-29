/*
	*Body of a mechanical toy
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
	set_name("body");
	set_pname("bodies");
	set_adj("rainbow-colored");
	set_adj("metal");
	set_short("rainbow-colored metal body");
	set_pshort("rainbow-colored metal bodies");
	set_long("It is a piece of a toy, shaped liked a little torso. " +
	"It looks like it has some cogs and gears inside. It has " +
	"various spots on it where other pieces of the toy might " +
	"belong. It is rainbow-colored; from the top down it is " +
	"colored red, yellow, green, blue, violet. It has a small " +
	"switch on its back.\n");
	
	add_item(({"small switch", "switch"}), "The switch is " +
	"is very small indeed. What would happen if you 'flip' " +
	"the switch?\n");
	
	add_prop(OBJ_I_WEIGHT, 20); 	
	add_prop(OBJ_I_VOLUME, 10);
	add_prop(OBJ_M_NO_STEAL, 0); 	

}

void init()
{
	add_action("start_toy", "flip");
}

int start_toy(string str)
{
	if(str == "switch")
	{
		if(TP->query_prop(VIOLET_PROP))
		{
			TP->catch_msg("You flip the switch on the back " +
			"of the toy... The switch suddenly melts into the " +
			"toy and becomes no more. A soft hum can be " +
			"heard from the toy, but just as quickly as it starts " +
			"the humming stops. The toy looks like it is finally " +
			"finished!\n");
			
			say(QCTNAME(TP) + " flips the switch on the back " +
			"of " + HIS_HER(TP) + " mechanical toy. A soft " +
			"hum can be heard from the toy, but just as quickly " +
			"as it starts the humming stops.\n"); 
			
			TP->remove_prop(VIOLET_PROP);
			TP->remove_prop(BLUE_PROP);
			TP->remove_prop(GREEN_PROP);
			TP->remove_prop(YELLOW_PROP);
			TP->remove_prop(RED_PROP);
			
			setuid();
			seteuid(getuid());
			
			clone_object("/w/altrus/obj/toy/mech_toy.c")->move(this_player());
			
			remove_object();
		}
		
		else
		{
			TP->catch_msg("Hmm... The toy doesn't appear " +
			"to be fully assembled yet. Keep working on it.\n");
		}
	}
	
	else
	{
		TP->catch_msg("Flip what? Switch?\n");
	}
	
	return 1;
}



