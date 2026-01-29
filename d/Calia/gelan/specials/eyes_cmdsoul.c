
/* 
 * Eyes cmdsoul with emotes to go with eye shadow sold in Gelan, Calia. 
 * 
 * Coded by Maniac, 18-29/6/96 
 * Added new emotes, Maniac, 20/9/96, 2/7/97 
 * Added support for one-eyed players, Maniac, 15/7/98 
 * Corrected typo, Maniac, 11/9/99 
 * Modified to allow compatibility with double emotes, Maniac, 22-23/7/01 
 * Removed interactive() check for npc usage, Lucius, 12/12/06
 */ 

inherit "/cmd/std/command_driver";

#include <adverbs.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <std.h>
#include "eyes.h"
#include "/d/Genesis/cmd/emotes.h"


int num; 
string type, colour, eyes_desc; 


int
get_eyes_details(object player)
{
/*
 * Allow NPC's to use emotes too.
 *
    if (!interactive(player)) 
         return 0;
 */
     
    type = player->query_eyes_type();
    if (!stringp(type))
        return 0;

    colour = player->query_eyes_colour();  
    if (!stringp(colour)) 
        return 0;

    num = player->query_eyes_number();  
    if (!num)
        num = 2; 

    eyes_desc = (type + " " + colour + (num == 1 ? " eye" : " eyes"));   

    return 1;
}


int
query_cmd_soul()
{
    return 1;
}


string
get_soul_id()
{
    return "Eyes";
}


mapping
query_cmdlist()
{
    return
    ([
        "help" : "help",
        "eyegaze" : "eyegaze", 
        "eyegaz" : "eyegaze", 
        "eyepeer" : "eyepeer", 
        "eyepee" : "eyepeer", 
        "eyestare" : "eyestare", 
        "eyesta" : "eyestare", 
        "eyeglare" : "eyeglare",  
        "eyegla" : "eyeglare",  
        "eyelook" : "eyelook",  
        "eyeloo" : "eyelook", 
        "eyeroll" : "eyeroll", 
        "eyerol" : "eyeroll", 
        "eyesparkle" : "eyesparkle", 
        "eyespa" : "eyesparkle", 
        "eyetwinkle" : "eyetwinkle",  
        "eyetwi" : "eyetwinkle",  
        "eyeblink" : "eyeblink",  
        "eyebli" : "eyeblink",  
        "eyehide" : "eyehide", 
        "eyehid" : "eyehide", 
        "eyedeath" : "eyedeath", 
        "eyedea" : "eyedeath", 
        "eyepok" : "eyepoke", 
        "eyepoke" : "eyepoke", 
        "eyerub" : "eyerub",
        "eyeshut" : "eyeshut", 
        "eyeshu"  : "eyeshut", 
        "eyewater" : "eyewater", 
        "eyewat" : "eyewater", 
        "eyepop" : "eyepop", 
        "eyecry" : "eyecry", 
        "eyelow" : "eyelower", 
        "eyelower" : "eyelower", 
        "eyewink" : "eyewink", 
        "eyewin" : "eyewink", 
    ]);
}


/* Help on eye emotes */ 
int 
help(string str) 
{ 
    if (!stringp(str)) 
        return 0; 

    if (str != "eyes") 
        return 0; 

    this_player()->more("You have the following emotes available " + 
        "for your eyes:\n\n" + 
        "eyebli[nk] [player]          - Blink your eyes [at someone].\n" + 
        "eyecry                       - Your eyes fill with tears.\n" + 
        "eyedea[th] <player>          - Give a look that could kill.\n" + 
        "eyegaz[e] [how] <player>     - Gaze [how] at someone.\n" + 
        "eyegla[re] [how] [player]    - Glare [how] [at someone].\n" + 
        "eyehid[e] [how] [player]     - Hide eyes and peek [how] [at someone].\n" + 
        "eyeloo[k] [how] <player>     - Look [how] at someone.\n" + 
        "eyelow[er] <player>          - Lower eyes from someone's gaze.\n" + 
        "eyepee[r] [how] [player]     - Peer [how] [at someone].\n" + 
        "eyepok[e] <player>           - Poke someone in the eye.\n" + 
        "eyepop                       - Your eyes nearly pop out.\n" + 
        "eyerol[l]                    - Roll eyes.\n" + 
        "eyerub [how]                 - Rub your eyes [how].\n" + 
        "eyeshu[t]                    - Shut your eyes for a moment.\n" + 
        "eyesta[re] [how] [player]    - Stare [how] [at someone].\n" + 
        "eyespa[rkle] [how]           - Your eyes sparkle [how].\n" + 
        "eyetwi[nkle] [how]           - Twinkle your eyes [how].\n" + 
        "eyewat[er]                   - Your eyes start watering.\n" + 
        "eyewin[k] [how] [player]     - Wink with your eyes.\n" + 
        "\nEye emotes can be used in double emotes - see \"help double\".\n"); 
    return 1; 
} 


