/*

    Modified: 6 May 2003, by Bleys
        - Commented out the lock & unlock actions. They
            belong in the door.

*/

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

    Not really, not anymore. This sort of thing should be handled
    by the door in question, in any event. Doing it in the room
    creates a situation where if the door changes it's easy to
    forget to change the room.

init()
{
     ::init();
     add_action("do_lock", "lock");
     add_action("do_unlock", "unlock");
}
*/

void
create_room()
{
    object door;

    set_short("Just inside tomb");
    set_long(
        "You brave the shadows which seem to linger strangely " +
    "about the water-worn stones and make your way into the tomb.  " +
    "You are immediately overcome by the sickening stench of decay. " +
    "Damp stone steps lead downward into darkness.\n"
    );

    add_item(({"steps", "stone steps"}),
        "The damp stone steps are made of the same ancient granite as " +
    "the rest of the tomb.  The lead downwards into the black recesses " +
        "of the earth.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);

    door = clone_object(TOMBDIR + "tomb_door2");
    door->move(TO);
    door->set_key(TOMB_DOOR_KEY);

    add_exit(TOMBDIR + "under_tomb01", "down", "@@go_down");
}

go_down()
{
     int tp_dis;
     object sorgum;

     tp_dis = (TP->query_stat(SS_DIS));

     if (tp_dis < 30) {
      write(
          "You are too afraid to descend the steps.  Perhaps you " +
          "should return here when you are more disciplined.\n"
      );
      say(QCTNAME(TP)+" starts to go down the stairs but chickens out.\n");
      return 1;
     }

     /*
      * Tell me when people enter the tomb area (if I am logged in).
      */

     sorgum = find_player("sorgum");
     if (sorgum)
     sorgum->catch_msg(TP->query_real_name() + " went downstairs in " +
               "the tomb.\n");
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
