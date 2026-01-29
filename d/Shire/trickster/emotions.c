#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver.c";

#include <std.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <tasks.h>
#include <language.h>
#include "trickster.h"
#include "/d/Shire/sys/defs.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))

//  Hex defines
#ifndef NO_HEX
#define SP_HEX_MANA 20
#define SP_HEX_TASK TASK_ROUTINE
#define SP_HEX_LIST ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
      SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
      SS_FORM_ENCHANTMENT, SS_ELEMENT_DEATH })
/* It is supposed to be a curse, after all. ^^^^^ */
#endif

/*
 * The list of verbs and functions. Please add new in alfabetical order.
 */

mapping
query_trickster_emotions()
{
    return ([
      "armpit":"armpit",
      "barf":"barf",
      "bonk":"bonk",
      "bark":"bark",
      "coin":"coin",
      "flame":"flame",
#ifndef NO_HEX
      "hex":"hex",
#endif
      "hotfoot":"hotfoot",
      "hiss":"hiss",
      "innocent":"innocent",
      "juggle":"juggle",
      "meet":"meet",
      "nude":"nude",
      "seduce":"seduce",
      "shuffle":"shuffle",
      "tcackle":"tcackle",
      "tforce" : "tforce",
      "tflex":"tflex",
      "tgrin":"tgrin",
      "thumbdown":"thumbdown",
      "tdown":"thumbdown",
      "thumbup":"thumbup",
      "tup":"thumbup",
      "tlaugh":"tlaugh",
      "tpeer":"tpeer",
      "trip":"trip",
      "tsmile":"tsmile",
#ifndef NO_STRING_TRICK
      "tstring":"tstring",
#endif
#ifndef NO_VENT
      "vent":"vent",
#endif
      "wigg":"wigg"
    ]);
}


/* 
 * Here follow the actual functions. Please add new functions in the 
 * same order as in the function name list.
 */

int
armpit()
{
    string poss;

    write("You flex your muscles and sniff greedily in your right armpit.\n");
    all(" flexes " + HIS_HER(TP) + " muscles and sniffs greedily in " + HIS_HER(TP) +
      " right armpit.");
    SOULDESC("sniffing greedily in " + HIS_HER(TP) + " right armpit");
    return 1;
}

int
barf(string str)
{
    object  *who;
    SOULDESC("barfing all over the place");
    if (!str || str == "")
    {
	write("You barf all over the place, making a huge stinking mess!\n");
	write("Maybe you should stop hitting the bottle so hard?\n");
	all(" barfs all over, making a huge mess!  Maybe " + HE_SHE(TP) +
	  " should take it easy on the booze?\n");
	return 1;
    }
    who = parse_this(str, "[on] %l");
    if (!sizeof(who)) return 0;
    target(" barfs all over you!  How gross!", who);
    actor("You barf on", who);
    all2act(" barfs all over", who);
    return 1;
}

int
bark(string str)
{
    object  *who;
    SOULDESC("barking like a mad dog");
    if (!str || str == "")
    {
	write("You bark like a mad dog.\n");
	all(" barks like a mad dog.");
	return 1;
    }
    who = parse_this(str, "[at] %l");
    if (!sizeof(who)) return 0;
    target(" barks at you ferociously.", who);
    actor("You bark at", who);
    all2act(" barks ferociously at", who);
    return 1;
}



int
bonk(string str)
{
    object *oblist;

    if (!str)
    {
	notify_fail("Whom do you want to bonk?\n");
	return 0;
    }

    oblist = parse_this(str, "[on] %l");

    if (!sizeof(oblist))
    {
	notify_fail("That person doesn't seem to be here.\n");
	return 0;
    }

    if (sizeof(oblist) != 1)
    {
	NF("Bonking more than one person at the same time is rather "+
	  "impossible to do.\n");
	return 0;
    }
    target(" bonks you on the head with "+HIS_HER(TP)+
      " large stick!",oblist);

    actor("You bonk",oblist," on the head with your large stick!");

    all2act(" bonks",oblist," on the head with "+HIS_HER(TP)+
      " large stick!");
    return 1;
}


