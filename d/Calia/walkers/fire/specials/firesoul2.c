
 /* Firewalkers soul   */
 /* August 28th, 1997  */
 /* Jaacar             */

#pragma strict_types
#pragma save_binary

inherit "/cmd/std/command_driver";

#include <stdproperties.h>
#include <macros.h>
#include <adverbs.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <options.h>
#include <filter_funs.h>
#include "defs.h"
#include FIRE_HEADER
#include COUNCIL_HEADER
#include WOR_LANGUAGE

#ifndef MY
#define MY TP->query_possessive()
#endif
#define HIM TP->query_objective()
#ifndef HE
#define HE TP->query_pronoun()
#endif
#define SOULDESC(x) (TP->add_prop(LIVE_S_SOULEXTRA, x))

string *fire_apprentices = ({});
mapping mentors = ([ ]);

string
get_soul_id()
{
    seteuid(getuid());
    return "Firewalkers of Thalassia";
}

string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

int
query_cmd_soul()
{
    seteuid(getuid());
    return 1;
}

int
is_fire(object living)
{
    return living->query_guild_name_occ() == GUILD_NAME;
}

int
is_worship(object living)
{
    return living->query_guild_name_lay() == WORSHIPPER_GUILD;
}

int
is_walker(object living)
{
    return living->query_skill(SS_WALKER_CHOSEN);
}

string
group_desc(object looking, object *group, int cap)
{
    string *qdesc, qd;

    if (member_array(looking, group) > -1) {
        group -= ({looking});
        if (cap)
            qdesc = ({"You"});
        else
            qdesc = ({"you"});
        if (sizeof(group))
            qdesc += map(group, &->query_the_name(looking));
    }
    else {
        if (cap)
            qdesc = ({group[0]->query_The_name(looking) });
        else
            qdesc = ({group[0]->query_the_name(looking) });
        group -= ({group[0]});
        if (sizeof(group))
            qdesc += map(group, &->query_the_name(looking));
    }

    return COMPOSITE_WORDS(qdesc); 
} 

int
cmd_list()
{
    write("You can use the following emotes:\n" +
    "fbless <player(s)>            - bless <player(s)> in the name of Pyros.\n"+
    "fcough (<how>) (<player(s)>)  - cough (<how>) (at <player(s)>).\n"+
    "feyes (<how>) (<player(s)>)   - glare (at player(s)) angrily.\n" +
    "ffare(well) <player(s)>       - bid farewell to <player(s)>.\n"+
    "ffoot                         - discreetly change your footing.\n"+
    "fgaze (<how>) (<player(s)>)   - gaze (<how>) (at <player(s)>).\n"+
    "fgrin (<how>) (<player(s)>)   - grin (<how>) (at <player(s)>).\n"+
    "fhail <player(s)>             - hail <player(s)> in an ancient sign\n"+
    "                                of greetings.\n"+
    "fhug (<how>) <player(s)>      - hug <player(s)> (<how>).\n" +
    "fknee                         - call to Lord Pyros for power.\n" +
    "flaugh (<how>) (<players(s)>) - laugh (<how>) (at <player(s)>).\n" +
    "fplay                         - play with fire.\n" +
    "fscream (<how>) (<player>)    - scream (<how>) (at <player>).\n"+
    "fshake <player(s)>            - shake <player(s)> hand heatedly.\n" +
    "fsmile (<how>) (<player(s)>)  - smile (<how>) (at <player(s)>).\n" +
    "fsnap (<how>)                 - snap your fingers (<how>).\n" +
    "fs(peak)                      - speak to another Walker in the\n"+
    "                                Ancient Elemental Tongue.\n"+
    "fspit (<player(s)>)           - spit fire (at <player(s)>).\n" +
    "help fire(walker)             - a list of all help fire(walker) options.\n"+
    "wch(ant) <message>            - chant <message> in ancient mantras\n"+
    "                                (NOTE: This language is understood\n"+
    "                                       by the Elemental Worshippers\n"+
    "                                       as well as Walkers.\n" +
    "\n"+
    "\n"+
    "You can also use the following commands:\n"+
    "fwho                          - get a list of Firewalkers in the Realms.\n"+
    "walkers                       - get a list of Walkers in the Realms.\n"+
    "worshippers                   - get a list of Worshippers in the Realms.\n"+
    "fchoose <player>              - select <player> to be your apprentice.\n" +
    "spells                        - get a list of your current spells.\n"+
    "\n");
    return 1;
}

