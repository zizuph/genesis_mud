/*
 * Black Robed Wizard of High Sorcery Soul
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

#pragma no_clone
#pragma strict_types
#pragma save_binary
#pragma no_shadow

inherit "/cmd/std/command_driver";

#include <macros.h>
#include <const.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Krynn/wayreth/guild/local.h"
#include "/d/Krynn/wayreth/local.h"
#include "common_soul.c"

/*
 * Return a proper name of the soul in order to get a nice printout.
 */
public string 
get_soul_id() 
{ 
    return "Black Robed Mage"; 
}

/* 
 * The type of soul 
 */
public int 
query_cmd_soul()
{ 
    return 1;
}

/*
 * The list of verbs and functions. Please add new in alphabetical order.
 */
public mapping
query_cmdlist()
{
    return ([ "wcantrip" : "wcantrip",
                 "wcant" : "wcantrip",
  	        "wcurse" : "wcurse",
                 "wdefy" : "wdefy", 
                 "wgaze" : "wgaze", 
                "wglare" : "wglare",
                 "wlook" : "wlook",  
  	         "wmock" : "wmock",
 	       "wpraise" : "wpraise",
                "wshake" : "wshake", 
                "wsmile" : "wsmile" 
           ]) + query_common_cmdlist();
}

public int
wcantrip(string str)
{
    if (strlen(str))
        return NF("What ?\n");

    switch(random(6))
    {
        case 1:
            all(" tosses a gold coin in your direction, then " +
		"snaps " + POSSESSIVE(TP) + " fingers and the coin " +
		"vanishes in a flash of light right as you " +
		"are about to catch it!");
	    write("You make an illusion of tossing a gold coin to " +
		"everyone in the room, and smirk as the fools try "+
		"to catch it.\n");
	    break;
	case 2:
	    all(" mutters something unintelligable, and suddenly " +
		"a giant ogre comes stomping into the room!\n" +
		"The giant ogre attacks you!");
	    all(" claps " + POSSESSIVE(TP) + " hands together " +
		"and the ogre vanished in a puff of smoke, leaving you " +
		"quite relieved.");
	    write("You create an illusion of an ogre that attacks everyone. "+
		"You barely keep from snickering out loud as they all "+
		"turn white in panic.\n");
	    break;
	case 3:
	    all(" wiggles " + POSSESSIVE(TP) + " fingers through the air " +
		"in a complicated series of motions, and suddenly a " +
		"tiny golden dragon flies down, and begins to circle " +
		POSSESSIVE(TP) + " head. It later vanishes.");
	    write("You casually make an image of a tiny golden "+
		"dragon circle your head and watch the gaping jaws "+
		"of your amazed audience.\n");
	    break;
	case 4:
	    all(" walks a coin across " + POSSESSIVE(TP) + 
                " knuckles then says one word in the spidery language of " +
		"magic, and the coin elongates, and transforms into " +
		"a small serpent weaving in between and around " +
		POSSESSIVE(TP) + " knuckles.");
	    write("You walk a coin across your knuckles, then change "+
		"it into a tiny serpent that slithers between your "+
		"fingers.\n");
	    break;
	case 5:
	    all(" tosses some sand into the air, and the area is lit " +
		"up with an amazing golden light! Then the light " +
		"changes to orange, then red, then violet, until " +
		"the colors are changing so fast that you can't even " +
		"distinguish them! You sit down, a bit dizzy after that " +
		"dazzling display.");
	    write("You put on a minor light show that leaves your "+
		"audience dizzied at the least of your powers.\n");
	    break;
	default:
            all(" throws a rock high into the air, you look upwards " +
		"wondering what this amazing rock will do. You wait " +
		"for the rock to come down, and wait, and wait, and " +
		"wait....");
	    write("You toss a rock up into the air and cause it to "+
		"disappear. You watch as the simpletons around you "+
		"stare into the air waiting for it to come down.\n");
    }
    return 1;
}    

public int
wcurse(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
        return NF("Curse whom?\n");

    target(" curses you in the name of Nuitari!", oblist);
    actor("You curse", oblist, " in the name of Nuitari!");
    all2act(" curses", oblist, " in the name of Nuitari!");

    return 1;
}

public int
wdefy(string str)
{
    object *oblist;
    int size;

    NF("Defy whom?\n");

    oblist = parse_this(str, "[the] %l");

    if (!(size = sizeof(oblist)))
	return 0;
    
    target(" scowls at you with undisguised hatred, hissing: Touch me not, " +
	   "for I am Magi!", oblist);
    actor("You scowl at", oblist, " letting " + 
	  (size > 1 ? "them" : OBJECTIVE(oblist[0])) + " know that " +
	  (size > 1 ? "they" : PRONOUN(oblist[0])) + " will pay dearly " +
          "if " + (size > 1 ? "they" : PRONOUN(oblist[0])) + " dares " +
	  "touch you again.");
    all2act(" scowls at", oblist, ", hissing: Touch me not, for I am " +
            "Magi!, who " + (size > 1 ? "all " : "") + "cautiously takes " +
	    "a step backwards.");
    return 1;
}

