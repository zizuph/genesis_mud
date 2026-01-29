/* This file is /d/Shire/hobbit/hobbit_soul.c 
 *
 * Intended for use by the Adventuresome Hobbits of
 *  The Shire domain in Genesis.
 *   Apologies to Elessar of Gondor for shamelessly stealing
 *   his rangersoul. *grin*
 *
 *   Dunstable, July 1994
 *
 * hcheer added March 20, 1995 by Dunstable
 * hriddle added March 21, 1995 by Dunstable
 * hsift, hrock, hhug, hrage, hstance, hbelt added by Jaypeg, 1997
 * hpride added by Jaypeg, Jan 2000
 * hparty added by Finwe, Dec 2003
 * Changed help hobbit emotions to help hobbit emotes to avoid a conflict
 *    Varian 2016
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";
#include <macros.h>
#include <formulas.h>
#include "hobbit.h"
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/sys/defs.h"
#include "hsing.h"
#include "hlist.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define S_RIDDLE_ANSWER "s_riddle_answer"
#define PIPE  "_hobbit_race_guild_pipe_"
#define IS_SMOKING  query_pipe_is_smoking()
#define FLAVOUR     query_pipe_flavour()
#define MORE(x)   this_player()->more(read_file(x,2))

int alarm_id;

string
get_soul_id()
{
    return "Adventuresome Hobbits";
}

int
query_cmd_soul()
{
    return 1;
}

mapping
query_cmdlist()
{

    setuid();
    seteuid(getuid());

    return ([
      "help"       :   "do_help",
      "hastonish"  :   "hastonish",
      "hbow"       :   "hbow",
      "hbuff"      :   "hbuff",
      "hflip"      :   "e_hflip",
      "hcheck"     :   "hcheck",
      "hchew"      :   "hchew",
      "hcheer"     :   "hcheer",
      "hcringe"    :   "hcringe",
      "hdance"     :   "hdance",
      "hdemand"    :   "hdemand",
      "hempty"     :   "hempty",
      "hfidget"    :   "hfidget",
      "hglint"     :   "hglint",
      "hhanky"     :   "hhanky",
      "hharvest"   :   "hharvest",
      "hinform"    :   "hinform",
      "hinquire"   :   "hinquire",
      "hjump"      :   "hjump",
      "hkick"      :   "hkick",
      "hlaugh"     :   "hlaugh",
      "hlist"      :   "list_active_hobbits",
      "hlook"      :   "hlook",
      "hmourn"     :   "hmourn",
      "hnap"       :   "hnap",
      "hobbitlist" :   "list_active_hobbits",
      "hparty"     :   "hparty",
      "hpick"      :   "hpick",
      "hpuff"      :   "hpuff",
      "hregard"    :   "hregard",
      "hriddle"    :   "hriddle",
      "hrumble"    :   "hrumble",
      "hshout"     :   "hshout",
      "hskip"      :   "hskip",
      "hsing"      :   "hsing",
      "hsmile"     :   "hsmile",
      "hspin"      :   "hspin",
      "hstretch"   :   "hstretch",
      "hthink"     :   "hthink",
      "hthought"   :   "hthought",
      "htummy"     :   "htummy",
      "htwirl"     :   "htwirl",
      "hsit"       :   "hsit",
      "hbelt"      :   "hbelt",
      "hsift"      :   "hsift",
      "hrock"      :   "hrock",
      "hhug"       :   "hhug",
      "hrage"      :   "hrage",
      "hstance"    :   "hstance",
      "hpride"     :   "hpride",
      "hwish"      :   "hwish"
    ]);

    /* The above are in the form: command : function */

}

