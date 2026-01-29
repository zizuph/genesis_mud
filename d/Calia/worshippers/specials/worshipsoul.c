
 /*

       Worshippers Layman soul  
       Jaacar, 1996/97  

 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <options.h>
#include <std.h>
#include <filter_funs.h>
#include "/d/Calia/domain.h"
#include "defs.h"
#include WORSHIP_HEADER
#include LANGUAGE_HEADER
#include SPELLS_HEADER
#include COUNCIL_HEADER

#define SPIRIT_GUILD "Spirit Circle of Psuchae"
#define COUNCIL_LOG  WOR_LOGS+"council"
#define MY this_player()->query_possessive()
#define HIM this_player()->query_objective()
#define HE this_player()->query_pronoun()
#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define HELP_FILE_DIR "/d/Calia/worshippers/texts/"

int wsummon_id;

string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

string
get_soul_id()
{
    seteuid(getuid());
    return "Elemental Worshippers of Calia";
}


void
title_help()
{
    setuid();
    seteuid(getuid());
    this_player()->more(read_file(HELP_FILE_DIR + "titles.txt"));
}

int
query_cmd_soul()
{
    seteuid(getuid());
    return 1;
}

int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_NAME;
}

int
is_walker(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD;
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


string
el_desc(object ob, int en)
{
    string elmet, elunmet; 
    switch (en)
        {
            case FIRE_FLAG:
                elunmet = "an intense fiery force";
                elmet = "Lord Pyros"; 
                break;
            case EARTH_FLAG:
                elunmet = "a natural caring force";
                elmet = "Lady Gu";  
                break;
            case WATER_FLAG:
                elunmet = "a profound wise force";
                elmet = "Lord Diabrecho"; 
                break;
            default:
                elunmet = "a carefree beautiful force";
                elmet = "Lady Aeria"; 
                break;
        }
    if (is_worship(ob))  
        return elmet; 
    else
        return elunmet; 
}

int
cmd_list()
{
    write("You can use the following commands:\n\n" +
        "help worshippers               Get a list of all of the Worshipper help\n"+
        "                               commands\n"+
        "wbless <player>                Bless <player> in the name of the Elementals\n"+
        "wch(ant) (<message>)           Chant (<message>) in ancient mantras\n" +
        "wcharge (<target>)             Give a battle charge (and attack <target>)\n" +
        "wconvert <player>              Try to convert <player> to Elemental worship\n" +
        "wcurse <player>                Send the wrath of the Elementals upon <player>\n"+
        "wfare(well) <player(s)>        Bid farewell to <player(s)>\n" +
        "wgaze                          Gaze silently into the sky/upwards\n" +
        "wjoy                           Show an expression of joy\n" +
        "whail <player(s)>              Hail <player(s)> in the name of the Elementals\n" +
        "wkneel (<player>)              Kneel briefly (before <player>)\n" +
        "wlaugh                         Give an elemental laugh\n"+
        "wlist                          Get a list of Worshippers currently in the\n"+
        "                               realms\n" +
        "wlisten (fire/water/earth/air) Listen to an element\n"+
        "wprepare                       Murmur a prayer in preparation of your next\n"+
        "                               battle\n"+
        "wscoff <player>                Scoff at <player>\n" +
        "wsilence                       Motion for a moment of silence\n" +
        "wsmile (<player(s)>)           Smile confidently (at (<player(s)>))\n"+
        "wstare <player(s)>             Stare angrily at <player(s)>\n"+
        "wvictory                       Give thanks to the Elements for your victory\n"+
        "\n");
    return 1;
}

int
cmd_list2()
{
    if (present(I_CAN_CAST,TP))
    {
        write("\nYou may use the following granted emotes:\n\n"+
        "weyes                          Your eyes dance with the power of your\n"+
        "                               Elemental\n"+
        "wpray <player>                 Pray for <player>\n"+
        "wsummon                        Summon the power of your Elemental\n"+
        "\n");
        return 1;
    }
    else
    return 0;
}

int
fail_ghost()
{
    write("Ghosts cannot do that.\n");
    return 1;
}

int
wbless(string str)
{
    int section;
    object *who;
    NF("Bless who?\n");
    if (!str || str == "")
        return 0;
    
    who = parse_this(str, " %l");
    if (!sizeof(who)) 
        return 0;
    
    section = TP->query_skill(SS_PATRON_ELEMENTAL);

    switch(section)
    {
        case FIRE_FLAG:
            actor("You bless",who," saying `May you kindle Fire "+
                "and never be burned by it.'");
            target(" blesses you saying, `May you kindle "+
                "Fire and never be burned by it.'",who);
            all2actbb(" blesses",who," and says `May you kindle "+
                "Fire and never be burned by it.'");
            break;
        case WATER_FLAG:
            actor("You bless",who," saying `May the Water of "+
                "your tears always taste sweet with joy.'");
            target(" blesses you saying, `May the Water of your "+
                "tears always taste sweet with joy.'",who);
            all2actbb(" blesses",who," and says `May the Water of "+
                "your tears always taste sweet with joy.'");
            break;
        case EARTH_FLAG:
            actor("You bless",who," saying `May your path across "+
                "the Earth be a soft one.'");
            target(" blesses you saying, `May your path across "+
                "the Earth be a soft one.'",who);
            all2actbb(" blesses",who," and says `May your path "+
                "across the Earth be a soft one.'");
            break;
        default:
            actor("You bless",who," saying `May the Air never "+
                "send storms across your path.'");
            target(" blesses you saying, `May the Air never "+
                "send storms across your path.'",who);
            all2actbb(" blesses",who," and says `May the Air "+
                "never send storms across your path.'");
            break;
    }
    return 1;
}

int
wchant(string str)
{
    object *oblist;
    int i, who;
    
    who = TP->query_skill(SS_PATRON_ELEMENTAL);

    if (!strlen(str) || str == "")
    {
        switch (who)
        {
            case FIRE_FLAG:
                write("You sit briefly and chant in the sounds of a "+
                    "crackling flame.\n");
                all(" sits down and begins to chant.\nYou hear the "+
                    "sound of crackling flames in "+MY+" voice.  After a brief "+
                    "moment, "+HE+" rises again.");
                break;
            case EARTH_FLAG:
                write("You sit briefly and chant in the sounds of the "+
                    "pounding earth.\n");
                all(" sits down and begins to chant.\nYou hear sounds "+
                    "like that of the pounding earth in "+MY+" voice.  "+
                    "After a brief moment, "+HE+" rises again.");
                break;
            case WATER_FLAG:
                write("You sit briefly and chant in the sounds of the "+
                    "ocean waves.\n");
                all(" sits down and begins to chant.\nYou hear the "+
                    "sound of the ocean in "+MY+" voice.  After a brief "+
                    "moment, "+HE+" rises again.");
                break;
            default:
                write("You sit briefly and chant in the sounds of the "+
                    "howling winds.\n");
                all(" sits down and begins to chant.\nYou hear the "+
                    "sounds of the howling winds in "+MY+" voice.  "+
                    "After a brief moment, "+HE+" rises again.");
                break;
        }
        return 1;
    }    
    
    if (TP->query_option(OPT_ECHO))
        write("You chant: " + str + "\n");
    else
        write("You chant your message in the ancient mantras.\n");

    oblist = all_inventory(environment(TP));
    for (i=0; i < sizeof(oblist); i++)
    {
        if ((living(oblist[i]) && oblist[i] != TP))
        {
            if (((is_worship(oblist[i])) 
                || is_walker(oblist[i])
                || (oblist[i]->query_skill(SS_LANGUAGE) > 70)))
                oblist[i]->catch_msg(QCTNAME(TP)+" chants: " + break_string(str+"\n",70));
            else
                oblist[i]->catch_msg(QCTNAME(TP)+" chants in ancient mantras.\n");
            }
        }
    SOULDESC("chanting in ancient mantras");
    return 1;
}

int
wcharge(string str)
{
    int who;
    who = TP->query_skill(SS_PATRON_ELEMENTAL);

    if (!str)
    {
        switch (who)
        {
            case FIRE_FLAG:
                write("Your eyes glow a fiery red as you call out a "+
                    "battle cry in honour of Lord Pyros!\n");
                all("'s eyes glow a fiery red as "+HE+" cries out, "+
                    "'For Lord Pyros!' and charges into battle.");
                break;
            case EARTH_FLAG:
                write("You feel the ground tremble beneath your "+
                    "feet as you call out a battle cry in honour of Lady Gu!\n");
                all("'s fists almost appear to be stone as "+HE+" cries out,"+
                    " 'For Lady Gu!' and charges into battle.");
                break;
            case WATER_FLAG:
                write("You hear the sound of waves crashing against a "+
                    "rocky shore as you call out a battle cry in honour "+
                    "of Lord Diabrecho!\n");
                all("'s eyes flash a deep sea blue as "+HE+" cries out, "+
                    "'For Lord Diabrecho!' and charges into battle.");
                break;
            default:
                write("You hear the sound of the howling winds of Aeria "+
                    "as you call out a battle cry in honour of the Elemental "+
                    "Lady!\n");
                all("'s voice sounds like that of a hurricane force wind "+
                    "as "+HE+" cries out, 'For Lady Aeria!' and charges "+
                    "into battle.");
                break;
        }
        return 1;
    }

    switch (who)
    {
        case FIRE_FLAG:
            write("You call out a battle cry in honour of Lord Pyros and "+
                "feel the strength of an unextinguishable fire flow through "+
                "you as you attack your target.\n");
            all("'s eyes glow a fiery read as "+HE+" cries out, "+
                "'For Lord Pyros!' and charges into battle.");
            TP->command("kill "+str);
            break;
        case EARTH_FLAG:
            write("The ground shakes beneath your feet as you call out "+
                "a battle cry in honour of Lady Gu and attack your target.\n");
            all("'s fists almost appear to be stone as "+HE+" cries out,"+
                " 'For Lady Gu!' and charges into battle.");
            TP->command("kill "+str);
            break;
        case WATER_FLAG:
            write("Your veins flow with the power of a mighty sea storm "+
                "as you call out a battle cry in honour of Lord "+
                "Diabrecho and attack your target.\n");
            all("'s eyes flash a deep sea blue as "+HE+" cries out, "+
                "'For Lord Diabrecho!' and charges into battle.");
            TP->command("kill "+str);
            break;
        default:
            write("You feel the power of a great tornado flow throughout "+
                "your body as you call out a battle cry in honour of "+
                "Lady Aeria and attack your target.\n");
            all("'s voice sounds like that of a hurricane force wind "+
                "as "+HE+" cries out, 'For Lady Aeria!' and charges "+
                "into battle.");
            TP->command("kill "+str);
            break;
    }
    return 1;
   
}

int
wconvert(string str)
{
    object *who;
    int section;

    section = TP->query_skill(SS_PATRON_ELEMENTAL);

    NF("Convert who?\n");
    if (!str || str == "")
        return 0;
    
    who = parse_this(str, " %l");
    if (!sizeof(who)) return 0;
    if (!is_worship(who[0]))
    {
        switch (section)
        {
            case FIRE_FLAG:
                actor("You attempt to convert",who," to follow Lord Pyros.");
                target(" tries to convince you to convert, and follow the ways of Lord Pyros.",who);
                break;
            case EARTH_FLAG:
                actor("You attempt to convert",who," to follow Lady Gu.");
                target(" tries to convince you to convert, and follow the ways of Lady Gu.",who);
                break;
            case WATER_FLAG:
                actor("You attempt to convert",who," to follow Lord Diabrecho.");
                target(" tries to convince you to convert, and follow the ways of Lord Diabrecho.",who);
                break;
            default:
                actor("You attempt to convert",who," to follow Lady Aeria.");
                target(" tries to convince you to convert, and follow the ways of Lady Aeria.",who);
                break;
        }
        all2actbb(" attempts to convert",who," to "+MY+" Elemental ways.");
        return 1;
    }
    else
    {
        NF("You can't convert someone who is already an Elemental Worshipper!\n");
        return 0;
    }
}

int
wcurse(string str)
{
    object *who;
    int section;

    section =TP->query_skill(SS_PATRON_ELEMENTAL);

    NF("Curse who?\n");
    if (!str || str == "")
        return 0;
    
    who = parse_this(str, " %l");
    if (!sizeof(who)) return 0;
    if (!is_worship(who[0]))
    {
        switch (section)
        {
            case FIRE_FLAG:
                actor("You curse",who," in the name of Lord Pyros.");
                target(" curses you with the wrath of Lord Pyros.",who);
                break;
            case EARTH_FLAG:
                actor("You curse",who," in the name of Lady Gu.");
                target(" curses you with the wrath of Lady Gu.",who);
                break;
            case WATER_FLAG:
                actor("You curse",who," in the name of Lord Diabrecho.");
                target(" curses you with the wrath of Lord Diabrecho.",who);
                break;
            default:
                actor("You curse",who," in the name of Lady Aeria.");
                target(" curses you with the wrath of Lady Aeria.",who);
                break;
        }
        all2actbb(" curses",who,".");
        return 1;
    }
    else
    {
        actor("You curse",who," in the name of the Elementals.");
        target(" curses you with the wrath of the four Elementals.",who);
        all2actbb(" curses",who,".");
        return 1;
    }
}


int
weyes()
{
    int who;
    who = TP->query_skill(SS_PATRON_ELEMENTAL);
    
    if (!present(I_CAN_CAST,TP))
    {
        NF("What ?\n");
        return 0;
    }
    switch (who)
    {
        case FIRE_FLAG:
            write("Your eyes flare with the power of Lord Pyros!\n");
            all("'s eyes flare like a bright red flame.");
            break;
        case EARTH_FLAG:
            write("Your eyes sparkle with the power of Lady Gu!\n");
            all("'s eyes sparkle like two perfectly cut diamonds.");
            break;
        case WATER_FLAG:
            write("Your eyes glow with the power of Lord Diabrecho!\n");
            all("'s eyes glow a bright watery blue.");
            break;
        default:
            write("Your eyes flash with the power of Lady Aeria!\n");
            all("'s eyes flash suddenly like a lightning strike.");
            break;
    }
    return 1;
}

int
wfarewell(string str)
{
    object *oblist;
    NF("Bid farewell to who?\n");
    if (!strlen(str))
        return 0;
    
    oblist = parse_this(str," %l");
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
wgaze()
{
    if ((environment(this_player())->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) ||
        (environment(this_player())->query_prop(ROOM_I_INSIDE)))
    {
        write("You gaze upwards in thoughtful silence.\n");
        all(" gazes upwards in thoughtful silence.");
        SOULDESC("gazing upwards in thoughtful silence");
    }
    else
    {
        write("You gaze off towards the sky in thoughtful silence.\n");
        all(" gazes off towards the sky in thoughtful silence.");
        SOULDESC("gazing upwards in thoughtful silence");
    }
    if (TP->carve_count() < TP->carve_count(1))
    {
        write("A voice echoes in your mind: "+
            "You are ready to carve a Word of Power into one of your "+
            "Elemental Tools.\n");
        all(" seems to radiate with power momentarily.");
    }
    return 1;
}

int
worhail(string str)
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

    members = filter(oblist, is_worship);
    members += filter(oblist, is_walker);
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
w_help(string str)
{
    if (!str) return 0;

    if (str == "worshippers emotes" || str == "worshipper emotes" ||
        str == "wor emotes")
    {
        cmd_list();
        return 1;
    }

    if (str == "worshippers granted" || str == "worshipper granted" ||
        str == "wor granted")
    {
        cmd_list2();
        return 1;
    }

    if (str == "worshippers titles" || str == "worshipper titles" ||
        str == "wor titles")
    {
        title_help();
        return 1;
    }

    if (str == "worshippers" || str == "worshipper" || str == "wor")
    {
        write("\nWorshipper help options\n"+
              "=======================\n\n"+
              "help worshippers         - this list\n"+
              "help worshippers emotes  - Worshippers emotes list\n"+
              "help worshippers titles  - Worshippers titles list\n");
        if (present(I_CAN_CAST,TP))
        {
            write("help worshippers granted - Worshippers granted "+
                "emotes list\n");
        }
        return 1;
     }
     return 0;
}

int
wjoy()
{
    write("You show an expression of your joy.\n");
    all("'s face brightens with joy.");
    return 1;
}

int
wjpray(string str)
{
    object *who, *onl, joinob;
    int section, i;
    string godmet, godunmet;

    if (!present(I_CAN_CAST,TP))
    {
        NF("What ?\n");
        return 0;
    }
    NF("Pray for who?\n");
    section = TP->query_skill(SS_PATRON_ELEMENTAL);
    if (!str || str == "")
        return 0;
    who = parse_this(str, "[for] %l");
    if (!sizeof(who)) return 0;

    /* Find onlookers */ 
    onl = FILTER_LIVE(all_inventory(environment(TP))); 
    onl -= ({TP}); 
    onl -= who; 

    actor("You pray for",who);
    setuid();
    seteuid(getuid());
    joinob = clone_object(WOR_OBJECTS+"joinob");

    for (i = 0; i < sizeof(who); i++)
    {   
        who[i]->catch_msg("You feel the presence of "+
               el_desc(who[i], section) + " as "+TP->query_the_name(who[i]) + 
               " prays for " + ((sizeof(who) == 1) ? 
               "your well being" : 
                ("the well being of " + group_desc(who[i], who, 0))) +
               ".\n");
        if (!present(I_CAN_JOIN,who[i]))
        {
            joinob->move(who[i],1);
            (WOR_OBJECTS+"council_log_book")->update_log_book(my_time()+
                TP->query_name()+" granted "+who[i]->query_name()+
                " permission to join the Circle.\n");
        }
    }

    for (i = 0; i < sizeof(onl); i++)  
        onl[i]->catch_msg("You feel the presence of " + 
               el_desc(onl[i], section) + " as " + 
                 TP->query_the_name(onl[i]) + " prays for the well " + 
                 "being of " + group_desc(onl[i], who, 0) + ".\n"); 

    return 1;
}

