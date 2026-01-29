/*
 * Command Soul for the WoHS - Arman January 2016
 *
 * This is the command soul that every member of the SoHM will
 * have. It includes emotes as well as the abilities/spells that they
 * possess.  Based on Petros' Academic code.
 *
 * Created by Petros, September 2009
 */

#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include "../defs.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

static string *wohs_white_titles = ({"Lesser White Wizard",
  "Wizard of the Ninth White Circle",
  "Wizard of the Eighth White Circle",
  "Wizard of the Seventh White Circle",
  "Wizard of the Sixth White Circle",
  "Wizard of the Fifth White Circle",
  "Wizard of the Fourth White Circle",
  "Wizard of the Third White Circle",
  "Wizard of the Second White Circle",
  "Wizard of the First White Circle",
    "Greater Wizard of the White Order of High Sorcery",
    "High Wizard of the White Order of High Sorcery",
    "Archwizard of the White Order of High Sorcery",});

static string *wohs_red_titles = ({"Lesser Red Wizard",
  "Wizard of the Ninth Red Circle",
  "Wizard of the Eighth Red Circle",
  "Wizard of the Seventh Red Circle",
  "Wizard of the Sixth Red Circle",
  "Wizard of the Fifth Red Circle",
  "Wizard of the Fourth Red Circle",
  "Wizard of the Third Red Circle",
  "Wizard of the Second Red Circle",
  "Wizard of the First Red Circle",
    "Greater Wizard of the Red Order of High Sorcery",
    "High Wizard of the Red Order of High Sorcery",
    "Archwizard of the Red Order of High Sorcery",});

static string *wohs_black_titles = ({"Lesser Black Wizard",
  "Wizard of the Ninth Black Circle",
  "Wizard of the Eighth Black Circle",
  "Wizard of the Seventh Black Circle",
  "Wizard of the Sixth Black Circle",
  "Wizard of the Fifth Black Circle",
  "Wizard of the Fourth Black Circle",
  "Wizard of the Third Black Circle",
  "Wizard of the Second Black Circle",
  "Wizard of the First Black Circle",
    "Greater Wizard of the Black Order of High Sorcery",
    "High Wizard of the Black Order of High Sorcery",
    "Archwizard of the Black Order of High Sorcery",});


