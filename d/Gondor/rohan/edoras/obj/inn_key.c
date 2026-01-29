inherit "/std/key";

#include "/d/Gondor/defs.h"

void
create_key()
{
  ::create_key();
  set_long(BSN("This is a large iron key. You wonder into which lock it might fit."));
  set_adj("iron");
  set_pshort("iron keys");
  set_key("_sleeping_stallion_key");
  add_name("_sleeping_stallion_key");
}
