/* This key is for the door to the cavern on dungeon level three.
 */

inherit "/std/key";

#include "../defs.h"

create_key()
{
   ::create_temple_room();

     set_short("large iron key");
   set_long("This key is made of black iron and is quite large and " +
       "heavy.\n");

   set_key("cavern_key");
}
