/*
	*Field west of the Anduin, near foothills of the Misty Mountains
	*Altrus, June 2005
*/
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/greymount/defs.h"

inherit FOOT_BASE;
inherit FIELD_BASE;

#define PATH_PROP "_found_path_to_backdoor"

void create_field_room()
{
	set_vbfc_extra(field_desc2);
	
	add_misty_near();
	add_mirk_far();
	add_anduin_far();
	
	add_exit(FOOT_DIR + "fd12", "east");
	add_exit(FOOT_DIR + "fd11", "south");
	
	add_item(({"foothills", "hills"}), "The tumbled hills at the foot of the Misty Mountains rise just to the west here. They are rugged hills, full of gullies and covered in wild grasses.\n");
	add_item("gullies", "@@exa_gullies");
	add_item("path", "@@exa_path");
	
	reset_shire_room();
}

void reset_shire_room()
{
}

void init()
{   
	::init();
	add_action("follow_path", "follow");
}

string exa_gullies()
{
	if(TP->query_skill(SS_AWARENESS)>25 && TP->query_stat(SS_INT)>=80)
	{   
		TP->add_prop(PATH_PROP, 1);
		TP->catch_msg("Some of them are deep, others mere shallow cuts in the hills, but they cover the foothills, making for a treacherous landscape even at this low level. One of the gullies comes to an end very near this spot. There appears to be a path coming out of it.\n");
		return "";
	}
	else
	{
		TP->catch_msg("Some of them are deep, others mere shallow cuts in the hills, but they cover the foothills, making for a treacherous landscape even at this low level.\n");
		return "";
	}
}

string exa_path()
{
	if(TP->query_prop(PATH_PROP))
	{   
		TP->catch_msg("You could probably follow the path quite easily.\n");
		return "";
	}
	else
	{
		TP->catch_msg("You find no path.\n");
		return "";
	}
}

int follow_path(string str)
{
	if(str == "path")
	{
		if(TP->query_prop(PATH_PROP))
		{    
			TP->catch_msg("You follow a path up the gully a ways.\n");
			say(QCTNAME(TP) + " follows a path up into one of the gullies.\n");
			tell_room(DOOR_DIR + "hill1", QCTNAME(TP) + " arrives, trudging up through the gully.\n");
			TP->move_living("M", DOOR_DIR +"hill1",1);
                       return 1;
		}
		
		else
		{
			TP->catch_msg("You don't see a " + str + " to follow.\n");
			return 1;
		}
	}
	
	else
	{
		TP->catch_msg("Follow what?\n");
		return 1;
	}
	return 1;
}
