inherit "/std/object";

public int absent(string str);

void
create_object()
{
    set_no_show();
    set_name("absentee_waiter");
}

public void
init()
{
    ::init();
    add_action(absent, "call");
    add_action(absent, "order");
    /*add_action(absent, "complain");*/
    add_action(absent, "check");
    add_action(absent, "pay");
}

public int
absent(string str)
{
    notify_fail("You will have to wait for the waiter to return first.\n");
    return 0;
}