int
coin(string str)
{
    object  *who;

    if (!str || str == "")
    {
	write("You flip a gold coin in the air, just to watch it turn.\n");
	all(" flips a gold coin high into the air and catches it again.");
	return 1;
    }
    who = parse_this(str, "[at] %l");
    if (!sizeof(who)) return 0;
    target(" suddenly pulls a platinum coin from behind your ear!\nWow!", who);
    actor("You pull a platinum coin from the ear of", who);
    all2act(" suddenly pulls a platinum coin from the ear of", who);
    return 1;
}

int
flame(string str)
{
    object *oblist;

    if(!strlen(str))
    {
	write("You make your own finger burst into flame!\n");
	all(" makes " + HIS_HER(TP) + " fingers burst into flames!");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Flame whom?\n");
	return 1;
    }
    target(" waves " + HIS_HER(TP)  + " hands, and you burst into flames!", 
      oblist);
    actor("You wave your hands and set fire to", oblist);
    all2act(" waves " + HIS_HER(TP)  + " hands, and sets fire to", oblist);
    return 1;
}

int
tforce(string str)
{
    string func, args;

    if (!stringp(str) || !strlen(str))
    {
	NF(CAP(query_verb()) + " what?\n");
	return 0;
    }
    sscanf(str, "%s %s", str, args);
    if (str == "tforce")
    {
	NF("You can't force that trickster emotion.\n");
	return 0;
    }
    if (!stringp(func = query_trickster_emotions()[str]))
    {
	NF("There is no trickster emotion called "+str+"\n");
	return 0;
    }
    return call_other(this_object(), func, args);
}

int
tflex(string str)
{
    object  who;
    if (str)
	return 0;
    write("You flex your muscles to impress everyone.\n");
    all(" flexes " + HIS_HER(TP)  + " muscles.\nYou are not impressed at all.");
    SOULDESC("flexing " + HIS_HER(TP)  + " muscles");
    return 1;
}

#ifndef NO_HEX
int
hex(string who)
{
    object curse, *oblist;
    int success, is_wiz;


    is_wiz = TP->query_wiz_level();

    if (!strlen(who))
    {
	notify_fail("Who did you want to hex?\n");
	return 0;
    }
    if (!sizeof(oblist = parse_this(who, "[the] %l")))
    {
	notify_fail("There is no "+who+" here to hex.\n");
	return 0;
    }


    if (sizeof(oblist) != 1)
    {
	notify_fail("You can't hex more than one person!\n");
	return 0;
    }
    /* Let's see how successful she is */
    if (is_wiz)
	success = random(20) + 20; /* X 30 secs. == 10 to 20 min. */
    else if ((success = TP->resolve_task(SP_HEX_TASK, SP_HEX_LIST)) <= 0)
    {
	write("You failed to hex your target.\n");
	return 1;
    }
    FIXEUID
    /* Do the hex effect. */
    curse = clone_object(HEX);
    curse->shadow_me(oblist[0]);
    curse->destruct_hex_shadow(success * 30);

    /* Tell them about the hex! */
    actor("You place a hex upon", oblist ,"!");
    target(" begins to make strange noises, and wiggles "+HIS_HER(TP)+
      " fingers dangerously.\nYou feel a malignant aura surround you.",oblist);
    all2act(" begins to make strange noises, and wiggles "+HIS_HER(TP)+
      " fingers dangerously.\n"+CAP(HE_SHE(TP))+" places a hex on", oblist,"!");

    TP->add_mana(-SP_HEX_MANA);

    return 1;
}   
#endif


int
hiss(string str)
{
    object  *who;
    SOULDESC("hissing dangerously");
    if (!str || str == "")
    {
	write("You hiss dangerously.\n");
	all(" hisses dangerously.");
	return 1;
    }
    who = parse_this(str, "[at] %l");
    if (!sizeof(who)) return 0;
    target(" hisses dangerously in your direction.", who);
    actor("You hiss dangerously at", who);
    all2act(" hisses dangerously at", who);
    return 1;
}

