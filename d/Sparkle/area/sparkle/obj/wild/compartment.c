
#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_container()
{
    /* This compartment is suposed to be invisible and only accessable
     * under the propper circumstances.  /Styles.
     */

    object comp;

    add_prop(CONT_I_WEIGHT,     10000);     /* This is the entire chimney. */
    add_prop(CONT_I_VOLUME,       50000);   /* Max 50 dm^3 internal volume.  */
    add_prop(CONT_I_MAX_WEIGHT, 1000000);   /* Can max hold 1000 Kg. */
    add_prop(CONT_I_MAX_VOLUME,   60000);   /* Volume of box + content.  */
    add_prop(CONT_I_RIGID,  	      1);   /* This is a rigid container.*/
    add_prop(OBJ_I_NO_GET,  	      1);   /* Can't get it.*/
    add_prop(CONT_I_TRANSP,  	      1);   /* Transparent.*/
    set_no_show_composite(1);               /* Don't see it in room desc. */


    set_name("hidden compartment");
    add_name("compartment");

    set_short("compartment");
    set_long("It is a small hidden compartment in "+
	     "the back of the fireplace.\n");

}