int
wkneel(string str)
{
    object *who;
    NF("Kneel before who?\n");
    if (!str || str == "")
    {
        write("You kneel in prayer briefly.\n");
        all(" kneels briefly in prayer.");
        return 1;
    }
    who = parse_this(str, " %l");
    if (!sizeof(who)) return 0;
    actor("You kneel briefly before",who);
    target(" kneels briefly before you.",who);
    all2actbb(" kneels briefly before",who,".");
    return 1;
}

int
wlaugh()
{
    int who;
    who = TP->query_skill(SS_PATRON_ELEMENTAL);
    
    switch (who)
    {
        case FIRE_FLAG:
            write("You laugh chaotically with the sound of a crackling bonfire.\n");
            all(" tilts "+MY+" head back in a chaotic laughter and you "+
                "are reminded inexplicably of a crackling bonfire.");
            break;
        case EARTH_FLAG:
            write("You laugh heartily like the earth rumbling.\n");
            all(" tilts "+MY+" head back in a hearty laughter and you "+
                "are reminded of the sound of the ground rumbling.");
            break;
        case WATER_FLAG:
            write("You laugh merrily with the sound of a babbling brook.\n");
            all(" tilts "+MY+" head back in a merry laughter and you "+
                "are reminded inexplicably of a babbling brook.");
            break;
        default:
            write("You laugh confidently with the sound of the howling winds.\n");
            all(" tilts "+MY+" head back in a confident laughter and you "+
                "are reminded of the sound of a howling wind.");
            break;
    }
    return 1;
}

