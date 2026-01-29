/* 
 * Soul for the Elemental Worshippers of Calia guild.
 * Coded by Bishop, June 2000. Based on Jaacars old work.
 *
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
#include "defs.h"
/*
#include "wlang.h"
*/

#define MY this_player()->query_possessive()
#define HE this_player()->query_pronoun()
#define HIM this_player()->query_objective()
#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))


int
query_cmd_soul()
{
    seteuid(getuid());
    return 1;
}


string
get_soul_id()
{
    seteuid(getuid());
    return "Elemental Worshippers of Calia";
}


int
cmd_list()
{
    write("You can use the following commands:\n\n" +
        "help worshippers               Get a list of all of the Worshipper help\n"+
        "                               commands\n"+
        "wbless <player>                Bless <player> in the name of the Elementals\n"+
        "wch(ant) <message>             Chant <message> in ancient mantras\n" +
        "wcharge (<target>)             Give a battle charge (and attack <target>)\n" +
        "wconvert <player>              Try to convert <player> to Elemental worship\n" +
        "wcurse <player>                Send the wrath of the Elementals upon <player>\n"+
        "weyes                          Your eyes flare with the power of your deity\n"+
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
        "wthank                         Thank your god. \n"+
        "wvictory                       Give thanks to the Elements for your victory\n"+
        "\n");
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
    if (who[0]->is_worship())
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
    if (!(who[0]->is_worship()))
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
    return 1;
}

/*

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

    members = filter(oblist, &->is_worship()); 
    nonmem = oblist - members;


//  Non-members 
    for (i = 0; i < sizeof(nonmem); i++)  
    { 
        nonmem[i]->catch_msg(TP->query_The_name(nonmem[i])+" reaches toward " +
            "you with "+ MY+" left hand open, palm facing you, in an " +
            "ancient sign of greetings.\n");
    } 

   if (sizeof(nonmem)) 
       TP->catch_msg("You hail " + group_desc(TP, nonmem, 0) +
            " in an ancient sign of greetings.\n");
//  Members  
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


//  Onlookers  

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

*/

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
/*
    if (str == "worshippers titles" || str == "worshipper titles" ||
        str == "wor titles")
    {
        title_help();
        return 1;
    }
*/

    if (str == "worshippers" || str == "worshipper" || str == "wor")
    {
        write("\nWorshipper help options\n"+
              "=======================\n\n"+
              "help worshippers         - this list\n"+
              "help worshippers emotes  - Worshippers emotes list\n"+
              "help worshippers titles  - Worshippers titles list\n");
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
    if (who[0]->is_worship())
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
        write("You smile confidently in the knowledge that the Elementals" +
            " are your allies.\n");
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
wthank(string str)
{
    object *who;
    string god;
    int section;

    NF("Thank who?\n");
    if (!str || str == "")
    {
        section = TP->query_skill(SS_PATRON_ELEMENTAL);
        switch (section)
        {
            case FIRE_FLAG:
                god = "Lord Pyros";
                break;
            case EARTH_FLAG:
                god = "Lady Gu";
                break;
            case WATER_FLAG:
                god = "Lord Diabrecho";
                break;
            default:
                god = "Lady Aeria";
                break;
        }
        write("You offer your thanks to "+god+".\n");
        tell_room(environment(TP),QCTNAME(TP)+
        " kneels briefly in a prayer of thanks to "+
        god+".\n",TP);
        return 1;
    }
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
//  "whail" : "worhail",
    "help" : "w_help",
    "wjoy" : "wjoy",
    "wkneel" : "wkneel",
    "wlaugh" : "wlaugh",
    "wlist" : "worlist",
    "wlisten" : "wlisten",
    "wpray" : "wpray",
    "wprepare" : "wprepare",
    "wscoff" : "wscoff",
    "wsilence" : "wsilence",
    "wsmile" : "wsmile",
    "wthank" : "wthank",
    "wvictory" : "wvictory",
    ]);
}