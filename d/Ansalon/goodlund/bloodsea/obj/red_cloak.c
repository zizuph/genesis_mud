/*
 * What         : A heavy red cloak.
 * Used by      : Minotaur captain Corth, sailing the Bloodsea
 *                /d/Ansalon/goodlund/bloodsea/obj
 * Description  : A simple cloak 
 * Made by      : Cherek, Feb 2007
 */ 

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit "/std/armour";

int AC =  5;

void
create_armour()
{
    set_name("cloak");
    set_ac(AC);
    set_at(A_ROBE);
    set_adj("heavy");
    add_adj("red");
    set_short("heavy red cloak");
    set_long("A warm cloak made to protect against the rough " +
             "weather on the Bloodsea. \n");

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_ROBE)
             +500+random(1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4 + random(500));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC));
    
    seteuid(getuid(TO));

}
