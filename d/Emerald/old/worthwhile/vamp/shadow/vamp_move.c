/* vamp_move.c created by Shiva@Genesis.
 * This file contains code related to a vampire movement
 * This is part of the vampire guild shadow
 */

/* autosneak code from the ranger guild, written by ??? */

#include "../guild.h"
#include "../voptions.h"

#include <stdproperties.h>

#define SW shadow_who

/* 
 * Function name: move_living
 * Description:   As move_living() in /std/living.c, but checks
 *                to see if this vampire is autosneaking, and takes
 *                the appropriate actions if so.
 * Arguments:     As move_living() in /std/living.c
 * Returns:       As move_living() in /std/living.c
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int hiding, retval, val, bval, did_sneak;
    int autosneak_on = query_vamp_option(VOPT_PROWL);
  
    if (autosneak_on && !SW->query_prop(LIVE_I_SNEAK) && query_verb() &&
        !(SW->query_prop(OBJ_I_LIGHT) && (SW->query_prop(OBJ_I_LIGHT) >
        environment(SW)->query_prop(OBJ_I_LIGHT))) &&
        !(objectp(SW->query_attack())))
    {
        hiding = environment(SW)->query_prop(ROOM_I_HIDE);
        bval = SW->query_skill(SS_SNEAK) * 2 + SW->query_skill(SS_HIDE) / 3;
        bval = (bval - hiding) / 2;
     
        if (hiding >= 0 && bval > 0)
        {
            val = bval + random(bval);
            SW->add_prop(OBJ_I_HIDE, val);
            SW->add_prop(LIVE_I_SNEAK, 1);
            did_sneak = 1;
        }
    
        if (!did_sneak)
        {
            tell_object(SW, "You failed to sneak.\n");
        }
    }
  
    retval = SW->move_living(how, to_dest, dont_follow, no_glance);
  
    if (!retval && (how != "X"))
    {
        add_thirst_random(35);
    }
  
    if (!did_sneak)
    {
        return retval;
    }
   
    hiding = environment(SW)->query_prop(ROOM_I_HIDE);
    bval = SW->query_skill(SS_HIDE);
    bval = (bval - hiding) / 2;
   
    set_this_player(SW);
    if (hiding < 0 || bval <= 0)
    {
        write("It's too difficult to hide in here, you're visible again.\n");
        SW->reveal_me(0);
    }
    else if ((SW->query_prop(OBJ_I_LIGHT) > 0) &&
        (SW->query_prop(OBJ_I_LIGHT) >
        environment(SW)->query_prop(OBJ_I_LIGHT)))
    {
        write("You can't hide here, shining like that!\n");
        SW->reveal_me(1);
    }
   
    val = bval + random(bval);
    SW->add_prop(OBJ_I_HIDE, val);
    return retval;
}
