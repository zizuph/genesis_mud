/*   wheel.c
 *
 * An old steering wheel, used to be attached on
 * the stick on the quarter-deck.
 *
 * Baldacin@Genesis, July 2003
 */
inherit "/std/object";
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
    set_name("wheel");
    add_name("shipwreck_wheel_");
    set_adj("old");
    add_adj("steering");
    set_short("old steering wheel");                    
    set_long("A wheel that controls the steering of a ship.\n");

    add_prop(OBJ_I_SHIPWRECK_EQUIPMENT, 1);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VALUE, 10);
    
}
