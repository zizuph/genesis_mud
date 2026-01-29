inherit "/std/key";

#include <stdproperties.h>

#include "defs.h"

void create_key()
{
 ::create_key();
 set_name(PLAN_KEY_ID);
 add_name("key");
 set_adj("small");
 add_adj("crystal");
 set_short("small crystal key");
 set_long("This is small key. It seems to be made of some kind of "+
   "crystal.\n");

 add_prop(OBJ_I_WEIGHT,2000);
 add_prop(OBJ_I_VOLUME,2000);
 add_prop(OBJ_M_NO_STEAL,1);

 set_key(PLAN_KEY_ID);
}

