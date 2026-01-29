/* 
 *  This is a crate that will contain items for a quest.
 *  More detail to be added after the quest is coded.
 *
 *  Raymundo, April 2020
 */

#pragma save_binary
#pragma strict_types

inherit "/std/container";


#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/tharbad/trail/defs.h"


void
create_container()
{
    FIX_EUID;
    
    object comp;

    add_prop(CONT_I_WEIGHT,     10000);     /* This is the entire container. */
    add_prop(CONT_I_VOLUME,       10000);   /* Max 50 dm^3 internal volume.  */
    add_prop(CONT_I_MAX_WEIGHT, 400000);   /* Can max hold  */
    add_prop(CONT_I_MAX_VOLUME,   400000);   /* Volume of box + content.  */
    add_prop(CONT_I_RIGID,            1);   /* This is a rigid container.*/
    add_prop(OBJ_I_NO_GET,            1);   /* Can't get it.*/
    add_prop(CONT_I_TRANSP,           1);   /* Transparent.*/
    set_no_show_composite(1);               /* Don't see it in room desc. */

    set_name("box");
    add_name("boxes");
    add_adj("wooden");
    add_adj("open");
    set_long("This box looks like the type of box that is typically stored "
        + "on boats as they move freight along the river. It's made of wood "
        + "and is scuffed and scratched in such a way that it is obvious "
        + "this box has been used often.\n");
    
    add_object( (TRAIL_OBJ + "brandy_bottle"), (1 + random(3)));
    enable_reset();
 
    reset_object();

}

