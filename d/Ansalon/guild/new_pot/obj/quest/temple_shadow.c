/* Stralle 030708
 */

inherit "/std/shadow";

#include "/d/Ansalon/common/defs.h"
#include "../../guild.h"

#define TDIR    "/d/Ansalon/taman_busuk/neraka/temple"

string *gTargetRooms = ({
    TDIR + "/blue/achamber",
    TDIR + "/black/achamber",
    TDIR + "/green/achamber",
    TDIR + "/red/achamber",
    TDIR + "/white/achamber"
});
int gTimeStarted, gHasStarted;

/* Functions called by Terwed when you report */

public int
ts_query_has_mission() { return 1; }

public int
ts_query_mission_success()
{
    return (sizeof(gTargetRooms) == 0 ? 1 : 0);
}

public int
ts_query_mission_time()
{
    return time() - gTimeStarted;
}

public void
ts_remove_mission_shadow() { remove_shadow(); }

/* write message to the shadowed player */
void
ts_catch_msg(string msg) { query_shadow_who()->catch_msg(msg); }

public varargs int
shadow_me(mixed to_shadow)
{
    gTimeStarted = time();
    
    return ::shadow_me(to_shadow);
}

/* Functions shadowing the player */

void
enter_env(object env, object from)
{
    string n;
    
    query_shadow_who()->enter_env(env, from);

    if (env)
    {
    	n = file_name(env);
    	if (member_array(n, gTargetRooms) >= 0)
    	{
    	    gTargetRooms -= ({ n });
    	    if (!gHasStarted)
    	    {
    	    	set_alarm(2.0,0.0,&ts_catch_msg(
    	            "\nGood, you have reached the first antechamber.\n\n"));
    	    	gHasStarted = 1;
    	    }
    	    if (sizeof(gTargetRooms) == 0)
    	    {
    	    	set_alarm(2.0,0.0,&ts_catch_msg(
    	    	    "\nThis was the last antechamber, better head back to " +
    	    	    "Terwed.\n\n"));
    	    }
    	}
    }
}
