/*
* Created by: Luther
* Date: SEPT 2001
*
* File: /d/Cirath/ridge/npc/v_corpse.c
* Comments: Corpse in v20.c
*/

inherit "/std/object";
#include "../defs.h"

void
create_object()
{
    	if (!IS_CLONE) return;
    	set_name("cross");
    	add_name("cross");
    	add_adj("wooden");
    	add_prop(OBJ_I_NO_GET, "The cross is stuck into the ground.\n");
    	add_prop(OBJ_M_NO_STEAL, "And steal the planet aswell?\n");
    	set_long("The cross has been driven into the ground with great force. It is "
    		+"almost 30 feet high and there looks like something up there.\n");
    	   	
    	    	
}

void
init()
{
    ::init();
    add_action("climb_cross", "climb");
}

int
climb_cross(string str)
{
	
   	notify_fail("Climb what?\n");
    	if(str!="cross")
        	return 0;
       	
  	 if (str == "cross" && (TP->query_skill(SS_CLIMB) > 29))
     	{
        TP->catch_msg("You climb the cross.\n");
        TP->move_living("climbing up the cross", RIDGE_VALLEY + "v_cross.c",1);
        TP->add_fatigue(-50);       
        return 1;
        }
        else
      	{
        TP->catch_msg("You lack the skill to climb the cross.\n");	
        return 1;
	}   

    return 0;
}