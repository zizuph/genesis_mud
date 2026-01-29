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
	set_adj("red");
	set_adj("jointed");
	set_short("red jointed leg");
	set_pshort("red jointed legs");
	set_long("It is a part of a toy. It looks like a small " +
	"jointed leg. You might try to 'fasten' it to some other " +
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
	add_action("fasten_red_leg", "fasten");
}

int fasten_red_leg(string str)
{
	if(str == "red leg" | str == "the red leg" | str == "red " +
		"jointed leg" | str == "the red jointed leg")
	{
		TP->catch_msg("You fasten the red leg " +
		"into the metal body.\n");
		
		say(QCTNAME(TP) + " fastens one of the pieces " +
		"in " + HIS_HER(TP) + " hand to one of the other " +
		"pieces " + HE_SHE(TP) + " is holding.\n"); 
		
		this_player()->add_prop(RED_PROP, 1);
		remove_object();
		
	}	
	
	else
	{
		TP->catch_msg("Fasten what? The red leg?\n");
	}
	
	return 1;
}

