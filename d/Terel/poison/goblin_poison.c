#pragma save_binary
#pragma strict_types

inherit "/std/poison_effect";

#include <poison_types.h>
#include <stdproperties.h>

public void
create_poison_effect()
{
    set_name("_terel_goblin_poison");
    set_interval(30);
    set_time(600);
    set_damage(({POISON_HP, 100, POISON_FATIGUE, 75}));
    set_strength(75);
    set_silent(0);
    set_poison_type("hp");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);    
}

