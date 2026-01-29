/*
 * A zombie, found in the crypts
 *
 * 950421 by Rastlin
 *
 * 2004-12-11 - Cotillion
 * - Rewritten to use the human zombie as a template
 */

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h";
#include "/d/Krynn/pax/local.h";

inherit "/d/Krynn/pax/monster/zombie_human";

void
create_zombie()
{
    set_race_name("elf");
    set_adj(({"hideous", "undead"}));
    set_stats(({ 110, 110, 110, 100, 100, 140 }), 20);

    set_skill(SS_DEFENCE,      40);
    set_skill(SS_PARRY,        60);
    set_skill(SS_WEP_SWORD,    80);

    equip(({ PWEAPON + "longsword",
             PARMOUR + "leather_arm" }));
}
