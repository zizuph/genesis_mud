/* Modified by Maniac 14.12.94  Check attack was successful before msg */

#include <macros.h>

void
map_attack(object attacker, object attacked)
{
    if (living(attacker) && attacker->query_attack() != attacked)
    {
        attacked->attacked_by(attacker);
	attacker->attack_object(attacked);
        if (attacker->query_attack() == attacked) {
	  attacked->catch_msg(QCTNAME(attacker) + " attacks you!\n");
	  say(QCTNAME(attacker) + " attacks " + QCTNAME(attacked) + "!\n");
        }
    }
} 

