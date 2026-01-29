/*
 * Created By : Ibun 070524
 */
#pragma strict_types
inherit "/std/object";

#include <stdproperties.h>     /* Where the properties are defined. */
#include <ss_types.h>          /* Where the skill defines are.      */

#define DBG(msg) 
//    find_player("lucius")->catch_tell("Wizinfo: "+ msg +"\n");

 
public void
create_object()
{
    set_no_show();
    set_name("_ave_distract_object");
    set_short("distraction object");

    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_S_WIZINFO,
    "This object means the player is distracted for a short while. " +
        "The object will remove the distraction ie raise awareness " +
        "and selfdestruct.\n");
}

private void
add_awareness(int val, object victim)
{
    DBG("Re-adding awareness.");
    DBG("Victim: " + victim->query_name())
    DBG("Environment: " + environment()->query_name())
    victim->set_skill_extra(SS_AWARENESS,
	victim->query_skill_extra(SS_AWARENESS) + val);

    remove_object();
}

public int
time_left(float time, int val, object victim)
{
    DBG("time_left called");
    set_alarm(time, 0.0, &add_awareness(val, victim));
}
