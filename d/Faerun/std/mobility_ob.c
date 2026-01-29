/* 
   This is a mobility object added to players
   who are in water rooms by the drown object. 
   It prevents players who cannot swim from making 
   easy progress from room to room.  
   The reason we must have this as a separate object is that
   we have to update the trap action on each move that the player 
   makes, so that the room exit actions do not take precedence. 
   Updating the actions of the drown object each time would 
   be wasteful. 

   Copyright Miguel Leith 1996
*/ 

inherit "/std/object"; 

#include "/d/Faerun/defs.h"
#include "/d/Faerun/sys/water.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

void
create_object()
{
    set_short(MOBILITY_OBJECT_NAME);
    set_long(MOBILITY_OBJECT_NAME);
    set_name(MOBILITY_OBJECT_NAME);
    /* so player won't see in inventory */
    set_no_show();
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_M_NO_INS, 1);
}


/* Players trying to move through water with no swim skill
   are going to have problems. */

int
trap_move(string str)
{
    object tp = this_player();
    string v = query_verb();

    if ((tp->query_skill(SS_SWIM) == 0) &&
        (IN_DEEP_WATER(tp) || UNDER_WATER(tp)) &&
        (member_array(v, environment(tp)->query_exit_cmds()) > -1) &&
         random(4)) {
        tp->catch_msg("You try to scramble through the " +
                      "water but fail dismally! Try again.\n");
        tell_room(environment(tp),
                  QCTNAME(tp) + " tries to scramble through " +
                  "the water but fails dismally!\n", tp);
        return 1;
     }
     return 0;
}


void
init()
{
    ::init(); 
   /* trap commands for player trying to swim */
    add_action(trap_move, "", 1);
}
