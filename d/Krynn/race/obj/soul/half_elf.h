/* Half-Elven soul by Morrigan and Teth
 * Adapted for the Krynn race guild by
 * ~Aridor 12/96
 *
 * Add emotes and commands used by half-elves here into this file.
 * There is no need to change the ../race_soul.c file.
 * Warning: Watch for commands that are used by more than one race/
 *          tribe/region.
 */

/* Define used for all commands here in this file. If it returns 0,
 * the player cannot use this emote.
 */
#define CHECK_HALF_ELF;    if(TP->query_region_title() != "half-elf" && \
                              TP->query_region_title() != "half-human") return 0;


/* Function:    query_cmdlist_*
 * Description: return all the commands that are available in this
 *              file.
 */
mapping
query_cmdlist_half_elf()
{
    return (["xblush":"xblush",
      "xbow":"xbow",
      "xcurtsey":"xcurtsey",
      "xdare":"xdare",
      "xdecline":"xdecline",
      "xlook":"xlook",
      "xgrim":"xgrim",
      "xsmile":"xsmile",
      "xtrace":"xtrace",
      "xscowl":"xscowl",
      "xstand":"xstand",
      "xhelp":"help_half_elf",
    ]);
}

/* Function:    help_*
 * Description: handle the help stuff for half elves.
 */
int
help_half_elf(string subject)
{
    CHECK_HALF_ELF;

    if (subject != "emotes" && subject != "emotions")
	return 0;

    write("Half-Elf Emotions:\n\n"+
      "xblush   - blush about your mixed heritage <at someone>\n"+
      "xbow     - bow gracefully <before someone>\n"+
      "xcurtsey - curtsey gracefully <before someone>\n"+
      "xdare    - grin daringly <at someone>\n"+
      "xdecline - decline <someone's> offer of companionship\n"+
      "xlook    - look defiantly around <or at someone>\n"+
      "xgrim    - feel grim and alone as you ponder your place in Krynn\n"+
      "xsmile   - smile joyfully <at someone>\n"+
      "xtrace   - ponder your elven heritage\n"+
      "xscowl   - scowl bitterly as you recall the haughty elves\n"+
      "xstand   - stand away from others, keeping to yourself\n"+
      "(For further emote suggestions, please 'mail krynn')\n" +
      "\n");
    return 1;
}

/*****************************************************************
 * Below follow the actual commands/emotes
 *****************************************************************/

/*********************** xblush **********************************/
int
xblush(string str)
{

    object *oblist;
    string feature;

    CHECK_HALF_ELF;

    if (TP->query_race() == "elf")
	feature = "human";
    else
	feature = "elven";

    if (!str)
    {
	write("You blush in embarassment at the notice of your distinctly "+
	  feature+" features.\n");
	say(QCTNAME(TP)+" blushes in embarassment at the notice of "+
	  POSSESSIVE(TP)+" distinctly "+feature+" features.\n");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});

    if ((!strlen(str)) || (!sizeof(oblist))) 
    {
	notify_fail("Blush at whom?\n");
	return 0;
    }

    actor("You blush as", oblist, " points out your distinctly "+feature+
      " features.");
    targetbb(" blushes as you point out "+POSSESSIVE(TP)+" distinctly "+
      feature+" features.", oblist);
    all2actbb(" blushes as", oblist, " points out "+POSSESSIVE(TP)+
      " distinctly "+feature+" features.");
    return 1;
}

/*********************** xbow **********************************/
int
xbow(string str)
{

    object         *oblist;

    CHECK_HALF_ELF;

    if (!str)
    {
	write("You bow with measured grace.\n");
	say(QCTNAME(TP)+" bows with measured grace.\n");
	return 1;
    }

    oblist = parse_this(str, "[before] [the] %l");
    oblist -= ({TP});

    if ((!strlen(str)) || (!sizeof(oblist))) 
    {
	notify_fail("Bow before whom?\n");
	return 0;
    }

    actor("You bow before", oblist, " with measured grace.");
    targetbb(" bows before you with measured grace.", oblist);
    all2actbb(" bows before", oblist, " with measured grace.");
    return 1;
}

/********************** xcurtsey ********************************/
int
xcurtsey(string str)
{

    object         *oblist;

    CHECK_HALF_ELF;

    if (!str)
    {
	write("You curtsey with measured grace.\n");
	say(QCTNAME(TP)+" curtseys with measured grace.\n");
	return 1;
    }

    oblist = parse_this(str, "[before] [the] %l");
    oblist -= ({TP});

    if ((!strlen(str)) || (!sizeof(oblist))) 
    {
	notify_fail("Curtsey before whom?\n");
	return 0;
    }

    actor("You curtsey before", oblist, " with measured grace.");
    targetbb(" curtseys before you with measured grace.", oblist);
    all2actbb(" curtseys before", oblist, " with measured grace.");
    return 1;
}

/*********************** xdare **********************************/
int
xdare(string str)
{

    object         *oblist;

    CHECK_HALF_ELF;

    if (!str)
    {
	write("You grin daringly.\n");
	say(QCTNAME(TP)+" grins daringly.\n");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});

    if ((!strlen(str)) || (!sizeof(oblist)))
    {
	notify_fail("Grin at whom?\n");
	return 0;
    }

    actor("You grin daringly at", oblist, ".");
    targetbb(" grins daringly at you.", oblist);
    all2actbb(" grins daringly at", oblist, ".");
    return 1;
}