int
do_help(string str)
{
    setuid(); seteuid(getuid());
    if(str == "hobbit")
    {
	MORE(HOBBIT_HELP+"general");
	write("And please report any problems you may encounter "+
	  "with the hobbit guild to "+
	  COMPOSITE_WORDS(map(HOBBIT_RACE_GUILD_MASTER, capitalize)) + ".\n");
	return 1;
    }

    if(str == "hobbit emotions")
    {
	MORE(HOBBIT_HELP+"emotes");
	return 1;
    }
        if(str == "hobbit emotes")
    {
    MORE(HOBBIT_HELP+"emotes");
    return 1;
    }

    if(str == "hobbit family")
    {
	MORE(HOBBIT_HELP+"family");
	return 1;
    }
    if (str == "hobbit news")
    {
	MORE(HOBBIT_NEWS);
	return 1;
    }
    return 0;
}


int
hastonish(string str)
{
    object *oblist;
    object pipe = present(PIPE, TP);

    if (!pipe)
    {
	write("You are so astonished at the thought, you stammer to " +
        "say something!\n");
    all(" gasps in astonishment, stammering for something to say!\n");
	return 1;
    }

// has a hobbit pipe    
	write(" You are so astonished at the thought that you nearly " +
        "drop your pipe!\n");
	all(" is so astonished "+HE_SHE(TP)+" nearly drops "+
        HIS_HER(TP)+" pipe in disbelief!");
	return 1;
}

int
hbow(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("You get down on one knee and bow, awkwardly.\n");
	all(" bows awkwardly from one knee.");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Bow to whom?\n");
	return 1;
    }

    actor("You bow, presenting yourself to the service of",oblist,".");
    target(" bows to you, at your service.",oblist);
    all2act(" bows to",oblist,", at their service.");
    return 1;

}

int
hbuff(string str)
{
    object *oblist;
    object pipe = present(PIPE, TP);

    if (!pipe)
    {
	notify_fail("But don't have a pipe to buff!\n");
	return 0;
    }
    if(!strlen(str))
    {
	write("You buff and polish your pipe to a brilliant shine.\n");
	all(" buffs and polishes "+HIS_HER(TP)+" pipe to a brilliant shine.");
	return 1;
    }
}


void
do_toast(object player)
{
    player->command("drink drink");
}

int
hcheer(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You suddenly burst into a cheer.\n");
	all(" suddenly starts cheering at something.");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
	write("Wish whom good health and prosperity?\n");
	return 1;
    }

    actor("You cheer",oblist," for good health and prosperity.");
    target(" cheers your good health and prosperity.",oblist);
    all2act(" raises "+HIS_HER(TP)+" glass, toasting health and wealth for",oblist);
    alarm_id = set_alarm(3.0,0.0,&do_toast(TP));
    return 1;
}

int
hcheck()
{
    write("You check the condition of your pipe, making sure " +
        "it's still in one piece.\n");
    say(QCTNAME(TP) + " checks the condition of "+HIS_HER(TP)+
        "pipe, making sure it's still in one piece.\n");
    return 1;

}


int
hchew(string str)
{
    object *oblist;
    object pipe = present(PIPE, TP);

    if (!pipe)
    {
	notify_fail("But you have no pipe here to chew on!\n");
	return 0;
    }
    if(!strlen(str))
    {
	write("You chew nervously on your pipe.\n");
	all(" chews nervously on "+HIS_HER(TP)+" pipe.");
	return 1;
    }
    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Chew on your pipe for whom?\n");
	return 1;
    }

    actor("You gnaw nervously on your pipe, concerned for",oblist);
    target(" gnaws nervously on "+HIS_HER(TP)+" pipe, concerned for you.",oblist);
    all2act(" gnaws "+HIS_HER(TP)+" pipe nervously, concerned for",oblist);
    return 1;
}

int
hcringe(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("Your face blanches and you swallow deep. Danger is at hand!\n");
	all(" goes white in the face, swallowing deeply.");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Cringe behind whom?\n");
	return 1;
    }

    actor("You blanch at the danger ahead and cringe behind",oblist,".");
    target(" cringes behind you, avoiding the danger.",oblist);
    all2act(" cringes behind",oblist,", avoiding the danger of the moment.");
    return 1;

}

int
hdance()
{
    write("You dance by lifting one foot and hopping on the other.\n");
    say(QCTNAME(TP) + " lifts one foot and hops on the other.\n"+
      "You think "+HE_SHE(TP)+" is trying to dance. What a sight!\n");
    return 1;

}

