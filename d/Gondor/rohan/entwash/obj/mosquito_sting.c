/*
 * /d/Gondor/rohan/entwash/obj/mosquito_sting.c
 *
 * Modified for mosquitoes in the Entwash by Gorboth.
 */

inherit "/d/Gondor/common/poison/mosquito_sting.c";

#include <poison_types.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

void
create_poison_effect()
{
    ::create_poison_effect();

    set_damage( ({
        POISON_FATIGUE, 3,
        POISON_HP, 3 }) );
}

