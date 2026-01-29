
#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_container()
{
    /* This compartment is suposed to be invisible and only accessable
     * under the propper circumstances.
     */

    object comp;

    add_prop(CONT_I_WEIGHT,     10000);     /* This is the entire container. */
    add_prop(CONT_I_VOLUME,       10000);   /* Max 50 dm^3 internal volume.  */
    add_prop(CONT_I_MAX_WEIGHT, 400000);   /* Can max hold  */
    add_prop(CONT_I_MAX_VOLUME,   400000);   /* Volume of box + content.  */
    add_prop(CONT_I_RIGID,            1);   /* This is a rigid container.*/
    add_prop(OBJ_I_NO_GET,            1);   /* Can't get it.*/
    add_prop(CONT_I_TRANSP,           1);   /* Transparent.*/
    set_no_show_composite(1);               /* Don't see it in room desc. */

    set_name("under the leaves");

    set_long("A hidden spot under the leaves.\n");

}
