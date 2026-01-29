 /* This file is /d/Shire/guild/noldor/noldor_soul.c

 Based on the hobbit soul file
 Racial speak and idea code borrowed from travellers
 -- Finwe, June 2001

 Palmer, Jan 2003
 Added ability to summon and dismiss Noldor horses.
 nosummon/nograze

 Arandir, Dec 2003
 Added a small routine for private speech.

 Finwe, January 2005
 Added ability to hide/reveal title, Based on Merc code

 Cotillion, January 2020
 Fixed cloning of horse
 */

#pragma save_binary
//#pragma strict_types

inherit "/cmd/std/command_driver";
#include <macros.h>
#include <formulas.h>
#include <language.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>
#include <files.h>
#include <time.h>
#include <std.h>
#include <wa_types.h>
#include <options.h>
#include <adverbs.h>
#include <cmdparse.h>
#include <options.h>


#include "/d/Shire/sys/defs.h"
#include "noldor.h"
#include "nlist.h"
#include "nidea.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define MORE(x)   this_player()->more(read_file(x,2))

int alarm_id;
void sing_song(object player, int stage);

string
get_soul_id()
{
    return "Noldor elves";
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
//      "help"            : "do_help",
      "nolist"          : "list_active_noldor",
      "noldorlist"      : "list_active_noldor",
      "noacknowledge"   : "nacknowledge",
      "noac"            : "nacknowledge",
      "nobow"           : "nbow",
      "nobo"            : "nbow",
      "nobow2"          : "nbow2",
      "nob2"            : "nbow2",
      "nocall"          : "ncall",
      "noca"            : "ncall",
      "noclean"         : "nclean",
      "nocl"            : "nclean",
      "nocontemplate"   : "ncontemplate",
      "noco"            : "ncontemplate",
      "nodismiss"       : "ndismiss",
      "nodi"            : "ndismiss",
      "nofarewell"      : "nfarewell",
      "nofa"            : "nfarewell",
      "nofight"         : "nfight",
      "nofi"            : "nfight",
      "noignore"        : "nignore",
      "noig"            : "nignore",
      "nograze"         : "ngraze",
      "nogr"            : "ngraze",
      "nohymn"          : "nhymn",
      "nohy"            : "nhymn",
      "nopolish"        : "npolish",
      "nopo"            : "npolish",
      "noremind"        : "nremind",
      "nore"            : "nremind",
      "nooath"          : "noath",
      "nooa"            : "noath",
      "nopause"         : "npause",
      "nopa"            : "npause",
      "nosad"           : "ntear",
      "nosa"            : "ntear",
      "nosigh"          : "nsigh",
      "nosi"            : "nsigh",
      "nospeak"         : "nspeak",
      "nosp"            : "nspeak",
      "nostep"          : "nstep",
      "nost"            : "nstep",
      "nost"            : "nstep",
      "nosummon"        : "nsummon",
      "nosu"            : "nsummon",
      "notale"          : "ntale",
      "nota"            : "ntale",
      "notitle"         : "ntitle",
      "noti"            : "ntitle",
      "nowelcome"       : "nwelcome",
      "nowe"            : "nwelcome",
      "noidea"          : "noidea",
      "noid"            : "noidea",
      "nolist"          : "list_active_noldor",
      "noli"            : "list_active_noldor",
    ]);

}

/*
 * Disabled Jan 6 2017
 */
/*
int
do_help(string str)
{
    setuid(); seteuid(getuid());
    switch (str)
    {
    case "noldor":
        MORE(NOLDOR_HELP + "general");
        TP->catch_tell("Please report any problems you may encounter "+
        "with the "+NOLDOR_RACE_GUILD_NAME+" to "+
        COMPOSITE_WORDS(map(NOLDOR_RACE_GUILD_MASTER, capitalize)) + ".\n");
        break;

    case "noldor general":
        MORE(NOLDOR_HELP + "general");
        break;

    case "noldor emotes":
    case "noldor emotions":
        MORE(NOLDOR_HELP + "emotes");
        break;

    case "noldor news":
        MORE(NOLDOR_HELP + "news");
        break;

    case "noldor horses":
    case "noldor steeds":
        MORE(NOLDOR_HELP + "horses");
        break;

    default:
    return 0;
    }
    return 1;
}
*/


