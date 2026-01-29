/* This file is /d/Shire/noldor/noldor_soul.c 
 *
 * The soul for the Noldor Elven Racial guild.
 * Ruthlessly borrowed from the Hobbit Racial guild 
 * which was in turn ruthlessly stolen from Gondor,
 * with permission, of course.
 * 
 * Done by Finwe, May 1999
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";
#include <macros.h>
#include <formulas.h>
#include "noldor.h"
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/sys/defs.h"
// #include "hsing.h"
#include "nlist.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define GLOW  "_noldor_race_guild_glow_"
#define MORE(x)   this_player()->more(read_file(x,2))

int alarm_id;
void sing_song(object player, int stage);

string
get_soul_id()
{
    return "Noldor Elves";
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
      "help"          : "do_help",
      "nacknowledge"   : "nacknowledge",
      "nac"            : "nacknowledge",
      "nattack"        : "nattack",
      "nat"            : "nattack",
      "ncast"          : "ncast",
      "nca"            : "ncast",
      "nfarewell"      : "nfarewell",
      "nfa"            : "nfarewell",
	  "nignore"        : "nignore",
	  "nig"            : "nignore",
      "nhymn"          : "nhymn",
      "nhy"            : "nhymn",
      "nremind"        : "nremind",
      "nre"            : "nremind", 
      "noath"          : "noath",
      "noa"            : "noath", 
      "npause"         : "npause",
      "npa"            : "npause",
      "ntear"          : "ntear",
      "nte"            : "ntear",
      "nwelcome"       : "nwelcome",
      "nwe"            : "nwelcome",
      "nlist"          : "list_active_noldor",
      "nli"            : "list_active_noldor",
      "noldorlist"     : "list_active_noldor",
    ]);

    /* The above are in the form: command : function */

}

int
do_help(string str)
{
    setuid(); seteuid(getuid());
    if(str == "noldor")
    {
	MORE(NOLDOR_HELP+"general");
	write("And please report any problems you may encounter "+
	  "with the noldor guild to "+
	  COMPOSITE_WORDS(map(NOLDOR_RACE_GUILD_MASTER, capitalize)) + ".\n");
	return 1;
    }

    if(str == "noldor emotions")
    {
	MORE(NOLDOR_HELP+"emotes");
	return 1;
    }
    if (str == "noldor news")
    {
	MORE(NOLDOR_NEWS);
	return 1;
    }
    return 0;
}


/* * * * * * * * * * *
 * emotes
 * * * * * * * * * * */

/*
 * acknowledge - acknowledge another's presence
 */

int
nacknowledge(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("You tilt your head slightly, acknowledging everyone's " +
         "presence.\n");
	all(" tilts " + HIS_HER(TP) + " head slightly, acknowledging " +
         "your presence.");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Acknowledge who?\n");
	return 1;
    }

    actor("You tilt your head slightly and acknowldge the presence of ", oblist); 
    target(" tilts " + HIS_HER(TP) + " head slightly, acknowledging " +
        "your presence.", oblist);
    all2act(" tilts " +HIS_HER(TP) + " head slightly at ",oblist,
         ", acknowledging " + HIS_HER(TP) + " presence.");
    return 1;
}

/*
 * attack - attack something with renewed strength
 */
int
nattack(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("You shout, 'Gilthoniel, A Elbereth!', and attack with " +
        "new strength.\n");
	all(" shouts, 'Gilthoniel, A Elbereth!', and attacks you!\n");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Attack who?\n");
	return 1;
    }

    actor("You shout, 'Gilthoniel, A Elbereth!', and attack", 
        oblist, " with new strength."); 
    target("shouts, 'Gilthoniel, A Elbereth!', and attacks you!", oblist);
    all2act(" shouts 'Gilthoniel, A Elbereth!', and attacks ", oblist, ".");
    return 1;
}

/*
 * cast - command something to leave your presence
 */
int
ncast(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("Command who to leave?\n");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Command who to leave?\n");
	return 1;
    }

    actor("You command", oblist, " to return to Mordor."); 
    target(" plants " +HIS_HER(TP) + " feet firmly in the ground " +
	    "and stretches forth " + HIS_HER(TP)+ " hand towards you. " +
        "In a commanding voice " + HE_SHE(TP) + " says, 'Go! Go " +
        "back to your Master and the land from whence you " +
        "come!'", oblist);
    all2act(" plants " +HIS_HER(TP) + " feet firmly in the ground " +
	    "and stretches forth " + HIS_HER(TP)+ " hand towards", 
        oblist,". In a commanding voice " +HE_SHE(TP) + 
        " says, 'Go! Go back to your Master and the land from " +
        "whence you come!'");
    return 1;
}


/*
 * farewell - bid farewell to someone
 */
int
nfarewell(string str)
{
    object *oblist;
    string greet;
    int ran;

    ran = random(5);

    switch(ran)
        {
        case 0: 
            greet = "'May the light of Elbereth guide you.'";
            break;
        case 1: greet = "'May the Valar protect you in your journeys.'";
            break;
        case 2: greet = "'May the road rise up to meet you and may your travels be pleasent.'";
            break;
        case 3: greet = "'Where ever you travel, may you never tire on your journey.'";
            break;
        default: greet = "'May your burdens be light and your travels be wonderous.'";
            break;
        }  

     
    if(!strlen(str)) /* no string supplied */
    {
    
	write("You bid everyone farewell, saying, " + greet + "\n");
	all(" bids you farewell, saying, " + greet + "\n");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Bid farewell to who?\n");
	return 1;
    }

    actor("You bid farewell to",oblist," saying " + greet); 
    target(" bids you farewell, saying, " +greet, oblist);
    all2act(" bids ",oblist," farewell, saying, " + greet);
    return 1;
}


