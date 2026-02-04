/* effect from riding Hilary's broom */
inherit "/std/poison_effect";
#include <poison_types.h>

void
create_poison_effect()
{

    set_interval(30);  /* every 30 seconds */
    set_time(600);     /* for 10 minutes */
    /* This heals fatigue instead of taking it away */
    set_damage( ({ POISON_FATIGUE, -25 }) );
    set_strength(80);
    set_poison_type("broom");
    set_no_cleanse();
    set_silent(2);
}
