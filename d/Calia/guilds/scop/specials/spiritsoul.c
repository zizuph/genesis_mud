
 /* Spirit Circle of Psuchae Occ Soul   */
 /* July 24th, 2003                     */
 /* Jaacar                              */
 /* Special thanks to Raven for help    */
 /* with the command parsing routines   */


/* Navarre Feb 12th 2007, added check so we don't sort
 * a list of names for swho, if there is only one cleric
 * this caused it to compare a string with 0, which 
 * caused a runtime error.
 */

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
#include COUNCIL_HEADER

#define SOULDESC(x) (TP->add_prop(LIVE_S_SOULEXTRA, x))

string
get_soul_id()
{
    seteuid(getuid());
    return "Spirit Circle of Psuchae";
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
is_spirit(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}

int
is_worship(object living)
{
    return living->query_guild_name_lay() == WORSHIPPER_GUILD;
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
    "sassess <player(s)>           - assess <player(s)> with a discriminating\n"+
    "                                glance, then discard them as harmless.\n"+
    "sbless <player(s)>            - bless <player(s) silently.\n"+
    "sbrush (<how>) <player(s)>    - brush your fingertips across\n"+
    "                                <player(s)> forearm touching it (<how>)\n"+
    "sboredom                      - show your boredom for the conversation.\n"+
//    "schant                        - speak in the Ancient Mantras.\n"+
    "sclose                        - close your eyes and turn your focus inward.\n"+
    "sconsume                      - be consumed with a derisive laughter.\n"+
    "sembrace <player(s) (<how>)   - embrace <player(s)> in the shadows.\n"+
    "sdisgust                      - observe the area with obvious disgust.\n"+
    "sdismiss <player(s)>          - dismiss <player(s)>, wanting them out of\n"+
    "                                your sight.\n"+
    "seyes (<how>) (<player(s)>)   - glare (at player(s)) angrily.\n" +
    "sfare(well) <player(s)>       - bow slightly and wave farewell to <player(s)>.\n"+
    "sgaze (<how>) (<player(s)>)   - gaze (<how>) (at <player(s)>).\n"+
    "sgesture                      - make a quick gesture in front of yourself, \n"+
    "                                kissing your fingers and touching your \n"+
    "                                forehead softly to protect yourself against \n"+
    "                                all evil.\n"+
    "sglare (<player(s)>)          - glare around (at <player(s)>) in a foul mood.\n"+
    "sgreet <player>               - greet <player> (only works for other members\n"+
    "                                of the Spirit Circle).\n"+
    "sgrin (<how>) (<player(s)>)   - grin (<how>) (at <player(s)>).\n"+
    "shail <player(s)>             - hail <player(s)> in an ancient sign\n"+
    "                                of greetings.\n"+
    "shug <player(s)> (<how>)      - hug <player(s)> (<how>).\n" +
    "sincline <player(s)>          - incline your head respectfully to <player(s)>,\n"+
    "                                recognizing them as kindred spirits.\n"+
    "sknee                         - call to Psuchae for power.\n" +
    "skneel                        - kneel beside a corpse to absorb the soul.\n"+
    "slaugh (<how>) (<players(s)>) - laugh (<how>) (at <player(s)>).\n" +
    "spause                        - pause for a moment of contemplation.\n"+
    "spoint                        - make it obvious you have no tongue.\n"+
    "splay                         - make your shadow dance on the ground.\n"+
    "\n");
    return 1;
}

int
cmd_list2()
{
    write("You can use the following emotes:\n" +
    "spray                         - pray silently to Psuchae.\n"+
    "sprepare                      - give a motion that you need preparation.\n"+
    "srage                         - give a momentary look of rage.\n"+
    "sraise (<player(s)>)          - raise your hand in warning (at <player(s)>.\n"+
    "srise                         - rise to full height, showing your\n"+
    "                                god(dess)like beauty and majesty.\n"+
    "sshake <player(s)>            - shake <player(s)> with a shadowy hand.\n" +
    "sshrug                        - give a shrug, not caring one way or\n"+
    "                                the other.\n"+
    "ssmile (<how>) (<player(s)>)  - smile (<how>) (at <player(s)>).\n" +
    "ssnap (<how>)                 - snap your fingers (<how>).\n" +
    "sstand                        - stand in a corner letting your presence\n"+
    "                                be felt.\n"+
    "sthank <player(s)>            - smile in thanks to <player(s)>.\n"+
    "stsay <message>               - telepathically say the message to\n"+
    "                                other Circle members in the room.\n"+
    "                                Only Circle members will be able to\n"+
    "                                hear you.\n"+
    "sstretch                      - stretch out your body and rest.\n"+
    "stense <player>               - tense your body up over the soulless\n"+
    "                                body of <player>. (ONLY works on undead)\n"+
    "help spirit (circle)          - a list of all help spirit (circle) options.\n"+
    "\nYou can also use the following commands:\n"+
    "swho                          - divine a list of Spirit Circle members in\n"+
    "                                the Realms.\n"+
    "schoose <player>              - select a player to be a Spirit Circle member.\n" +
    "spells                        - get a list of your currently divined gifts.\n\n"+
    "\n");
    return 1;
}

int
com_cmd_list()
{
    write("You have the following communication abilities:\n" +
    "stsay <message>                 - telepathically say the message to\n"+
    "                                  other Circle members in the room.\n"+
    "                                  Only Circle members will be able to\n"+
    "                                  hear you.\n"+
    "sfsay to <target> <message>     - telepathically tell your familiar to say\n"+
    "                                  <message> to <target> on your behalf.\n"+
    "sfshout <message>               - telepathically tell your familiar to say\n"+
    "                                  <message> to the entire room you are in\n"+
    "                                  on your behalf.\n"+
    "sfask to <target> <message>     - telepathically tell your familiar to ask\n"+
    "                                  <message> to <target> on your behalf.\n"+
    "sfwhisper to <target> <message> - telepathically tell your familiar to\n"+
    "                                  whisper <message> to <target> on your\n"+
    "                                  behalf.\n\n"+
    "NOTE: sfsay, sfshout, sfask, and sfwhisper will ALL cost you health and\n"+
    "      mana to use. For sfsay, sfask and sfwhisper YOU MUST use the format\n"+
    "      <command> to <target> <message>. If you forget the 'to', it will not\n"+
    "      work with the desired results you are after.\n"+
    "\n");
    return 1;
}

int
sassess(string str)
{
    object *oblist;

    if (!str || str == "")
    {
        NF("Assess whom with a discriminating glance?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NF("Assess whom with a discriminating glance?\n");
        return 0;
    }

    actor("You assess",oblist," with a discriminating glance, but "+
        "discard them as harmless.");
    all2act(" assesses",oblist," with a discriminating glance, but "+
        "discards them as harmless.");
    target(" assesses you with a discriminating glance, but discards "+
        "you as harmless.",oblist);
    return 1;
}

int
sbless(string str)
{
    object *oblist;

    if (!str || str == "")
    {
        NF("Bless whom silently in the name of Psuchae?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NF("Bless whom silently in the name of Psuchae?\n");
        return 0;
    }

    actor("You bless",oblist," silently in the name of Psuchae.");
    all2act(" blesses",oblist," silently.");
    target(" blesses you silently.",oblist);
    return 1;
}

int
sboredom()
{
    write("Your attention wavers and you gaze off into the distance, "+
        "having grown bored with the current conversation.\n");
    all("'s attention wavers and "+HE+" gazes off into the distance, "+
        "having grown bored with the current conversation.");
    return 1;
}

int
sbrush(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "gently", 0);

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Brush [how] on whom?\n");
        return 0;
    }

    actor("You brush your fingertips briefly across",oblist,"'s forearm, "+
        "touching it"+how[1]+".");
    all2act(" brushes "+HIS+" fingertips briefly across",oblist,"'s forearm, "+
        "touching it"+how[1]+".",how[1]);
    target(" brushes "+HIS+" fingertips briefly across your forearm, "+
        "touching it"+how[1]+".",oblist,how[1]);
    return 1;
}

int
schoose(string str)
{
    object *who;
    object chosen;
    string my_name, apprentice;

    if (!(COUNCIL_CODE->is_spirit_elder(TP->query_real_name())))
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

    if (is_spirit(who[0]))
    {
        NF("That person is already a Spirit Circle member!\n");
        return 0;
    }

    if (present("_schosen_", who[0]))
    {
        NF("That person is already chosen!\n");
        return 0;
    }

    my_name = TP->query_real_name();

    
    target(" places "+HIS+" hands on your shoulders. You feel "+
        "power flowing through your body.",who);
    actor("You place your hands on",who,"'s shoulder, chosing "+
        who[0]->query_objective()+" as your Apprentice.");
    all2actbb(" places "+HIS+" hands on",who,"'s shoulders.");
    apprentice = who[0]->query_real_name();
    COUNCIL_CODE->add_mentor(my_name, apprentice);

    (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
        capitalize(my_name) + " has selected "+capitalize(apprentice) +
        " as "+TP->query_possessive()+" apprentice of Psuchae.\n");

    setuid();
    seteuid(getuid());
    chosen=clone_object(SPIRIT_OBJECTS+"chosen");
    chosen->move(who[0],1);
    return 1;
}

