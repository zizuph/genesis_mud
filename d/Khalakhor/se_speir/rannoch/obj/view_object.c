/* File         : /d/Khalakhor/se_speir/rannoch/obj/view_object.c
 * Creator      : Darragh@Genesis
 * Date         : 01-04-22      
 * Purpose      : Paralyzing object
 * Related Files: /d/Khalakhor/se_speir/rannoch/room/g_06.c
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit "/std/object";

public void
create_object()
{
    set_name("view_object");
    add_name("view_obj");
    set_short("view object");
    set_long("Loch Rannoch hilltop view object.\n");
    set_no_show();
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_DROP, 1);

}

public int
do_view_10()
{
    write("View sequence 10 activated.\n");
    set_alarm(3.0,0.0,&remove_object());
}

public int
do_view_9()
{
    write("View sequence 9 activated.\n");
    set_alarm(3.0,0.0,&do_view_10());
}

public int
do_view_8()
{
    write("View sequence 8 activated.\n");
    set_alarm(3.0,0.0,&do_view_9());
}

public int
do_view_7()
{
    write("View sequence 7 activated.\n");
    set_alarm(3.0,0.0,&do_view_8());
}

public int
do_view_6()
{
    write("View sequence 6 activated.\n");
    set_alarm(3.0,0.0,&do_view_7());
}

public int
do_view_5()
{
    write("View sequence 5 activated.\n");
    set_alarm(3.0,0.0,&do_view_6());
}

public int
do_view_4()
{
    write("View sequence 4 activated.\n");
    set_alarm(3.0,0.0,&do_view_5());
}

public int
do_view_3()
{
    write("View sequence 3 activated.\n");
    set_alarm(3.0,0.0,&do_view_4());
}

public int
do_view_2()
{
    write("View sequence 2 activated.\n");
    set_alarm(3.0,0.0,&do_view_3());
}

public int
do_view_1()
{
    write("View sequence 1 activated.\n");
    set_alarm(3.0,0.0,&do_view_2());
}

public int
do_stop()
{
    write("You stop gazing at the lands around you.\n");
    say(QCTNAME(TP) + " seems to have lost interest in "
                    + " watching " + HIS + " surroundings.\n");
    remove_object();
    return 1;
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
        case "stop":
            return do_stop();
            break;
        default:
            write("You're too busy watching the view "
                + "to do anything else, just 'stop' if "
                + "you wish to do something else.\n");
            return 1;
    }
}

public void
init()
{
    ::init();
    say(QCTNAME(TP) + " gazes off into the distance, "
                    + "turning " + HIS + " head now and then "
                    + "while scanning the lands around you.\n");
    TP->add_prop(LIVE_S_EXTRA_SHORT, " is watching the view");
    add_action(cmd_lock, "", 1);
    do_view_1();
}

public int
remove_object()
{
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    write("Removing object.\n");
    return ::remove_object();
}