int
worlist()
{
    setuid();
    seteuid(getuid());
    return MEMBER_LIST_UTILITY->list_members();    
}

int
old_worlist()
{
    object *list;
    string fire, water, earth, air;

    list = filter(users(),&operator(==)(GUILD_NAME) @
        &->query_guild_name_lay());
    list = filter(list, &operator(!=)(100) @ &->query_invis());

    fire = implode(filter(list,&operator(==)(FIRE_FLAG) @
        &->query_skill(SS_PATRON_ELEMENTAL))->query_presentation(),
        "\n");
    water = implode(filter(list,&operator(==)(WATER_FLAG) @
        &->query_skill(SS_PATRON_ELEMENTAL))->query_presentation(),
        "\n");
    earth = implode(filter(list,&operator(==)(EARTH_FLAG) @
        &->query_skill(SS_PATRON_ELEMENTAL))->query_presentation(),
        "\n");
    air = implode(filter(list,&operator(==)(AIR_FLAG) @
        &->query_skill(SS_PATRON_ELEMENTAL))->query_presentation(),
        "\n");

    write("The following members are within the Realms:\n"+
        (strlen(fire) > 2 ? "Followers of Pyros:\n"+fire : "") +
        (strlen(water) > 2 ? "\n\nFollowers of Diabrecho:\n"+water : "") +
        (strlen(earth) > 2 ? "\n\nFollowers of Gu:\n"+earth : "") +
        (strlen(air) > 2 ? "\n\nFollowers of Aeria:\n"+air : "") +
        "\n");
 
    return 1;
}

