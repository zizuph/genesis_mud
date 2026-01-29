/* /doc/examples/weapons/elf_slayer.c
 *
 * This is an example of a weapon that does extra magical damage
 * in addition to its regular damage.  In this case the weapon does
 * additional damage to elves.
 */

inherit "/std/weapon";
inherit "/d/Genesis/magic/resist";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <ss_types.h>
#include <tasks.h>

void
create_weapon()
{
    set_name("sword");
    set_adj(({ "elf-slaying", "slaying" }));
    set_short("elf-slaying sword");
    set_long("A magical sword, it is enchanted to cause great " +
        "damage to elves.\n");

    set_default_weapon(30, 30, W_SWORD, W_SLASH | W_IMPALE, W_LEFT);
   
    /* Designate this as a magic weapon */
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    /* Allow for identification of the magical properties */
    add_prop(MAGIC_AM_ID_INFO, ({ 
      "The sword seems magically enchanted.\n", 10,
      "It causes extra damage to elves.\n", 20 }));

    /* Indicate the level and type of magic */
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));

    /* Let wizards know what the sword does */
    add_prop(OBJ_S_WIZINFO, "This sword does additional damage to " +
        "to targets of the elf race.\n");

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 2800);
    add_prop(OBJ_I_WEIGHT, 9500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30, 30) + 1000);
}

/*
 * did_hit() is called whenever the weapon is used.  We redefine it
 * to do extra damage when we hit an elf.
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
    int resistance;
    object attacker = query_wielded();

    /* did_hit() is called even when the weapon misses, so we need
     * to check if phurt < 0 before we do any special damage.  If
     * phurt < 0, then it was a missed attack.
     */
    if (phurt < 0)
    {
        return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    /* We only want to do the special damage if the target is an elf,
     * and then only 1 in 10 attacks.
     */
    if ((enemy->query_race_name() == "elf") && !random(10))
    {
        attacker->catch_tell("The elf-slaying sword glows with magical " +
            "energy.\n");
        enemy->catch_tell(attacker->query_The_possessive_name(enemy) +
            " elf-slaying sword glows with magical energy.\n");
        enemy->tell_watcher(QCTPNAME(attacker) + " elf-slaying sword " +
            "glows with magical energy.\n", attacker);

        /* Check the target's magic resistance */
    	resistance = spell_resist_basic(this_object(), enemy, SS_ELEMENT_DEATH,
    	    TASK_DIFFICULT);

        /* Do the extra damage, taking the magic resistance into account */
    	enemy->hit_me(200 * (100 - resistance) / 100, MAGIC_DT,
            attacker, -1);

        /* Kill the target, if appropriate */
        if (enemy->query_hp() <= 0)
	{
            enemy->do_die(attacker);
	}
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}
    
