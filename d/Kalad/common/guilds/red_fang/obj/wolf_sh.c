#pragma save_binary
#pragma strict_types
inherit "/std/shadow";
#include "/d/Kalad/defs.h"
#include <tasks.h>

object wolf;

void
set_wolf(object ob)
{
    wolf = ob;
}

object
query_wolf()
{
    return wolf;
}

string
query_m_out()
{
    return "rides";
}

string
query_m_in()
{
    return "rides in on a "+wolf->short();
}


void
remove_wolf_shadow()
{
    remove_shadow();
}

public void
add_fatigue(int f)
{
    wolf->add_fatigue(f);
}

public varargs int
move_living(string how, mixed to_dest, int no_fol, int no_gla)
{
    int in,tmp,tired;

    if(objectp(to_dest))
	in = member_array(file_name(to_dest),E(shadow_who)->query_exit());
    else
	in = member_array(to_dest,E(shadow_who)->query_exit());

    if(in >= 0) // Do fatigue check to see if we can move on. 
	// Only if there is fatigue to be added, though
    {
	if((tmp = shadow_who->query_encumberance_weight()) > 20)
	{
	    tired = E(shadow_who)->query_tired_exit(in+2);
	    tired = ((tmp > 80) ? (tired * 2) : tired);
	    if (wolf->query_fatigue() < tired)
	    {
		tell_object(shadow_who,"Your wolf is too tired to move.\n");
		return 7;
	    }
	}
    }
    // Check if they fall off
    if(shadow_who->resolve_task(TASK_SIMPLE,({TS_DEX,SS_WOLF_RIDING})) <=0)
    {
	tell_object(shadow_who,"Oh no, you fell off the wolf!\n");
	tell_room(E(shadow_who),QCTNAME(shadow_who)+" fell off "+
	  HIS(shadow_who)+" wolf!\n",shadow_who);
	wolf->dismount(shadow_who);
	wolf->move_living("runs off.",to_dest);
	return 7;
    }        
    in = wolf->move_living("M",to_dest,1,1);
    if (in == 0)
    {
	if (in = shadow_who->move_living(how,to_dest,no_fol,no_gla))
	{
	    wolf->move(environment(shadow_who));
	}
    }
    return in;
}
