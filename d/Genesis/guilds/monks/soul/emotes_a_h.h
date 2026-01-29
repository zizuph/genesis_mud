/* 
 *  The emotions of the Dragon Order, from A - H
 *
 *  Transferred into an .h file by 	Cirion, 160496
 *  Emotes updated and added by 	Lilith, 01 Feb 99
 */


/*
 * Function name: aod_bless
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_bless(string str)
{
    object  *oblist;
    string   a, b, temp;
    int      i;

    if (TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        notify_fail("You can't seem to speak.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("What or whom wouldst thou bless?\n");
        return 0;
    }

    a = "blessing of Segoy, the Dragon Father of All Creation";
    b = "the likeness of a dragon-tooth in the air";

    if (str == (string) this_player()->query_real_name() ||
        str == "me" || str == "myself")
    {
        write("You ask the "+ a +", over your endeavor.\n");
        allbb(" seeks the "+ a +" for "+ HIM(TP) + "self.");
        return 1;
    }

    oblist = parse_this(str, "[the] %i");

    if (!sizeof(oblist)) 
    {
        notify_fail("What or whom wouldst thou bless?\n");
        return 0;
    }

    if (sizeof(oblist[0]->query_prop(MONK_AM_BLESSED)) > 1)
    {
        write("You sense that " + LANG_THESHORT(oblist[0]) +
            (oblist[0]->num_heap() > 1 ? " have":" has") +
            " already received Segoy's blessing through "+ 
            capitalize(
            oblist[0]->query_prop(MONK_AM_BLESSED)[0])+".\n");
        return 1;
    }

    if (sizeof(oblist) == 1)
        temp = oblist[0]->query_objective();
    else
        temp = "them";

    actor("You sketch "+ b +" near", oblist," and solemnly ask "+
        "the "+ a +" over "+ temp +".");
    targetbb(" sketches "+ b +" and asks the "+ a +" over you.",
        oblist);
    all2actbb(" sketches "+ b +" near", oblist, " and solemnly "+
        "asks the "+ a +" over "+ temp +".");

    for (i=0;i<sizeof(oblist);i++)
    {
        if (sizeof(oblist[i]->query_prop(MONK_AM_BLESSED)) > 1 &&
            oblist[i]->query_prop(MONK_AM_BLESSED)[1] > 
            m_query_guild_rank(TP))
            continue;
        oblist[i]->add_prop(MONK_AM_BLESSED, 
             ({ TP->query_real_name(), m_query_guild_rank(TP) }));
    }

    return 1;
}

/*
 * Function name: aod_bow
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int
aod_bow(string str)
{
    object *oblist;
    string  temp;

    if (!strlen(str))
    {
        write("You drop your arms to your sides and perform "+
            "a small bow, holding it for a few seconds before "+
            "standing fully erect.\n");
        allbb(" drops "+ this_player()->query_possessive() +
            " arms to "+ this_player()->query_possessive() +
            " sides and performs a small bow.");
        return 1;
    }

    oblist = parse_this(str, "[to] [the] / [a] %l");

    if (!sizeof(oblist))
    {
         notify_fail("Whom dost thou wish to bow to?\n");
         return 0;
    }

    actor("You drop your arms to your sides and perform "+
        "a small bow to", oblist, ", holding it for a "+
        "few seconds before standing fully erect.");
    targetbb(" drops "+ this_player()->query_possessive() +
        " arms to "+ this_player()->query_possessive() +
        " sides and performs a small bow to you.", oblist);
    all2actbb(" drops "+ this_player()->query_possessive() +
        " arms to "+ this_player()->query_possessive() +
        " sides and performs a small bow to", oblist,".");
    return 1;
}

/*
 * Function name: aod_center
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_center(string str)
{
    object *oblist;
    int     success;
    string  a, b;

    if (!success)
    {   
        if (m_query_council_member(this_player(), 1))
            success = 1;
        else
        {
            if (m_query_guild_rank(this_player()) - 
              this_player()->query_skill(MONK_SKILL_FOCUS) > 0) 
            success = 1;
        }
    }

    if (!success)
    {
        write("You breathe deeply and attempt to center yourself, "+
            "but fail.\n");
        allbb(" looks momentarily disconcerted.");
        return 1;
    }

    a = "You breathe in deeply, briefly tapping the dragon-"+
        "spirit within and centering yourself so that you "+
        "might ignore the";
    b = "provoke "+ HIM(TP) +", nor disturb "+ HIS(TP) +" equanimity";

    if (!strlen(str) && success)
    {
        write(a +" distractions of your surroundings.\n");
        all(" seems to radiate a calm certainty that leaves you "+
            "with the feeling that nothing can "+ b +".");
        success = 0;
        SOULDESC("radiating a calm certainty");
	return 1;
    }

    oblist = parse_this(str, "[the] / [a] %i");
    if (sizeof(oblist) != 1)
    {
        notify_fail("Center thine self to ignore whom or what?\n");
        return 0;
    }

    actor(a +" provocations of", oblist, ".");
    target(" seems to radiate a calm certainty that leaves you "+
        "with the feeling that nothing you can do will "+ b +
        ".", oblist);
    all2actbb(" seems to radiate a calm certainty that leaves you "+
        "with the feeling that nothing", oblist, " can do will "+ 
        b +".", oblist);
    SOULDESC("radiating a calm certainty");
    return 1;
}

/*
 * Function name: aod_chant
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_chant(string str)
{
    string a;

    notify_fail("You can't seem to speak.\n");
    if(TP->query_prop(LIVE_M_MOUTH_BLOCKED))
        return 0;

    a = "a bit of dragon lore in an arcane language";
    switch(TP->query_race_name())
    {
        case "elf":
            write("You close your eyes and raise your mellifluous "+
                "voice to chant "+ a +".\n");
            all(" raises "+ HIS(TP) +" mellifluous voice to "+
                "chant "+ a +".");
            SOULDESC("chanting melliflously");
            return 1;
            break;
        case "hobbit":
            write("In a voice like that of a chirping bird, you "+
                "close your eyes and chant "+ a +".\n");
            all(", sounding like a chirping bird, raises "+ HIS(TP) +
                "voice to chant "+ a +".");
            SOULDESC("chanting quickly");
            return 1;
            break;
        case "goblin":
            write("You raise your low, gravelly voice to chant "+
                a +".\n");
            all(" raises "+ HIS(TP) +" low, gravelly voice to "+
                "chant "+ a +".");
            SOULDESC("chanting deeply");
            return 1;
            break;
        case "dwarf":
            write("You raise your deep, earthy voice to chant "+
                a +".\n");
            all(" raises "+ HIS(TP) +" deep, earthy voice to "+
                "chant "+ a +".");
            SOULDESC("chanting deeply");
            return 1;
            break;
        default:
            write("You raise your full, melodious voice to chant "+
                a +".\n");
            all(" raises "+HIS(TP)+" voice to chant "+ a +".");
            SOULDESC("chanting with a full, melodious voice");
            return 1;
            break;
    }
        return 1;
}

/*
 * Function name: aod_chastise
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_chastise(string str)
{
    object *oblist;
    string  temp;

    if (!strlen(str))
    {
        notify_fail("Whom dost thou wish to chastize?\n");    
        return 0;
    }

    oblist = parse_this(str, "[the] / [a] %l");

    if (!sizeof(oblist))
    {
         notify_fail("Whom dost thou wish to chastize?\n");
         return 0;
    }

    if (sizeof(oblist) == 1)
    {

        actor("You allow the barest hint of castigation to "+
            "show on your face as you meet", oblist, "'s eyes.");
        targetbb(" raises wise, fiery eyes to meet yours, and with"+
            "in their implacable depths you see the barest hint "+
            "of castigation.", oblist);
        all2act(" looks for a long moment into", oblist,"'s "+
            "eyes.");
        return 1;
    }

    if(sizeof(oblist) > 1)
    {
        actor("You allow the barest hint of castigation to "+
            "show on your face as you meet the eyes of", oblist,
            ".");
        targetbb(" raises wise, fiery eyes to meet yours, and with"+
            "in their implacable depths you see the barest hint "+
            "of castigation.", oblist);
        return 1;
    }
    return 1;
}

/*
 * Function name: aod_control
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_control(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You fight to control your anger as you have "+
            "learned in your studies of the dragon-discipline.\n");
        all("'s face visibly clouds as "+ HE(TP) +" fights to "+
            "control " + HIS(TP) + " anger.");
       return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[my] [anger] [at] [the] %l")))
    {
        notify_fail("Control thine anger at whom?\n");
        return 0;
    }

    target("'s face clouds visibly as " + HE(TP)+" struggles to "+
        "control "+ HIS(TP) +" anger at your behavior.", oblist);
    actor("You fight to control your anger with", oblist,", using "+
        "what you have learned in your studies of the dragon-"+
        "discipline.");
    all2act(" clouds visibly in the face as "+ HE(TP)+" fights to "+
        "control "+ HIS(TP) +" anger at", oblist, "'s behavior.");
    return 1;
}

/*
 * Function name: aod_dedicate
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_dedicate(string str)
{
    if (str != "myself")   
    {
        notify_fail("You can only dedicate yourself.\n");
        return 0;
    }

    if (m_query_monk(TP, SS_OCCUP))
    {
        write("You take a moment to mentally re-dedicate your "+
            "life to mastering the dragon-discipline.\nYou feel "+
            "a renewed sense of purpose.\n");
        allbb(" appears to have a renewed sense of purpose.");
        SOULDESC("looking purposeful");
        return 1;
    }

    write("You take a moment to consider the possibility of "+
        "fully dedicating yourself to the mastery of the "+
        "dragon-discipline.\n");
    allbb(" appears to be considering something.");
    return 1;
}


/*
 * Function name: aod_defend
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_defend(string str)
{
    object *oblist;
    string a;

    a = "with serpentine grace and economy of movement";

    if (!strlen(str))
    {
        write("You shift "+ a +" into a stance from which you "+
            "might better defend yourself.\n");
        allbb(" shifts "+ a +" into a stance from which "+
            HE(TP) +" can defend "+ HIM(TP) +"self, a look "+
            "of calm preparation on "+ HIS(TP) +" face.");
	return 1;
    }

    oblist = parse_this(str, "[the] / [a] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Whom dost thou wish to defend?\n");
        return 0;
    }

    targetbb(" shifts "+ a +" into a stance from which "+
        HE(TP) +" can more readily defend you, a look of calm "+
        "preparation on "+ HIS(TP) +" face.", oblist);
    actor("You shift "+ a +" into a stance from which you "+
        "might better defend", oblist, " against harm.");
    all2actbb(" shifts "+ a +" into a stance from which "+
        HE(TP) +" can more readily defend", oblist, " a look of "+
        "calm preparation on "+ HIS(TP) +" face.");
    return 1;
}

/*
 * Function name: aod_display
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_display(string str)
{
    object  *oblist;
    string   how;


    if (TP->query_fatigue() < 10)
    {
        notify_fail("Thou art too exhausted to do that.\n");
        return 0;
    }

    switch(TP->query_skill(SS_UNARM_COMBAT) + random(5) - 3)
    {
        case -20 .. 5:  how = "pathetic";               break;
        case 6 .. 10:   how = "amateurish";             break;
        case 11 .. 20:  how = "passable";               break;
        case 21 .. 30:  how = "mildly impressive";      break;
        case 31 .. 37:  how = "impressive";             break;
        case 38 .. 46:  how = "very impressive";        break;
        case 47 .. 58:  how = "remarkably agile";       break;
        case 59 .. 70:  how = "fleet, graceful";        break;
        case 71 .. 80:  how = "fluid and dextrous";     break;
        case 81 .. 91:  how = "absolutely dazzling";    break;
        case 92 .. 96:  how = "incredibly swift and fluid";  
                                                        break;
        case 97 .. 101: how = "impossibly serpentine";  break;
        default:        how = "amazingly dragon-like";  break;
    }

    if (!strlen(str))
    {
        write("You perform "+ LANG_ADDART(how) +" display of your "
            +"combat abilities.\n");
        allbb(" performs "+ LANG_ADDART(how) +" display of "+ HIS(TP)
            +" combat abilities.\n");
        TP->add_fatigue(-random(10));
        return 1;
    }

    oblist = parse_this(str, "[before] / [to] [the] %l");
    if (!sizeof(oblist))
    {
        notify_fail("Whom dost thou wish to display thine "+
            "combat abilities before?\n");
        return 0;
    }

    targetbb(" performs "+ LANG_ADDART(how) +" display of "
        + HIS(TP) +" combat abilities before you.", oblist);
    actor("You perform "+ LANG_ADDART(how) +" display of "
        +"your combat abilities before", oblist, ".");
    all2actbb(" performs "+ LANG_ADDART(how) +" display of "
        + HIS(TP) +" combat abilities before",oblist,".");
    TP->add_fatigue(-random(10));
    return 1;
}

/*
 * Function name: aod_drop
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int
aod_drop(string str)
{
    object *oblist;
    string a;

    a = "bare of all pretenses of civility, revealing the intent "+
        "and chilling eyes of a predator";

    if (!strlen(str))
    {
        write("You drop all pretenses of civility and stare about "+
            "you with the intent eyes of a predator.\n");
        allbb("'s equanimity suddenly dissolves.  You find yourself "+
            "staring at a face "+ a +".");  
        return 1;
    }

    oblist = parse_this(str, "[all] [pretenses] [before] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Drop all pretenses before whom?\n");
        return 0;
    }

    actor("You drop all pretenses of civility and stare at",oblist,
        " with the intent and chilling eyes of a predator.");
    targetbb("'s equanimity toward you suddenly dissolves.  You "+
        "find yourself staring at a face "+ a +".", oblist);
    all2actbb(" 's equanimity towards",oblist," suddenly dissolves.  "+
        "You find yourself staring at a face "+ a +".");
    return 1;
}


/*
 * Function name: aod_fist
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_fist(string str)
{
    string *how;

    find_living ("cirion")->catch_tell ("aod_fist called with (" + str + ") arg\n");

    how = parse_adverb_with_space(str, "triumphantly", 0);
    if (!strlen(how[0]))
    {
        write("You raise your fist" + how[1] + " in the air.\n");
        allbb(" raises "+ HIS(TP) +" fist" + how[1] + " in the air.");
        SOULDESC("raising "+ HIS(TP) +" fist"+ how[1]);
        return 1;
    }

    write("You raise your fist" + how[1] + " in the air.\n");
    allbb(" raises "+ HIS(TP) +" fist" + how[1] + " in the air.");
    SOULDESC("raising "+ HIS(TP) +" fist"+ how[1]);
    return 1;
}

/*
 * Function name: aod_gaze
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_gaze(string str)
{
    object *oblist;
 
    if (!strlen(str))
    {
        write("Your eyes gleam as you reflect upon the vast wisdom "+
            "of the dragons.\n");
        allbb("'s eyes gleam with the brilliance of untold wisdom.");
        return 1;
    }
 
    if (!sizeof(oblist = parse_this(str, "[at] / [upon] [the] %i"))) 
    {
        notify_fail("What or whom dost thou wish to gaze upon?\n");
        return 0;
    }
 
    target("'s eyes gleam with the brilliance of untold wisdom "+
        "as "+ HE(TP) +" gazes upon you.", oblist);
    actor("You reflect upon the vast wisdom of the dragons as you "+
        "gaze at", oblist,".");
    all2actbb(" gazes upon", oblist, " "+ HIS(TP) +" eyes gleaming "+
        "with the brilliance of untold wisdom.");
    return 1;
}

/*
 * Function name: aod_growl
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int
aod_growl(string str)
{
    object *oblist;
    string  a;

    a = "a low, rumbling growl as a chilling, almost predatory "+
        "grin creeps across";

    if (!strlen(str))
    {
        write("You emit "+ a +" your lips.\n");
        allbb(" emits "+ a +" "+ HIS(TP) +" lips.");
        return 1;
    }
 
    if (!sizeof(oblist = parse_this(str, "[at] [the] %i"))) 
    {
        notify_fail("Whom dost thou wish to growl at?\n");
        return 0;
    }
 
    target(" emits a low, rumbling growl at you while a chilling, "+
        "almost predatory grin creeps across "+ HIS(TP) +" face.", 
        oblist);
    actor("You emit a low, rumbling growl at", oblist, " while a "+
        "chilling, almost predatory grin spreads across your face.");
    all2actbb(" emits a low growl at", oblist, ", while a chilling, "+
        "almost predatory grin spreads across "+ HIS(TP) +" face.");
    return 1;
}

