inherit "/std/poison_effect";

#include <ss_types.h>
#include <poison_types.h>
#include "steed.h"

void
create_poison_effect()
{
    ::create_poison_effect();
    set_interval(CHECK_TIME / 10);
    set_time(CHECK_TIME * 3 - 10);
    set_damage( ({ POISON_FATIGUE, 100,
		   POISON_STAT, SS_STR,
		   POISON_STAT, SS_CON }) );
    set_poison_type("hunger");
    set_no_show();
    set_name(POISON_ID);
}