int
fbless(string str)
{
    object *oblist;

    if (!str || str == "")
    {
        NF("Bless whom in the name of Pyros?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NF("Bless whom in the name of Pyros?\n");
        return 0;
    }

    actor("You bless",oblist," saying `May you kindle Fire "+
        "and never be burned by it.'");
    all2act(" blesses",oblist," and says `May you kindle Fire "+
        "and never be burned by it.'");
    target(" blesses you saying `May you kindle Fire and never "+
        "be burned by it.'",oblist);
    return 1;
}

int
fchoose(string str)
{
    object *who;
    object chosen;
    string my_name, apprentice;

    setuid();
    seteuid(getuid());
    COUNCIL_CODE->load_me();
    restore_object(COUNCIL);

    if (!(COUNCIL_CODE->is_fire_elder(TP->query_real_name())))
    {
        NF("You are not permitted to accept apprentices until you "+
            "have reached the Elder status.\n");
        return 0;
    }

    if (!str || str == "")
    {
        NF("Choose who?\n");
        return 0;
    }

    who = parse_this(str, " %l");

    if (!sizeof(who))
        return 0;

    if (!who)
        return 0;

    if (sizeof(who)>1)
    {
        NF("You can't choose more than one person at a time!\n");
        return 0;
    }

    if (is_fire(who[0]))
    {
        NF("That person is already a Firewalker!\n");
        return 0;
    }

    if (!is_worship(who[0]))
    {
        NF("That person is not a Worshipper of the Elementals!\n");
        return 0;
    }

    if (present("_fchosen_", who[0]))
    {
        NF("That person is already chosen!\n");
        return 0;
    }

    my_name = TP->query_real_name();

    if (mentors[my_name])
    {
        NF("You already have an apprentice!\n");
        return 0;
    }

    target(" places "+MY+" hands on your shoulders.  You feel "+
        "power flowing through your body.",who);
    actor("You place your hands on",who,"'s shoulder.");
    all2actbb(" places "+MY+" hands on",who,"'s shoulders.");
    apprentice = who[0]->query_real_name();
    mentors += ([ my_name : apprentice ]);
    fire_apprentices += ({ apprentice });
    (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
        capitalize(my_name) + " has selected "+capitalize(apprentice) +
        " as "+TP->query_possessive()+" apprentice of Pyros.\n");
    save_object(COUNCIL);

    setuid();
    seteuid(getuid());
    chosen=clone_object(FIRE_OBJECTS+"chosen");
    chosen->move(who[0],1);
    return 1;
}

int
fcough(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "noisily", 0);

    if (!stringp(how[0]))
    {
        write("You cough"+how[1]+", releasing small clouds of smoke.\n");
        all(" coughs"+how[1]+", releasing small clouds of smoke.",how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Cough [how] at whom?\n");
        return 0;
    }

    actor("You cough"+how[1]+" at", oblist,", releasing a cloud of smoke.");
    all2act(" coughs"+how[1]+" at",oblist,", releasing a cloud of smoke.",how[1]);
    target(" coughs"+how[1]+" at you, releasing a cloud of smoke in your face.",oblist,how[1]);
    return 1;
}

int
feyes(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "angrily", 0);

    if (!stringp(how[0]))
    {
        write("You glare around"+how[1]+".\n");
        all(" glares around"+how[1]+", "+MY+" eyes blazing embers of power.",how[1]);
        return 1;
    }

    oblist = parse_this(how[0],"[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Glare [how] at whom?\n");
        return 0;
    }

    actor("You glare"+how[1]+" at",oblist);
    all2act(" glares"+how[1]+" at",oblist,", "+MY+" eyes blazing embers of power.",how[1]);
    target(" glares"+how[1]+" at you, "+MY+" eyes blazing embers of power.",oblist, how[1]);
    return 1;
}

int
ffarewell(string str)
{
    object *oblist;

    NF("Bid farewell to who?\n");
    if (!strlen(str))
        return 0;
    
    oblist = parse_this(str,"[to] [the] %l");
    if (!sizeof(oblist))
        return 0;
    
    target(" bids you farewell and good luck in your journeys.",oblist);
    if (sizeof(oblist) == 1)
    {
        actor("You bid",oblist," farewell and good luck in "+
            oblist[0]->query_possessive()+" journeys.");
        all2actbb(" bids",oblist," farewell and good luck in "+
            oblist[0]->query_possessive()+" journeys.");
    }
    else
    {
        actor("You bid",oblist," farewell and good luck in their journeys.");
        all2actbb(" bids",oblist," farewell and good luck in their journeys.");
    }
    return 1;
}

int
ffoot(string str)
{
    str = check_adverb_with_space(str, "discreetly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        NF("Change your footing how?\n");
        return 0;
    }
    write("Small wisps of smoke start to snake upwards from underneath "+
        "your feet as you"+str+" change your footing.\n");
    tell_room(environment(TP),"Small wisps of smoke start to snake upwards "+
        "from underneath the feet of "+QTNAME(TP)+" and "+
        TP->query_pronoun()+str+
        " changes "+MY+" footing.\n",({TP}));
    return 1;
}