int
wpray(string str)
{
    object *who, *onl;
    int section, i;
    string godmet, godunmet;

    if (!present(I_CAN_CAST,TP))
    {
        NF("What ?\n");
        return 0;
    }
    NF("Pray for who?\n");
    section = TP->query_skill(SS_PATRON_ELEMENTAL);
    if (!str || str == "")
        return 0;
    who = parse_this(str, "[for] %l");
    if (!sizeof(who)) return 0;

    /* Find onlookers */ 
    onl = FILTER_LIVE(all_inventory(environment(TP))); 
    onl -= ({TP}); 
    onl -= who; 

    actor("You pray for",who);
    
    for (i = 0; i < sizeof(who); i++)
    {   
        who[i]->catch_msg("You feel the presence of "+
               el_desc(who[i], section) + " as "+TP->query_the_name(who[i]) + 
               " prays for " + ((sizeof(who) == 1) ? 
               "your well being" : 
                ("the well being of " + group_desc(who[i], who, 0))) +
               ".\n");
       
    }

    for (i = 0; i < sizeof(onl); i++)  
        onl[i]->catch_msg("You feel the presence of " + 
               el_desc(onl[i], section) + " as " + 
                 TP->query_the_name(onl[i]) + " prays for the well " + 
                 "being of " + group_desc(onl[i], who, 0) + ".\n"); 

    return 1;
}

