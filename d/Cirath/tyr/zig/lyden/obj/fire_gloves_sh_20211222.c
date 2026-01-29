/* fire_glove_sh.c created by Shiva@Genesis
* This shadow goes along with the fire gloves (fire_gloves.c).
* It detects wielding/unwielding of weapons and attacks,
* calling the appropriate functions in the gloves.
*
*   Recoded by Meton 2020.
*   Changed from update_flames to remove_flames call in the gloves.
*   Calls additional damage on unarmed hit if and dmg>20&phurt>=0
*  2021-11-20 Meton Removed delay from remove/unwield/release as
*       it interefered with remove all - And the flames problem
*       on items was solved making it redundant.
*/

inherit "/std/shadow";
#include <wa_types.h>

static object gloves;

void
remove_glove_shadow()
{
    remove_shadow();
}

int
query_glove_shadow() { return 1; }

void
set_gloves_ob(object ob)
{
    gloves = ob; 
}

object
query_gloves_ob() { return gloves; }

/*
*   Function name: did_hit
*   Description  : Calls possible extra damage
*   Arguments    : 
*   Returns      : did_hit original call
*/
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam)
{
    if (!gloves)
    {
        set_alarm(0.5, 0.0, &remove_shadow());
        return shadow_who->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    /* If the attack has done more than 20 hps damage and the
    * attack is done with the right or left hand, we call a function
    * in the gloves to do special damage. Return 0 if weapons wielded,
    * so the normal hits go, and returning 1 disables the
    * combat system's normal handling of the remainder of the unarmed
    * attack; the special_damage() function in the gloves takes care
    * of combat messages, etc.
    */
    if ((phurt >= 0) && (dam > 20) && (aid & W_BOTH) && 
    gloves->special_damage(aid, hdesc, phurt, enemy, phit, dam))
    {
        return 1;
    }

    return shadow_who->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

/*
*   Function name: wield
*   Description  : Calls removal of magic effects
*   Arguments    : 
*   Returns      : 
*/
int
wield(object wep)
{
    if (!gloves)
    {
        remove_glove_shadow();
    }
    else
    {
        set_alarm(0.2, 0.0, &gloves->remove_flames());
    }
    
    return shadow_who->wield(wep);
}

/*
*   Function name: unwield
*   Description  : Calls removal of magic effects and
                    checks if gloves still worn.
*   Arguments    : 
*   Returns      : 
*/
void
unwield(object wep)
{
    if (!gloves)
    {
        remove_glove_shadow();
    }
    else
    {
        gloves->remove_flames();
    }
    
    //set_alarm(0.1, 0.0, &shadow_who->unwield(wep));
    shadow_who->unwield(wep);
}

/*
*   Function name: wear_arm
*   Description  : Calls removal of magic effects
*   Arguments    : 
*   Returns      : 
*/
mixed
wear_arm(object arm)
{
    if (!gloves)
    {
        remove_glove_shadow();
    }
    else
    {
        set_alarm(0.2, 0.0, &gloves->remove_flames());
    }

    return shadow_who->wear_arm(arm);
}

/*
*   Function name: remove_arm
*   Description  : Calls removal of magic effects
*   Arguments    : 
*   Returns      : 
*/
void
remove_arm(object arm)
{
    if (!gloves)
    {
        remove_glove_shadow();
    }
    else
    {
        gloves->remove_flames();
    }
    
    //set_alarm(0.1, 0.0, &shadow_who->remove_arm(arm));
    shadow_who->remove_arm(arm);
}

/*
*   Function name: hold
*   Description  : Calls removal of magic effects
*   Arguments    : 
*   Returns      : 
*/
mixed
hold()
{
    if (!gloves)
    {
        remove_glove_shadow();
    }
    else
    {
        set_alarm(0.2, 0.0, &gloves->remove_flames());
    }

    return shadow_who->hold();
}

/*
*   Function name: release
*   Description  : Calls removal of magic effects
*   Arguments    : 
*   Returns      : 
*/
void
release()
{
    if (!gloves)
    {
        remove_glove_shadow();
    }
    else
    {
        gloves->remove_flames();
    }
    
    //set_alarm(0.1, 0.0, &shadow_who->release());
    shadow_who->release();
}