/*
 * lizard_soul.c
 * Contains emotes for the Saurians of Kalad,
 * and based on the Halflings of Faerun and Orc guild of the Shire
 * Credit to Finwe, September 2015
 * Rewritten - Mirandus February, 2018
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

//inherit "/std/leftover";

#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <std.h>
#include <stdproperties.h>
#include <time.h>
#include <wa_types.h>
#include "lizards.h"

#define MORE(x)     this_player()->more(read_file(x))

string  *surname_list = ({  "Ku'Tathar", "Im'Kazath", "Ek'Trabal", 
                            "Zin'Katar", "Em'Bratal", "Ath'Takath",
                            "Ik'Bizan", "Ef'Kamal", "En'Biktal", 
                            "Al'Azar", "Mith'Kiltar", "Baz'Zin", 
                            "Es'Tik", "Ba'Lia"});

string
get_soul_id()
{
    return GUILD_NAME_LAY + " soul";
}

//Returns if it is a command soul
int
query_cmd_soul()
{
    return 1;
}

public mapping
query_ability_map()
{
    return ([
    "disembowel" : LIZGUILD + "disembowel",
    ]);
}
//Gets the listing of commands available
mapping query_cmdlist()
{
// command : routine
    setuid();
    seteuid(getuid());
    return ([
    /******************* COMMANDS *********************/
    "disembowel" :  "do_ability",
    "ssurname"  :   "do_surname_set",
    "slist"     :   "list_saurians",

    /******************* EMOTES ***********************/
    "sagree"    :   "s_agree",
    "sclean"    :   "s_clean",
    "sdisagree" :   "s_disagree",
    "sembrace"  :   "s_embrace",
    "sgaze"     :   "s_gaze",
    "sglint"    :   "s_glint",
    "sgrin"     :   "s_grin",
    "sgrimace"  :   "s_grimace",
    "sgrowl"    :   "s_growl",
    "shumans"   :   "s_humans",
    "shungry"   :   "s_hungry",
    "sproud"    :   "s_proud",
    "sreflect"  :   "s_reflect",
    "sremind"   :   "s_remind", 
    "ssay"      :   "s_say",
    "ssigh"     :   "s_sigh",
    "ssmile"    :   "s_smile",
    "ssnarl"    :   "s_snarl",
    "stouch"    :   "s_touch",
        
    ]);
}
/***************************** COMMANDS *********************/

/*
 * Function name: do_surname_set
 * Description  : Let's us set a Saurian Surname
 * Arguments    : string - the Surname that the player wants
 */
public int
do_surname_set(string str)
{
    string list = "";
    int size = 0;
    object necklace;

    foreach(string surname: surname_list)
    {
        size++;
        list += capitalize(surname);
        if (sizeof(surname_list) - size == 1)
            list += ", and ";
        else if (sizeof(surname_list) - size > 1)
               list += ", ";
     }

     if(!str)
     {
       write("You have the following surname options to choose from:\n\n\n"
        + "          Ku'Tathar   - Those who led us into battle.\n"
        + "          Im'Kazath   - Those who taught our young.\n"
        + "          Ek'Trabal   - Those who passed on our stories.\n"
        + "          Zin'Katar   - Those who taught us to hunt.\n"
        + "          Em'Bratal   - Those who guided our scouts.\n"
        + "          Ath'Takath  - Those who developed our technologies.\n"
        + "          Ik'Bizan    - Those who tended to the hurt and sick.\n"
        + "          Ef'Kamal    - Those who travelled to gather knowledge.\n"
        + "          En'Biktal   - Those who saw what others cannot.\n"
        + "          Al'Azar     - Those amongst us who knew magic.\n"
        + "          Mith'Kiltar - Those whose name brought fear to enemies.\n"
        + "          Baz'Zin     - Those who prepared us for battle.\n"
        + "          Es'Tik      - Those who knew what others could not.\n"
        + "          Ba'Lia      - Those who led us with wisdom.\n\n"
        + "If you don't want a surname, or want to remove it, choose 'none'."
        +"\n");
         return 1;
     }

     if(str == "none")
     {
         write("You no longer have a Saurian surname.\n");
         SURNAME_MANAGER->set_saurian_surname(this_player(),0);
         return 1;
     }

     str = capitalize(str);

     if(member_array(str, surname_list) > -1)
     {
         write("You change your surname to " +str+ "!\n");
         SURNAME_MANAGER->set_saurian_surname(this_player(), str);
         return 1;
     }

     write("That isn't a Saurian surname you can change to.\n");
     return 1;
}

