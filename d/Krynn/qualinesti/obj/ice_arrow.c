/*
 * This arrow does 25% added frost damage, with a pen of 36, this roughly equals
 * 47 pen for white hits. This pen is quite detrimental to special abilities.
 *
 * The slow ability decreases haste by 15 for 30 seconds.
 */

#include </stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/arrow";
inherit "/lib/keep";

#define SLOW_EFFECT         15
#define SLOW_TIME           30.0

static object   gSlowEffect;
static int      gSlowAlarm;
static string   gStringDesc;

public mixed
query_slow_effect(string prop)
{
    if (objectp(gSlowEffect) && gSlowEffect->query_hp() > 0
        && !gSlowEffect->query_ghost())
    {
        switch(prop)
        {
            case OBJ_M_NO_INS:
            case OBJ_M_NO_SELL:
            case OBJ_M_NO_GIVE:
            case OBJ_M_NO_DROP:
                return "The " + singular_short(this_player()) + " is frozen "
                + "stuck in your " + gStringDesc + "\n";
            case OBJ_M_NO_STEAL:
                return "The " + singular_short(this_player()) + " is frozen "
                + "stuck in the " + gStringDesc + " of "
                + this_player()->query_the_name(gSlowEffect) + "\n";
        }
        return 1;
    }
    
    return 0;
} /* query_slow_effect */

public void
remove_slow_effect(object enemy)
{
    if (objectp(gSlowEffect))
    {
        gSlowEffect->inc_prop(LIVE_I_QUICKNESS, SLOW_EFFECT);
        gSlowEffect->query_combat_object()->cb_update_speed();
        gSlowEffect = 0;
        update_heap_id();
        
        remove_prop(OBJ_M_NO_GIVE);
        remove_prop(OBJ_M_NO_DROP);
        remove_prop(OBJ_M_NO_STEAL);
        remove_prop(OBJ_M_NO_SELL);
        remove_prop(OBJ_M_NO_INS);
    }
} /* remove_slow_effect */

public void
add_slow_effect(object enemy, string hdesc)
{
    if (objectp(enemy) && !objectp(gSlowEffect) && environment() == enemy)
    {
        gSlowEffect = enemy;
        if (hdesc = "legs")
            hdesc = one_of_list(({ "right leg", "left leg" }));
        
        gStringDesc = hdesc;
        enemy->dec_prop(LIVE_I_QUICKNESS, SLOW_EFFECT);
        enemy->query_combat_object()->cb_update_speed();
        
        add_prop(OBJ_M_NO_GIVE, &query_slow_effect(OBJ_M_NO_GIVE));
        add_prop(OBJ_M_NO_DROP, &query_slow_effect(OBJ_M_NO_DROP));
        add_prop(OBJ_M_NO_STEAL, &query_slow_effect(OBJ_M_NO_STEAL));
        add_prop(OBJ_M_NO_SELL, &query_slow_effect(OBJ_M_NO_SELL));
        add_prop(OBJ_M_NO_INS, &query_slow_effect(OBJ_M_NO_INS));
        
        update_heap_id();
        if (gSlowAlarm)
            remove_alarm(gSlowAlarm);
        
        gSlowAlarm = set_alarm(SLOW_TIME, 0.0, &remove_slow_effect());
    }
} /* add_slow_effect */

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
    set_adj("blue");
    add_adj("crystal-tipped");
    set_projectile_id("blue_crystal-tipped_arrow");
    set_hit(52);
    set_pen(36);
    set_keep(1);
    
    add_item(({"feathers", "griffon feathers", "white feathers", "white "
    + "griffon feathers"}), "The white griffons feathers make up the fins and "
    + "are responsible for making the arrow fly straight.\n");

    add_item("shaft", "The shaft is made of wood from the finest vallenwood "
    + "trees.\n");

    add_item(({"crystal", "crystal tip", "tip"}), "The crystal is bright-blue "
    + "and shared liked a small leaf.\n");
    
    add_prop(MAGIC_AM_ID_INFO, ({
        "This arrow is magically embrued to be able to cause frost damage in "
        + "the right hands.", 60
    }));
        
    add_prop(MAGIC_AM_MAGIC, ({ 70, "enchantment" }));
    
    add_prop(OBJ_S_WIZINFO, "This arrow cause magical a little frost damage "
    + "and slows the target if it is fired.\n");
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
    return ((num == 1) ? "This elegant arrow is tipped with a leaf shaped "
    + "bright-blue crystal, yet it remains very light and perfectly balanced. "
    + "It has been carved from the finest of vallenwood trees, and the fins "
    + "are made from white griffon feathers. The blue crystal shimmers "
    + "slightly as skin touches its cold surface.\n" : "These elegant arrows "
    + "are tipped with a leaf shaped bright-blue crystal, yet they remain very "
    + "light and perfectly balanced. They have been carved from the finest of "
    + "vallenwood trees, and the fins are made from white griffon feathers. "
    + "The blue crystal shimmers slightly as skin touches its cold surface.\n");
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
    string  you_frozen,
            they_frozen;
    int     extra_dam = 0,
            resist;

    ::projectile_hit_target(archer, aid, hdesc, phurt, enemy, dt, phit, dam, hid);
    if (phurt > 1)
    {
        // Deal 25% cold damage.
        dam /= 4;
        resist = enemy->query_magic_res(MAGIC_I_RES_COLD);
        extra_dam = spell_resist_modify_value(dam, resist);
        switch(extra_dam)
        {
            case 1..15:
            you_frozen = "You were slightly chilled by the ice.\n";
            they_frozen = " was slightly chilled by the ice.\n";
                break;
            case 16..45:
            you_frozen = "You were chilled by the ice.\n";
            they_frozen = " was chilled by the ice.\n";
                break;
            case 46..99:
            you_frozen = "You feel frozen from the ice.\n";
            they_frozen = " seems frozen from the ice.\n";
                break;
            case 100..175:
            you_frozen = "You are badly frozen from the ice.\n";
            they_frozen = " seems badly frozen from by the ice.\n";
                break;
            default:
            you_frozen = "You are chilled to the bone from the ice.\n";
            they_frozen = " appears chilled to the bone from the ice.\n";
        }
        
        tell_room(environment(enemy), "A cloud of ice errupts from the blue "
        + "crystal-tipped arrow as it hits " + QTNAME(enemy) + ".\n", enemy);
        tell_room(environment(enemy), QCTNAME(enemy) + they_frozen, enemy);
        enemy->catch_tell("A cloud of ice errupts from the blue crystal-tipped "
        + "arrow as it hits you.\n");
        enemy->catch_tell(you_frozen);

        if (random(100) > resist)
            add_slow_effect(enemy, hdesc);

        enemy->heal_hp(-extra_dam);
        if (enemy->query_hp() <= 0)
            enemy->do_die(archer);
    }
} /* projectile_hit_target */

/*
 * Function name:   set_hidden
 * Description:     This functions updates the heap_id of the arrow so it stacks
 *                  properly whith other hidden/broken arrows as well.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
update_heap_id()
{
    string  slow_id;
    int     level;

    slow_id = projectile_id;
    level   = query_prop(OBJ_I_HIDE);
    
    if (objectp(gSlowEffect))
        slow_id += "_slowed_object_" + OB_NAME(this_object());
    
    add_prop(HEAP_S_UNIQUE_ID,
             (loaded ? "loaded_" : "") +
             (broken ? "broken_" : "") +
             (level ? "hidden_" + level + "_" : "") +
             slow_id);
} /* update_heap_id */