/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
public string
get_soul_id() 
{ 
    return WOHS_GUILD_NAME + " Soul"; 
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
public int 
query_cmd_soul() 
{ 
    return 1; 
}

public mapping
query_cmdlist()
{
    return ([
      // Emotes from SoHM
      "wcalm"             : "scalm",
      "wconcentrate"      : "sconcentrate",
      "wfarewell"         : "sfarewell",
      "wfinger"           : "sfinger",
      "wfrown"            : "sfrown",
      "wlean"             : "slean",
      "wlisten"           : "slisten",
      "wphase"            : "sphase",
      "wpouch"            : "spouch",
      "wpractice"         : "spractice",
      "wrubbish"          : "srubbish",
      "wslump"            : "sslump",
      "wstudy"            : "sstudy",
      // New emotes for WoHS
      "wdismiss"          : "wdismiss",
      "wfury"             : "wfury",
      "wglare"            : "wglare",
      "wgreet"            : "wgreet",
      "whug"              : "whug",
      "wpouch"            : "wpouch",
      "wprod"             : "wprod",
      "wremind"           : "wremind",
      "wsmooth"           : "wsmooth",
      "wstare"            : "wstare",
      "wtap"              : "wtap",
      "wtest"             : "wtest",
      "wtouch"            : "wtouch",
      "wtuck"             : "wtuck",
      "wturn"             : "wturn",
      "wwithdraw"         : "wwithdraw",

      // Help and Options
      /* slist will be a cantrip, ehtahhewa
       "slist"             : "slist",
       */
      "help"              : "help",        
      "burn"              : "sleave",
      "wcheck"            : "wcheck",
      "whide"             : "whide",
    ]);
}


// WoHS emotes in alphabetical order

public int
scalm(string str)
{
    if (strlen(str))
    {
	notify_fail("You can only calm yourself!\n");
	return 0;
    }

    // Concentrates on remaining calm in the face of distractions
    write("You focus your attention inward. The distractions around "
      + "you fade to nothingness, allowing you to remain perfectly "
      + "calm.\n");
    allbb(" focuses " +HIS(TP)+ " attention inwards, becoming perfectly " 
      + "calm.");
    return 1;
}

public int
sconcentrate(string str)
{
    if (strlen(str))
    {
	notify_fail("Concentrate on what?\n");
	return 0;
    }
    write("You close your eyes in concentration, going over your "+
      "spells in preparation for battle.\n");
    allbb(" closes " + this_player()->query_possessive() + " eyes and " +
      "mumbles the words to " + this_player()->query_possessive() + 
      " spells over and over, making certain that " + 
      this_player()->query_pronoun() + " has them memorized.");

    return 1;
}

public int
sfarewell(string str)
{
    object * oblist;

    if (!str)
    {
        write("You inform everyone that you must return to your studies, "
          + "and bid farewell.\n");
        allbb(" informs everyone that " +this_player()->query_pronoun()+ 
          " must return to " + this_player()->query_possessive()+ 
          " studies, and bids farewell.");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
	return 0;
    }

    target(" informs you that " + this_player()->query_pronoun() + " must "
      + "return to " + this_player()->query_possessive() + " studies, and "
      + "bids you farewell.", 
      oblist);
    actor("You inform", oblist, " that you must return to your studies, "
      + "and bid farewell.");
    all2act(" informs", oblist, " that " + this_player()->query_pronoun()
      + " must return to " + this_player()->query_possessive()
      + " studies, and bids them farewell.");    

    return 1;
}

public int
sfinger(string str)
{
    if (strlen(str))
    {
	notify_fail("Finger what?\n");
	return 0;
    }

    write("You gently run your fingers across your spellbook, wiping "+
      "the dust from it.\n");
    allbb(" lightly brushes the dust from " +this_player()->query_possessive()+ 
      " leather-bound spellbook, lingering fondly on the cover.");
    return 1;
}

public int
sfrown(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You pause and frown, clearly showing your irritation by the "+
	  "interruption.\n");
	allbb(" pauses and frowns, clearly showing " 
	  +this_player()->query_possessive()+ " irritation "+
	  "by the interruption.");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");
    oblist = oblist - ({ this_player() });

    if (!sizeof(oblist))
    {
	notify_fail("Frown at whom?\n");
	return 0;
    }     

    if (sizeof(oblist) > 1)
    {
	notify_fail("Please be a bit more precise - who do you want to "+
	  "frown at?\n");
	return 0;
    } 

    actor("You pause and frown, cleary showing your irritation at", oblist,
      "'s interruption.");
    target(" pauses and frowns, clearly showing " 
      +this_player()->query_possessive()+ " irritation at your interruption.", 
      oblist);
    all2actbb(" pauses and frowns, clearly showing " 
      +this_player()->query_possessive()+ " irritation at", oblist, 
      "'s interruption.");

    return 1;
}

public int
slean(string str)
{
    object *polearm;

    if (strlen(str))
	return notify_fail("Lean on what?\n");

    polearm = this_player()->query_weapon(-1);

    if ((!sizeof(polearm)) || (!polearm[0]->id("staff")))
    {
	write("Weary from your spellcasting you support yourself on "+
	  "your staff only to find that you haven't brought one. "+
	  "You quickly regain your balance.\n");

	tell_room(environment(this_player()), QCTNAME(this_player()) +
	  " shifts " +this_player()->query_possessive()+ 
	  " weight to lean on a staff that isn't there. " +
	  QCTNAME(this_player()) + " regains " 
	  +this_player()->query_possessive()+ 
	  " balance and looks around sheepishly to see if " +
	  "anyone noticed the misstep.", ({ this_player() }), 
	  this_player());           
	return 1;
    }

    write("You lean on your " + polearm[0]->short() + 
      ", weary from spellcasting.\n");
    all(" leans on " +this_player()->query_possessive()+ " " 
      + polearm[0]->short() +  ", weary from spellcasting.");
    return 1;
}

public int
slisten(string str)
{
    // Listen to gain knowledge from others
    object * oblist;

    notify_fail("Whom do you wish to listen to?\n");
    if (!str)
    {
	return 0;
    }

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
	return 0;
    }

    target(" inclines " + this_player()->query_possessive() + " ear towards "
      + "you and listens closely for words of wisdom and knowledge.", 
      oblist);
    actor("You incline your ear towards", oblist, " and listen closely for "
      + "words of wisdom and knowledge.");
    all2act(" inclines " + this_player()->query_possessive() + " ear towards", 
      oblist, " and listens closely for words of wisdom and knowledge.");    

    return 1;
}

