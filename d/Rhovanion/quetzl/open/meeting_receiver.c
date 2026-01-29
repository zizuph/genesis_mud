#pragma strict_types

inherit "/std/object";

public void  
create_object()
{
    add_name("_meeting_receiver_");
    set_name("earpiece");
    set_adj("meeting");
    set_long("This is a meeting earpierce.  To use it, simply type " +
        "wear earpiece.  You will then hear the meeting, assuming one " +
        "is in progress, and you have been invited to listen.\n");
}

private int listening = 0;

public void
init()
{
    ::init();
    add_action("wear", "wear");
    add_action("remove", "remove");
}

public int
wear(string arg)
{
    if ((arg != "earpiece") && (arg != "meeting earpiece"))
        return 0;

    notify_fail("But you are already wearing it!\n");
    if (listening)
        return 0;

    write("You wear the earpiece and begin receiving the meeting.\n");
    listening = 1;
    return 1;
}

public int
remove(string arg)
{
    if ((arg != "earpiece") && (arg != "meeting earpiece"))
        return 0;

    notify_fail("But you aren't wearing it!\n");
    if (!listening)
        return 0;

    write("You remove the earpiece and stop listening.\n");
    listening = 0;
    return 1;
}

public int
query_active_listen()
{
    return listening;
}
