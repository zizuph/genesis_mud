/* Ashlar, 30 Oct 97
        The shadow handling the Kalman task
*/

inherit "/std/shadow";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "../../guild.h"

#define KDIR    "/d/Ansalon/kalaman/city/"

string *target_rooms = ({
    KDIR + "r21",
    KDIR + "b1",
    KDIR + "b2",
    KDIR + "b3",
    KDIR + "b4",
    KDIR + "b5",
    KDIR + "b6",
});

int has_started = 0;
int kill_counter = 0;

/* Functions called by Terwed when you report */

public int
ks_query_has_mission() { return 1; }

public int
ks_query_mission_success()
{
    return (sizeof(target_rooms) == 0 ? 1 : 0);
}

public int
ks_query_kills()
{
    return kill_counter;
}

public void
ks_remove_mission_shadow() { remove_shadow(); }

/* write message to the shadowed player */
void
ks_catch_msg(string msg) { shadow_who->catch_msg(msg); }

/* Functions shadowing the player */

void
enter_env(object env, object from)
{
    string n;
    
    shadow_who->enter_env(env, from);

    if (env)
    {
    	n = file_name(env);
    	if (member_array(n, target_rooms) >= 0)
    	{
    	    target_rooms -= ({ n });
    	    if (!has_started)
    	    {
    	    	set_alarm(2.0,0.0,&ks_catch_msg(
    	            "\nGood, you have now started " +
    	    	    "scouting the defences of Kalaman.\n\n"));
    	    	has_started = 1;
    	    }
    	    if (sizeof(target_rooms) == 0)
    	    {
    	    	set_alarm(2.0,0.0,&ks_catch_msg(
    	    	    "\nYou have all the information Terwed required. " +
    	    	    "You can return to the Temple now.\n\n"));
    	    }
    	}
    }
}

public void
notify_you_killed_me(object victim)
{
    string garbage;
    if (sscanf(file_name(victim), "/d/Ansalon/kalaman/%s",garbage) >= 1)
        kill_counter++;

    shadow_who->notify_you_killed_me(victim);
}