varargs mixed 
eyestare(string str, int indirect, object trg) 
{ 
    object tp = this_player(); 
    object *oblist; 
    string *how; 
    string vb; 

    if (!get_eyes_details(tp)) 
    {
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0;
    }

    vb = (num == 1 ? " stares" : " stare"); 

    how = parse_adverb_with_space(str, "briefly", 0);

    if (!stringp(how[0]))
    {
        if (indirect) 
            return ({ tp, 0, strlen(how[1]) ? how[1] : 0, 0, 
                      ({ EVH_ACT_POS, eyes_desc + vb }) + 
                       (strlen(how[1]) ? ({ EVH_ADVERB, "into space" }) : 
                                         ({ "into space" })), 
                         "eyestare", "." }); 

        write("Your " + eyes_desc + vb + how[1] + " into space.\n");
        allbb("'s " + eyes_desc + vb + how[1] + " into space.", how[1]);
        return 1;
    } 

    if (objectp(trg) && (str == "it" || trg->query_objective() == str)) 
        oblist = ({ trg }); 
    else 
    { 
        oblist = parse_this(how[0], "[at] [the] %l"); 
        if (sizeof(oblist) != 1) 
        { 
            notify_fail("Eyestare [how] [at whom?]\n"); 
            return 0; 
        } 
    } 

    if (indirect) 
        return ({ tp, oblist[0], strlen(how[1]) ? how[1] : 0, 0, 
                  ({ EVH_ACT_POS, eyes_desc + vb }) + 
                   (strlen(how[1]) ? ({ EVH_ADVERB }) : ({ })) + 
                   ({ "at", EVH_TRG_OBJ }), 
                     "eyestare", "." }); 

    actor("Your " + eyes_desc + vb + how[1] + " at", oblist); 
    all2actbb("'s " + eyes_desc + vb + how[1] + " at", 
              oblist); 
    targetbb("'s " + eyes_desc + vb + how[1] + " at you.", 
             oblist);
    return 1;
}


varargs mixed 
eyegaze(string str, int indirect, object trg) 
{ 
    object tp = this_player(); 
    object *oblist; 
    string *how; 

    if (!get_eyes_details(tp)) 
    { 
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0; 
    } 

    how = parse_adverb_with_space(str, "thoughtfully", 0); 

    if (objectp(trg) && (str == "it" || trg->query_objective() == str)) 
        oblist = ({ trg }); 
    else 
    { 
        oblist = parse_this(how[0], "[at] [the] %l"); 
        if (sizeof(oblist) != 1) 
        { 
            notify_fail("Eyegaze [how] at whom?\n"); 
            return 0; 
        } 
    } 

    if (indirect) 
        return ({ tp, oblist[0], strlen(how[1]) ? how[1] : 0, 0, 
                  ({ EVH_ACT_SBJ, EVH_VERBE("gaze") }) + 
                   (strlen(how[1]) ? ({ EVH_ADVERB }) : ({ })) + 
                   ({ "at", EVH_TRG_OBJ, "with", EVH_ACT_POS, eyes_desc }), 
                     "eyegaze", "." }); 

    actor("You gaze" + how[1] + " at", oblist," with your " + eyes_desc + "."); 
    all2actbb(" gazes" + how[1] + " at", oblist, " with " + 
              tp->query_possessive() + " " + eyes_desc + "."); 
    targetbb(" gazes" + how[1] + " at you with " + tp->query_possessive() + 
             " " + eyes_desc + ".", oblist); 
    return 1; 
} 


