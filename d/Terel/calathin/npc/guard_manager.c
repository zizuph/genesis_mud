static object *guards = ({});

public void
register_guard(object guard)
{
    guards -= ({ 0 });
    guards += ({ guard });
}

public object *
query_guards()
{
    guards -= ({ 0 });
    return guards + ({});
}

public void
absolve(object player)
{
    guards -= ({ 0 });
    guards->stop_fight(player);
    player->stop_fight(guards);
}

public void
remove_object()
{
    if (sizeof(query_guards()))
    {
        throw("Cannot remove guard manager while guards are registered.  " +
            "Use Destruct -D to force removal.\n");
    }

    destruct();
}
