#include "defs.h"

#include <poison_types.h>
inherit "/std/poison_effect";

public void
create_poison_effect()
{
    set_interval(20);
    set_time(3600);
    set_damage( ({ POISON_FATIGUE, 100, POISON_HP, 50 }) );
    set_strength(20);
    set_poison_type("magic");
}

public int
may_not_recover()
{
    return 1;
}
