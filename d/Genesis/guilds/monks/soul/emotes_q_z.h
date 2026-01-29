/* 
 *  The emotions of the Dragon Order, from Q - Z
 *
 *  Transferred into an .h file by 	Cirion, 160496
 *  Emotes updated and added by 	Lilith, 01 Feb 99
 */


/*
 * Function name: aod_refuse
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int
aod_refuse(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "adamantly", 0);
    if (!strlen(how[0]))
    {
        write("You refuse to become embroiled in the dispute.\n");
        return 1;
    }

    oblist = parse_this(how[0], "[in] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Mrefuse how in whose dispute?\n");
        return 0;
    }


    actor("You"+ how[1] +" refuse to become embroiled in", oblist, "'s "+
        "dispute.");
    target(how[1] +" refuses to become embroiled in your dispute.",
        oblist);
    all2act(" refuses quite"+ how[1] +" to become embroiled in", oblist,
        "'s dispute.");
    return 1;
}

/*
 * Function name: aod_relax
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_relax(string str)
{
    if (strlen(str))   
        return 0;
 
    write("You consciously relax every muscle in your body in an "+
        "attempt to achieve inner peace.\n");
    allbb(" appears completely relaxed.  Suddenly you notice " +
        "how still and peaceful everything has become.");
    SOULDESC("looking relaxed and peaceful");
    
    return 1;
}

/*
 * Function name: aod_roar
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_roar(string str)
{
    if (strlen(str))   
        return 0;

    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        write("You throw your head back and roar with fury.\n");
        allbb(" throws "+ HIS(TP) +" head back and roars so "+
            "loudly your ears ring.");
        return 1;
    }

    write("You roar forth your fury to the skies.\n"+
        "Thunder rumbles in the distance.\n");
    allbb(" roars forth "+ HIS(TP) +" fury to the skies.\n"+
        "Thunder rumbles in the distance.");
    SOULDESC("roaring furiously");
    return 1;
}


/*
 * Function name: aod_shun
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_shun(string str)
{
    object  *oblist;
    string   temp;

    if (!strlen(str))
    {
        notify_fail("What or whom dost thou wish to shun?\n");
        return 0;
    }   

    if (str == (string) this_player()->query_real_name() ||
	str == "me" || str == "myself")
    {
        write("You shun yourself in a fit of existential angst.\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %i");

    if(!sizeof(oblist))
    {
        notify_fail("Whom or what wouldst thou shun?\n");
        return 0;
    }

    SOULDESC("looking disdainful");

    if (sizeof(oblist) == 1)
        temp = oblist[0]->query_pronoun() +" represents";
    else
        temp = "they represent";

    actor("You shun", oblist," and all "+ temp +".");
    targetbb(" regards you, and all that you represent, with "+
        "an expression of utter revulsion.", oblist);
    all2actbb(" appears to regard", oblist, " and all that "+
        temp +" with utter revulsion.");
    return 1;

}

/*
 * Function name: aod_sketch
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_sketch(string str)
{
    object  *oblist;
    string   a;

    a = "the likeness of a dragon-tooth in the air";

    if (!strlen(str))
    {
        write("You extend your arm and with your forefinger, sketch "+
            a +".\n");
        allbb(" extends "+ HIS(TP) +" arm and sketches "+ a +" with "+
            HIS(TP) +" forefinger.");
        return 1;
    }

    if (str == (string) this_player()->query_real_name() ||
        str == "me" || str == "myself")
    {
        write("You sketch "+ a +" before you.\n");
        allbb(" extends "+ HIS(TP) +" arm and sketches "+ a +" with "+
            HIS(TP) +" forefinger.");
        return 1;
    }

    oblist = parse_this(str, "[before] / [near] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Whom or what dost thou wish to sketch "+
            "before?\n");
        return 0;
    }

    targetbb(" extends "+ HIS(TP) +" arm and sketches "+ a +" before "+
        "you with "+ HIS(TP) +" forefinger.", oblist);
    actor("You extend your arm and with your forefinger, sketch "+
        a +" before", oblist, ".");
    all2actbb(" extends "+ HIS(TP) +" arm and sketches "+ a +" before", 
        oblist," with "+ HIS(TP) +" forefinger.");
    return 1;
}

/*
 * Function name: aod_slice
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_slice(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "repeatedly", 0);

    if (!strlen(how[0]))
    {
        write("You emphasize what you are saying by slicing the "+
            "air"+ how[1] +" with your hand.\n");
        allbb(" emphasizes what "+ HE(TP) +" is saying by slicing "+
            "the air"+ how[1] +" with "+ HIS(TP) +" hand.");
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Slice how at whom?\n");
        return 0;
    }

    targetbb(" emphasizes what "+ HE(TP) +" is saying to you by "+
        "slicing the air"+ how[1] +" with "+ HIS(TP) +" hand.",
        oblist);
    actor("You emphasize what you are saying to", oblist, " by "+
        "slicing the air"+ how[1] +" with your hand.");
    all2actbb(" emphasizes what "+ HE(TP) +" is saying to", oblist, 
        " by slicing the air"+ how[1] +" with "+ HIS(TP) +" hand.");
    return 1;
}

/*
 * Function name: aod_victory
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_victory(string str)
{
    object  *oblist;

    if (!strlen(str))
    {
        write("A magnificent cry of victory erupts from your throat "+
            "and wings away into the heavens.\n");
        say("A magnificent cry of victory erupts from "+ QTNAME(TP) +
            "'s throat and wings away into the heavens.\n");
        return 1;
    }

    oblist = parse_this(str, "[over] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Whom or what dost thou wish to cry victory "+
            "over?\n");
        return 0;
    }

    targetbb(" declares "+ HIS(TP) +" triumph over you with a "+
        "magnificent cry of victory that erupts from "+ HIS(TP) +
        " throat and wings away into the heavens.", oblist);
    actor("You declare your triumph over", oblist, " with a "+
        "magnificent cry of victory that erupts from your "+
        "throat and wings away into the heavens.");
    all2actbb(" declares "+ HIS(TP) +" triumph over", oblist,
        " with a magnificent cry of victory that erupts from "+ 
        HIS(TP) +" throat and wings away into the heavens.");
    return 1;
}

/*
 * Function name: aod_wing
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int
aod_wing(string str)
{
    object *oblist;
    string  temp;

    if (!strlen(str))
    {
        notify_fail("Whom dost thou wish to take under thine wing?\n");
        return 0;
    }

    oblist = parse_this(str, " [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Whom dost thou wish to cry victory "+
            "over?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
        temp = "wings";
    else
        temp = "wing";

    actor("You take", oblist, " under your "+ temp +", promising "+
        "lessons in wisdom, honour, and lore.");
    target(" takes you under "+ HIS(TP) +" wing, promising lessons "+
        "in wisdom, honour, and lore.", oblist);
    all2act(" takes", oblist," under "+ HIS(TP) +" "+ temp +", "+
        "promising lessons in wisdom, honour, and lore.");
    return 1;
}


/*  Warn
 */
