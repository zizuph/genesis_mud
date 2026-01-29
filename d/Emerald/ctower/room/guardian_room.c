int level;
object *may_pass = ({ });

#include "../ctower.h"
#include <macros.h>
 
int
add_guardian()
{
    object guardian;
  
    if (!present("tower_guardian"))
    {
    	if (guardian = clone_object(CTOWER_NPC + "guard" + level))
     	{
	    return !guardian->move(this_object(), 1);
    	}
    
    	return 0;
    }
   
    return 1;
}

int
exit_block()
{
    if (this_player()->query_wiz_level() || 
        (member_array(this_player(), may_pass) >= 0))
    {
        return 0;
    }
  
    if (!present("tower_guardian"))
    {
    	if (!add_guardian())
    	{
	  return 0;
    	}
    
    	write("A guardian arrives and takes post at the exit just " +
	    "before you get there.\n");
    }
  
    write("The guardian blocks your access!\n");
    say(QCTNAME(this_player()) + " tried to go north, but was denied.\n");
    return 1;
}

void
register(object who)
{
    if (member_array(who, may_pass) < 0)
    {
        may_pass += ({ who });
    }
}
