/*

 Sindar guard arrow
 Palmer 12/09/2003

 */

inherit "/std/arrow";

#include <stdproperties.h>

public void
create_arrow()
{
    set_adj(({ "grey", "grey-feathered" }));
    set_projectile_id("sindar_guard_arrow");
    add_prop(HEAP_I_UNIT_WEIGHT, 22);
    add_prop(HEAP_I_UNIT_VOLUME, 26);
    add_prop(HEAP_I_UNIT_VALUE, 12);
    set_hit(50);
    set_pen(50);
    set_heap_size(1);
}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow is" : "These arrows are") +
      " of good quality. Balanced, straight and with " +
      "fins made from mat black feathers.\n";
}



/*
 * Function name: projectile_hit_target
 * Description  : A hook that is called in projectiles when it hits a target.
 *                The hook is meant to be redefined to enable special effects
 *                like poisoned projectiles.
 *
 * Arguments:     attacker: The attacker shooting this missile.
 *                aid:      The attack id
 *                hdesc:    The hitlocation description.
 *                phurt:    The %hurt made on the enemy
 *                enemy:    The enemy who got hit
 *                dt:       The current damagetype
 *                phit:     The %success that we made with our weapon
 *                dam:      The actual damage caused by this weapon in hit
 *                          points.
 *                hid:      The hit location id.
 */

public varargs void
projectile_hit_target(object archer, int aid, string hdesc, int phurt,
		      object enemy, int dt, int phit, int dam, int hid)
{
    say("Hit.\n\n");
    write("Hit.\n\n");
}

