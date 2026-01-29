/* this poison object is part of the special attack of the Talisman        */
/* Priestess. Since she is part of a quest, this is designed to discourage */
/* people from attacking her.                                              */
inherit "/std/poison_effect";
#include <poison_types.h>
#include "defs.h"
 
create_poison_effect() {
    set_name(({"poison"}));
    set_interval(30);
    set_time(2000);
    set_damage(({POISON_HP,175}));
    set_strength(60);
    set_poison_type("standard");
}
