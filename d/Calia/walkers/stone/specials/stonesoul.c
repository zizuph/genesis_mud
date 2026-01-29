
 /* Stonewalkers soul  */
 /* April 7th, 1998    */
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
#include STONE_HEADER
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

string *stone_apprentices = ({});
mapping mentors = ([ ]);

string
get_soul_id()
{
    seteuid(getuid());
    return "Stonewalkers of Thalassia";
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
is_stone(object living)
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
    "wbless <player(s)>            - bless <player(s)> in the name of Aeria.\n"+
    "wembrace (<how>) <player(s)>  - open your arms and embrace <player(s)>\n"+
    "                                (<how>).\n"+
    "wfare(well) <player(s)>       - bid farewell to <player(s)>.\n"+
    "wgaze (<how>) (<player(s)>)   - gaze (<how>) (at <player(s)>).\n"+
    "wglare (<player(s)>)          - glare around/(at <player(s)>) in a\n"+
    "                                foul mood.\n"+
    "wgrin (<how>)                 - grin (<how>) while playing with minute\n"+
    "                                bolts of lighting.\n"+
    "whail <player(s)>             - hail <player(s)> in an ancient sign\n"+
    "                                of greetings.\n"+
    "wlaugh (<how>) (<players(s)>) - laugh (<how>) (at <player(s)>).\n" +
    "wplay                         - play with a small whirlwind.\n"+
    "wpray                         - pray to Aeria to guide you forth in your\n" +
    "                                journies.\n"+
    "wrage                         - contort your face angrily for a moment.\n"+
    "wrise                         - rise to full height, showing your\n"+
    "                                god(dess)like beauty and majesty.\n"+
    "wshrug                        - give a shrug, not caring one way or\n"+
    "                                the other.\n"+
    "wsmile (<how>) (<player(s)>)  - smile (<how>) (at <player(s)>).\n" +
    "ws(peak)                      - speak to another Walker in the\n"+
    "                                Ancient Elemental Tongue.\n"+
    "wstretch                      - stretch out your body and rest.\n"+
    "help wind(walker)             - a list of all help wind(walker) options.\n"+
    "wch(ant) <message>            - chant <message> in ancient mantras\n"+
    "                                (NOTE: This language is understood\n"+
    "                                       by the Elemental Worshippers\n"+
    "                                       as well as Walkers.\n" +
    "\n"+
    "\n"+
    "You can also use the following commands:\n"+
    "wwho                          - get a list of Windwalkers in the Realms.\n"+
    "walkers                       - get a list of Walkers in the Realms.\n"+
    "wchoose <player>              - select <player> to be your apprentice.\n" +
    "spells                        - get a list of your current spells.\n"+
    "\n");
    return 1;
}

int
wbless(string str)
{
    object *oblist;

    if (!str || str == "")
    {
        NF("Bless whom in the name of Aeria?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NF("Bless whom in the name of Aeria?\n");
        return 0;
    }

    actor("You bless",oblist," saying `May the Air never send storms "+
        "across your path.'");
    all2act(" blesses",oblist," and says `May the Air never send storms "+
        "across your path.'");
    target(" blesses you saying `May the Air never send storms across "+
        "your path.'",oblist);
    return 1;
}

int
wchoose(string str)
{
    object *who;
    object chosen;
    string my_name, apprentice;

    setuid();
    seteuid(getuid());
    COUNCIL_CODE->load_me();
    restore_object(COUNCIL);

    if (!(COUNCIL_CODE->is_stone_elder(TP->query_real_name())))
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

    if (is_stone(who[0]))
    {
        NF("That person is already a Stonewalker!\n");
        return 0;
    }

    if (!is_worship(who[0]))
    {
        NF("That person is not a Worshipper of the Elementals!\n");
        return 0;
    }

    if (present("_stone_chosen_", who[0]))
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
    stone_apprentices += ({ apprentice });
    (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
        capitalize(my_name) + " has selected "+capitalize(apprentice) +
        " as "+TP->query_possessive()+" apprentice of Gu.\n");
    save_object(COUNCIL);

    setuid();
    seteuid(getuid());
    chosen=clone_object(STONE_OBJECTS+"chosen");
    chosen->move(who[0],1);
    return 1;
}

int
wembrace(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "closely", 1);

    oblist = parse_this(how[0], "[the] %l");

    if (!sizeof(oblist))
    {
        NF("Embrace whom [how]?\n");
        return 0;
    }

    actor("You open your arms and embrace",oblist,how[1]+", surrounding "+
        "them with mild breezes.");
    all2act(" opens "+MY+" arms and embraces",oblist, how[1]+", surrounding "+
        "them with mild breezes.",how[1]);
    target(" opens "+MY+" arms and embraces you"+how[1]+", surrounding "+
        "you with mild breezes.",oblist,how[1]);
    return 1;
}

