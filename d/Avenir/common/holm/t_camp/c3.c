/* file name:        /d/Avenir/common/holm/t_camp/c3.c
 *  creator(s):      (Rangorn , Feb 97)
 *  revisions:
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

object door, other;

string 
cage_view()
{
    object *inv, *live, *dead, room;
    int i;
 
    inv = ({ });
    for (i = 0; i < sizeof(CAGE1); i++)
        if ((room = find_object(CAGE1[i])))
            inv += all_inventory(room);
 
    if (inv && sizeof(inv) > 0) 
    {
        live = FILTER_LIVE(inv);
        live = FILTER_CAN_SEE(live, TP);
        dead = FILTER_DEAD(inv);
        dead = FILTER_CAN_SEE(dead, TP);

        if (sizeof(live) > 0 && sizeof(dead) > 0)
            return COMPOSITE_LIVE(live) + ", as well as "+ 
                   COMPOSITE_DEAD(dead) +" in the cage.";
        else if (sizeof(live))
            return COMPOSITE_LIVE(live) +" in the cage.";
        else if (sizeof(dead))
            return COMPOSITE_DEAD(dead) +" in the cage.";
    }
    return "that the cage is empty, yet it reeks of both fear and menace.";
}

/* Now create the room.  */
void
create_camp_room()
{
    set_short("Cage in northwest part of camp");
    set_long("You have reached a junction in the northwestern part of the " +
           "camp. A huge cage is standing here. It is very sturdy " +
           "and the steel bars of the cage appear very well made, " +
           "as if it is meant to imprison something very big and very "+
           "dangerous. You can see @@cage_view@@\n");

    add_exit("c2", "southwest", 0);
    add_exit("c10", "west", 0); 
    add_exit("c12", "north", 0);
    add_exit("c7", "east", 0);
    /* So we can hear shouts from the cage */
    add_exit("cage1", "under", 1, 1, 1);
    
    add_ground(); 

    add_item(({"cage"}),
             "A large cage which is made up of a wooden roof and sturdy " +
             "steel bars that have been fastened directly into the " + 
             "bedrock. You notice that the cage door has a simple " + 
             "locking mechanism. You can see @@cage_view@@\n");
  
    add_item(({"bars", "steel bars"}),
             "Finely crafted steel bars about 4 inches in diameter.\n");

    door = clone_object(HOLM_OBJ + "cagedoor_a");
    door->move(TO);
    other = "/d/Avenir/common/holm/t_camp/cage1"->load_it();
}

void
lockup()
{
    if (door->query_locked() == 0)
    {
        door->auto_close_door();   
        tell_room(this_object(),
            "The flat iron grill swings closed. You hear "+
            "the lock click.\n");
    }
}
