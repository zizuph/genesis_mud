#include "defs.h"
#include <tasks.h>
#define RAUMDOR_TRAP_FOUND_MOSS "_raumdor_trap_found_moss"
#define TRAP_CLIMB_FATIGUE 20
inherit "/std/object";

void
create_object()
{
    set_name(({"crevice"}));
    set_long("It would not be easy, but you might be able to use it to " +
            "climb out of here.\n");
    set_no_show_composite(1);
    add_prop(OBJ_I_NO_GET, 1);
}

public int
check_seen(object for_obj)
{
    if (for_obj->query_prop(RAUMDOR_TRAP_FOUND_MOSS)
            && environment(this_object())->query_moss_ripped())
            return ::check_seen(for_obj);
    return 0;
}

int
do_climb(string str)
{
    int success;
    object ob;

    if (!check_seen(TP) || !TP->can_see_in_room())
        return 0;

    notify_fail("Climb up?\n");
    if (str != "up" && str != "out" && str != "crevice")
        return 0;
   
    notify_fail("You are not skilled enough to climb such a small crevice "
            + "while carrying so much weight.\n");
    if (TP->query_encumberance_weight() > TP->query_skill(SS_CLIMB))
        return 0;

    notify_fail("You are too tired to climb right now.\n");
    if (TP->query_fatigue() < TRAP_CLIMB_FATIGUE)
        return 0;

    TP->add_fatigue(-TRAP_CLIMB_FATIGUE);

    success = TP->resolve_task(TASK_FORMIDABLE,
            ({SS_CLIMB, SKILL_AVG, TS_DEX, TS_STR, SKILL_END}));

    if (success < 0)
    {
        write("You try to climb up using the crevice, but your fingers slip.\n");
        TELL_SEEN(TP, QCTNAME(TP) + 
            " tries to climb up, but slips back down.\n"); 
        return 1;
    }
    
    write("You manage to climb high enough to reach the trap door and " +
            "push yourself through!\n");
    TELL_SEEN(TP, QCTNAME(TP) + " leaves climbing up!\n");
    TP->move_living("M", MTRAIL_DIR + "death_room");
    TELL_SEEN(TP, QCTNAME(TP) + " arrives through the trap door!\n");
    return 1;
}


void
init()
{
    ::init();
    add_action(do_climb, "climb");
}


