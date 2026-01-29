/* Elf soul
 * For the Krynn race guild by
 * ~Aridor 1/97
 *
 * Add emotes and commands used by ALL elves here into this file.
 * There is no need to change the ../race_soul.c file.
 * Warning: Watch for commands that are used by more than one race/
 *          tribe/region.
 */


/* Define used for all commands here in this file. If it returns 0,
 * the player cannot use this emote.
 */
#define CHECK_ELF;    if(TP->query_race_name() != "elf") return 0;
#define CHECK_DARK_ELF;    if(TP->query_region_title() != "dark elf") return 0;

/* Function:    query_cmdlist_*
 * Description: return all the commands that are available in this
 *              file.
 */
mapping
query_cmdlist_elf()
{
   return ([
	"ebow"		: 	"ebow",
	"eignore"	:	"eignore",
	"einspect"	:	"einspect",
	"eregard"	: 	"eregard",
	"estand"	:	"estand",
	"estudy"	:	"estudy",
	"etrace"	:	"etrace",
        ]);
}

/* Function:    help_*
 * Description: handle the help stuff for elves.
 */
int
help_elf(string subject)
{
    CHECK_ELF;

    if (subject != "emotes" && subject != "emotions")
    return 0;

    write("Elven Emotions:\n\n"+
      "ebow     - bow [how] [to someone]\n"+
      "eignore  - ignore [someone] as beneath your station\n"+
      "einspect - inspect [something/someone] [how]\n"+
      "eregard  - regard [someone] [how]\n"+
      "estand   - stand away from others, keeping to yourself\n"+
      "estudy   - study [something/someone] [how]\n"+
      "etrace   - ponder your elven heritage\n"+
      "(For further emote suggestions, please mail Krynn)\n" +
      "\n");
    return 1;
}

#ifdef ALLOW_SUBLOC_HIDING
mapping
query_cmdlist_elf_dark()
{
   return ([
	"dehide"        : 	"dehide",
        ]);
}

int
help_elf_dark(string subject)
{
    CHECK_DARK_ELF;

    if (subject != "emotes" && subject != "emotions")
    return 0;

    write("Dark Elf Emotions:\n\n"+
      "dehide   - hide your heritage from casual examination\n"+
      "           dehide -or- dehide [my] heritage <on|off>\n"+
      "\n");
    return 1;
}
#endif

/*****************************************************************
 * Below follow the actual commands/emotes
 *****************************************************************/

public int
ebow(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "with regal grace", 0);

    CHECK_ELF;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[before] [to] [the] %i");

    /* Setup failure message */
    notify_fail("Bow [how] to [whom]?\n");

    if (!strlen(how[0]))
    {

        write("You bow"+how[1] + ".\n");
        all(" bows"+how[1] + ".");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    if (how[1] == " with regal grace")
    {
	actor("You bow before", oblist, how[1]+".");
	target(" bows before you"+how[1]+".", oblist);
	all2act(" bows before",oblist, how[1]+".");
    }
    else
    {
	actor("You bow"+how[1]+" before", oblist, ".");
	target(" bows"+how[1]+" before you.", oblist);
	all2act(" bows"+how[1]+" before",oblist, ".");
    }

    return 1;
}


public int
eignore(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "haughtily", 1);
    string tmp;

    CHECK_ELF;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[the] %i");

    /* Setup failure message */
    notify_fail("Ignore [whom] [how]?\n");

    if (!sizeof(oblist))
    {
        return 0;
    }

    if (sizeof(oblist) > 1)
	tmp = "them";
       else
	tmp = OBJECTIVE(oblist[0]);

    actor("You turn away from",oblist,how[1]+", deeming "+tmp+" unworthy "+
	"of your attention.");
    target(" turns away from you"+how[1]+", deeming you unworthy of "+
	POSSESSIVE(TP)+" attention.", oblist);
    all2act(" turns away from",oblist,how[1]+", deeming "+tmp+" unworthy "+
	"of "+POSSESSIVE(TP)+" attention.");

    return 1;
}


public int
einspect(string str)
{
    object ob;
    string *how;

    CHECK_ELF;

    if (!str)
        str = "wielded weapon";

    how = parse_adverb_with_space(str, "carefully", 1);

    notify_fail("Inspect [what] [how]?\n");
    if (!parse_command(how[0], TP, "[my] [the] %o", ob))
        if (!parse_command(how[0], E(TP), "[my] [the] %o", ob))
	return 0;

    /* No argument given */
    if (!objectp(ob))
        return 0;

    if (IS_WEAPON_OBJECT(ob))
    {
        write("You inspect your "+ob->short()+how[1]+". "+
	    ob->wep_condition_desc());
	all(" inspects "+POSSESSIVE(TP)+" "+ob->short()+how[1]+".");
	return 1;
    }

    if (IS_ARMOUR_OBJECT(ob))
    {
        write("You inspect your "+ob->short()+how[1]+". "+
	    ob->arm_condition_desc());
	all(" inspects "+POSSESSIVE(TP)+" "+ob->short()+how[1]+".");
	return 1;
    }

    if (IS_LIVING_OBJECT(ob))
    {
	write("You inspect "+ob->query_the_name(TP)+how[1]+", taking "+
	    POSSESSIVE(ob)+" measure.\n");
	say(QCTNAME(TP)+" inspects "+QTNAME(ob)+how[1]+", taking "+
	    POSSESSIVE(ob)+" measure.\n", ({ ob, TP }));
        ob->catch_tell(TP->query_The_name(ob)+" inspects you"+how[1]+", "+
	    "seeming to take your measure.\n");
	return 1;
    }

    write("You inspect the "+ob->short()+how[1]+".\n");
    all(" inspects the "+ob->short()+how[1]+".\n");

    return 1;
}


