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
    add_prop(CONT_I_WEIGHT,      100000);   /* This is the entire ruins. */
    add_prop(CONT_I_VOLUME,         500);   /* Max 50 dm^3 internal volume.  */
    add_prop(CONT_I_MAX_WEIGHT,  200000);   /* Can max hold 5 Kg. */
    add_prop(CONT_I_MAX_VOLUME,     600);   /* Volume of box + content.  */
    add_prop(CONT_I_RIGID,            1);   /* This is a rigid container.*/
    add_prop(OBJ_I_NO_GET,            1);   /* Can't get it.*/
    add_prop(CONT_I_TRANSP,           1);   /* Transparent.*/
    set_no_show_composite(1);               /* Don't see it in room desc. */
    set_name("metal box");
    add_name("box");
    set_short("metal box");
    set_long("This is a small metal box that has been left wedged " +
        "amongst the stone blocks of the ruins.\n");
}