#include "../guild.h"

#include <stdproperties.h>
#include <formulas.h>

/*
 * Function name: can_attack_with_occ_special
 * Description:   See if we are allowed to attack someone
 * Arguments:     object target - the thing we want to attack
 *                string attack - a name for the attack we want to use
 * Returns:       A string describing why we cannot attack or 0 if
 *                we can attack
 */
mixed
can_attack_with_occ_special(object target, string attack)
{
    mixed why;
    object who = query_shadow_who();

    if (!target || !living(target) || !present(target, environment(who)))
    {
        return attack + " whom?\n";
    }
 
    if (who->query_prop(LIVE_I_ATTACK_DELAY) ||
        who->query_prop(LIVE_I_STUNNED))
    {
        return "You are too stunned to " + attack + ".\n";
    }
 
    if (stringp(why = target->query_prop(OBJ_M_NO_ATTACK)) ||
        stringp(why = environment(target)->query_prop(ROOM_M_NO_ATTACK)))
    {
        return why;
    }
    else if (why)
    {
        return "You sense a force protecting " + 
            target->query_the_name(who) + ".\n";
    }

    if ((!who->query_npc()) && (who->query_met(target)) &&
        !(who == target->query_attack()) &&
        (who->query_prop(LIVE_O_LAST_KILL) != target))
    {
        who->add_prop(LIVE_O_LAST_KILL, target);
        return "Attack " + target->query_the_name(who) + 
            "?!? Please confirm by trying again.\n";
    }
 
    if (!F_DARE_ATTACK(who, target))
    {
        return "You don't dare attack.\n";
    }

    return 0;
}
