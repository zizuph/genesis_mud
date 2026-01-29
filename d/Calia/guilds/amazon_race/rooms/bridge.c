/*
 *    bridge.c  
 *
 * A rope bridge connecting the Amazon racial guild
 * with the main tree.
 *
 * Baldacin@Genesis, Nov 2003   
 *
 */

inherit "/std/room.c";
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

int
block_exit()
{
    object guard = present("entrance_guard", TO);
    object token = present("amazon_race_token", TP);
           
    if (objectp(guard))
    {
        if (IS_MEMBER(TP) || objectp(token))
	{
	    if (IS_MEMBER(TP))
	    {
	        guard->command("bow "+TP->query_name());
	        guard->command("say Welcome home, "+TP->query_name());
	    }
	    else
	    {
	    	say(QCTNAME(TP)+ " displays a token to " + QTNAME(guard) +
	          ". And with a quick nod of her head she acknowledges it "+
	          "and let "+HIM(TP)+" pass.\n");
	    	TP->catch_msg("You display your token to "+QTNAME(guard)+
	    	  ". And with a quick nod of her head she acknowledges it and "+
	    	  "let you pass.\n");
	    }
	    return 0; 
	}

    if (CAN_SEE(TO, TP)) {
     	guard->command("glare "+TP->query_name());
     	guard->command("say to "+TP->query_name()+" Don't push it! "+
     	  "I'll throw you over the bridge.");
    }
    else
    {
     	guard->command("say Don't push it! "+
     	  "I'll throw you over the bridge.");
    }
   	say(QCTNAME(guard)+ " prevents " + QTNAME(TP) +
	" from leaving northwest.\n");
	TP->catch_msg(QCTNAME(guard)+ " prevents you "+
	"from leaving northwest.\n");
	return 1;
    }		  
   return 0; 
}

void
create_room()
{
    set_short("High up on a rope bridge");
    set_long("You are swaying on a rope bridge high up in the "+
      "air. The bridge itself seems to be of good quality and "+
      "sturdy. But with the wind blowing, forcing the bridge to sway, "+
      "it is pretty hard to walk on it. Looking down you see the trunks "+
      "and a thick fog, but no ground. You should probably get over "+
      "to the other side as quick as possible.\n");
        
    if (!present("entrance_guard", TO))
        clone_object(NPC + "entrance_guard")->move(TO, 1);
        
    add_exit(ROOMS + "tree3","northwest", &block_exit());
    add_exit(ROOMS + "platform","southeast");
}
