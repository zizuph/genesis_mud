/*   shard.c
 *
 *  A small glass shard.
 *
 * Baldacin@Genesis, Dec 2003
 */
 
inherit "/std/object";
#include "../ldefs.h"
#include <stdproperties.h>
#include <macros.h>
 
void
create_object() 
{
    set_name("shard");
    set_adj("small");
    add_adj("glass");
    set_long("A small shard of glass, you have no idea where it come from "+
    "but it sure is sharp-edged.\n");
 
    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,  20);
    add_prop(OBJ_I_VALUE, 0);
}