/*
 * Function name: list_saurians()
 * Description  : Let's us see what other saurians are awake.
 * Arguments    : none
 */
int
list_saurians()
{
    string g_name, g_short;
    int i;
    int cnt = 0;
    object *list;
    write("\n\tThe " + GUILD_NAME_RACE + ":\n");

    list = users();

    for (i = 0; i < sizeof(list); i++)
    {
        g_name = capitalize(list[i]->query_real_name());
        if (IS_MEMBER_LAY(list[i]))
        {
            /* Don't want a jr's or wizards in the list */
            if ((extract(g_name, -2) == "jr") && (!(TP->query_wiz_level())))
            continue;
            if(!list[i]->query_invis())
            {
                if (list[i]->query_wiz_level())
                {
                    g_short = list[i]->query_guild_title_race();
                    write("\t  * " + g_name + " " + g_short);
                }
                else
                {
                    g_short = list[i]->query_guild_title_race();
                    write("\t  - " + g_name + " " + g_short);
                }
                cnt++;
            }

            if (list[i]->query_invis() && TP->query_wiz_level())
            {
                write("\t  @ (" + g_name + ")");
                cnt++;
            }
            else
            {
                if (list[i]->short())
                write("");
            }

            if (!list[i]->query_invis() || TP->query_wiz_level())
                write("\n");
        }
    }
    write("\n\n");

    if(cnt > 1)
    {
        write("There are "+cnt+" Saurians awake in the world.\n");
        return 1;
    }
    else
    {
        write("You are the only Saurian awake.\n");
        return 1;
    }
}


/**************************** EMOTES ************************/

int
s_agree(string arg)
{
    object *oblist;
    
    NF("Agree with whom?\n");
    
    if (!strlen(arg))
    {
        write("Considering the points made you nod in completely "
        +"agreement.\n");
        allbb(" nods in complete agreement\n");
        SOULDESC("nodding in complete agreement");
        return 1;
    }
    
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %1");
    if (!sizeof(oblist))
        return 0;
    
    SOULDESC("nodding in complete agreement");
    actor("You nod at", oblist, " completely agreeing.");
    all2actbb(" nods at", oblist, " in complete agreement.");
    targetbb(" nods at you in completely agreement.",oblist);
    return 1;
}

int
s_clean()
{
    allbb( "cleans some bits of flesh from underneath "+HIS(TP)+" claws "
    + "before flinging it to the ground.\n");
    write("You clean some bits of flesh from under your fingernails.\n");
    return 1;
}

int
s_disagree(string arg)
{
    object *oblist;
    
    NF("Disagree with whom?\n");
    
    if (!strlen(arg))
    {
        write("Considering the points made you shake your head in "
        + "complete disagreement.\n");
        allbb(" shakes "+HIS(TP)+" head in complete disagreement\n");
        SOULDESC("in complete disagreement");
        return 1;
    }
    
    oblist = parse_this(arg, "[with] / [the] %1");
    if (!sizeof(oblist))
        return 0;
    
    SOULDESC("in complete disagreement");
    actor("You look at", oblist, " shaking your head in complete "+
    "disagreement.");
    all2actbb(" shakes "+HIS(TP)+" head at", oblist, " in complete "
    + "disagreement.");
    targetbb(" shakes "+HIS(TP)+" head at you in complete disagreement."
    ,oblist);
    return 1;
}

int
s_embrace(string arg)
{
    object *oblist;
    
    NF("Embrace with who?\n");
    if (!strlen(arg))
        return 0;
    
    oblist = parse_this(arg, "[the] %l");
    if (!sizeof(oblist))
        return 0;
    
    if (sizeof(oblist) >1)
    { 
        NF("You can only embrace one person at a time.\n"); 
        return 0; 
    }
    
    actor("You grab", oblist, " with both hands pulling" +HIM(oblist[0])+
    " towards you in an embrace of true friendship and camaraderie.");
    
    all2actbb(" grabs", oblist, " with both hands pulling" +HIM(oblist[0])+
    " in close to " + HIS(TP) + " body in an embrace of true friendship "
    +"and camaraderie.");
    
    targetbb(" grabs you with both hands and pulls you close to "+HIS(TP)+
    " scaled body in an act of true friendship and camaraderie.", oblist);
    return 1;
}