int
sclose()
{
    write("You close your eyes, turning your focus inwards.\n");
    all(" closes "+HIS+" eyes, turning "+HIS+" focus inwards.");
    return 1;
}

int
sconsume()
{
    write("You are consumed with a derisive laughter.\n");
    all(" is consumed with derisive laughter. The disturbing sound "+
        "strikes fear in your very soul.");
    return 1;
}

int
sdisgust()
{
    write("You observe the area with obvious disgust.\n");
    all(" observes the area with obvious disgust.");
    return 1;
}

int
sdismiss(string str)
{
    object *oblist;

    NF("Dismiss whom?\n");
    if (!strlen(str))
        return 0;
    
    oblist = parse_this(str,"[the] %l");
    if (!sizeof(oblist))
        return 0;
    
    target(" dismisses you, wanting you out of "+HIS+" sight.",oblist);
    if (sizeof(oblist) == 1)
    {
        actor("You dismiss",oblist,", wanting them out of your sight.");
        all2actbb(" dismisses",oblist,", wanting them out of "+HIS+" sight.");
    }
    else
    {
        actor("You dismiss",oblist,", wanting them out of your sight.");
        all2actbb(" dismisses",oblist,", wanting them out of "+HIS+" sight.");
    }
    return 1;
}

int
sembrace(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "warmly", 1);

    oblist = parse_this(how[0], "[the] %l");

    if (!sizeof(oblist))
    {
        NF("Embrace whom [how]?\n");
        return 0;
    }

    actor("You open your arms and embrace",oblist,how[1]+", infusing "+
          "their body and soul with a profound sense of peace.");
    all2act(" opens "+HIS+" arms and embraces",oblist, how[1]+", infusing "+
        "their body and soul with a profound sense of peace.",how[1]);
    target(" opens "+HIS+" arms and embraces you"+how[1]+", infusing "+
        "your body and soul with a profound sense of peace.",oblist,how[1]);
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
        all(" glares around"+how[1]+", "+HIS+" eyes seemingly absorb "+
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
    all2act(" glares"+how[1]+" at",oblist,", "+HIS+" eyes seem to absorb "+
        "their very soul.",how[1]);
    target(" glares"+how[1]+" at you, "+HIS+" eyes seem to absorb your "+
        "very soul.",oblist, how[1]);
    return 1;
}

int
sfarewell(string str)
{
    object *oblist;

    NF("Bow and wave farewell to who?\n");
    if (!strlen(str))
        return 0;
    
    oblist = parse_this(str,"[to] [the] %l");
    if (!sizeof(oblist))
        return 0;
    
    target(" bows slightly and waves farewell to you. You "+
        "somehow know that "+HE+" wishes you all the best "+
        "in your travels.",oblist);
    if (sizeof(oblist) == 1)
    {
        actor("You bow slightly and wave farewell to",oblist,".");
        all2actbb(" bows slightly and waves farewell to",oblist,".");
    }
    else
    {
        actor("You bow slightly and wave farewell to",oblist,".");
        all2actbb(" bows slightly and waves farewell to",oblist,".");
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
        all(" fixes "+HIS+" eyes on an invisible point and gazes"+
            how[1]+" at it, causing "+HIS+" pupils to dialate and "+
            "turning "+HIS+" eyes into black voids.",how[1]);
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
        "your contempt. "+capitalize(oblist[0]->query_pronoun())+
        " looks back, but quickly trembles and looks away.");
    all2act(" gazes"+how[1]+" at",oblist," with unconcealed contempt. "+
        "After a brief struggle, "+oblist[0]->query_pronoun()+" trembles "+
        "and averts "+oblist[0]->query_possessive()+ " gaze.", how[1]);
    target(" gazes"+how[1]+" at you, not bothering to conceal "+HIS+
        " contempt. Bravely you look "+TP->query_objective()+" in the "+
        "eye and suddenly feel you are looking into a dark void. "+
        "A sharp pain spreads from behind your eyes and just as you feel "+
        "you are about to faint, you tremble and lower your gaze.",oblist,how[1]);
    return 1;
}

int
sgesture()
{
    write("You make a quick gesture in front of yourself, kissing your fingers "+
        "and touching your forehead softly to protect yourself against all "+
        "evil.\n");
    all(" makes a quick gesture in front of "+HIM+", kissing "+HIS+" fingers "+
        "and touching "+HIS+" forehead softly to protect "+HIM+"self against "+
        "all evil.");
    return 1;
}

int
sglare(string str)
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
    all2act(" glares at",who,", obviously in a foul mood.");
    target(" glares at you, obviously in a foul mood. You silently "+
        "pray "+HE+" does not take it out on you.",who);
    return 1;
}