int
wprepare()
{
    int who;
    who = TP->query_skill(SS_PATRON_ELEMENTAL);
    
    switch (who)
    {
        case FIRE_FLAG:
            write("You murmur a prayer to Lord Pyros in preparation "+
                "of your next battle.\n");
            all(" murmurs a prayer under "+MY+" breath in preparation "+
                "of "+MY+" next battle.");
            break;
        case EARTH_FLAG:
            write("You murmur a prayer to Lady Gu in preparation "+
                "of your next battle.\n");
            all(" murmurs a prayer under "+MY+" breath in preparation "+
                "of "+MY+" next battle.");
            break;
        case WATER_FLAG:
            write("You murmur a prayer to Lord Diabrecho in preparation "+
                "of your next battle.\n");
            all(" murmurs a prayer under "+MY+" breath in preparation "+
                "of "+MY+" next battle.");
            break;
        default:
            write("You murmur a prayer to Lady Aeria in preparation "+
                "of your next battle.\n");
            all(" murmurs a prayer under "+MY+" breath in preparation "+
                "of "+MY+" next battle.");
            break;
    }
    return 1;
}


int
wlisten(string str)
{
    string element;

    element = str;
    if (!str)
    {
        notify_fail("Listen to what?  Air/Fire/Water/Earth perhaps?\n");
        return 0;
    }
    switch (element)
    {
        case "earth":
            write("You listen attentively to the rumble of a distant earthquake.\n");
            all(" listens attentively to the rumble of a distant earthquake.");
            break;
        case "water":
            write("You listen attentively to the hum of waves.\n");
            all(" listens attentively to the hum of waves.");
            break;
        case "air":
            write("You listen attentively to the whispers of the wind.\n");
            all(" listens attentively to the whispers of the wind.");
            break;
        case "fire":
            write("You listen attentively to the crackling flame.\n");
            all(" listens attentively to the crackling flame.");
            break;
        default:
            notify_fail("Listen to what?  Earth/Air/Fire/Water perhaps?\n");
            return 0;
            break;
    }
    return 1;
}


