/* Kender soul
 * For the Krynn race guild by
 * ~Aridor 03/97
 *
 * Add emotes and commands used by ALL kender here into this file.
 * There is no need to change the ../race_soul.c file.
 * Warning: Watch for commands that are used by more than one race/
 *          tribe/region.
 *
 * February 8, 2000: added slip - Gwyneth
 *
 * March 29, 2000: fixed small bug with slip
 */


/* Define used for all commands here in this file. If it returns 0,
 * the player cannot use this emote.
 */
#define CHECK_KENDER;    if(TP->query_race_name() != "kender") return 0;



/*
klook: Elwin looks around curiously for something useless to play with.
ksincere: Elwin trys to look sincre.
kbow; As Elwin bows, several borroed goods fall from his pockets.
kinnocent: Elwin says: I was only polishing it!
*/



/* Function:    query_cmdlist_*
 * Description: return all the commands that are available in this
 *              file.
 */
mapping
query_cmdlist_kender()
{
    return (["kstare":"kstare",
	     "ktease" : "ktease",
	     "ktrace" : "ktrace",
	     "ksmile" : "ksmile",
	     "koops" : "koops",
	     "kbored" : "kbored",
	     "kpray" : "kpray",
	     "kbrighten" : "kbrighten",
	     "kchatter" : "kchatter",
	     "kwonder" : "kwonder",
	     "kgasp" : "kgasp",
	     "kready" : "kready",
	     "klust" : "klust",
	     "slip" : "slip",
	     ]);
}

/* Function:    help_*
 * Description: handle the help stuff for kender.
 */
int
help_kender(string subject)
{
    CHECK_KENDER;

    if (subject != "emotes" && subject != "emotions")
	return 0;

    write("Kender Emotions:\n\n"+
	  "<> refers to optional commands.\n" +
	  "[] refers to necessary input.\n\n" +
	  "kbored - Express to others your boredeom.\n" +
	  "kbrighten - Brighten up with the thought of excitement ahead.\n" +
	  "kchatter <string> - Chatter about something.\n" +
	  "kgasp - Gasp in shock at being called a thief!\n" +
	  "klust - Feel overwhelmed with wanderlust.\n" +
	  "koops - Yes, that well feared word.\n" +
	  "kpray <god> - utter a prayer you borrowed from someone.\n" +
	  "kready - Show you are ready and eager for the road ahead.\n" +
	  "ksmile - Smile like a kender.\n" +
	  "kstare <person> - Stare at someones pockets curiously.\n" +
	  "ktease [person] [something] - Tease someone about something.\n" +
	  "ktrace - Absentmindedly play with one of your ears.\n" +
	  "kwonder <person> - Stare in wonder at something.\n" +
	  "slip <item into/in container> - Try to slip something into your " + 
              "pouch unnoticed.\n" +
	  "\nAny emote suggestions please send to the Ansalon domain.\n\n" +
	  "\n");
    return 1;
}

/*****************************************************************
 * Below follow the actual commands/emotes
 *****************************************************************/