public int
e_hflip(string arg)
{
    object *oblist;

    notify_fail("Backflip how?\n");

    if (!strlen(arg))
    {
	all(" performs several adroit backflips in order to impress you.");
	write("You do several backflips in order to pass the time.\n");
	return 1;
    }

    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
	return 0;

    actor("You do two quick backflips all over", oblist, ".");
    all2act(" does two quick backflips over", oblist, ".");
    target(" does two quick backflips over you.", oblist);
    return 1;
}

int
hempty(string str)
{
    object *oblist;
    object pipe = present(PIPE, TP);
    if (!pipe)
    {
	notify_fail("But you have no pipe to empty!!!\n");
	return 0;
    }
    if (pipe->IS_SMOKING)
    {
	notify_fail("You shouldn't empty a lit pipe, perhaps you should "+
	  "extinguish your pipe first before you try and empty it.\n");
	return 0;
    }
    if(!strlen(str))
    {
	write("You empty the ashes from your pipe with a good whack!\n");
	say(QCTNAME(TP) + " empties the ashes from "+HIS_HER(TP)+" pipe with "+
	  "a good solid whack!\n");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");
    if(!sizeof(oblist))
    {
	write("Empty your pipe on whom?\n");
	return 1;
    }

    actor("You empty your pipe on",oblist,"'s head.");
    target(" empties "+HIS_HER(TP)+" pipe by tapping it on your head.",oblist);
    all2act(" empties "+HIS_HER(TP)+" pipe on the head of",oblist);
    tell_room(environment(TP),"Thwok, twok, twok!\n");
    return 1;

}

int
hfidget()
{
    int ran;
    ran = random(3);

    if(ran == 0)
    {
	write("You fidget, straightening your hair.\n");
	say(QCTNAME(TP)+" fidgets, straightening "+HIS_HER(TP)+" hair.\n");
	return 1;
    }

    if(ran == 1)
    {
	write("You fidget, keeping your feet clean of debris.\n");
	say(QCTNAME(TP)+" fidgets, cleaning "+HIS_HER(TP)+" feet absentmindedly.\n");
	return 1;
    }

    if(ran == 2)
    {
	write("You fidget, inspecting the buttons on your clothes.\n");
	say(QCTNAME(TP)+" fidgets, inspecting the buttons on "+HIS_HER(TP)+" clothing.\n");
	return 1;
    }

}

int
hglint(string str)
{
    if(!strlen(str))
    {
	write("Your eyes light up at a secret thought.\n");
	say(QCTNAME(TP) + "'s eyes light up at some secret thought.\n");
	return 1;
    }
    if(strlen(str) > 35)
    {
	write("Your eyes are not THAT evocative.\n");
	return 1;
    }

    write("Your eyes glint at the thought of "+str+".\n");
    say(QCTNAME(TP)+ "'s eyes glint brightly, apparently thinking of "+str+".\n");
    return 1;

}

int
hhanky(string str)
{
    object *oblist;
    if(!strlen(str))
    {
	write("You rummage through your pocketses for a handkerchief.\n");
	say(QCTNAME(TP) + " rummages through "+HIS_HER(TP)+" pockets for a handkerchief.\n");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Let whom borrow your hanky?\n");
	return 1;
    }

    actor("You lend a handkerchief to",oblist," to cry into.");
    target(" lends you a handkerchief to cry into.",oblist);
    all2act(" lends "+HIS_HER(TP)+" handkerchief to",oblist," to cry into.");
    return 1;

}

int
hharvest()
{
    write("You wonder if the pipeweed harvest will be as good " +
        "this year as in the past.\n");
    say(QCTNAME(TP) + " wonders if this year's pipeweed harvest " +
        "will be as good as in the past.\n");
    return 1;

}

int
hinform(string str)
{
    if(!strlen(str))
    {
	write("Inform your audience on what topic?\n");
	return 1;
    }

    if(str == "beer" || str == "brew")
    {
	write("You give your audience a brief summary of the finer points of making beer.\n");

	say(QCTNAME(TP) + " bores you with all the miniscule details of making beer.\n");
	return 1;
    }

    if(str == "gardening" || str == "garden" || str == "herbs")
    {
	write("You tell all who will listen about gardening and herblore.\n");

	say(QCTNAME(TP) + " gives a long, cluttered speech about gardening and herbs.\n");
	return 1;
    }

    if(str == "tobacco" || str == "pipeweed")
    {
	write("You educate your audience on the matter of tobacco, even mentioning Old Toby.\n");

	say(QCTNAME(TP)+" goes on and on about tobacco and some person named Tobold.\n");
	return 1;
    }
    write("You don't know much about "+str+" so you decide not to speak about it.\n");
    return 1;

}

int
hinquire(string str)
{
    object *oblist;

    if (!str)
    {
	notify_fail("To whom are you going to inquire about the next meal?\n");
	return 0;
    }
    oblist = parse_this(str, "[to] %l");

    if (!sizeof(oblist))
    {
	notify_fail("There is no "+str+" here to inquire about the next meal.\n");
	return 0;
    }
    actor("You politely inquire to",oblist," about when the next meal will be, "+
      "with a hungry look in your eyes");
    target(" politely inquires to you about when the next meal might be, "+
      "the poor hobbit looks like "+HE_SHE(TP)+" is starving.",oblist);
    all2act(" politely inquires to",oblist," about when the next meal might "+
      "be, the poor hobbit looks like "+HE_SHE(TP)+" is starving.");
    return 1;
}

int
hkick(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	notify_fail("Who's shins do you wish you could kick?\n");
	return 0;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("There is no "+str+" here for you to do that to.\n");
	return 0;
    }

    actor("You stare at",oblist,"'s shins, wishing you could kick "+
      "them, hard!!");
    target(" starts staring at your shins, with an evil grin "+
      "on "+HIS_HER(TP)+" face.",oblist);
    all2act(" starts to stare at",oblist,"'s shins, with an evil "+
      "grin on "+HIS_HER(TP)+" face.");
    return 1;

}