int
hotfoot(string str)
{
    object  *who, hot;

    if (!str || str == "")
    {
	write("Give yourself a hotfoot? You must be crazy!\n");
	return 1;
    }
    who = parse_this(str, "[on] %l");
    if (!sizeof(who))
    { 
	notify_fail("You don't see that person here.\n");
	return 0;
    }
    if (sizeof(who) != 1)
    {
	notify_fail("Giving more than one person a hotfoot at the same time?\n"+
	  "My aren't we talented.\n");
	return 0;
    }
    if (who[0]->query_prop("_i_have_a_trickster_hotfoot"))
    {
	notify_fail("It's rather impossible to give someone a hotfoot if "+
	  "they are already hopping around the room from one already!\n");
	return 0;
    }
    if (who[0]->query_skill(SS_AWARENESS) > 
      (TP->query_stat(SS_LAYMAN) + random(100) - random(100)))
    {
	who[0]->catch_msg("You notice "+QTNAME(TP)+" sneaking up behind you "+
	  "trying to play some trick on you.  You give "+HIM_HER(TP)+
	  " a swift kick as a warning not to do this again.\n");
	TP->catch_msg(QCTNAME(who[0])+" sees you sneaking up on "+
	  HIM_HER(who[0])+" and gives you a swift kick preventing you "+
	  "from giving "+HIM_HER(who[0]) +" a hot foot.\n");
	say(QCTNAME(who[0])+" catches "+QTNAME(TP)+" sneaking up on "+
	  HIM_HER(who[0])+" and gives "+QTNAME(TP)+" a swift kick so that "+
	  HE_SHE(TP)+" won't do it again.\n",({who[0],TP}));
	return 1;
    }
    actor("You sneak up behind",who," and light some material "+
      "underfoot in order to give "+HIM_HER(who[0])+" a hot foot.");
    all2act(" sneaks up behind",who, " and lights something under "+
      HIS_HER(who[0])+" foot!");
    setuid(); seteuid(getuid());
    who[0]->add_prop("_i_have_a_trickster_hotfoot",1);
    hot = clone_object(HOTFOOT);
    hot->move(who[0]);
    hot->start_hot_foot(who[0]);
    return 1;
}



int
innocent(string str)
{
    object *oblist;

    if (!str)
    {
	write("You desperately try to look as innocent as you possibly "+
	  "can, in hopes that it will fool all onlookers into believing that "+
	  "you aren't responsible for what happened.\n");
	all("'s eyes start to shift from side to side and "+HE_SHE(TP)+" starts "+
	  "to whistle a cheerful tune in a pitiful attempt to look innocent.");
	return 1;
    }
    oblist = parse_this(str, "[at] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Look innocent at whom?\n");
	return 0;
    }
    actor("You desperately try to look as innocent as you can at",oblist," in "+
      "hopes that "+HE_SHE(oblist[0])+" will believe you.");
    target(" looks at you with an innocent smile on "+HIS_HER(TP)+" face.",oblist);
    all2act(" smiles at",oblist," with an innocent look on "+HIS_HER(TP)+" face.");
    return 1;
}

