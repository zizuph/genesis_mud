inherit "std/object";
 
#include "/sys/macros.h"
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
 
 
void
create_object()
{
 
seteuid(getuid());
 
  set_name("sarcophagus");
  set_adj("stone");
  set_long("Its a stone sarcophagus, standing on a rock base, "
         + "but hardly big enough for anyone to hide behind. "
         + "On the left side of the sarcophagus is a big and "
         + "thick wax candle burning, giving the chamber both "
         + "light and an aura of peace and quietness. "
         + "The surface of the sarcophagus is so smoothe that "
         + "it's hard to belive it's made of stone. There is no "
         + "lid though, so you cannot open it to see what's inside.\n");
 
    add_prop(OBJ_I_WEIGHT, 500000);
    add_prop(OBJ_I_VOLUME, 500000);
}