int
hlaugh(string str)
{
    if (living(present(str, environment(TP))))
    {
	notify_fail("It's impolite to laugh at other people.\n");
	return 0;
    }
    write("You laugh a jolly and rumbunctious laugh.\n");
    all(" laughs a jolly and rambunctious laugh.");
    return 1;
}

int
hlook(string str)
{
    object *oblist;
    if(!strlen(str))
    {
	write("Look up at whom?\n");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Look up at whom?\n");
	return 1;
    }

    actor("You look up at",oblist," pleadingly.");
    target(" looks up at you pleadingly. Well, "+HE_SHE(TP)+" would have "+
      "to, wouldn't "+HE_SHE(TP)+"?",oblist);
    all2act(" looks up at",oblist,", pleadingly.");
    return 1;
}



int
hmourn(string str)
{
    write("Your eyes well up with tears as you remember that you "+
      "missed a meal!\n");
    all("'s well up with tears, "+HE_SHE(TP)+" must have missed a meal.");
    return 1;
}
int
hnap()
{
    write("You find a comfortable place on the ground, curl up "+
      "and drift off into sleep.\n");
    say(QCTNAME(TP) + " finds a comfortable spot on the ground for "+
      "a little nap.\n");
    return 1;
}

int
hparty()
{
    write("You grin wildly and clap your hands excitedly as you think " +
        "about the next party.\n");
    say(QCTNAME(TP)+ " grins wildly and claps "+HIS_HER(TP)+" hands excitedly as " + HE_SHE(TP) + " thinks about the next party.\n");
    return 1;
}


int
hpick()
{
    write("You pick some road-dust and other debris from your "+
      "hairy feet.\n");
    say(QCTNAME(TP)+ " picks "+HIS_HER(TP)+" feet clean of dirt and debris.\n");
    return 1;
}


