/* Centaur sculpture to go on mount Kyrus.
   Coded by Maniac, 14.9.95
*/

inherit "/std/object";
#include <stdproperties.h>
#include "obj.h"

string
centaur_long()
{
    seteuid(getuid());
    cat(MOUNTAIN_TEXTS+"centaur"); 
    return "";
}


void
create_object()
{
     set_name("sculpture");
     add_name("centaur");
     set_adj("winged");
     set_short("sculpture of a winged centaur");
     set_long("@@centaur_long");
     add_prop(OBJ_I_WEIGHT, 1000000);
     add_prop(OBJ_I_VOLUME, 1000000);
     add_prop(OBJ_M_NO_GET, "The sculpture is much too heavy.\n");
}