int
wscoff(string str)
{
    object *who;
    NF("Scoff at who?\n");
    if(!str || str == "")
        return 0;
    
    who = parse_this(str, " %l");
    if (!sizeof(who)) return 0;
    if (is_worship(who[0]))
    {
        NF("You can't scoff at an Elemental Worshipper!\n");
        return 0;
    }
    actor("You scoff at",who," for believing in the power of such a minor diety.");
    target(" scoffs at you for believing in the power of such a "+
        "minor diety.",who);
    all2actbb(" scoffs at",who,".");
    return 1;
}

int
wsilence()
{
    write("You motion for a moment of silence.\n");
    all(" raises "+MY+" hand and calls for a moment of silence.");
    return 1;
}

int
wsmile(string str)
{
    object *who;
    NF("Smile at who?\n");
    if (!str || str == "")
    {
        write("You smile confidently about your allies.\n");
        all(" smiles confidently, knowing "+HE+" has "+
            "such powerful allies to aid "+HIM+".");
        return 1;
    }
    who = parse_this(str, " %l");
    if (!sizeof(who)) return 0;
    actor("You smile confidently at",who);
    target(" smiles confidently at you, knowing "+HE+
        " has such powerful allies to aid "+HIM+".",who);
    all2actbb(" smiles confidently at",who,", knowing that "+
        HE+" has such powerful allies to aid "+HIM+".");
    return 1;
}

