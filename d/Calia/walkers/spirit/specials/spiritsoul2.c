
 /* Spiritwalkers soul   */
 /* February 9th, 1998  */
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
#include SPIRIT_HEADER

#define MY TP->query_possessive()
#define HIM TP->query_objective()
#define HE TP->query_pronoun()
#define SOULDESC(x) (TP->add_prop(LIVE_S_SOULEXTRA, x))

string
get_soul_id()
{
    seteuid(getuid());
    return "Spiritwalkers of Thalassia";
}

int
query_cmd_soul()
{
    seteuid(getuid());
    return 1;
}

int
is_spirit(object living)
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
    "sbless <player(s)>            - bless <player(s)> in the name of Psuchae.\n"+
    "seyes (<how>) (<player(s)>)   - glare (at player(s)) angrily.\n" +
    "sfare(well) <player(s)>       - bid farewell to <player(s)>.\n"+
    "sgaze (<how>) (<player(s)>)   - gaze (<how>) (at <player(s)>).\n"+
    "sgrin (<how>) (<player(s)>)   - grin (<how>) (at <player(s)>).\n"+
    "shail <player(s)>             - hail <player(s)> in an ancient sign\n"+
    "                                of greetings.\n"+
    "shug (<how>) <player(s)>      - hug <player(s)> (<how>).\n" +
    "sknee                         - call to Psuchae for power.\n" +
    "slaugh (<how>) (<players(s)>) - laugh (<how>) (at <player(s)>).\n" +
    "sshake <player(s)>            - shake <player(s)> hand heatedly.\n" +
    "ssmile (<how>) (<player(s)>)  - smile (<how>) (at <player(s)>).\n" +
    "ssnap (<how>)                 - snap your fingers (<how>).\n" +
    "ss(peak)                      - speak to another Spiritwalker.\n"+
    "help spirit(walker)           - a list of all help spirit(walker) options.\n"+
    "\n"+
    "\n"+
    "You can also use the following commands:\n"+
    "swho                          - get a list of Spiritwalkers in the Realms.\n"+
    "schoose <player>              - select a player to be a Spiritwalker.\n" +
    "spells                        - get a list of your current spells.\n"+
    "\n");
    return 1;
}

int
sbless(string str)
{
    object *oblist;

    if (!str || str == "")
    {
        NF("Bless whom in the name of Psuchae?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NF("Bless whom in the name of Psuchae?\n");
        return 0;
    }

    actor("You bless",oblist," saying `May the shadows always surround "+
        "you but never blind you.'");
    all2act(" blesses",oblist," and says `May the shadows always surround "+
        "you but never blind you.'");
    target(" blesses you saying `May the shadows always surround you "+
        "but never blind you.'",oblist);
    return 1;
}

int
schoose(string str)
{
    object *who;
    object chosen;

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

    if (is_spirit(who[0]))
    {
        NF("That person is already a Spiritwalker!\n");
        return 0;
    }

    if (!is_worship(who[0]))
    {
        NF("That person is not a Worshipper of the Elementals!\n");
        return 0;
    }

    if (present("_spchosen_", who[0]))
    {
        NF("That person is already chosen!\n");
        return 0;
    }

    target(" places "+MY+" hands on your shoulders.  You feel "+
        "power flowing through your body.",who);
    actor("You place your hands on",who,"'s shoulder.");
    all2actbb(" places "+MY+" hands on",who,"'s shoulders.");

    setuid();
    seteuid(getuid());
    chosen=clone_object(SPIRIT_OBJECTS+"chosen");
    chosen->move(who[0],1);
    return 1;
}

int
seyes(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "angrily", 0);

    if (!stringp(how[0]))
    {
        write("You glare around"+how[1]+".\n");
        all(" glares around"+how[1]+", "+MY+" eyes seemingly absorb "+
            "the light.",how[1]);
        return 1;
    }

    oblist = parse_this(how[0],"[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Glare [how] at whom?\n");
        return 0;
    }

    actor("You glare"+how[1]+" at",oblist);
    all2act(" glares"+how[1]+" at",oblist,", "+MY+" eyes seem to absorb "+
        oblist->query_possessive()+" very soul.",how[1]);
    target(" glares"+how[1]+" at you, "+MY+" eyes seem to absorb your "+
        "very soul.",oblist, how[1]);
    return 1;
}

