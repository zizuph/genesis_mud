/* Minotaur soul
 * For the Krynn race guild by
 * ~Elmore 2001
 *
 */


/* Define used for all commands here in this file. If it returns 0,
 * the player cannot use this emote.
 */
#define CHECK_MINOTAUR    if(TP->query_race_name() != "minotaur") return 0

/* Function:    query_cmdlist_*
 * Description: return all the commands that are available in this
 *              file.
 */
mapping
query_cmdlist_minotaur()
{
    return (["msnort"  :"msnort",
             "mflare"  :"mflare",
             "mlaugh"  :"mlaugh",
             "mspit"   :"mspit",
             "mrevenge":"mrevenge",
             "mpolish" :"mpolish",
             "mthrow"  :"mthrow",
             "mwarn"   :"mwarn",
             "mroar"   :"mroar",
             "mglance" :"mglance",
             "mremind" :"mremind"
         ]);
}

/* Function:    help_*
 * Description: handle the help stuff for minotaur.
 */
int
help_minotaur(string subject)
{
    CHECK_MINOTAUR;

    if (subject != "emotes" && subject != "emotions")
    return 0;

    write("Minotaur Emotions:\n\n"+
      "<> refers to optional commands.\n" +
      "[] refers to necessary input.\n\n" +
      "msnort <person>  - Snort arrogantly at someone.\n" +
      "mlaugh           - Laugh heartily at the weaknesses of the other races.\n" +
      "mspit            - Spit on the ground at the thought of weakness.\n" +
          "mrevenge         - Renew your vow of revenge.\n" +
          "mflare           - Let your temper flare at the thought of such insolence.\n" +
          "mpolish          - Polish your horns.\n" +
          "mthrow [person]  - Throw someone away with your horns.\n"+
          "mwarn  [person]  - Warn someone.\n"+
          "mroar  <person>  - Roar at someone.\n"+
          "mglance [person] - Glare at someone for not showing enough respect.\n"+
          "mremind [person] - Remind someone that there's no room for weakness\n"+
          "                   within the minotaurs.\n"+
          "--------------------------------------------------------------------------\n"+
      "\nAny emote suggestions should be mailed to Krynn.\n\n" +
      "\n");
    return 1;
}

/*****************************************************************
 * Below follow the actual commands/emotes
 *****************************************************************/

int
msnort(string str)
{
    object *oblist;

    CHECK_MINOTAUR;

    oblist = parse_this(str, "[at] [the] %l");

    if (!strlen(str))
    {
        write("You snort arrogantly.\n");
        say(QCTNAME(TP)+" snorts arrogantly.\n");
        return 1;
    }

    if (!sizeof(oblist))
    {
        NF("Snort at who?\n");
        return 0;
    }

    actor("You snort arrogantly at", oblist, " obviously displeased.");
    targetbb(" snorts arrogantly at you, obviously displeased.", oblist);
    all2actbb(" snorts arrogantly at", oblist, " obviously displeased.");
    return 1;
}

int
mlaugh(string str)
{
    CHECK_MINOTAUR;

    if (!strlen(str))
    {
        write("You laugh heartily at the weaknesses of the other races.\n");
        say(QCTNAME(TP) +" laughs heartily at the weaknesses of other races.\n");
        return 1;
    }
    else
    {
        write("Just use 'mlaugh' without any arguments.\n");
    }
    return 1;
}


int
mspit(string str)
{
    CHECK_MINOTAUR;


    if (!strlen(str))
    {
        write("You spit on the ground at the thought of weakness.\n");
        say(QCTNAME(TP) +" spits on the ground at the thought of weakness.\n");
        return 1;
    }
    else
    {
        write("Just use 'mspit' without any arguments.\n");
    }
    return 1;
}

int
mrevenge(string str)
{
    CHECK_MINOTAUR;

    if (!strlen(str))
    {
        write("You renew your vow of revenge upon any and all that "+
              "may have crossed you.\n");
        say(QCTNAME(TP) +" renews "+HIS(TP)+" vow of revenge upon any and all "+
                  "that may have crossed "+HIM(TP)+".\n");
        return 1;
    }
    else
    {
        write("Just use 'mrevenge' without any arguments.\n");
    }
    return 1;
}

int
mflare(string str)
{
    CHECK_MINOTAUR;

    if (!strlen(str))
    {
        write("Your temper flares at the thought of such insolence.\n");
        say(QCTNAME(TP) +" temper flares at the thought of such insolence.\n");
        return 1;
    }
    else
    {
        write("Just use 'mflare' without any arguments.\n");
    }
    return 1;
}