public int
sphase(string str)
{
    object env = environment(TP);

    string sol = GET_MOON_PHASE(SOLINARI);
    string lun = GET_MOON_PHASE(LUNITARI);
    string nui = GET_MOON_PHASE(NUITARI); 

    string black_robe_string;

    if(QUERY_WOHS_ROBE(TP) == "black")
	black_robe_string = " Only observable by those of the Order " +
	"of the Black Robes, the black moon Nuitari is " +nui+ ".";
    else
	black_robe_string = "";

    if(env->query_prop(ROOM_I_INSIDE))
    {
	notify_fail("You are inside and cannot check the phases of the " +
	  "moons.\n");
	return 0;  
    }    

    if(!str || str == "moons of magic" || str == "moons")
    {
	if((sol == "full") && (lun == "full") && (nui == "full"))
	{
	    write("You stare up in to the sky and study the orbits of " +
                "the moons of magic. You note all three moons are full " +
                "and aligned in high sanction. A rare event known as " +
                "the Night of the Eye, where magic is at its peak!\n");
	    allbb(" stares up in to the sky, studying the orbits of " +
                "the moons of magic.");
	    return 1;
	}

	write("You stare up in to the sky and study the orbits of the " +
            "moons of magic. You note the white moon Solinari is " +sol+ 
            ", while the red moon Lunitari is " +lun+"." +
            black_robe_string+ "\n");
	allbb(" stares up in to the sky, studying the orbits of the " +
            "moons of magic.");
	return 1;

    }

    if(str == SOLINARI)
    {
	write("You stare up in to the sky and study the orbit of the " +
            "white moon Solinari. You note it is " +sol+ ".\n");
	allbb(" stares up in to the sky, studying the orbits of the " +
            "moons of magic.");
	return 1;
    }

    if(str == LUNITARI)
    {
	write("You stare up in to the sky and study the orbit of the " +
            "red moon " + "Lunitari. You note it is " +lun+ ".\n");
	allbb(" stares up in to the sky, studying the orbits of the " +
            "moons of magic.");
	return 1;
    }

    if(str == NUITARI)
    {
	if(QUERY_WOHS_ROBE(TP) == "black")
	{
	    write("You stare up in to the sky and study the orbit of " +
                "the black moon Nuitari. As a mage of the Black Robes, " +
                "Nuitari's radiance is brighter than the other two " +
                "moons of magic! You note it is " +nui+ ".\n");
	    allbb(" stares up in to the sky, studying the orbits of " +
                "the moons of magic.");
	    return 1;
	}
	else
	{
	    write("You cannot find Nuitari in the sky. It is said only " +
                "those of the Order of the Black Robes can detect it, " +
                "however you think it may be " +nui+ ".\n");
	    allbb(" stares up in to the sky, studying the orbits of the " +
                "moons of magic.");
	    return 1;
	}
    }

    notify_fail("Study the phases of the moons of magic? Or " +
        "specifically the moons Solinari, Lunitari or Nuitari?\n");
    return 0;    
}

public int
spouch(string str)
{
    if (strlen(str))
	return notify_fail("What?\n");

    write("You look through your pouches, checking to make sure "+
      "that you have all of the necessary components.\n");
    all("'s supple fingers examine "+ this_player()->query_possessive() +
      " pouches, expertly checking all of "+ 
      this_player()->query_possessive() +" spell components.");
    return 1;
}

public int
spractice(string str)
{
    if (strlen(str))
    {
	notify_fail("Practicing should be done on your own!\n");
	return 0;
    }

    // Mental excercises
    write("You concentrate upon your magical studies, practicing forms "
      + "that you have been taught.\n");
    allbb(" concentrates upon " + this_player()->query_possessive()
      + " magical studies, practicing forms " +this_player()->query_pronoun()
      + " has been taught.");
    return 1;
}

public int
srubbish(string str)
{
    object *oblist;

    if (!str || !strlen(str))
    {
	notify_fail("Who has a bad opinion?\n");
	return 0;
    }

    oblist = parse_this(str, "%l");

    if (!sizeof(oblist))
    {
	notify_fail("Who has a bad opinion?\n");
	return 0;
    }

    target(" dismisses your opinions as utter rubbish.", oblist);
    all2act(" dismisses", oblist,"'s opinions as utter rubbish.");
    actor("You dismiss", oblist, "'s opinions as utter rubbish.");
    return 1;
}

