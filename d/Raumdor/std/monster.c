/* Raumdor standard monster */
#pragma strict_types
#pragma save_binary
#include "defs.h"
inherit "/std/monster";

public void
create_monster()
{
    add_prop(NPC_M_NO_ACCEPT_GIVE, "@@mobile_deny_objects");
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
    if (calling_function() != "combat_init" && objectp(environment()))
		FILTER_LIVE(all_inventory(environment()) - 
			({this_object()}))->notify_ob_attacked_me(this_object(), attacker);
}

void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
	return;

    if (member_array(friend, (object*)query_team_others()) >= 0)
	set_alarm(1.0, 0.0, "help_friend", attacker);
}

void
seen_emote(string text)
{
    if (!text || !strlen(text))
        throw("text required");

    if (extract(text, 0, 0) != "'")
        text = " " + text;
    TELL_SEEN(TO, QCTNAME(TO) + text + "\n");
}

public void
test_special()
{
    int i;
    object enemy = query_attack();
    if (!enemy)
        return;
    for (i = 0; i < 100; i++)
    {
        if (special_attack(enemy))
            break;
    }
}