/********************* xdecline ********************************/
int
xdecline(string str)
{

    object         *oblist;
    string          offer;

    CHECK_HALF_ELF;

    if (!str)
    {
	write("You decline the offers of companionship, preferring "+
	  "comfortable solitude.\n");
	say(QCTNAME(TP)+" declines the offers of companionship, "+
	  "preferring comfortable solitude.\n");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");
    oblist -= ({TP});

    if ((!strlen(str)) || (!sizeof(oblist))) 
    {
	notify_fail("Decline who's offer?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
	offer = "offers";
    else
	offer = "offer";

    actor("You decline", oblist, "'s "+offer+" of companionship, "+
      "preferring comfortable solitude.");
    targetbb(" declines your offer of companionship, preferring "+
      "comfortable solitude.", oblist);
    all2actbb(" declines", oblist, "'s "+offer+" of companionship, "+
      "preferring comfortable solitude.");
    return 1;
}

/*********************** xgrim **********************************/
int
xgrim(string str)
{
    CHECK_HALF_ELF;

    NF("Feel grim how?\n");
    if (str)
	return 0;

    write("A grim and lonely feeling settles over you as you "+
      "think of how your impure blood prevents you from fitting "+
      "in anywhere...\n");
    say(QCTNAME(TP)+"'s face settles into a grim expression as "+
      PRONOUN(TP)+" thinks of "+POSSESSIVE(TP)+" impure blood.\n");
    return 1;
}

/*********************** xlook **********************************/
int
xlook(string str)
{
    object         *oblist;

    CHECK_HALF_ELF;

    if (!str)
    {
	write("You place your hands on your hips defiantly and look "+
	  "coolly around.\n");
	say("Placing "+POSSESSIVE(TP)+" hands defiantly on "+POSSESSIVE(TP)+
	  " hips, "+QTNAME(TP)+" looks coolly around.\n");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});

    if ((!strlen(str)) || (!sizeof(oblist))) 
    {
	notify_fail("Look at whom?\n");
	return 0;
    }

    actor("You place your hands on your hips defiantly and look "+
      "coolly at", oblist, ".");
    targetbb(" places "+POSSESSIVE(TP)+" hands defiantly on "+
      POSSESSIVE(TP)+" hips and looks coolly at you.", oblist);
    all2actbb(" places "+POSSESSIVE(TP)+" hands defiantly on "+
      POSSESSIVE(TP)+" hips and looks coolly at", oblist, ".");
    return 1;
}

/*********************** xsmile **********************************/
int
xsmile(string str)
{
    object         *oblist;
    string             adj;

    CHECK_HALF_ELF;

    if (TP->query_gender() == 1)
	adj = "beautiful";
    else
	adj = "handsome";

    if (!str)
    {
	write("You smile softly in joy.\n");
	say(QCTNAME(TP)+" smiles, the "+adj+" features of "+
	  POSSESSIVE(TP)+" face revealing a soft joy.\n");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});

    if ((!strlen(str)) || (!sizeof(oblist))) 
    {
	notify_fail("Smile at whom?\n");
	return 0;
    }

    actor("You smile softly at", oblist, " in joy.");
    targetbb(" smiles at you, the "+adj+" features of "+POSSESSIVE(TP)+
      " face revealing a soft joy.", oblist);
    all2actbb(" smiles at", oblist, " the "+adj+" features of "+
      POSSESSIVE(TP)+" face revealing a soft joy.", oblist);
    return 1;
}

/*********************** xscowl **********************************/
int
xscowl(string str)
{
    object         *oblist;

    CHECK_HALF_ELF;

    if (!str)
    {
	write("You scowl bitterly as you think of the haughty elves "+
	  "who shun your kind.\n");
	say(QCTNAME(TP)+" scowls bitterly, thinking of the haughty "+
	  "elves who shun "+POSSESSIVE(TP)+" kind.\n");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});

    if ((!strlen(str)) || (!sizeof(oblist))) 
    {
	notify_fail("Scowl at whom?\n");
	return 0;
    }

    actor("You scowl bitterly at", oblist, " as you think of the "+
      "haughty elves who shun your kind.");
    targetbb(" scowls bitterly at you, thinking of the haughty elves "+
      "who shun "+POSSESSIVE(TP)+" kind.", oblist);
    all2actbb(" scowls bitterly at", oblist, ", thinking of the haughty "+
      "elves who shun "+POSSESSIVE(TP)+" kind.");
    return 1;
}

/************************* xstand **********************************/
int
xstand(string str)
{
    CHECK_HALF_ELF;

    NF("Stand how?\n");
    if (str)
	return 0;

    write("You stand apart from the others, feeling uncomfortable in "+
      "the crowd.\n");
    say(QCTNAME(TP)+" stands apart from the crowd, looking a bit "+
      "uncomfortable.\n");
    return 1;
}

/************************** xtrace ********************************/
int
xtrace(string str)
{
    CHECK_HALF_ELF;

    NF("Trace how?\n");
    if (str)
	return 0;

    write("You absentmindedly trace your finger along the tip of "+
      "your pointed ear, pondering your elven heritage.\n");
    say(QCTNAME(TP)+" absentmindedly traces "+POSSESSIVE(TP)+
      " finger along the tip of "+POSSESSIVE(TP)+" pointed ear, "+
      "pondering "+POSSESSIVE(TP)+" elven heritage.\n");
    return 1;
}