public int
sslump(string str)
{
    if (strlen(str))
    {
	notify_fail("Slump what?\n");
	return 0;
    }

    write("You slump to the ground, overcome with exhaustion from "+
      "spellcasting.\n");
    all(" pales and slumps to the ground, mentally and physically "+
      "exhausted.");
    return 1;
}

public int
sstudy(string str)
{
    if (strlen(str))
    {
	notify_fail("You should study on your own!\n");
	return 0;
    }

    // Go over study notes
    write("You pull out your spellbook and study it closely, "
      + "ignoring your surroundings.\n");
    allbb(" pulls out " + this_player()->query_possessive() + " " +
      "spellbook and studies it closely, ignoring "
      + this_player()->query_possessive() + " surroundings.");
    return 1;

}

public int
wdismiss(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space( str, "archly", 0 );

    if (!strlen( how[0] ))
    {
	notify_fail("Dismiss whom?\n");
        return 0;
    }

    oblist = parse_this( how[0], "[the] %l" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist )) 
    {
        notify_fail( "Dismiss whom?\n" );
        return 0;
    }

    actor( "You dismiss", oblist, how[1]+ " with a wave of your hand." );
    targetbb( " dismisses you" +how[1]+ " with a wave of " +HIS(TP)+
        " hand.", oblist );
    all2actbb( " dismisses", oblist, how[1]+ " with a wave of " +HIS(TP)+
        "hand." );
    return 1;
}

public int
wfury(string str)
{
    object *oblist;
    int wis_diff;
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({ this_player() });
    
    if (!sizeof(oblist))
        return NF("Look at whom?\n");

    if (sizeof( oblist ) != 1)
    {
        notify_fail("You can look this way only at one person.\n");
        return 0;
    }        
        
    if ((TP->query_stat(SS_WIS) > oblist[0]->query_stat(SS_DIS)))
    {
        actor("With eyes smouldering with an inner fire, you fix your " +
            "furious gaze on", oblist, ".");
        oblist[0]->catch_msg(QCTPNAME(TP)+ " eyes smoulder with an " +
            "inner fire as " +HE(TP)+ " gazes at you furiously, " +
            "a menacing aura of power radiating from " +HIM(TP)+ ".\n");
        all2actbb(" fixes " + HIS(TP) + " furious gaze upon", oblist, 
            ", " +HIS(TP)+ " eyes smouldering with with a menacing " +
            "inner fire.");
    }
    else
    {
        actor("With eyes smouldering with an inner fire, you fix your " +
              "furious gaze on", oblist, ".");
        oblist[0]->catch_msg(QCTPNAME(TP)+ " eyes smoulder with " +
            "an inner fire as " +HE(TP)+ " gazes at you furiously.\n");
        all2actbb(" fixes " + HIS(TP) + " furious gaze upon", oblist, 
            " with eyes that seem to smoulder with an inner fire.");
    }
    return 1;        
}

public int
wglare(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space( str, "vehemently", 0 );

    if (!strlen( how[0] ))
    {
	notify_fail("Glare at whom?\n");
        return 0;
    }

    oblist = parse_this( how[0], "[at] [the] %l" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist )) 
    {
        notify_fail( "Glare at whom?\n" );
        return 0;
    }

    actor( "You glare"+ how[1]+ " at", oblist, " and mutter something " +
        "about turning " +HIM(oblist[0])+ " into a newt." );
    targetbb( " glares" +how[1]+ " at you and mutters something about " +
        "turning you into a newt.", oblist );
    all2actbb( " glares" +how[1]+ " at", oblist, ", muttering something " +
        "about turning " +HIM(oblist[0])+ " into a newt!" );
    return 1;
}

public int
wgreet(string str)
{
    object * oblist;
    string *how;

    how = parse_adverb_with_space( str, "in acknowledgement", 0 );

    if (!(TP == present( "wohs_robe_object", TP )->query_worn()))
    {
        notify_fail( "You will need to be wearing your robe " +
            "to do that.\n" );
        return 0;
    }

    if (!TP->query_hooded())
    {
        notify_fail( "You will need to be hooded to do that.\n" );
        return 0;
    }

    if (!strlen( how[0] ))
    {
        write("You greet everyone" +how[1]+ " from the shadows of your " +
          "hooded robe.\n");
        allbb(" greets everyone" +how[1]+ " from the shadows of " + 
          this_player()->query_possessive()+ " hooded robe.");
        return 1;
    }

    oblist = parse_this( how[0], "[the] %l" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist )) 
    {
        notify_fail( "Greet whom?\n" );
        return 0;
    }

    actor( "You greet", oblist, how[1]+ " from the shadows of your hooded " +
        "robe." );
    targetbb( " greets you" +how[1]+ " from the shadows of " +HIS(TP)+ 
        " hooded robe.", oblist );
    all2actbb( " greets", oblist, how[1]+ " from the shadows of " +HIS(TP)+ 
        " hooded robe." );
    return 1;  
}