int
juggle(string str)
{
    int     i;
    string how;
    object   *oblist,  *juggle_array = ({});

    if (!str)
    {
	notify_fail("Juggle what?\n");
	return 0;
    }
    if (parse_command(str, all_inventory(TP), "%i", oblist))
    {
	oblist = NORMAL_ACCESS(oblist,0,0);
	if (sizeof(oblist) > 5)
	    juggle_array = ({oblist[0],oblist[1],oblist[2],oblist[3],oblist[4]});
	else
	    juggle_array = oblist;
    }
    if (!sizeof(juggle_array))
    {
	notify_fail("There is no "+str+" here for you to juggle!\n");
	return 0;
    }
    if (random(15) < sizeof(juggle_array))
    {
	write("You fumble your attempt to juggle "+COMPOSITE_DEAD(juggle_array)+
	  ".  Causing everything to land on your head giving you a nasty "+
	  "bump!!\n\nOuch!!!\n");
	allbb(" fumbles "+HIS_HER(TP)+" attempt to juggle "+COMPOSITE_DEAD(juggle_array)+
	  ".  Causing everything to land on "+HIS_HER(TP)+" head!!!");
	return 1;
    }
    write("You skillfully juggled "+COMPOSITE_DEAD(juggle_array)+".\n");
    switch(sizeof(juggle_array))
    {
    case 1:
	how = "are left disappointed by";
	break;
    case 2:
	how = "were slightly amused by";
	break;
    case 3:
	how = "are left amazed by";
    case 4:
	how = "marvel at";
	break;
    case 5:
	how = "are left totally flabergasted by";
	break;
    }
    allbb(" skillfully juggles "+COMPOSITE_DEAD(juggle_array)+
      ".\nYou "+ how +" "+ HIS_HER(TP) +" skill.");
    return 1;
}

int
meet(string str)
{
    object *who;

    if (!str)
    {
	notify_fail("Meet whom?\n");
	return 0;
    }

    who = parse_this(str, "[the] %l");

    if (!sizeof(who))
    {
	notify_fail("That person doesn't seem to be here.\n");
	return 0;
    }

    if (sizeof(who) != 1)
    {
	notify_fail("It's rather difficult to meet more than one person "+
	  "at a time.\n");
	return 0;
    }


    target(" greets you, shaking your hand.\nOuch! "+CAP(HE_SHE(TP))+
      " must have had a tack in "+HIS_HER(TP)+" hand!!!",who);

    actor("You greet",who," with the tricky handshake.");

    all2act(" shakes",who,"'s hand, causing "+HIM_HER(who[0])+" to wince, holding "+
      HIS_HER(who[0])+" hand tenderly.");
    return 1;
}

int
nude(string str)
{
    object  *who;

    if (!str)
    {
	write("You wave your hands and your pants fall down! Everyone laughs at you!\n");
	all(" waves " + HIS_HER(TP) + " hands, and " + HIS_HER(TP)        + " pants fall down!!\n" +
	  "You fall down laughing!");
	SOULDESC("pulling up " + HIS_HER(TP) + " pants");
	return 1;
    }
    who = parse_this(str, "%l");
    if (!sizeof(who)) return 0;
    if(random(4) == 3 && !(TP->query_wiz_level()))
    {
	write("You fail to do the trick correctly, and your own pants fall down.\n");
	write("Everyone laughs at you.\n");
	all(" waves " + HIS_HER(TP) + " hands, and " + HIS_HER(TP) + " pants fall down!!\n" +
	  "You fall down laughing!");
	return 1;
    }
    str = capitalize(str);

    target(" waves " + HIS_HER(TP) + " hands and your pants fall down!", who);
    actor("You wave your hands, and embarrass", who);
    all2act(" waves " + HIS_HER(TP) + " hands, and", who, "'s pants fall down!");
    return 1;
}


int
seduce(string str)
{
    object  *who;
    if (!str || str == "")
    {
	write("You try to look seductive.\n");
	all(" tries to look seductive.");
	SOULDESC("trying to look seductive");
	return 1;
    }
    who = parse_this(str, "[at] %l");
    if (!sizeof(who)) return 0;
    target(" tries to seduce you.", who);
    actor("You whisper sweet words of love to", who);
    all2act(" tries to seduce", who);
    return 1;
}

