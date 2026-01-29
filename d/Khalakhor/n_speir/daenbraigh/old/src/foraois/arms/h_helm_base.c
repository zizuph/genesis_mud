/*
 *
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/armour";

int ac,
   *am,
    weight,
    volume;

public void
create_helm(string adj, string material)
{
    if (material == "leather")
    {
        ac = 4 + random(2); // max 6
        am = ({0,0,0});
        volume = 1500;
    }
    else if (material == "hardened leather")
    {
        ac = 7 + random(2); // max 9
        am = ({0,0,0});
        volume = 2000;
    }
    else if (material == "iron")
    {
        ac = 12 + random(2); // max 14
        am = ({0,0,0});
        volume = 2000;
    }
    else if (material == "steel")
    {
        ac = 16 + random(3); //max 19
        am = ({0,0,0});
        volume = 2500;
    }

// based on material - type, AC and modifiers
    set_at(A_HEAD);
    set_ac(ac); 
    set_am(am);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac));

    set_adj(adj);
    add_adj(material);
    set_name("helm");
    add_name("armour");
    
    set_short( adj + " " + material + " helm");
    set_pshort( adj + " " + material + " helms");

    set_keep(1);

    add_prop(OBJ_I_VOLUME, volume);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac));
}