varargs mixed 
eyeglare(string str, int indirect, object trg) 
{ 
    object tp = this_player(); 
    string vb; 
    object *oblist; 
    string *how; 

    if (!get_eyes_details(tp)) 
    { 
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0; 
    } 

    how = parse_adverb_with_space(str, "stonily", 0); 

    vb = (num == 1 ? " glares" : " glare"); 

    if (!stringp(how[0])) 
    { 
        if (indirect) 
            return ({ tp, 0, strlen(how[1]) ? how[1] : 0, 0, 
                      ({ EVH_ACT_POS, eyes_desc + vb }) + 
                       (strlen(how[1]) ? ({ EVH_ADVERB }) : ({ })), 
                         "eyeglare", "." }); 

        write("Your " + eyes_desc + vb + how[1] + ".\n"); 
        allbb("'s " + eyes_desc + vb + how[1] + ".", how[1]); 
        return 1; 
    } 

    if (objectp(trg) && (str == "it" || trg->query_objective() == str)) 
        oblist = ({ trg }); 
    else 
    { 
        oblist = parse_this(how[0], "[at] [the] %l"); 
        if (sizeof(oblist) != 1) 
        { 
            notify_fail("Eyeglare [how] [at whom]?\n"); 
            return 0; 
        } 
    } 

    if (indirect) 
        return ({ tp, oblist[0], strlen(how[1]) ? how[1] : 0, 0, 
                  ({ EVH_ACT_POS, eyes_desc + vb }) + 
                   (strlen(how[1]) ? ({ EVH_ADVERB }) : ({ })) + 
                   ({ "at", EVH_TRG_OBJ }), 
                     "eyeglare", "." }); 

    actor("Your " + eyes_desc + vb + how[1] + " at", oblist); 
    all2actbb("'s " + eyes_desc + vb + how[1] + " at", 
              oblist); 
    targetbb("'s " + eyes_desc + vb + how[1] + " at you.", 
             oblist); 
    return 1; 
}


varargs mixed 
eyepeer(string str, int indirect, object trg)
{
    object tp = this_player();
    object *oblist;
    string *how; 
    string vb; 

    if (!get_eyes_details(tp))   
    {
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0;
    }

    how = parse_adverb_with_space(str, "quizzically", 0);

    vb = (num == 1 ? " peers" : " peer"); 

    if (!stringp(how[0]))
    {
        if (indirect) 
            return ({ tp, 0, strlen(how[1]) ? how[1] : 0, 0, 
                      ({ EVH_ACT_POS, eyes_desc + vb }) + 
                       (strlen(how[1]) ? ({ EVH_ADVERB, "around" }) : 
                                         ({ "around" })), 
                         "eyepeer", "." }); 

        write("Your " + eyes_desc + vb + how[1] + " around.\n");
        allbb("'s " + eyes_desc + vb + how[1] + " around.", how[1]);
        return 1;
    }

    if (objectp(trg) && (str == "it" || trg->query_objective() == str)) 
        oblist = ({ trg }); 
    else 
    { 
        oblist = parse_this(how[0], "[at] [the] %l"); 
        if (sizeof(oblist) != 1) 
        { 
            notify_fail("Eyepeer [how] [at whom]?\n"); 
            return 0; 
        } 
    } 

    if (indirect) 
        return ({ tp, oblist[0], strlen(how[1]) ? how[1] : 0, 0, 
                  ({ EVH_ACT_POS, eyes_desc + vb }) + 
                   (strlen(how[1]) ? ({ EVH_ADVERB }) : ({ })) + 
                   ({ "at", EVH_TRG_OBJ }), 
                     "eyepeer", "." }); 

    actor("Your " + eyes_desc + vb + how[1] + " at", oblist); 
    all2actbb("'s " + eyes_desc + vb + how[1] + " at", 
              oblist); 
    targetbb("'s " + eyes_desc + vb + how[1] + " at you.", 
             oblist); 
    return 1; 
}


varargs mixed 
eyelook(string str, int indirect, object trg) 
{ 
    object tp = this_player(); 
    object *oblist; 
    string *how; 

    if (!get_eyes_details(tp)) 
    {
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0;
    }

    how = parse_adverb_with_space(str, "searchingly", 0);

    if (!stringp(how[0])) 
    { 
         notify_fail("Eyelook [how] at whom?\n"); 
         return 0;
    }

    if (objectp(trg) && (str == "it" || trg->query_objective() == str)) 
        oblist = ({ trg }); 
    else 
    { 
        oblist = parse_this(how[0], "[at] [the] %l"); 
        if (sizeof(oblist) != 1) 
        { 
            notify_fail("Eyelook [how] at whom?\n"); 
            return 0; 
        } 
    } 

    if (indirect) 
        return ({ tp, oblist[0], strlen(how[1]) ? how[1] : 0, 0, 
                  ({ EVH_ACT_SBJ, EVH_VERB("look") }) + 
                   (strlen(how[1]) ? ({ EVH_ADVERB }) : ({ })) + 
                   ({ "at", EVH_TRG_OBJ, "with", EVH_ACT_POS, eyes_desc }), 
                     "eyelook", "." }); 

    actor("You look" + how[1] + " at", oblist, " with your " + 
          eyes_desc + ".");
    all2actbb(" looks" + how[1] + " at", oblist, " with " + 
              tp->query_possessive() + " " + eyes_desc + "."); 
    targetbb(" looks" + how[1] + " at you with " + tp->query_possessive() + 
             " " + eyes_desc + ".", oblist);
    return 1;
}


