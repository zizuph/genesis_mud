/*
 * File: worm.c
 * Creator: Shadowlynx
 * Date: June/97
 *
 * Modified from /d/Shire/common/npc/worm.c
 *
 */

inherit "/d/Krynn/std/creature";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_creature()
{
    set_name("worm");
    set_pname("worms");
    set_short("big fat ugly worm");
    set_long("A big fat ugly worm wiggles part way out" +
      " of a small hole in the juicy red apple.\n");
    set_adj(({"big","fat","ugly"}));
    set_race_name("worm");
    set_gender(random(2));
}
