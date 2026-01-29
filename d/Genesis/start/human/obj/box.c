#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>

void
create_container()
{
    /* This is a wooden box, 0.8 m high and 1 m on the inside.
     * The sides are made of 3 cm thick wood which gives the box a
     * total (rigid) volume of 0.92 m^3. The internal volume will be
     * 0.8 m^3. Thus the wood itself has a volume of 0.126 m^3.
     * The density of this wood is 800Kg/m^3, giving the empty box 
     * a weight of 100.8 Kg. Let's just say 100. Kg. :)
     * In short, people should not carry the box around... 
     */

    add_prop(CONT_I_WEIGHT,      100000);   /* Empty box weighs 100 Kg.  */
    add_prop(CONT_I_VOLUME,      800000);   /* Max 0.8 m^3 internal volume.  */
    add_prop(CONT_I_MAX_WEIGHT, 1000000);   /* The box can max hold 1000 Kg. */
    add_prop(CONT_I_MAX_VOLUME,  920000);   /* Volume of box + content.  */
    add_prop(CONT_I_RIGID,  	      1);   /* This is a rigid container.*/
    add_prop(OBJ_I_NO_GET,  	      1);   /* Can't get it.*/
    add_prop(CONT_I_TRANSP,  	      1);   /* Transparent.*/

    set_name("charity box");
    add_name("box");
}