int
fgaze(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "intensely", 0);

    if (!stringp(how[0]))
    {
        write("You fix your eyes on an invisible point in front of "+
            "you and gaze at it"+how[1]+".\n");
        all(" fixes "+MY+" eyes on an invisible point and gazes"+
            how[1]+" at it, causing "+MY+" eyes to burn brightly.",how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Gaze [how] at whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        actor("You gaze"+how[1]+" at",oblist);
        all2act(" gazes"+how[1]+" at",oblist,0,how[1]);
        target(" gazes"+how[1]+" at you.",oblist, how[1]);
        return 1;
    }

    actor("You gaze"+how[1]+" at",oblist,", not bothering to conceal "+
        "your contempt.  "+capitalize(oblist[0]->query_pronoun())+
        " looks back, but quickly trembles and looks away.");
    all2act(" gazes"+how[1]+" at",oblist," with unconcealed contempt.  "+
        "After a brief struggle, "+QTNAME(oblist[0])+" trembles and "+
        "averts "+oblist[0]->query_possessive()+ " gaze.", how[1]);
    target(" gazes"+how[1]+" at you, not bothering to conceal "+MY+
        " contempt.  Bravely you look "+TP->query_objective()+" in the "+
        "eye and suddenly feel you are looking into a blazing furnace.  "+
        "A sharp pain spreads from behind your eyes and just as you feel "+
        "you are about to faint, you tremble and lower your gaze.",oblist,how[1]);
    return 1;
}

int
fhail(string str)
{
    object *onl, *oblist, *members, *nonmem;
    
    int i;
    
    NF("Hail who?\n");
    if (!strlen(str))
        return 0;

    onl = FILTER_LIVE(all_inventory(environment(TP))); 
    if (!sizeof(onl)) 
        return 0;

    oblist = parse_this(str," %l");
    oblist -= ({TP});
    if (!sizeof(oblist)) return 0;

    onl -= oblist; 
    onl -= ({TP}); 

    members = filter(oblist, is_walker);
    members += filter(oblist, is_worship);
    nonmem = oblist - members;


    /* Non-members */ 
    for (i = 0; i < sizeof(nonmem); i++)  
    { 
        nonmem[i]->catch_msg(TP->query_The_name(nonmem[i])+" reaches toward " +
            "you with "+ MY+" left hand open, palm facing you, in an " +
            "ancient sign of greetings.\n");
    } 

   if (sizeof(nonmem)) 
       TP->catch_msg("You hail " + group_desc(TP, nonmem, 0) +
            " in an ancient sign of greetings.\n");

    /* Members */ 
    for (i = 0; i < sizeof(members); i++)  
    { 
        members[i]->catch_msg(TP->query_The_name(members[i]) + " reaches " +
            "toward you with "+ MY+" left hand open, palm facing you, " +
            "in an ancient sign of greetings.\n"+
            "You place your right fist in "+MY+" hand to complete the "+
            "greeting.\n");
    } 
    if (sizeof(members)) 
        TP->catch_msg("You hail "+group_desc(TP, members, 0) + 
            " in an ancient sign of greetings.  "+
            (sizeof(members) > 1 ? "They complete" : 
            capitalize(members[0]->query_pronoun())+" completes") +
            " the greeting by placing "+
            (sizeof(members) > 1 ? "their right fists" :
            members[0]->query_possessive()+" right fist")+
            " in your left hand.\n");


    /* Onlookers */ 

    for (i = 0; i < sizeof(onl); i++) 
    { 
        onl[i]->catch_msg(TP->query_The_name(onl[i]) + " reaches toward " +
            group_desc(onl[i], oblist, 0) + " with "+MY+" left hand, in an "+
            "ancient sign of greetings.\n"); 
        if (sizeof(members)) {  
            onl[i]->catch_msg(group_desc(onl[i], members, 1) + " " +  
               (sizeof(members) > 1 ? "complete" : "completes") +
               " the greeting by placing "+
               (sizeof(members) > 1 ? "their right fists" :
               members[0]->query_possessive()+" right fist")+
               " in " +TP->query_the_name(onl[i]) +"'s left hand.\n");
        } 
    } 

    return 1;
}

int
fhug(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "closely", 1);

    oblist = parse_this(how[0], "[the] %l");

    if (!sizeof(oblist))
    {
        NF("Hug whom [how]?\n");
        return 0;
    }

    actor("You hug",oblist,how[1]+", enveloping them in your heat and singeing their eyebrows.");
    all2act(" hugs",oblist, how[1]+", enveloping them in "+MY+
        " heat and singeing their eyebrows.", how[1]);
    target(" hugs you"+how[1]+", enveloping you in "+MY+" heat "+
        "and singeing your eyebrows!",oblist,how[1]);
    return 1;
}

int
fknee(string str)
{
    write("You get down on one knee and call upon the power of "+ 
        "Lord Pyros.\n");
    all(" gets down on one knee and calls out to Pyros, "+
       "Lord of Flame, Elemental of Fire.");
    return 1;
}