varargs mixed 
eyehide(string str, int indirect, object trg) 
{ 
    object tp = this_player(); 
    object *oblist; 
    string *how; 

    if (!get_eyes_details(tp)) 
    { 
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0; 
    } 

    how = parse_adverb_with_space(str, BLANK_ADVERB, 0); 

    if (!stringp(how[0])) 
    { 
        if (indirect) 
            return ({ tp, 0, strlen(how[1]) ? how[1] : 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBE("hide"), 
                         EVH_ACT_POS, eyes_desc, "and", 
                         EVH_VERB("peek") }) + 
                       (strlen(how[1]) ? ({ EVH_ADVERB }) : ({ })) + 
                      ({ "between", EVH_ACT_POS, "fingers" }), 
                         "eyehide", "." }); 

        write("You hide your " + eyes_desc + " and peek" + how[1] + 
              " between your fingers.\n"); 
        allbb(" hides " + tp->query_possessive() + " " + eyes_desc + 
              " and peeks" + how[1] + " between " + 
              tp->query_possessive() + " fingers."); 
        return 1; 
    } 

    if (objectp(trg) && (str == "it" || trg->query_objective() == str)) 
        oblist = ({ trg }); 
    else 
    { 
        oblist = parse_this(how[0], "[at] [the] %l"); 
        if (sizeof(oblist) != 1) 
        { 
            notify_fail("Eyehide [how] [at whom]?\n"); 
            return 0; 
        } 
    } 

    if (indirect) 
        return ({ tp, oblist[0], strlen(how[1]) ? how[1] : 0, 0, 
                  ({ EVH_ACT_SBJ, EVH_VERBE("hide"), 
                     EVH_ACT_POS, eyes_desc, "and", 
                     EVH_VERB("peek") }) + 
                   (strlen(how[1]) ? ({ EVH_ADVERB }) : ({ })) + 
                   ({ "between", EVH_ACT_POS, "fingers at", 
                      EVH_TRG_OBJ }), 
                     "eyehide", "." }); 

    actor("You hide your " + eyes_desc + " and peek" + how[1] + 
         " between your fingers at", oblist); 
    all2actbb(" hides " + tp->query_possessive() + " " + eyes_desc + 
          " and peeks" + how[1] + " between " + 
          tp->query_possessive() + " fingers at", oblist); 
    targetbb(" hides " + tp->query_possessive() + " " + eyes_desc + 
          " and peeks" + how[1] + " between " + 
          tp->query_possessive() + " fingers at you.", oblist); 
    return 1; 
}


