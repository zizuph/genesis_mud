/*
* Created by: Luther
* Date: SEPT 2001
*
* File: /d/Cirath/ridge/npc/v_corpse.c
* Comments: Corpse in v20.c
*/

inherit "/std/object";
#include "../defs.h"
#include "/d/Cirath/quest_handler/quest_handler.h"
#define ROPE_OBJECT "rope_object"

object ccorpse;

void
create_object()
{
    	if (!IS_CLONE) return;
    	set_name("body");
    	add_name("qcorpse");
    	add_adj("hanging");
    	add_adj("dead");
    	add_prop(OBJ_I_NO_GET, "The body is tied to the cross.\n");
    	add_prop(OBJ_M_NO_STEAL, "The body is tied to the cross.\n");
    	set_long("The body appears to be tied up here with rope. It "
        	+"looks possible to release the body from this place.\n");
    		
        add_item("rope", "The rope is holding the corpse up. Maybe you should "
        	+"remove it so the corpse can be at rest.\n");		
        
        add_cmd_item("rope", "cut", "Are you crazy? Rope is extremely rare in Athas.\n");		
    	add_cmd_item("body", "release", "The rope is holding it there.\n");		
    	    	
}

void
init()
{
    ::init();
    add_action("rope_untie", "untie");
}

int
rope_untie(string str)
{
	object obj; 
   	notify_fail("Untie what?\n");
    	if(str!="rope")
        	return 0;
       	
  	if (str == "rope")
     	{
        TP->catch_msg("You untie the rope and the corpse falls to the ground. The next thing you "
        	+"know the body is sinking into the sand.\n");
        tell_room("/d/Cirath/ridge/valley/v_cross.c", "The hanging body falls to the ground when " + QCTNAME(TP) + 
        	" removes the rope.\n", TP);
        tell_room("/d/Cirath/ridge/valley/v20.c", "The body from the cross falls down. "
        	+"Shortly afterwards the corpse sinks into the sand.\n", TP);        
                   	
    	if (!QH_QUERY_QUEST_COMPLETED(TP, "valley_body_quest"))
    	{
    		TP->catch_msg("You fell a little more experienced.\n");
    		QH_QUEST_COMPLETED(TP,"valley_body_quest");
    	}          	
    	
    	if (!TP->query_prop(ROPE_OBJECT))
    	{
    		TP->catch_msg("You also manage to hold onto the rope.\n");
    		clone_object(RIDGE_OBJ +"rope")->move(TP);
    		TP->add_prop(ROPE_OBJECT, 1);
    	}
    	else
    	{
    		TP->catch_msg("You failed to hold onto the rope.\n");
    		TP->catch_msg("The rope falls with the corpse.\n");
    	}
    	
    	if(ccorpse = present("qcorpse", environment(TP)))
    	{
        	ccorpse -> remove_object();
    	}        	
        
        return 1;

	}
        
    return 0;
}

