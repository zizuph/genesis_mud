/*
	*Battle standard for the orcs of middle earth
	*Altrus, May 2005
*/

inherit "/std/object";
inherit "/cmd/std/command_driver";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <wa_types.h>      
#include <formulas.h>      
#include <macros.h>        
#include "/d/Shire/guild/orc_guild/orc.h"

#define PLANTED "_standard_is_planted"
#define IS_STANDARD "_standard_for_orcs"
#define IS_PAINTED "_standard_is_painted"
#define IS_LASHED "_standard_is_lashed"
#define HAS_LASHED "_has_standard_lashed"

void create_object()
{
	set_name("standard");
	add_name("battle standard");
	add_pname("battle standards");
	set_pname("standards");
	add_name("_battle_standard");
	
	add_prop(OBJ_I_WEIGHT, 1750); 	
	add_prop(OBJ_I_VOLUME, 550);
	add_prop(IS_STANDARD, 1);
}

void init()
{
	::init();
	add_action("extract_standard", "extract");
	add_action("break_standard", "break");
	//add_action("paint_standard", "opaint"); *moved to the soul, for various reasons*
	add_action("lash_standard", "olash");
	add_action("remove_standard", "oremove");
}

int extract_standard(string str)
{
	mixed *item;
	object room = environment(TP);
	
	if(str != "standard" && str != "battle standard" && str != TO->short())
	{
		write("Extract what?\n");
		return 1;
	}
	
	if(!TO->query_prop(PLANTED))
	{
		write("What?\n");
		return 1;
	}
	
	if(!IS_MEMBER(TP))
	{
		write("It wouldn't make sense for you to carry around a battle standard that has nothing to do with your cause. You could probably break it though.\n");
		return 1;
	}
	
	TO->remove_prop(OBJ_M_NO_GET);
	TO->remove_prop(PLANTED);

	write("Using all your strength, you pull the battle standard out of the ground.\n");
	say("Using all " + HIS_HER(TP) + " strength, " + QCTNAME(TP) +" pulls the battle standard out of the ground.\n");
	
	TO->set_short("grisly battle standard with a bloody " + TO->query_adj() + " scalp");
	TO->move(TP);
	
	return 1;
}

int break_standard(string str)
{
	if(str != "standard" && str != "battle standard" && str != TO->short())
	{
		write("Break what?\n");
		return 1;
	}
	
	if(!TO->query_prop(PLANTED))
	{
		write("But it isn't stuck in the ground.\n");
		return 1;
	}
	
	write("You kick the battle standard over, snapping the shaft. You then make quick work of tearing the rest apart, tossing away the remains.\n");
	say(QCTNAME(TP) +" kicks the battle standard over, snapping the shaft in half. " + HE_SHE(TP) + " then makes quick work of tearing the rest apart, tossing away the remains.\n");
	
	TO->remove_object();
	
	return 1;
}

//This function was moved to the soul, mainly because of the need
//to refer to standards using numbers (i.e. first, second, etc.) to
//make painting of multiple standards in the inventory possible.
/*
int paint_standard(string str)
{
	string existing;
	
	if(!IS_MEMBER(TP))
	{
		write("What?\n");
		return 1;
	}
	
	if(!strlen(str))
	{
		write("Paint what? Gotta have a message!\n");
		return 1;
	}

	if(TO->query_prop(IS_PAINTED))
	{
		write("But it already has a message on it!\n");
		return 1;
	}
	
	if(strlen(str) > 50)
	{
		write("Come on! That's just too long to fit on it!\n");
		return 1;
	}
	
	existing = TO->query_long();
	
	write("Using blood from one of your recent kills, you paint a message on your battle standard.\n");
	say("Using blood from one of " + HIS_HER(TP) + " recent kills, " + QCTNAME(TP) +" paints something on " + HIS_HER(TP) + " battle standard.\n");
	
	TO->set_long(existing + "A message is painted in blood on the standard: " + capitalize(str) + "\n");
	TO->add_prop(IS_PAINTED, 1);
	
	return 1;
}
*/

int lash_standard(string str)
{
	if(!IS_MEMBER(TP))
	{
		write("What?\n");
		return 1;
	}
	
	if(str != "standard" && str != "battle standard")
	{
		write("Lash what to your back? A standard?\n");
		return 1;
	}

	if(TO->query_prop(IS_LASHED))
	{
		write("But it is already lashed to your back!\n");
		return 1;
	}
	
	if(TP->query_prop(HAS_LASHED))
	{
		write("But you already have a standard lashed to your back!\n");
		return 1;
	}
	
	write("You quickly lash your " + short() + " to your back, proudly displaying it for all to see.\n");
	say(QCTNAME(TP) + " quickly lashes " + HIS_HER(TP) + " " + short() + " to " + HIS_HER(TP) +" back, proudly displaying it.\n");
	
	TP->add_subloc("_display_standard", this_object());
	TP->add_prop(HAS_LASHED, 1);
	TO->add_prop(OBJ_M_NO_DROP, "It is lashed to your back! 'Oremove' it first.\n");
	TO->add_prop(OBJ_M_NO_GIVE, "It is lashed to your back! 'Oremove' it first.\n");
	TO->add_prop(IS_LASHED, 1);
	
	return 1;
}

int remove_standard()
{
	if(!IS_MEMBER(TP))
	{
		write("What?\n");
		return 1;
	}
	
	if(!TO->query_prop(IS_LASHED))
	{
		write("But it is not lashed to your back!\n");
		return 1;
	}
	
	write("You untie your " + short() + ", taking it off your back.\n");
	say(QCTNAME(TP) + " unties " + HIS_HER(TP) + " " + short() + ", taking it off " + HIS_HER(TP) +" back.\n");
	
	TP->remove_subloc("_display_standard");
	TP->remove_prop(HAS_LASHED);
	TO->remove_prop(OBJ_M_NO_DROP);
	TO->remove_prop(OBJ_M_NO_GIVE);
	TO->remove_prop(IS_LASHED);
	return 1;
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if(subloc!="_display_standard")
      return "";

    //What they see in their inventory
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
 
    //What they see when they examine themselves
    if (for_obj == me)
        return "You have a " + short() + " lashed to your back.\n";
    
    //What others see when they examine the welt-haver
    else
        return CAP(HE_SHE(me))+" has a " + short() + " lashed to " + HIS_HER(me) + " back.\n";
}
