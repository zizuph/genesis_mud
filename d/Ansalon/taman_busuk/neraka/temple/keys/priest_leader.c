/* This key goes to the door to the Nightlord or Nightlady's room.
 */

inherit "/std/key";

#include "../defs.h"

create_key()
{
   ::create_temple_room();

     set_short("silver key");
   set_long("This is a silver key fashioned as a vine with thorns on it.\n");

   set_key("priest_leader_key");
}
