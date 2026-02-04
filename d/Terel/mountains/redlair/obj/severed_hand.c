/* Key to unlock the Red Dragon Lair Cell of the 
 * nororious Hand assassins guild.
 *
 * The hand is set to decay around 2000 seconds or 33 minutes
 *
 * Tomas  -- May 2000
 *
 * Modificiation Log:
 *
*/


inherit "/std/key";

#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

int do_alarm();
int do_decay();

create_key()
{
  set_short("severed bloody hand");
  set_pshort("bloody hands");
  set_adj(({"severed","bloody"}));
  set_long("Its a severed bloody hand. You notice " +
     "a tattoo in the middle of the palm.\n");
  add_item(({"tattoo","palm"}),"The palm of the " +short()+ 
     " has been marked with a tattoo depicting a key.\n");
  add_name("hand");
  add_name("terel:severed_hand");
  add_prop(OBJ_M_NO_BUY,1);
  do_alarm();
}

int
do_alarm()
{
  set_alarm(2000.0, 10.0, do_decay);
  return 0;
}

int 
do_decay()
{
        tell_room(ETO, "The " + short() + " disolves " +
            "into dust falling between your fingertips.\n");
         TO->remove_object();
}