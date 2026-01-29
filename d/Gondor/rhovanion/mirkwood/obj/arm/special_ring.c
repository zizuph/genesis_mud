/*
 * Spider Treasure - Sword
 * Varian - October 2015
 *
 * This ring is a base for some special effects
 *
 * For some of these special effects, it would be nice to see a mana
 * (and maybe health?) drain to use the special effect. So, for a ring
 * of invisibility, you wear the ring and it drains mana at a set rate,
 * once mana is 0, either the player is forced to remove the ring or
 * else it begins to drain health instead. Depends on how this is seen
 * in terms of balance and/or code difficulty.
 *
 * There may possibly need to be an intial drain for putting on the ring
 * as some of these effects could be abused otherwise. Perhaps a stronger
 * drain for putting the ring back on within X seconds after removing it?
 * Simply having a faster drain for stronger powers might not always be enough.
 *
 * Special Effects:
 * - Invisibility
 * - Speed/Haste
 * - Panic (on everyone in the room not teamed with bearer?)
 * - Freedom (no paralyze or stun)
 * - Magic Prevention (either for player only, or for room player is in)
 * - Protection from poison (poisons wont affect)
 * - See in darkness
 * - Courage (always secure, no panic)
 * - Light
 * - Constitution (no fatigue)
 * - Armour (Large AC boost)
 * - Health (healing HP)
 * - Lower resistance (magic, fire etc..) of race type (orc, troll etc...) in room
 * - Panic race type (orc, troll etc...) in room
 * - Slow race type (orc, troll etc...) in room
 * - Peace (cannot be attacked, stops combat for player)
 * - Wealth (gives 100 trading skill/advantage when selling?)
 */

#include "defs.h";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/armour";
inherit "/lib/keep";


create_armour()
{
    set_name("ring");
    add_adj("gold");
    set_short("gold ring");
    set_long("This is a ring to be described\n");

   set_ac(1);
   set_at(A_R_FINGER);

   add_prop(OBJ_I_WEIGHT, 10);
   add_prop(OBJ_I_VOLUME, 10);
   set_keep();
}

