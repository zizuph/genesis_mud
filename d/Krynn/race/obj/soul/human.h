/* Human soul
 * For the Krynn race guild by
 * ~Aridor 12/96
 *
 * Add emotes and commands used by ALL humans here into this file.
 * There is no need to change the ../race_soul.c file.
 * Warning: Watch for commands that are used by more than one race/
 *          tribe/region.
 */


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
	    "xkglare":"xkglare",
	    "xhomesick":"xhomesick",
	    "xwait":"xwait",
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
	  "xkglare   - glare at <kender>\n" +
	  "xhomesick - feel homesick\n" +
	  "xwait     - wait <for someone>\n"+
	  "(For further emote suggestions, please 'mail krynn')\n" +
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
