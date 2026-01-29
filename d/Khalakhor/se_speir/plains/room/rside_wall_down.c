/* File         : /d/Khalakhor/se_speir/plains/room/rside_wall_down.c
 * Creator      : Darragh@Genesis
 * Date         : 01-03-02   
 * Purpose      : Temporary room for climbers
 * Related Files: 
 * Comments     :
 * Modifications:  
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "plains.h"

#define CLIMB_FATIGUE -90

inherit "/d/Khalakhor/se_speir/plains/room/tforbase";

int climb_down_1();
int climb_down_2();
int climb_down_3();
int climb_down_4();
int climb_down_5();
int climb_down_done();

int
climb_down_1()
{
    write("\nJust a few feet below the top, you take extra "
        + "care in planning your descent before continuing "
        + "downwards.\n\n");
    set_alarm(12.4,0.0,&climb_down_2());
    return 1;
}

int
climb_down_2()
{
    write("You are almost halfway down, but the ground below "
        + "seems so very far away.\n\n");
    set_alarm(7.7,0.0,&climb_down_3());
    return 1;
}

int
climb_down_3()
{
    write("With great effort and determination you climb down "
        + "the cliff, getting closer to the ground.\n\n");
    set_alarm(7.6,0.0,&climb_down_4());
    return 1;
}

int
climb_down_4()
{
    write("You are just a couple of feet above the ground, "
        + "nothing can go wrong now.\n\n");
    set_alarm(4.5,0.0,&climb_down_5());
    return 1;
}

int
climb_down_5()
{
    write("Your climb is at an end, and with a short drop you "
        + "finally land on the firm, horizontal ground.\n\n");
    set_alarm(1.2,0.0,&climb_down_done());
    return 1;
}

int
climb_down_done()
{
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    TP->move_living("down the cliff, landing on the ground",PLAINS + "rside_btm",1,0);
    TP->add_fatigue(CLIMB_FATIGUE);
    say(QCTNAME(this_player())+" arrives climbing from above.\n");

    return 1;
}

void
create_khalakhor_room()
{
   set_short("You find a solid foothold, and carefully begin "
           + "to climb down the cliff");
   set_long("   You find a solid foothold, and carefully begin "
           + "to climb down the cliff.\n");
}

public int
cmd_lock(string str)
{
    string verb = query_verb();

    switch (verb)
    {
        case "commune":
        case "reply":
        case "quit":
        case "bug":
        case "sysbug":
        case "typo":
        case "systypo":
        case "idea":
        case "sysidea":
        case "praise":
        case "syspraise":
            return 0;
            break;
        case "stop":
            write("Stop climbing? But then you would fall down!\n");
            return 1;
        default:
            write("You can not do that while climbing, it takes "
                + "all your concentration and energy to find a "
                + "safe passage down the cliff wall.\n");
            return 1;
    }
}

public void
init()
{
    ::init();
    TP->add_prop(LIVE_S_EXTRA_SHORT, " is not far off, also climbing down the cliff");
    set_alarm(7.1,0.0,&climb_down_1());
    add_action(cmd_lock, "", 1);
}


