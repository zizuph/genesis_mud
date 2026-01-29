/* File         : /d/Khalakhor/se_speir/plains/room/rside_wall_up.c
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

#define CLIMB_FATIGUE -100
inherit "/d/Khalakhor/se_speir/plains/room/tforbase";

int climb_up_1();
int climb_up_2();
int climb_up_3();
int climb_up_4();
int climb_up_5();
int climb_up_done();

int
climb_up_1()
{
    write("\nYou are only a few feet above the ground, it would not "
        + "hurt that bad if you should happen to fall down.\n\n");
    set_alarm(8.0,0.0,&climb_up_2());
    return 1;
}

int
climb_up_2()
{
    write("You continue to climb up the cliff, you are almost "
        + "halfway up.\n\n");
    set_alarm(11.5,0.0,&climb_up_3());
    return 1;
}

int
climb_up_3()
{
    write("Steadily and carefully you climb up the cliff, the top "
        + "drawing nearer.\n\n");
    set_alarm(11.2,0.0,&climb_up_4());
    return 1;
}

int
climb_up_4()
{
    write("Just a few feet from the top, you begin to seriously "
        + "long for this climb to come to an end.\n\n");
    set_alarm(7.4,0.0,&climb_up_5());
    return 1;
}

int
climb_up_5()
{
    write("Finally you have reached the top, and you pull yourself "
        + "over the ledge.\n\n");
    set_alarm(1.3,0.0,&climb_up_done());
    return 1;
}

int
climb_up_done()
{
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    TP->move_living("over the top of the cliff",PLAINS + "rside_top",1,0);
    TP->add_fatigue(CLIMB_FATIGUE);
    return 1;
}

void
create_khalakhor_room()
{
   set_short("You find a good place to start your climb from, and with "
           + "a final look at the flat ground beneath your feet, you "
           + "begin to climb up the cliff wall");
   set_long("   You find a good place to start your climb from, and with "
          + "a final look at the flat ground beneath your feet, you "
          + "begin to climb up the cliff wall.\n");
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
                + "safe passage up the cliff wall.\n");
            return 1;
    }
}

public void
init()
{
    ::init();
    TP->add_prop(LIVE_S_EXTRA_SHORT, " is not far off, also climbing up the cliff");
    set_alarm(7.0,0.0,&climb_up_1());
    add_action(cmd_lock, "", 1);
}


