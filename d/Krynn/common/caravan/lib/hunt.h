
/*
 *  Filename:       hunt.c
 *  Description:    A hunt library to be inherited for hunting players
 *
 *
 *  Copyright (c) Nov. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Most of the code taken from the attackdragon originally from neraka.

 *  Change log:
 */
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>

inherit "/std/act/domove";
inherit "/std/act/trigaction";
inherit "/std/act/attack";


object *gHunted = ({ });
object hunter;
int gHaveSetTrigger = 0;

/*
 * Function name: do_hunt_special
 * Description:   prototype, can be filled if one wants something
 *                special setup if the opponent flees.
 * Arguments:     none.
 */


void do_hunt_special(object hunted, object attacker);

int
set_hunting(object ob)
{
//    DEBUG_MSG("in set_hunting");
    if(!ob)
        return 0;

    if (!gHaveSetTrigger)
        trig_new("%s 'leaves' / 'sneaks' / 'panics' [and] [flees] [limping] %w",
        "react_leave");
    gHaveSetTrigger = 1;
    if (member_array(ob, gHunted) == -1)
    {
//        DEBUG_MSG("added someone to hunt");
        gHunted += ({ ob });
    }
    gHunted -= ({ 0 });
    return 1;
}

int set_hunting_name(string name, object ob)
{
    hunter = ob;
    return set_hunting(find_player(name));
}

void
do_follow_player(object ob, string cmd)
{
    object room;

//    DEBUG_MSG("in follow player");
    if (!objectp(ob))
        return;

    room = environment(ob);
    if (!objectp(room))
        return;

    if (room->query_prop(ROOM_I_INSIDE))
         return;

    this_object()->command(cmd);
    set_alarm(0.0, 0.0, &do_hunt_special(ob, hunter));
}

void
react_leave(string name, string dir)
{
    object tone;

//    DEBUG_MSG("in react_leave");
    tone = find_player(lower_case(name));
    if(!tone)
    {
        return;
    }
    if(member_array(tone,gHunted) != -1)
    {
        dir = extract(dir,0,-3);
        set_alarm(0.0, 0.0, &do_follow_player(tone, dir));
        return;
    }
}