varargs mixed 
eyewink(string str, int indirect, object trg) 
{ 
    object tp = this_player(); 
    object *oblist; 
    string *how; 

    if (!get_eyes_details(tp)) 
    { 
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0; 
    } 

    how = parse_adverb_with_space(str, "suggestively", 0); 

    if (!stringp(how[0])) 
    { 
        if (indirect) 
            return ({ tp, 0, strlen(how[1]) ? how[1] : 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERB("wink") }) + 
                        (num == 2 ? ({ "one of" }) : ({ })) + 
                       ({ EVH_ACT_POS, eyes_desc }) + 
                       (strlen(how[1]) ? ({ EVH_ADVERB }) : ({ })), 
                         "eyewink", "." }); 

        write("You wink" + (num == 2 ? " one of " : " ") + "your " + 
              eyes_desc + how[1] + ".\n"); 
        allbb(" winks" + (num == 2 ? " one of " : " ") + 
              tp->query_possessive() + 
              " " + eyes_desc + how[1] + "."); 
        return 1; 
    } 

    if (objectp(trg) && (str == "it" || trg->query_objective() == str)) 
        oblist = ({ trg }); 
    else 
    { 
        oblist = parse_this(how[0], "[at] [the] %l"); 
        if (sizeof(oblist) != 1) 
        { 
            notify_fail("Eyewink [how] [at whom]?\n"); 
            return 0; 
        } 
    } 

    if (indirect) 
        return ({ tp, oblist[0], strlen(how[1]) ? how[1] : 0, 0, 
                  ({ EVH_ACT_SBJ, EVH_VERB("wink") }) + 
                    (num == 2 ? ({ "one of" }) : ({ })) + 
                   ({ EVH_ACT_POS, eyes_desc }) + 
                   (strlen(how[1]) ? ({ EVH_ADVERB }) : ({ })) + 
                   ({ "at", EVH_TRG_OBJ }), 
                     "eyewink", "." }); 

    actor("You wink" + (num == 2 ? " one of " : " ") + "your " + 
          eyes_desc + how[1] + " at", oblist); 
    all2actbb(" winks" + (num == 2 ? " one of " : " ") + 
              tp->query_possessive() + 
              " " + eyes_desc + how[1] + " at", oblist); 
    targetbb(" winks" + (num == 2 ? " one of " : " ") + 
             tp->query_possessive() + 
             " " + eyes_desc + how[1] + " at you.", oblist); 
    return 1; 
} 


varargs mixed 
eyeroll(string str, int indirect, object trg) 
{ 
    object tp = this_player(); 

    if (stringp(str)) 
    { 
        notify_fail("Eyeroll what?\n"); 
        return 0; 
    } 

    if (!get_eyes_details(tp)) 
    { 
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, EVH_VERB("roll"), EVH_ACT_POS, 
                     eyes_desc + " in exasperation" }), 
                  "eyeroll", "." }); 

    write("You roll your " + eyes_desc + " in exasperation.\n"); 
    all(" rolls " + tp->query_possessive() + " " + eyes_desc + 
        " in " + "exasperation."); 
    return 1; 
} 


varargs mixed 
eyesparkle(string str, int indirect, object trg) 
{ 
    object tp = this_player(); 
    string *how; 
    string vb; 

    if (!get_eyes_details(tp)) 
    { 
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0; 
    } 

    how = parse_adverb_with_space(str, "brightly", 0); 

    vb = (num == 1 ? " sparkles" : " sparkle"); 

    if (!stringp(how[0])) 
    { 
        if (indirect) 
            return ({ tp, 0, strlen(how[1]) ? how[1] : 0, 0, 
                      ({ EVH_ACT_POS, eyes_desc + vb }) + 
                      (strlen(how[1]) ? ({ EVH_ADVERB }) : ({ })), 
                         "eyesparkle", "." }); 

        write("Your " + eyes_desc + vb + how[1] + ".\n"); 
        allbb("'s " + eyes_desc + vb + how[1] + "."); 
        return 1; 
    } 

    notify_fail("Eyesparkle how?\n"); 
    return 0; 
}


varargs mixed
eyetwinkle(string str, int indirect, object trg)
{
    object tp = this_player(); 
    string *how; 

    if (!get_eyes_details(tp)) 
    {
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0;
    }

    how = parse_adverb_with_space(str, "merrily", 0);

    if (!stringp(how[0])) 
    {
        if (indirect) 
            return ({ tp, 0, 
                      strlen(how[1]) ? how[1] : 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBE("twinkle"), EVH_ACT_POS, 
                         eyes_desc }) + 
                         (strlen(how[1]) ? ({ EVH_ADVERB }) : ({ })), 
                      "eyetwinkle", "." }); 

        write("You twinkle your " + eyes_desc + how[1] + ".\n");
        allbb(" twinkles " + tp->query_possessive() + " " + 
              eyes_desc + how[1] + ".");
        return 1;
    }

    notify_fail("Eyetwinkle how?\n"); 
    return 0;
}