int
hpuff(string str)
{
    object *oblist;
    object pipe = present(PIPE, TP);

    if (!pipe)
    {
	notify_fail("But you have no pipe to take a puff from.\n");
	return 0;
    }
    if (!pipe->IS_SMOKING)
    {
	notify_fail("Taking a puff from an un-lit pipe is a skill which you "+
	  "haven't mastered yet.\n");
	return 0;
    }
    if(!strlen(str))
    {
	write("You pull deeply on your pipe and send perfectly formed "+
	  "rings of smoke floating high into the air.\n");
	say(QCTNAME(TP) + " inhales deeply on "+HIS_HER(TP)+" pipe, sending fluffy, white rings floating into the air.\n");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");
    if(!sizeof(oblist))
    {
	write("Puff rings at whom?\n");
	return 1;
    }

    actor("You puff smoke into ",oblist,"'s face!");
    target(" blows a cloud of smoke from "+HIS_HER(TP)+" pipe in your face!",oblist);
    all2act(" blows smoke into",oblist,"'s face!");
    return 1;
}

int
hregard(string str)
{
    object *oblist;
    object pipe = present(PIPE, TP);
    if (!pipe)
    {
	notify_fail("It's quite impossible to regard someone over a pipe if "+
	  "you do not have one.\n");
	return 0;
    }
    if (!pipe->IS_SMOKING)
    {
	notify_fail("You would look rather silly regarding someone over an "+
	  "un-lit pipe.\n");
	return 0;
    }
    if(!strlen(str))
    {
	write("Regard whom?\n");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Regard whom?\n");
	return 1;
    }

    actor("You regard",oblist," carefully over the bowl of your pipe.");
    target(" eyes you carefully over the bowl of "+HIS_HER(TP)+" pipe.",oblist);
    all2act(" eyes",oblist," carefully over the bowl of "+HIS_HER(TP)+" pipe.");
    return 1;

}

int
hriddle(string question)
{

    if(!question)
    {
	write("Pose what riddle?\n");
	return 1;
    }

    if(present("_hob_riddle_obj_",environment(TP)))
    {
	write("There is still an unsolved question, you must wait until "+
	  "it has been solved or the time limit has been reached.\n");
	return 1;
    }

    write("Ok, your riddle is: "+question+" What is your answer?\n");

    say(QCTNAME(TP)+ " asks this riddle: "+question+"\n");

    input_to("make_answer");
    return 1;

}

void 
make_answer(string str)
{
    object riddle;
    string ans;

    ans = str;

    FIXEUID

    riddle =  clone_object(HOBGLD_DIR + "riddle_obj");
    riddle->move(environment(TP),1);

    riddle->set_answer(str);
    riddle->set_riddler(TP);
    return;

}


int
hrumble()
{
    write("Hunger racks your body, it must have been minutes since "+
      "you last ate!\n");
    say(QCTNAME(TP)+ "'s stomach begins to make a loud rumbling sound!\n");
    SOULDESC("looking rather hungry");
    return 1;
}

int
hshout(string str)
{
    string fam;
    if(!strlen(str))
    {
	TP->command("$shout For the Shire!");
	return 1;
    }

    if(str != "family")
    {
	write("Shout for what? Family?\n");
	return 1;
    }

    fam = TP->query_guild_title_race();

    TP->command("$shout For all the "+fam+"s of the Shire!");
    return 1;

}



int
hskip(string str)
{
    object *oblist;

    if(!strlen(str))
    {
	write("You skip around merrily.\n");
	say(QCTNAME(TP)+ " skips around merrily.\n");
	return 1;
    }

    oblist = parse_this(str, "[with] %l");
    if(!sizeof(oblist))
    {
	write("Skip with whom?\n");
	return 1;
    }

    actor("You grab",oblist," by the arm and skip around, carefree.");
    target(" grabs you by the arm and you two go skipping around carefree.",oblist);

    all2act(" takes",oblist," by the arm and they go skipping around.");
    return 1;
}

int
hsmile()
{
    write("You smile greedily, with a mischevious twinkle "+
      "in your eyes.\n");

    say(QCTNAME(TP) + " smiles greedily, a mischevious thought "+
      "hidden behind "+HIS_HER(TP)+" eyes.\n");
    return 1;

}

// Some routines in hspin taken directly from 'tackle'.
int
hspin(string str)
{
    object *oblist;

    if(!strlen(str))
    {
	write("You start spinning in a circle, but quickly get dizzy and "+
	  "fall down.\n");

	say(QCTNAME(TP) + " starts spinning around in a circle, but "+
	  "soon loses "+HIS_HER(TP)+" balance, falling into a heap of hobbit.\n");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Spin whom?\n");
	return 0;
    }

    if (random(10)) /* fail less than tackle! */
    {
	target(" grabs you by the arm and starts spinning you.\n" +
	  capitalize((string) this_player()->query_pronoun()) +
	  " suddenly lets go, sending you flying.\n" +
	  "You fall to the ground, bouncing and spinning.", oblist);
	actor("You spin", oblist);
	all2act(" spins", oblist, ".\n" + ((sizeof(oblist) > 1) ? "They fall":
	    capitalize((string) oblist[0]->query_pronoun()) + " falls") +
	  " to the ground bouncing and spinning dizzily.");
    }
    else
    {
	target(" grabs you by the arm and starts spinning you.\n" +
	  capitalize((string) this_player()->query_pronoun()) +
	  " attempts to spin you but loses control.", oblist);
	actor("You try to spin", oblist, " but suddenly fall down.");
	all2act(" tries to spin", oblist, " but slips.");
	all(" falls suddenly on " + this_player()->query_possessive() + " behind.");
    }

    return 1;
}


int
hthink(string str)
{
    object pipe = present(PIPE, TP);

    if (!pipe)
    {
	notify_fail("You are unable to think without your pipe.\n");
	return 0;
    }
    if (!pipe->IS_SMOKING)
    {
	notify_fail("You mind is too cluttered to think, maybe smoking your "+
	  "pipe might help you clear your mind in order to think more clearly.\n");
	return 0;
    }

    if (!str)
    {
	write("You take a deep, long puff on your pipe, thinking hard about your "+
	  "current situtation.\n");
	all(" takes a deep, long puff from "+HIS_HER(TP)+" pipe, while "+
	  "thinking hard about "+HIS_HER(TP)+" current situtation.");
	return 1;
    }
    if (strlen(str) > 35)
    {
	write("Your thought was so long you soon forget what "+
	  "it was about and you suck some smoke from your pipe trying to "+
	  "remember what it was.\n");
	all(" takes a long puff from "+HIS_HER(TP)+" pipe, as "+HE_SHE(TP)+
	  " tries to remember what "+HE_SHE(TP)+" was thinking about.");
	return 1;
    }
    write("You inhale deeply from your pipe, lost in thought about "+str+".\n");
    all(" inhales deeply on "+HIS_HER(TP)+" pipe, lost in thought "+
      "about "+str+".");
    return 1;
}

int
hthought(string str)
{
    object *oblist;
    object pipe = present(PIPE, TP);

    if (!pipe)
    {
	notify_fail("But you have no pipe here to chew on!\n");
	return 0;
    }
    if(!strlen(str))
    {
	write("You chew on your pipe, deep in thought.\n");
	all(" chews on "+HIS_HER(TP)+" pipe, deep in thought.");
	return 1;
    }
    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Chew on your pipe, thinking about what??\n");
	return 1;
    }

    actor("You chew on your pipe, deep in thought, thinking about "+str,oblist);
    target(" chews on "+HIS_HER(TP)+" pipe, deep in thought, thinking about"+str,oblist);
    all2act(" chews on "+HIS_HER(TP)+" pipe, deep in thought, thinking about"+str,oblist);
    return 1;
}

