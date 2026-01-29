varargs void
introduce_me(object pl, int delay)
{
    if (!present(pl, environment(this_object())))
        return;

    if (!delay)
        delay = 5;
    delay = random(delay);

    if (!random(4))
        return;

    if (pl->query_met(this_object()->query_real_name()))
        return;

    if (!random(3))
        set_alarm(itof(delay + 1), 1.0, 0.0, "command", "say Hi!");
    if (random(2))
        set_alarm(itof(delay + 2), 0.0, "command", "present me");
    else
        set_alarm(itof(delay + 2), 0.0, "command", "present me to "
          + pl->query_real_name());

    if (!random(3))
        set_alarm(itof(delay + 3), 0.0, "command", "shake "
          + pl->query_real_name());
}

void
return_introduce(string who, string whom)
{
    introduce_me(this_player(), 2);
}

/*
 * Function name: enable_intro
 * Description:   adds the necessary trig for introductions
 */
public void
enable_intro()
{
    this_object()->trig_new("%s 'introduces' %s", "return_introduce");
}
 
/*
 * Function name: disable_intro
 * Description:   removes the intro trigger.
 */
public void
disable_intro()
{
    this_object()->trig_delete("%s 'introduces' %s");
}
 