varargs mixed
eyeblink(string str, int indirect, object trg)
{
    object tp = this_player(); 
    object *oblist; 

    if (!get_eyes_details(tp)) 
    {
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0;
    }

    if (!strlen(str)) 
    { 
        if (indirect) 
            return ({ tp, 0, 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERB("blink"), EVH_ACT_POS, 
                         eyes_desc }), 
                         "eyeblink", "." }); 

        write("You blink your " + eyes_desc + ".\n"); 
        allbb(" blinks " + tp->query_possessive() + " " + eyes_desc + "."); 
        return 1; 
    } 

    if (objectp(trg) && (str == "it" || trg->query_objective() == str)) 
        oblist = ({ trg }); 
    else 
    { 
        oblist = parse_this(str, "[at] [the] %l"); 
        if (sizeof(oblist) != 1) 
        { 
            notify_fail("Eyeblink at whom?\n"); 
            return 0; 
        } 
    } 

    if (indirect) 
        return ({ tp, oblist[0], 0, 0, 
                  ({ EVH_ACT_SBJ, EVH_VERB("blink"), EVH_ACT_POS, 
                     eyes_desc + " at", EVH_TRG_OBJ }), 
                     "eyeblink", "." }); 

    actor("You blink your " + eyes_desc + " at", oblist); 
    all2actbb(" blinks " + tp->query_possessive() + " " + eyes_desc + 
              " at", oblist); 
    targetbb(" blinks " + tp->query_possessive() + " " + eyes_desc + 
             " at you.", oblist); 
    return 1; 
}


varargs mixed 
eyedeath(string str, int indirect, object trg)
{
    object tp = this_player();
    object *oblist;

    if (!get_eyes_details(tp)) 
    {
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0;
    }

    if (!strlen(str)) 
    { 
        notify_fail("Eyedeath at whom?\n");
        return 0;
    }

    if (objectp(trg) && (str == "it" || trg->query_objective() == str)) 
        oblist = ({ trg }); 
    else 
    { 
        oblist = parse_this(str, "[at] [the] %l"); 
        if (sizeof(oblist) != 1) 
        { 
            notify_fail("Eyedeath at whom?\n"); 
            return 0; 
        } 
    } 

    if (indirect) 
        return ({ tp, oblist[0], 0, 0, 
                  ({ EVH_ACT_SBJ, EVH_VERBE("give"), EVH_TRG_OBJ, 
                     "a look that could kill with", 
                     EVH_ACT_POS, eyes_desc }), 
                     "eyedeath", "." }); 

    actor("You give", oblist, " a look that could kill with your " + 
          eyes_desc + "."); 
    all2actbb(" gives", oblist, " a look that could kill with " + 
              tp->query_possessive() + " " + eyes_desc + "."); 
    targetbb(" gives you a look that could kill with " + 
             tp->query_possessive() + " " + eyes_desc + ".", 
             oblist); 
    return 1; 
}


varargs mixed 
eyepoke(string str, int indirect, object trg) 
{ 
    object tp = this_player(); 
    object *oblist; 

    if (!strlen(str)) 
    { 
        notify_fail("Eyepoke whom?\n"); 
        return 0; 
    } 

    if (objectp(trg) && (str == "it" || trg->query_objective() == str)) 
        oblist = ({ trg }); 
    else 
    { 
        oblist = parse_this(str, "%l"); 
        if (sizeof(oblist) != 1) 
        { 
            notify_fail("Eyepoke whom?\n"); 
            return 0; 
        } 
    } 

    if (!get_eyes_details(oblist[0])) 
    { 
        notify_fail("Oops, that person doesn't seem to have any eyes!\n"); 
        return 0; 
    } 

    if (indirect) 
        return ({ tp, oblist[0], 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBE("poke"), EVH_TRG_OBJ, 
                     "in" + (num == 2 ? " one of" : ""), 
                     EVH_TRG_POS, eyes_desc }),  
                     "eyepoke", "." }); 

    actor("You poke", oblist, " in" + (num == 2 ? " one of " : " ") + 
          oblist[0]->query_possessive() + " " + eyes_desc + "."); 
    all2act(" pokes", oblist, " in" + (num == 2 ? " one of " : " ") + 
          oblist[0]->query_possessive() + " " + eyes_desc + "."); 
    target(" pokes you in" + (num == 2 ? " one of " : " ") + 
           "your " + eyes_desc + ".", oblist); 
    return 1; 
} 


varargs mixed
eyerub(string str, int indirect, object trg)
{
    object tp = this_player();
    string *how; 

    if (!get_eyes_details(tp))  
    {
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0;
    }

    how = parse_adverb_with_space(str, "tiredly", 0); 

    if (!stringp(how[0])) 
    { 
        if (indirect) 
            return ({ tp, 0, 
                      strlen(how[1]) ? how[1] : 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBD("rub"), EVH_ACT_POS, 
                         eyes_desc }) + 
                         (strlen(how[1]) ? ({ EVH_ADVERB }) : ({ })), 
                      "eyerub", "." }); 

        write("You rub your " + eyes_desc + how[1] + ".\n"); 
        allbb(" rubs " + tp->query_possessive() + " " + eyes_desc + 
              how[1] + "."); 
        return 1; 
    } 

    notify_fail("Eyerub how?\n"); 
    return 0;
}


