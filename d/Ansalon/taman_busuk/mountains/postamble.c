    set_noshow_obvious(1);
    add_prop(ROOM_I_NO_CLEANUP, 1);

}

int cleanUpAlarm = 0;

public void
clean_up()
{
    object *ob;
    int i;

    cleanUpAlarm = 0;

    ob = all_inventory(this_object());
    for (i = 0 ; i < sizeof(ob) ; i++)
    {
	if (living(ob[i]))
	{
	    cleanUpAlarm = set_alarm(itof(Timeout),0.0,"clean_up");
	    return;
	}
    } 

    for (i = 0 ; i < sizeof(ob) ; i++)
	Master_ob->dispose_of(ob[i]);

    rm(MASTER_OB(TO) + ".c");
    remove_object();
}

public nomask void
enter_inv(object ob, object from)
{
    if (cleanUpAlarm)
      remove_alarm(cleanUpAlarm);
    cleanUpAlarm = set_alarm(itof(Timeout),0.0,"clean_up");
    ::enter_inv(ob, from);
}

public nomask void
set_cleanup_time(int time)
{
    Timeout = time;
    if(cleanUpAlarm)
      remove_alarm(cleanUpAlarm);
    cleanUpAlarm = set_alarm(itof(Timeout),0.0,"clean_up");
}
