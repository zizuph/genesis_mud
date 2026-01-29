
/*
 * Sporos seed vial
 * No value
 * Only used for mandala creation
 *
 */
 
inherit "/std/object";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void create_object() 
{
    set_name(({"Sporos seed vial","sporos seed vial","seed vial","vial"}));
    set_short("Sporos seed vial");
    set_long("It is a Sporos seed vial.\n");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_M_NO_SELL,1);
}

public string
query_auto_load()
{
    return MASTER + ":";
}
