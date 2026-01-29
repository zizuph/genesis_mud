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
    set_race_name("dwarf");
    set_adj(({"short", "undead"}));
    set_stats(({ 150, 70, 100, 70, 70, 140 }), 20);

    set_skill(SS_DEFENCE,      50);
    set_skill(SS_PARRY,        30);
    set_skill(SS_WEP_SWORD,    90);
    set_skill(SS_WEP_AXE,      90);
    
    equip(({ PWEAPON + "battleaxe",
             PARMOUR + "leather_arm" }));
}