int
flaugh(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "wickedly", 0);

    if (!stringp(how[0]))
    {
        write("You laugh"+how[1]+".\n");
        all(" laughs"+how[1]+", sounding disturbingly like the crackle "+
            "of a wildfire!",how[1]);
        SOULDESC("laughing"+how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Laugh [how] at whom?\n");
        return 0;
    }

    actor("You laugh"+how[1]+" at",oblist);
    all2act("  laughs"+how[1]+" at",oblist,", sounding disturbingly "+
        "like a crackling wildfire!",how[1]);
    target(" laughs"+how[1]+" at you, sounding disturbingly like a "+
       "wildfire!",oblist,how[1]);
    SOULDESC("laughing"+how[1]);
    return 1;
}

int
fplay(string str)
{
    write("You weave your hands in an intricate design causing "+
        "the edges of your hair to repeatedly burst into flames, "+
        "then extinguish.\n");
    all(" weaves "+MY+" hands in an intricate design causing the "+
        "edges of "+MY+" hair to repeatedly burst into flames, "+
        "then extinguish.");
    return 1;
}

int
fscream(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "loudly", 0);

    if (!stringp(how[0]))
    {
        if ((environment(TP)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) || (environment(TP)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER))
        {
            write("You scream"+how[1]+" and a flame jets out of your mouth "+
                "causing the water to boil around you.\n");
            all(" screams"+how[1]+" and a flame jets out of "+MY+" mouth causing "+
                "the water to boil around "+TP->query_objective()+".",how[1]);
            SOULDESC("screaming"+how[1]);
            return 1;
        }
        else
        {
            write("You scream"+how[1]+" and a flame jets out of your "+
                "mouth burning a black mark into the ground.\n");
            all(" screams"+how[1]+" and a flame jets out of "+MY+" mouth "+
                "burning a black mark into the ground.",how[1]);
            SOULDESC("screaming"+how[1]);
            return 1;
        }
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Scream [how] at whom?\n");
        return 0;
    }
    
    if (sizeof(oblist) > 1)
    {
        NF("You can only scream at one person at a time!\n");
        return 0;
    }

    actor("You scream"+how[1]+" at",oblist," and a flame jets from your mouth "+
        "leaving a black mark on "+oblist[0]->query_possessive()+" face.");
    all2act(" screams"+how[1]+" at",oblist," and a flame jets from "+MY+
        " mouth leaving a black mark on "+QTNAME(oblist[0])+"'s face.",how[1]);
    target(" screams"+how[1]+" at you and a flame jets from "+MY+" mouth "+
        "leaving a black mark on your face.",oblist,how[1]);
    SOULDESC("screaming"+how[1]);
    return 1;
}

int
fshake(string str)
{
    object *oblist;

    if(!strlen(str))
    {
       NF("Shake hands with whom?\n");
       return 0;
    }

    oblist = parse_this(str, "[with] [the] %l");

    if(!sizeof(oblist))
    {
       NF("Shake hands with whom?\n");
       return 0;
    }

    actor("You shake",oblist," with a heated hand.");
    all2actbb(" grasps",oblist," by the hand in a strong "+
        "shake.");
    target(" grasps your hand in a strong shake.  You recoil and "+
       "jerk back in pain at the intense heat of "+MY+" hand!",oblist);
    return 1;
}

int
fgrin(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "wickedly", 0);

    if (!stringp(how[0]))
    {
        write("You grin"+how[1]+".\n");
        all(" grins"+how[1]+", flames slipping out of "+MY+" mouth.");
        SOULDESC("grinning"+how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] %l");

    if(!sizeof(oblist))
    {
       NF("Grin [how] at whom?\n");
       return 0;
    }

    actor("You grin"+how[1]+" at",oblist,".");
    all2act(" grins"+how[1]+" at",oblist,", "+MY+" eyes "+
        "seem to burn a hole right down to their soul!",how[1]);
    target(" grins at you"+how[1]+", "+MY+" eyes seem to burn a "+
        "hole right down to your soul.",oblist,how[1]);
    SOULDESC("grinning"+how[1]);
    return 1;
}


int
fsmile(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "disdainfully", 0);

    if (!stringp(how[0]))
    {
        write("You smile"+how[1]+".\n");
        all(" smiles"+how[1]+".  Your muscles tighten in an unconscious response.",how[1]);
        SOULDESC("smiling"+how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Smile [how] at whom?\n");
        return 0;
    }

    actor("You smile"+how[1]+" at",oblist);
    all2act(" smiles"+how[1]+" at",oblist,0,how[1]);
    target(" smiles"+how[1]+" at you.  Your muscles tighten in an unconscious response.",oblist,how[1]);
    SOULDESC("smiling"+how[1]);
    return 1;
}

