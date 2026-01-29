inherit "/std/key";
#include "/d/Krynn/icewall/local.h"

create_key() 
{
   ::create_key();
   set_name("key");
   set_short("large engraved key");
   set_adj("large");
   add_adj("engraved");
   set_pshort("Large iron keys");
   set_long("It is a large key made from an unknown material. It has a picture\n"
      + "of a dragon engraved on it.\n");
   
   set_key(MASKEY);
}
