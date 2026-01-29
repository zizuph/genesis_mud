/*
 * /d/Gondor/common/dwarf_guild/obj/whetstone.c
 *
 * It is a whetstone or grindstone. You can buy it from Borin, the
 * smith and use it to sharpen an axe or other weapon type if you are
 * skilled enough.
 *
 * /Mercade, 30 July 1994
 *
 * Revision history:
 *   Adapted for use by Morrigan for Mercenary Guild, 11/01
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/dwarf_guild/obj/whetstone";

#include "/d/Gondor/common/dwarf_guild/dwarf.h"
#include "/d/Gondor/defs.h"

#define DWARF_STONE_ID     (DWARVEN_RACE_GUILD_PREFIX + "whetstone")
#define STONE_ID     ("mercenary whetstone")
#define CHECK_WEAPON "check_weapon"
#define STD_WEAPON   "/std/weapon"
#define WEAPON_SKILL (30 + random(20))

void
create_object()
{
    ::create_object();
    remove_name(DWARF_STONE_ID);
    add_name(STONE_ID);
    add_adj("mercenary");
}
