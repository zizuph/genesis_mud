
object Clone;

public void set_clone(object clone)
{
    Clone=clone;
}

public object query_clone()
{
    return Clone;
}

public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    object room=environment(TP);
    
    int result=QSW->move_living(how,to_dest,dont_follow,no_glance);

    if (!result && objectp(Clone))
    {
        Clone->move(room,1);
        Clone->move_living(how,to_dest,dont_follow,no_glance);
        Clone->move(environment(TO),1);
    }

    return result;    
}
