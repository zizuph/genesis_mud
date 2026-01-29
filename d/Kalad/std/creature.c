/* creature.c
       Kalad standard creature.

       Fysix, Nov 1997              Serpine, July 1998
*/
#pragma strict_types
#pragma save_binary

inherit "/std/creature";
inherit "/d/Kalad/lib/speak";
inherit "/d/Kalad/lib/prestige";

#include <stdproperties.h>
#include <filter_funs.h>

/* Function name: create_kalad_creature
 * Description:   Creation function of the standard Kalad creature.
 */
public void
create_kalad_creature()
{
}

// Not nomask for backwards compatibility
public void
create_creature()
{
    set_exp_factor(50);
    add_prop(NPC_M_NO_ACCEPT_GIVE,"@@mobile_deny_objects");
    create_kalad_creature();
}

void
init_living()
{
    ::init_living();
    init_speak();
}

void add_speak(string s)
{
    set_speak(s);
}

/* Function name: attacked_by
 * Description:   Masked this function to let everybody in
 *                the environment know that I am attacked.
 *                Is used for letting guards assist me.
 * Arguments:     object attacker
 */
public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);

    // If I attacked myself, don't call notify_ob_attacked_me
    if (calling_function() != "combat_init")
	FILTER_LIVE(all_inventory(environment()) - ({this_object()}))->
	notify_ob_attacked_me(this_object(), attacker);
}


void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
	return;

    if (member_array(friend, (object*)query_team_others()) >= 0)
	set_alarm(1.0, 0.0, "help_friend", attacker);
}