public int
wgaze(string str)
{
    object *oblist;
    int size;

    NF("Gaze upon whom?\n");

    if (!str)
    {
        write("You radiate a dark, malevolent power throughout the room, as "+
	      "your gaze slowly drifts across it.\n");
	all("'s eyes burn with an inner fire as " + PRONOUN(TP) +
	    " gazes around, radiating a dark, malevolent power throughout " +
	    "the area.");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");
    
    if (!(size = sizeof(oblist)))
        return 0;

    target(" fixes " + POSSESSIVE(TP) + " gaze upon you, " + POSSESSIVE(TP) +
	   " eyes bore into your soul, as wave after wave of " +
	   POSSESSIVE(TP) + " dark power come crashing into " +
           "you, filling you with dread.", oblist);
    actor("You turn your eyes upon",oblist,", penetrating "+
          (size > 1 ? "their very souls" : POSSESSIVE(oblist[0]) + " very " +
	   "soul") + " with your evil aura.");
    all2act(" turns " + POSSESSIVE(TP)+" malevolent gaze "+
	    "upon",oblist,", berating " + 
	    (size > 1 ? "them" : OBJECTIVE(oblist[0])) + " with " +
           POSSESSIVE(TP)+" dark aura.");
    return 1;
}

public int
wglare(string str)
{
    object *oblist;
    int size;

    oblist = parse_this(str, "[at] [the] %l");

    if (!(size = sizeof(oblist)))
	return NF("Glare at whom?\n");
    
    target(" glares menacingly at you, and you can see the " +
           "hatred and power gleaming in " + POSSESSIVE(TP) +
           " eyes.", oblist);
    actor("You glare menacingly at", oblist, ", confident that your " +
          "magic could shrivel " + (size > 1 ? "them" : OBJECTIVE(oblist[0])) +
	  " to dust.");
    all2act(" glares menacinly at", oblist, ", with a look of utter " +
            "hatred on " + POSSESSIVE(TP) + " face.");
    return 1;
}

public int
wlook(string str)
{
    if (strlen(str))
        return NF("Look at what?\n");

    write("You look upward, into the sky, searching for your master, " +
          "the dark moon, Nuitari.\n");
    all(" gazes up into the sky, apparently searching for something.");

    return 1;
}

public int
wmock(string str)
{
    object *oblist;
    int size;

    oblist = parse_this(str, "[the] %l");

    if (!(size = sizeof(oblist)))
        return NF("Mock whom?\n");

    target(" mocks your suggestion with a sibilant hissing laughter.", oblist);
    actor("You mock the suggestion" + (size > 1 ? "s" : "") + " made " +
	  "by", oblist, ".");
    all2act(" mocks", oblist, "'s suggestion" + (size > 1 ? "s" : "") +
	    " with a sibilant hissing laughter.");

    return 1;    
}

public int
wpraise(string str)
{
    if (strlen(str))
        return NF("Praise what?\n");

    write("You praise Nuitari for your good fortune.\n");
    all(" sends a praise to Nuitari for " + POSSESSIVE(TP) + " good " +
	"fortune.");
    return 1;
}

public int
wshake(string str)
{
    object *oblist;
    string tmp;
    int size;

    oblist = parse_this(str, "[the] %l");

    if (!(size = sizeof(oblist)))
	return NF("Shake whom?\n");

    tmp = "take";
    if ((TP->query_gender() == G_MALE) || (TP->query_gender() == G_NEUTER))
        tmp = "shake";

    target(" " + tmp + "s your hand. An icy chill runs down your spine, " +
           "as " + POSSESSIVE(TP) + " cold fingertips touch your skin.",
           oblist);
    actor("You " + tmp + " hands with", oblist,", taking grim pleasure in " +
           (size > 1 ? "their" : POSSESSIVE(oblist[0])) + " start at your " +
	  "chilling touch.");
    all2act(tmp+"s",oblist,"'s hand, and " + 
	    (size > 1 ? "they all" : PRONOUN(oblist[0])) +
	    " gasps softly, as " + 
	    (size > 1 ? "their" : POSSESSIVE(oblist[0])) + " eyes widen " +
	    "in alarm!");
    return 1;
}

public int
wsmile(string str)
{
    object *oblist;

    NF("Smile at whom?\n");

    if (!str)
    {
        write("You smile eerily, keeping your face a mask, devoid of all "+
              "emotion.\n");
        all(" smiles eerily, " + POSSESSIVE(TP) + " face a "+
            "cold mask, devoid of all emotion.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
        return 0;
    
    target(" smiles eerily at you, " + POSSESSIVE(TP) + 
           " face a cold mask, devoid of all emotion.", oblist);
    actor("You smile coldly at", oblist, ", keeping your face a mask "+
          "devoid of all emotion.");
    all2act(" smiles eerily, at", oblist, ", " + POSSESSIVE(TP)+
            " face a cold mask, devoid of emotion.");
    return 1;
}

