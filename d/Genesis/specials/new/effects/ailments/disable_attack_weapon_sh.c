/*
 * disable_attack_weapon_sh
 *
 * Created by Zizuph, Dec 2021
 *
 * This ability will allow specific attack IDs from white hits to be
 * blocked.  It works like an evade, but in reverse - preventing a
 * fraction of white hits from being initiated at the source.
 *
 */

#pragma strict_types
#pragma save_binary
#pragma no_inherit

inherit "/std/shadow";

public object attack_shadow;

public int has_disable_attack_weapon_shadow()
{
    return 1;
}

public void set_attack_shadow(object shadow)
{
    attack_shadow = shadow;
}

public object query_attack_shadow()
{
    return attack_shadow;
}

public int try_hit(object target)
{
    if (attack_shadow && 
        attack_shadow->attack_weapon_blocked(shadow_who))
    {
        return 0;
    }
    int result = shadow_who->try_hit(target);
    return result;
}
