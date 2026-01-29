inherit "/std/key";

#include "../defs.h"
#include <stdproperties.h>

public void
create_key()
{
   set_name("key");
   add_name("_sheepkey_thwil_");
   set_adj("hairy");
   
   set_short("hairy key");
   set_long("This is a very old rather rusty key covered in white hair.\n");
   
   set_key(HAIRY_KEY);
}
