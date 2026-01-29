/* Crystalline doors, of the Palace of Caliana.

   Coded by Glykron.

   History: 
          16/5/95     change other door                  Maniac
*/

inherit "/std/door";
#include <stdproperties.h>
#define SOUTH_CONNECT "/d/Calia/mountain/croad/croad27"
#include "defs.h"

void
create_door()
{
    ::create_door();
    set_door_name( ({ "door", "doors", "crystalline door", "crystalline doors"
        }) );
    set_door_desc("Two solid crystalline doors.\n");
    set_door_id("crystalline_door");
    set_other_room(SOUTH_CONNECT);
    set_pass_command( ({ "out", "south", "s" }) );
    set_fail_pass("The doors are closed.\n");
    set_pick(49);
    set_open(0);
    set_open_desc("There are crystalline double doors leading south out of " +
	"the palace.\n");
    set_open_command("open");
    set_open_mess( ({ "opens the crystalline doors.\n",
	"The crystalline doors open.\n" }) );
    set_fail_open( ({ "The doors are already open.\n",
	"The doors are locked.\n" }) );
    set_closed_desc("There are crystalline double doors leading south which " +
	"are closed.\n");
    set_close_command("close");
    set_close_mess( ({ "closes the crystalline doors.\n",
	"The crystalline doors close.\n" }) );
    set_fail_close("The doors are already closed.\n");
    set_locked(0);
    set_lock_name("lock");
    set_lock_desc("The lock is large and made from crystal.\n");
    set_lock_command("lock");
    set_lock_mess( ({ "locks the crystalline doors.\n",
	"The crystalline doors lock.\n" }) );
    set_fail_lock( ({ "The doors are already locked.\n",
	"The doors are open.\n" }) );
    set_unlock_command("unlock");
    set_unlock_mess( ({ "unlocks the crystalline doors.\n",
	"The crystalline doors unlock.\n" }) );
    set_fail_unlock("The doors are already unlocked.\n");
    set_key(CRYSTALLINE_KEY);
    add_prop(DOOR_I_HEIGHT, 300);
}
