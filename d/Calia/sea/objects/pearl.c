
/*
 *  Coded by Amelia, 
 * 
 *  Modifications by Maniac 9/9/96
 *  It's one of the non-special pearls that can be found in oysters
 *  in the mermaid quest. 
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("pearl");
    set_adj("white");
    add_adj("lustrous");
    set_short("lustrous white pearl");
    set_pshort("lustrous white pearls");
    set_long("You can't believe your good luck! "+
        "This is a beautiful, lustrous white pearl, "+
        "about the size of your thumbnail.\n");
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_WEIGHT, 10);
}

