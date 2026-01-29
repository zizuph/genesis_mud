/******************************************************
 *  Solamnic gauntlets for The Death Knights of Krynn *
 *  By Elmore, April - 2001                           *
 ******************************************************/

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../../local.h"

void
create_armour()
{
    set_name("gauntlets");
    add_name(DKNIGHT_ARMOUR);
    set_ac(35);
    set_at(A_HANDS);
    set_am( ({ 10, 10, 3 }) );
    set_adj("blackened");
    add_adj("solamnic");
    set_short("pair of blackened solamnic gauntlets");
    set_long("This is a pair of solamnic gauntlets, made from hardened "+
             "steel and covered with beautiful ornate covering the "+
             "surface. This piece of armour however seems to have been "+
             "thrown into a fire. The once flawless steel has been "+
             "charred black.\n"); 

    add_prop(OBJ_I_VOLUME, 2550);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(35, A_HANDS));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35));
}
