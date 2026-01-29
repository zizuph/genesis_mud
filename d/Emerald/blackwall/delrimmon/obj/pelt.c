/*
 *  /d/Emerald/blackwall/delrimmon/obj/pelt.c
 *
 *  These pelts can be taken from the corpses of slain
 *  animals in the Del Rimmon area. The goal here is to
 *  make the area newbie friendly with small amounts of
 *  cash to earn from the easy kills.
 *
 *  Copyright (c) February 2002, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

/* global variables */
public int         Pelt;

/* prototypes */
public void        create_armour();
public mixed       check_steal();
public string      pelt_long();
public string      pelt_short();
public void        set_pelt(int i) { Pelt = i; }


/*
 * Function name:        create_armour
 * Description  :        set up the armour
 */
public void
create_armour()
{
    set_name("pelt");
    add_adj( ({ "brown", "fox", "grey", "bobcat", "black",
                "badger", "small", "animal" }) );
    set_short(pelt_short);
    set_long(pelt_long);

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1500);
    set_default_armour(1, A_ROBE, ({0,0,0}), this_object());
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3)
           + this_player()->query_skill(SS_TRADING) * 2);
    add_prop(OBJ_M_NO_STEAL, check_steal);
    long();

} /* create_armour */


/*
 * Function name:        check_steal
 * Description  :        this pelt should not be stolen from the
 *                       animal who wears it (duh)
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

    if (environment(this_object())->id("_delrimmon_forest_animal"))
    {
        return "Live animals do not typically give up their pelts.\n";
    }

    return 0;
} /* check steal */


/*
 * Function name:        pelt_long
 * Description  :        variable returns for what the pelt's
 *                       long desc will be
 * Returns      :        string - the long desc
 */
public string
pelt_long()
{
    switch(Pelt)
    {
        case 1:
            set_long("The brown fur on this pelt is soft and"
              + " sleek. It appears to have once belonged to"
              + " a small fox.\n");
            break;
        case 2:
            set_long("The grey fur on this pelt is intermixed"
              + " with the occasional black or brown strand of"
              + " hair. It once belonged to a bobcat.\n");
            break;
        case 3:
            set_long("The long black fur of this pelt is thick and"
              + " coarse, and would no doubt have provided its former"
              + " owner with a strong resistance to the cold.\n");
            break;
        default:
            set_long("This pelt once belonged to a free roaming"
              + " animal of some kind. Its hair is soft and yet"
              + " thick enough to have provided warmth and"
              + " protection from the elements.\n");
            break;
    }
} /* pelt_long */


/*
 * Function name:        pelt_short
 * Description  :        variable returns for what the pelts
 *                       short desc will be
 * Returns      :        string - the short desc
 */
public string
pelt_short()
{
    switch(Pelt)
    {
        case 1:
            return "brown fox pelt";
            break;
        case 2:
            return "grey bobcat pelt";
            break;
        case 3:
            return "black badger pelt";
            break;
        default:
            return "small animal pelt";
            break;
    }
} /* pelt_short */

