/* fire_glove_sh.c created by Shiva@Genesis
 * This shadow goes along with the fire gloves (fire_gloves.c).
 * It detects wielding/unwielding of weapons and unarmed attacks,
 * calling the appropriate functions in the gloves.
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
set_gloves_ob(object ob) { gloves = ob; }

object
query_gloves_ob() { return gloves; }

/* Called from the combat sys when we make an attack */
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam)
{
    if (!gloves)
    {
        remove_shadow();
        return shadow_who->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }
  
    /* If the unarmed attack has done more than 20 hps damage and the
     * attack is done with the right or left hand, we call a function
     * in the gloves to do special damage.  Returning 1 disables the
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

/* This is called when the wearer tries to wield a weapon.
 * It makes a call to the gloves to update the flames, should
 * a weapon be wielded in either hand.
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
        set_alarm(0.0, 0.0, &gloves->update_flames());
    }
     
    return shadow_who->wield(wep);
}

/* This is called when the wearer tries to unwield a weapon.
 * It makes a call to the gloves to update the flames, should
 * a weapon be wielded in either hand.
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
        set_alarm(0.0, 0.0, &gloves->update_flames());
    }
    
    shadow_who->unwield(wep);
}

/* This is called when the wearer tries to wear armour
 * It makes a call to the gloves to update the flames, should
 * a shield be worn.
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
        set_alarm(0.0, 0.0, &gloves->update_flames());
    }
  
    return shadow_who->wear_arm(arm);
}

/* This is called when the wearer tries to remove armour
 * It makes a call to the gloves to update the flames, should
 * a shield be removed.
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
        set_alarm(0.0, 0.0, &gloves->update_flames());
    }
  
    shadow_who->remove_arm(arm);
}