int
s_gaze(string arg)
{
    object *oblist;
    
    NF("Gaze at who with concern?\n");
    
    if (!strlen(arg))
    {
        write("You gaze off into the distance, a feeling of general "
        + "concern for the lands of Kalad washing over you.\n");
        allbb(" looks off into the distance, a look of deep concern washing "
        + "over "+HIS(TP)+" face.\n");
        SOULDESC("deeply concerned");
        return 1;
    }
    
    oblist = parse_this(arg, "[at] / [toward] [the] %1");
    if (!sizeof(oblist))
        return 0;
    
    SOULDESC("deeply concerned");
    actor("You look at", oblist, " with deep concern for their well-being.");
    all2actbb(" looks at", oblist,", a look of deep concern washing over "
    +HIS(TP)+" face.");
    targetbb(" looks at you intently with deep concern growing on "+HIS(TP)+
    " face.",oblist);
    return 1;
}

int
s_glint()
{
    allbb( "get a strange glint in "+HIS(TP)+" eyes, smiling slightly as "
    + "recalling something amusing.\n");
    write("You remember just how stupid others can be, a small smile coming "
    +"over you with a glint in your eyes.\n");
    return 1;
}

int
s_grin(string arg)
{
    object *oblist;
    
    NF("Grin at who?\n");
    
    if (!strlen(arg))
    {
        write("You grin slightly, revealing jagged teeth.\n");
        allbb(" grins slightly, revealing "+HIS(TP)+" jagged teeth.\n");
        SOULDESC("grinning slightly");
        return 1;
    }
    
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;
    
    SOULDESC("grinning slightly");
    actor("You look at", oblist, " grinning slightly, revealing "
    +"jagged teeth.");
    all2actbb(" looks at", oblist,", grinning slightly, revealing "+HIS(TP)+
    " jagged teeth.");
    targetbb(" grins at you slightly, revealing "+HIS(TP)+" jagged teeth."
    ,oblist);
    return 1;
}

int
s_grimace()
{
    allbb(" grimaces in deep pain as if recalling something horrific.\n");
    write("You flash back to when you were born as a Saurian, a wave of "
    +"deep pain washing over you.\n");
    SOULDESC("grimacing in pain");
    return 1;
}

int
s_growl(string arg)
{
    object *oblist;
    
    NF("Growl at whom?\n");
    
    if (!strlen(arg))
        {
        allbb(" growls, the deep tone reverberating.");
        write("You growl, the deep tone reverberating in your chest.\n");
        SOULDESC("growling deeply");
        return 1;
    }
    
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;
    
    SOULDESC("growling deeply");
    actor("You growl at", oblist, " the tone reverberating deep in your "
    +"chest.");
    all2actbb(" growls at", oblist, ", the deep tone reverberating.");
    targetbb(" growls at, the deep tone reverberating deep in your "
    +"chest.", oblist);
    return 1;
}

int
s_humans(string arg)
{
        object *oblist;
    
    NF("Complain about humans with who?\n");
    
    if (!strlen(arg))
        {
        allbb(" begins complaining about how stupid humans can be.");
        write("With complete disregard for common sense, you begin complaining "
        +"about how stupid humans can be and how they've wasted their power "
        +"on trivial things.\n");
        SOULDESC("complaining about humans");
        return 1;
    }
    
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;
    
    if (oblist[0]->query_race_name() != "human")
    {
        SOULDESC("complaining about humans");
        actor("You beginning telling", oblist, " about how stupid humans can "
        +"be and how they've wasted their power on trivial things.");
        all2actbb(" begins telling", oblist, ", about how stupid "
        +"humans can be and how they've wasted their power on trivial "
        +"things.");
        targetbb(" begins explaining to you how stupid humans are and how "
        +"they've wasted their power on trivial things.", oblist);
        return 1;
    }
        
    SOULDESC("complaining about humans");
    actor("You tell", oblist, " how stupid "+HIS(oblist[0])+" race has "
    +"been and how they've wasted all their power on trivial things.");
    all2actbb(" begins telling", oblist, " how stupid "+HIS(oblist[0])+
    " race has been and how they've wasted all their power on trivial "
    +"things.");
    targetbb(" Tells you how stupid your race has been and how you've "
    +"wasted all your power on trivial things.", oblist);
    return 1;
}

int
s_hungry()
{
    allbb(" pats "+HIS(TP)+" stomach and gazes around curiously.\n");
    write("You feel a twing of hunger come over you and start looking "
    +"for fresh meat.\n");
    SOULDESC("looking hungry");
    return 1;
}

