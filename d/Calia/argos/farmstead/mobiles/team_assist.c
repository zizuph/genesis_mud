/* /d/Calia/argos/farmstead/mobiles/team_assist.c
**   Code to make the brigands assist each other
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   5/2/20    Brine      Created
**
*/

#pragma strict_types

#include "defs.h"

void
notify_attacked(object friend, object attacker)
{
    if(!objectp(query_attack()))
    {
        command("assist " + OB_NAME(friend));
    }
}

void
react_attack(object attacker)
{
    if (!CAN_SEE(TO, attacker) || !CAN_SEE_IN_ROOM(TO))
    {
        command("say Who goes there? Show yourself!");
    } else {
        command(
            "say to " + OB_NAME(attacker) + " You just made your last "
            + "mistake, " + attacker->query_race_name() + "!"
        );
    }
    query_team_others()->notify_attacked(TO, attacker);
}

void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    set_alarm(0.5, 0.0, &react_attack(attacker));
}
