/*
 * Blocks north.
 *
 * Gwyneth
 */
inherit "/std/object";

void
create_object()
{
    set_name("event_blocker");
    add_name("blocker");
    set_short("blocker");
    set_no_show();
}

int
blocked(string str)
{
    write("The men won't let you pass.\n");
    return 1;
}

int
block_sneak(string str)
{
    if (str != "north")
    {
        return 0;
    }
    else
    {
        write("The men won't let you pass.\n");
        return 1;
    }
}
void
init()
{
    add_action(blocked, "north");
    add_action(blocked, "n");
    add_action(block_sneak, "sneak");
}
