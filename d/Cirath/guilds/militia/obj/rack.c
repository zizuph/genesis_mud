/*
* Created by: Luther
* Date: Dec 2001
*
* File: /d/Cirath/guilds/militia/obj/rack.c
* Comments: Militia starting rack.
*/

inherit "/std/object";
#include "../defs.h"
#define CO(x)    clone_object(x)

void
create_object()
{
    	if (!IS_CLONE) return;
    	set_name("rack");
    	add_name("rack");
    	add_adj("wooden");
    	add_prop(OBJ_I_NO_GET, "The rack is bolted to the ground.\n");
    	add_prop(OBJ_M_NO_STEAL, "The posted Militia would kill you.\n");
    	set_long("This is the starting rack for the militia, militia members may "
    		+ "'help rack' for additional help.\n");
    	add_cmd_item("rack","help","Rack options.\n" +
    	"To get a starter shield 	- 'request shield'\n" +
    	"To get a one handed polearm	- 'request pole1'\n" +
    	"To get a two handed polearm	- 'request pole2'\n");   	
    	    	
}

void
init()
{
    ::init();
    add_action("request_item", "request");
}

int
request_item(string str)
{	

    setuid();
   seteuid(getuid());
	if ((!IS_TYR_MILITIA(TP)) && (!TP->query_wiz_level()))	
	{
		NF("Only Militia may request equipment!\n");
		return 0;
	}
	
	if (str == "shield")
     	{
     	   	CO(MILITIA_ARM + "shield")->move(TP, 1);
     	   	TP->catch_msg("You receive a starter shield.\n");
     	   	say(QCTNAME(this_player()) + " gets a shield from the rack.\n");
           	return 1;    
	}
   	if (str == "pole1")
     	{
     	   	CO(MILITIA_WEP + "pole1")->move(TP, 1);
     	   	TP->catch_msg("You receive a starter polearm.\n");
     	   	say(QCTNAME(this_player()) + " gets a weapon from the rack.\n");
           	return 1;    
	}
   	if (str == "pole2")
     	{
     	   	CO(MILITIA_WEP + "pole2")->move(TP, 1);
     	   	TP->catch_msg("You receive a starter polearm.\n");
     	   	say(QCTNAME(this_player()) + " gets a weapon from the rack.\n");
           	return 1;    
	}
	
	notify_fail("Request what?\n");
    	return 0;
}
