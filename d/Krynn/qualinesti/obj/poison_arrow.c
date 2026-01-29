/*
 * poison_arrow.c
 *
 * This is an arrow that deals 100% poison damage over 50 seconds.
 *
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include <poison_types.h>

inherit "/std/arrow";
inherit "/lib/keep";

/*
 * Function Name:   create_arrow
 * Description:     This is the basic construct for the arrow.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
create_arrow()
{
    set_adj("serrated");
    add_adj("oakwood");
    set_projectile_id("serrated_oakwood_arrow");
    set_hit(56);
    set_pen(44);
    set_keep(1);
    
    add_item(({"feathers", "green feathers", "dyed feathers"}), "The feathers "
    + "making up the fins have been dyed green.\n");
   
    add_item("shaft", "The shaft is made out of wood from oak trees, and has a "
    + "snake decorated on it.\n");

    add_item(({"snake", "tip"}), "The tip of the arrow has a snake head carved "
    + "on it. Small onyx gems are used for its eyes, and its mouth open with "
    + "fangs sticking out ready to strike its victim.\n");
    
    add_prop(MAGIC_AM_ID_INFO, ({
        "This arrow is magically embrued to be able to poison its victims.", 60
    }));
        
    add_prop(MAGIC_AM_MAGIC, ({ 70, "enchantment" }));
    
    add_prop(OBJ_S_WIZINFO, "This arrow poison its targets.\n");
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
    return ((num == 1) ? "This arrow is made out of wood from oak trees, and "
    + "has a small snake head carved at the tip. Along the serrated shaft, the "
    + "arrow is decorated with carvings that makes it appear to have a snake "
    + "slithering across it. With this unusual design and the rough green "
    + "feathers making up the fins, this arrow is most likely not intended for "
    + "precision.\n" : "These arrows are made out of wood from oak trees, and "
    + "each has a small snake head carved at the tip. Along the serrated "
    + "shafts, the arrows are decorated with carvings that make them appear to "
    + "have a snake slithering across them. With this unusual design and the "
    + "rough green feathers making up the fins, these arrows aren't intended "
    + "for precision.\n");
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
    object poison;

    ::projectile_hit_target(archer, aid, hdesc, phurt, enemy, dt, phit, dam, hid);
    
    if (phurt > 1)
    {
        tell_room(environment(enemy), QCTNAME(enemy) + " appears to shudder at "
        + "the impact of the arrow.\n", enemy);
        
        enemy->catch_tell("The carved snake arrow leaves behind a sickly green "
        + "residue from where it pierced your skin.\n");
        
        /* This arrow adds 100% damage over 50 seconds. */
        poison = clone_object("/std/poison_effect");
        poison->set_interval(5);
        poison->set_time(50);
        poison->set_damage(({ POISON_FATIGUE, dam / 15, POISON_HP, dam / 5 }));
        poison->set_strength(20+random(40));
        poison->set_poison_type("snake");
        poison->move(enemy, 1);
        poison->start_poison(archer);
    }
} /* projectile_hit_target */