/* * * * * * * * * * *
 * emotes
 * * * * * * * * * * */

/*
* Used to create and move horse to player after delay in nsummon
*/

public void
make_horse(string *saved_data)
{
    object horse;

    setuid();
    seteuid(getuid());

    horse = clone_object("/d/Shire/rivendell/steeds/horse");
    horse->move_living("M", ENV(TP));
    horse->add_desc(saved_data);
    tell_room(ENV(horse), "A " + horse->short() + " comes galloping in.\n");
    return;
}

/*
* Used to move horse to player after delay in nsummon
*/

public void
bring_horse(object horse)
{
    // Make sure not to move if horse has a driver or leader
    if (objectp(horse->query_leader()))
    {
        return;
    }

    if (objectp(horse->query_driver()))
    {
        return;
    }


    horse->move_living("off", ENV(TP));
    return;
}


/*
 * nsummon - summon your horse
 */


public int
nsummon()
{
    object horse;
    mapping steed_owners = ([ ]);
    string horse_name, player_name, *props, *saved_data;
    int test;

    player_name = QCTNAME(TP);

    // We need to switch euid's in order to access map
    setuid();
    seteuid(getuid());
    steed_owners = restore_map("/d/Shire/rivendell/steeds/steed_owners");

    if (!steed_owners[TP->query_real_name()])
    {
        write("You don't have a horse. Go visit the stable master.\n");
        return 1;
    }

    // Get room properties and do checks to be sure horse is allowed here.
    props = ENV(TP)->query_props();

    // Cheesy test to see if ship is at sea. Help me please.
    // if (ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
    test = member_array("_room_m_no_firewood", props);
    if (test != -1)
    {
        write("Your horse can swim, but not quite that good.\n");
        return 1;
    }

    test = member_array("_room_i_no_allow_steed", props);
    if (test != -1)
    {
        write("Your horse isn't allowed here.\n");
        return 1;
    }

    test = member_array("_room_i_inside", props);
    if (test != -1)
    {
        write("Your horse can't come inside this room. " +
            "Try summoning from outdoors.\n");
        return 1;
    }

    saved_data = steed_owners[TP->query_real_name()];
    horse_name = saved_data[3];
    write("You whisper a few words into the air, summoning your horse " +
    capitalize(horse_name) + ".\n");
    say(player_name + " whispers a few words into the air.\n");

    if (find_living(lower_case(horse_name)))
    {
        horse = find_living(lower_case(horse_name));
        if (ENV(TP) == ENV(horse))
        {
            horse->command("eyebrow");
            return 1;
        }
        set_alarm(8.0, 0.0, &bring_horse(horse));
        return 1;
    }
    set_alarm(8.0, 0.0, &make_horse(saved_data));
    return 1;
}



/*
 * ngraze - send your horse off to graze/home
 */

public int
ngraze()
{
    object horse, saddlebag;
    string *saved_data;
    mapping steed_owners = ([ ]);
    string horse_name, player_name;

    player_name = QCTNAME(TP);
    // Need to switch euid to be able to access mapping saved on disk, 
    // then switch back to current euid.
    setuid();
    seteuid(getuid());
    steed_owners = restore_map("/d/Shire/rivendell/steeds/steed_owners");
    seteuid(getuid(this_object()));

    if (!steed_owners[TP->query_real_name()])
    {
        write("You don't have a horse. Go visit the stable master.\n");
        return 1;
    }
    saved_data = steed_owners[TP->query_real_name()];
    horse_name = saved_data[3];

    if (find_living(lower_case(horse_name)))
    {
        horse = find_living(lower_case(horse_name));

        // Make sure nobody is riding it when we send it home.
        if (sizeof(horse->query_riders()) > 0)
        {
            write ("You must dismount before sending your steed to graze.\n");
            return 1;
        }

        // Horse must be in the same room
        if (environment(horse) != environment(TP))
        {
            write ("Your horse must be here for you to send it to graze.\n");
            return 1;
        }

        // Don't let them send horse off with saddlebag. (virtual drop rooms)
        saddlebag = present("saddlebag", horse);
        if (saddlebag)
        {
            write("You'd better remove your saddlebag from your horse first.\n");
            return 1;
        }

        write("You whisper a few words into " + capitalize(horse_name) +
            "'s ear.\n");
        say(player_name + " whispers a few words into " + HIS_HER(TP) +
            " horses ear.\n");

        write("The " + horse->short() + " trots off to graze. Remember, if " + 
            HE_SHE(TP) + " is not summoned, " + HE_SHE(TP) + " will go home.\n");
        say("The " + horse->short() + " trots off.\n");
        horse->remove_object();
        return 1;
    }

    write("Your horse isn't here. " + CAP(HIS_HER(TP)) + " may be out grazing " +
        "or has gone home. do <nosummon> to summon your horse.\n");
    return 1;
}


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
    all(" rejoices to everyone present. " + CAP(HE_SHE(TP)) +
        " embraces and fondly welcomes you and everyone as " +
        "close friends saying, 'Elen sila lumenn omentielvo.'");
    return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
    write("Acknowledge who?\n");
    return 1;
    }

    actor("You tilt your head slightly and acknowldge the presence of", oblist);
    target(" tilts " + HIS_HER(TP) + " head slightly, acknowledging " +
        "your presence.", oblist);
    all2act(" tilts " +HIS_HER(TP) + " head slightly at",oblist,
         ", acknowledging their presence.");
    return 1;
}