int
wfarewell(string str)
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
wgaze(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "restlessly", 0);

    if (!stringp(how[0]))
    {
        write("You gaze"+how[1]+" at the dancing clouds and begin "+
            "shifting in place, conveying the image of unpredictability "+
            "and moodiness.\n");
        all(" gazes"+how[1]+" at the dancing clouds and begins shifting "+
            "in place, conveying the image of unpredictability and "+
            "moodiness.",how[1]);
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
        "eye and suddenly feel your thoughts swirling inside of your head "+
        "making it hard to concentrate.  A sharp pain spreads from behind "+
        "your eyes.  Just as you feel you are about to faint, you tremble, "+
        "lower your gaze, and the pain subsides.",oblist,how[1]);
    return 1;
}

int
wglare(string str)
{
    object *who;

    if (!str || str == "")
    {
       write("You glare around, obviously in a foul mood.\n");
       all(" glares around, obviously in a foul mood.");
       return 1;
    }

    who = parse_this(str, "[at] [the] %l");

    if (!sizeof(who))
    {
        NF("Glare at whom?\n");
        return 0;
    }

    actor("You glare at",who);
    all2act(" glares at",who);
    target(" glares at you, obviously in a foul mood.  You silently "+
        "pray he does not take it out on you.",who);
    return 1;
}

int
wgrin(string str)
{
    string *how;
    object *oblist;

    how = parse_adverb_with_space(str, "absentmindedly", 0);

    if (!stringp(how[0]))
    {
        write("You grin"+how[1]+", dancing minute bolts of lightning "+
            "between your fingertips.\n");
        all(" grins"+how[1]+", dancing minute bolts of lighting "+
            "between "+MY+" fingertips.");
        SOULDESC("grinning"+how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Grin [how] at whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        actor("You grin"+how[1]+" at",oblist);
        all2act(" grins"+how[1]+" at",oblist,0,how[1]);
        target(" grins"+how[1]+" at you and you feel a small jolt "+
            "pass through your body causing your hair to stand "+
            "on end.",oblist, how[1]);
        return 1;
    }

    actor("You gaze"+how[1]+" at",oblist,", sending a small jolt "+
        "through "+oblist[0]->query_objective()+" and causing "+
        oblist[0]->query_possessive()+" hair to stand on end.");
    all2act(" gazes"+how[1]+" at",oblist," causing "+
        oblist[0]->query_possessive()+" hair to stand on end.", how[1]);
    target(" gazes"+how[1]+" at you, sending a small jolt through you that "+
        "causes your hair to stand on end.",oblist,how[1]);
    return 1;
}

int
whail(string str)
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
wlaugh(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "softly", 0);

    if (!stringp(how[0]))
    {
        write("You laugh"+how[1]+" and the wind carries your laughter "+
            "throughout the area.\n");
        all(" laughs"+how[1]+", and the wind carries "+MY+" laughter "+
            "throughout the area.  The beautiful sound strikes a chord "+
            "in your soul.",how[1]);
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
    all2act("  laughs"+how[1]+" at",oblist,".  The air around you begins "+
        "to emit a thunderous echo then becomes quiet once again.",how[1]);
    target(" laughs"+how[1]+" at you.  The air around you begins to "+
       "emit a thunderous echo that seems to eat away at your very soul!  "+
       "As suddenly as it began, the echoing stops.",oblist,how[1]);
    SOULDESC("laughing"+how[1]);
    return 1;
}

int
wplay()
{
    if ((environment(TP)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) || (environment(TP)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER))
    {
        write("You conjure up a small whirlwind and playfully let it dance "+
            "around in the water.\n");
        all(" conjures up a small whirlwind and playfully lets it dance "+
            "around in the water.");
        return 1;
    }

    write("You conjure up a small whirlwind and playfully let it dance "+
        "around on the ground, stirring up dust and debris where it "+
        "passes.\n");
    all(" conjures up a small whirlwind and playfully lets it dance "+
       "around on the ground, stirring up dust and debris wherever it "+
       "passes.");
    return 1;
}

int
wpray()
{
    write("You look up into the sky and call out for the power of "+
        "Lady Aeria to guide you forth.\n");
    all(" looks up into the sky and calls out, \"Aeria, "+
       "Ruler of the Winds, Elemental of Air, guide me forth in my "+
       "journies.\n");
    return 1;
}

int
wrage()
{
    write("You contort your face in violent anger for a few moments.\n");
    all("'s face contorts in violent anger, but the fit passes in a "+
        "few moments and "+TP->query_pronoun()+" appears as serene as ever.");
    return 1;
}

int
wrise()
{
    string p_sex;
    if (TP->query_gender() == G_FEMALE)
        p_sex = "goddess";
    else
        p_sex = "god";

    write("You rise to your full height and show everyone your "+p_sex+
        "like beauty and majesty.\n");
    all(" rises up to "+MY+" full height and as your eyes are drawn to "+
        TP->query_objective()+", you are humbled by "+MY+" "+p_sex+
        "like beauty and majesty.");
    return 1;
}

int
wshrug()
{
    write("You shrugs, not caring one way or the other.\n");
    all(" shrugs, not caring one way or the other.\n");
    return 1;
}

int
wsmile(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "amusedly", 0);

    if (!stringp(how[0]))
    {
        write("You smile"+how[1]+".\n");
        all(" smiles"+how[1]+" causing you to glance over your shoulder "+
            "uneasily.",how[1]);
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
    target(" smiles"+how[1]+" at you, causing you to glance over your "+
        "shoulder uneasily.",oblist,how[1]);
    SOULDESC("smiling"+how[1]);
    return 1;
}

int
wspeak(string msg)
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
            oblist[i]->catch_msg(QCTNAME(TP) + " says in the Ancient Elemental Tongue : " +
            msg + "\n");
            else
                oblist[i]->catch_msg(QCTNAME(TP) + " speaks in a language "+
                "you do not understand.\n");
        }
    }
    return 1;
}

