push(string str)
{
    if(str != "panel")
	return 0;
    if(door)
	return 0;
    get_door();
    return 1;
}

get_door2()
{
    if (door)
	door->remove_object();

    if (dAlarm_id1)
    {
	remove_alarm(dAlarm_id1);
	dAlarm_id1 = set_alarm(20.0, 0.0, &remove_door());
    }
    else
    {
	dAlarm_id1 = set_alarm(20.0, 0.0, &remove_door());
    }

    door = clone_object(SECRET_DOOR);
    door->move(TO);
    door->set_key(BOGUS_KEY);
    tell_room(TO,"With a soft click, a secret door " +
      "in the wall pops open!\n");
}

remove_door2()
{
    door->remove_object();
    if (dAlarm_id1)
    {
	remove_alarm(dAlarm_id1);
	dAlarm_id1 = 0;
    }
}

get_door()
{
    get_door2();
    call_other(OTHER_ROOM,"get_door2");
}

remove_door()
{
    remove_door2();
    call_other(OTHER_ROOM,"remove_door2");
    tell_room(TO,"The secret door closes silently, " +
      "becoming unnoticeable again.\n");
}
