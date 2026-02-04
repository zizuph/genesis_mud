
int
member_check()
{
    object member = find_object(MAGES_LOG);
    if(member->query_member(TP->query_name()))
    {
       return 1;
    }
    return 0;
}


int
elder_check()
{
    object elder = find_object(MAGES_LOG);
    if(elder->query_elder(TP->query_name()))
    {
       return 1;
    }
    return 0;
}

int
leader_check()
{
    object leader = find_object(MAGES_LOG);
    if(leader->query_leader(TP->query_name()))
    {
       return 1;
    }
    return 0;
}


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
do_accept(string str)
{

    object *oblist;

    if(!leader_check())
    {
        write("Only the leader can offer a place in the Order.\n");
        return 1;
    }

    if(!str || !strlen(str))
    {
        write("Accept who into the Order?\n");
        return 1;
    }
    oblist = parse_this(str, "[at] [the] %l");

    if(!sizeof(oblist))
        return 0;

    actor("You accept ",oblist," into the Order of the White.");
    targetbb(" accepts you into the Order of the White.",oblist);
    all2actbb(" accepts ",oblist," into the Order of the White.");
    oblist->add_prop(MAGES_ACCEPTED, 1);
    return 1;
}



public int
do_smile(string str)
{
    object *oblist;

    NF("Xsmile at whom?\n");

    if(!str || !strlen(str))
    {
        write("You flash an icy smile.\n");
        allbb(" flashes an icy smile.\n");
        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");

    if(!sizeof(oblist))
        return 0;

    actor("You flash an icy smile at",oblist,".");
    targetbb(" flashes an icy smile at you.",oblist);
    all2actbb(" flashes an icy smile at",oblist,".");
    return 1;
}

