/*   rope.c
 *
 * A strong rope
 *
 * Baldacin@Genesis, Aug 2003
 */
inherit "/std/rope";
#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>

void
create_rope()
{
    set_name("rope");
    set_adj("strong");
    set_short("strong rope");
    set_long("A strong rope made of good material.\n");
    
    add_prop(OBJ_I_SHIPWRECK_EQUIPMENT, 1);
    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VALUE, 35);
}
