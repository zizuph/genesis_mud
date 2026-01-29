/* Human soul
 * For the Krynn race guild by
 * ~Aridor 12/96
 *
 * Add emotes and commands used by ALL humans here into this file.
 * There is no need to change the ../race_soul.c file.
 * Warning: Watch for commands that are used by more than one race/
 *          tribe/region.
 */


/* Xwipe fixed by navarre June 14th 2006. */

/* Define used for all commands here in this file. If it returns 0,
 * the player cannot use this emote.
 */
#define CHECK_HUMAN;    if(TP->query_race_name() != "human") return 0;


/* Function:    query_cmdlist_*
 * Description: return all the commands that are available in this
 *              file.
 */
mapping
query_cmdlist_human()
{
   return (["xboast":"xboast",
       "xcurse":"xcurse",
       "xdragon":"xdragon",
       "xelves":"xelves",
       "xfool":"xfool",
       "xgaze":"xgaze",
       "xkglare":"xkglare",
       "xgreed":"xgreed",
       "xhomesick":"xhomesick",
       "xhunt":"xhunt",
       "xinvite":"xinvite",
       "xleaf":"xleaf",
       "xmarvel":"xmarvel",
       "xpace":"xpace",
       "xpray":"xpray",
       "xpride":"xpride",
       "xpunish":"xpunish",
       "xsatis":"xsatis",
       "xscan":"xscan",
       "xscoff":"xscoff",
       "xshiver":"xshiver",
       "xsplash":"xsplash",
       "xstars":"xstars",
       "xstretch":"xstretch",
       "xsusp":"xsusp",
       "xtie":"xtie",
       "xtoast":"xtoast",
       "xtrade":"xtrade",
       "xtremble":"xtremble",
       "xvow":"xvow",
       "xwait":"xwait",
       "xwind":"xwind",
       "xwipe":"xwipe",
       "xwork":"xwork",
        ]);
}

/* Function:    help_*
 * Description: handle the help stuff for humans.
 */
int
help_human(string subject)
{
    CHECK_HUMAN;

    if (subject != "emotes" && subject != "emotions")
      return 0;

    write("Human Emotions:\n\n"+
      "xboast    - boast about your family\n" +
      "xcurse    - curse <how> at <target>\n" +
      "xdragon   - dare dragons to come\n"+
      "xelves    - snort at the arrogance of elves\n"+
      "xfool     - make a remark about old tales\n" +
      "xgaze     - gaze <how> at the lands around you\n" +
      "xkglare   - glare at <kender>\n" +
      "xgreed    - scowl at the sight of a beggar\n" +
      "xhomesick - feel homesick\n" +
      "xhunt     - survey the area [how]\n" +
      "xinvite   - invite someone to visit your homeland\n" +
      "xleaf     - pick a nearby leaf and tear it to pieces\n" +
      "xmarvel   - marvel at the beauty of elven maidens or <someone>\n" +
      "xpace     - pace around <how>\n"+
      "xpray     - whisper a prayer\n"+
      "xpride    - stand with pride\n"+
      "xpunish   - mutter how <someone> would be dealt with in your homeland\n"+
      "xsatis    - smile in satisfaction\n" +
      "xscan     - scan the horizon <how> for the approaching storm\n" +
      "xscoff    - scoff <how> at the mention of the old gods\n" +
      "xshiver   - shiver\n" +
      "xsplash   - imitate [how] a dwarf in water\n" +
      "xstars    - remind people of the missing constellations\n" +
      "xstretch  - stretch your arms <how>\n" +
      "xsusp     - look around or at <someone> with suspicion\n" +
      "xtie      - tie your hair back <how>\n" +
      "xtoast    - raise your glass in a toast\n" +
      "xtrade    - thank someone for a trade\n" +
      "xtremble  - tremble at the thought of Takhisis\n"+
      "xvow      - vow to keep your promise <to someone>\n"+
      "xwait     - wait <for someone>\n"+
      "xwind     - turn your face to the wind <how>\n"+
      "xwipe     - wipe the sweat <how> from your <face/body/brow>\n"+
      "xwork     - boast about the accomplishments of humans\n"+
      "(For further emote suggestions, please mail Krynn)\n" +
      "\n");
    return 1;
}

/*****************************************************************
 * Below follow the actual commands/emotes
 *****************************************************************/