int
sfarewell(string str)
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
sgaze(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "intensely", 0);

    if (!stringp(how[0]))
    {
        write("You fix your eyes on an invisible point in front of "+
            "you and gaze at it"+how[1]+".\n");
        all(" fixes "+MY+" eyes on an invisible point and gazes"+
            how[1]+" at it, causing "+MY+" pupils to dialate and "+
            "turning "+MY+" eyes into black voids.",how[1]);
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
        "eye and suddenly feel you are looking into a dark void.  "+
        "A sharp pain spreads from behind your eyes and just as you feel "+
        "you are about to faint, you tremble and lower your gaze.",oblist,how[1]);
    return 1;
}

int
shail(string str)
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
shug(string str)
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

    actor("You hug",oblist,how[1]+", enveloping them in "+
        "shadow, concealing them from sight for a brief moment.");
    all2act(" hugs",oblist, how[1]+", enveloping them in "+
        "shadow, concealing them from sight for a brief moment.",how[1]);
    target(" hugs you"+how[1]+", enveloping you in shadow, "+
        "concealing you from sight for a brief moment.",oblist,how[1]);
    return 1;
}

int
sknee(string str)
{
    write("You get down on one knee and call upon the power of "+ 
        "Psuchae.\n");
    all(" gets down on one knee and calls out to Psuchae, "+
       "Ruler of the Spirits, Elemental of Shadow.");
    return 1;
}

int
slaugh(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "wickedly", 0);

    if (!stringp(how[0]))
    {
        write("You laugh"+how[1]+".\n");
        all(" laughs"+how[1]+", emmitting a thunderous echo!",how[1]);
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
    all2act("  laughs"+how[1]+" at",oblist,", emmitting a thunderous "+
        "echo.",how[1]);
    target(" laughs"+how[1]+" at you, emmitting a thunderous echo "+
       "that eats away at your very soul!",oblist,how[1]);
    SOULDESC("laughing"+how[1]);
    return 1;
}

int
sshake(string str)
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

    actor("You shake",oblist," with a cold hand.");
    all2actbb(" grasps",oblist," by the hand in a strong "+
        "shake.");
    target(" grasps your hand in a strong shake.  You recoil and "+
       "jerk back as you feel your soul being sucked into "
       +MY+" hand!",oblist);
    return 1;
}