int
shuffle(string str)
{
    int tmp;
    string dance;
    object  *who;

    tmp = random(7);   

    switch(tmp)
    {
    case 0:
	dance = "Waymeet";
	break;
    case 1:
	dance = "Bree";
	break;
    case 2:
	dance = "Hobbiton";
	break;
    case 3:
	dance = "Hardbottle";
	break;
    case 4:
	dance = "Frogmorton";
	break;
    case 5:
	dance = "Brandybuck";
	break;
    case 6:
	dance = "Nobish";
	break;
    default:
	dance = "Michel Delving";
	return 0;
    }

    if (!str)
    {
	write("You do the " + dance + " shuffle!\n");
	all(" does the " + dance + " shuffle! You watch amazed!");
	return 1;
    }
    else
    {
	who = parse_this(str, "[at] %l");
	if (!sizeof(who)) return 0;
	target(" does the " + dance + " shuffle with you!", who);
	actor("You do the " + dance + " shuffle with", who);
	all2act(" does the " + dance + " shuffle with", who,"\nYou watch amazed!");
	return 1;
    }
}


int
tcackle(string str)
{

    write("You throw your head back and cackle with mischievous glee, "+
      "thoroughly enjoying all the mischief you have just caused.\n");
    all(" throws "+HIS_HER(TP)+" head back and cackles with mischievous "+
      "glee, reveling in all the mischief "+HE_SHE(TP)+" has just "+
      "caused.");
    return 1;
}

int
tgrin(string str)
{
    object   *oblist;
    string   *how;

    how = parse_adverb_with_space(str, "wickedly", 0);

    if (!strlen(how[0]))
    {
	write("You grin"+how[1]+", thinking of all the joys of "+
	  "being a Trickster.\n");
	all(" grins"+how[1]+", with a twinkle of mischief in "+HIS_HER(TP)+
	  " eyes.");
	return 1;
    }

    oblist = parse_this(how[0], "[at] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Grin [how] at whom?\n");
	return 0;
    }

    actor("You grin"+how[1]+" at",oblist,", thinking of all the "+
      "nasty tricks you could play on "+HIM_HER(oblist[0])+".");
    target(" grins"+how[1]+" at you, "+HIS_HER(TP)+" eyes "+
      "sparkling with mischief.",oblist);
    all2act(" grins"+how[1]+" at",oblist,", with a mischievous "+
      "twinkle in "+HIS_HER(TP)+" eyes.");
    return 1;
}

int
thumbdown(string str)
{
    object  *who;
    if (!str || str == "")
    {
	write("You turn your thumb downwards as a sign of "+
	  "disapproval.\n");
	all(" turns " + HIS_HER(TP) +" thumb downwards as a sign of "+
	  "disapproval.");
	return 1;
    }
    who = parse_this(str, "[at] %l");
    if (!sizeof(who)) return 0;
    target(" turns "+HIS_HER(TP)+" thumb downwards in your direction.",who);
    actor("You turn your thumb downwards at",who);
    all2act(" turns "+HIS_HER(TP)+" thumb down at",who,", as a sign of disapproval.");
    return 1;
}

int
thumbup(string str)
{
    object  *who;
    if (!str || str == "")
    {
	write("You hold up your thumb.\n");
	all(" holds up " + HIS_HER(TP)        + " thumb.");
	SOULDESC("holding up " + HIS_HER(TP)        + " thumb");
	return 1;
    }
    who = parse_this(str, "[at] %l");
    if (!sizeof(who)) return 0;
    target(" holds up " + HIS_HER(TP)        + " thumb in your direction.",
      who);
    actor("You hold up your thumb at", who);
    all2act(" holds up "+HIS_HER(TP)+" thumb at", who);
    return 1;
}

int
tlaugh(string str)
{
    object  *who;

    if (!str || str == "")
    {
	write("You throw your head back and laugh mischievously, going into "+
	  "a fit of hysterics.\n");
	all(" laughs until "+HE_SHE(TP)+" turns red in the face and tears "+
	  "stream down "+HIS_HER(TP)+" face.");
	return 1;
    }
    who = parse_this(str, "[at] %l");
    if (!sizeof(who)) return 0;
    target(" points at you and laughs until "+HE_SHE(TP)+" turns bright red!",
      who);
    actor("You laugh, going into hysterics at the thought of", who);
    all2act(" turns red in the face laughing at", who);
    return 1;
}

int
tpeer(string str)
{
    write("You peer mischievously around the area, searching "+
      "fanatically for your next victim.\n");
    all(" peers mischievously around the area, searching "+
      "for something.");
    return 1;
}

