/*  /d/Raumdor/common/beach/bountiful/chest_rewards/c_globe.c
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
    set_name("globe");

    set_adj("crystal");
    add_adj("snow");

    set_short("crystal snow globe");
    set_pshort("crystal snow globes");
    
    set_long("The thick heavy base allows this to rest "
    +"easily upon any flat surface and but also cumbersome "
    +"enough to deter children from picking it up. Once shook, "
    +"the snow will fly around a small run down neighborhood. "
    +"Various people walk about inside.\n");
    
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 11000);
}