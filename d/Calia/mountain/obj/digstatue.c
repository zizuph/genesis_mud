 /* Digit 01 FEB 95 */

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Calia/mountain/defs.h"


create_object()
{
    set_name("statue");
    set_short("statue");
    set_long("The statue is carved out of crystalline and is facing the "+
       "land below, almost as if it were watching over it and protecting "+
       "it from danger.  It is an average sized female human attired in a long "+
       "flowing robe.  You get a feeling of awe just looking at her.\n");
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_M_NO_GET,1);
}
