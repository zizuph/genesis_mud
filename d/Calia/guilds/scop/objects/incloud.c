
/* A cloud of incense which fills the chapel during ceremonies.
 *
 */
 
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER

create_object()
{
    set_name(({"incense",INCENSE_CLOUD,"cloud"}));
    set_short("cloud of incense");
    set_long("It is a smoky cloud of incense, streaming from the silver censor, "+
        "filling the chamber with its bitter-sweet aroma.\n");
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_GIVE,1);
    add_prop(OBJ_M_NO_GET,1);
}