int
trip(string str)
{
    object *who;

    if (!str)
    {
	write("You trip over your own clumsy feet and fall down!\nHow "+
	  "embarassing!\n");
	all(" trips over "+HIS_HER(TP)+" own two feet and falls down.\n"+
	  "You laugh uproariously.");
	return 1;
    }

    who = parse_this(str, "[on] %l");

    if (!sizeof(who))
    {
	notify_fail("That person doesn't seem to be here.\n");
	return 0;
    }

    if (sizeof(who) != 1)
    {
	notify_fail("Trying to trip more than one person?\n"+
	  "How foolish of you.\n");
	return 0;
    }


    target(" slips up next to you and trips you up.\nYou fall down "+
      "rather gracelessly.",who);

    actor("You trip",who," with a quick placement of your left foot.");

    all2act(" trips",who," causing "+HIM_HER(who[0])+" to fall gracelessly on "+
      HIS_HER(who[0])+" backside.");
    return 1;
}

int
tsmile(string str)
{
    object  *oblist;
    string  *how;

    how = parse_adverb_with_space(str, "mischievously", 0);

    if (!strlen(how[0]))
    {
	write("You smile"+how[1]+", day-dreaming of all the tricks "+
	  "you'll be playing on some poor sucker today.\n");
	all(" smiles"+how[1]+", with a queer gleam in "+HIS_HER(TP)+" eyes.");
	return 1;
    }

    oblist = parse_this(how[0], "[at] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Smile [how] at whom?\n");
	return 0;
    }

    actor("You smile"+how[1]+" at",oblist,", thinking of the perfect "+
      "prank to play on "+HIM_HER(oblist[0])+".");
    target(" smiles"+how[1]+" at you, "+HIS_HER(TP)+" eyes filled "+
      "with a queer gleam.  You start to wonder what "+HE_SHE(TP)+" is "+
      "smiling about.",oblist);
    all2act(" turns and smiles"+how[1]+" at",oblist,", with a queer gleam "+
      "in "+HIS_HER(TP)+" eyes.");
    return 1;
}

#ifndef NO_STRING_TRICK
int
tstring(string str)
{
    object *trigger;

    if (TP->query_prop(TRICKSTER_STRING_PROP))
    {
	notify_fail("But you've already attached your string to something!\n");
	return 0;
    }
    trigger = FIND_STR_IN_OBJECT(str, TP);
    if (!sizeof(trigger))
    {
	notify_fail("You find nothing to place your string on.\n");
	return 0;
    }
    if (sizeof(trigger) != 1)
    {
	notify_fail("You can only trap one object at a time.\n");
	return 0;
    }
    if (trigger[0]->query_trickster_shadow() == 666)
    {
	notify_fail("There seems to be a trick being played on "+
	  LANG_THESHORT(trigger[0])+" already.\n");
	return 0;
    }
    if (trigger[0]->query_prop(OBJ_M_NO_DROP))
    {
	notify_fail("Why would you attach a string to something which you "+
	  "can't drop?\n");
	return 0;
    }
    if (trigger[0]->query_prop(OBJ_M_NO_GET))
    {
	notify_fail("Why attach a string to something which you can "+
	  "not get?\n");
	return 0;
    }
    write("You quickly attach a string to "+LANG_THESHORT(trigger[0])+
      " and place it on the ground, hoping that some unknowing fool will "+
      "come around to entertain you.\n");
    say(QCTNAME(TP)+" attaches something to "+LANG_THESHORT(trigger[0])+
      " and then carefully places it on the ground infront of "+HIM_HER(TP)+
      ".\n");
    setuid(); seteuid(getuid());
    clone_object(STRING_TRICK)->shadow_me(trigger[0]);
    trigger[0]->set_up_trap(TP);
    trigger[0]->move(ENV(TP),1);
    TP->add_prop(TRICKSTER_STRING_PROP,1);
    return 1;
}
#endif

