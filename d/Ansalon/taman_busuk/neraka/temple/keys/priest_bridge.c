/* This key goes to the door between the priests area on level 2 and the
 * stonebridge in the Great Hall of Audience.
 */

inherit "/std/key";

#include "../defs.h"

create_key()
{
   ::create_temple_room();

     set_short("delicate key");
   set_long("This key is made of black iron and even though it has quite " +
       "a delicate appearance you find it to be quite heavy. It is shaped " +
       "as a dragons claw.\n");

   set_key("priest_bridge_key");
}
