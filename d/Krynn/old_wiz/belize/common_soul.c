/*
 * Common soul for the Wizards of High Sorcery
 *
 * First prototype by Rastlin.
 * Emotes has been suggested by Alustrial, Teth
 * and Jeremiah.
 *
 * Note: When adding commands to the soul, think of the
 * gender of the actor. The appearens might be different.
 */

/*
 * NOTE:
 *  wfinger - doesn't work properly.. Shamus's fingers->Shamus' fingers
 *  wgaze - (see wfinger)
 *  wpouch - (see wfinger) Do we need the emote at all?
 */

#define ROBE_WORN(x)           (present(GUILD_OBJECT, x)->query_worn())
#define GET_ROBE(x)            (present(GUILD_OBJECT, x))
#define DOC_GUILD              ({"wizard", "wohs", "guild"})
#define SOULDESC(x)            (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define LANG_OBJ               GOBJ + "language_obj"

#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <options.h>

/*
 * The list of verbs and functions. Please add new in alphabetical order.
 */
public mapping
query_common_cmdlist()
{
    return ([  "help" : "whelp",
	       "wait" : "wait",
               "wbow" : "wbow", 
       "wconcentrate" : "wconcentrate", 
               "wcon" : "wconcentrate", 
             "wcough" : "wcough",
           "wcurtsey" : "wbow", 
	   "wdismiss" : "wdismiss",
            "wfinger" : "wfinger",
             "wfrown" : "wfrown",
              "wfury" :	"wfury",
	      "whelp" : "whelp",
	    "wignore" : "wignore",
              "wlean" : "wlean", 
              "wpace" : "wpace", 
             "wpouch" : "wpouch", 
               "wrap" : "wrap",
              "wrobe" : "wdust", 
           "wrubbish" : "wrubbish", 
            "wsilent" : "wsilent", 
               "wsay" : "wsay",
             "wslump" : "wslump", 
             "wsmirk" : "wsmirk",
             "wstare" : "wstare",          
             "wstudy" : "wstudy",         
	      "wtest" : "wtest",
	     "wtrick" : "wtrick"
          ]);
}

/*
 * Here follows the actual functions. Please add new in alphabetical order.
 */
