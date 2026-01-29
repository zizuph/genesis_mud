/* An insectoid for the Manor's Garden.
 * This is a crossbreed created by magic by
 * the evil wizard that lives in the manor.
 * Coded by Marisol (9/23/97)
 * Copyright (c) Marisol Ramos 1997 */

#pragma strict_types

inherit "/d/Earthsea/std/monster";

#include "defs.h"
#include <ss_types.h> /* Contains skills */
#include <const.h>

void
create_earthsea_monster()
{
    set_name("insectoid");
    set_short("ugly insectoid");
    set_adj("ugly");
    set_race_name("insectoids");
    add_name("g_insectoid");
    set_long("This misfit of nature is half-human and "+
        "half-insect. He looks like the result of a "+
        "wizard spell that backfired. Its facet eyes "+
        "shine with a glint of evil.\n");

    set_act_time(10);
    add_act("emote grits his jaws with a horrible sound.");
    add_act("emotes cleans his face with his hands like a coakroach.");
    add_act("emote swings his machete in the air menacingly.");

    set_alignment(-50);

    set_gender(G_MALE);

    set_skill(SS_WEP_KNIFE, 5);
    set_skill(SS_PARRY, 5);
    set_skill(SS_DEFENCE, 5);
    set_skill(SS_BLIND_COMBAT, 10);
    set_skill(SS_AWARENESS, 100);    

              /* str, dex, con, int, wis, dis */
    set_stats(({  6,  6,  6,  15,  15,  9 }));

    add_equipment( ({
        MANOR_WEP_AND_ARM + "machete",
        MANOR_WEP_AND_ARM + "tunic" }) );
}
