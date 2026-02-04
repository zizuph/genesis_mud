inherit "/std/room";
     
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"

/*
 * The player should only be able to lock the door from the outside
 */

init()
{
     ::init();
     add_action("do_lock", "lock");
     add_action("do_unlock", "unlock");
}

void
create_room()
{
    object door;
    
    set_short("Just inside tomb");
    set_long(BSN(
        "You brave the shadows which seem to to linger strangely " +
	"about the water-worn stones and make your way into the tomb.  " +
	"You are immediately overcome by the sickening stench of decay. " +
	"Damp stone steps lead downward into darkness."
    ));

    add_item(({"steps", "stone steps"}), BSN(
        "The damp stone steps are made of the same ancient granite as " +
	"the rest of the tomb.  The lead downwards into the black recesses " +
        "of the earth."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    door = clone_object(TOMBDIR + "tomb_door2");
    door->move(TO);
    door->set_key(TOMB_DOOR_KEY);
    
    add_exit(TOMBDIR + "under_tomb01", "down", "@@go_down");
    add_exit(TOMBDIR + "tomb_ent", "back", 0);
}

go_down()
{
     int tp_dis;

     tp_dis = (TP->query_stat(SS_DIS));

     if (tp_dis < 75) {
	  write(BSN(
	      "You are too afraid to descend the steps.  Perhaps you " +
	      "should return here when you are more disciplined."
	  ));
	  say(QCTNAME(TP)+" starts to go down the stairs but chickens out.\n");
	  return 1;
     }

    return 0;
}

/*go_down()
{
     write("The tomb area is still under construction.\n" + 
           "Come back later if you dare!\n");
     return 1;
}*/

do_lock(string str)
{
     notify_fail("Lock what?\n");
     if ((str == "door") || (str == "padlock")) {
	  write("You can't do that.  The lock is on the other side!\n");
	  return 1;
     }
     return 0;
}

do_unlock(string str)
{
     notify_fail("Unock what?\n");
     if ((str == "door") || (str == "padlock")) {
	  write("You can't do that.  The lock is on the other side!\n");
	  return 1;
     }
     return 0;
}
