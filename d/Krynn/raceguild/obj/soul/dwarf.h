/* Dwarf soul
 * For the Krynn race guild by
 * ~Aridor 12/96
 *
 * Add emotes and commands used by ALL dwarves here into this file.
 * There is no need to change the ../race_soul.c file.
 * Warning: Watch for commands that are used by more than one race/
 *          tribe/region.
 */


/* Define used for all commands here in this file. If it returns 0,
 * the player cannot use this emote.
 */
#define CHECK_DWARF;    if(TP->query_race_name() != "dwarf") return 0;


/* Function:    query_cmdlist_*
 * Description: return all the commands that are available in this
 *              file.
 */
mapping
query_cmdlist_dwarf()
{
    return (["xexclaim":"xexclaim",
      "xstare":"xstare",
      "xrefuse":"xrefuse",
    ]);
}

/* Function:    help_*
 * Description: handle the help stuff for dwarves.
 */
int
help_dwarf(string subject)
{
    CHECK_DWARF;

    if (subject != "emotes" && subject != "emotions")
	return 0;

    write("General Dwarf Emotions:\n\n"+
      "xexclaim   - By Reorx!\n" +
      "xstare     - stare <at someone>\n"+
      "(For further emote suggestions, please mail Krynn)\n" +
      "\n");
    return 1;
}

/*****************************************************************
 * Below follow the actual commands/emotes
 *****************************************************************/


/*********************** xexclaim ***********************************/
int
xexclaim(string str)
{
    object *oblist;

    CHECK_DWARF;

    /*if (!str) for now, allow only 'By Reorx!'. Might add others later, or even free text. */
    {
	write("By Reorx!!\n");
	say(QCTNAME(TP)+" exclaims: By Reorx!\n");
	return 1;
    }

    if (!strlen(str))
    {
	notify_fail("Exclaim what?\n");
	return 0;
    }

    write(str);
    say(QCTNAME(TP) + " exclaims: " + str + "\n");
    return 1;
}

/*********************** xstare ***********************************/
int
xstare(string str)
{
    object *oblist;

    CHECK_DWARF;

    if (!str)
    {
	write("You stare into the air.\n");
	say(QCTNAME(TP)+" stares into the air, " + HIS(TP) + " face so emotionless " +
	  "you would swear it was set in stone.\n");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});

    if ((!strlen(str)) || (!sizeof(oblist)))
    {
	notify_fail("Stare at whom?\n");
	return 0;
    }

    actor("You stare at", oblist, ".");
    targetbb(" stares at you, " + HIS(TP) + " face so emotionless you " +
      "would swear it was set in stone.", oblist);
    all2actbb(" stares at ", oblist, ", " + HIS(TP) + " face so " +
      "emotionless you would swear it was set in stone.");
    return 1;
}

/*********************** xrefuse **********************************/
int
xrefuse(string str)
{
    object *oblist, ob;

    CHECK_DWARF;

    if (!str)
    {
	write("You stubbornly refuse to take another cursed boatride!\n");
	say(QCTNAME(TP)+" makes it clear to everyone that " +
	  HE(TP) + " refuses to take another cursed boatride!\n");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});

    if ((!strlen(str)) || (!sizeof(oblist)))
    {
	notify_fail("Refuse to follow whom on a boatride?\n");
	return 0;
    }

    ob = oblist[0];
    
    actor("You make it clear to", oblist, " that you refuse " +
      "to follow " + HIM(ob) + " on yet another cursed boatride!");
    targetbb(" makes it clear to you that " + HE(TP) + " refuses " +
      "to follow you on yet another cursed boatride", oblist);
    all2actbb(" makes it clear to ", oblist, " that " +
      HE(TP) + " refuses to take yet another cursed boatride!");
    return 1;
}