/*********************** xstare ***********************************/
int
kstare(string str)
{
    object *oblist;

    CHECK_KENDER;

    if (!str)
    {
	write("You look curiously at everything.\n");
	say(QCTNAME(TP)+" is filled with wonder about all the nice things here " +
	    "and eyes them curiously.\n");
	return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({TP});
    
    if ((!strlen(str)) || (!sizeof(oblist))) 
    {
	notify_fail("Stare at whom?\n");
	return 0;
    }
    
    actor("You look curiously at", oblist, " wondering about all the fun things " +
	  "people have in their pockets.");
    targetbb(" stares curiously at you and especially your pockets.", oblist);
    all2actbb(" stares in wonder at", oblist, ".");
    return 1;
}

int
ktease(string str)
{
    object *pers;
    string str1, str2;
    
    CHECK_KENDER;
    
    NF("Tease who about what?\n");
    if (!str)
      return 0;
    if (sscanf(str, "%s %s", str1, str2) != 2)
      return 0;
    pers = FILTER_OTHER_LIVE(FIND_STR_IN_OBJECT(str1, E(TP)));
    if (!pers || !sizeof(pers))
      return 0;
    
    tell_room(E(TP), QCTNAME(TP) + " teases " +COMPOSITE_LIVE(pers) +
	      " incessantly about " +str2+ "\n", pers + ({TP}));
    TP->catch_msg("You tease " +QCOMPLIVE+ " incessantly about " +str2+ "\n");
    pers->catch_msg(QCTNAME(TP)+ " teases you incessantly about " +str2+ "\n");
    return 1;
}

int
ktrace(string str)
{
    CHECK_KENDER;
    
    if (str)
      return 0;
    
    write("You absentmindedly trace a finger along " +
	  "one of your pointy, elfin ears.\n");
    say(QCTNAME(TP)+ " absentmindedly traces a finger " +
	"along one of " +HIS(TP)+ " pointy, elfin ears.\n");
    return 1;
}

int
ksmile(string str)
{
    object *oblist;
    oblist = parse_this(str, "[at] [the] %l");

    if (!strlen(str))
    {
        write("You smile with the innocence of a child.\n");
        all(" smiles with the innocence of a child.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        NF("Smile at who?\n");
        return 0;
    }

    actor("You smile up at", oblist, " with the innocence of a child.");
    target(" smiles up at you with the innocence of a " +
        "child.", oblist);
    all2act(" smiles up at", oblist, " with the innocence " +
        "of a child.");
    return 1;
}

int
koops(string str)
{
    CHECK_KENDER;

    if (str)
      return 0;
    
    write("You look up wide-eyed and say: Oops!\n");
    say(QCTNAME(TP) + " looks up wide-eyed and says that " +
	"awful word that sends most adventurers experienced " +
	"with kenders running, 'Oops!'.\n");
    return 1;
}


int
kbored(string str)
{
    CHECK_KENDER;
    if (str)
    {
	notify_fail("Do what?\n");
	return 0;
    }

    write("You begin to feel bored. You wonder what you " +
	  "can do to make things a little more interesting?\n");
    say(QCTNAME(TP) + " begins to look bored, never " +
	"a good sign considering the mischievous nature " +
	"of kenders.\n");
    return 1;
}


int
kpray(string str)
{
    string god_name;
    
    CHECK_KENDER;
    
    if (!str || str == "reorx")
    {
	write("You utter an oath to " +
	      "Reorx that you once heard a dwarf use.\n");
	say(QCTNAME(TP) + " utters an oath to Reorx, one " +
	    HE(TP)+ " probably borrowed off some dwarf.\n");
	return 1;
    }
    if (str == "paladine")
      god_name = "Paladine, Father of Good";
    else if (str == "kiri jolith" || str == "kiri-jolith")
      god_name = "Kiri-Jolith";
    else if (str == "habbaukuk")
      god_name = "Habbaukuk, the Fisher King";
    else if(str == "mishakal")
      god_name = "Mishakal, the Healer";
    else if(str == "branchala")
      god_name = "Branchala, the Songmaster";
    else if(str == "solinari")
      god_name = "Solinari, god of Good Magic";
    else if(str == "chislev")
      god_name = "Chislev, the Wild One";
    else if(str == "gilean")
      god_name = "Gilean, the Gate of Souls";
    else
    {
	write("You don't know a god by that name.\n");
	return 1;
    }
    
    write("You whisper a prayer you overheard in your " +
	  "travels to " +god_name+ ".\n");
    say(QCTNAME(TP) + " whispers a prayer to " +god_name+
	", one " +HE(TP)+ " probably borrowed in " +HIS(TP)+
	" travels.\n");
    return 1;
}

int
kbrighten(string str)
{
    CHECK_KENDER;
    
    if (str)
    {
	notify_fail("Brighten how?\n");
	return 0;
    }
    
    write("You brighten at the thought of there being " +
	  "something dangerous, albeit interesting, ahead.\n");
    say(QCTNAME(TP)+ "'s eyes brighten at the thought of something " +
	"dangerous ahead.\n");
    return 1;
}

int
kchatter(string str)
{
    CHECK_KENDER;

    if (!str)
    {
	write("You chatter merrily about nothing in particular.\n");
	say(QCTNAME(TP) + " chatters merrily about nothing " +
	    "in particular.\n");
	return 1;
    }
    
    write("You chatter merrily about " +str + "\n");
    say(QCTNAME(TP) + " chatters merrily about " +str+ "\n");
    return 1;
}

int
kwonder(string str)
{
    object *oblist;

    CHECK_KENDER;

    if (!str)
    {
	write("You stare around in wonder and absolute fascination.\n");
	say(QCTNAME(TP) + " stares around in wonder and absolute fascination.\n");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");
    oblist -= ({TP});

    if ((!strlen(str)) || (!sizeof(oblist)))
    {
	notify_fail("Stare in wonder at whom or what?\n");
	return 0;
    }
    
    actor("You stare with wonder and absolute " +
          "fascination at", oblist, ".");
    targetbb(" stares with wonder and absolute " +
	     "fascination at you.",oblist);
    all2actbb(" stares in wonder and absolute fascination " +
	      "at",oblist,".");
    return 1;
}

int
kgasp(string str)
{
    CHECK_KENDER;
 
    if (str)
    {
	notify_fail("Too difficult to gasp in " +
		    "indignation another way...\n");
	return 0;
    }
    
    write("You gasp in shock and indignation " +
	  "at being referred to as a thief!\n");
    say(QCTNAME(TP) + " gasps in shock and indignation at " +
	"being referred to as a thief!\n");
    return 1;
}

int
kready(string str)
{
    CHECK_KENDER;

    if (str)
    {
	notify_fail("Do what?\n");
	return 0;
    }
    
    write("You bounce around eagerly, ready for the " +
	  "road ahead.\n");
    say(QCTNAME(TP) + " bounces around eagerly, ready " +
	"for the road ahead.\n");
    return 1;
}

int
klust(string str)
{
    CHECK_KENDER;

    if (str)
      return 0;

    write("You suddenly feel overwhelmed with the desire to wander.\n");
    say(QCTNAME(TP) + "'s eyes suddenly blaze with " +
	"wanderlust.\n");
    return 1;
}

/* Function name : slip
 * Description   : Slip an object into a container without notice
*/

int
slip(string str)
{
    object *item, *pouch, *watchers, *is_wiz;
    string str1, str2;
    int siz_watchers, task, modifier;

    if (!str)
    {
        NF("Slip what into where?\n");
        return 0;
    }

    sscanf(str, "%s into %s", str1, str2);
    if (!strlen(str1))
    {
        NF("Slip what into where?\n");
        return 0;
    }

    if (!strlen(str2))
    {
        NF("Slip what into where?\n");
        return 0;
    }

    if (!parse_command(str1, (all_inventory(TP)), "[the] %i", item))
    {
        NF("Slip what into where?\n");
        return 0;
    }

    item = NORMAL_ACCESS(item, 0, 0);

    if (sizeof(item) > 1)
    {
        NF("Slip only one thing at a time.\n");
        return 0;
    }

    if (sizeof(item) == 0)
    {
        NF("Slip what into where?\n");
        return 0;
    }

    if (item[0]->query_prop(OBJ_M_NO_DROP))
    {
        NF("You can't drop that.\n");
        return 0;
    }

    if (!parse_command(str2, (all_inventory(TP)), "[the] %i", pouch))
    {
        NF("Slip what into where?\n");
        return 0;
    }

    pouch = NORMAL_ACCESS(pouch, 0, 0);

    if (sizeof(pouch) > 1)
    {
        NF("You can't slip something into more than one container " +
            "at a time.\n");
        return 0;
    }

    if (sizeof(pouch) == 0)
    {
        NF("Slip what into where?\n");
        return 0;
    }

    if (pouch[0]->query_prop(CONT_I_CLOSED))
    {
        NF("It's awfully hard to slip something into a closed " +
            "container.\n");
        return 0;
    }

    if (!pouch[0]->query_prop(CONT_I_IN))
    {
        NF("Slip something into a container, will you?\n");
        return 0;
    }

    if (item[0]->query_prop(CONT_I_IN))
    {
        NF("That's not a good place to put that.\n");
        return 0;
    }

    if (item[0]->move(pouch[0]) != 0)
    {
        NF("You failed to slip the " + item[0]->short() + " into your " +
            pouch[0]->short() + ".\n");
        return 0;
    }

    watchers = FILTER_OTHER_LIVE(all_inventory(E(TP)));
    watchers -= ({ TP });
    is_wiz = FILTER_IS_WIZARD(watchers);
    watchers -= is_wiz;
    siz_watchers = sizeof(watchers);

    TP->catch_msg("You slip a " + item[0]->short() + " into a " +
        pouch[0]->short() + ".\n");

    while (siz_watchers--)
    {
        if (!CAN_SEE_IN_ROOM(watchers[siz_watchers]) ||
            !CAN_SEE(watchers[siz_watchers], TP))
        {
            continue;
        }

        modifier = item[0]->query_prop(OBJ_I_VOLUME);
        modifier /= 200;

        task = TP->resolve_task(TASK_ROUTINE, SS_HIDE, watchers[siz_watchers],
            (SS_AWARENESS + modifier));

        if (task > 0)
        {
            continue;
        }

        if (TP->query_skill(SS_HIDE) <
            (watchers[siz_watchers]->query_skill(SS_AWARENESS) / 2))
        {
            watchers[siz_watchers]->catch_msg(QCTNAME(TP) + " slips " +
                item[0]->short() + " into " + HIS(TP) + " " +
                pouch[0]->short() + ".\n");
        }

        else
        {
            watchers[siz_watchers]->catch_msg(QCTNAME(TP) + " slips " +
                "something into " + HIS(TP) + " " + pouch[0]->short() +
                ".\n");
        }
    }

    if (sizeof(is_wiz))
    {
        is_wiz->catch_msg(QCTNAME(TP) + " slips " + item[0]->short() +
            " into " + HIS(TP) + " " + pouch[0]->short() + ".\n");
    }

    return 1;
}

