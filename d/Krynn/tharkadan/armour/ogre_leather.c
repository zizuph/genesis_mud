inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define     ARMOUR_CLASS 28
#define     AOD_WEAR_PROP        ("_aod_wear_prop")

void
create_armour()
{
    set_name("breastplate");
    set_pname("breastplates");
    add_name("armour");
    add_pname("armours");

    set_adj("large");
    add_adj("leather");

    set_short("large leather breastplate");
    set_pshort("large leather breastplates");
    set_long("This large leather breastplate is of crudely made, " +
      "and looks like it was crafted for a person of massive " +
      "proportions. It is incredibly thick and heavy, and probably " +
      "as tough to penetrate as chainmail.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);

    set_wf(this_object());
    /* This armour is wearable by ogres. */
    add_prop(AOD_WEAR_PROP, 1);

    add_prop(OBJ_I_WEIGHT, 20000);
    add_prop(OBJ_I_VOLUME, 9500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
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