int
wstretch()
{
    write("You stretch your body out and assume a resting position, "+
        "floating a few feet up in the air.\n");
    all(" stretches out " + MY+ " body and assumes a resting position, "+
        "floating a few feet up in the air.\n");
    return 1;
}

int
list_stones()
{
    string g_name, g_short;
    int i;
    int cnt = 0;
    object *list;

    write("The following Stonewalkers are in the Realms:\n");
    list = users();
    for (i=0; i < sizeof(list); i++)
    {
       if (!is_stone(list[i]))
          continue;

       g_name = capitalize(list[i]->query_real_name());

       if(!list[i]->query_wiz_level())
       {
          g_short = list[i]->query_stone_walker_title();
          write("- " + g_name + " " + g_short + "\n");
          cnt++;
       }
       if(list[i]->query_wiz_level())
       {
          g_short = list[i]->query_title();
          write("- " + g_name + " " + g_short + "\n");
          cnt++;
       }
    }
   
    if (cnt < 2)
    {
        write("There is only one Stonewalker in the Realms.\n");
        return 1;
    }
    write("There are now "+cnt+" Stonewalkers in the Realms.\n");
    return 1;
}

int
list_walkers()
{
    string g_name, g_short;
    int i;
    int cnt = 0;
    object *list;

    write("The following Walkers are in the Realms:\n");
    list = users();
    for (i=0; i < sizeof(list); i++)
    {
        if (!is_walker(list[i]))
            continue;

        g_name = capitalize(list[i]->query_real_name());

            g_short = list[i]->query_title();
            write("- "+g_name+" "+g_short+"\n");
            cnt++;
    }
    if (cnt < 2)
    {
        write("There is only one Walker in the Realms.\n");
        return 1;
    }
    write("There are now "+cnt+" Walkers in the Realms.\n");
    return 1;
}

