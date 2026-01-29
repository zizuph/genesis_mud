public int alarm_id = 0;

public void create()
{
    setuid();
    seteuid(getuid());
}

public void
clear()
{
    int group, bit;
    object pl = find_player("lloril");

    find_player("shiva")->catch_tell("Checking\n");
    if (!pl)
    {
        return;
    }

    for (group = 0; group < 5; group++)
    {
        for (bit = 0; bit < 20; bit++)
        {
            pl->clear_bit(group, bit);
        }
    }

    remove_alarm(alarm_id);
    destruct();
}

public void start()
{
    alarm_id = set_alarm(0.0, 120.0, clear);
}
