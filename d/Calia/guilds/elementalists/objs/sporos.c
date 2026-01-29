
/*
 * Sporos
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
    set_name(({"Sporos","sporos"}));
    add_name("_completed_sporos_");
    set_short("Sporos");
    set_long("It is a Sporos. It is a small seed that is growing and "+
        "shrinking in a constant pattern, almost as if it were mimicking you "+
        "heartbeat.\n");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_M_NO_SELL,1);
}

public string
query_auto_load()
{
    return MASTER + ":";
}