public int
whug(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space( str, "warmly", 0 );

    if (!strlen( how[0] ))
    {
	notify_fail("Hug whom?\n");
        return 0;
    }

    oblist = parse_this( how[0], "[the] %l" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist )) 
    {
        notify_fail( "Hug whom?\n" );
        return 0;
    }

    if (!(TP == present( "wohs_robe_object", TP )->query_worn()))
    {
        notify_fail( "You will need to be wearing your robe " +
            "to do that.\n" );
        return 0;
    }

    actor( "You envelope", oblist, how[1]+ " in a hug, the smell " +
        "of dried herbs rising from your robes as your hidden " +
        "components are crushed in the embrace." );
    targetbb( " envelopes you" +how[1]+ " in a hug, the smell of dried " +
        "herbs rising from " +HIS(TP)+ " robes as " +HIS(TP)+
        " hidden components are crushed in the embrace.", oblist );
    all2actbb( " envelopes", oblist, how[1]+ " in a hug, the " +
        "smell of dried herbs rising from " +HIS(TP)+ " robes as " +
        HIS(TP)+ " hidden components are crushed in the embrace." );
    return 1;
}

public int
wpouch(string str)
{
    if (strlen(str))
        return NF("What ?\n");
    write("You look through your pouches, checking to make sure "+
          "that you have all of the necessary components.\n");
    all(" examines "+POSSESSIVE(TP)+" pouches, "+
        "expertly checking all of "+POSSESSIVE(TP)+" spell "+
        "components.");
    return 1;
}

public int
wprod(string str)
{
    object *polearm;
    object *oblist;
    string *how;

    how = parse_adverb_with_space( str, "gently", 0 );
    polearm = this_player()->query_weapon(-1);

    if (!strlen( how[0] ))
    {
	notify_fail("Prod whom with your staff?\n");
        return 0;
    }

    oblist = parse_this( how[0], "%l [with] [staff]" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist )) 
    {
        notify_fail( "Prod whom?\n" );
        return 0;
    }

    if ((!sizeof(polearm)) || (!polearm[0]->id("staff")))
    {
	return notify_fail("You are not wielding a staff to " +
            "prod anyone with!\n");
    }

    actor( "You"+ how[1]+ " prod", oblist, " with the end of your "+
        polearm[0]->short()+ "." );
    targetbb( how[1]+ " prods you with the end of " +HIS(TP)+ " " +
        polearm[0]->short()+ ".", oblist );
    all2actbb( how[1]+ " prods", oblist, " with the end of " +HIS(TP)+
        " " +polearm[0]->short()+ "." );
    return 1;
}

public int
wremind(string str)
{
    object *oblist;

    if (!strlen( str ) || str == "all")
    {
        write( "You remind everyone that your first loyalty is to " +
            "magic.\n" );
        allbb( " reminds everyone that "+ HIS(TP)+ " first loyalty is " +
            "to magic." );
        return 1;
    }

    oblist = parse_this( str, "[the] %l" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist )) 
    {
	notify_fail("Remind whom?\n");
        return 0;
    }

    actor( "You remind", oblist, " that your first loyalty is to " +
        "magic." );
    targetbb( " reminds you " +HIS(TP)+ " first loyalty is to magic.", 
        oblist );
    all2actbb( " reminds", oblist, " " +HIS(TP)+ " first loyalty is to " +
        "magic." );
    return 1;
}

