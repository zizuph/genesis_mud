
/*
 * Anointing Oil
 * No value, can't be taken outside of the temple
 * Only used for ceremonies in the temple
 *
 */
 
inherit "/std/object";

#include <formulas.h>
#include <stdproperties.h>

#include "defs.h"
#include SPIRIT_HEADER
 
void create_object() 
{
    set_name(({"anointing oil","oil"}));
    add_name(CEREMONIAL_GARB);
    set_adj("anointing");
    set_short("anointing oil");
    set_long("It is anointing oil used for ceremonial purposes.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_SELL,1);
}
