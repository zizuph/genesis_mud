/*
 * bracers_base.c
 *
 * Base object for a variety of different bracers to
 * save a bit of cut'n'pasting.
 *
 * Khail - August 12, 1997
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/armour";

int ac,
    weight,
    volume;

public void
create_bracers(string material)
{
    set_name("bracers");
    set_pname("bracers");
    set_at(A_ARMS);
    set_keep(1);
    set_af(TO);
    set_adj(material);

    if (material == "leather")
    {
        ac = 5;
        weight = 250;
        volume = 2000;
    }
    else if (material == "hardened leather")
    {
        ac = 8;
        weight = 400;
        volume = 2000;
    }
    else if (material == "ringmail")
    {
        ac = 17;
        weight = 600;
        volume = 2000;
    }
    else if (material == "scale mail")
    {
        ac = 19;
        weight = 1900;
        volume = 2000;
    }
    else
    {
        ac = 5;
        weight = 1000;
        volume = 2000;
    }

    add_name("pair of " + material + " bracers");
    add_name("pair of bracers");
    add_pname("pairs of " + material + " bracers");
    add_pname("pairs of bracers");
    set_short("pair of " + material + " bracers");
    set_pshort("pairs of " + material + " bracers");
    
    set_ac(ac);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac));
    add_prop(OBJ_I_WEIGHT, weight);
    add_prop(OBJ_I_VOLUME, volume);
}