/*
 * nbow - bow before someone
 */
int
nbow(string str)
{

    object *oblist;
    if(!strlen(str) || str=="all" || str=="to all") /* no string supplied */
    {
    write("You stand tall, then bow slightly before everyone, " +
        "locking their gazes with yours until they turn away.\n");
    all(" stands tall and bows " + HIS_HER(TP) +
        " head slightly before you. " + CAP(HIS_HER(TP))+ " gaze " +
        "meets yours, holding you until you look away.");
    return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist)|| str=="all")
    {
    write("Bow to who?\n");
    return 1;
    }

    actor("You stand tall and bow slightly before",oblist,".");
    target(" stands tall and bows slightly before you.", oblist);
    all2act(" stands tall and bows slightly before", oblist,".");
    return 1;

}

/*
 * nbow2 - bow before someone, less intimidating version
 */
int
nbow2(string str)
{

    object *oblist;
    if(!strlen(str) || str=="all" || str=="to all") /* no string supplied */
    {
    write("You bow before everyone, captivating them with your charm " +
        "and grace.\n");
    all(" bows before you and everyone else nearby, in a graceful, captivating manner.");
    return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist)|| str=="all")
    {
    write("Bow to who?\n");
    return 1;
    }

    actor("You bow before",oblist,", in a graceful, captivating manner.");
    target(" bows before you, in a graceful, captivating manner.", oblist);
    all2act(" bows before", oblist,", in a graceful, captivating manner.");
    return 1;

}


/*
 * ncall - call upon a valar for assistance
 */
int
ncall(string str)
{
    string valar;

    switch (str)
    {
    case "yavanna": case "elbereth":
        valar = "to " + CAP(str) + ", asking her to nourish the " +
            "earth and renew it.";
        break;
    case "tulkas":
        valar = "to " + CAP(str) + " to strengthen and go " +
            "before you in your upcoming battle.";
        break;
    case "aule":
        valar = "to " + CAP(str) + ", thanking him for knowledge and understanding.";
        break;
    case "manwe":
        valar = "to " + CAP(str) + " asking for compassion and wisdom.";
        break;
    default:
        valar = "to the Valar for guidance and support.";
        break;

    }
    write("You stop for a moment and look to the west. Next you " +
        "lift up your voice and sing " + valar + " Your voice calms " +
        "and you return to your natural state.\n");
    say(QCTNAME(TP) + " stops and turns to the west and begins " +
        "to sing a beautiful song. " +
        CAP(HE_SHE(TP)) + " begins to shine. The song ends and " +
        HE_SHE(TP) + " turns back to you, with a smile on " +
        HIS_HER(TP) + " face.\n");
    return 1;
}


int
ncontemplate(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
    write("You pause for a moment, tapping your chin lightly with a " +
        "finger in quiet contemplation of something important.\n");
    all(" pauses for a moment and taps " + HIS_HER(TP) + " chin lightly " +
        "with a finger in quiet contemplation of something important.");
    return 1;
    }
}


