/* Sick of an extra alarm in every room... Rhyn, Sep 24 '03. */

#pragma strict_types
#pragma no_clone

private int id;

public void
do_room_tells()
{
    object *list, *e = filter(map(users(), environment),
        &operator(==)("Earthsea") @ &->query_domain());
    mapping rooms = ([]);
    string err;
    int i, sz = sizeof(e), t;

    if(!sz)
    {
        return;
    }

    for(i = 0; i < sz; i++)
    {
        rooms[e[i]] = 1;
    }

    list = m_indices(rooms);

    if(!(sz = sizeof(list)))
    {
        return;
    }

    t = time();

    for(i = 0; i < sz; i++)
    {
        if(strlen(err = catch(list[i]->do_room_tell(t))))
        {
            log_file("room_tell_err", "- " + ctime(t) + " " + 
                file_name(list[i]) + ": " + err);
        }
    }
}

public void
create()
{
    setuid();
    seteuid(getuid());
    id = set_alarm(15.0, 15.0, do_room_tells);
}

public int
query_alarm_id()
{
    return id;
}
