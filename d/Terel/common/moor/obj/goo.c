// when mixing in the flower pot goes wrong.
inherit "/std/object";
#include <stdproperties.h>

void
create_object()
{
     set_name("goo");
	 add_name("mess");
	 set_adj("gooey");
     set_short("gooey mess");
     set_long("This is a mess of goo. You're not sure it is safe "+
         "to handle.\n");

     add_prop(OBJ_I_WEIGHT, 10);
     add_prop(OBJ_I_VOLUME, 2);
     add_prop(OBJ_M_NO_DROP, 0);

}
     
