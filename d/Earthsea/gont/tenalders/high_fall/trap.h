#ifndef SS_LOC_SENSE
#include <ss_types.h>
#endif
#define SEE_PATH(x) \
    ( \
        (x->query_skill(SS_LOC_SENSE) > 15) && \
        (x->query_skill(SS_AWARENESS) > 15) && \
        (x->query_skill(SS_TRACKING) > 15) \
    )
#define SEE_TRAP(x) \
    ( \
        SEE_PATH(x) && \
        (x->query_skill(SS_FR_TRAP) > 15) \
    )

private string around_room;
private string around_dir;
public void
set_around_room(string str, string dir)
{
    around_room = str;
    around_dir = dir;
}

public int
trap(string str)
{
    object tp = this_player();

    if(str == "around")
        return notify_fail("Go around what?\n");

    if(str && parse_command(str, this_object(), "[around] [the] 'trap'") &&
        SEE_TRAP(tp))
    {
        write("You cleverly circumnavigate a trap laid at your feet, easing " +
            "around the edge of it.\n");
        tp->move_living(around_dir + ", taking a circuitous route",
            around_room, 1);
        return 1;
    }

    return notify_fail("Go where?\n");
}

public string
see_path()
{
    object tp = this_player();

    if(SEE_TRAP(tp))
    {
        return "You can make out a trap set in the undergrowth "+
            "just ahead! The trap consists of a pit that is "+
            "disguised by branches and brush lying across it.\n";
    }

    if(SEE_PATH(tp))
    {
        return "In the gloom you make out a faint trail that heads "+
            "north and south.\n";
    }

    return "\n";
}

public string
see_trap()
{
    if(!SEE_TRAP(this_player()))
        return "What trap?\n";

    return "You see a trap laid in the undergrowth. "+
        "You might be able to get past it by going around ... "+
        "very carefully.\n";
}

public void
init_trap_room()
{
    add_action(trap, "go");
    add_action(trap, "around");
    add_action(trap, "circumnavigate");
}