int
hstretch()
{
    write("You give each of your knuckles a good pop to ensure their "+
      "flexibility.\n");
    say(QCTNAME(TP) + " gives each of "+HIS_HER(TP)+" knuckles a good "+
      "crack in order to keep them flexible.\n");
    return 1;
}

string
calc_full(object player)
{
    string full;
    int tummy, max;
    max = TP->eat_max(); /* Gets the max eat for the player */

    if(( tummy / max ) < (1) || ( tummy / max ) > (8/10))
    {
	return "stuffed full";
    }

    if(( tummy / max ) < (8/10) || ( tummy / max ) > (6/10))
    {
	return "somewhat full";
    }

    if(( tummy / max ) < (6/10) || ( tummy / max ) > (4/10))
    {
	return "half-full";
    }

    if(( tummy / max ) < (4/10) || ( tummy / max ) > (2/10))
    {
	return "not totally empty";
    }

    if(( tummy / max ) < (2/10))
    {
	return "very empty";
    }

}

string
calc_str(object player)
{
    string str;
    int tummy, max;
    max = TP->eat_max(); /* Gets the max eat for the player */

    if(( tummy / max ) < (1) || ( tummy / max ) > (8/10))
    {
	return "thinking of how wonderful the next meal will be.";
    }

    if(( tummy / max ) < (8/10) || ( tummy / max ) > (6/10))
    {
	return "trying to fill up the corners.";
    }

    if(( tummy / max ) < (6/10) || ( tummy / max ) > (4/10))
    {
	return "asking for dessert.";
    }

    if(( tummy / max ) < (4/10) || ( tummy / max ) > (2/10))
    {
	return "looking around for a second serving.";
    }

    if(( tummy / max ) < (2/10))
    {
	return "wondering where the next meal will come from.";
    }

}