public int
wait(string str)
{
    object *oblist;
    string tmp;
    int size;

    NF("Wait on whom?\n");
    
    tmp = "places her hands on her hips";
    if ((TP->query_gender() == G_MALE) || (TP->query_gender() == G_NEUTER))
        tmp = "folds " + POSSESSIVE(TP) + " arms across " + POSSESSIVE(TP) +
	      " chest";
    
    if (!str)
    {
        SOULDESC("waiting for something");
        
        write("You let everyone know that you are awaiting their " +
	      "attention.\n");
	all(" " + tmp + " and glares angrily around, obviously wanting " +
	    "your attention.");
	return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    
    if (!(size = sizeof(oblist)))
        return 0;

    target(" " + tmp + " and glares angrily at you, obviously wanting " +
           "your attention.", oblist);
    actor("You glare angrily at", oblist, " letting " + 
	  (size > 1 ? "them" : OBJECTIVE(oblist[0])) + " know you want " +
	  (size > 1 ? "their" : POSSESSIVE(oblist[0])) + " attention.");
    all2act(tmp + " and glares angrily at", oblist, ", obviously " +
            "wanting " + (size > 1 ? "their" : POSSESSIVE(oblist[0])) + 
	    " attention.");
    return 1;
}

public int
wbow(string str)
{
    object *oblist;
    string tmp, his_her = POSSESSIVE(TP);
    string vb = query_verb();

    NF((vb == "wbow" ? "Bow" : "Curtsey") + " to whom?\n");
    
    tmp = "curtsey";
    if (vb == "wbow")
        tmp = "bow";

    if (!str)
    {
        if (ROBE_WORN(TP))
	{
	    if (TP->query_wohs_hooded())
	    {
	        write("You throw back your hood and " + tmp + " formally.\n");
		all(" throws back " + his_her + " hood, and " + tmp + 
		    "s formally, " + his_her + " robe rustling softly.");
		TP->remove_wohs_hood_shadow();
		return 1;
	    }

	    write("You " + tmp + " formally.\n");
	    all(" " + tmp + "s formally, " + his_her + " robe rustling " +
		"softly.");
	    return 1;
	}

	write("You " + tmp + " formally.\n");
        all(" " + tmp + "s formally.");

        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    
    if (!sizeof(oblist))
        return 0;

    if (ROBE_WORN(TP))
    {
        if (TP->query_wohs_hooded())
	{
	    target(" throws back " + his_her + " hood, and " + tmp + "s " +
		   "formally to you, " + his_her + " robe making a soft " +
		   "rustle.", oblist);
	    actor("You throw back your hood and " + tmp + " formally to",
		  oblist, ", your robe rustling softly.");
	    all2act(" throws back the hood on " + his_her + " robe, as " +
		    PRONOUN(this_player()) + " " + tmp + "s formally "+
		    "to", oblist, ".");
	    TP->remove_wohs_hood_shadow();
	    return 1;
	}

	target(" " + tmp + "s formally to you, " + his_her + " robe " +
	       "making a soft rustle.", oblist);
	actor("You " + tmp + " formally to", oblist, ", your robe " +
	      "rustling softly.");
	all2act(tmp + "s formally to", oblist, ".");
	return 1;
    }

    target(" " + tmp + "s formally to you.", oblist);
    actor("You " + tmp + " formally to", oblist, ".");
    all2act(tmp + "s formally to", oblist, ".");

    return 1;
}

public int
wconcentrate(string str)
{
    if (strlen(str))
        return NF("Concentrate on what?\n");

    write("You close your eyes in concentration, going over your "+
          "spells in preparation for battle.\n");
    all(" closes " + POSSESSIVE(TP) + " eyes and mumbles the "+
        "words to " + POSSESSIVE(TP) + " spells over and over, "+
        "making certain that " + PRONOUN(TP) + " has them memorized.");
    return 1;
}

public int
wcough(string str)
{
    if (strlen(str))
        return NF("Cough how?\n");
        
    if (ADMIN->query_member_type(TP) == TYPE_APPRENTICE)
    {
        TP->catch_msg("But you haven't taken the Test yet and you are " +
            "feeling rather ok!\n");
        return 1;
    }

    write("You go into a convulsive cough. After it is over, you wipe " +
        "some some blood from the corner of your mouth with a piece of " +
        "cloth.\n");
    all(" goes into a convulsive cough. When it's over " + HE(TP) + 
       " wipes some blood from the corner of " + HIS(TP) + " mouth with " +
       "a small piece of cloth.");
       
    return 1;
}


public int
wdismiss(string str)
{
    string *how, *rest, tarstr, allstr;
    object *oblist;

    NF("Dismiss whom?\n");

    if (!str || !strlen(str))
        return 0;

    how = parse_adverb(str, "kindly", 0);
    
    if (!strlen(how[0]))
        return 0;

    rest = explode(how[0], " ");

    oblist = parse_this(rest[0], "%l");

    if (!sizeof(oblist))
        return 0;

    if (sizeof(rest) > 1)
    {
        str = implode(rest[1..sizeof(rest)], " ");
        tarstr = allstr = "saying: " + str;
    }
    else
    {
        allstr = "dismissing " + (sizeof(oblist) > 1 ? "them" : 
              OBJECTIVE(oblist[0])) + ".";
        tarstr = "dismissing you.";
    }

/*
    target(" " + how[1] + " waves a hand in your direction " + tarstr, 
           oblist);
    all2act(how[1] + " waves a hand in", oblist, " direction " + allstr);
    actor("You " + how[1] + " wave a hand in", oblist, " direction " +
          allstr);
*/
    target(" " + how[1] + " waves a hand in your direction " + tarstr,
        oblist);
    all2act(how[1] + " waves a hand in the direction of", oblist,
        ", " + allstr);
    actor("You " + how[1] + " wave a hand in the direction of", oblist,
        ", " + allstr);

    return 1;     
}

public int
wdust(string str)
{
    NF("Dust what?\n");

    if (strlen(str))
        return 0;

    if (ROBE_WORN(TP))
    {
        write("You absentmindedly smooth your robe, making sure that it "+
	      "is, as always, flawless.\n");
        all(" absentmindedly smooths " + POSSESSIVE(TP) + " " +
            GET_ROBE(TP)->query_robe_color() + " robe.");
	return 1;
    }

    return 0;
}

public int
wfinger(string str)
{
    if (strlen(str))
        return NF("Finger what?\n");

    write("You gently run your fingers across your spellbook, wiping "+
          "the dust from it.\n");
    all("'s fingers lightly brush the dust from " + POSSESSIVE(TP) + 
        " spellbook, lingering fondly on the cover.");
    return 1;
}

public int
wfrown(string str)
{
    object *oblist;
    
    if (!strlen(str))
    {
        write("You pause and frown, clearly showing your irritation by the "+
            "interruption.\n");
        allbb(" pauses and frowns, clearly showing " + HIS(TP) + " irritation "+
            "by the interruption.");
        
        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist = oblist - ({ TP });
    
    if (!sizeof(oblist))
        return NF("Frown at whom?\n");
        
    if (sizeof(oblist) > 1)
        return NF("Please be a bit more precise - who do you want to frown "+
            "at?\n");

    actor("You pause and frown, cleary showing your irritation at", oblist,
        "'s interruption.");
    targetbb("pauses and frowns, clearly showing " + HIS(TP) + 
        " irritation at your interruption.");
    all2actbb(" pauses and frowns, clearly showing " + HIS(TP) + 
        " irritation at", oblist, "'s interruption.");
        
   return 1;
}

public int
wfury(string str)
{
    object *oblist;
    string *how;
    int wis_diff;
    
    oblist = parse_this(str, "[at] [the] %l");
    
    if (!sizeof(oblist))
        return NF("Look at whom?\n");
        
    if (sizeof(oblist) > 1)
        return NF("You can look this way only at one person.\n");

        target(" raises " + HIS(TP) + " head and gazes at you.", 
            oblist);
        
    if ((TP->query_stat(SS_DIS) - oblist[0]->query_stat(SS_WIS)) > 0)
    {
        actor("You raise your head and fix your gaze on",
             oblist, " who seems to be a little startled.");
        oblist[0]->catch_msg("As " + HIS(TP) + " eyes glowing with " +
            "magical fire meet your gaze, you back away slowly from the " +
            "mage, a little startled.\n");
        all2actbb(" raises " + HIS(TP) + " head and fixes " +
            HIS(TP) + " eyes glowing with magical fire on", 
            oblist, ", who seems to be a little startled.");
    }
    else
    {
        actor("You raise your head and fix your gaze on",
             oblist, " who returns the look rather calmly.");
        oblist[0]->catch_msg("Even with " + HIS(TP) + " eyes glowing "+
            "with magical fire " + HE(TP) + " doesn't seem that impressive.\n");
        all2actbb(" raises " + HIS(TP) + " head and fixes " +
            HIS(TP) + " eyes glowing with magical fire on", 
            oblist, ", who looks back rather calmly.");
    }

    return 1;        
}

public int
whelp(string str)
{
    string *parts;
    string color, strorig;

    strorig = str;

    if (query_verb() == "whelp" && (!str || !strlen(str)))
        str = "wohs";

    if (!strlen(str))
        return 0;

    str = lower_case(str);
    
    setuid();
    seteuid(getuid());

    color = GET_ROBE(TP)->query_robe_color() + "/";

    if (member_array(str, DOC_GUILD) >= 0)
    {
        cat(HELP_DIR + "commands");
        cat(HELP_DIR + color + "commands");
	return 1;
    }

    parts = explode(str, " ");

    if (sizeof(parts) > 1)
    {
        if (member_array(parts[0], DOC_GUILD) >= 0)
	{
	    if ((file_size(HELP_DIR + color + parts[1]) >= 0) ||
		(file_size(HELP_DIR + parts[1]) >= 0) ||
		(file_size(HELP_DIR + "conclave_help/" + parts[1]) >= 0))
	    {
	        cat(HELP_DIR + color + parts[1]);
		cat(HELP_DIR + parts[1]);

		if (IS_CONCLAVE(RNAME(TP)))
		    cat(HELP_DIR + "conclave_help/" + parts[1]);

		return 1;
	    }
	}
    }

    NF("No help on \"" + strorig + "\" available.\n");
    return 0;
}

public int
winvite(string str)
{
    object *oblist;

    if (!str || !strlen(str))
        return NF("Invite whom?\n");

    if (!THIS_GUILD(TP))
        return NF("Invite is for true members only.\n");

    if (TP->query_wohs_level())
        return NF("An apprentice is not trusted to handle such " +
		  "kind of magic.\n");

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
	return NF("Invite whom?\n");

    if (sizeof(oblist) > 1)
        return NF("Be a little more specific of whom you want to invite.\n");

    if (ADMIN->check_banned(oblist[0]))
        return NF("Somehow you get the feeling that your magic wouldn't " +
		  "work here.\n");

    if (THIS_GUILD(oblist[0]))
        return NF("That would be a waste of your magical power.\n");

    if (oblist[0]->query_prop(LIVE_I_AM_INVITED))
        return NF("Why invite someone that is already invited.\n");

    target(" presses " + POSSESSIVE(TP) + " lips against your " +
	   "forehead, giving you the charm that will allow you to " +
	   "reach the Tower of Wayreth.", oblist);

    write("You press your lips against " + POSSESSIVE(oblist[0]) + 
	  " forehead, giving " + OBJECTIVE(oblist[0]) + " the charm " +
	  "to enter the Tower.\n");

    all2act(" presses " + POSSESSIVE(TP) + " lips against", oblist,
	    "forehead.");

    oblist[0]->add_prop(LIVE_I_AM_INVITED, 1);

    return 1;
}

public int
wignore(string str)
{
    string *how;
    object *oblist;
    string allstr = "", actstr = "";
    int hood;

    NF("Ignore who?\n");

    if (!str || !strlen(str))
        return 0;

    how = parse_adverb(str, "slowly", 0);

    if (ROBE_WORN(TP) && !TP->query_wohs_hooded())
    {
        allstr = how[1] + " raises the hood of " + POSSESSIVE(TP) +
                 " robe and ";
        actstr = how[1] + " raise the hood of your robe and ";

        hood = 1;
    }
    
    if (how[0] == "all")
    {
        all(" " + allstr + "starts to ignore everyone.");
        write("You " + actstr + "start to ignore everyone.\n");
    }
    else
    {
        oblist = parse_this(how[0], "%l");

	if (!sizeof(oblist))
            return 0;

        all2act(allstr + "start to ignore", oblist, ".");
        target(" " + allstr + "starts to ignore you.", oblist);
        actor("You " + actstr + "start to ignore", oblist, ".");
    }

    if (hood)
        GET_ROBE(TP)->hood_player(TP);

    return 1; 
}

public int
wlean(string str)
{
    object *polearm;
    
    if (strlen(str))
        return NF("Lean on what?\n");

    polearm = this_player()->query_weapon(-1);
    
    if ((!sizeof(polearm)) || (polearm[0]->query_wt() != W_POLEARM))
    {
        write("Weary from your spellcasting you support yourself on "+
            "your staff only to find that you haven't brought one. "+
            "You quickly regain your balance.\n");
        all(" shifts " + HIS(TP) + " weight to lean on a staff that " +
            HE(TP) + " discovers in the last second isn't there. " +
            C(HE(TP)) + " regains " + HIS(TP) + " balance with amazing " +
            "agility and look around to see if anyone noticed the misstep.");
            
        return 1;
    }
    
    write("You lean on your " + polearm[0]->short() + 
        ", weary from the spell you cast.\n");
    all(" leans on " + POSSESSIVE(TP) + " " + polearm[0]->short() + 
        ", weary from spellcasting.");

    return 1;
}

public int
wpace(string str)
{
    if (strlen(str))
        return NF("Pace where?\n");

    SOULDESC("pacing around, deep in thought");

    write("You silently pace about the room, deep in thought.\n");

    if (ROBE_WORN(TP))
        all(" paces about the room, apparently deep in thought. All is " +
	    "silent, save the soft rustle of " + POSSESSIVE(TP) + " robe.");
    else
        all(" paces about the room, apparently deep in thought.");
    
    return 1;
}

public int
wpouch(string str)
{
    if (strlen(str))
        return NF("What ?\n");

    write("You look through your pouches, checking to make sure "+
          "that you have all of the necessary components.\n");
    all("'s supple fingers examine "+POSSESSIVE(TP)+" pouches, "+
        "expertly checking all of "+POSSESSIVE(TP)+" spell "+
        "components.");
    return 1;
}

public int
wrap(string str)
{
    NF("Wrap what?\n");
 
    if (strlen(str) || !ROBE_WORN(TP))
        return 0;

    write("You wrap your robe around you tighter, in an effort to " +
          "keep warm.\n");
    all(" suddenly shivers, and wraps " + POSSESSIVE(TP) + " " + GET_ROBE(TP)->query_robe_color() + " robe " +
	"tightly around " + POSSESSIVE(TP) + " body.");
    return 1;
}

public int
wrubbish(string str)
{
    object *oblist;

    NF("Who have a bad opinion?\n");

    if (!str || !strlen(str))
        return 0;

    oblist = parse_this(str, "%l");

    if (!sizeof(oblist))
        return 0;

    target(" dismisses your opinions as utter rubbish.", oblist);
    all2act(" dismisses", oblist,"'s opinions as utter rubbish.");
    actor("You dismiss", oblist, "'s opinions as utter rubbish.");
    return 1;
}

public int
wsilent(string str)
{
    if(strlen(str))
    {
        NF("Be silent about what?\n");
        return 0;
    }
    
    SOULDESC("watching surroundings in silence");

    if (ROBE_WORN(TP))
    {
        if (!TP->query_wohs_hooded())
	  {
            write("You straighten your robe, pull your hood " +
                  "over your head, and watch your " +
                  "surroundings in silence.\n");

            all(" straightens " + POSSESSIVE(TP) + " robe, " +
                "pulls the hood over " + POSSESSIVE(TP) + " head, " +
                "and watches " + POSSESSIVE(TP) +
                " surroundings in silence.");

            GET_ROBE(TP)->hood_player(TP);
            return 1;
        }
        else
        {
            write("You straighten your robe, and watch your " +
                  "surroundings in silence.\n");

            all(" straightens " + POSSESSIVE(TP) + " robe, and " +
                "watches " + POSSESSIVE(TP) +
                " surroundings in silence.");

            return 1;    
        }        

    }
    else
    {
        write("You watch the surroundings in silence.\n");
        all(" watches " + POSSESSIVE(TP) + 
            " surroundings in silence.");
    }

    return 1;
}

public int
wsay(string str)
{
    object *oblist;
    int ix, size;
    string text;
    
    if (!strlen(str))
    {
        write("You decide not to speak in the last moment.\n");
        all(" looks as if " + HE(TP) + " wanted to say something, but "+
            "decided not to in the last moment.");
            
       return 1;
    }
    
    oblist = FILTER_LIVE(all_inventory(E(TP))) - ({ TP });
    
    setuid();
    seteuid(getuid());
    
    size = sizeof(oblist);
    for(ix = 0; ix < size; ix++)
    {
        text = "/d/Krynn/wayreth/guild/obj/language_obj"->translate(str, 
            oblist[ix], 
            (atoi(OB_NUM(TP)) + atoi(OB_NUM(oblist[ix]))));
        
        oblist[ix]->catch_msg(TP->query_The_name(oblist[ix]) + " " + 
            text + "\n");
    }
    
    if (TP->query_option(OPT_ECHO))
        write("You speak in the language of magic: " + str + "\n");
    else
        write("Ok.\n");
    
    return 1;
}

public int
wslump(string str)
{
    if (strlen(str))
        return NF("Slump what?\n");

    write("You slump to the ground, overcome with exhaustion from "+
          "the spellcasting.\n");
    all(" pales, and slumps to the ground, mentally and physically "+
        "exhausted.");
    return 1;
}

public int
wsmirk(string str)
{
    object *oblist;

    if (!str || !strlen(str))
    {
  
        tell_room(E(TP), QCTNAME(TP) + " smirks in a slightly " +
		  "condescending manner, apprently amused.\n", TP);
        write("You smirk amused in a slightly condescending manner.\n");
	return 1;
    }
    
    oblist = parse_this(str, "[at] %l");

    if (!oblist || !sizeof(oblist))
        return NF("Smirk at whom?\n");

    SOULDESC("smirking slightly");

    target(" smirks at you in a slightly condescending manner, apprently " +
           "amused by your ignorance.", oblist);
    all2act(" smirks at", oblist, " in a slightly condescending manner, " +
            "apparently amused by " + (sizeof(oblist) > 1 ? "their" :
            POSSESSIVE(oblist[0])) + " ignorance.");
    actor("You smirk at", oblist, " in a slightly condescending " +
	  "manner, amused by " + (sizeof(oblist) > 1 ? "their" :
          POSSESSIVE(oblist[0])) + " ignorance.");
    return 1;
}

public int
wstare(string str)
{
    object *oblist;
    int size;

    NF("Stare at what?\n"); 
    
    if (!str)
    {
        SOULDESC("studying surroundings");

        write("You intensely study your surroundings, letting nothing " +
              "escape your scrutinizing gaze.\n");
        all(" silently studies " + POSSESSIVE(TP) + " surroundings, " +
            "taking in every detail.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!(size = sizeof(oblist)))
        return 0;

    target(" stares intensely at you. You feel " + POSSESSIVE(TP) + 
           " gaze penetrating deep into your mind, as if " +
           PRONOUN(TP) + " could read your innermost " +
	   "thoughts.", oblist);
    actor("You stare intensely at", oblist, ", searching "+
          (size > 1 ? "their" : POSSESSIVE(oblist[0])) + " intermost " +
	  "thoughts and soul.");
    all2act(" stares intensely at", oblist, ", seemingly searching for " +
            "something within " + (size > 1 ? "them" : OBJECTIVE(oblist[0])) +
	    ".");
    return 1;
}

public int
wstudy(string str)
{
    if (strlen(str))
        return NF("Study what? Your spellbook?\n");

    SOULDESC("studying something");

    write("You open your spellbook, and study the spells in it, "+
          "committing them to memory.\n");
    all(" opens " + POSSESSIVE(TP) + " spellbook, and studies the spells " +
        "it contains, committing each to memory.");

    return 1;
}

public int
wtest(string str)
{
    string tmp;

    if (strlen(str))
        return NF("What ?\n");

    if (ADMIN->query_member_type(TP) == TYPE_APPRENTICE)
    {
        TP->catch_msg("You haven't taken the Test yet.\n");
        return 1;
    }

    switch(random(9))
    {
        case 1:
            tmp = "and breaks out in a cold sweat";
            SOULDESC("sweating");
            break;
        case 2:
	    tmp = "and " + POSSESSIVE(TP) + " cheeks flush";
	    SOULDESC("flushing");
            break;
        case 3:
	    tmp = "and looks stares blankly around";
	    SOULDESC("staring blankly around");
            break;
        case 4:
	    tmp = "and is wracked with a sudden pain in " + 
	          POSSESSIVE(TP) + " leg";
	    SOULDESC("looks wracked");
            break;
        case 5:
	    tmp = "and begins to cough violently";
	    SOULDESC("coughing violently");
            break;
        case 6:
	    tmp = "staring solemnly at the ground";
	    SOULDESC("staring solemnly at the ground");
            break;
        case 7:
	    tmp = "but quickly regains " + PRONOUN(TP) + " composure";
            break;
        case 8:
	    tmp = "and smiles grimly";
	    SOULDESC("smiling grimly");
            break;
	default:
	    tmp = "but " + PRONOUN(TP) + " does not seem bothered";
	    break;
    }

    write("You shudder, as you remember the time you visited the " +
          "Tower of High Sorcery at Wayreth. The time when you faced " +
          "death, yet did not die, for the love of the Art.\n");
    all(" suddenly shudders, " + tmp + "!");

    return 1;
}    

public int
wtrick(string str)
{
    object *oblist;
    int num;
    
    NF("Fake spell for whom?\n");
    
    if (!strlen(str))
        return 0;

    oblist = parse_this(str, "[the] %l"); 
    
    if (!(num = sizeof(oblist)))
        return 0;
        
    actor("You glare menacingly at", oblist, " and throw some " +
        "obviously fake magical gestures at " + (num > 1
        ? "them" : HIM(oblist[0])) + " while mumbling a recipe for some "+
        "foul-tasting cookies just low enough for noone to properly hear.");
        
    target(" glares menacingly at you and begins gesturing at you in a " +
        "mysterious and frankly uncanny way, while making some low "+
        "gutteral sounds that make you wonder what will happen next.", 
        oblist);
        
    all2act(" glares menacingly at", oblist, " while gesturing " + 
        "mysteriously at " + (num > 1 ? "them" : HIM(oblist[0])) + 
        " and mumbling something you can't hear under " + HIS(TP) + 
        " breath. Nothing really seems to happen though.");
        
    return 1;
}
