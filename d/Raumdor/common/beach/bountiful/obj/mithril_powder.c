/*  /d/Raumdor/common/beach/bountiful/obj/mithril_powder.c
 *
 *  Crate supply item.
 *
 *  Nerull, 2021
 *
 */


inherit "/std/object";
#include "../defs.h";
#include <stdproperties.h>
#include <macros.h>


void
create_object()
{
    set_name("_pinch_of_mithril_powder");
    add_name("powder");
    add_name("pinch");
    add_name("pinch of powder");
    add_name("pinch of mithril powder");
    
    set_short("pinch of mithril powder");
    set_pshort("pinches of mithril powder");
    
    set_long("Judging by the looks of this fine grained "
    +"powder, you think it's pure mithril.\n");
    
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 12000);
}