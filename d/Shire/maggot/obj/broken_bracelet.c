/*
	*Broken necklace, needs to be fixed
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

#define ONE_PROP 	"_attached_one_bead"
#define TWO_PROP 	"_attached_two_bead"
#define THREE_PROP	"_attached_three_bead"
#define FOUR_PROP	"_attached_four_bead"
#define FIVE_PROP	"_attached_five_bead"
#define PROP_E		"_found_e_bead"
#define PROP_M		"_found_m_bead"
#define PROP_A		"_found_a_bead"
#define PROP_R		"_found_r_bead"
#define PROP_Y		"_found_y_bead"
#define KNOW_NAME	"_know_rosemary_name"
#define FIXED_PROP	"_fixed_broken_bracelet"

void create_object()
{
	set_name("bracelet");
	add_name("_quest_bracelet");
	set_adj("small");
	set_adj("bead");
	set_short("small bead bracelet");
	set_long("@@query_long");
	
	add_item(({"letters"}), "@@query_beads");
	add_item(({"band", "leather band", "strap", "leather strap"}), "It is a slender, supple leather strap.\n");
	
	add_prop(OBJ_I_WEIGHT, 10); 	
	add_prop(OBJ_I_VOLUME, 5);
	add_prop(OBJ_M_NO_STEAL, 0); 
	add_prop(OBJ_M_NO_DROP, "How would you like it if someone intentionally dropped something precious of yours?!\n");
        add_prop(OBJ_M_NO_GIVE, "Don't you think it would be sad if you gave away someone else's bracelet?\n");


}

string query_long()
{
	if(TP->query_prop(FIXED_PROP))
		return "This small bracelet is made from a leather band on which are strung eight small beads. The beads look like they have letters carved on them. It seems all fixed now.\n";
	if(TP->query_prop(FIVE_PROP))
		return "This small bracelet is made from a leather band on which are strung eight small beads. The beads look like they have letters carved on them. The strap still needs to be tied.\n";
	if(TP->query_prop(FOUR_PROP))
		return "This small bracelet is made from a leather band on which are strung seven small beads. The beads look like they have letters carved on them.\n";
	if(TP->query_prop(THREE_PROP))
		return "This small bracelet is made from a leather band on which are strung six small beads. The beads look like they have letters carved on them.\n";
	if(TP->query_prop(TWO_PROP))
		return "This small bracelet is made from a leather band on which are strung five small beads. The beads look like they have letters carved on them.\n";
	if(TP->query_prop(ONE_PROP))
		return "This small bracelet is made from a leather band on which are strung four small beads. The beads look like they have letters carved on them.\n";
	else
		return "This small bracelet is made from a leather band on which are strung three small beads. The beads look like they have letters carved on them.\n";
}

string query_beads()
{
	if(TP->query_prop(FIXED_PROP))
		return "The small beads spell out 'ROSEMARY'.\n";
	if(TP->query_prop(FIVE_PROP))
		return "The small beads spell out 'ROSEMARY'.\n";
	if(TP->query_prop(FOUR_PROP))
		return "The small beads spell out 'ROSEMAR'.\n";
	if(TP->query_prop(THREE_PROP))
		return "The small beads spell out 'ROSEMA'.\n";
	if(TP->query_prop(TWO_PROP))
		return "The small beads spell out 'ROSEM'.\n";
	if(TP->query_prop(ONE_PROP))
		return "The small beads spell out 'ROSE'.\n";
	else
		return "The small beads spell out 'ROS'.\n";
}

void init()
{
	::init();
	add_action("string_beads", "string");
	add_action("tie_strap", "tie");
}

int string_beads(string str)
{
	if(!TP->query_prop(KNOW_NAME))
	{
		TP->catch_msg("How would you know where to start? You don't even know what the beads are supposed to spell.\n");
	}
	
	else
	{
		if(str == "e" | str == "e bead" | str == "E" | str == "E bead")
		{
			if(!TP->query_prop(PROP_E))
			{
				TP->catch_msg("Umm... You don't seem to have a bead like that.\n");
				return 1;
			}
			
			if(!TP->query_prop(ONE_PROP) && TP->query_prop(PROP_E))
			{
				object bead;
				bead = present("_e_bead", TP);
				
				TP->catch_msg("You string a bead onto the leather band. The beads now spell out 'ROSE'.\n");
				
				say(QCTNAME(TP) + " strings a bead onto the leather band " + HE_SHE(TP) + " is holding.\n"); 
				
				TP->add_prop(ONE_PROP, 1);
				bead->remove_object();
			}
			
			else
				TP->catch_msg("Didn't you already string that bead?\n");
				
			return 1;
		}
		
		else if(str == "m" | str == "m bead" | str == "M" | str == "M bead")
		{
			if(!TP->query_prop(PROP_M))
			{
				TP->catch_msg("Umm... You don't seem to have a bead like that.\n");
				return 1;
			}
			
			if(!TP->query_prop(TWO_PROP) && TP->query_prop(PROP_M))
			{
				if(TP->query_prop(ONE_PROP))
				{
					object bead;
					bead = present("_m_bead", TP);
					
					TP->catch_msg("You string a bead onto the leather band. The beads now spell out 'ROSEM'.\n");
					
					say(QCTNAME(TP) + " strings a bead onto the leather band " + HE_SHE(TP) + " is holding.\n"); 
					
					TP->add_prop(TWO_PROP, 1);
					bead->remove_object();
				}
				
				else
					TP->catch_msg("You string a bead onto the leather band, but somehow it just doesn't seem right so you take it off.\n");
			}
			
			else
				TP->catch_msg("Didn't you already string that bead?\n");
				
			return 1;
		}
		
		else if(str == "a" | str == "a bead" | str == "A" | str == "A bead")
		{
			if(!TP->query_prop(PROP_A))
			{
				TP->catch_msg("Umm... You don't seem to have a bead like that.\n");
				return 1;
			}
			
			if(!TP->query_prop(THREE_PROP) && TP->query_prop(PROP_A))
			{
				if(TP->query_prop(TWO_PROP))
				{
					object bead;
					bead = present("_a_bead", TP);
					
					TP->catch_msg("You string a bead onto the leather band. The beads now spell out 'ROSEMA'.\n");
					
					say(QCTNAME(TP) + " strings a bead onto the leather band " + HE_SHE(TP) + " is holding.\n"); 
					
					TP->add_prop(THREE_PROP, 1);
					bead->remove_object();
				}
				
				else
					TP->catch_msg("You string a bead onto the leather band, but somehow it just doesn't seem right so you take it off.\n");
			}
			
			else
				TP->catch_msg("Didn't you already string that bead?\n");
				
			return 1;
		}
		
		else if(str == "r" | str == "r bead" | str == "R" | str == "R bead")
		{
			if(!TP->query_prop(PROP_R))
			{
				TP->catch_msg("Umm... You don't seem to have a bead like that.\n");
				return 1;
			}
			
			if(!TP->query_prop(FOUR_PROP) && TP->query_prop(PROP_R))
			{
				if(TP->query_prop(THREE_PROP))
				{
					object bead;
					bead = present("_r_bead", TP);
					
					TP->catch_msg("You string a bead onto the leather band. The beads now spell out 'ROSEMAR'.\n");
					
					say(QCTNAME(TP) + " strings a bead onto the leather band " + HE_SHE(TP) + " is holding.\n"); 
					
					TP->add_prop(FOUR_PROP, 1);
					bead->remove_object();
				}
				
				else
					TP->catch_msg("You string a bead onto the leather band, but somehow it just doesn't seem right so you take it off.\n");
			}
			
			else
				TP->catch_msg("Didn't you already string that bead?\n");
			
			return 1;
		}
		
		else if(str == "y" | str == "y bead" | str == "Y" | str == "Y bead")
		{
			if(!TP->query_prop(PROP_Y))
			{
				TP->catch_msg("Umm... You don't seem to have a bead like that.\n");
				return 1;
			}
			
			if(!TP->query_prop(FIVE_PROP) && TP->query_prop(PROP_Y))
			{
				if(TP->query_prop(FOUR_PROP))
				{
					object bead;
					bead = present("_y_bead", TP);
					
					TP->catch_msg("You string a bead onto the leather band. The beads now spell out 'ROSEMARY'. All the beads seem to be in the right order. Maybe you should tie the strap so the beads don't fall off again.\n");
					
					say(QCTNAME(TP) + " strings a bead onto the leather band " + HE_SHE(TP) + " is holding.\n"); 
					
					TP->add_prop(FIVE_PROP, 1);
					bead->remove_object();
				}
				
				else
					TP->catch_msg("You string a bead onto the leather band, but somehow it just doesn't seem right so you take it off.\n");
			}
			
			else
				TP->catch_msg("Didn't you already string that bead?\n");
				
			return 1;
			
		}
		
		else
		{
			TP->catch_msg("String what? A bead? Maybe you should be more specific and try to string one of the letters.\n");
			return 1;
		}
	
	}
}
	
int tie_strap(string str)	
{
	if(str == "bracelet" | str == "small bracelet" | str == "strap" | str == "leather strap" | str == "band" | str == "leather band" | str == "bead bracelet" | str == "small bead bracelet")
	{
		if(TP->query_prop(FIVE_PROP))
		{
			TP->catch_msg("You tie up the ends of the leather strap in a tight small knot. Hopefully now the beads will not get lost.\n");
			
			say(QCTNAME(TP) + " ties a knot on the small bracelet " + HE_SHE(TP) + " is holding.\n"); 
			
			TP->remove_prop(PROP_E);
			TP->remove_prop(PROP_M);
			TP->remove_prop(PROP_A);
			TP->remove_prop(PROP_R);
			TP->remove_prop(PROP_Y);
			TP->remove_prop(ONE_PROP);
			TP->remove_prop(TWO_PROP);
			TP->remove_prop(THREE_PROP);
			TP->remove_prop(FOUR_PROP);
			TP->add_prop(FIXED_PROP, 1);			
		}
		
		else
		{
			TP->catch_msg("Hmm... It doesn't look like all the beads are back on the bracelet, better wait to tie it.\n");
		}
	}
	
	else
	{
		TP->catch_msg("Tie what? The bracelet?\n");
	}
	
	return 1;
}
