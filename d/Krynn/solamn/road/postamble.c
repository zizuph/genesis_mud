    set_noshow_obvious(1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    LIGHT;

    /* Set up the herbs */
    if (query_short() == "On the plains of Solamnia")
      herbs = HERB_MASTER->query_herbs( ({ "plains", }) );
    if (query_short() == "Foot of the mountains")
      herbs = HERB_MASTER->query_herbs( ({ "mountains", }) );
    if (query_short() == "On a riverbank")
      herbs = HERB_MASTER->query_herbs( ({ "riverbank", }) );
    if (query_short() == "A stream on the plains of Solamnia")
      herbs = HERB_MASTER->query_herbs( ({ "wetlands", }) );


    if (herbs)
      set_up_herbs(({ ONE_OF(herbs),
		      ONE_OF(herbs),
		      ONE_OF(herbs) }),
		   ({"bushes","trees","ground"}));
    reset();
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