varargs mixed
eyeshut(string str, int indirect, object trg)
{
    object tp = this_player();
    string *how; 

    if (!get_eyes_details(tp)) 
    {
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0;
    }

    if (stringp(str)) 
    { 
        notify_fail("Eyeshut how?\n"); 
        return 0; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, EVH_VERBD("shut"), EVH_ACT_POS, 
                     eyes_desc + " for a moment" }), 
                  "eyeshut", "." }); 

    write("You shut your " + eyes_desc + " for a moment.\n"); 
    allbb(" shuts " + tp->query_possessive() + " " + eyes_desc + 
          " for a moment."); 
    return 1; 
}


varargs mixed 
eyewater(string str, int indirect, object trg)
{
    object tp = this_player(); 
    string vb; 
    string *how; 

    if (!get_eyes_details(tp)) 
    { 
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0; 
    } 

    if (stringp(str)) 
    { 
        notify_fail("Eyewater how?\n"); 
        return 0; 
    } 

    vb = (num == 1 ? " starts" : " start"); 
    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_POS, eyes_desc + vb + " to water" }), 
                  "eyewater", "." }); 

    write("Your " + eyes_desc + vb + " to water.\n");
    allbb("'s " +  eyes_desc + vb + " to water.");
    return 1;
}


varargs mixed
eyecry(string str, int indirect, object trg)
{
    object tp = this_player();
    string vb; 
    string *how; 

    if (!get_eyes_details(tp)) 
    {
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0;
    }

    if (stringp(str)) 
    { 
        notify_fail("Eyecry how?\n"); 
        return 0;
    }

    vb = (num == 1 ? " fills" : " fill"); 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_POS, eyes_desc + vb + " with tears" }), 
                  "eyecry", "." }); 

    write("Your " + eyes_desc + vb + " with tears.\n");
    allbb("'s " + eyes_desc + vb + " with tears.");
    return 1;
}


varargs mixed
eyepop(string str, int indirect, object trg)
{
    object tp = this_player();
    string post, vb; 
    // string *how; 

    if (!get_eyes_details(tp))  
    {
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0;
    }

    vb = (num == 1 ? " pops" : " pop"); 
    post = (num == 1 ? " its socket" : " their sockets");

    if (stringp(str)) 
    { 
        notify_fail("Eyepop how?\n"); 
        return 0;
    }

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_POS, eyes_desc + " nearly" + vb + 
                     " out of" + post }), 
                  "eyepop", "!" }); 

    write("Your " + eyes_desc + " nearly" + vb + " out of" + post + "!\n");
    allbb("'s " + eyes_desc + " nearly" + vb + " out of" + post + "!");
    return 1;
}


varargs mixed
eyelower(string str, int indirect, object trg)
{
    object tp = this_player(); 
    object *oblist; 
    // string *how; 

    if (!get_eyes_details(tp)) 
    { 
        notify_fail("Oops, you don't seem to have any eyes!\n"); 
        return 0; 
    } 

    if (objectp(trg) && (str == "it" || trg->query_objective() == str)) 
        oblist = ({ trg }); 
    else 
        oblist = parse_this(str, "[from] [the] %l"); 

    if (sizeof(oblist) != 1) 
    { 
        notify_fail("Eyelower from whose gaze?\n"); 
        return 0; 
    } 

    if (indirect) 
        return ({ tp, oblist[0], 0, 0, 
                  ({ EVH_ACT_SBJ, EVH_VERB("lower"), EVH_ACT_POS, 
                     eyes_desc + " from", EVH_TRG_POS, "gaze" }), 
                  "eyelower", "." }); 

    actor("You lower your " + eyes_desc + " from", oblist, "'s gaze."); 
    all2actbb(" lowers " + tp->query_possessive() + " " + eyes_desc + 
              " from", oblist, "'s gaze."); 
    targetbb(" lowers " + tp->query_possessive() + " " + eyes_desc + 
             " from your gaze.", oblist); 
    return 1; 
}