#ifndef NO_VENT
int
vent(string str)
{
    object target, *oblist;

    NF("Who do you wish to ventriloquize?\n");
    if(!strlen(str)) return 0;

    NF("No such person bub!\n");
    if (!sizeof(oblist = parse_this(str, "[through] %i"))) 
	return 0;

    target = oblist[0];

    if (target->query_wiz_level())
    {
	write("You can't impersonate a wizard!\n");
	return 1;
    }   

    if (interactive(target) && target->query_average_stat() < 25)
    {
	write("You can't impersonate a newbie.\n");
	return 1;
    }

    TP->catch_tell("Okay, what do you want to say through "+
      (living(target) ? target->query_the_name(TP) : LANG_THESHORT(target))+
      "?\n");

    input_to("get_words", 0, target);
    return 1;
}

int
get_words(string words, object victim)
{
    int watcheraware, totalaware, victimint, guildstat, i;
    object *watchers;

    if (words == "" || !words)
    {
	TP->catch_msg("You can't attempt to make "+
	  (living(victim) ? victim->query_the_name(TP) : LANG_THESHORT(victim))+
	  " say nothing!.\n");
	return 1;
    }

    watchers = FILTER_OTHER_LIVE(all_inventory(environment(TP)));


    guildstat = TP->query_stat(SS_LAYMAN);

    if (living(victim))
    {
	victimint = victim->query_stat(SS_INT);
	if ((victimint) > (guildstat + random(25)))
	{
	    victim->catch_msg(QCTNAME(TP)+ " starts trying to "+
	      "imitate your voice.  You quickly kick "+HIM_HER(TP)+" to "+
	      "put a stop to it.\n");
	    victim->command("kick "+TP->query_real_name());
	    TP->catch_msg(QCTNAME(victim)+ " seems to have caught on to "+
	      "you.\n");
	    say(QCTNAME(victim)+ " stares at "+QTNAME(TP)+" angrily.\n",
	      ({TP,victim}));
	    return 1;
	}
	if (interactive(victim))
	{
	    setuid(); seteuid(getuid());
	    log_file("vent", ctime(time()) +" "+ TP->query_cap_name() +
	      " forced "+victim->query_cap_name() +" to say: "+words +".\n");
	}
	victim->command("$say "+words);
	victim->catch_tell("You weren't aware you were going to say that.\n");
    }
    else
    {
	if (ENV(victim) == TP)
	{
	    TP->catch_tell("You try to make others believe that "+
	      LANG_THESHORT(victim)+" you are holding says: "+words+"\n");
	    say("A voice coming from "+LANG_THESHORT(victim)+" held by "+
	      QTNAME(TP)+" says: "+ words +"\n");
	}
	else
	{
	    tell_room(ENV(victim), "A voice coming from "+LANG_THESHORT(victim)+
	      " says: "+ words +"\n");
	}
    }
    for (i = 0; i < sizeof(watchers); i++)
    {
	watcheraware = watchers[i]->query_skill(SS_AWARENESS);
	totalaware = watcheraware + totalaware;
    }
    /* Watchers might see lips moving! */
    watchers -= ({victim});
    if ((totalaware) > (guildstat + random(30)))
    {
	for (i = 0; i < sizeof(watchers); i++)
	    watchers[i]->catch_msg(QCTNAME(TP) + "'s lips move slightly.\n");
	TP->catch_tell("You think others might have caught on to you though.\n");
    }
    return 1;

}
#endif


int
wigg(string str)
{
    object *oblist;

    if(!strlen(str))
    {
	write("You wiggle your fingers dangerously.\n");
	all(" wiggles " + HIS_HER(TP) + " fingers dangerously.");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Wiggle your fingers at whom?\n");
	return 1;
    }
    target(" wiggles " + HIS_HER(TP) + " fingers dangerously in your "+
      "general direction.", oblist);
    actor("You wiggle your fingers at", oblist);
    all2act(" dangerously wiggles " + HIS_HER(TP) + " fingers at", oblist);
    return 1;
}
