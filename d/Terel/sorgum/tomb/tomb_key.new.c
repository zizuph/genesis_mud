inherit "/std/key";

#include <stdproperties.h>

create_key()
{
     ::create_key();

     set_short("stone key");
     set_adj(({"iron", "heavy"}));
     set_long("It's a heavy key. It's made from stone.\n");
     set_name("tomb key.\n");
     add_name("key");
     add_prop(OBJ_I_VOLUME,  5);
	 add_prop(OBJ_I_WEIGHT, 5000);


}
