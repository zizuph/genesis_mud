
/*
 * Anointing Oil
 * No value
 * Only used for ceremonies
 *
 */
 
inherit "/std/object";

#include <formulas.h>
#include <stdproperties.h>
 
void create_object() 
{
    set_name(({"anointing oil","oil"}));
    set_adj("anointing");
    set_short("anointing oil");
    set_long("It is anointing oil used for ceremonial purposes.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_SELL,1);
}