public int 
wsmooth(string str)
{
    if (strlen( str ))
    {
        notify_fail( "Smooth what?\n" );
        return 0;
    }

    if (!(TP == present( "wohs_robe_object", TP )->query_worn()))
    {
        notify_fail( "You will need to be wearing your robe " +
            "to do that.\n" );
        return 0;
    }

    write( "You smooth the wrinkles from your robe and meticulously " +
        "remove a piece of lint from your sleeve.\n" );
    allbb( " smoothes the wrinkles from "+ HIS(TP)+ " robe and " +
        "meticulously removes a piece of lint from " +HIS(TP)+ 
        " sleeve." );
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
wtap(string str)
{
    object *polearm;
    polearm = this_player()->query_weapon(-1);

    if (strlen( str ))
    {
        notify_fail( "Tap what?\n" );
        return 0;
    }

    if ((!sizeof(polearm)) || (!polearm[0]->id("staff")))
    {
	notify_fail("You are not wielding a staff to " +
            "tap the ground with!\n");
        return 0;
    }

    write( "You tap the ground with your " +polearm[0]->short()+
        " to get everyone's attention.\n" );
    allbb( " taps the ground with "+ HIS(TP)+ " " +polearm[0]->short()+
        " to get everyone's attention." );
    return 1;
}

public int
wtest(string str)
{
    string wiz, tmp;
    if (strlen(str))
        return NF("What ?\n");

    switch(random(8)) 
    {
        case 1:
            wiz = "You break out in a cold sweat";
            tmp = "breaks out in a cold sweat";
            break;
        case 2:
            wiz = "Your cheeks flush";
	    tmp = "looks suddenly flushed in the face";
            break;
        case 3:
            wiz = "You stare blankly into space";
	    tmp = "stares blankly into space";
            break;
        case 4:
            wiz = "You are wracked with a sudden pain";
	    tmp = "is wracked with a sudden pain";
            break;
        case 5:
            wiz = "You begin coughing violently";
	    tmp = "begins to cough violently"; 
            break;
        case 6:
            wiz = "You stare solemnly at the ground";
	    tmp = "stares solemnly at the ground";
            break;
        case 7:
            wiz = "You suddenly go pale";
	    tmp = "suddenly goes pale";
            break;
        default:
            wiz = "You smile grimly";
	    tmp = "smiles grimly";
            break;
    }
    write(wiz + " as you recall the time you visited the " +
          "Tower of High Sorcery at Wayreth. The time when you took " +
          "the Test and risked death for the love of the Art.\n");
    all(" " + tmp + " as " +HE(TP)+ " recalls " +HIS(TP)+ 
        " trials completing the Test of High Sorcery.");
    return 1;
} 

public int
wtouch(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space( str, "irritably", 0 );

    if (!strlen( how[0] ))
    {
	notify_fail("Target whom for touching you?\n");
        return 0;
    }

    oblist = parse_this( how[0], "[at] [the] %l" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist )) 
    {
        notify_fail( "Target who for touching you?\n" );
        return 0;
    }

    actor( "You"+ how[1]+ " raise your finger towards", oblist, ", " +
        "releasing a flash of crackling blue light at " +HIM(oblist[0])+ 
        " and sending a shock through " +HIM(oblist[0])+ " body as a " +
        "warning for touching you." );
    targetbb( how[1]+ " raises " +HIS(TP)+ " finger towards you, " +
        "releasing a flash of crackling blue light. A numbing shock " +
        "runs through your body, a warning for daring to touch a " +
        "Wizard of High Sorcery!", oblist );
    all2actbb( how[1]+ " raises " +HIS(TP)+ " finger towards", oblist, 
        ", releasing a flash of crackling blue light at " +HIM(oblist[0])+ 
        " in warning for touching a Wizard of High Sorcery!" );
    return 1;
}

public int 
wtuck(string str)
{
    string *how;
    how = parse_adverb_with_space( str, "solemnly", 0 );

    if (strlen( how[0] ))
    {
        notify_fail( "You want to tuck your hands in your sleeves " +
            "how?\n" );
        return 0;
    }

    if (!(TP == present( "wohs_robe_object", TP )->query_worn()))
    {
        notify_fail( "You will need to be wearing your robe " +
            "to do that.\n" );
        return 0;
    }

    write( "You"+ how[1]+ " tuck your hands into the voluminous sleeves " +
        "of your robe.\n" );
    allbb( how[1]+ " tucks "+ HIS(TP)+ " hands into the voluminous " +
        "sleeves of " +HIS(TP)+ " robe." );
    return 1;
}   