/*********************** xboast *********************************/
/* suggested by Fourtcoer */
int
xboast(string str)
{
    string fam = TP->query_family_title();
    string dummy;

    CHECK_HUMAN;

    if (str)
      return 0;

    sscanf(fam, "%s of %s", fam, dummy);

    write("You boast about your family line.\n");
    say(QCTNAME(TP) + " proudly boasts about the accomplishments of " +
    "the " + fam + " family.\n");
    return 1;
}
/*********************** xcurse ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xcurse(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "loudly", 0);

    CHECK_HUMAN;
    
    if (!strlen(how[0]) || !how[0]) {
        write("You curse"+how[1]+", your face flushed with anger.\n");
        say(QCTNAME(TP)+" curses"+how[1]+", "+HIS(TP)+" face flushed with anger.\n");
        return 1;
    }
    
    oblist = parse_this(how[0], "[at] [the] %l");
    oblist -= ({TP});

    if (!sizeof(oblist)) {
        notify_fail("Curse [how] at [whom]?\n");
        return 0;
    }

    actor("You curse"+how[1]+" at", oblist, ", your face flushed with anger.");
    targetbb(" curses"+how[1]+" at you, "+HIS(TP)+" face flushed with anger.", oblist);
    all2actbb(" curses "+how[1]+" at", oblist, ", "+HIS(TP)+" face flushed with anger.");

    return 1;
}
/*********************** xdragon ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xdragon(string str)
{
     string *how = parse_adverb_with_space(str, "defiantly", 0);

    CHECK_HUMAN;

    write("You shake your fist"+how[1]+" at the sky, daring dragons to come.\n");
    say(QCTNAME(TP)+" shakes "+HIS(TP)+" fist"+how[1]+" at the sky, daring dragons to come.\n");

    return 1;
}
/*********************** xelves ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xelves(string str)
{
    string *how = parse_adverb_with_space(str, "derisively", 0);

    CHECK_HUMAN;

    write("You snort"+how[1]+" at the arrogance of elves.\n");
    say(QCTNAME(TP)+" snorts"+how[1]+" at the arrogance of elves.\n");

    return 1;
}
/*********************** xfool ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xfool(string str)
{
    CHECK_HUMAN;

    write("You make a remark about old wives' tales meant to fool children.\n");
    say(QCTNAME(TP)+" makes a remark about old wives' tales meant to fool children.\n");

    return 1;
}
/*********************** xgaze ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xgaze(string str)
{
    string *how = parse_adverb_with_space(str, "greedily", 0);

    CHECK_HUMAN;

    write("You gaze"+how[1]+" at the lands around you, eager to claim their riches.\n");
    say(QCTNAME(TP)+" gazes"+how[1]+" at the lands around "+HIM(TP)+
        ", eager to claim their riches.\n");

    return 1;
}
/*********************** xkglare *********************************/
/* suggested by Fourtcoer */
int
xkglare(string str)
{
    object *oblist;

    CHECK_HUMAN;

    if (!str)
    {
    write("You look around for kenders, afraid one has already " +
          "gotten too close.\n");
    say(QCTNAME(TP) + " looks nervously around.\n");
    return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");
    oblist = filter(oblist, &operator(==)("kender") @ &->query_race_name());

    if ((!strlen(str)) || (!sizeof(oblist)))
    {
    NF("Glare at whom?\n");
    return 0;
    }

    actor("You glare at", oblist, " suspiciously.");
    targetbb(" glares at you suspiciously, making sure all " + HIS(TP) +
         " belongings are still in place.", oblist);
    all2actbb(" glares at", oblist, " suspiciously, making sure all " +
          HIS(TP) + " belongings are still in place.");
    TP->command("$inventory");
    return 1;
}
/*********************** xgreed ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xgreed(string str)
{
    CHECK_HUMAN;

    write("You scowl at the sight of a beggar.\n");
    say(QCTNAME(TP)+" scowls at the sight of a beggar.\n");

    return 1;
}
/*********************** xhomesick *******************************/
int
xhomesick(string str)
{
    string home = TP->query_family_title();
    string dummy;

    CHECK_HUMAN;

    if (str)
      return 0;

    if (sscanf(home, "%sof %s", dummy, home) == 2)
    {
    write("You think about your home in " + home +
          " and feel a little homesick.\n");
    say(QCTNAME(TP) + " sighs wistfully, mumbling something about " +
        HIS(TP) + " home in " + home + ".\n");
    return 1;
    }
    NF("You have no home (denoted with 'of') in your name you could think of.\n");
    return 0;
}
/*********************** xhunt ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xhunt(string str)
{
    string *how = parse_adverb_with_space(str, "slowly", 0);

    CHECK_HUMAN;

    write("You"+how[1]+" survey the area with the eyes of a hunter, "+
        "looking for your next victim.\n");
    say(QCTNAME(TP)+how[1]+" surveys the area with the eyes of a hunter, "+
        "looking for "+HIS(TP)+" next victim.\n");

    return 1;
}
/*********************** xinvite ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xinvite(string str)
{
    string home = TP->query_family_title();
    string dummy;
    object *oblist;

    CHECK_HUMAN;

    if (!sscanf(home, "%sof %s", dummy, home) == 2)
    {
        NF("You have no home (denoted with 'of') in your name you could think of.\n");
        return 0;
    }

    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});

    if (!sizeof(oblist)) {
        write("You invite everyone to visit your home in "+home+".\n");
        say(QCTNAME(TP)+" invites everyone to visit "+HIS(TP)+" home in "+home+".\n");
        return 1;
    }

    actor("You invite", oblist, " to visit your home in "+home+".");
    targetbb(" invites you to visit "+HIS(TP)+" home in "+home+".", oblist);
    all2actbb(" invites", oblist, " to visit "+HIS(TP)+" home in "+home+".");
    return 1;

}

/*********************** xleaf ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xleaf(string str)
{
    CHECK_HUMAN;

    if (environment(TP)->query_prop(ROOM_I_INSIDE)) {
        notify_fail("You are indoors!\n");
        return 0;
    }

    write("You pick a leaf from a nearby bush and tear it to pieces.\n");
    say(QCTNAME(TP)+" picks a leaf from a nearby bush and tears it to pieces.\n");

    return 1;
}
/*********************** xmarvel ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xmarvel(string str)
{
    object *oblist;

    CHECK_HUMAN;
    
    if (!strlen(str) || !str) {
        write("You marvel at the beauty of elven maidens.\n");
        say(QCTNAME(TP)+" marvels at the beauty of elven maidens.\n");
        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});

    if (!sizeof(oblist)) {
        notify_fail("Marvel at [whom]?\n");
        return 0;
    }

    actor("You marvel at the beauty of", oblist, ".");
    targetbb(" marvels at your beauty.", oblist);
    all2actbb(" marvels at the beauty of", oblist, ".");

    return 1;
}
/*********************** xpace ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xpace(string str)
{

    CHECK_HUMAN;

    string *how = parse_adverb_with_space(str, "impatiently", 0);

    write("You pace around"+how[1]+", for there is little time.\n");
    say(QCTNAME(TP)+" paces around"+how[1]+", for there is little time.\n");

    return 1;
}
/*********************** xpray ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xpray(string str)
{

    CHECK_HUMAN;

    write("You whisper a prayer to the gods of your childhood stories.\n");
    say(QCTNAME(TP)+" whispers a prayer to the gods of "+HIS(TP)+" childhood stories.\n");

    return 1;
}
/*********************** xpride ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xpride(string str)
{
    CHECK_HUMAN;

    write("You straighten your stance with pride.\n");
    say(QCTNAME(TP)+" straightens with pride, a distant look on "+HIS(TP)+" face.\n");

    return 1;
}
/*********************** xpunish ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xpunish(string str)
{
    object *oblist;
    string home = TP->query_family_title();
    string dummy;

    CHECK_HUMAN;

    if (!strlen(str) || !str) {
        notify_fail("Punish [whom]?\n");
        return 0;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});

    if (!sizeof(oblist)) {
        notify_fail("Punish [whom]?\n");
        return 0;
    }

    if (!sscanf(home, "%sof %s", dummy, home) == 2)
    {
        NF("You have no home (denoted with 'of') in your name you could think of.\n");
        return 0;
    }

    actor("You glare at", oblist, " and mutter something about how such "+
        "behavior would be dealt with in "+home+".");
    targetbb(" glares at you and mutters something about how such "+
        "behavior would be dealt with in "+home+".", oblist);
    all2actbb(" glares at ", oblist, " and mutters something about how such "+
        "behavior would be dealt with in "+home+".");

    return 1;
}
/*********************** xsatis ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xsatis(string str)
{
     string *how = parse_adverb_with_space(str, "contentedly", 0);

    CHECK_HUMAN;

    write("You smile"+how[1]+", a look of supreme satisfaction on your face.\n");
    say(QCTNAME(TP)+" smiles"+how[1]+", a look of supreme satisfaction on "+HIS(TP)+" face.\n");

    return 1;
}
/*********************** xscan ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xscan(string str)
{
     string *how = parse_adverb_with_space(str, "warily", 0);

    CHECK_HUMAN;

    write("You"+how[1]+" scan the horizon for the approaching storm.\n");
    say(QCTNAME(TP)+ how[1]+" scans the horizong for the approaching storm.\n");

    return 1;
}
/*********************** xscoff ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xscoff(string str)
{
     string *how = parse_adverb_with_space(str, ".", 0);

    CHECK_HUMAN;

    write("You scoff"+how[1]+" at the mention of the old gods.\n");
    say(QCTNAME(TP)+" scoffs"+how[1]+" at the mention of the old gods.\n");

    return 1;
}
/*********************** xshiver ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xshiver(string str)
{
    CHECK_HUMAN;

    write("Shivering from the cold, you turn your back to the wind in a vain effort to keep warm.\n");
    say("Shivering from the cold, "+QTNAME(TP)+" turns "+HIS(TP)+
        " back to the wind in a vain effort to keep warm.\n");

    return 1;
}

/*********************** xsplash ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xsplash(string str)
{
     string *how = parse_adverb_with_space(str, "uncontrollably", 0);

    CHECK_HUMAN;

    write("You"+how[1]+" flail your arms around like a dwarf in water.\n");
    say(QCTNAME(TP)+how[1]+" flails "+HIS(TP)+ " arms around like a dwarf in water.\n");

    return 1;
}
/*********************** xstars ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xstars(string str)
{
    object *oblist;
 
    CHECK_HUMAN;

    if (!strlen(str) || !str) {
        write("You gesture to the sky and remind everyone of the constellations "+
            "missing from the Krynn heavens.\n");
        say(QCTNAME(TP)+" gestures to the sky and reminds everyone of the "+
            "constellations missing from the Krynn heavens.\n");
        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});

    if (!sizeof(oblist)) {
        notify_fail("Remind [whom]?\n");
        return 0;
    }

    actor("You gesture to the sky and remind", oblist, " of the constellations "+
        "missing from the Krynn heavens.");
    targetbb(" gestures to the sky and reminds you of the constellations "+
        "missing from the Krynn heavens.", oblist);
    all2actbb(" gestures to the sky and reminds", oblist, " of the constellations "+
        "missing from the Krynn heavens.");

    return 1;
}
/*********************** xstretch ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xstretch(string str)
{
    string *how = parse_adverb_with_space(str, "wearily", 0);

    CHECK_HUMAN;

    write("Your joints creak as you"+how[1]+" stretch your arms after the day's travels.\n");
    say(QCTNAME(TP)+"'s joints creak as "+HE(TP)+how[1]+" stretches "+
        HIS(TP)+" arms after the day's travels.\n");

    return 1;
}
/*********************** xsusp ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xsusp(string str)
{
    object *oblist;
 
    CHECK_HUMAN;

    if (!strlen(str) || !str) {
        write("You look around with suspicion.\n");
        say(QCTNAME(TP)+" looks around with suspicion.\n");
        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});

    if (!sizeof(oblist)) {
        notify_fail("Look at [whom]?\n");
        return 0;
    }

    actor("You look at", oblist, " with suspicion.");
    targetbb(" looks at you with suspicion.", oblist);
    all2actbb(" looks at", oblist, " with suspicion.");

    return 1;
}
/*********************** xtie ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xtie(string str)
{
    string *how = parse_adverb_with_space(str, "carefully", 0);

    CHECK_HUMAN;

    write("You"+how[1]+" tie your hair back in preparation for battle.\n");
    say(QCTNAME(TP)+how[1]+" ties "+HIS(TP)+" hair back in preparation for battle.\n");

    return 1;
}
/*********************** xtoast ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xtoast(string str)
{

    CHECK_HUMAN;

    write("You raise your glass in a toast.\n");
    say(QCTNAME(TP)+" raises "+HIS(TP)+" glass in a toast.\n");

    return 1;
}
/*********************** xtrade ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xtrade(string str)
{
    object *oblist;
 
    CHECK_HUMAN;

    if (!strlen(str) || !str) {
        write("You thank everyone for a profitable trade.\n");
        say(QCTNAME(TP)+" thanks everyone for a profitable trade.\n");
        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});

    if (!sizeof(oblist)) {
        notify_fail("Thank [whom]?\n");
        return 0;
    }

    actor("You thank", oblist, " for a profitable trade.");
    targetbb(" thanks you for a profitable trade.", oblist);
    all2actbb(" thanks", oblist, " for a profitable trade.");

    return 1;
}
/*********************** xtremble ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xtremble(string str)
{

    CHECK_HUMAN;

    write("You tremble at the thought of Takhisis conquering Krynn.\n");
    say(QCTNAME(TP)+" trembles at the thought of Takhisis conquering Krynn.\n");

    return 1;
}
/*********************** xvow ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xvow(string str)
{
    object *oblist;
    string fam = TP->query_family_title();
    string dummy;

    CHECK_HUMAN;

    sscanf(fam, "%s of %s", fam, dummy);

    if (!strlen(str) || !str) {
        write("You vow on the honour of the "+fam+" family name to keep your promise.\n");
        say(QCTNAME(TP)+" vows on the honour of the "+fam+" family name to keep "+
            HIS(TP)+" promise.\n");
        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});

    if (!sizeof(oblist)) {
        notify_fail("Vow to [whom]?\n");
        return 0;
    }

    actor("You vow on the honour of the "+fam+
        " family name to keep your promise to", oblist, ".");
    targetbb(" vows on the honour of the "+fam+" family name to "+
        "keep "+HIS(TP)+" promise to you.", oblist);
    all2actbb(" vows on the honour of the "+fam+" family name to "+
        "keep "+HIS(TP)+" promise to", oblist, ".");

    return 1;
}
/*********************** xwait ***********************************/
int
xwait(string str)
{
    object *oblist;

    CHECK_HUMAN;

    if (!str)
    {
        write("You stand around waiting.\n");
        say(QCTNAME(TP)+" shuffles around impatiently.\n");
        return 1;
    }

    oblist = parse_this(str, "[for] [the] %l");
    oblist -= ({TP});

    if ((!strlen(str)) || (!sizeof(oblist)))
    {
    notify_fail("Wait for whom?\n");
    return 0;
    }

    actor("You are waiting for", oblist, " to get going.");
    targetbb(" shuffles around impatiently, waiting for you to get done.", oblist);
    all2actbb(" shuffles around impatiently, waiting for", oblist, " to get done.");
    return 1;
}

/*********************** xwind ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xwind(string str)
{
    string *how = parse_adverb_with_space(str, ".", 0);

    CHECK_HUMAN;

    write("You"+how[1]+" turn your face to the wind.\n");
    say(QCTNAME(TP)+how[1]+" turns "+HIS(TP)+ " face to the wind.\n");

    return 1;
}
/*********************** xwipe ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xwipe(string str)
{
    string *how = parse_adverb_with_space(str, "tiredly", 0);

    CHECK_HUMAN;
    
    if (!strlen(how[0]) || !str) {
        how[0] = "brow";
    }
    
    if (!(how[0] == "body") && !(how[0] == "face")
        && !(how[0] == "brow"))
    {
        notify_fail("Wipe [how] your [body/brow/face]?\n");
        return 0;
    }

    write("You"+how[1]+" wipe the sweat from your "+how[0]+".\n");
    say(QCTNAME(TP)+how[1]+" wipes the sweat from "+HIS(TP) + 
        " "+how[0]+".\n");

    return 1;
}
/*********************** xwork ***********************************/
/*Added by Louie - Suggested by Sekhmet*/
int
xwork(string str)
{

    CHECK_HUMAN;

    write("You boast about the accomplishments of the human race, "+
        "in comparison with other races.\n");
    say(QCTNAME(TP)+" boasts about the accomplishments of the human race, "+
        "in comparison with other races.\n");

    return 1;
}
