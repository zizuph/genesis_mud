#include <macros.h>

void
map_attack(object attacker, object attacked)
{
    if (living(attacker) && attacker->query_attack() != attacked)
    {
	attacked->catch_msg(QCTNAME(attacker) + " attacks you!\n");
	say(QCTNAME(attacker) + " attacks " + QCTNAME(attacked) + "!\n");
	attacker->attack_object(attacked);
    }
} 