public int
wturn(string str)
{
    object *oblist;

    if (!strlen( str ))
    {
	notify_fail("Turn to whom?\n");
        return 0;
    }

    oblist = parse_this( str, "[to] [the] %l" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist )) 
    {
        notify_fail( "Turn to whom?\n" );
        return 0;
    }

    if (!(TP == present( "wohs_robe_object", TP )->query_worn()))
    {
        notify_fail( "You will need to be wearing your robe " +
            "to do that.\n" );
        return 0;
    }

    if (!TP->query_hooded())
    {
        notify_fail( "You will need to be wearing the hood of your " +
            "robe to do that.\n" );
        return 0;
    }

    actor( "You turn your gaze towards", oblist, ", your " +
        "expression hidden in the shadows of your robe." );
    targetbb( " turns " +HIS(TP)+ " gaze towards you, " +HIS(TP)+
        " expression hidden in the shadows of " +HIS(TP)+ " robe.", 
        oblist );
    all2actbb( " turns " +HIS(TP)+ " gaze towards", oblist, ", " +
        HIS(TP)+ " expression hidden in the shadows of " +HIS(TP)+ 
        " robe." );
    return 1;
}

public int 
wwithdraw(string str)
{
 string *how;
    how = parse_adverb_with_space( str, "thoughtfully", 0 );
 
    if (strlen( how[0] ))
    {
        return 0;
    }

    if (!(TP == present( "wohs_robe_object", TP )->query_worn()))
    {
        notify_fail( "You will need to be wearing your robe " +
            "to do that.\n" );
        return 0;
    }

    if (!TP->query_hooded())
    {
        notify_fail( "You will need to be wearing the hood of your " +
            "robe to do that.\n" );
        return 0;
    }

    write( "You withdraw"+ how[1]+ " into the shadows of your hooded " +
        "robe.\n" );
    allbb(" withdraws"+ how[1]+ " into the shadows of "+ 
        HIS(this_player())+ " hooded robe." );

    return 1;
}

// List of other WoHS member function - through cantrip ehtahhewa

public int
slist(string str)
{
    // List of other SoHM and WoHS members
    mixed list = WOHS_MANAGER->query_awake_members(this_player());

    list = sort_array(map(list, &->query_presentation()));  
    list = implode(map(list, &operator(+)("- ",)), "\n");  

    this_player()->more("The following practitioners of High Magic " +
        "are currently in the realms:\n"+ list + "\n");

    return 1;
}

public int
help(string str)
{
    // Access help files
    string content, *files; 
    setuid(); 
    seteuid(getuid()); 

    if (!stringp(str) || !strlen(str))
    { 
	return 0; 
    }

    if (str == "wohs") 
    {         
	if (!pointerp(files = get_dir(WOHS_HELP)) || !sizeof(files))
	{
	    return 0; 
	}

	if (!stringp(content = read_file(WOHS_HELP + "general")))
	{
	    notify_fail("Something is terribly wrong! Please contact "
	      + "the guildmaster and let them know that the help files "
	      + "for the Wizards of High Sorcery are not working "
              + "property.\n");
	    return 0;
	}

	write("You open up your spellbook and read through your notes "
	  + "and spells of High Sorcery.\n");
	this_player()->more(content);
	return 1;
    } 

    if (sscanf(str, "wohs %s", str) != 1)
    {
	return 0;
    }

    str = lower_case(str); // set everything to lowercase
    // Players can get information about spells that they know
    if ((WOHS_MANAGER->query_scribed_spell(this_player(), str)
	&& stringp(content = read_file(WOHS_SPELLS_HELP + str)))
      || stringp(content = read_file(WOHS_HELP + str)))
    {
	write("You flip through your spellbook and read the notes "
	  + "pertaining to " + capitalize(str) + ".\n");
	this_player()->more(content);
	return 1;         
    }

    notify_fail("You can't seem to find any notes on that topic "
      + "within your spellbook.\n"); 
    return 0;     
}

// Functions to leave the SoHM

public void
remove_confirmation_prop(object player)
{    
    player->remove_prop(WOHS_I_CONFIRM_LEAVE);
}

