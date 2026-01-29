/*
 * fire_arrow.c
 * 
 * This is a 50/50 arrow which deals 25% additional fire damage, this would
 * roughly to a 60/60 arrow in white hit damage. If you calculate the impact
 * on specials, it would be alot lower.
 *
 */

#include </stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/arrow";
inherit "/lib/keep";

/*
 * Function name:   spell_resist_modify_value
 * Description:     This function modifies the specified value based on the
 *                  specified resistance, reducing or increasing it.
 * Arguments:       (int) value  - value to modify, most likely a pen value
 *                  (int) resist - resistance mod, the return of spell_resist 
 * Returns:         (int) result - the value modified by the resistance
 */
public int
spell_resist_modify_value(int value, int resist)
{
    /*
     * Modification for pen to match non-magic calculation inside of cb_hit_me,
     * using F_NEW_DAMAGE formula. We multiply the resistance by 80% to make it
     * so that there is a chance that the pen goes to 0.
     */
    if (random(100) < (resist * 80 / 100))
        return 0;
    
    /*
     * Reduces the effectiveness of vulnerability, -100 resistance equals 50%
     * bonus effect on the spell instead of 100%.
     */
    if (resist < 0)
        resist /= 2;
    
    /*
     * Modify value with resistance, this formula has been altered to allow for
     * negative resistance, meaning things can be vulnerable and increase the
     * actual effect of the spell.
     * 
     * Vulnerability has been capped at 50% increased damage for now (-50).
     */
    value = (value * (100 - max(min(resist, 100), -50))) / 100;

    return value;
} /* spell_resist_modify_value */

/*
 * Function Name:   create_arrow
 * Description:     This is the basic construct for the arrow.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
create_arrow()
{
    set_adj("fiery");
    add_adj("black-feathered");
    set_projectile_id("fiery_black_feathered_arrow");
    set_hit(50);
    set_pen(50);
    set_keep(1);
    
    add_item(({"feathers", "raven feathers"}), "These black raven feathers are "
    + "incredible smooth, allowing the wind to pass over them without "
    + "hindrance.\n");
    add_item(({"thin runes", "runes", "delicate runes", "thin and delicate "
    + "runes", "delicate and thin runes"}), "They run across the shaft of the "
    + "arrow, but you have no idea what they mean.\n");
    add_item(({"shaft", "ebony shaft"}), "The shaft is made of light ebony "
    + "making this arrow very well balanced.\n");
    add_item(({"crystal", "crystal tip", "tip"}), "It is some sort of crystal. "
    + "Since the runes appears to flow towards the tip, it might be the place "
    + "where the power of the runes come together.\n");
    add_item(({"glow", "red glow"}), "The red glow seems to come from the "
    + "crystal tip and envelopes the rest of the arrow.\n");

    add_prop(MAGIC_AM_ID_INFO, ({
        "This arrow is magically embrued to be able to cause fire damage in "
        + "the right hands.", 60
    }));
        
    add_prop(MAGIC_AM_MAGIC, ({ 70, "enchantment" }));
    
    add_prop(OBJ_S_WIZINFO, "This arrow cause magical fire damage.\n");
} /* create_arrow */

/*
 * Function name:   get_projectile_long
 * Description:     Use this function to return the proper long description of
 *                  this arrow.
 * Arguments:       (string) str     - the pseudo-item to describe. This is an
 *                                     item added with add_item. If this is 0,
 *                                     it will return the description of the
 *                                     whole object.
 *                  (object) for_obj - the object trying to get the long.
 *                  (int) num        - The number of arrows in this stack.
 * Returns:         (string)         - the description of the object or
 *                                     pseudo-item.
 */
string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow has" : "These arrows have") + " fins made "
    + "from the finest raven feathers, from which thin and delicate runes "
    + "stretch out along the ebony shaft ending at a crystal tip. A red glow "
    + ((num == 1) ? "emanates from the arrow and pervades its" : "emanates "
    + "from the arrows and pervade their") + " presense by a radiating "
    + "warmth.\n";
} /* get_projectile_long */

/*
 * Function name:   projectile_hit_target
 * Description:     A hook that is called in projectiles when it hits a target.
 *                  The hook is meant to be redefined to enable special effects
 *                  like poisoned projectiles.
 * Arguments:       (object) attacker: The attacker shooting this missile.
 *                  (int)    aid:      The attack id
 *                  (string) hdesc:    The hitlocation description.
 *                  (int)    phurt:    The %hurt made on the enemy
 *                  (object) enemy:    The enemy who got hit
 *                  (int)    dt:       The current damagetype
 *                  (int)    phit:     The %success that we made with our weapon
 *                  (int)    dam:      The actual damage caused by this weapon
 *                                     in hit points.
 *                  (int)    hid:      The hit location id.
 * Returns:         Nothing
 */
public varargs void
projectile_hit_target(object archer, int aid, string hdesc, int phurt,
                      object enemy, int dt, int phit, int dam, int hid)
{
    string  you_burnt,
            they_burnt;
    int     extra_dam = 0,
            resist;

    ::projectile_hit_target(archer, aid, hdesc, phurt, enemy, dt, phit, dam, hid);
    if (phurt > 1)
    {
        // Deal 25% fire damage.
        dam /= 4;
        resist = enemy->query_magic_res(MAGIC_I_RES_FIRE);
        extra_dam = spell_resist_modify_value(dam, resist);
        switch(extra_dam)
        {
            case 1..15:
            you_burnt = "You were slightly singed by the fire.\n";
            they_burnt = " was slightly singed by the fire.\n";
                break;
            case 16..45:
            you_burnt = "You were singed by the fire.\n";
            they_burnt = " was singed by the fire.\n";
                break;
            case 46..99:
            you_burnt = "You feel burnt by the fire.\n";
            they_burnt = " seems burnt by the fire.\n";
                break;
            case 100..175:
            you_burnt = "You are badly hurt by the fire.\n";
            they_burnt = " seems badly hurt by the fire.\n";
                break;
            default:
            you_burnt = "You are engulfed in flames.\n";
            they_burnt = " is engulfed in flames.\n";
        }
        
        tell_room(environment(enemy), "A burst of fire emits from the fiery "
        + "black-feathered arrow as it hits " + QTNAME(enemy) + ".\n", enemy);
        tell_room(environment(enemy), QCTNAME(enemy) + they_burnt, enemy);
        enemy->catch_tell("A burst of fire emits from the fiery black-"
        + "feathered arrow as it hits you.\n");
        enemy->catch_tell(you_burnt);

        enemy->heal_hp(-extra_dam);
        if (enemy->query_hp() <= 0)
            enemy->do_die(archer);
    }
} /* projectile_hit_target */
