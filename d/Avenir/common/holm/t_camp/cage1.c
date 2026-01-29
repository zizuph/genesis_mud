/* file name:        /d/Avenir/common/holm/t_camp/cage1.c
 *  creator(s):      (Rangorn, Feb 97)
 *  revisions:        Lilith Sept 97
 *  purpose:
 *  note:
 *  bug(s):
 *  to-do:
 */

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/t_camp/camp_base";

/* Include the local area defines, etc */
#include "camp.h"
#include <filter_funs.h>
#include <composite.h>

object door;

string 
camp_view()
{
    object *inv, *live, *dead, room;
    int i;
 
    inv = ({ });
    for (i = 0; i < sizeof(ROOM1); i++)
        if ((room = find_object(ROOM1[i])))
            inv += all_inventory(room);
 
    if (inv && sizeof(inv) > 0) 
    {
        live = FILTER_LIVE(inv);
        live = FILTER_CAN_SEE(live, TP);
        dead = FILTER_DEAD(inv);
        dead = FILTER_CAN_SEE(dead, TP);

        if (sizeof(live) > 0 && sizeof(dead) > 0)
            return COMPOSITE_LIVE(live) + ", as well as "+ 
                   COMPOSITE_DEAD(dead);
        else if (sizeof(live))
            return COMPOSITE_LIVE(live);
        else if (sizeof(dead))
            return COMPOSITE_DEAD(dead);
    }
    return "that this area of the camp is fairly empty";
}

/* Now create the room.  */
void
create_camp_room()
{
    set_short("cage in the troloby camp");
    set_long("A large cage which is made up of a wooden roof and "+
        "sturdy steel bars that have been fastened directly into the "+ 
        "bedrock. You can see @@camp_view@@ beyond the bars of "+
        "this cage.\n");

    /* So we can hear shouts from the next room */
    add_exit("c3", "qw", 1, 1, 1);
    
    add_item(({"cage"}), query_long());
  
    add_item(({"bars"}),
             "Finely crafted steel bars about 4 inches in diameter.\n");
    door = clone_object(HOLM_OBJ + "cagedoor_b");
    door->move(TO);
}

void
lock_up()
{

    if (door->query_locked() == 0)
    {
        call_other(T_CAMP+"c3", "lockup");
        door->reset_door();
        tell_room(this_object(), "The iron grill swings closed. You hear the lock "
          + "click.\n");
    }
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (living(ob))
        set_alarm(3.0, 0.0, "lock_up");
    return;
}

void load_it() { /* empty function */ }
