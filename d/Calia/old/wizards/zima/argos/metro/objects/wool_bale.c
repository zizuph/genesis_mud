/* ARGOS - Metro - A bale of wool obtained by shearing a sheep using
**         the sheep shears (objects/sheep_sheers)
**         May be taken to wool works (rooms/woolwrk) and turned into
**         yarn, cloth, etc.
**
*/
inherit "/std/object";
#include <stdproperties.h>
#include "defs.h"
 
void create_object() {
   set_name("wool");
   add_name(({"bale","bale of wool",ARGOS_WOOL}));
   set_short("bale of wool");
   set_pshort("bales of wool");
   set_long(
      "It is a very large wad of wool recently sheared from a sheep. "+
      "It could be spun into yarn.\n");
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME, 3000);
   add_prop(OBJ_I_VALUE,  20);
}
