/*  /d/Raumdor/common/beach/bountiful/chest_rewards/c_humidor.c
 *
 *  Money Drop Item - Common.
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
    set_name("humidor");
    set_adj("emerald");
    add_adj("trimmed");
    add_adj("onyx");

    set_short("emerald trimmed onyx humidor");
    set_pshort("emerald trimmed onyx humidors");
    
    set_long("A personal humidor finely crafted with an onyx veneer "
    +"and emerald trimmings. Inside is lined with thick velvet and "
    +"looks to hold twelve good sized cigars.\n");
    
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 10000);
}