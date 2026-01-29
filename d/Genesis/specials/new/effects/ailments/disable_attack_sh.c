/*
 * disable_attack_sh
 *
 * Created by Zizuph, Dec 2021
 *
 * This ability will allow specific attack IDs from white hits to be
 * blocked.  It works like an evade, but in reverse - preventing a
 * fraction of white hits from being initiated at the source.
 *
 * The option 
 * 
 *
 */

#pragma strict_types
#pragma save_binary
#pragma no_inherit

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>

inherit DISABLE_ATTACK_NPC_SH;

public mixed
wield(object weapon)
{
    setuid();
    seteuid(getuid());
       
    mixed result = shadow_who->wield(weapon);
    if (intp(result) && result == 1 && 
        !weapon->has_disable_attack_weapon_shadow())
    {
        object weapon_shadow = clone_object(DISABLE_ATTACK_WEAPON_SH);
        weapon_shadow->set_attack_shadow(this_object());
        weapon_shadow->shadow_me(weapon);
        disable_attack_weapon_shadows[weapon] = weapon_shadow;
    }
   return result;
}

public void
unwield(object weapon)
{
    shadow_who->unwield(weapon);
    object weapon_shadow = disable_attack_weapon_shadows[weapon];
    if (objectp(weapon_shadow))
    {
        weapon_shadow->remove_shadow();
        m_delkey(disable_attack_weapon_shadows, weapon);
    }
}