int
sgreet(string str)
{
    object *who;

    if (!str || str == "")
    {
        NF("Greet whom?\n");
        return 0;
    }

    who = parse_this(str, " %l");

    if (!sizeof(who))
        return 0;

    if (!who)
        return 0;
    
    if (sizeof(who)>1)
    {
        NF("You cannot greet more than one member at a time.\n");
        return 0;
    }

    if (!is_spirit(who[0]))
    {
        NF("That person is not a member of the Spirit Circle.\n");
        return 0;
    }

    if (COUNCIL_CODE->is_patriarch(TP->query_real_name()))
    {
        target(" inclines "+HIS+" head towards you as "+HE+" mouths "+
            "a silent blessing that sends a flickering shadow across "+
            HIS+" visage.",who);
        actor("You incline your head towards",who," and mouth a silent "+
            "blessing that sends a flickering shadow across your visage.");
        all2actbb(" inclines "+HIS+" head towards",who," as "+HE+" mouths "+
            "a silent blessing that sends a flickering shadow across "+
            HIS+" visage.");
        return 1;
    }

    if (COUNCIL_CODE->is_archon(TP->query_real_name()))
    {
        if (COUNCIL_CODE->is_patriarch(who[0]->query_real_name()))
        {
            target(" kneels briefly before you and gently brings your hand to "+
                HIS+" forehead in a gesture of reverence.",who);
            actor("You kneel briefly before",who," and gently bring "+
                who[0]->query_possessive()+" hand to your forehead in "+
                "a gesture of reverence.");
            all2actbb(" kneels briefly before",who," and gently brings "+
                who[0]->query_possessive()+" hand to "+HIS+" forehead in "+
                "a gesture of reverence.");
            return 1;
        }

        target(" inclines "+HIS+" head towards you as "+HE+" mouths "+
            "a silent blessing that sends a flickering shadow across "+
            HIS+" visage.",who);
        actor("You incline your head towards",who," and mouth a silent "+
            "blessing that sends a flickering shadow across your visage.");
        all2actbb(" inclines "+HIS+" head towards",who," as "+HE+" mouths "+
            "a silent blessing that sends a flickering shadow across "+
            HIS+" visage.");
        return 1;
    }

    if (COUNCIL_CODE->is_theurgist(TP->query_real_name()))
    {
        if (COUNCIL_CODE->is_patriarch(who[0]->query_real_name()))
        {
            target(" kneels briefly before you and gently brings your hand to "+
                HIS+" forehead in a gesture of reverence.",who);
            actor("You kneel briefly before",who," and gently bring "+
                who[0]->query_possessive()+" hand to your forehead in "+
                "a gesture of reverence.");
            all2actbb(" kneels briefly before",who," and gently brings "+
                who[0]->query_possessive()+" hand to "+HIS+" forehead in "+
                "a gesture of reverence.");
            return 1;
        }

        if (COUNCIL_CODE->is_archon(who[0]->query_real_name()))
        {
            target(" kneels briefly before you and gently brings your hand to "+
                HIS+" forehead in a gesture of reverence.",who);
            actor("You kneel briefly before",who," and gently bring "+
                who[0]->query_possessive()+" hand to your forehead in "+
                "a gesture of reverence.");
            all2actbb(" kneels briefly before",who," and gently brings "+
                who[0]->query_possessive()+" hand to "+HIS+" forehead in "+
                "a gesture of reverence.");
            return 1;
        }

        target(" inclines "+HIS+" head towards you as "+HE+" mouths "+
            "a silent blessing that sends a flickering shadow across "+
            HIS+" visage.",who);
        actor("You incline your head towards",who," and mouth a silent "+
            "blessing that sends a flickering shadow across your visage.");
        all2actbb(" inclines "+HIS+" head towards",who," as "+HE+" mouths "+
            "a silent blessing that sends a flickering shadow across "+
            HIS+" visage.");
        return 1;
    }

    if (COUNCIL_CODE->is_spirit_apprentice(TP->query_real_name()))
    {
        if (COUNCIL_CODE->is_patriarch(who[0]->query_real_name()))
        {
            target(" kneels briefly before you and gently brings your hand to "+
                HIS+" forehead in a gesture of reverence.",who);
            actor("You kneel briefly before",who," and gently bring "+
                who[0]->query_possessive()+" hand to your forehead in "+
                "a gesture of reverence.");
            all2actbb(" kneels briefly before",who," and gently brings "+
                who[0]->query_possessive()+" hand to "+HIS+" forehead in "+
                "a gesture of reverence.");
            return 1;
        }

        if (COUNCIL_CODE->is_archon(who[0]->query_real_name()))
        {
            target(" kneels briefly before you and gently brings your hand to "+
                HIS+" forehead in a gesture of reverence.",who);
            actor("You kneel briefly before",who," and gently bring "+
                who[0]->query_possessive()+" hand to your forehead in "+
                "a gesture of reverence.");
            all2actbb(" kneels briefly before",who," and gently brings "+
                who[0]->query_possessive()+" hand to "+HIS+" forehead in "+
                "a gesture of reverence.");
            return 1;
        }

        if (COUNCIL_CODE->is_theurgist(who[0]->query_real_name()))
        {
            target(" kneels briefly before you and gently brings your hand to "+
                HIS+" forehead in a gesture of reverence.",who);
            actor("You kneel briefly before",who," and gently bring "+
                who[0]->query_possessive()+" hand to your forehead in "+
                "a gesture of reverence.");
            all2actbb(" kneels briefly before",who," and gently brings "+
                who[0]->query_possessive()+" hand to "+HIS+" forehead in "+
                "a gesture of reverence.");
            return 1;
        }

        if (COUNCIL_CODE->is_spirit_apprentice(who[0]->query_real_name()))
        {
            target(" clasps "+HIS+" hands together in a silent gesture "+
                "of prayer as "+HE+" inclines "+HIS+" head towards you, "+
                "recognizing you as a kindred spirit.",who);
            actor("You clasp your hands together in a silent gesture of "+
                "prayer as you incline your head towards",who,", recognizing "+
                who[0]->query_objective()+" as a kindred spirit.");
            all2actbb(" clasps "+HIS+" hands together in a silent gesture "+
                "of prayer as "+HE+" inclines "+HIS+" head towards",who,", "+
                "recognizing "+who[0]->query_objective()+" as a kindred "+
                "spirit.");
            return 1;
        }

        if (COUNCIL_CODE->is_spirit_master(who[0]->query_real_name()))
        {
            target(" clasps "+HIS+" sacred mandala to "+HIS+" chest as "+
                HE+" genuflects before you in a gesture of reverence.",who);
            actor("You clasp your sacred mandala to your chest as you "+
                "genuflect before",who," in a gesture of reverence.");
            all2actbb(" clasps "+HIS+" sacred mandala to "+HIS+" chest as "+
                HE+" genuflects before",who," in a gesture of reverence.");
            return 1;
        }

        if (COUNCIL_CODE->is_spirit_elder(who[0]->query_real_name()))
        {
            target(" clasps "+HIS+" sacred mandala to "+HIS+" chest as "+
                HE+" genuflects before you in a gesture of reverence.",who);
            actor("You clasp your sacred mandala to your chest as you "+
                "genuflect before",who," in a gesture of reverence.");
            all2actbb(" clasps "+HIS+" sacred mandala to "+HIS+" chest as "+
                HE+" genuflects before",who," in a gesture of reverence.");
            return 1;
        }
    }

    if (COUNCIL_CODE->is_spirit_master(TP->query_real_name()))
    {
        if (COUNCIL_CODE->is_patriarch(who[0]->query_real_name()))
        {
            target(" kneels briefly before you and gently brings your hand to "+
                HIS+" forehead in a gesture of reverence.",who);
            actor("You kneel briefly before",who," and gently bring "+
                who[0]->query_possessive()+" hand to your forehead in "+
                "a gesture of reverence.");
            all2actbb(" kneels briefly before",who," and gently brings "+
                who[0]->query_possessive()+" hand to "+HIS+" forehead in "+
                "a gesture of reverence.");
            return 1;
        }

        if (COUNCIL_CODE->is_archon(who[0]->query_real_name()))
        {
            target(" kneels briefly before you and gently brings your hand to "+
                HIS+" forehead in a gesture of reverence.",who);
            actor("You kneel briefly before",who," and gently bring "+
                who[0]->query_possessive()+" hand to your forehead in "+
                "a gesture of reverence.");
            all2actbb(" kneels briefly before",who," and gently brings "+
                who[0]->query_possessive()+" hand to "+HIS+" forehead in "+
                "a gesture of reverence.");
            return 1;
        }

        if (COUNCIL_CODE->is_theurgist(who[0]->query_real_name()))
        {
            target(" kneels briefly before you and gently brings your hand to "+
                HIS+" forehead in a gesture of reverence.",who);
            actor("You kneel briefly before",who," and gently bring "+
                who[0]->query_possessive()+" hand to your forehead in "+
                "a gesture of reverence.");
            all2actbb(" kneels briefly before",who," and gently brings "+
                who[0]->query_possessive()+" hand to "+HIS+" forehead in "+
                "a gesture of reverence.");
            return 1;
        }

        if (COUNCIL_CODE->is_spirit_apprentice(who[0]->query_real_name()))
        {
            target(" inclines "+HIS+" head towards you as "+HE+" mouths "+
                "a silent blessing that sends a flickering shadow across "+
                HIS+" visage.",who);
            actor("You incline your head towards",who," and mouth a silent "+
                "blessing that sends a flickering shadow across your visage.");
            all2actbb(" inclines "+HIS+" head towards",who," as "+HE+" mouths "+
                "a silent blessing that sends a flickering shadow across "+
                HIS+" visage.");
            return 1;
        }

        if (COUNCIL_CODE->is_spirit_master(who[0]->query_real_name()))
        {
            target(" clasps "+HIS+" hands together in a silent gesture "+
                "of prayer as "+HE+" inclines "+HIS+" head towards you, "+
                "recognizing you as a kindred spirit.",who);
            actor("You clasp your hands together in a silent gesture of "+
                "prayer as you incline your head towards",who,", recognizing "+
                who[0]->query_objective()+" as a kindred spirit.");
            all2actbb(" clasps "+HIS+" hands together in a silent gesture "+
                "of prayer as "+HE+" inclines "+HIS+" head towards",who,", "+
                "recognizing "+who[0]->query_objective()+" as a kindred "+
                "spirit.");
            return 1;
        }

        if (COUNCIL_CODE->is_spirit_elder(who[0]->query_real_name()))
        {
            target(" clasps "+HIS+" sacred mandala to "+HIS+" chest as "+
                HE+" genuflects before you in a gesture of reverence.",who);
            actor("You clasp your sacred mandala to your chest as you "+
                "genuflect before",who," in a gesture of reverence.");
            all2actbb(" clasps "+HIS+" sacred mandala to "+HIS+" chest as "+
                HE+" genuflects before",who," in a gesture of reverence.");
            return 1;
        }
    }

    if (COUNCIL_CODE->is_spirit_elder(TP->query_real_name()))
    {
        if (COUNCIL_CODE->is_patriarch(who[0]->query_real_name()))
        {
            target(" kneels briefly before you and gently brings your hand to "+
                HIS+" forehead in a gesture of reverence.",who);
            actor("You kneel briefly before",who," and gently bring "+
                who[0]->query_possessive()+" hand to your forehead in "+
                "a gesture of reverence.");
            all2actbb(" kneels briefly before",who," and gently brings "+
                who[0]->query_possessive()+" hand to "+HIS+" forehead in "+
                "a gesture of reverence.");
            return 1;
        }

        if (COUNCIL_CODE->is_archon(who[0]->query_real_name()))
        {
            target(" kneels briefly before you and gently brings your hand to "+
                HIS+" forehead in a gesture of reverence.",who);
            actor("You kneel briefly before",who," and gently bring "+
                who[0]->query_possessive()+" hand to your forehead in "+
                "a gesture of reverence.");
            all2actbb(" kneels briefly before",who," and gently brings "+
                who[0]->query_possessive()+" hand to "+HIS+" forehead in "+
                "a gesture of reverence.");
            return 1;
        }

        if (COUNCIL_CODE->is_theurgist(who[0]->query_real_name()))
        {
            target(" kneels briefly before you and gently brings your hand to "+
                HIS+" forehead in a gesture of reverence.",who);
            actor("You kneel briefly before",who," and gently bring "+
                who[0]->query_possessive()+" hand to your forehead in "+
                "a gesture of reverence.");
            all2actbb(" kneels briefly before",who," and gently brings "+
                who[0]->query_possessive()+" hand to "+HIS+" forehead in "+
                "a gesture of reverence.");
            return 1;
        }

        if (COUNCIL_CODE->is_spirit_apprentice(who[0]->query_real_name()))
        {
            target(" inclines "+HIS+" head towards you as "+HE+" mouths "+
                "a silent blessing that sends a flickering shadow across "+
                HIS+" visage.",who);
            actor("You incline your head towards",who," and mouth a silent "+
                "blessing that sends a flickering shadow across your visage.");
            all2actbb(" inclines "+HIS+" head towards",who," as "+HE+" mouths "+
                "a silent blessing that sends a flickering shadow across "+
                HIS+" visage.");
            return 1;
        }

        if (COUNCIL_CODE->is_spirit_master(who[0]->query_real_name()))
        {
            target(" inclines "+HIS+" head towards you as "+HE+" mouths "+
                "a silent blessing that sends a flickering shadow across "+
                HIS+" visage.",who);
            actor("You incline your head towards",who," and mouth a silent "+
                "blessing that sends a flickering shadow across your visage.");
            all2actbb(" inclines "+HIS+" head towards",who," as "+HE+" mouths "+
                "a silent blessing that sends a flickering shadow across "+
                HIS+" visage.");
            return 1;
        }

        if (COUNCIL_CODE->is_spirit_elder(who[0]->query_real_name()))
        {
            target(" clasps "+HIS+" hands together in a silent gesture "+
                "of prayer as "+HE+" inclines "+HIS+" head towards you, "+
                "recognizing you as a kindred spirit.",who);
            actor("You clasp your hands together in a silent gesture of "+
                "prayer as you incline your head towards",who,", recognizing "+
                who[0]->query_objective()+" as a kindred spirit.");
            all2actbb(" clasps "+HIS+" hands together in a silent gesture "+
                "of prayer as "+HE+" inclines "+HIS+" head towards",who,", "+
                "recognizing "+who[0]->query_objective()+" as a kindred "+
                "spirit.");
            return 1;
        }
    }
}

