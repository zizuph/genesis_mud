
/*
 * Sporos crystalline seed vial
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
    set_name(({"Sporos crystalline seed vial","sporos crystalline seed vial",
    	"crystalline seed vial","seed vial","vial","crystalline vial"}));
    set_short("Sporos crystalline seed vial");
    set_long("It is a Sporos crystalline seed vial.\n");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_M_NO_SELL,1);
}

public string
query_auto_load()
{
    return MASTER + ":";
}
