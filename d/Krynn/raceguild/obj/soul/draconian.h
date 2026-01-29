/* Draconian soul
 * For the Krynn race guild by
 * ~Elmore 2015
 *
 */


/* Define used for all commands here in this file. If it returns 0,
 * the player cannot use this emote.
 */
#define CHECK_DRACONIAN    if(TP->query_race_name() != "draconian") return 0

/* Function:    query_cmdlist_*
 * Description: return all the commands that are available in this
 *              file.
 */
mapping
query_cmdlist_draconian()
{
    return (["dwait"  :"dwait"]);
}

/* Function:    help_*
 * Description: handle the help stuff for draconians.
 */
int
help_draconian(string subject)
{
    CHECK_DRACONIAN;

    if (subject != "emotes" && subject != "emotions")
    return 0;

    write("Draconian Emotions:\n\n"+
      "<> refers to optional commands.\n" +
      "[] refers to necessary input.\n\n" +
      "dwait - Wait for someone.\n" +
      "--------------------------------------------------------------------------\n"+
      "\nAny emote suggestions should be mailed to Elmore.\n\n" +
      "\n");
    return 1;
}

/*****************************************************************
 * Below follow the actual commands/emotes
 *****************************************************************/

int
dwait(string str)
{
    object *oblist;

    CHECK_DRACONIAN;

    actor("You wait arrogantly.");
    targetbb(" waits.", oblist);
    all2actbb(" waits.");
    return 1;
}