public int
sleave(string str)
{
    object player = this_player();

    if (!objectp(player))
    {
	return 0;
    }

    if (!strlen(str) || str != "wizard of high sorcery spellbook")
    {
	notify_fail("Did you want to <burn wizard of high sorcery " +
            "spellbook>?\n");
	return 0;
    }

    if (!WOHS_IS_MEMBER(player))
    {
	notify_fail("You are not a Wizard of High Sorcery!\n");
	return 0;
    }

    if (!player->query_prop(WOHS_I_CONFIRM_LEAVE))
    {
	write("Type the <burn wizard of high sorcery spellbook> command " +
          "again in the next minute to confirm that you really want to " +
          "leave.\n");
	player->add_prop(WOHS_I_CONFIRM_LEAVE, 1);
	// Give them 1 minute to respond. If they don't then just remove
	// the property
	set_alarm(60.0, 0.0, &remove_confirmation_prop(player));
	return 1;
    }

    player->remove_prop(WOHS_I_CONFIRM_LEAVE);
    setuid();
    seteuid(getuid());
    if (WOHS_JOINROOM->leave_guild(player))
    {
	write("You summon for the last time arcane flames, and watch " +
	  "your leather-bound spellbook burn into ash. You have " +
	  "abandoned the way of the Magi and are no longer a Wizard " +
	  "of High Sorcery.\n");
	say(QCTNAME(player) + " summons arcane flames to devour " + 
	  this_player()->query_possessive()+ " spellbook, abandoning " +
	  "the ways of the Wizards of High Sorcery.\n");
	return 1;
    }

    notify_fail("For some reason you can't leave the Wizards of High " +
        "Sorcery.\n");
    return 0;
}

string
title_check(int level, object player)
{
    string colour = QUERY_WOHS_ROBE(player);

    if(colour == "white")
       return wohs_white_titles[level];
    else if(colour == "red")
       return wohs_red_titles[level];
    else if(colour == "black")
       return wohs_black_titles[level];
    else
       return "your next rank";
}

public int
wcheck(string str)
{
    if (!str || str != "progress")
    {
	notify_fail("Check what? Progress?\n");
	return 0;
    }

    setuid();
    seteuid(getuid());

    this_player()->update_wohs_guild_experience();

    int cl = WOHS_GUILD_LEVEL(this_player());
    int dl = (cl + 1);

    int base_level_xp = WOHS_BASE_GUILD_LEVEL(this_player());
    int current_xp = this_player()->query_skill(WOHS_GUILD_STAT);
    int desired_level_xp = WOHS_NEXT_GUILD_LEVEL(this_player());

    int level_xp_required = desired_level_xp - base_level_xp;
    int current_level_xp = current_xp - base_level_xp;

    int level_ratio = ftoi((itof(current_level_xp) / itof(level_xp_required)) * 100.0);

    string progress_message, next_rank;

    if(cl > 11)
    {
	write("You are currently ranked as Archwizard. You cannot " +
	  "progress any further than that!\n");
	return 1;
    }

    next_rank = title_check(dl, this_player());

    switch(level_ratio)
    {
    case 0..10:
	progress_message = "newly promoted to your rank";
	break;
    case 11..20:
	progress_message = "just beginning your journey to " +next_rank;
	break;
    case 21..30:
	progress_message = "early in your journey to " +next_rank;
	break;
    case 31..40:
	progress_message = "far from progressing to " +next_rank;
	break;
    case 41..50:
	progress_message = "almost halfway towards progressing to " +
            next_rank;
	break;
    case 51..60:
	progress_message = "over halfway to " +next_rank;
	break;
    case 61..70:
	progress_message = "advancing well towards " +next_rank;
	break;
    case 71..80:
	progress_message = "advancing very well towards " +next_rank;
	break;
    case 81..90:
	progress_message = "close to advancing to " +next_rank;
	break;
    case 91..100:
	progress_message = "very close to advancing to " +next_rank;
	break;
    default:
	progress_message = "uncertain of where you sit in your " +
            "advancement";
	break;
    }

    write("You are " +progress_message+".\n");

    return 1;

}

public int
whide(string str)
{

   if(!WOHS_MANAGER->query_wohs_test_marking(this_player()))
   {
        notify_fail("You have no mark from the Test of High Sorcery to " +
             "hide!\n");
        return 0;
   }
      
   if(!str)
   {
       write("Hide what? Your mark?\n");
       return 1;
   }

   if(str == "mark")
   {
      if(WOHS_MANAGER->query_wohs_test_marking_status(this_player()))
      {
          write("You conceal the marks you received from your ordeals " +
             "in the Test of High Sorcery.\n");
          WOHS_MANAGER->set_wohs_test_marking_status(this_player(), 0);
          return 1;
      }
      else
      {
          write("You reveal the marks you received from your ordeals in " +
             "the Test of High Sorcery.\n");
          WOHS_MANAGER->set_wohs_test_marking_status(this_player(), 1);
          return 1;
      }
    }

    write("Hide what? Your mark?\n");
    return 1;
}
