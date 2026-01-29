/*
 * enchantment_interface.c
 *
 * This is the shadowed functions that must be in the player
 * using a POT enchanted object
 *
 * Since only POT members can use them, we inherit this file
 * from the guildshadow
 * 
 * 2017-02-09 - Cotillion
 * - Fixed hit_me to forward target_hitloc
 */

static int gHPBonus         = 0;
static int gManaBonus       = 0;
static int gFatigueBonus    = 0;
static object gLastWeapon   = 0;

public void
ei_add_hp_bonus(int bonus)
{
    gHPBonus += bonus;
}

public void
ei_add_mana_bonus(int bonus)
{
    gManaBonus += bonus;
}

public void
ei_add_fatigue_bonus(int bonus)
{
    gFatigueBonus += bonus;
}

public int
ei_query_hp_bonus()
{
    return gHPBonus;
}

public int
ei_query_mana_bonus()
{
    return gManaBonus;
}

public int
ei_query_fatigue_bonus()
{
    return gFatigueBonus;
}

public object
ei_query_last_weapon()
{
    return gLastWeapon;
}

/*
 * Function name:   query_max_mana
 * Description:     Calculates that maximum of mana points that a living
 *                  can get.
 * Returns:         The maximum.
 */
public int
query_max_mana()
{
    int tmp = this_object()->query_shadow_who()->query_max_mana();
    
    if (gManaBonus)
    {

        return tmp + (tmp * gManaBonus) / 100;
    }
    else
        return tmp;
}

/*
 * Function name:   query_max_hp
 * Description:     Calculates the maximum number of hitpoints that the
 *                  living can achieve.
 * Returns:         The maximum
 */
public int
query_max_hp()
{
    int tmp = this_object()->query_shadow_who()->query_max_hp();
    
    if (gHPBonus)
    {
        return tmp + (tmp * gHPBonus) / 100;
    }
    else
        return tmp;
}

/*
 * Function name:   add_fatigue
 * Description:     Add an amount of fatigue points to the current amount
 *                  of the living. Observe, negative argument makes a player
 *		            more tired.
 * Arguments:       f: the amount of change
 */
public void
add_fatigue(int f)
{
    object obj = this_object()->query_shadow_who();
    
    if (gFatigueBonus && f < 0 && objectp(obj->query_attack()))
    {
        f *= gFatigueBonus;
    }

    obj->add_fatigue(f);
}

/*
 * Function name:   hit_me
 * Description:     Called to make damage on this object. The actually
 *		            made damage is returned and will be used to change
 *		            the score of the aggressor.
 * Arguments:	    wcpen 	- The wc-penetration
 *		            dt    	- damagetype, use MAGIC_DT if ac will not
 *				              help against this attack.
 *		            attacker 	- Object hurting us
 *		            attack_id 	- Special id saying what attack hit us. If you
 *		    		              have made a special attack, let the id be -1
 * Returns:         The hitresult as given by the external combat object.
 */
public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    if (attack_id >= 0 && objectp(attacker))
        gLastWeapon = attacker->query_weapon(attack_id);
    else
        gLastWeapon = 0;

    return this_object()->query_shadow_who()->hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
}
