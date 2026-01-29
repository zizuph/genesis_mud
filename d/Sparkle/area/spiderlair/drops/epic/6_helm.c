/*
 * /d/Sparkle/area/spiderlair/drops/epic/6_helm.c
 *
 * magical resistance helm vs poison and illusions.
 * Nerull, 21/2/09.
 */

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../../defs.h";

inherit "/std/armour";

// The creation of the armour.
void create_armour()
{
    set_name("helm");
    set_adj("dimly");
    set_adj("green-glowing");
    set_short("dimly green-glowing helm");
    set_long("This is a dimly green-glowing helm made of steel. It covers"+
    " much of the head and neck, and partically some of the lower facial "+
    "areas.\n");
    set_ac(45);
    set_at(A_HEAD);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, 1450);
    
    add_prop(OBJ_S_WIZINFO, "This helm adds "+MAGIC_SP_RESIST+
    " magical resistance to poison and illusion magic.\n");
        
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
        
    add_prop(MAGIC_AM_ID_INFO, ({
    "This helm is enchanted by a protection " +
    "spell.\n", 10,
    "This helm protects the wearer from both " +
    "poison and illusion magic.\n", 50}));
}


// The resistance check.
mixed query_magic_protection(string prop, object what)
{
    if (!worn || what != wearer || !stringp(prop))
        return 0;

    if (prop == MAGIC_I_RES_POISON || prop == MAGIC_I_RES_ILLUSION)
    {
    		return ({MAGIC_SP_RESIST, 1});
    }

		return 0;
}


// Masking wear.
int wear(object to)
{
    TP->catch_msg("You feel more shielded vs magical spells.\n");
    
    if (wearer)
        wearer->remove_magic_effect(TO);

    TP->add_magic_effect(TO);
    return 0;
}


// Masking remove.
int remove(object to)
{
    if (wearer == TP)
        wearer->catch_tell("You feel more vurneable to magical spells.\n");

    wearer->remove_magic_effect(TO);


    return 0;
}


// Masking leave_env.
void leave_env(object to, object from)
{
    ::leave_env(to, from);

    if (!living(from))
        return;

    from->remove_magic_effect(TO);
}


// If the item is dispelled/disenchanted.
int dispel_magic(int power)
{
    if (power < query_prop(MAGIC_I_RES_MAGIC))
        return 0;

    query_worn()->catch_tell("Your "+short()+" fades away!\n");    
    remove_broken(1);
    remove_object();
    return 1;
}