int
w_help(string str)
{
    if (!str)
        return 0;

    if (str == "windwalker" || str == "wind" || str == "windwalkers")
    {
        write("You may get help on the following:\n\n"+
            "    help wind(walker) titles - a list of windwalker titles\n"+
            "    help wind(walker) spells - a list of windwalker spells\n"+
            "    help wind(walker) emotes - a list of windwalker emotes\n"+
            "    help wind(walker)        - this list\n"+
            "\n");
        return 1;
    }

    if (str == "windwalker emotes" || str == "wind emotes")
    {
        cmd_list();
        return 1;
    }

    if (str == "windwalker titles" || str == "wind titles")
    {
        write("There are the following titles in the Windwalkers:\n\n"+
            "    <title> of the Primitive Ring of Air\n"+
            "    <title> of the Obscure Ring of Air\n"+
            "    <title> of the Outer Ring of Air\n"+
            "    <title> of the Inner Ring of Air\n"+
            "    <title> of the Esoteric Sphere of Air\n"+
            "    <title> of the Harmonic Sphere of Air\n"+
            "    <title> of the Transcendent Sphere of Air\n"+
            "    <title> of the Ancient Sphere of Air\n"+
            "    <title> of the Divine Realm of Air\n"+
            "    Windwalker of Legends, Arch-Angel of Storms\n\n"+
            "<title> is broken down into the following:\n\n"+
            "    Initiate, Novice, Disciple, Master\n\n"+
            "Council members can be recognized by having the additional "+
            "title of 'Harbinger of Aeria' added to their own.\n\n"+
            "Council assistants can be recognized by having the additional "+
            "title of 'Emmissary of Aeria' added to their own.\n\n"+
            "\n");
        return 1;
     }

    if (str == "windwalker spells" || str == "wind spells")
    {
        write("\n\n"+
              "Spells of the Primitive Ring:       Anemos, Gsechon\n"+
              "Spells of the Obscure Ring:         Tuphlono, Aernero\n"+
              "Spells of the Outer Ring:           Aertrophia\n"+
              "Spells of the Inner Ring:           Therapeaou, Ochetos, Pichno\n"+
              "Spells of the Esoteric Sphere:      Upala, Nuchta\n"+
              "Spells of the Harmonic Sphere:      Topi, Aulaki\n"+
              "Spells of the Transcendent Sphere:  Pleko, Photostepsanos\n"+
              "Spells of the Ancient Sphere:       Antidroaera\n"+
              "Spells of the Divine Realm:         Stoiecheio, Aeras\n"+
              "Spells of the Legendary Domain:     Diarroae, Agios, Lepida\n\n"+
              "If you have earned the use of the spell, you may get help "+
              "on it by doing 'help wind <spellname>'.  If you have not "+
              "earned the use of it, you will get no help on it.\n"+
              "\n");
        return 1;
    }

    if (str == "windwalker anemos" || str == "wind anemos")
    {
        write("Anemos - Wind Speak :   With this spell you will be "+
            "able to send a message to anyone in the Realms.  You will "+
            "need a feather to sacrifice.\n");
        return 1;
    }

    if (str == "windwalker gsechon" || str == "wind gsechon")
    {
        write("Gsechon - Name Forget :   With this spell you will be "+
            "able make a target forget your identity by burning it from "+
            "their minds.  For this you will require a black feather "+
            "and an ice crystal to sacrifice.\n");
        return 1;
    }

    if (str == "windwalker tuphlono" || str == "wind tuphlono")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TWO_FLAG)
        {
            write("Tuphlono - Tearing Eyes :  This will leave your target "+
                "blinded for a short time by causing their eyes to begin to "+
                "tear uncontrollably.  You will require the herb "+
                "laminaria and a water vial for this spell.\n");
            return 1;
        }
    }
        
    if (str == "windwalker aernero" || str == "wind aernero")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TWO_FLAG)
        {
            write("Aernero - Spirits :  This will raise the alcohol "+
                "level in the blood of the target.  You may use this on "+
                "yourself if you wish to do so.  You must be under the "+
                "effects of the nero potion for it to work, and it "+
                "may be cast until the effects of the potion wear off.  "+
                "The nero potion is mixed with poison ivy and a "+
                "water vial.\n");
            return 1;
        }
    }

    if (str == "windwalker aertrophia" || str == "wind aertrophia")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_THREE_FLAG)
        {
            write("Aertrophia - Peace :  Once this spell is cast, all fighting "+
                "in your location will cease immediately.  Be warned, "+
                "it can be started right away, this merely stops the "+
                "current conflicts.  You must be under the effects of "+
                "the aertrophia potion for it to work, and may be cast until "+
                "the effects of the potion wear off.  The aertrophia potion "+
                "is mixed with elkhorn kelp and a water vial.\n");
            return 1;
        }
    }

    if (str == "windwalker therapeaou" || str == "wind therapeaou")
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

    if (str == "windwalker pichno" || str == "wind pichno")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FOUR_FLAG)
        {
            write("Pichno - Wall Of Air :  This spell will block the "+
                "selected exit with a wall of blowing debris.  Those who "+
                "have some resistance to electricity and those who worship "+
                "Lady Aeria may pass through this wall unhindered.  All "+
                "others will not be able to pass this barrier.  You may "+
                "have more than one of these barriers in a place at any "+
                "time.  They will only last a short time.  You must be "+
                "under the influence of the pichno potion for this spell "+
                "to work.  You may continue to cast this spell until the "+
                "effects of the potion wear off.  The pichno potion is "+
                "mixed with the herb fucus, and ice crystal and a water "+
                "vial.\n");
            return 1;
        }
    }

    if (str == "windwalker ochetos" || str == "wind ochetos")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FOUR_FLAG)
        {
            write("Ochetos - Air Armour :  This spell will encompass "+
                "the target in a suit of armour made from solid air.  This "+
                "armour will block some damage inflicted upon the target.  "+
                "You may cast this on yourself if you so desire to do so.  "+
                "You must be under the influence of the armour of ochetos "+
                "potion as well as have a spotted feather for "+
                "this spell to work and you can continue to cast it until "+
                "the effects of the potion wear off and you have spotted "+
                "feathers.  To mix the ochetos potion you need bull kelp, "+
                "and a water vial.\n");
            return 1;
        }
    }

    if (str == "windwalker upala" || str == "wind upala")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FIVE_FLAG)
        {
            write("Upala - Air Blast :  The first, and weakest of "+
                "the offensive spells, this will do a small amount of "+
                "damage to the target by sending a blast of air at "+
                "them.  This spell will initiate combat.  To use "+
                "this spell, you must be under the influence of the "+
                "upala potion and have a black feather and you may "+
                "continue to cast it until the "+
                "effects of the potion wears off and you have black "+
                "feathers.  To mix the upala potion you will require "+
                "an ice crystal and a powerful alcohol (moonshine).\n");
            return 1;
        }
    }

    if (str == "windwalker nuchta" || str == "wind nuchta")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FIVE_FLAG)
        {
            write("Nuchta - Darkness :  This spell will make the current "+
                "room dark.  This spell can only be used indoors, and will "+
                "last for a short period of time.  You will require a "+
                "black feather and drakeroot to sacrifice for this spell.\n");
            return 1;
        }
    }

    if (str == "windwalker topi" || str == "wind topi")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SIX_FLAG)
        {
            write("Topi - Lightning Bolt :  The second offensive "+
                "spell you recieve is a bit more powerful than its predecesor "+
                "as it sends a lightning bolt at its target.  This bolt "+
                "will explode when it contacts its intended victim.  You "+
                "will need to be under the influence of the topi potion "+
                "for this spell to work and you may continue to cast it "+
                "until the effects of the potion wear off.  The topi "+
                "potion is mixed with coral alga and a powerful "+
                "alcohol (moonshine).\n");
            return 1;
        }
    }

    if (str == "windwalker aulaki" || str == "wind aulaki")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SIX_FLAG)
        {
            write("Aulaki - Far Sight :  This spell will grant "+
                "the target the ability to see into another place in "+
                "the realms so long as they know someone who is in that "+
                "place.  You must be under the influence of the aulaki "+
                "potion to be able to cast it successfully and you can "+
                "continue to cast it until the effects of the potion wear "+
                "off.  The aulaki potion is mixed with sargassum and a "+
                "water vial.\n");
            return 1;
        }
    }

    if (str == "windwalker pleko" || str == "wind pleko")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SEVEN_FLAG)
        {
            write("Pleko - Hurricane :  This spell sends a hurricane "+
                "force wind at its target, knocking "+
                "them out of the current area you are in.  You will "+
                "need to be under the influence of the pleko potion for "+
                "it to be cast and you can continue to cast it until the "+
                "effects of the potion wear off.  To mix the pleko potion "+
                "you will need sea lettuce and a strong alcohol (moonshine).\n");
            return 1;
        }
    }

    if (str == "windwalker photostepsanos" || str == "wind photostepsanos")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SEVEN_FLAG)
        {
            write("Photostepsanos - Invisibility :  The target of this spell "+
                "will suddenly become surrounded by winds that will conceal "+
                "them from onlookers.  In reality the target will become "+
                "invisible for a short period of time.  You may cast "+
                "this spell on "+
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

    if (str == "windwalker antidroaera" || str == "wind antidroaera")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_EIGHT_FLAG)
        {
            write("Antidroaera - Resist Lightning :  The target of this spell "+
                "will have their skin enchanted so they will become "+
                "magically resistant to lightning and air magic.  You may "+
                "cast this upon yourself.  You must be under the effects "+
                "of the antidroaera potion to cast this spell and can "+
                "continue to cast it until the potion wears off.  To mix "+
                "the antidroaera potion you will require the herb sargassum, "+
                "an ice crystal, and a water vial.\n");
            return 1;
        }
    }

    if (str == "windwalker stoiecheio" || str == "wind stoiecheio")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_NINE_FLAG)
        {
            write("Stoiecheio - Elemental Form :  Once this spell is "+
                "successfully cast, you will be granted the form of an "+
                "air elemental.  This form will disguise you so no person "+
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

    if (str == "windwalker aeras" || str == "wind aeras")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_NINE_FLAG)
        {
            write("Aeras - Whisper Wind :  This spell will allow you "+
                "to send a message to an entire area that someone you "+
                "know is located in.  Everyone located in that area will "+
                "hear the message as a voice originating from the winds "+
                "themself.  To cast this spell successfully, you will "+
                "need to be under the effects of the aeras potion, which "+
                "is mixed with the herb salt wort and a powerful alcohol "+
                "(moonshine).\n");
            return 1;
        }
    }

    if (str == "windwalker diarroae" || str == "wind diarroae")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TEN_FLAG)
        {
            write("Diarroae - Slow :  This spell shall slow the target "+
                "causing them to move much slower and therefore fight "+
                "much worse than they normally can.  The effects of the "+
                "spell shall last only a short time, so use it wisely.  "+
                "You will need to be under the influence of the diarroae "+
                "potion to cast it and you may continue to cast it until "+
                "the effects of the potion wear off.  The diarroae potion "+
                "is mixed with cord grass, an ice crystal and a powerful "+
                "alcohol (moonshine).\n");
            return 1;
        }
    }

    if (str == "windwalker agios" || str == "wind agios")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TEN_FLAG)
        {
            write("Agios - Fly To Shrine :  Upon the successful "+
                "casting of this spell, you shall be flown to the Elemental "+
                "Shrine entrance.  Once you are finished your business within "+
                "the Shrine, you only need enter the archway to be returned to "+
                "the place where you cast the spell.  There are some areas in "+
                "the realms where this spell will not work.  You will "+
                "require eel grass and a feather to sacrifice.\n");
            return 1;
        }
    }

    if (str == "windwalker lepida" || str == "wind lepida")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TEN_FLAG)
        {
            write("Lepida - Paralysis :  Upon the successful casting of "+
                "this spell, your target will be paralyzed.  They will not "+
                "be able to fight or move.  They may be able to cast spells if "+
                "the spell they are trying to cast only requires a verbal "+
                "component.  You must also be under the effects of the lepida "+
                "potion.  This spell may be cast until the effects of the "+
                "lepida potion.  The lepida potion is mixed "+
                "with a water vial, fireweed, an ice crystal, and a "+
                "powerful alcohol (moonshine).\n");
            return 1;
        }
    }

    return 0;
}

mapping
query_cmdlist()
{
    return ([
    "wbless"    : "wbless",
    "wchoose"   : "wchoose",
    "wembrace"  : "wembrace",
    "wfare"     : "wfarewell",
    "wfarewell" : "wfarewell",
    "wgaze"     : "wgaze",
    "wglare"    : "wglare",
    "wgrin"     : "wgrin",
    "whail"     : "whail",
    "wknee"     : "wknee",
    "wlaugh"    : "wlaugh",
    "wplay"     : "wplay",
    "wpray"     : "wpray",
    "wrage"     : "wrage",
    "wrise"     : "wrise",
    "wshrug"    : "wshrug",
    "wsmile"    : "wsmile",
    "ws"        : "wspeak",
    "wspeak"    : "wspeak",
    "wstretch"  : "wstretch",
    "wch"       : "usay",
    "wchant"    : "usay",
    "wwho"      : "list_stones",
    "walkers"   : "list_walkers",
    "help"      : "w_help",
    ]);
}


