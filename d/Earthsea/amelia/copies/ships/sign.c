#pragma save_binary

inherit "/std/object";

#include "/d/Roke/common/defs.h"

create_object()
{
  set_name("sign");
  set_adj("green");

  set_short("sign");
  set_long("It reads:\n"+
           "This is where the ship to Re Albi lands.\n"+
           "The fare is 24 cc, except for newbies who\n"+
           "ride for free. (But they still have to 'buy' it.)\n");

  add_prop(OBJ_M_NO_GET, "This sign will stay here!\n");

}

