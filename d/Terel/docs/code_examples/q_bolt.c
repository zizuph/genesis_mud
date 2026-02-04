/* quarrel_bolt.c
 * built upon /std/bolt.c
*/

#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/d/Terel/std/bolt.c";

public void
create_bolt()
{
    set_short("short quarrel bolt");
    set_adj("short");
    add_adj(({"quarrel","wooden"}));

    add_prop(HEAP_I_UNIT_WEIGHT, 33);
    add_prop(HEAP_I_UNIT_VOLUME, 36);
    add_prop(HEAP_I_UNIT_VALUE, 45);
    set_heap_size(10);

    set_hit(40);
    set_pen(40);

    set_projectile_id("t_q_bolt");

    set_no_merge(1);
}

/* Return the string for the long description of num arrow or arrows
 * for the object for_obj
 */
public string
get_projectile_long(string str, object for_obj, int num)
{
    return "The " + singular_short(for_obj) +
        ((num == 1) ? " is " : "s are ") + "perfectly balanced. " +
        "Two feathers are attached to the shaft" +
        ((num == 1) ? " of this bolt, " : "s of these bolts, ") +
        "instead of three normally found on arrows.\n";
}

public void
init()
{
    ::init();
    set_no_merge(0);
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
}

/*
 * Arguments:     attacker: The attacker shooting this missile.
 *                aid:      The attack id
 *                hdesc:    The hitlocation description.
 *                phurt:    The %hurt made on the enemy
 *                enemy:    The enemy who got hit
 *                dt:       The current damagetype
 *                phit:     The %success that we made with our weapon
 *                dam:      The actual damage caused by this weapon in
 *                          hit points.
 *                hid:      The hit location id.
 */
void
projectile_hit_target(object archer, int aid, string hdesc, int phurt,
                      object enemy, int dt, int phit, int dam, int hid)
{
    object *clothing_arr;
    object clothing_hit;

    archer->catch_msg("Phurt: " + phurt + ", phit: " + phit +
        ", Damage: " + dam + "\n");

    enemy->reduce_hit_point(dam); //double damage the enemy

    //check if any clothing worn where arrow hit
    if(clothing_arr = enemy->query_clothing(hid)) {
      if(sizeof(clothing_arr)) {

        //pick one of the items worn
        clothing_hit = clothing_arr[ random( sizeof(clothing_arr) ) ];

        //if item is magic, no effect
        if( clothing_hit->query_prop(MAGIC_AM_MAGIC) ) return;

        //only 1/3 chance of continuing
        if(random(3) > 0) return;

        enemy->catch_msg("The " + singular_short(enemy) +
            " rips through your " + hdesc + " and the " +
            clothing_hit->query_short() + " is badly damaged.\n");

        //break this item
        clothing_hit->set_short("ripped " + clothing_hit->query_short());
        clothing_hit->add_prop_obj_i_broken(1);
        clothing_hit->remove_broken(0);
      }
    }

    //tell enemy about the extra damage
    enemy->catch_msg("The " + singular_short(enemy) + " rips through your " +
        hdesc + " badly as it hits you hard.\n");

    return;
}
