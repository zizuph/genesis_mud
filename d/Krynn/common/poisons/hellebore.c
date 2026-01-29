/*
 * Filename:        Krynn/common/poisons/hellebore.c
 * Description:     This poison belongs to the Hellebore Stinkwort
 *                  herb.
 *
 * Copyright (c) May 2003 by Daniel W. Mathiasen aka Boron
 *
 * Revision history:
 * When, Who, What:
 */

inherit "/d/Krynn/std/poison_effect";

#include "/d/Krynn/common/defs.h"
#include <poison_types.h>
#include <ss_types.h>


void
create_krynn_poison_effect()
{
    set_name("_hellebore_stinkwort");
    // Its not too dangerous, but eating it makes you feel less confident
    // as it is a stupid mistake.
    set_damage(({ POISON_HP, 2, POISON_FATIGUE, 5, POISON_STAT, SS_DIS }));
    set_time(900);
    set_interval(21);
}

