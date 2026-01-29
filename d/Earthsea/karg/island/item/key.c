inherit "/std/key";

#include <stdproperties.h>

#include "defs.h"

void create_key()
{
 ::create_key();
 set_name("key");
 set_adj("massive");
 add_adj("rusty");
 set_long("This is very rusty key. It looks massive and very heavy.\n");

 add_prop(OBJ_I_WEIGHT,2000);
 add_prop(OBJ_I_VOLUME,2000);

 set_key(TENT_KEY_ID);
}