int
htummy()
{
    int tummy, max;
    string full, str;

    full = calc_full(TP);
    str = calc_str(TP);

    write("You rub your "+full+" tummy, "+ str+ "\n");
    say(QCTNAME(TP) + " rubs "+HIS_HER(TP)+" "+full+" tummy, "+str+"\n");

    return 1;
}


int
htwirl()
{
    object pipe = present(PIPE, TP);

    if (!pipe)
    {
	notify_fail("You have no pipe to twirl!\n");
	return 0;
    }
    if (pipe->IS_SMOKING)
    {
	notify_fail("Twirl a lit pipe?!?  You must be daft.\n");
	return 0;
    }
    write("You twirl your large brown pipe with great skill.\n");
    all(" twirls "+HIS_HER(TP)+" large brown pipe with great skill.");
    return 1;
}

int
hsit(string str)
{

    write("You take a seat, your feet swinging subconsciously as "+
      "your mind wanders.\n");
    all(" sits with legs swinging, "+HIS_HER(TP)+" thoughts "+
      "obviously elsewhere.");
    return 1;

}

int
hbelt(string str)
{

    write("With a sigh you grit your teeth against your "+
      "hunger, tighten your belt a notch and continue on.\n");
    all(" takes a moment to tighten "+HIS_HER(TP)+" belt, sighs, "+
      "and resolutely continues on.");
    return 1;

}

int
hsift(string str)
{

    object rock;

    write("You kneel down on the ground and sift your hand over "+
      "the ground in search of a good throwing rock.\n");
    all(" kneels down and runs "+HIS_HER(TP)+" hands over the ground, "+
      "looking for something.");

    rock = present("rock",ENV(TP));
    if (objectp(rock))
	TP->command("$get "+OB_NAME(rock));
    return 1;
}

int
hrock(string str)
{
    object rock;

    rock = present("rock",TP);
    if (!objectp(rock))
    {
	notify_fail("But you don't have a rock on you!\n");
	return 0;
    }

    write("You subconciously fuss with "+LANG_ASHORT(rock)+" in "+
      "your hand; feeling over its edges, flipping it over and "+
      "testing its weight.\n");
    all(" fiddles with "+LANG_ASHORT(rock)+" in "+HIS_HER(TP)+
      " hand, rubbing it with rough long fingers, tossing and "+
      "flipping it while in thought.");
    return 1;

}

