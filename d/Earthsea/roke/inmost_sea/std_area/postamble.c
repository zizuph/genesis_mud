
    add_prop(ROOM_I_NO_CLEANUP, 1);
}

public void
clean_up()
{
    object *ob;
    int i;

    ob = all_inventory(this_object());
    for (i = 0 ; i < sizeof(ob) ; i++)
    {
        if (living(ob[i]))
        {
            call_out("clean_up", Timeout);
            return;
        }
    } 

    for (i = 0 ; i < sizeof(ob) ; i++)
        Master_ob->dispose_of(ob[i]);

    rm(MASTER_OB(TO) + ".c");
    remove_object();
}

public void
sink(object ob)
{
   tell_room(TO,"The "+ob->query_name()+" sinks to the " +
      "bottom of the sea.\n");
   ob->remove_object(); 
}

public nomask void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if(living(ob))
       return;
    set_alarm(2.0, 0.0, &sink(ob));

    remove_call_out("clean_up");
    call_out("clean_up", Timeout);
}


public nomask void
set_cleanup_time(int time)
{
    Timeout = time;
    remove_call_out("clean_up");
    call_out("clean_up", Timeout);
}