public int
eregard(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "imperiously", 1);

    CHECK_ELF;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[the] %i");

    /* Setup failure message */
    notify_fail("Regard [whom] [how]?\n");

    if (!strlen(how[0]))
    {

        write("You regard your surroundings"+how[1] + ", maintaining the "+
		"august poise befitting an elf.\n");
        all(" looks around "+OBJECTIVE(TP)+"self"+how[1] + ", projecting "+
		"an august presence.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    actor("You regard",oblist,how[1]+", maintaining the august poise "+
	"befitting an elf.");
    target(" regards you"+how[1]+" with an august visage that reveals "+
	"nothing of "+POSSESSIVE(TP)+" thoughts.", oblist);
    all2act(" regards",oblist,how[1]+" with an august visage that "+
	"reveals nothing of "+POSSESSIVE(TP)+" thoughts.");

    return 1;
}


public int
estand(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "silently", 0);

    CHECK_ELF;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[away] [from] %i");

    /* Setup failure message */
    notify_fail("Stand [how] away from [someone]?\n");

    if (!strlen(how[0]))
    {

        write("You stand"+" apart from others"+how[1]+", remaining "+
	    "emotionally distant.\n");
        all(" stands apart from everyone"+how[1]+", reflecting an "+
	    "emotional distance.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    actor("You stand apart from",oblist,how[1]+", remaining "+
	"emotionally distant.");
    target(" stands apart from you"+how[1]+", reflecting an emotional "+
	"distance.", oblist);
    all2act(" stands apart from", oblist, how[1]+", reflecting an "+
	"emotional distance.");

    return 1;
}


public int
estudy(string str)
{
    object ob;
    string *how;

    CHECK_ELF;

    notify_fail("Study [what]/[whom] [how]?\n");
    if (!str)
    {
	write("You pause as your keen elven eyes study the "+
	    "surroundings confidently.\n");
	all(" pauses as "+POSSESSIVE(TP)+" keen elven eyes "+
	    "study the surroundings confidently.\n");
	return 1;
    }

    how = parse_adverb_with_space(str, "confidently", 1);

    if (!strlen(how[0]) ||
    (!parse_command(how[0], TP, "[my] [the] %o", ob) &&
    !parse_command(how[0], E(TP), "[my] [the] %o", ob)))
    {
	write("You pause as your keen elven eyes study the "+
	    "surroundings"+how[1]+".\n");
	all(" pauses as "+POSSESSIVE(TP)+" keen elven eyes "+
	    "study the surroundings"+how[1]+".\n");
	return 1;
    }

    /* No argument given */
    if (!objectp(ob))
        return 0;

    if (IS_LIVING_OBJECT(ob))
    {
	write("Your keen elven eyes bore into "+ob->query_the_name(TP)+
	    " as you stand motionless, studying "+OBJECTIVE(ob)+how[1]+".\n");
	say(QCTNAME(TP)+" stands motionless as "+POSSESSIVE(TP)+" keen "+
	    "elven eyes bore into "+QTNAME(ob)+", studying "+OBJECTIVE(ob)+
	    how[1]+".\n", ({ ob, TP }));
        ob->catch_tell(TP->query_The_name(ob)+" stands motionless as "+
	    POSSESSIVE(TP)+" keen elven eyes bore into you, studying "+
	    "you"+how[1]+".\n");
	return 1;
    }

    write("You pause as your keen elven eyes study the "+
	ob->short()+how[1]+".\n");
    all(" pauses, studying the "+ob->short()+how[1]+" with "+
	POSSESSIVE(TP)+" keen elven eyes.\n");
    return 1;
}


int
etrace(string str)
{
    string *how = parse_adverb_with_space(str, "absentmindedly", 0);

    CHECK_ELF;

    write("You"+how[1]+" trace your finger along the tip of "+
      "your pointed ear, pondering your elven heritage.\n");
    say(QCTNAME(TP)+how[1]+" traces "+POSSESSIVE(TP)+
      " finger along the tip of "+POSSESSIVE(TP)+" pointed ear, "+
      "pondering "+POSSESSIVE(TP)+" elven heritage.\n");
    return 1;
}


public int
dehide(string str)
{
    string arg;
    object hider = present(RACE_HIDER_NAME, TP);

    CHECK_DARK_ELF;

    if (!strlen(str))
    {
        arg = (objectp(hider) ? " " : " not ");
        NF("You are currently"+ arg +"hiding your heritage.\n");
        return 0;
    }

    parse_command(str, ({}), "[my] 'heritage' %w", arg);

    if (arg == "on")
    {
        if (objectp(hider))
        {
            write("You are already masking your racial heritage.\n");
            return 1;
        }

        setuid(); seteuid(getuid());
        catch(hider = clone_object(RACE_HIDER_OBJ));

        if (!objectp(hider))
        {
            write("There was an issue with hiding your heritage, "+
                "please mail Krynn about this.\n");
            return 1;
        }

        hider->move(TP, 1);
        write("You are now masking your racial heritage.\n");
        return 1;
    }
    else if (arg == "off")
    {
        if (!objectp(hider))
        {
            write("You are not currently masking your racial heritage.\n");
            return 1;
        }

        hider->remove_object();
        write("You will no longer mask your racial heritage.\n");
        return 1;
    }

    NF("Try "+ query_verb() +" [my] heritage <on|off>\n");
    return 0;
}
