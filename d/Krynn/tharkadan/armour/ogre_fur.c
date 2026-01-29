inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/lib/keep";

#define     AOD_WEAR_PROP        ("_aod_wear_prop")

void
create_armour()
{
    set_name("cloak");
    add_name("fur");
    set_ac(12);
    set_at(A_ROBE);
    set_adj("fur");
    add_adj("heavy");
    set_short("heavy fur cloak");
    set_long("This heavy cloak is made from the furs of a mix of " +
      "creatures, ranging from the grey mountain wolves to the " +
      "alpine elk. You find it very thick and heavy.\n");
    add_prop(OBJ_I_VOLUME, 8750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_ROBE) * 4);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));

    set_wf(this_object());
    /* This armour is wearable by ogres. */
    add_prop(AOD_WEAR_PROP, 1);
}

/*
 * Function name:        wear
 * Description  :        only allow ogres to wear this massive armour
 * Arguments    :        object obj - this_object
 * Returns      :        0 -- allow to wear
 *                       1 -- not an ogre, fail
 */
public mixed
wear(object obj)
{
    object  tp = environment(this_object()); 

    if (!living(tp))
    {
        return 0;
    }

    if (tp->query_race_name() == "ogre")
    {
        return 0;
    }

    return "Wear this massive thing? You could more likely"
      + " take a nap under it! Whatever creature was intended to wear"
      + " this piece of equipment is more than twice your height.\n";

    return 1;
} /* wear */