int
wstare(string str)
{
    object *who;
    int section;

    section =TP->query_skill(SS_PATRON_ELEMENTAL);

    NF("Stare at who?\n");
    if (!str || str == "")
        return 0;
    
    if (environment(TP)->query_prop(ROOM_I_INSIDE))
    {
        NF("You cannot use your Elemental stare indoors.\n");
        return 0;
    }

    who = parse_this(str, "[at] %l");
    if (!sizeof(who)) return 0;

    switch (section)
    {
        case FIRE_FLAG:
            actor("The temperature starts rising as you stare angrily "+
                "at",who,".");
            target(" stares angrily at you.\nYour skin temperature "+
                "suddenly begins to rise, almost burning you, then "+
                "returns to normal.",who);
            all2actbb(" stares angrily at",who,".  Their skin temperature "+
                "suddenly beings to rise, almost burning them, then "+
                "returns to normal.");
            break;
        case EARTH_FLAG:
            actor("The earth starts rumbling as you stare angrily at",who,".");
            target(" stares angrily at you.\nThe ground beneath your feet "+
                "begins to rumble for a moment but quickly calms.",who);
            all2actbb(" stares angrily at",who,".  The ground beneath "+
                "their feet begins to rumble for a moment, then "+
                "quickly calms.");
            break;
        case AIR_FLAG:
            actor("The wind starts picking up speed as you stare angrily "+
                "at",who,".");
            target(" stares angrily at you.\nSuddenly a gust of wind almost "+
                "knocks you over.",who);
            all2actbb(" stares angrily at",who,".  Suddenly a gust of "+
                "wind knocks them over.");
            break;
        default:
            actor("The sky darkens and it begins raining on",who," as you "+
                "stare angrily at them.");
            target(" stares angrily at you.\nSuddenly the sky darkens and "+
                "it begins raining on you for a brief moment.  The rain "+
                "stops and the sky returns to normal.",who);
            all2actbb(" stares angrily at",who,".  Suddenly the sky "+
                "darkens and it begins raining on them for a brief moment.  "+
                "The rain stops and the sky returns to normal.");
            break;
    }
    return 1;
}

void
wsummon3(object who)
{
    int section;
    section = who->query_skill(SS_PATRON_ELEMENTAL);
    set_this_player(who);

    switch (section)
    {
        case FIRE_FLAG:
            write("The flames begin to swirl around you quickly, "+
                "then fade away leaving no trace they were ever here.\n");
            tell_room(environment(who),"The flames begin to quickly "+
                "swirl around "+HIM+
                ", then fade away leaving no trace they were ever "+
                "here.\n",who);
            break;
        case EARTH_FLAG:
            write("The ground stops trembling, "+
                "returning everything back to normal.\n");
            tell_room(environment(who),"The ground suddenly stops "+
                "trembling, returning everything back to normal.\n",who);
            break;
        case WATER_FLAG:
            write("As quickly as it came, the rain stops and the "+
                "clouds disappear.\n");
            tell_room(environment(who),"As quickly as it came, "+
                "the rain stops and the clouds disappear.\n",who);
            break;
        default:
            write("The funnel shrinks into "+
                "nothing and the winds calm to normal.\n");
            tell_room(environment(who),"The funnel "+
                "shrinks into nothing and the winds calm to normal.\n",who);
            break;
    }
}

void
wsummon2(object who)
{
    int section;
    section = who->query_skill(SS_PATRON_ELEMENTAL);
    set_this_player(who);
    
    switch (section)
    {
        case FIRE_FLAG:
            write("A ring of flames arises around your feet as you "+
                "call upon the powers of Lord Pyros.  The flames "+
                "surge around you, embracing your body, filling "+
                "you with warmth and power.\n");
            tell_room(environment(who),"A ring of flames arises "+
                "around the feet of "+
                QTNAME(who)+" as "+HE+" chants.  The flames "+
                "surge around "+HIM+", embracing "+MY+" body.\n",who);
            break;
        case EARTH_FLAG:
            write("The ground beneath your feet begins to rumble as you "+
                "call upon the powers of Lady Gu.  The vibrations "+
                "from the ground soothe you, re-energizing your "+
                "strength and power.\n");
            tell_room(environment(who),"The ground beneath your feet "+
                "begins to rumble as "+
                QTNAME(who)+" chants.  You are almost forced to the "+
                "ground by the tremours below you.  "+QCTNAME(who)+
                " almost appears to be laughing, seemingly uneffected "+
                "by everything happening.\n",who);
            break;
        case WATER_FLAG:
            write("Clouds form around you as you call upon the powers "+
                "of Lord Diabrecho.  Rain begins to fall from the "+
                "clouds, splashing on your face and feet.  Listening "+
                "carefully, you hear the voice of Lord Diabrecho "+
                "chanting, filling you with strength and power.\n");
            tell_room(environment(who),"Clouds quickly form around "
                +QTNAME(who)+" as "+
                HE+" chants.  Rain begins to fall from the clouds, "+
                "splashing at your feet.  Listening carefully, you "+
                "can almost hear the lull of the ocean waves in the "+
                "patter of the rain hitting the ground.\n",who);
            break;
        default:
            write("Strong winds begin to blow as you "+
                "call upon the powers of Lady Aeria.  A large "+
                "funnel of air begins to form before you, rising "+
                "up into the sky.  It dances around you, restoring "+
                "your strength and power.\n");
            tell_room(environment(who),"Strong winds begin to blow as "+
                QTNAME(who)+
                " chants.  A large funnel of air begins to form "+
                "before "+HIM+", rising up into the sky.  It dances "+
                "around "+HIM+ ", almost playfully.\n",who);
            break;
    }
    wsummon_id=set_alarm(4.0,0.0,&wsummon3(who));
}