int
test_name(object target, object member)
{
    string *names = ({ });
    string  n;

    if (!member->query_prop(MONK_HAS_WARNED))
    {
        n = target->query_real_name();
        member->add_prop(MONK_HAS_WARNED, ({ n }));
        return 1;
    }
   
    names = member->query_prop(MONK_HAS_WARNED);
    n = target->query_real_name();
    if (member_array(n, names) == -1)
    {
        names = names + ({ n });
        member->add_prop(MONK_HAS_WARNED, names);
        return 1;
    }
}

/*
 * Function name: aod_warn
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int
aod_warn(string str)
{
    object *oblist;
    int     i;
    string  temp;

    if (!strlen(str))
    {
        notify_fail("Whom dost thou wish to warn?\n");
        return 0;
    }

    oblist = parse_this(str, " [the] %l");
    oblist -= ({this_player});

    if (!sizeof(oblist))
    {
        notify_fail("Whom or what dost thou wish to warn?\n");
        return 0;
    }
            
    for (i=0; i < sizeof(oblist); i++)
    if (interactive(oblist[i]))
    {
        test_name(oblist[i], TP);
    }

    temp = "with cold intensity:\n    I am "+ capitalize(
           this_player()->query_real_name()) +", "+ 
           m_query_title(this_player()) +
           ", and as is my Way, I offer you this warning.  "+
           "Depart or I shall attack";

    actor("You focus a stern gaze upon", oblist, " and declare "+
        temp +"!");
    target(" focuses a stern gaze upon you and declares "+ temp +
        "!", oblist);
    all2act(" focuses a stern gaze upon", oblist," and declares "+
        temp + "!");
    return 1;
}