int
fsnap(string str)
{
    str = check_adverb_with_space(str, "confidently");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        NF("Snap how?\n");
        return 0;
    }
    write("You snap your fingers"+str+".\n");
    all(" snaps "+MY+" fingers"+str+".  The smell of sulfur "+
       "pervades the air.",str);
    return 1;
}

int
fspit(string str)
{
    object *who;

    SOULDESC("spitting fire on the ground");

    if (!str || str == "")
    {
       write("You spit fire on the ground in disgust.\n");
       all(" spits fire on the ground in disgust.\nIt extinguishes "+
          "itself quickly.");
       return 1;
    }

    who = parse_this(str, "[at] %l");

    if (!sizeof(who))
    {
        NF("Spit fire at whom?\n");
        return 0;
    }

    actor("You spit fire at",who);
    all2act(" spits fire at",who);
    target(" spits fire at you.  You quickly dodge it and it extinguishes "+
       "itself on the ground beside you.",who);
    return 1;
}

int
fspeak(string msg)
{
    object *oblist;
    int i;
    
    if (TP->query_skill(SS_LANGUAGE) < 10)
    {
        NF("Speaking in the Ancient Elemental Tongue " +
            "requires more training of the language skill.\n");
        return 0;
    }
    
    if (!strlen(msg))
    {
        NF("Say what in the Ancient Elemental Tongue?\n");
        return 0;
    }
    
    if (TP->query_option(OPT_ECHO))
        write("In the Ancient Elemental Tongue, you say: " + msg + "\n");
    else
        write("Ok.\n");

    oblist = all_inventory(environment(TP));

    for (i=0; i < sizeof(oblist); i++)
    {
        if ((living(oblist[i]) && oblist[i] != TP))
	    {
            if (((is_walker(oblist[i]) && oblist[i]->query_skill(SS_LANGUAGE) > 10) ||
                (oblist[i]->query_skill(SS_LANGUAGE) > 70)))
            oblist[i]->catch_msg(QCTNAME(TP) + " says in the Ancient Elemental Tongue: " +
                msg + "\n");
            else
                oblist[i]->catch_msg(QCTNAME(TP) + " speaks in a language "+
                "you do not understand.\n");
        }
    }
    return 1;
}

int
list_fires()
{
    string g_name, g_short;
    int i;
    object *list;

    write("The following Firewalkers are in the Realms:\n");
    list = users();
    for (i=0; i < sizeof(list); i++)
    {
        if (!is_fire(list[i]) || list[i]->query_invis())
          continue;

       g_name = capitalize(list[i]->query_real_name());

       if(!list[i]->query_wiz_level())
       {
          g_short = list[i]->query_fire_walker_title();
          write("- " + g_name + " " + g_short + "\n");
       }
        if (list[i]->query_wiz_level())
       {
          g_short = list[i]->query_title();
          write("- " + g_name + " " + g_short + "\n");
       }
    }
   
    return 1;
}

int
list_walkers()
{
    string g_name, g_short;
    int i;
    object *list;

    write("The following Walkers are in the Realms:\n");
    list = users();
    for (i=0; i < sizeof(list); i++)
    {
        if (!is_walker(list[i]) || list[i]->query_invis())
            continue;

        g_name = capitalize(list[i]->query_real_name());

            g_short = list[i]->query_title();
            write("- "+g_name+" "+g_short+"\n");
    }
    return 1;
}

int
list_worshippers()
{
    string g_name, g_short;
    int i;
    object *list;

    write("The following Worshippers are in the Realms:\n");
    list = users();
    for (i=0; i < sizeof(list); i++)
    {
        if (!is_worship(list[i]) || list[i]->query_invis())
            continue;

        g_name = capitalize(list[i]->query_real_name());

            g_short = list[i]->query_title();
            write("- "+g_name+" "+g_short+"\n");
    }
    return 1;
}