int
mpolish(string str)
{
    CHECK_MINOTAUR;

    if (!strlen(str))
    {
        write("You lower your head and starts to polish your horns.\n");
        say(QCTNAME(TP) +" lowers "+HIS(TP)+" head and starts to polish "+HIS(TP)+" horns.\n");
        return 1;
    }
    else
    {
        write("Just use 'mpolish' without any arguments.\n");
    }
    return 1;
}

int
mthrow(string str)
{
    object *ob;
    object obj;

    CHECK_MINOTAUR;

    if(!strlen(str))
    {
        notify_fail("Throw who?\n");
        return 0;
    }

    ob = parse_this(str, "[the] %l");

    if(!sizeof(ob))
    {
        notify_fail("Throw who?\n");
        return 0;
    }

    obj = ob[0];

    actor("You hook the tip of your massive horns under", ob,"'s arms and throw "+HIM(obj)+
          " behind you in one smooth action.");
    target(" hooks the tip of "+HIS(TP)+" massive horns under your arms and throw you "+
           "behind "+HIM(TP)+ " in one smooth action.", ob);
    all2act(" hooks the tip of "+HIS(TP)+ " massive horns under", ob,"'s arms and "+
            "throw "+HIM(obj)+" behind "+HIM(TP)+"self in one smooth action.");
    return 1;
}

int
mwarn(string str)
{
    object *ob;
    object obj;

    CHECK_MINOTAUR;

    if(!strlen(str))
    {
        notify_fail("Warn who?\n");
        return 0;
    }

    ob = parse_this(str, "[the] %l");

    if(!sizeof(ob))
    {
        notify_fail("Warn who?\n");
        return 0;
    }

    obj = ob[0];

    actor("You warn", ob," to remove "+HIM(obj)+ "self from your presence before "+
          "you rid yourself of it permanently.");
    target(" warns you to remove yourself from "+HIS(TP)+" presence before "+
           HE(TP)+ " removes you permanently.", ob);
    all2act(" warns", ob," to remove "+HIM(obj)+ "self from "+HIS(TP)+" presence "+
            "before "+HE(TP)+ " removes "+HIM(obj)+" permanently.");
    return 1;
}


int
mremind(string str)
{
    object *ob;
    object obj;

    CHECK_MINOTAUR;

    if(!strlen(str))
    {
        notify_fail("Remind who?\n");
        return 0;
    }

    ob = parse_this(str, "[the] %l");

    if(!sizeof(ob))
    {
        notify_fail("Remind who?\n");
        return 0;
    }

    obj = ob[0];

    actor("You remind", ob," that there is no room for weakness within the "+
          "ranks of the mighty minotaur.");
    target(" reminds you that there is no room for weakness within the ranks "+
           "of the mighty minotaur.", ob);
    all2act(" reminds", ob," that there is no room for weakness within the "+
            "ranks of the mighty minotaur.");
    return 1;
}

int
mglance(string str)
{
    object *ob;
    object obj;

    CHECK_MINOTAUR;

    if(!strlen(str))
    {
        notify_fail("Glance at who?\n");
        return 0;
    }

    ob = parse_this(str, "[at] %l");

    if(!sizeof(ob))
    {
        notify_fail("Glance at who?\n");
        return 0;
    }

    obj = ob[0];

    actor("You glance at", ob," in a way that leaves no doubt in "+ HIS(obj)+
          " mind that minotaurs do not take disrespect lightly.");
    target(" glances at you in a way that leaves no doubt in your "+
          "mind that minotaurs do not take disrespect lightly.", ob);
    all2act(" glances at", ob," in a way that leaves no doubt in "+HIS(obj)+
            " mind that minotaur do not take disrespect lightly.");
    return 1;
}

int
mroar(string str)
{
    object *ob;
    object obj;

    CHECK_MINOTAUR;

    if(!strlen(str))
    {
        write("You roar defiantly.\n");
        say(QCTNAME(TP) +" roars defiantly.\n");
        return 1;
    }

    ob = parse_this(str, "[at] %l");

    if(!sizeof(ob))
    {
        notify_fail("Roar at who?\n");
        return 0;
    }

    obj = ob[0];

    actor("You roar in", ob,"'s face defiantly.");
    target(" roars in your face defiantly.", ob);
    all2act(" roars in", ob,"'s face defiantly.");
    return 1;
}

