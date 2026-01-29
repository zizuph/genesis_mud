/* Goblin soul
 * For the Krynn race guild by
 * ~Aridor 1/97
 *
 * Add emotes and commands used by ALL goblins here into this file.
 * There is no need to change the ../race_soul.c file.
 * Warning: Watch for commands that are used by more than one race/
 *          tribe/region.
 */


/* Define used for all commands here in this file. If it returns 0,
 * the player cannot use this emote.
 */
#define CHECK_GOBLIN;    if(TP->query_race_name() != "goblin") return 0;


/* Function:    query_cmdlist_*
 * Description: return all the commands that are available in this
 *              file.
 */
mapping
query_cmdlist_goblin()
{
   return ([
        ]);
}

/* Function:    help_*
 * Description: handle the help stuff for goblins.
 */
int
help_goblin(string subject)
{
    CHECK_GOBLIN;

    if (subject != "emotes" && subject != "emotions")
      return 0;

    write("General Goblin Emotions:\n\n"+
      "(none yet, we are looking for suggestions! Please mail Krynn)\n"+
      "\n");
    return 1;
}

/*****************************************************************
 * Below follow the actual commands/emotes
 *****************************************************************/


