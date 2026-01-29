/* Sick of an extra alarm in every room... Rhyn, Sep 24 '03. */

private static string *tell_strings = ({}), *tell_strings_left = ({});
private static int tell_time = 60, started = 0, last_time = time();

public void start_room_tells() { }
public void stop_room_tells() { }

public void
set_tell_time(int t)
{
    if(t > 0)
    {
        tell_time = t;
    }
}

public int
query_tell_time()
{
    return secure_var(tell_time);
}

public void
add_tell(string str)
{
    if(str && member_array(str, tell_strings) == -1)
    {
        tell_strings += ({ str });
    }
}

public varargs void
do_room_tell(int t = 0)
{
    string current_tell;
    object to;

    if(!sizeof(tell_strings))
    {
        return;
    }

    if(t && t < (last_time + tell_time))
    {
        return;
    } else if(t) {
        last_time = t;
    }

    if(!sizeof(tell_strings_left))
    {
         tell_strings_left = tell_strings + ({});
    }

    to = this_object();
    current_tell = tell_strings_left[random(sizeof(tell_strings_left))];
    tell_strings_left -= ({ current_tell });

    tell_room(to, to->check_call(current_tell));
}

public string *
query_tell_strings()
{
    return secure_var(tell_strings);
}

public string *
query_tell_strings_left()
{
    return secure_var(tell_strings_left);
}
