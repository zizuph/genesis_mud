/* Minotaur soul
 * For the Krynn race guild by
 * ~Elmore 2001
 *
 */


/* Define used for all commands here in this file. If it returns 0,
 * the player cannot use this emote.
 */
#define CHECK_MINOTAUR;    if(TP->query_race_name() != "minotaur") return 0;

/* Function:    query_cmdlist_*
 * Description: return all the commands that are available in this
 *              file.
 */
mapping
query_cmdlist_minotaur()
{
    return (["msnort":"msnort"
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
	  "msnort <person> - Snort arrogantly at someone.\n" +
	  "\nAny emote suggestions should be mailed to Elmore.\n\n" +
	  "\n");
    return 1;
}

/*****************************************************************
 * Below follow the actual commands/emotes
 *****************************************************************/


/*********************** msnort ***********************************/
int
msnort(string str)
{
    object *ob;
    object obj;

    CHECK_MINOTAUR;

    ob = parse_this(str, "[the] %l");

    obj = ob[0];

    if (!str)
    {
	write("You snort arrogantly.\n");
	say(QCTNAME(TP)+" snorts arrogantly.\n");
	return 1;
    }
    
    if ((!strlen(str)) || (!sizeof(ob))) 
    {
	notify_fail("Snort at whom?\n");
	return 0;
    }
    
    actor("You look snort arrogantly at", ob, " obviously displeased with "+HIM(obj)+".");
    targetbb(" snorts arrogantly at you, obviously displeased with you.", ob);
    all2actbb(" snorts arrogantly at", ob, " obviously displeased with "+HIM(obj)+".");
    return 1;
}

