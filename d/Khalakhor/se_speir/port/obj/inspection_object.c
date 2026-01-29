/*
 * inspection_object.c
 *
 * This is just a little invis object used for the
 * second tour in the village, and gives players the
 * 'inspect' command needed to check out the
 * embankment around the village.
 *
 * Embankment rooms in the plains:
 *    plains_12_11
 *    plains_12_10
 *    plains_12_9
 *    plains_12_8
 *    plains_13_8
 *    plains_14_8
 *    plains_16_9
 *    plains_17_9
 *    plains_17_10
 *    plains_17_11
 *
 * Khail - August 21, 1997
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

#define FIELD_PATH "/d/Khalakhor/se_speir/plains/room/"

inherit "/std/object";

int inspect_alarm,
    finished_inspection;
mapping inspected;

public void
create_object()
{
    set_name("inspection_object");
    add_name("insp_obj");
    set_short("inspection object");
    set_long("Port Macdunn embankment inspection object.\n");
    set_no_show();
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    inspected = ([FIELD_PATH + "plains_12_11": 0,
                  FIELD_PATH + "plains_12_10": 0,
                  FIELD_PATH + "plains_12_9": 0,
                  FIELD_PATH + "plains_12_8": 0,
                  FIELD_PATH + "plains_13_8": 0,
                  FIELD_PATH + "plains_14_8": 0,
                  FIELD_PATH + "plains_16_9": 0,
                  FIELD_PATH + "plains_17_9": 0,
                  FIELD_PATH + "plains_17_10": 0,
                  FIELD_PATH + "plains_17_11": 0]);
}

public int
query_finished_inspection()
{
    return finished_inspection;
}

public void
add_inspected(string str, object who)
{
    who->remove_prop(LIVE_S_EXTRA_SHORT);
    if (member_array(str, m_indexes(inspected)) < 0)
        return 0;

    inspected[str] = 1;

    if (!sizeof(filter(m_values(inspected), &operator(==)(0))))
    {
        who->catch_tell("That's the last of them, time to " +
            "report back to Fahlmar.\n");
        finished_inspection = 1;
        return;
    }
}

public mapping
query_inspected()
{
    return inspected + ([]);
}

      
public void
complete_inspection(object who, object where)
{
    if (environment(who) != where)
    {
        who->remove_prop(LIVE_S_EXTRA_SHORT);
        return;
    }

    write("You finish inspecting this section of " +
        "the embankment and decide it's in perfect " +
        "condition.\n");
    add_inspected(file_name(where), who);
}

public void
inspect_2(object who, object where)
{
    if (environment(who) != where)
    {
        who->remove_prop(LIVE_S_EXTRA_SHORT);
        return;
    }

    write("The middle looks fine too, you turn your " +
        "attention towards the upper reaches of the " +
        "embankment to complete the inspection.\n");
    inspect_alarm = set_alarm(10.0, 0.0, 
        &complete_inspection(who, where));
}

public void
inspect_1(object who, object where)
{
    if (environment(who) != where)
    {
        who->remove_prop(LIVE_S_EXTRA_SHORT);
        return;
    }

    write("The base looks good, you climb up a bit to " +
        "get a closer look at the middle section of "+
        "the embankment to continue your inspection.\n");
    inspect_alarm = set_alarm(10.0, 0.0, &inspect_2(who, where));
}

public int
do_inspect(string str)
{
    if (!environment(TP)->query_embankment_room())
        return 0;

    NF("Inspect what? The embankment?\n");

    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "[the] 'embankment'"))
        return 0;

    if (get_alarm(inspect_alarm))
    {
        write("You are already in the process of " +
            "inspecting the embankment.\n");
        return 1;
    }
    write("You begin inspecting the embankment, " +
        "this will take awhile.\n");
    say(QCTNAME(TP) + " begins closely examining " +
        "the embankment.\n");
    TP->add_prop(LIVE_S_EXTRA_SHORT, " is inspecting the embankment");
    TO->move(TP,1);
    inspect_alarm = set_alarm(20.0, 0.0, 
        &inspect_1(TP, environment(TP)));
    return 1;
}

public int
do_stop(string str)
{
    if (!str || !strlen(str) || str != "inspecting")
        return 0;

    if (!get_alarm(inspect_alarm))
        return 0;

    write("You stop inspecting the embankment.\n");
    say(QCTNAME(TP) + " appears to have lost interest in " +
        "inspecting the embankment.\n");
    remove_alarm(inspect_alarm);
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
}

public int
cmd_lock(string str)
{
    string verb = query_verb();

    if (!get_alarm(inspect_alarm))
        return 0;

    if (TP->query_wiz_level())
    {
        write("You're supposed to be inspecting the embankment, " +
            "but since you're a wizard we'll let you do " +
            "something else. Ain't I a sweetie?\n");
        return 0;
    }

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
        case "inspect":
            return 0;
            break;
        case "stop":
            return do_stop(str);
            break;
        default:
            write("You're too busy inspecting the embankment " +
                "to do anything else, 'stop inspecting' if " +
                "you want to do something else.\n");
            return 1;
    }
}

public void
init()
{
    ::init();
    add_action(do_inspect, "inspect");
    add_action(cmd_lock, "", 1);
}

public void
remove_object()
{
    environment()->remove_prop(LIVE_S_EXTRA_SHORT);
    ::remove_object();
}
