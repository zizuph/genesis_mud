/* Ashlar, 9 Jun 97 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"
#include "/d/Ansalon/common/defs.h"

#define NGUARD NNPC + "cityguard"

inherit NGUARD;

void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    
    if (E(TO))
        E(TO)->sound_alarm();
    TO->command("shout Attack! Enemies at the gate! Reinforcements this way!");
}

void
attack_object(object target)
{
    ::attack_object(target);

    if (E(TO))
        E(TO)->sound_alarm();
    TO->command("shout Attack! Enemies at the gate! Reinforcements this way!");
}
