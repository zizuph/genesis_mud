/*
 * /d/Gondor/guilds/rangers/obj/poison.c
 *
 * Used for Apprentice Ranger tasks
 */
inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>

void 
create_poison_effect()
{
    set_name("Orc poison");
    set_interval(20);
    set_time(360);
    set_damage(({ POISON_HP, 300 }));
    set_strength(100);
    set_poison_type("orc-poison");
}

int
query_task_poison()
{
    return 1;
}