/*
 * nhymn - Sings famous elbereth hymn
 */
 int
 nhymn(string str)
 {
    if (TP->query_prop("_live_i_am_singing"))
    {
	NF("But you are already in a middle of a song.\n");
	return 0;
    }
    TP->add_prop("_live_i_am_singing", 1);
    write("You prepare to sing a holy song.\n");
    say(QCTNAME(TP)+ " begins to sing in a clear voice.",TP);
    set_alarm(5.0,0.0, &sing_song(TP, 1));
    return 1;
}


int
nignore(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("You turn your back and ignore everyone.\n");
	all(" turns " + HIS_HER(TP) + " his back and ignores you!");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Ignore who?\n");
	return 1;
    }

    actor("You ignore ", oblist); 
    target(" turns " + HIS_HER(TP) + " back and ignores you.", oblist);
    all2act(" turns " + HIS_HER(TP) + " and and ignores ",oblist, ".");
    return 1;
}


int
noath(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("You valiantly renew your oath to never be deceived " +
         "by the Shadow again!\n");
	all(" valiantly renews " + HIS_HER(TP) + " oath to never be " +
         "deceived by the Shadow again!");
	return 1;
    }
}


int
npause(string str)
{
    write("You pause and rest your mind, admiring the beauty of " + 
        "Arda. You feel refreshed and stronger.\n");
    say(QCTNAME(TP) + " pauses briefly admiring something nearby. " +
       "After a few moments, " + HE_SHE(TP) + " looks refreshed.\n");
    return 1;
}


int
nremind(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("You remind everyone you are one of the First-born.\n");
	all(" reminds you " + HE_SHE(TP) + " is one of the First-born.");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Remind who?\n");
	return 1;
    }

    actor("You remind", oblist, " you are one of the First-born."); 
    target(" reminds you " + HE_SHE(TP) + " is one of the First-born.", oblist);
    all2act(" reminds", oblist, " that " +HE_SHE(TP) + 
        " is one of the First-born.");
    return 1;
}



int
ntear(string str)
{
    if(!strlen(str))
    {
	write("Your eyes suddenly fill with tears.\n");
	say(QCTNAME(TP) + "'s eyes suddenly fill with tears.\n");
	return 1;
    }
    if(strlen(str) > 35)
    {
	write("That news is more than you can bear!\n");
	return 1;
    }

    write("Your eyes fill with tears at the sad news of "+str+".\n");
    say(QCTNAME(TP)+ "'s eyes fill with tears at the sad news of "+str+".\n");
    return 1;

}


int
nwelcome(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("Welcome who?\n");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Welcome who?\n");
	return 1;
    }

    actor("You warmly embrace and welcome", oblist,", saying 'Elen sila lumenn omentilmo.'");
    target(" rejoices to meet you. " + CAP(HE_SHE(TP)) +
        " embraces you fondly and welcomes you as a close friend and says, " + 
        "saying 'Elen sila lumenn omentilmo.'", oblist);
    all2act(" warmly embraces and welcomes", oblist, ", saying " +
        "'Elen sila lumenn omentilmo.'");
    return 1;
}

/* * * * * * * * * * * * * * * * 
 * Miscellaneous routines associated with emotes
 * * * * * * * * * * * * * * * * 

/*
 * sing_song - sings elbereth hymn
 * shamelessly taken from heralds
 */

void
sing_song(object player, int stage)
{
    float time;

    set_this_player(player);
    switch (stage)
    {
    case 1:
	write("A Elbereth Gilthoniel,\n");
	say(QCTNAME(TP)+ "A Elbereth Gilthoniel,\n",TP);
	time = 1.5;
	break;
    case 2:
	write("silivren penna miriel\n");
	say("silivren penna miriel",TP);
	time = 1.5;
	break;
    case 3:
	write("o menel aglar elenath!\n");
	say("o menel aglar elenath!",TP);
	time = 1.5;
	break;
    case 4:
	write("Na-chaered palan-díriel\n");
	say("Na-chaered palan-díriel",TP);
	time = 1.5;
	break;
    case 5:
	write("o galadhremmin ennorath,\n");
	say("o galadhremmin ennorath,",TP);
	time = 1.5;
	break;
    case 6:
	write("Fanuilos, le linnathon\n");
	say("Fanuilos, le linnathon",TP);
	time = 1.5;
	break;
    case 7:
	write("nef aear, si nef aearon!\n");
	say("nef aear, si nef aearon!",TP);
	time = 1.5;
	break;
    default:
	write("You stop sing and feel refreshed.\n");
	say(QCTNAME(TP)+" stops singing and looks refreshed\n",TP);
	TP->remove_prop("_live_i_am_singing");
	return;
    }
    set_alarm(time, 0.0, &sing_song(player, ++stage));
}
