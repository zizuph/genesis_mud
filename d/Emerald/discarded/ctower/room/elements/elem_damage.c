#include "../../ctower.h"

static object *who = ({ });

void damage();

void register(object ob)
{
    if (member_array(ob, who) >= 0)
    { 
      return;
    }
  
    if (!sizeof(who))
    {
      set_alarm(itof(5 + random(10)), 0.0, damage);
    }
  
    who += ({ ob });
}

void damage()
{
    int i;
    object env;
    object *newwho = ({ });
    string *inherits, str;
  
    for (i = 0; i < sizeof(who); i++)
    {
    	if (!who[i])
    	{
	    continue;
    	}
    
    	if (!(env = environment(who[i])))
    	{
	    continue;
    	}
    	 
    	if (!present("elem_talis_tower", who[i]))
    	{  
	    inherits = inherit_list(env);
      
	    if (member_array(AIRSTD, inherits) >= 0)
	    {
	        str = "slammed against the wall by the fierce winds";
	    }
	    else if (member_array(EARTHSTD, inherits) >= 0)
	    {
	        str = "smashed by a stalactite";
	    }
	    else if (member_array(FIRESTD, inherits) >= 0)
	    {
	        str = "burned by the flames";
	    }
	    else if (member_array(WATERSTD, inherits) >= 0)
	    {
	        str = "drowning";
	    }
	    else
	    {
	        continue;
	    }
	    
	    who[i]->reduce_hit_point(who[i]->query_max_hp() / 10);
      
	    if (strlen(str))
	    {
	    	who[i]->catch_tell("You are " + str + "!\n");
	    	tell_room(env, QCTNAME(who[i]) + " is " + str + "!\n", who[i]);
	    }
      
	    if (who[i]->query_hp() <= 0)
	    {
	    	who[i]->catch_msg("You die.\n");
	    	who[i]->do_die(this_object());
	    }
    	}
    
    	newwho += ({ who[i] });
    }
  
    if (sizeof(who = newwho))
    {
        set_alarm(itof(5 + random(10)), 0.0, damage);
    }
}
