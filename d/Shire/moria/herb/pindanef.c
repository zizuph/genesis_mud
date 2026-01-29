#include <ss_types.h>
#include "defs.h"

inherit "/d/Shire/common/lib/effect";

create_effect()
{
    set_name("_pindan_effect_");
    set_time((2+random(10))*60);
}

void
do_start_effect(object who)
{
    who->catch_msg("Ah! Your brain clears up!\n");
    ADD_SKILL(who, SS_LOC_SENSE, 10);
}

void
do_stop_effect(object who)
{
    ADD_SKILL(who, SS_LOC_SENSE, -10);
    who->catch_msg("Your mind fogs up again.\n");
}
