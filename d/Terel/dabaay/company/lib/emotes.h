

/*
 * Function name : cant_talk
 * Description   : Returns false if this_player can talk,
 *                 else a string with the failure message.
 * Arguments     : str - String describing the action to
 *                       be attempted, i.e. 'bwar'.
 * Returns       : As described.
 */
public string
cant_talk(string str)
{
    mixed fail;
    string ret;
    
    fail = TP->query_prop(LIVE_M_MOUTH_BLOCKED);

  /* Can't talk if gagged. */
    if (fail)
    {
        if (stringp(fail) && strlen(fail))
            ret = (string)fail;

        else
            ret = "You are somehow prevented from saying " +
                "anything!\n";
    }

  /* Can't talk if stunned. */
    if (TP->query_prop(LIVE_I_STUNNED))
    {
        ret = "You're too stunned and can't catch your breath " +
            "to say anything.\n";
    }

  /* Can't talk if under water. */
    fail = environment(TP)->query_prop(ROOM_I_TYPE);
    if (fail == ROOM_UNDER_WATER)
    {
        ret = "You can't say anything underwater.\n";
    }

    if (ret && strlen(ret))
        return ret;
    else
        return 0;
}

public int
do_smile(string str)
{
    object *oblist;

    NF("Csmile at whom?\n");

    if(!str || !strlen(str))
    {
        write("You flash a quick smile.\n");
        allbb(" flashes a quick smile.\n");
        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");

    if(!sizeof(oblist))
        return 0;

    actor("You flash a quick smile at",oblist,".");
    targetbb("flashes a quick smile at you.",oblist);
    all2actbb(" flashes a quick smile at",oblist,".");
    return 1;
}

public int
do_curse(string str)
{
    object *oblist;

    NF("ccurse at whom?\n");

    if(!str || !strlen(str))
    {
        write("You curse everyone for being a bunch of drunkards.\n");
        allbb(" curses everyone for being a bunch of drunkards.\n");
        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");

    if(!sizeof(oblist))
        return 0;

    actor("You curse",oblist,", for being such a drunkard.");
    targetbb(" curses you for being such a drunkard.",oblist);
    all2actbb(" curses",oblist,", for being such a drunkard");
    return 1;
}