int
s_proud(string arg)
{
    object *oblist;
    
    NF("Stand in defiance at whom?\n");
    
    if (!strlen(arg))
        {
        allbb(" stands to "+HIS(TP)+" full height in defiance to those "
        +"who would seek to oppress "+HIM(TP)+".");
        write("You stand in defiance to those who would oppress you.\n");
        SOULDESC("standing tall");
        return 1;
    }
    
    oblist = parse_this(arg, "[of] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;
    
    SOULDESC("standing tall");
    actor("You stand tall, staring defiantly towards", oblist);
    all2actbb(" stands tall, staring defiantly at", oblist);
    targetbb(" stands tall and stares at you defiantly.", oblist);
    return 1;
}

int
s_reflect()
{
    allbb(" reflects upon "+HIS(TP)+" ancient ancestry.\n");
    write("You turn your thoughts inward, remembering just how ancient "
    +"your race is and how young all others in comparison to you.\n");
    SOULDESC("looking reflective");
    return 1;
}

int
s_remind(string arg)
{
    object *oblist;
    
    NF("Remind who just how ancient the Saurians are?\n");
    
    if (!strlen(arg))
    {
       return 0;
    }
    
    oblist = parse_this(arg, "[the] %l");
    if (!sizeof(oblist))
        return 0;
    
    actor("You remind", oblist, " just how ancient the Saurians are.");
    all2actbb(" reminds", oblist, " that Saurians have been around since "
    +"time immemorial and are not a fledgling race to be oppressed.");
    targetbb(" reminds you that the Saurians have existed since time "
    +"immemorial and that they should not be discounted or seen as easy "
    +"to oppress.", oblist);
    return 1;
}

int
s_say(string arg)
{
    if (!strlen(arg))
        {
        NF("Say what in the Saurian tongue?\n");
        return 0;
    }
        
    write("In the ancient Saurian Tongue, you say: " + arg + "\n");
    filter(all_inventory(environment(this_player())) - ({ this_player() }),
        "do_say", this_object(), arg);
    return 1;
}

public int
do_say(object who, string arg)
{
    if (!living(who))
        return 0;
    if ((IS_MEMBER_LAY(who)) || who->query_skill(SS_LANGUAGE) > 69 ||
    who->query_wiz_level() > 0)
    tell_object(who, this_player()->query_The_name(who) + " intones " +
        "in the Saurian tongue: " + arg + "\n");
    else
        tell_object(who, this_player()->query_The_name(who)  +" intones " +
        "something incomprehensible.\n");
}

int
s_sigh()
{
    allbb(" sighs with deep sorrow.\n");
    write("You sigh, recalling just how far the Saurians have let things "
    +"go.\n");
    SOULDESC("sighing deeply");
    return 1;
}

int
s_smile(string arg)
{
    object *oblist;
    
    NF("Smile at who?\n");
    
    if (!strlen(arg))
    {
        write("You smile broadly, revealing a wide jagged smile.\n");
        allbb(" smiles broadly, revealing "+HIS(TP)+" wide jagged smile.\n");
        SOULDESC("smiling broadly");
        return 1;
    }
    
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;
    
    SOULDESC("smiling broadly");
    actor("You look at", oblist, " smiling broadly, revealing "
    +"numerous jagged teeth.");
    all2actbb(" looks at", oblist,", smiling broadly, revealing "+HIS(TP)+
    " numerous jagged teeth.");
    targetbb(" smiles at you broadly, revealing "+HIS(TP)+" numerous "
    +"jagged teeth.",oblist);
    return 1;
}

int
s_snarl(string arg)
{
    object *oblist;
    NF("Snarl at whom?\n");
    if(!strlen(arg))
        {
        allbb(" snarls with inhuman rage.");
        write("You snarl with inhuman rage.\n");
        SOULDESC("snarling with inhuman rage");
        return 1;
    }
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if(!sizeof(oblist))
        return 0;
    SOULDESC("snarling with inhuman rage");
    actor("You snarl at", oblist," with inhuman rage.");
    all2actbb(" snarls at", oblist,"with inhuman rage.");
    targetbb(" snarls at you with inhuman rage.\n"+
        "You take a slight step back.",oblist);
    return 1;
}

int
s_touch()
{
    allbb(" reaches down touching" +HIS(TP)+ "tooth necklace, a tear "
    +"welling up within "+HIS(TP)+" eye.\n");
    write("You reach down and touch your tooth necklace. You remember "
    +"those who came before you, those who will come after you, and all "
    +"that you will accomplish. A tear comes to your eye.\n");
    SOULDESC("looking upset");
    return 1;   
}