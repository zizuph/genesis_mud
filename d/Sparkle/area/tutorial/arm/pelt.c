/*
 *  /d/Sparkle/area/tutorial/obj/pelt.c
 *
 *  These pelts can be looted from the animals in the Sterling Woods.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
inherit "/std/armour";

#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

/* global variables */
public string      Pelt_Type = "";

/* prototypes */
public void        create_pelt();
public void        create_armour();
public mixed       check_steal();
public void        config_pelt();

public void        set_pelt(string s) { Pelt_Type = s; }
public string      query_pelt() { return Pelt_Type; }


/*
 * Function name:        create_pelt
 * Description  :        a dummy function to be used by inheriting files
 */
public void
create_pelt()
{
} /* create_pelt */

/*
 * Function name:        create_armour
 * Description  :        set up the animal pelt
 */
public void
create_armour()
{
    set_name("pelt");

    create_pelt();
    config_pelt();

    add_prop(OBJ_I_WEIGHT, 60);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_M_NO_STEAL, check_steal);
} /* create_armour */


/*
 * Function name:        check_steal
 * Description  :        this pelt should not be stolen from the
 *                       animal who owns it (duh)
 * Returns      :        1: cannot steal
 *                       0: okay to steal
 */
public mixed
check_steal()
{
    if (!living(environment(this_object())))
    {
        return 0;
    }

    if (environment(this_object())->id("_tutorial_animal"))
    {
        return "Live animals do not typically give up their pelts.\n";
    }

    return 0;
} /* check steal */


/*
 * Function name:        config_pelt
 * Description  :        set up the foot based on the Bunny Type
 * Arguments    :        string type - the type of rabbit
 */
public void
config_pelt()
{
    switch(Pelt_Type)
    {
        case "small":
            set_short("small animal pelt");
            add_adj( ({ "small", "animal" }) );
            add_prop(OBJ_I_VALUE, 15 + random(4));
            set_default_armour(1, A_ROBE, ({ 0, 0, 0 }), this_object());
            break;
        case "medium":
            set_short("medium-sized animal pelt");
            add_adj( ({ "medium", "sized", "medium-sized", "animal" }) );
            add_prop(OBJ_I_VALUE, 20 + random(4));
            set_default_armour(3, A_ROBE, ({ 0, 0, 0 }), this_object());
            break;
        case "large":
            set_short("large animal pelt");
            add_adj( ({ "large", "animal" }) );
            add_prop(OBJ_I_VALUE, 25 + random(4));
            set_default_armour(5, A_ROBE, ({ 0, 0, 0 }), this_object());
            break;
        case "gigantic":
            set_short("gigantic animal pelt");
            add_adj( ({ "gigantic", "animal" }) );
            add_prop(OBJ_I_VALUE, 250 + random(100));
            set_default_armour(20, A_ROBE, ({ 0, 0, 0 }), this_object());
            break;
    }

    set_long("This " + short() + " is sleek and attractive. You could"
      + " either wear it for added protection, or sell it for money.\n");
} /* config_pelt */

