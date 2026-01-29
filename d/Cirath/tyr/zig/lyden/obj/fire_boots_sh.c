/*  Modified fire_boots_sh.c created by Shiva@Genesis
*  This shadow goes along with the fire boots
*  (fire_boots.c).
*  It detects unarmed attacks, calling the appropriate 
*  functions in the boots.
*  2021-11-20 Meton Removed delay from remove/unwield/release as
*       it interefered with remove all - And the flames problem
*       on items was solved making it redundant.
*/

inherit "/std/shadow";
#include <wa_types.h>

static object boots;

void
remove_boot_shadow()
{
    remove_shadow();
}

int
query_boot_shadow() { return 1; }

void
set_boots_ob(object ob)
{
    boots = ob; 
}

object
query_boots_ob() { return boots; }

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
    if (!boots)
    {
        set_alarm(0.5, 0.0, &remove_shadow());
        return shadow_who->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }
  
    /* If the unarmed attack has done more than 20 hps damage and the
     * attack is done with the right or left hand, we call a function
     * in the boots to do special damage.  Returning 1 disables the
     * combat system's normal handling of the remainder of the unarmed
     * attack; the special_damage() function in the boots takes care
     * of combat messages, etc.
     */
    if ((phurt >= 0) && (dam > 20) && (aid & (W_FOOTR | W_FOOTL)) && 
    boots->special_damage(aid, hdesc, phurt, enemy, phit, dam))
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
    if (!boots)
    {
        remove_boot_shadow();
    }
    else
    {
        set_alarm(0.2, 0.0, &boots->remove_flames());
    }
    
    return shadow_who->wield(wep);
}

/*
*   Function name: unwield
*   Description  : Calls removal of magic effects and
                    checks if boots still worn.
*   Arguments    : 
*   Returns      : 
*/
void
unwield(object wep)
{
    if (!boots)
    {
        remove_boot_shadow();
    }
    else
    {
        boots->remove_flames();
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
    if (!boots)
    {
        remove_boot_shadow();
    }
    else
    {
        set_alarm(0.2, 0.0, &boots->remove_flames());
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
    if (!boots)
    {
        remove_boot_shadow();
    }
    else
    {
        boots->remove_flames();
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
    if (!boots)
    {
        remove_boot_shadow();
    }
    else
    {
        set_alarm(0.2, 0.0, &boots->remove_flames());
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
    if (!boots)
    {
        remove_boot_shadow();
    }
    else
    {
        boots->remove_flames();
    }
    
    //set_alarm(0.1, 0.0, &shadow_who->release());
    shadow_who->release();
}