int
sgrin(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "wickedly", 0);

    if (!stringp(how[0]))
    {
        write("You grin"+how[1]+".\n");
        all(" grins"+how[1]+".");
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
ssmile(string str)
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
sspeak(string msg)
{
    object *oblist;
    int i;
    
    if (TP->query_skill(SS_LANGUAGE) < 20)
    {
        NF("Speaking in the Ancient Tongue of Shadow " +
            "requires more training of the language skill.\n");
        return 0;
    }
    
    if (!strlen(msg))
    {
        NF("Say what in the Ancient Tongue of Shadow?\n");
        return 0;
    }
    
    if (TP->query_option(OPT_ECHO))
        write("In the Ancient Tongue of Shadow, you say: " + msg + "\n");
    else
        write("Ok.\n");

    oblist = all_inventory(environment(TP));

    for (i=0; i < sizeof(oblist); i++)
    {
        if ((living(oblist[i]) && oblist[i] != TP))
	    {
            if (((is_spirit(oblist[i]) && oblist[i]->query_skill(SS_LANGUAGE) > 22) ||
                (oblist[i]->query_skill(SS_LANGUAGE) > 70)))
            oblist[i]->catch_msg(QCTNAME(TP) + " says in the Ancient Tongue of Shadow : " +
                break_string(msg + "\n", 70));
            else
                oblist[i]->catch_msg(QCTNAME(TP) + " speaks in a language "+
                "you do not understand.\n");
        }
    }
    return 1;
}

int
list_spirits()
{
    string g_name, g_short;
    int i;
    int cnt = 0;
    object *list;

    write("The following Spiritwalkers are in the Realms:\n");
    list = users();
    for (i=0; i < sizeof(list); i++)
    {
       if (!is_spirit(list[i]))
          continue;

       g_name = capitalize(list[i]->query_real_name());

       if(!list[i]->query_wiz_level())
       {
          g_short = list[i]->query_spirit_walker_title();
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
        write("There is only one Spiritwalker in the Realms.\n");
        return 1;
    }
    write("There are now "+cnt+" Spiritwalkers in the Realms.\n");
    return 1;
}

int
s_help(string str)
{
    if (!str)
        return 0;

    if (str == "spiritwalker" || str == "spirit" || str == "spiritwalkers")
    {
        write("You may get help on the following:\n\n"+
            "    help spirit(walker) titles - a list of spiritwalker titles\n"+
            "    help spirit(walker) spells - a list of spiritwalker spells\n"+
            "    help spirit(walker) emotes - a list of spiritwalker emotes\n"+
            "    help spirit(walker)        - this list\n"+
            "\n");
        return 1;
    }

    if (str == "spiritwalker emotes" || str == "spirit emotes")
    {
        cmd_list();
        return 1;
    }

    if (str == "spiritwalker titles" || str == "spirit titles")
    {
        write("There are the following titles in the Firewalkers:\n\n"+
            "    <title> of the Primitive Ring of Shadow\n"+
            "    <title> of the Obsucure Ring of Shadow\n"+
            "    <title> of the Outer Ring of Shadow\n"+
            "    <title> of the Inner Ring of Shadow\n"+
            "    <title> of the Esoteric Sphere of Shadow\n"+
            "    <title> of the Harmonic Sphere of Shadow\n"+
            "    <title> of the Transcendent Sphere of Shadow\n"+
            "    <title> of the Ancient Sphere of Shadow\n"+
            "    <title> of the Divine Realm of Shadow\n"+
            "    Firewalker of Legends\n\n"+
            "<title> is broken down into the following:\n\n"+
            "    Initiate, Novice, Disciple, Master\n\n"+
            "Council members can be recognized by having the additional "+
            "title of 'Harbinger of Pyros' added to their own.\n\n"+
            "\n");
        return 1;
     }

    if (str == "spiritwalker spells" || str == "spirit spells")
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
              "on it by doing 'help spirit <spellname>'.  If you have not "+
              "earned the use of it, you will get no help on it.\n"+
              "\n");
        return 1;
    }

    if (str == "spiritwalker astraphto" || str == "spirit astraphto")
    {
        write("Astraphto - Shadow Speak :   With this spell you will be "+
            "able to send a message to anyone in the Realms.  You will "+
            "need a feather to sacrifice.\n");
        return 1;
    }

    if (str == "spiritwalker gsechon" || str == "spirit gsechon")
    {
        write("Gsechon - Name Forget :   With this spell you will be "+
            "able make a target forget your identity by burning it from "+
            "their minds.  For this you will require ash and obsidian "+
            "to sacrifice.\n");
        return 1;
    }

    if (str == "spiritwalker tuphlono" || str == "spirit tuphlono")
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
        
    if (str == "spiritwalker pyronero" || str == "spirit pyronero")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TWO_FLAG)
        {
            write("Pyronero - Fire Water :  This will raise the alcohol "+
                "level in the blood of the target.  You may use this on "+
                "yourself if you wish to do so.  You must be under the "+
                "effects of the pyronero potion for it to work, and it "+
                "may be cast until the effects of the potion wear off.  "+
                "The pyronero potion is mixed with poison ivy and a "+
                "water vial.\n");
            return 1;
        }
    }

    if (str == "spiritwalker bradu" || str == "spirit bradu")
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

    if (str == "spiritwalker therapeaou" || str == "spirit therapeaou")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FOUR_FLAG)
        {
            write("Therapeaou - Heal :  This spell will restore some of "+
                "the target it is cast upon.  This spell may be cast on "+
                "yourself if you so choose to do so.  You will require "+
                "the herbs spiritweed and brown slime for this to work.\n");
            return 1;
        }
    }

    if (str == "spiritwalker akoutari" || str == "spirit akoutari")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FOUR_FLAG)
        {
            write("Akoutari - Wall Of Fire :  This spell will block the "+
                "selected exit with a wall of flames.  Those who have "+
                "some resistance to spirit and those who worship Lord Pyros "+
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

    if (str == "spiritwalker aspida" || str == "spirit aspida")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FOUR_FLAG)
        {
            write("Aspida - Shadow Shield :  This spell will encompass "+
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

    if (str == "spiritwalker saita" || str == "spirit saita")
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

    if (str == "spiritwalker photitso" || str == "spirit photitso")
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

    if (str == "spiritwalker purkagia" || str == "spirit purkagia")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SIX_FLAG)
        {
            write("Purkagia - Fireball :  The second offensive spell you "+
                "recieve is a bit more powerful than its predecesor as "+
                "it sends a flaming ball at its target.  This spiritball "+
                "will explode when it contacts its intended victim.  You "+
                "will need to be under the influence of the purkagia potion "+
                "for this spell to work and you may continue to cast it "+
                "until the effects of the potion wear off.  The purkagia "+
                "potion is mixed with coral alga and a strong alcohol "+
                "(again, moonshine is recommended).\n");
            return 1;
        }
    }

    if (str == "spiritwalker optasia" || str == "spirit optasia")
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

    if (str == "spiritwalker aeras" || str == "spirit aeras")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SEVEN_FLAG)
        {
            write("Aeras - Shadow Wind :  The third offensive spell you "+
                "recieve is much more powerful that its predecesors "+
                "as it sends a flaming wind at its target.  You will "+
                "need to be under the influence of the aeras potion for "+
                "it to be cast and you can continue to cast it until the "+
                "effects of the potion wear off.  To mix the aeras potion "+
                "you will need salt wort and a powerful alcohol (moonshine).\n");
            return 1;
        }
    }

    if (str == "spiritwalker photostepsanos" || str == "spirit photostepsanos")
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

    if (str == "spiritwalker anthisto" || str == "spirit anthisto")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_EIGHT_FLAG)
        {
            write("Anthisto - Resist Fire :  The target of this spell "+
                "will have their skin enchanted so they will become "+
                "magically resistant to spirit and spirit magic.  You may "+
                "cast this upon yourself.  You must be under the effects "+
                "of the anthisto potion to cast this spell and can "+
                "continue to cast it until the potion wears off.  To mix "+
                "the anthisto potion you will require sulphur, sargassum, "+
                "and a water vial.\n");
            return 1;
        }
    }

    if (str == "spiritwalker stoiecheio" || str == "spirit stoiecheio")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_NINE_FLAG)
        {
            write("Stoiecheio - Elemental Form :  Once this spell is "+
                "successfully cast, you will be granted the form of a "+
                "spirit elemental.  This form will disguise you so no person "+
                "will know your name unless you choose to introduce "+
                "yourself to them.  This form will grant you no special "+
                "powers and no special attacks, and shall stay until you "+
                "choose to <revert> back to your normal form, or until "+
                "you run out of mental energies.  Maintaining this form "+
                "does requre mental energy so you shall continue to lose "+
                "mana until you revert to your normal form.  To cast this "+
                "spell successfully, you will need to be under the effects "+
                "of the stoiecheio potion, which is mixed with ash, spiritweed "+
                "and a strong alcohol (moonshine).\n");
            return 1;
        }
    }

    if (str == "spiritwalker aemera" || str == "spirit aemera")
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

    if (str == "spiritwalker hagiospyro" || str == "spirit hagiospyro")
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

    if (str == "spiritwalker phlogaphulo" || str == "spirit phlogaphulo")
    {
        if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TEN_FLAG)
        {
            write("Phlogaphulo - Shadow Weapon :  Upon the successful "+
                "casting of this spell, the weapon you cast it on shall "+
                "begin to flame, causing more damage when an enemy is hit "+
                "with it.  You may only use this spell a limited number "+
                "of times on any one weapon and there are some weapons "+
                "which it will not work on.  You must be under the influence "+
                "of the phlogaphulo potion to cast this spell and you may "+
                "continue to do so until the effects of the potion wear "+
                "off.  To mix the phlogaphulo potion you will require "+
                "obsidian, salt, spiritweed, laminaria, and a water vial.\n");
            return 1;
        }
    }

    if (str == "spiritwalker kausae" || str == "spirit kausae")
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
    "sbless"    : "sbless",
    "schoose"   : "schoose",
    "seyes"     : "seyes",
    "sfare"     : "sfarewell",
    "sfarewell" : "sfarewell",
    "sgaze"     : "sgaze",
    "sgrin"     : "sgrin",
    "shail"     : "shail",
    "shug"      : "shug",
    "sknee"     : "sknee",
    "slaugh"    : "slaugh",
    "sshake"    : "sshake",
    "ssmile"    : "ssmile",
    "ss"        : "sspeak",
    "sspeak"    : "sspeak",
    "swho"      : "list_spirits",
    "help"      : "s_help",
    ]);
}