int
wsummon()
{
    if (!present(I_CAN_CAST,TP))
    {
        NF("What ?\n");
        return 0;
    }

    if (environment(TP)->query_prop(ROOM_I_INSIDE))
    {
        NF("You cannot summon the Elementals indoors!\n");
        return 0;
    }

    if (environment(TP)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        NF("You cannot summon the Elementals underwater!\n");
        return 0;
    }

    if (environment(TP)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
    {
        NF("You cannot summon the Elementals while in water!\n");
        return 0;
    }
    
    if (get_alarm(wsummon_id))
    {
        NF("You are already summoning forth the power of the Elementals!\n");
        return 0;
    }

    write("You begin to murmur a strange incantation.\n");
    tell_room(environment(TP),QCTNAME(TP)+" begins to murmur "+
        "a strange incantation.\n",TP);
    
    wsummon_id=set_alarm(2.0,0.0,&wsummon2(TP));
    return 1;
}

int
wvictory()
{
    int who;
    who = TP->query_skill(SS_PATRON_ELEMENTAL);
    
    switch (who)
    {
        case FIRE_FLAG:
            write("You close your eyes and bow your head in thanks "+
                "to Lord Pyros for your victory.\n");
            all(" closes "+MY+" eyes and bows "+MY+" head in thanks "+
                "to Lord Pyros for "+MY+" victory.");
            break;
        case EARTH_FLAG:
            write("You close your eyes and bow your head in thanks "+
                "to Lady Gu for your victory.\n");
            all(" closes "+MY+" eyes and bows "+MY+" head in thanks "+
                "to Lady Gu for "+MY+" victory.");
            break;
        case WATER_FLAG:
            write("You close your eyes and bow your head in thanks "+
                "to Lord Diabrecho for your victory.\n");
            all(" closes "+MY+" eyes and bows "+MY+" head in thanks "+
                "to Lord Diabrecho for "+MY+" victory.");
            break;
        default:
            write("You close your eyes and bow your head in thanks "+
                "to Lady Aeria for your victory.\n");
            all(" closes "+MY+" eyes and bows "+MY+" head in thanks "+
                "to Lady Aeria for "+MY+" victory.");
            break;
    }
    return 1;
}

mapping
query_cmdlist()
{
    return ([
    "wbless" : "wbless",
    "wchant" : "usay",
    "wch" : "usay",
    "wcharge" : "wcharge",
    "wconvert" : "wconvert",
    "wcurse" : "wcurse",
    "weyes" : "weyes",
    "wfare" : "wfarewell",
    "wfarewell" : "wfarewell",
    "wgaze" : "wgaze",
    "wgrant" : "wgrant",
    "whail" : "worhail",
    "help" : "w_help",
    "wjoy" : "wjoy",
    "wjpray" : "wjpray",
    "wkneel" : "wkneel",
    "wlaugh" : "wlaugh",
    "wlist" : "worlist",
    "wlisten" : "wlisten",
    "wpray" : "wpray",
    "wprepare" : "wprepare",
    "wscoff" : "wscoff",
    "wsilence" : "wsilence",
    "wsmile" : "wsmile",
    "wstare" : "wstare",
    "wsummon" : "wsummon",
    "wvictory" : "wvictory",
    ]);
}
