inherit "/std/key";

#pragma strict_types
#include <stdproperties.h>

void
create_key() 

{

   set_adj("thin");
   add_adj("iron");
   set_long("This is a thin iron key. It looks as though it would fit " +
       "a small lock.\n");
   set_key("FOOTLOCKER_KEY_ID");
}
