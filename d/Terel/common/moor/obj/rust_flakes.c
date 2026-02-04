// It is a component needed for making thermite for
// the cottage chest quest.

inherit "/std/object";
#include <stdproperties.h>

void
create_object()
{
     set_name(({"rust","flake","is_ironoxide"}));
     set_short("rust flake");
     set_adj("rust");
     set_long("A large flake of reddish-brown rust.\n");

     add_prop(OBJ_I_WEIGHT, 10);
     add_prop(OBJ_I_VOLUME, 2);

}
     