int
sgrin(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "delightedly", 0);

    if (!stringp(how[0]))
    {
        write("You grin"+how[1]+", your face brightening as you do so.\n");
        all(" grins"+how[1]+", "+HIS+" face brightening as "+HE+" does so.");
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
    all2act(" grins"+how[1]+" at",oblist,", "+HIS+" eyes "+
        "seem to look knowingly into their soul!",how[1]);
    target(" grins at you"+how[1]+", "+HIS+" eyes seem to look "+
        "knowingly into your soul.",oblist,how[1]);
    SOULDESC("grinning"+how[1]);
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

    members = filter(oblist, is_spirit);
    members += filter(oblist, is_worship);
    nonmem = oblist - members;


    /* Non-members */ 
    for (i = 0; i < sizeof(nonmem); i++)  
    { 
        nonmem[i]->catch_msg(TP->query_The_name(nonmem[i])+" reaches toward " +
            "you with "+ HIS+" left hand open, palm facing you, in an " +
            "ancient sign of greetings.\n");
    } 

   if (sizeof(nonmem)) 
       TP->catch_msg("You hail " + group_desc(TP, nonmem, 0) +
            " in an ancient sign of greetings.\n");

    /* Members */ 
    for (i = 0; i < sizeof(members); i++)  
    { 
        members[i]->catch_msg(TP->query_The_name(members[i]) + " reaches " +
            "toward you with "+ HIS+" left hand open, palm facing you, " +
            "in an ancient sign of greetings.\n"+
            "You place your right fist in "+HIS+" hand to complete the "+
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
            group_desc(onl[i], oblist, 0) + " with "+HIS+" left hand, in an "+
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
sincline(string str)
{
    object *oblist;

    if(!strlen(str))
    {
       NF("Incline your head to whom?\n");
       return 0;
    }

    oblist = parse_this(str, "[to] [the] %l");

    if(!sizeof(oblist))
    {
       NF("Incline your head to whom?\n");
       return 0;
    }
       
    actor("You incline your head respectfully to",oblist,", recognizing "+
        "them as a kindred spirit.");
    all2actbb(" inclines "+HIS+" head respectfully to",oblist,", recognizing "+
        "them as a kindred spirit.");
    target(" inclines "+HIS+" head respectfully to you, recognizing you "+
        "are a kindred spirit.",oblist);
    return 1;
}

int
sknee()
{
    write("You get down on one knee and mentally call upon the power of "+ 
        "Psuchae, Ruler of the Spirits, Elemental of Shadow.\n");
    all(" gets down on one knee and gets a look of extreme concentration "+
        "on "+HIS+" face.");
    return 1;
}

int
skneel()
{
    if (!present("corpse",environment(TP)))
    {
        write("There is no corpse here to kneel beside.\n");
        return 1;
    }

    write("You kneel serenely beside the corpse and lay your hands over "+
        "its eyes and chest. A silvery form seems to appear from the body, "+
        "only to dissipate immediately into the surroundings.\n");
    all(" kneels serenely beside the corpse and lays "+HIS+" hands over "+
        "its eyes and chest. A silvery form seems to appear from the body, "+
        "only to dissipate immediately into the surroundings. Were it not "+
        "for the tingling in your skin, you would think you had imagined it.");
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
        write("Concentrating all of your energies, you laugh"+how[1]+
            ", emmitting a thunderous echo.\n");
        all(" laughs"+how[1]+", emmitting a thunderous echo!",how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Laugh [how] at whom?\n");
        return 0;
    }

    actor("Concentrating all of your energies, you laugh"+how[1]+
        " at",oblist,", emmiting a thunderous echo.");
    all2act(" laughs"+how[1]+" at",oblist,", emmitting a thunderous "+
        "echo.",how[1]);
    target(" laughs"+how[1]+" at you, emmitting a thunderous echo "+
       "that eats away at your very soul!",oblist,how[1]);
    return 1;
}

int
spause()
{
    write("A shadow passes over your eyes as you pause for a moment of "+
        "reflection and contemplation.\n");
    all("'s eyes are clouded over with shadows briefly as "+HE+" pauses "+
        "for a moment of reflection and contemplation.");
    return 1;
}

int
spoint()
{
    write("You open your mouth and point to it, showing the fact that "+
        "you have no tongue.\n");
    all(" opens "+HIS+" mouth and points to it. You are filled with awe "+
        "as you realize "+HE+" has no tongue.");
    return 1;
}

int
splay()
{
    write("You weave your hands in an intricate design causing "+
        "the your shadow to dance around on the ground.\n");
    all(" weaves "+HIS+" hands in an intricate design causing "+
        HIS+" shadow to dance around on the ground.");
    return 1;
}

int
spray()
{
    write("You look up into the sky and call out for the power of "+
        "Psuchae to guide you forth.\n");
    all(" looks up into the sky and prays silently.");
    return 1;
}

int
sprepare()
{
    write("You make a graceful gesture with your hands indicating "+
        "that you need a moment's preparation.\n");
    all(" makes a graceful gesture with "+HIS+" hands indicating "+
        "that "+HE+" needs a moment's preparation.");
    return 1;
}

int
srage()
{
    write("You contort your face in violent anger for a few moments.\n");
    all("'s face contorts in violent anger, but the fit passes in a "+
        "few moments and "+HE+" appears as serene as ever.");
    return 1;
}

int
sraise(string str)
{
    object *oblist;

    if(!strlen(str))
    {
        write("You raise your hand in warning.\n");
        all(" raises "+HIS+" hand in warning.");
        return 1;  
    }

    oblist = parse_this(str, "[at] [the] %l");

    if(!sizeof(oblist))
    {
       NF("Raise your hand in warning to whom?\n");
       return 0;
    }

    actor("You raise your hand in warning to",oblist,".");
    all2actbb(" raises "+HIS+" hand in warning to",oblist,".");
    target(" raises "+HIS+" hand in warning to you.",oblist);
    return 1;
}

int
srise()
{
    string p_sex;
    if (TP->query_gender() == G_FEMALE)
        p_sex = "goddess";
    else
        p_sex = "god";

    write("You rise to your full height and show everyone your "+p_sex+
        "like beauty and majesty.\n");
    all(" rises up to "+HIS+" full height and as your eyes are drawn to "+
        TP->query_objective()+", you are humbled by "+HIS+" "+p_sex+
        "like beauty and majesty.");
    return 1;
}

int
sshrug()
{
    write("You shrug, not caring one way or the other.\n");
    all(" shrugs, not caring one way or the other.\n");
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
    target(" grasps your hand in a strong shake. You recoil and "+
       "jerk back as you feel your soul being sucked into "
       +HIS+" hand!",oblist);
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
        all(" smiles"+how[1]+". Your muscles tighten in an "+
            "unconscious response.",how[1]);
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
    target(" smiles"+how[1]+" at you. Your muscles tighten in an "+
        "unconscious response.",oblist,how[1]);
    SOULDESC("smiling"+how[1]);
    return 1;
}

int
ssnap(string str)
{
    str = check_adverb_with_space(str, "loudly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        NF("Snap how?\n");
        return 0;
    }
    write("You snap your fingers"+str+".\n");
    all(" snaps "+HIS+" fingers"+str+".",str);
    return 1;
}

int
sstand()
{
    write("You stand in the shadows, unassuming, yet your presence "+
        "seems to pervade the area.\n");
    all(" stands in the shadows, unassuming, yet "+HIS+" presence seems "+
        "to pervade the area.");
    return 1;
}


int
sstretch()
{
    write("You stretch your body out and assume a resting position, "+
        "briefly letting your body absorb down into your shadow.\n");
    all(" stretches out " + HIS+ " body and assumes a resting position. "+
        capitalize(HIS)+" body briefly sinks into "+HIS+" own shadow "+
        "on the ground.");
    return 1;
}

int
stense(string str)
{
    object *who;

    if (!str || str == "")
    {
       NF("Tense up over whom?\n");
       return 0;
    }

    who = parse_this(str, "[at] [the] %l");

    if (!sizeof(who))
    {
        NF("Tense up over whom?\n");
        return 0;
    }

    if (sizeof(who)>1)
    {
        NF("You can only tense over one person at a time.\n");
        return 0;
    }

    if (!who[0]->query_prop(LIVE_I_UNDEAD))
    {
        NF("That person is not a Soulless one.\n");
        return 0;
    }

    actor("You body tenses with the holy power of Psuchae as you "+
        "focus your attention on the soulless body of",who);
    all2act("'s body tenses with the holy power of Psuchae as "+
        HE+" focuses "+HIS+" attention on the soulless body of",who);
    target("'s body tenses with the holy power of Psuchae as "+
        HE+" focuses "+HIS+" attention on you.",who);
    return 1;
}

int
sthank(string str)
{
    object *who;

    if (!str || str == "")
    {
       NF("Smile in thanks to whom?\n");
       return 0;
    }

    who = parse_this(str, "[at] [the] %l");

    if (!sizeof(who))
    {
        NF("Smile in thanks to whom?\n");
        return 0;
    }

    actor("You smile graciously in thanks to",who);
    all2act(" smiles graciously in thanks to",who);
    target(" smiles graciously in thanks to you. Your soul "+
        "feels uplifted.",who);
    return 1;
}

/*
 * Function name: sort_ranks
 * Description  : Sorts the members list (swho).
 */
int
sort_ranks(object user1, object user2)
{
    string name1  = user1->query_name();
    string name2  = user2->query_name();
    int    value1 = user1->query_spirit_circle_level();
    int    value2 = user2->query_spirit_circle_level();

    if (value1 != value2)
    {
	/* sort by ranks */
        return value2 - value1; 
    }
    
	// the ranks are same, sort by name 

    if (name1 > name2)
    {
        return 1;
    }

    if (name1 < name2)
    {
        return -1;
    }
    // the names are same
    return 0; 

}

int
filter_players(object player1)
{
    if(player1 && player1->query_guild_name_occ() == SPIRIT_GUILD_NAME)
    {
	return 1;
    }
    return 0;
}

int
list_spirits()
{
    setuid();
    seteuid(getuid());
    return MEMBER_LIST_UTILITY->list_members();
}

int
old_list_spirits()
{
    string g_name, g_short, *LDnames = ({});
    int i;
    int cnt = 0;
    object* nonfiltered_list;
    object* LDmembers;
    object* list;
    
    write("The following Spirit Circle members are in the Realms:\n");

    nonfiltered_list = users();

    list = filter(nonfiltered_list, filter_players);
    
    if(sizeof(list) > 1)
    {
        list = sort_array(list, sort_ranks); //Sort by rank and then name
    }

    LDmembers = filter(all_inventory(find_object("/d/Genesis/obj/statue")),
		        &operator(==)(SPIRIT_GUILD_NAME, ) @ &->query_guild_name_occ());

    for (i=0; i < sizeof(list); i++)
    {
       if (!is_spirit(list[i]))
          continue;

       g_name = capitalize(list[i]->query_real_name());

       if(!list[i]->query_wiz_level())
       {
          if (wildmatch("*jr", list[i]->query_real_name())
              && !this_player()->query_wiz_level()
              && this_player() != list[i])
          {
             // Juniors should not be seen by mortals.
             continue;
          }
          
          g_short = list[i]->query_presentation();

          if (COUNCIL_CODE->is_liberator(g_name))
              g_short += " (Liberator of Souls)";
          else if (COUNCIL_CODE->is_cultivator(g_name))
              g_short += " (Cultivator of Life)";
          else if (COUNCIL_CODE->is_beacon(g_name))
              g_short += " (Beacon of Spirits)";
          else if (COUNCIL_CODE->is_missionary(g_name))
              g_short += " (Missionary of the Spirit Circle)";
          else if (COUNCIL_CODE->is_emissary(g_name))
              g_short += " (The Emissary)";
          else if (COUNCIL_CODE->is_luminary(g_name))
              g_short += " (Luminary of the Spirit Circle)";
          else if (COUNCIL_CODE->is_conservator(g_name))
              g_short += " (Conservator of Armaments)";
          else if (COUNCIL_CODE->is_illuminati(g_name))
              g_short += " (The Illuminati)";
          else if (COUNCIL_CODE->is_intercessor(g_name))
              g_short += " (Intercessor of the Spirit Circle)";
          
          write("- " + g_short + "\n");
          cnt++;
       }
       if (list[i]->query_wiz_level() && list[i]->query_invis())
       {
          continue;
       }
       else
       if(list[i]->query_wiz_level())
       {
          g_short = list[i]->query_presentation() + " ("+
              list[i]->query_guild_title_occ()+", "+
              list[i]->query_guild_title_lay()+")";
          write("- " + g_short + "\n");
          cnt++;
       }
    }
	
	if (sizeof(LDmembers))
	{
		LDmembers = sort_array(LDmembers); //Sort by name
		for (i = sizeof(LDmembers) - 1; i >= 0; i--)
        {
			LDnames += ({LDmembers[i]->query_name()});
        }
		write("\nThe following Spirit Circle members are in the shadows of the Spiritworld:\n");
		write("- "+COMPOSITE_WORDS(LDnames)+".\n");
	}

    if (cnt < 2)
    {
        write("\nThere is only one Spirit Circle member in the Realms"+
			(sizeof(LDnames)?" and "+LANG_NUM2WORD(sizeof(LDnames))+
			" currently in the shadows of the Spiritworld.\n":".\n"));
    }
	else
	{
        write("\nThere are now "+LANG_NUM2WORD(cnt)+" Spirit Circle members in "+
			"the Realms"+(sizeof(LDnames)?" and "+LANG_NUM2WORD(sizeof(LDnames))+
			" currently in the shadows of the Spiritworld.\n":".\n"));
	}
    return 1;
}



int
s_help(string str)
{
    if (!str)
        return 0;

    if (str == "spirit circle" || str == "spirit")
    {
        write("You may get help on the following:\n\n"+
            "help spirit titles            - a list of all Spirit Circle titles\n"+
            "help spirit apprentice titles - a list of Spirit Circle Apprentice titles\n"+
            "help spirit master titles     - a list of Spirit Circle Master titles\n"+
            "help spirit elder titles      - a list of Spirit Circle Elder titles\n"+
            "help spirit other titles      - a list of Spirit Circle other titles\n"+
            "help spirit circle gifts      - a list of Spirit Circle gifts\n"+
            "help spirit emotes            - a list of Spirit Circle emotes\n"+
            "help spirit emotes 2          - a continued list of Spirit Circle emotes\n"+
//            "help spirit communication     - a list of Spirit Circle communication commands\n"+
            "help spirit other             - a list of other Spirit Circle commands.\n"+
            "help spirit speakers          - a list of approved Speakers\n"+
            "help spirit mandala           - a list of sacred mandala emotes\n"+
            "help spirit                   - this list\n"+
            "\n");
        return 1;
    }

    if (str == "spirit circle emotes" || str == "spirit emotes")
    {
        cmd_list();
        return 1;
    }

    if (str == "spirit circle emotes 2" || str == "spirit emotes 2")
    {
        cmd_list2();
        return 1;
    }

/*    if (str == "spirit circle communication" || str == "spirit communication")
    {
        com_cmd_list();
        return 1;
    } */

    if (str == "spirit speakers" || str == "spirit circle speakers")
    {
        COUNCIL_CODE->see_speakers(str);
        return 1;
    }

    if (str == "spirit circle mandala" || str == "spirit mandala")
    {
        write("There are the following emotes you can do with the sacred "+
            "mandala:\n\n"+
//            "   charge (sacred) mandala      - charge the mandala with some mana.\n"+
//            "   drain (sacred) mandala       - drain some of the charged mana from\n"+
//            "                                  the mandala.\n"+
            "   clasp (sacred) mandala       - clasp the mandala and hold it close\n"+
            "                                  to your chest.\n");
//            "\nNOTE: All charged mana will be lost when you leave the realms.\n");
        return 1;
    }

    if (str == "spirit circle titles" || str == "spirit titles")
    {
        write("There are the following titles in the Spirit Circle of Psuchae:\n\n"+
            "Apprentice Titles:\n==================\n"+
            "Novice of the Quickening\n"+
            "Seeker of Vision\n"+
            "Student of the Penumbra\n"+
            "Proselyte of the Eternal Cycle\n"+
            "Eidolon of Transcendence\n"+
            "Master Titles:\n==============\n"+
            "Enlightened Servant of the Spirit\n" +
            "Defender of the Living\n" +
            "Preceptor of Spirit\n" +
            "Vanguard of Psuchae\n" +
            "Dawnbringer\n" +
            "Elder Titles:\n=============\n"+
            "Philosopher of Transcendence\n" +
            "Redeemer of the Lost\n" +
            "Soothsayer of Essentia\n" +
            "Theurgist of the Soulwarden\n"+ 
            "Synthesis of Eternity, Paradigm of Soul\n"+
            "Leader Titles:\n==============\n"+
            "Archon of Revelation\n"+
            "Archon of Deliverance\n"+
            "Archon of Apotheosis\n"+
            "Apprentices have the additional title of 'Child of Psuchae' added "+
            "after their own.\n\n"+
            "Council members can be recognized by having the additional "+
            "title of 'Harbinger of Psuchae' added to their own.\n\n"+
            "The following special titles can be awarded as well:\n"+
            "====================================================\n"+
            "Liberator of Souls     Cultivator of Life\n"+
            "Beacon of Spirits      Missionary of the Spirit Circle\n"+
            "The Emissary           Luminary of the Spirit Circle\n"+
            "The Illuminati         Conservator of the Armaments\n"+
            "The Intercessor of the Spirit Circle\n"+
            "\n");
        return 1;
    }

    if (str == "spirit circle apprentice titles" || str == "spirit apprentice titles")
    {
        write("There are the following titles in the Spirit Circle of Psuchae:\n\n"+
              "Novice of the Quickening\n"+
              "Seeker of Vision\n"+
              "Student of the Penumbra\n"+
              "Proselyte of the Eternal Cycle\n"+
              "Eidolon of Trancendence\n");
        return 1;
    }

    if (str == "spirit circle master titles" || str == "spirit master titles")
    {
        write("There are the following titles in the Spirit Circle of Psuchae:\n\n"+
            "Master Titles:\n==============\n"+
            "Devout Shepherd\n" +
            "Defender of the Living\n"+
            "Hammer of the Faith\n"+
            "Vanguard of Psuchae\n"+
            "Dawnbringer\n");
        return 1;
    }

    if (str == "spirit circle elder titles" || str == "spirit elder titles")
    {
        write("There are the following titles in the Spirit Circle of Psuchae:\n\n"+
              "Philosopher of Transcendence\n"+
              "Redeemer of the Lost\n"+
              "Celestial Hierarch\n" +
              "Theurgist of the Soulwarden\n" + 
              "Will of Heaven\n");
        return 1;
    }

    if (str == "spirit circle other titles" || str == "spirit other titles")
    {
        write("There are the following titles in the Spirit Circle of Psuchae:\n\n"+
            "Leader Titles:\n==============\n"+
            "Archon of Revelation\n"+
            "Archon of Deliverance\n"+
            "Archon of Apotheosis\n\n"+
            "Apprentices have the additional title of 'Child of Psuchae' added "+
            "after their own.\n\n"+
            "Council members can be recognized by having the additional "+
            "title of 'Harbinger of Psuchae' added to their own.\n\n"+
            "The following special titles can be awarded as well:\n"+
            "====================================================\n"+
            "Liberator of Souls     Cultivator of Life\n"+
            "Beacon of Spirits      Missionary of the Spirit Circle\n"+
            "The Emissary           Luminary of the Spirit Circle\n"+
            "The Illuminati         Conservator of the Armaments\n"+
            "The Intercessor of the Spirit Circle\n"+
            "\n");
        return 1;
     }

    if (str == "spirit circle gifts" || str == "spirit gifts" ||
        str == "spirit circle spells" || str == "spirit spells")
    {
        write("\n\n"+
              "Apprentice Gifts:        Exevrisko,   Siopi,\n"+
              "=================        Fos,         Skiamorfi,\n"+
              "                         Magikos,     Spazopetra,\n"+
              "                         Niktamati,   Vekpos,\n"+
              "                         Psychi\n\n");

        if (COUNCIL_CODE->is_spirit_master(TP->query_real_name()))
        {
            write("Master Gifts:        Anagnorizo,  Metaballo,\n"+
                "=============          Anakalo,     Sfyri,\n"+
                "                       Apergo,      Skiamati,\n"+
                "                       Elefrinisi,  Syskotisi,\n"+
                "                       Giatreou,    Tharos,\n"+
                "                       Therapeaou\n\n");

        }

        else if (COUNCIL_CODE->is_spirit_elder(TP->query_real_name()))
        {
            write("Master Gifts:        Anagnorizo,  Metaballo,\n"+
                "=============          Anakalo,     Sfyri,\n"+
                "                       Apergo,      Skiamati,\n"+
                "                       Elefrinisi,  Syskotisi,\n"+
                "                       Giatreou,    Tharos,\n"+
                "                       Therapeaou,\n\n");
            write("Elder Gifts:         Oneiro,      Tihosskias\n"+
                "============\n\n");
        }
        
        write("If you have earned the use of the gift, you may get help "+
              "on it by doing 'help spirit <giftname>'.  If you have not "+
              "earned the use of it, you will get no help on it. You may "+
              "get a list of currently divined gifts by type <spells>.\n"+
              "\n");
        return 1;
    }

    if (str == "spirit circle psychi" || str == "spirit psychi")
    {
        write("Psychi - Psychic Speech :   With this gift you will be "+
            "able to telepathically send a message to anyone in the "+
            "Realms. A silver coin is necessary for the use of this "+
            "gift. You will require training in the art of "+
            "the art of divination to use this gift.\n");
        return 1;
    }

    if (str == "spirit circle exevrisko" || str == "spirit exevrisko")
    {
        write("Exevrisko - Detect Alignment :  With this gift you will "+
            "be able to divine the alignment of your target. You will "+
            "require a skull for this gift, as well "+
            "as training in the art of divination.\n");
            return 1;
    }

    if (str == "spirit circle magikos" || str == "spirit magikos")
    {
        write("Magikos - Identify Magic :  This gift will allow you "+
            "to detect magical properties in an object of your "+
            "choosing. You will require a shard of yellow beryl and a thighbone as a "+
            "sacrifice, as well as training in the art of divination "+
            "to use this gift.\n");
        return 1;
        
    }

    if (str == "spirit circle fos" || str == "spirit fos")
    {
        write("Fos - Light :  With this gift, you will be able to "+
            "summon a lighted halo above your head. You "+
            "will require a shard of pink coral to sacrifice to use this gift as "+
            "well as training in the art of enchantment and life "+
            "spells.\n");
        return 1;
        
    }

    if (str == "spirit circle siopi" || str == "spirit siopi")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_TWO_FLAG)
        {
            write("Siopi - Silence :  This gift will allow "+
                "you to silence the target, making it so they "+
                "cannot speak (or cast spells most likely). You "+
                "will require a shard of lapis lazuli, and a tooth to sacrifice to use this "+
                "gift as well as training in the art of enchantment.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }
/*
    if (str == "spirit circle gsechon" || str == "spirit gsechon")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_TWO_FLAG)
        {
            write("Gsechon - Name Forget :   With this gift you will be "+
                "able make a target forget your identity by removing the "+
                "memory of your soul from their mind. For this you will "+
                "require a bloodstone to sacrifice. You will require "+
                "training in the art of divination to use this gift.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }
*/
    if (str == "spirit circle vekpos" || str == "spirit vekpos")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_TWO_FLAG)
        {
            write("Vekpos - Turn Undead : Turning the Soulless can be "+
                "difficult, but you may attempt to do so by using the "+
                "vekpos gift. The target naturally must be undead and "+
                "the turning may not always work. If it is successful, "+
                "the target will run out of the area you are in, as well "+
		"as leaving it feeling ill from your prayer, which may "+
		"result in the end of the soulless creatures existence.\n"+
                "For this gift you will require a shard of bloodstone and a skull "+
                "to sacrifice. You will require training in the art of "+
                "divination to use this gift.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }
/* 
    if (str == "spirit circle eirini" || str == "spirit eirini")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_THREE_FLAG)
        {
            write("Eirini - Peace :  Once this gift is used, all fighting "+
                "in your location will cease immediately. Be warned, "+
                "it can be started right away, this merely stops the "+
                "current conflicts. You will require a carnelian to sacrifice "+
                "for this gift. You will also require training in the art "+
                "of divination for this gift. This gift is temporarily "+
                "unavailable.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }
*/
    if (str == "spirit circle skiamorfi" || str == "spirit skiamorfi")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_THREE_FLAG)
        {
            write("Skiamorfi - Shadow Form :  This gift will allow "+
                "you to transform yourself into a shadowy form. This "+
                "form will shroud you in shadows. It will conceal "+
                "all that you are carrying (except to someone who tries "+
                "to peek at your possessions of course). You will return to "+
                "normal when you can no longer maintain the spell or if you "+
                "use the command <revert>. You will require a skiamorfi " +
                "component and a rib to sacrifice "+
                "to use this gift as well as training in the art of "+
                "transmutation.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }

    if (str == "spirit circle spazopetra" || str == "spirit spazopetra")
    {
	write("Spazopetra - Shatter Gems :  This gift will allow "+
	      "you to shatter selected gems that has a usages with your gifts. "+
	      "The gems will shatter into shards, which will be used as components "+
	      "for your other gifts. There are no ingredients required for this "+
	      "gift, besides the gems to be shattered, those must be placed on the ground.\n");
	return 1;
    }
    
    if (str == "spirit circle therapeaou" || str == "spirit therapeaou")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_FOUR_FLAG)
        {
            write("Therapeauou - Cure Wounds :  This gift will restore "+
                "some of the health of the target it is cast upon. This "+
                "gift may be used on yourself if you choose to do so. "+
                "Note that not all creatures take kindly upon 'healing', "+
                "such as the soulless. " +
                "You will require a shard of pearl and an intestine for this to work as well as "+
                "training in the art of enchantment and life spells.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }

    
    if (str == "spirit circle giatreou" || str == "spirit giatreou")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_FOUR_FLAG)
        {
            write("Giatreou - Neutralize Poison :  This gift will "+
                "allow you to attempt to neutralize poisons in the "+
                "target of your choice. You will require a shard of yellow topaz "+
                "and a kidney to "+
                "sacrifice to use this gift, as well as training in "+
                "the art of enchantment and life spells.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }

    if (str == "spirit circle sfyri" || str == "spirit sfyri")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_FOUR_FLAG)
        {
            write("Sfyri - Spiritual Hammer :  This gift will allow you "+
                "to summon a spiritual hammer that can be thrown at a " +
                "target. Undead are more easily hit and hurt by this weapon." +
                " You will need a sfyri component and a rib to "+
                "sacrifice to use this gift, as well as training in the art "+
                "of conjuration.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }
    
    if (str == "spirit circle syskotisi" || str == "spirit syskotisi")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_FOUR_FLAG)
        {
            write("Syskotisi - Confusion :  This gift will cause your target "+
                "to have a hard time concentrating on his current actions. "+
                "As he becomes confused the results can be somewhat unexpected. "+
                "You will need a shard of iridescent opal and a skull to "+
                "sacrifice to use this gift, as well as training in the art "+
                "of conjuration.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }


    if (str == "spirit circle skiamati" || str == "spirit skiamati")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_FIVE_FLAG)
        {
            write("Skiamati - Shadow Eyes :  This gift will allow "+
                  "you to enhance your eyes so that you can see the "+
                  "souls lurking in the shadows. You will require a " +
                  "shard of amethyst and an eye to sacrifice "+
                  "to use this gift, as well as training in the art of "+
                  "divination.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }

    if (str == "spirit circle tharos" || str == "spirit tharos")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_FIVE_FLAG)
        {
            write("Tharos - Reduce Panic :  This gift will cause your target "+
                "to feel more secure in his surroundings, and thereby remain calm "+
                "when encountering some of the soulless creatures. "+
                "You will need a shard of garnet and a rib to "+
                "sacrifice to use this gift, as well as training in the art "+
                "of conjuration.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }


/*    if (str == "spirit circle bdella" || str == "spirit bdella")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_FIVE_FLAG)
        {
            write("Bdella - Soul Leech :  This gift will allow "+
                "you to sap the very strength away from your "+
                "victim. You will require a glittering diamond to sacrifice "+
                "to use this gift, as well as training in the art of "+
                "enchantment. This gift is temporarily not available.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }
*/
    if (str == "spirit circle apergo" || str == "spirit apergo")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_SIX_FLAG)
        {
            write("Apergo - Soul Strike : This gift allows you to reach" +
                " within someone's soul and wound them by forcing the" +
                " damage on their souls onto their bodies as well. It does" +
                " not work on the undead, for they are soulless. Nor will" +
                " it be effective on the good-aligned. You will find it to" +
                " be more effective the further into shadow your target is." +
                " You will need a shard of carnelian and a nail to" +
                " sacrifice to use this gift, as well as training in the art"+
                " of enchantment.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
              "find out information about it.\n");
        return 1;
    }
    
    if (str == "spirit circle anakalo" || str == "spirit anakalo")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_SIX_FLAG)
        {
            write("Anakalo - Word of Recall :  This powerful gift can be cast"+
                  " in four different ways. If you specify 'temple', you will" +
                  " be transported to the Temple garden. Specify 'memorize', and"+
                  " you will commit" +
                  " your current location to memory, for future use with this" +
                  " spell. If you use 'recall', you will visualize the location"+
                  " you have memorized at an earlier time. Finally, specify" +
                  " 'travel', and you will be transported to the location you" +
                  " have memorized." +
                  " You will need an anakalo component and a heart in order to cast the" +
                  " spell, and training in the art of transmutation.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }

    if (str == "spirit circle anagnorizo" || str == "spirit anagnorizo")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_SEVEN_FLAG)
        {
            write("Anagnorizo - True Identity :  This gift will allow "+
                "you to divine the true identity of a target. You will "+
                "then be able to remember them if you have room in your "+
                "memory to do so. You will require a shard of moonstone and an eye to "+
                "sacrifice to use this gift as well as training in "+
                "the art of divination. NOTE: This gift will NOT work "+
                "on mindless creatures.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }

    if (str == "spirit circle metaballo" || str == "spirit metaballo")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_SEVEN_FLAG)
        {
            write("Metaballo - Convert Weapon :  The use of this gift "+
                "will allow you to turn the target of the incantation "+
                "(a magical weapon) into a usable bludgeoning weapon, with" +
                " power dependant on that of the targeted weapon. The" +
                " weapon you receive will be dedicated by Psuchae to the" +
                " battle against the soulless. It will still serve you" +
                " against other foes, but will not be as effective." +
                " You cannot drop or give away the weapon you have been" +
                " gifted with. This prayer uses the following syntax:\n" +
                "<cast metaballo "+
                "weapon>\nYou will require a metaballo component and a " +
                "thighbone as a "+
                "sacrifice to use this gift, as well as training in the "+
                "art of transmutation.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }
    if (str == "spirit circle oneiro" || str == "spirit oneiro")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_EIGHT_FLAG)
        {
            write("Oneiro - Dream Walk:   This gift will allow you to travel" +
                " the world of dreams. In many places, the border between" +
                " the real and the dream is thin, allowing one to gather" +
                " information. Beware though, danger lurks in the shadows" +
                " of the dream, and you will find keeping a presence there" +
                " mentally draining. Also choose your place to sleep" +
                " carefully, for you are vulnerable while descending into" +
                " the dream. To use this gift, you will need training in the" +
                " art of divination, as well as a shard of glittering diamond and an eye.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }  
/*  if (str == "spirit circle energia" || str == "spirit energia")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_EIGHT_FLAG)
        {
            write("Energia - Spiritual Link:   This gift forges a bond" +
                " between you and a target. The nature of this link is such" +
                " that your physical and mental health become intertwined" +
                " with that of the target, regardless of the distance" +
                " between you. You need an energia component in order to" +
                " use this gift, as well as training in the art of" +
                " conjuration.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }               
*/
    if (str == "spirit circle tihosskias" || str == "spirit tihosskias")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_EIGHT_FLAG)
        {
            write("Tihosskias - Shadow Wall:   This gift forges a wall of "+
                "shadows towards a chosen direction. This wall will cause "+
                "soulless creatures to think twice about using the path blocked "+
                "by the wall. The soulless deciding to test their fate, will "+
                "have to go through a draining fight to tear their way through. "+
                "Evil beings may experience some discomfort as well. " +
                "You need a shard of black diamond and a rib in order to" +
                " use this gift, as well as training in the art of" +
                " conjuration.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }               



    if (str == "spirit circle elefrinisi" || str == "spirit elefrinisi")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_SIX_FLAG)
        {
            write("Elefrinisi - Relieve Encumberment:   This gift takes the "+
                  "burden of life off the shoulders of the target for a short "+
                  "period of time. You need a shard of chalcedony and a thighbone in order to" +
                " use this gift, as well as training in the art of" +
                " conjuration.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }               

    if (str == "spirit circle niktamati" || str == "spirit niktamati")
    {
        if (TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_THREE_FLAG)
        {
            write("Niktamati - Night Eyes:   This gift will enhance the sight of "+
                  "the target to be able to see through shrouds of darkness. "+
                  "You need a shard of black onyx and an eye in order to" +
                  " use this gift, as well as training in the art of" +
                  " conjuration.\n");
            return 1;
        }
        write("You do not have access to this gift, therefore you cannot "+
            "find out information about it.\n");
        return 1;
    }               
    return 0;
}

int
stsay(string str)
{
    object *oblist;
    object listener;
    object speaker = this_player();
    int i;
    
    if (!strlen(str) || str == "")
    {
        NF("Telepathically say what?\n");
        return 0;
    }    
    
    if (TP->query_option(OPT_ECHO))
    {
        write("You telepathically say: " + str + "\n");
        TP->gmcp_comms("stsay", 0, "You telepathically say: " + str + "\n");
    }

    else
    {
        write("You telepathically send your message.\n");
	TP->gmcp_comms("stsay", 0, "You telepathically send your message.\n");
    }

    oblist = all_inventory(environment(TP));
    for (i=0; i < sizeof(oblist); i++)
    {
        if ((living(oblist[i]) && oblist[i] != TP))
        {
            if (is_spirit(oblist[i]))
            {
                listener = oblist[i];
                oblist[i]->catch_msg(QCTNAME(TP)+" telepathically says: " 
                    + str+"\n");
		oblist[i]->gmcp_comms("telepathy",0,speaker->query_The_name(listener) + " telepathically says: "
                    + str + "\n");
            }
            else
            if (oblist[i]->query_wiz_level())
            {
                listener = oblist[i];
                oblist[i]->catch_msg(QCTNAME(TP)+" telepathically says: " 
                    + str+"\n");
                oblist[i]->gmcp_comms("telepathy",0,speaker->query_The_name(listener) + " telepathically says: "
                    + str + "\n");
            }   
        }
    }

    return 1;
}

int
sfsay(string argval)
{
    object familiar;
    mixed oblist;
    int     saysto;

    if (!(TP->query_prop(SPIRIT_FAMILIAR_SUMMONED)))
    {
        NF("You do not have a familiar.\n");
        return 0;
    }

    if (TP->query_mana() < SPEECH_MANA_COST)
    {
        NF("You do not have enough mana!\n");
        return 0;
    }

    if (TP->query_hp() < SPEECH_HP_COST)
    {
        NF("You do not have enough health!\n");
        return 0;
    }

    if (!argval)
    {
        NF(capitalize(query_verb()) + " what? to whom?\n");
        return 0;
    }

    familiar = present("_synithis_object_",TP);

    if (!familiar)
        return 0;
   
    oblist = all_inventory(environment(TP));
    oblist -= ({ this_player() });
    oblist = FILTER_CAN_SEE(oblist, TP);

    if (parse_command(argval, ({ }), "'to' [the] %s", argval))
    {
        saysto = 1;

        if (lower_case(argval[..2]) == "all")
        {
            argval = argval[4..];
        }
        else if (lower_case(argval[..3]) == "team")
        {
            oblist &= TP->query_team_others();
            argval = argval[5..];
        }
        else if (parse_command(argval, oblist, "%l %s", oblist, argval))
        {
            oblist = NORMAL_ACCESS(oblist, 0, 0);
        }
        else
        {
            argval = "to " + argval;
            saysto = 0;
        }
    }

    familiar->catch_say(saysto, oblist, argval);
    TP->add_mana(-SPEECH_MANA_COST);
    TP->heal_hp(-SPEECH_HP_COST);
    return 1;
}

int
sfshout(string argval)
{
    object familiar;
    
    if (!(TP->query_prop(SPIRIT_FAMILIAR_SUMMONED)))
    {
        NF("You do not have a familiar.\n");
        return 0;
    }

    if (TP->query_mana() < SPEECH_MANA_COST)
    {
        NF("You do not have enough mana!\n");
        return 0;
    }

    if (TP->query_hp() < SPEECH_HP_COST)
    {
        NF("You do not have enough health!\n");
        return 0;
    }

    if (!argval)
    {
        NF(capitalize(query_verb()) + " what? to whom?\n");
        return 0;
    }

    familiar = present("_synithis_object_",TP);

    if (!familiar)
        return 0;
   
    sscanf(argval, "to %s", argval);
    familiar->catch_shout(argval);
    TP->add_mana(-SPEECH_MANA_COST);
    TP->heal_hp(-SPEECH_HP_COST);
    return 1;
}

int
sfask(string argval)
{
    object familiar;
    mixed oblist;
    int     saysto;

    if (!(TP->query_prop(SPIRIT_FAMILIAR_SUMMONED)))
    {
        NF("You do not have a familiar.\n");
        return 0;
    }

    if (TP->query_mana() < SPEECH_MANA_COST)
    {
        NF("You do not have enough mana!\n");
        return 0;
    }

    if (TP->query_hp() < SPEECH_HP_COST)
    {
        NF("You do not have enough health!\n");
        return 0;
    }

    if (!argval)
    {
        NF(capitalize(query_verb()) + " what? to whom?\n");
        return 0;
    }

    familiar = present("_synithis_object_",TP);

    if (!familiar)
        return 0;
   
    oblist = all_inventory(environment(TP));
    oblist -= ({ this_player() });
    oblist = FILTER_CAN_SEE(oblist, TP);

    if (parse_command(argval, ({ }), "'to' [the] %s", argval))
    {
        saysto = 1;

        if (lower_case(argval[..2]) == "all")
        {
            argval = argval[4..];
        }
        else if (lower_case(argval[..3]) == "team")
        {
            oblist &= TP->query_team_others();
            argval = argval[5..];
        }
        else if (parse_command(argval, oblist, "%l %s", oblist, argval))
        {
            oblist = NORMAL_ACCESS(oblist, 0, 0);
        }
        else
        {
            argval = "to " + argval;
            saysto = 0;
        }
    }

    familiar->catch_ask(saysto, oblist, argval);
    TP->add_mana(-SPEECH_MANA_COST);
    TP->heal_hp(-SPEECH_HP_COST);
    return 1;}

int
sfwhisper(string argval)
{
    object familiar;
    mixed oblist;
    int     saysto;

    if (!(TP->query_prop(SPIRIT_FAMILIAR_SUMMONED)))
    {
        NF("You do not have a familiar.\n");
        return 0;
    }

    if (TP->query_mana() < SPEECH_MANA_COST)
    {
        NF("You do not have enough mana!\n");
        return 0;
    }

    if (TP->query_hp() < SPEECH_HP_COST)
    {
        NF("You do not have enough health!\n");
        return 0;
    }

    if (!argval)
    {
        NF(capitalize(query_verb()) + " what? to whom?\n");
        return 0;
    }

    familiar = present("_synithis_object_",TP);

    if (!familiar)
        return 0;
   
    oblist = all_inventory(environment(TP));
    oblist -= ({ this_player() });
    oblist = FILTER_CAN_SEE(oblist, TP);

    if (parse_command(argval, ({ }), "'to' [the] %s", argval))
    {
        saysto = 1;

        if (lower_case(argval[..2]) == "all")
        {
            argval = argval[4..];
        }
        else if (lower_case(argval[..3]) == "team")
        {
            oblist &= TP->query_team_others();
            argval = argval[5..];
        }
        else if (parse_command(argval, oblist, "%l %s", oblist, argval))
        {
            oblist = NORMAL_ACCESS(oblist, 0, 0);
        }
        else
        {
            argval = "to " + argval;
            saysto = 0;
        }
    }

    familiar->catch_whisper(saysto, oblist, argval);
    TP->add_mana(-SPEECH_MANA_COST);
    TP->heal_hp(-SPEECH_HP_COST);
    return 1;}

mapping
query_cmdlist()
{
    return ([
    "schoose"   : "schoose",
    "sassess"   : "sassess",
    "sboredom"  : "sboredom",
    "sbless"    : "sbless",
    "sbrush"    : "sbrush",
    "sclose"    : "sclose",
    "sconsume"  : "sconsume",
    "sdisgust"  : "sdisgust",
    "sdismiss"  : "sdismiss",
    "sembrace"  : "sembrace",
    "seyes"     : "seyes",
    "sfare"     : "sfarewell",
    "sfarewell" : "sfarewell",
    "sgaze"     : "sgaze",
    "sgesture"  : "sgesture",
    "sglare"    : "sglare",
    "sgreet"    : "sgreet",
    "sgrin"     : "sgrin",
    "shail"     : "shail",
    "shug"      : "shug",
    "sincline"  : "sincline",
    "sknee"     : "sknee",
    "skneel"    : "skneel",
    "slaugh"    : "slaugh",
    "spause"    : "spause",
    "spoint"    : "spoint",
    "splay"     : "splay",
    "spray"     : "spray",
    "sprepare"  : "sprepare",
    "srage"     : "srage",
    "sraise"    : "sraise",
    "srise"     : "srise",
    "sshake"    : "sshake",
    "sshrug"    : "sshrug",
    "ssmile"    : "ssmile",
    "ssnap"     : "ssnap",
    "sstand"    : "sstand",
    "sstretch"  : "sstretch",
    "stense"    : "stense",
    "sthank"    : "sthank",
    "stsay"     : "stsay",
    "sfsay"     : "sfsay",
    "sfshout"   : "sfshout",
    "sfask"     : "sfask",
    "sfwhisper" : "sfwhisper",
    "swho"      : "list_spirits",
    "help"      : "s_help",
    ]);
}


