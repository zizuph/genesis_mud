/* fire_glove_sh.c created by Shiva@Genesis
*
*   Fire gloves recoded by Meton 2020.
*   Equipped shadow created from original fire_glove_sh.c
*   This shadow goes along with the fire gloves (fire_gloves.c).
*   It detects wielding/unwielding of weapons
*   calling the appropriate functions in the gloves.
*
*   Calls damage if wielded weapon hits, and dmg>20&phurt>=0.
*   Calls damage if worn shield is hit, and dmg>20&phurt>=0.
*   Removes shadow when doing enter_env due to problems with npc death
*/

inherit "/std/shadow";
#include <wa_types.h>
#include "../local.h"

//Integers
object equip = 0;
object gloves = 0;

/*
*   Function name: remove_flames_shadow
*   Description  : removes this shadow
*   Arguments    : 
*   Returns      : 
*/
void
remove_flames_shadow()
{
    gloves->removal_message(equip);
    remove_shadow();
}

/*
*   Function name: query_flames_shadow
*   Description  : checks this shadow
*   Arguments    : 
*   Returns      : 
*/
int
query_flames_shadow() { return 1; }

/*
*   Function name: set_flames_ob
*   Description  : sets the ob.
*   Arguments    : 
*   Returns      : 
*/
void
set_flames_ob(object ob)
{
    equip = ob;
}

/*
*   Function name: query_flames_ob
*   Description  : checks the ob.
*   Arguments    : 
*   Returns      : ob
*/

void
set_gloves_ob(object ob)
{
    gloves = ob; 
}

object
query_flames_ob() { return equip; }


/*
*   Function name: did_hit
*   Description  : adds fire damage.
*   Arguments    : 
*   Returns      : did_hit original call
*/
int
did_hit(int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam)
{
    // Ckrik: Sanity check
    if (!objectp(equip) || equip != shadow_who || !objectp(gloves))
    {
        set_alarm(0.0, 0.0, &remove_shadow());
        return shadow_who->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

/*  If the attack has done more than 20 hps damage we have a 25%
*   to add a bit of fire damage and returns the call to the weapon.
*/

    if ((phurt >= 0) && (dam > 20) && (random(4) == 0))
    {
        string with = equip->query_short();

        int hurt = gloves->fire_damage(enemy);
        string burn = gloves->burn_description(hurt);
        gloves->armed_hit(with, enemy, burn);

        return shadow_who->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    return shadow_who->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

/*
*   Function name: short
*   Description  : adds description
*   Arguments    : 
*   Returns      : description
*/
// Thanks to Arman for sharing enchantmentspell to describe how it works.
public varargs string
short(object for_obj)
{
    return ("flame-covered " + shadow_who->short(for_obj));
}

/*
*   Function name: long
*   Description  : adds description
*   Arguments    : 
*   Returns      : description
*/
string 
long(string str, object for_obj)
{
    return (shadow_who->long(str, for_obj) 
        + "It is surrounded by flames, from the gloves.\n");
}

/*
* Function name: got_hit
* Description:   Gives damage when flaming shields hit.
* Arguments:     hid:   The hitloc id, ie the bodypart hit.
*                ph:    The %hurt
*                att:   Attacker
*                dt:    The damagetype
*                dam:   The damage done to us in hit points
*/
int
got_hit(int hid, int phurt, object enemy, int dt, int dam)
{
    // Ckrik: Sanity check
    if (!objectp(equip) || equip != shadow_who || !objectp(gloves))
    {
        set_alarm(0.0, 0.0, &remove_shadow());
        return shadow_who->got_hit(hid, phurt, enemy, dt, dam);
    }

    // 25% chance to trigger.
    if ((phurt >= 0) && (dam > 20) && (random(4) == 0))
    {
        int hurt = gloves->fire_damage(enemy);
        string burn = gloves->burn_description(hurt);

        gloves->flame_shield_hit(enemy, burn);
    }
    
    return shadow_who->got_hit(hid, phurt, enemy, dt, dam);
}

void
enter_env(object env, object from)
{
    set_alarm(0.0, 0.0, &remove_shadow());
    return shadow_who->enter_env(env, from);
}