int
f_help(string str)
{
    if (!str)
        return 0;

    if (str == "firewalker" || str == "fire" || str == "firewalkers")
    {
        write("You may get help on the following:\n\n"+
            "    help fire(walker) titles - a list of firewalker titles\n"+
            "    help fire(walker) spells - a list of firewalker spells\n"+
            "    help fire(walker) emotes - a list of firewalker emotes\n"+
            "    help fire(walker)        - this list\n"+
            "\n");
        return 1;
    }

    if (str == "firewalker emotes" || str == "fire emotes")
    {
        cmd_list();
        return 1;
    }

    if (str == "firewalker titles" || str == "fire titles")
    {
        write("There are the following titles in the Firewalkers:\n\n"+
            "    <title> of the Primitive Ring of Flame\n"+
            "    <title> of the Obscure Ring of Flame\n"+
            "    <title> of the Outer Ring of Flame\n"+
            "    <title> of the Inner Ring of Flame\n"+
            "    <title> of the Esoteric Sphere of Flame\n"+
            "    <title> of the Harmonic Sphere of Flame\n"+
            "    <title> of the Transcendent Sphere of Flame\n"+
            "    <title> of the Ancient Sphere of Flame\n"+
            "    <title> of the Divine Realm of Flame\n"+
            "    Firewalker of Legends\n\n"+
            "<title> is broken down into the following:\n\n"+
            "    Initiate, Novice, Disciple, Master\n\n"+
            "Council members can be recognized by having the additional "+
            "title of 'Harbinger of Pyros' added to their own.\n\n"+
            "Assistants can be recognized by having the additional "+
            "title of 'Emmissary of Pyros' added to their own.\n\n"+
            "\n");
        return 1;
     }

    if (str == "firewalker spells" || str == "fire spells")
    {
        write("\n\n"+
              "Spells of the Primitive Ring:       Astraphto, Gsechon\n"+
              "Spells of the Obscure Ring:         Tuphlono, Pyronero\n"+
              "Spells of the Outer Ring:           Bradu\n"+
              "Spells of the Inner Ring:           Therapeaou, Akoutari, Aspida\n"+
              "Spells of the Esoteric Sphere:      Saita, Photitso\n"+
              "Spells of the Harmonic Sphere:      Purkagia, Optasia\n"+
              "Spells of the Transcendent Sphere:  Aeras, Photostepsanos\n"+
              "Spells of the Ancient Sphere:       Anthisto\n"+
              "Spells of the Divine Realm:         Stoiecheio, Aemera\n"+
              "Spells of the Legendary Domain:     Hagiospyro, Phlogaphulo, Kausae\n\n"+
              "If you have earned the use of the spell, you may get help "+
              "on it by doing 'help fire <spellname>'.  If you have not "+
              "earned the use of it, you will get no help on it.\n"+
              "\n");
        return 1;
    }

    if (str == "firewalker astraphto" || str == "fire astraphto")
    {
        write("Astraphto - Flame Speak :   With this spell you will be "+
            "able to send a message to anyone in the Realms.  You will "+
            "need a handful of ash to sacrifice.\n");
        return 1;
    }

    if (str == "firewalker gsechon" || str == "fire gsechon")
    {
        write("Gsechon - Name Forget :   With this spell you will be "+
            "able make a target forget your identity by burning it from "+
            "their minds.  For this you will require ash and obsidian "+
            "to sacrifice.\n");
        return 1;
    }

    if (str == "firewalker tuphlono" || str == "fire tuphlono")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TWO_FLAG)
        {
            write("Tuphlono - Blinding Flash :  This will leave your target "+
                "blinded for a short time by creating a bright flash of "+
                "light before their eyes.  You will require the herb "+
                "laminaria and salt for this spell.\n");
            return 1;
        }
    }
        
    if (str == "firewalker pyronero" || str == "fire pyronero")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TWO_FLAG)
        {
            write("Pyronero - Fire Water :  This will raise the alcohol "+
                "level in the blood of the target.  You may use this on "+
                "yourself if you wish to do so.  You must be under the "+
                "effects of the nero potion for it to work, and it "+
                "may be cast until the effects of the potion wear off.  "+
                "The nero potion is mixed with poison ivy and a "+
                "water vial.\n");
            return 1;
        }
    }

    if (str == "firewalker bradu" || str == "fire bradu")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_THREE_FLAG)
        {
            write("Bradu - Peace :  Once this spell is cast, all fighting "+
                "in your location will cease immediately.  Be warned, "+
                "it can be started right away, this merely stops the "+
                "current conflicts.  You must be under the effects of "+
                "the bradu potion for it to work, and may be cast until "+
                "the effects of the potion wear off.  The bradu potion "+
                "is mixed with elkhorn kelp and a water vial.\n");
            return 1;
        }
    }

    if (str == "firewalker therapeaou" || str == "fire therapeaou")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FOUR_FLAG)
        {
            write("Therapeaou - Heal :  This spell will restore some of "+
                "the target it is cast upon.  This spell may be cast on "+
                "yourself if you so choose to do so.  You will require "+
                "the herbs fireweed and brown slime for this to work.\n");
            return 1;
        }
    }

    if (str == "firewalker akoutari" || str == "fire akoutari")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FOUR_FLAG)
        {
            write("Akoutari - Wall Of Fire :  This spell will block the "+
                "selected exit with a wall of flames.  Those who have "+
                "some resistance to fire and those who worship Lord Pyros "+
                "may pass through these flames unhindered.  All others will "+
                "not be able to pass this barrier.  You may have more than "+
                "one of these barriers in a place at any time.  They will "+
                "only last a short time.  You must be under the influence "+
                "of the akoutari potion for this spell to work.  You may "+
                "continue to cast this spell until the effects of the "+
                "potion wear off.  The akoutari potion is mixed with "+
                "fucus, sulphur and a water vial.\n");
            return 1;
        }
    }

    if (str == "firewalker aspida" || str == "fire aspida")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FOUR_FLAG)
        {
            write("Aspida - Flame Shield :  This spell will encompass "+
                "the target in a shield of flames for some time.  This "+
                "shield will block some damage inflicted upon the target.  "+
                "You may cast this on yourself if you so desire to do so.  "+
                "You must be under the influence of the aspida potion for "+
                "this spell to work and you can continue to cast it until "+
                "the effects of the potion wear off.  To mix the aspida "+
                "potion you need sulphur, bull kelp, and a water vial.\n");
            return 1;
        }
    }

    if (str == "firewalker saita" || str == "fire saita")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FIVE_FLAG)
        {
            write("Saita - Flaming Bolt :  The first, and weakest of "+
                "the offensive spells, this will do a small amount of "+
                "damage to the target by sending a bolt of flames at "+
                "them.  This spell cannot be used underwater (for "+
                "obvious reasons) and will initiate combat.  To use "+
                "this spell, you must be under the influence of the "+
                "saita potion and you may continue to cast it until the "+
                "effects of the potion wears off.  To mix the saita "+
                "potion you will require sulphur, salt, and a powerful "+
                "alcohol (moonshine is recommended).\n");
            return 1;
        }
    }

    if (str == "firewalker photitso" || str == "fire photitso")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FIVE_FLAG)
        {
            write("Photitso - Light :  The target of this spell will "+
                "have their hand surrounded by light for a short period "+
                "of time.  You may cast this upon yourself if you desire "+
                "to do so.  This light is magical in nature and can be "+
                "used underwater.  You will require sulphur and salt to "+
                "sacrifice for this spell.\n");
            return 1;
        }
    }

    if (str == "firewalker purkagia" || str == "fire purkagia")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SIX_FLAG)
        {
            write("Purkagia - Fireball :  The second offensive spell you "+
                "recieve is a bit more powerful than its predecesor as "+
                "it sends a flaming ball at its target.  This fireball "+
                "will explode when it contacts its intended victim.  You "+
                "will need to be under the influence of the purkagia potion "+
                "for this spell to work and you may continue to cast it "+
                "until the effects of the potion wear off.  The purkagia "+
                "potion is mixed with coral alga and a strong alcohol "+
                "(again, moonshine is recommended).\n");
            return 1;
        }
    }

    if (str == "firewalker optasia" || str == "fire optasia")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SIX_FLAG)
        {
            write("Optasia - Night Vision :  This spell will grant "+
                "the target the ability to see in the dark.  This "+
                "spell may be cast upon yourself.  The darkness vision "+
                "will last for a small amount of time.  You must be under "+
                "the influence of the optasia potion to be able to cast it "+
                "successfully and you can continue to cast it until the "+
                "effects of the potion wear off.  The optasia potion is "+
                "mixed with ash, sea lettuce, and a water vial.\n");
            return 1;
        }
    }

    if (str == "firewalker aeras" || str == "fire aeras")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SEVEN_FLAG)
        {
            write("Aeras - Flame Wind :  The third offensive spell you "+
                "recieve is much more powerful that its predecesors "+
                "as it sends a flaming wind at its target.  You will "+
                "need to be under the influence of the aeras potion for "+
                "it to be cast and you can continue to cast it until the "+
                "effects of the potion wear off.  To mix the aeras potion "+
                "you will need salt wort and a powerful alcohol (moonshine).\n");
            return 1;
        }
    }

    if (str == "firewalker photostepsanos" || str == "fire photostepsanos")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SEVEN_FLAG)
        {
            write("Photostepsanos - Fire Aura :  The target of this spell "+
                "will suddenly become surrounded by flames that will burn "+
                "away all traces of their existance, at least to all "+
                "onlookers.  In reality the target will become invisible "+
                "for a short period of time.  You may cast this spell on "+
                "yourself.  If you (or the target of the spell) attack "+
                "something or are attacked in this invisible state, "+
                "you (or the target of the spell) will instantly become "+
                "visible again.  You must be under the influence of the "+
                "photostepsanos potion for this spell to be correctly cast "+
                "and it can continue to be cast until the effects of the "+
                "potion wear off.  To mix the photostepsanos potion you "+
                "will require sea bubble and a strong alcohol (moonshine).\n");
            return 1;
        }
    }

    if (str == "firewalker anthisto" || str == "fire anthisto")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_EIGHT_FLAG)
        {
            write("Anthisto - Resist Fire :  The target of this spell "+
                "will have their skin enchanted so they will become "+
                "magically resistant to fire and fire magic.  You may "+
                "cast this upon yourself.  You must be under the effects "+
                "of the anthisto potion to cast this spell and can "+
                "continue to cast it until the potion wears off.  To mix "+
                "the anthisto potion you will require sulphur, sargassum, "+
                "and a water vial.\n");
            return 1;
        }
    }

    if (str == "firewalker stoiecheio" || str == "fire stoiecheio")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_NINE_FLAG)
        {
            write("Stoiecheio - Elemental Form :  Once this spell is "+
                "successfully cast, you will be granted the form of a "+
                "fire elemental.  This form will disguise you so no person "+
                "will know your name unless you choose to introduce "+
                "yourself to them.  This form will grant you no special "+
                "powers and no special attacks, and shall stay until you "+
                "choose to <revert> back to your normal form, or until "+
                "you run out of mental energies.  Maintaining this form "+
                "does requre mental energy so you shall continue to lose "+
                "mana until you revert to your normal form.  To cast this "+
                "spell successfully, you will need to be under the effects "+
                "of the stoiecheio potion, which is mixed with ash, fireweed "+
                "and a strong alcohol (moonshine).\n");
            return 1;
        }
    }

    if (str == "firewalker aemera" || str == "fire aemera")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_NINE_FLAG)
        {
            write("Aemera - Daylight :  This spell will cause the flame "+
                "in your necklace pendant to glow as bright as the sun "+
                "itself, giving you light to see by as you travel.  You "+
                "will require the herb laminaria and obsidian to cast "+
                "this spell.  The light will last for quite a long period "+
                "of time and can be used underwater.\n");
            return 1;
        }
    }

    if (str == "firewalker hagiospyro" || str == "fire hagiospyro")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TEN_FLAG)
        {
            write("Hagiospyro - Holy Fires :  The fourth offensive "+
                "spell at your control unleashes waves of flames down "+
                "from the skies upon the target, causing them much damage "+
                "and costing you much of your mental energies.  This spell "+
                "cannot be case while you are underwater (for obvious "+
                "reasons), nore inside any caves or buildings.  You will "+
                "need to be under the influence of the hagiospyro potion "+
                "to cast it and you may continue to cast it until the "+
                "effects of the potion wear off.  The hagiospyro potion "+
                "is mixed with ash, sargassum, poison ivy, and a strong "+
                "alcohol (moonshine).\n");
            return 1;
        }
    }

    if (str == "firewalker phlogaphulo" || str == "fire phlogaphulo")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TEN_FLAG)
        {
            write("Phlogaphulo - Flame Weapon :  Upon the successful "+
                "casting of this spell, the weapon you cast it on shall "+
                "begin to flame, causing more damage when an enemy is hit "+
                "with it.  You may only use this spell a limited number "+
                "of times on any one weapon and there are some weapons "+
                "which it will not work on.  You must be under the influence "+
                "of the phlogaphulo potion to cast this spell and you may "+
                "continue to do so until the effects of the potion wear "+
                "off.  To mix the phlogaphulo potion you will require "+
                "obsidian, salt, fireweed, laminaria, and a water vial.\n");
            return 1;
        }
    }

    if (str == "firewalker kausae" || str == "fire kausae")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TEN_FLAG)
        {
            write("Kausae - Combustion :  The final offensive spell under "+
                "your control, this spell can only be cast while you are "+
                "in elemental form (stoiecheio).  It will send part of "+
                "your flaming energies towards the target causing much "+
                "damage to them.  Along with being in elemental form, you "+
                "must also be under the effects of the kausae potion.  This "+
                "spell may be cast until the effects of the kausae potion "+
                "wear off, or you revert back to your normal form.  This spell "+
                "may not be cast underwater.  The kausae potion is mixed "+
                "with salt, ash, laminaria, surf grass and a powerful "+
                "alcohol (moonshine).\n");
            return 1;
        }
    }

    return 0;
}

mapping
query_cmdlist()
{
    return ([
    "fbless"    : "fbless",
    "fchoose"   : "fchoose",
    "fcough"    : "fcough",
    "feyes"     : "feyes",
    "ffare"     : "ffarewell",
    "ffarewell" : "ffarewell",
    "ffoot"     : "ffoot",
    "fgaze"     : "fgaze",
    "fgrin"     : "fgrin",
    "fhail"     : "fhail",
    "fhug"      : "fhug",
    "fknee"     : "fknee",
    "flaugh"    : "flaugh",
    "fplay"     : "fplay",
    "fscream"   : "fscream",
    "fshake"    : "fshake",
    "fsmile"    : "fsmile",
    "fsnap"     : "fsnap",
    "fs"        : "fspeak",
    "fspeak"    : "fspeak",
    "fspit"     : "fspit",
    "fwho"      : "list_fires",
    "walkers"   : "list_walkers",
    "worshippers" : "list_worshippers",
    "wch"       : "usay",
    "wchant"    : "usay",
    "help"      : "f_help",
    ]);
}

