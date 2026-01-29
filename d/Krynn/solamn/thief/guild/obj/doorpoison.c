/* the poison in the door locks into the thief guild, by Aridor, 08/29/94 */

inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>

void
create_poison_effect()
{
    set_interval(10);
    set_time(500);
    set_damage(({ POISON_FATIGUE, 100, POISON_HP, 150, POISON_STAT, SS_DEX }));
    set_strength(60);
}