/*
 * dismiss - command something to leave your presence
 */
int
ndismiss(string str)
{
    object *oblist;
    if(!strlen(str) && !sizeof(oblist)) /* no string supplied */
    {
    write("You see no one to command to leave.\n");
    return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
    write("Command who to leave?\n");
    return 1;
    }

    actor("You raise your hand to", oblist, " and with authority " +
        "declare: 'Go! Go back to your Master and the land from " +
        "whence you came!'");
    target(" plants " +HIS_HER(TP) + " feet firmly in the ground " +
        "and stretches forth " + HIS_HER(TP)+ " hand towards you. " +
        "In a commanding voice " + HE_SHE(TP) + " orders, 'Go! Go " +
        "back to your Master and the land from whence you " +
        "came!'", oblist);
    all2act(" plants " +HIS_HER(TP) + " feet firmly in the ground " +
        "and stretches forth " + HIS_HER(TP)+ " hand towards",
        oblist,". In a commanding voice " +HE_SHE(TP) +
        " orders, 'Go! Go back to your Master and the land from " +
        "whence you came!'");
    return 1;
}


/*
 * nclean - clean and polish circlet
 */

int
nclean()
{
    write("You clean and polish your circlet until it shines " +
        "brightly.\n");
    say(QCTNAME(TP) + " cleans and polishes "+HIS_HER(TP)+
        " circlet. It shines brightly and almost blinds you.\n");
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
        case 1: greet = "'May you be protected in your journeys.'";
            break;
        case 2: greet = "'May the road rise up to meet you and " +
            "may your travels be pleasant.'";
            break;
        case 3: greet = "'Wherever you travel, may you never " +
            "tire on your journey.'";
            break;
        case 4: greet = "'May your burdens be light and your travels be wonderous.'";
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
 * nfight - fight something with renewed strength
 */
int nfight(string str)
{
    object *oblist;
    if(!strlen(str) && !sizeof(oblist) ) /* no string supplied */
    {
        write("Fight who?\n");

    return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
    write("Fight who?\n");
    return 1;
    }
    actor("You shout, 'Gilthoniel, A Elbereth!', and fight",
        oblist, " with renewed strength.");
    target(" shouts, 'Gilthoniel, A Elbereth!', and fights you " +
        "with renewed strength!", oblist);
    all2act(" shouts 'Gilthoniel, A Elbereth!', and fights ",
        oblist, " with renewed strength.");
    return 1;
}

/*
 * nhymn - Sings famous elbereth hymn
 */
 int
 nhymn(string str)
 {
    if IS_SINGING
    {
    NF("But you are already in a middle of a song.\n");
    return 0;
    }
    START_SINGING;
    write("You prepare to sing a holy song.\n\n");
    say(QCTNAME(TP)+ " begins to sing in a clear voice.\n\n",TP);
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

    actor("You ignore", oblist);
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

/*
 * npolish - polishes beryl in circlet
 */
int
npolish()
{
    write("You polish the gem in your circlet. It gleams and " +
        "twinkles in the light.\n");
    say(QCTNAME(TP) + " polishes a gem in "+HIS_HER(TP)+
        " circlet. It gleams and twinkles in the light.\n");
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

/*
 * nspeak - think out loud to your kindred
 */
int
nspeak(string str)
{
    object oActor = this_player ();
    int    iListener;
    object oListener;
    object *aoListeners;

    notify_fail ("What is it you wish to speak?\n");

    if (!strlen (str)) return (0);

    write ("You pause for a moment and think: " + str + "\n");

    aoListeners = FILTER_LIVE (all_inventory (environment (oActor)) - ({ oActor }));
    for (iListener = 0 ; iListener < sizeof (aoListeners) ; iListener ++)
    {
        oListener = aoListeners [iListener];
        if (IS_MEMBER (oListener))
        {
            oListener->catch_tell (oActor->query_The_name (oListener) + " pauses " +
                                   "and thinks: " + str + "\n");
        }
    }

    return (1);
}


/*
 * nsigh
 */
int
nsigh(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
    write("You sigh sadly, recalling the many atrocities you have " +
        "seen committed to Arda.\n");
    all(" sighs sadly, recalling the many atrocities "+HE_SHE(TP)+
         " has seen committed to Arda.");
    return 1;
    }
}


/*
 * nstep - steps back and evaluates the situation
 */
int nstep()
{
    write("You step back cautiously and evaluate the situation.\n");
    say(QCTNAME(TP) + " steps back cautiously, evaluating the " +
        "situation.\n");
    return 1;
}



/*
 * ntale - tell a tale of history past
 */
int
ntale(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
    write("You tell a tale about the history of the Noldor.\n");
    all(" tells you a tale about ancient Noldor history.");
    return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
    write("There is no one present to talk to.\n");
    return 1;
    }

    actor("You put your hand on", oblist, "'s shoulder and tell " +
        HIM_HER(TP)+ " a sad tale about ancient Noldor history.");
    target(" places" +HIS_HER(TP) + " his hand on your shoulder " +
        "and tells you a sad tale about ancient Noldor history.",
        oblist);
    all2act(" places" +HIS_HER(TP) + " his hand on ", oblist,
    "'s shoulder and tells " + HIM_HER(TP) + " a sad tale about " +
    "ancient Noldor history.");
    return 1;
}


int
ntear(string str)
{
    object *oblist;

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

    write("Your eyes fill with tears at the sad news of "+CAP(str)+".\n");
//  target(" eyes fill with tears at the sad news about you.",oblist);
    say(QCTNAME(TP)+ "'s eyes fill with tears at the sad news of "+
        CAP(str)+".\n");

    return 1;

}

public int
ntitle(string str)
{
/*
    string title;
    int setting;



    if( str=="off" || str == "Off" || str == "OFF")        
    {
        if((TP->test_bit("Shire", 4,0)))
        {
            TP->query_guild_title_race() + "";
            TP->clear_bit(4,0); 
            write("You will not introduce yourself as a Noldor.\n");
        }
            return 1;
        
    }

    if( str=="on" || str == "On" || str == "ON")        
        {
            if((TP->test_bit("Shire", 4,0)))
            {
                TP->query_guild_title_race() + NOLDOR_RACE_GUILD_TITLE;
                TP->set_bit(4,0);
                write("You will now introduce yourself as a Noldor.\n");

            }
            return 1;
        }
    }
    write("Turn your title off or on?\n");
    return 0;

*/
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
    write("There is no one to welcome.\n");
    return 1;
    }

    actor("You warmly embrace and welcome", oblist,", saying 'Elen sila lumenn omentilmo.'");
    target(" rejoices to meet you. " + CAP(HE_SHE(TP)) +
        " embraces you fondly and welcomes you as a close friend and says, " +
        "'Elen sila lumenn omentilmo.'", oblist);
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
    write("\nYou begin singing: A Elbereth Gilthoniel,\n");
    say(QCTNAME(TP)+ " starts singing: A Elbereth Gilthoniel,\n",TP);
    time = 1.5;
    break;
    case 2:
    write("You sing: silivren penna miriel\n");
    say(QCTNAME(TP)+" sings: silivren penna miriel\n",TP);
    time = 1.5;
    break;
    case 3:
    write("You sing: o menel aglar elenath!\n");
    say(QCTNAME(TP)+" sings: o menel aglar elenath!\n",TP);
    time = 1.5;
    break;
    case 4:
    write("You sing: Na-chaered palan-diriel\n");
    say(QCTNAME(TP)+" sings: Na-chaered palan-diriel\n",TP);
    time = 1.5;
    break;
    case 5:
    write("You sing: o galadhremmin ennorath,\n");
    say(QCTNAME(TP)+" sings: o galadhremmin ennorath,\n",TP);
    time = 1.5;
    break;
    case 6:
    write("You sing: Fanuilos, le linnathon\n");
    say(QCTNAME(TP)+" sings: Fanuilos, le linnathon\n",TP);
    time = 1.5;
    break;
    case 7:
    write("You sing: nef aear, si nef aearon!\n\n");
    say(QCTNAME(TP)+" sings: nef aear, si nef aearon!\n",TP);
    time = 1.5;
    break;
    default:
    write("\nYou stop singing and feel refreshed.\n\n");
    say("\n"+QCTNAME(TP)+" stops singing and looks refreshed\n\n",TP);
    STOP_SINGING;
    return;
    }
    set_alarm(time, 0.0, &sing_song(player, ++stage));
}

