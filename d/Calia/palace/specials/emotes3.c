#pragma save_binary

/*      This is the third set of emotes for the Calian warrior's guild.
        It is included into the calian cmdsoul.

    coder(s):   Digit
    history:
             29.3.95           Modified slightly              Maniac
             30.3.95           csuspect corrected             Maniac
*/

calian_suspect(string str)
{
    object tp, tmp, *who, *secondwho;
    int i;
    secondwho = (({}));
    tp = TP;
    if (!str)
    {
       write("Suspect who?\n");
       return 1;
    }
    who = parse_this(str, "%l");
    if (!sizeof(who)) return 0;
    for(i = 0; i < sizeof(who); i++)
    {
       if(!who[i]->query_met(tp) || !tp->query_met(who[i]))
       {
          tmp = who[i];
          secondwho += ({tmp});
       }
    }

    if(!sizeof(secondwho))
    {
       notify_fail("You have met " + ((sizeof(who) > 1) ? 
                                     "those people!\n" :
                                     "that person!\n"));
       return 0;
    }

    str = capitalize(str);
    targetbb(" glares at you suspiciously as " + tp->query_pronoun()+
       " doesn't know who you are.",secondwho);
    actor("You glare suspiciously at",secondwho);
    all2actbb(" glares suspiciously at",secondwho," as "+tp->query_pronoun()+
       " doesn't know " + ((sizeof(secondwho) > 1) ? 
                           "them." : 
                           secondwho[0]->query_objective() + "."));
    SOULDESC("glaring suspiciously.");
    return 1;
}

calian_amused(string str)
{
    object tp;
    tp = TP;
    if (str) return 0;
    write("You show that you are rather amused.\n");
    all(" looks rather amused about something.");
    SOULDESC("looking rather amused about something");
    return 1;
}

calian_concern(string str)
{
    object *oblist;
    if(!strlen(str))
    {
        notify_fail("Look concerned about who?\n");
        return 0;
    }

    oblist = parse_this(str, "%l");
    if(!sizeof(oblist))
    {
        return 0;
    }
    if (!living(oblist[0]))
    {
        notify_fail(oblist[0]->query_name()+" doesn't seem to be alive.\n");
        return 0;
    }
    target(" gives you a look of concern.",oblist);
    actor("You give",oblist," a look of concern.");
    all2actbb(" gives",oblist," a look of concern.");
    return 1;
}

calian_friend(string str)
{
    object *oblist;
    if(!strlen(str))
    {
        notify_fail("Declare who as a true friend?\n");
        return 0;
    }

    oblist = parse_this(str, "%l");
    if(!sizeof(oblist))
    {
        return 0;
    }
    if (!living(oblist[0]))
    {
        notify_fail(oblist[0]->query_name()+" doesn't seem to be alive.\n");
        return 0;
    }
    target(" declares you a true friend of Calia.",oblist);
    actor("You declare",oblist,((sizeof(oblist)>1) ? 
                                " true friends of Calia." :
                                " a true friend of Calia."));
    all2actbb(" declares",oblist, ((sizeof(oblist)>1) ? 
                                " true friends of Calia." :
                                " a true friend of Calia."));
    return 1;
}

calian_hug(string str)
{
    object *oblist;
    if(!strlen(str))
    {
        notify_fail("Give a hug to who?\n");
        return 0;
    }

    oblist = parse_this(str, "%l");
    if(!sizeof(oblist))
    {
        return 0;
    }
    if (!living(oblist[0]))
    {
        notify_fail(oblist[0]->query_name()+" doesn't seem to be alive.\n");
        return 0;
    }
    target(" grins and hugs you joyously.",oblist);
    actor("You grin and give",oblist," a joyous hug.");
    all2actbb(" grins and gives",oblist," a joyous hug.");
    SOULDESC("grinning joyously");
    return 1;
}

calian_fear(string str)
{
    object tp;
    tp = TP;
    if (str) return 0;
    write("You show your fear at being alone and outnumbered.\n");
    all(" looks fearful about being alone and outnumbered.");
    SOULDESC("looking fearful about being alone");
    return 1;
}

calian_intim(string str)
{
    object *oblist;

    notify_fail("Intimidate who?\n");
    if (!strlen(str))
        return 0;
    oblist = parse_this(str, "%l");
    if (!sizeof(oblist))
        return 0;
    if (sizeof(oblist) != 1)
    {
        notify_fail("You cannot intimidate everyone at the same time!\n");
        return 0;
    }
    if ((TP->query_stat(SS_DIS)+random(15)) < 
        (oblist[0]->query_stat(SS_DIS)+random(15)+20))
    {
        target(" tries to physically intimidate you, but you are"+
            " not at all bothered, and smirk in amusement.",oblist);
        actor("You try to physically intimidate",oblist,", but "+
            oblist[0]->query_pronoun()+
                " is not at all bothered, and smirks in amusement.");
        all2actbb(" tries to physically intimidate",oblist,", but "+
            oblist[0]->query_pronoun()+
            " is not at all bothered, and smirks in amusement.");
        return 1;
    }
    if ((TP->query_stat(SS_STR)+random(15)) <
        (oblist[0]->query_stat(SS_STR)+random(15)+20))
         {
             target(" physically intimidates you.  You feel " +
                    "somewhat flustered.",oblist);
             actor("You physically intimidate",oblist,".  "+
                    capitalize(oblist[0]->query_pronoun())+
                    " looks somewhat flustered.");
             all2actbb(" physically intimidates",oblist,".  "
                 +capitalize(oblist[0]->query_pronoun())+
                 " looks somewhat flustered.");
             return 1;
         }
      target(" physically intimidates you.  You cringe in terror " +
             "and become very panic stricken.",oblist);
      actor("You physically intimidate",oblist,".  "+
            capitalize(oblist[0]->query_pronoun())+
            " cringes in terror and becomes very panic stricken.");
      all2actbb(" physically intimidates",oblist,".  "+
            capitalize(oblist[0]->query_pronoun())+
            " cringes in terror and becomes very panic stricken.");
      return 1;
}