int hhug(string str)
{
    object *oblist;
    string where;

    if(!strlen(str))  /* no string supplied */
    {
	write("Whom do you wish to hug?\n");
	return 1;
    }
    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Whom do you wish to hug?\n");
	return 1;
    }

    if (sizeof(oblist) > 1) 
    {
	write("You can only hug one person at a time.\n");
	return 1;
    }

    switch (oblist[0]->query_race())
    {
    case  "elf"   : case "human":
	where = "legs";
	break;
    case "dwarf": case "goblin":
	where = "waist";
	break;
    case  "gnome" : case "hobbit":
	where = "body";
	break;
    default:
	actor("You demonstrate your delight in seeing", oblist, " by "+
	  "embracing "+HIM_HER(oblist[0])+" firmly.");
	target(" shows "+HIS_HER(TP)+" delight to see you with a "+
	  "firm hug.", oblist);
	all2act(" darts forward with a cheery smile and hugs", oblist, ""+
	  " firmly.");
	return 1;
    }

    actor("You demonstrate your delight in seeing"
      , oblist, " by embracing "+HIM_HER(oblist[0])+" around the "+
      where +" in a firm hug.");
    target(" shows "+HIS_HER(TP)+" delight to see you by hugging you "+
      "tightly around your "+ where +".", oblist);
    all2act(" darts forward with a cheery smile and hugs", oblist, ""+
      " tightly around "+HIS_HER(oblist[0])+" "+ where +".");
    return 1;

}

int hrage(string str)

{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("Your building desperation and frustration boil over, and "+
	  "you launch yourself into combat renewed with an unexpected ferocity.\n");
	all(" displays a sudden turn of rage that causes you to pause, "+
	  "throwing "+HIM_HER(TP)+"self into combat full of fury.");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Vent your fury at whom?\n");
	return 1;
    }

    actor("Your building desperation and frustration boil over, and "+
      "you launch yourself at", oblist," with a ferocity unexpected.");
    target(" suddenly throws "+HIM_HER(TP)+"self at you with eyes "+
      "aflame in a grim and desperate rage.", oblist);
    all2act(" displays a sudden turn of rage that causes you to pause, "+
      "throwing "+HIM_HER(TP)+"self at ", oblist, " with desperate fury.");
    return 1;

}

int hstance(string str)
{
    object *oblist;
    string how;
    if(!strlen(str)) /* no string supplied */
    {
	write("You pull up your belt and plant your feet wide in "+
	  "preparation for some rough stuff.\n");
	all(" pulls up "+HIS_HER(TP)+" belt, setting "+HIS_HER(TP)+" feet "+
	  "apart in preparation for the worst.");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Stare down whom?\n");
	return 1;
    }

    switch(TP->query_stat(SS_RACE))
    {
    case 0..25:
	how = "some";
	break;
    case 26..50:
	how = "measureable";
	break;
    case 51..75:
	how = "considerable";
	break;
    case 76..100:
	how = "surprising";
	break;
    default:
	how = "legendary";
	break;
    }

    actor("You pull up your belt and plant your feet wide, locking "+
      "your gaze onto", oblist,".");
    target(" pulls up "+HIS_HER(TP)+" belt, settles into a fighting stance, "+
      "and stares you right in the eyes.\nApparently you are messing with a "+
      "hobbit of "+ how +" toughness.", oblist);
    all2act(" pulls up his belt and settles into a wide fighting stance, "+
      "staring down", oblist," with a look of total defiance.\n"+
      "Apparently "+ QCTNAME(TP) +" is a hobbit of "+ how +" toughness.");
    return 1;
}

int
hpride(string str)
{
    write("Your cheeks redden and your chest swells with pride!\n");
    all("'s cheeks flush and "+ HIS_HER(TP) +" chest puffs out with "+
        "pride.\n");
    return 1;
}

int
hwish()
{
    write("You wish for the comforts of your nice, warm, hobbit hole.\n");
    say(QCTNAME(TP) + " wishes for the comforts of "+HIS_HER(TP)+
        " nice, warm, hobbit hole.\n");
    return 1;

}