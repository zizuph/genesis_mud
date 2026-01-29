
/* 

    this is the cmdsoul for hairstyles in Gelan 

    coder(s):   Maniac 

    History: 
            14/8/01    typos fixed                            Maniac 
            30/7/01    compatibility with double emotes       Maniac 
            20/9/96    more emote suggestions added           Maniac 
            18/3/96    more emote suggestions added           Maniac 
            23/1/96    hwash check for OBJ_I_CONTAIN_WATER    Maniac 
            4/12/95    more emotes added                      Maniac 
            11.7.95    Created                                Maniac 

*/ 

inherit "/cmd/std/command_driver"; 

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <std.h>
#include "specials.h"
#include "/d/Genesis/cmd/emotes.h"


/* 
 * Details of hair, instantiated during emotes. 
 */ 
string length, colour, style; 


/* 
 * Function name: get_soul_id
 * Description:   give identification of soul
 * Arguments:     none
 * Returns:       string with id
 */
string
get_soul_id()
{
    return "Hairstyle";
}


/* 
 * Function name: query_cmd_soul 
 * Description:   identify this one as cmd soul 
 * Arguments:     none 
 * Returns:       always 1 
 */ 
int
query_cmd_soul()
{
    return 1;
}


/* Get hair details of a particular player */ 
int 
get_hair_details(object player) 
{ 
    if (!interactive(player)) 
        return 0; 

    if (!(length = player->query_hair_length())) 
        return 0; 

    if (!(colour = player->query_hair_colour())) 
        return 0; 

    if (!(style = player->query_hair_style())) 
        return 0; 

    return 1; 
} 


/* Help on hair emotes */ 
int 
help(string str) 
{ 
    if (str != "hair") 
        return 0; 

    this_player()->more("You have the following emotes available " + 
                        "for hair:\n\n" + 
           "hbrush [player]  - brush away a lock of hair.\n" + 
           "hflutter         - hair flutters in the breeze.\n" + 
           "hpull            - pull a tuft of your hair out.\n" + 
           "hrip <player>    - attack someone else's hair!\n" + 
           "hruffle <player> - ruffle a player's hairstyle.\n" + 
           "hrun [player]    - run fingers through someone's hair.\n" + 
           "hstand           - hair stands on end.\n" + 
           "hstroke          - absent-mindedly stroke your hair.\n" + 
           "hthrash          - thrash your head around.\n" + 
           "htoss            - toss your head.\n" + 
           "htrim <player>   - give someone's hair a light trim.\n" + 
           "htwist           - idly twist a lock of hair.\n" + 
           "hwash            - wash your hair in nearby water.\n" + 
           "\nHair emotes can be used in double emotes - see \"help double\".\n"); 
    return 1; 
} 


/* Thrash one's head (hair) around. */
varargs mixed 
hthrash(string str, int indirect, object trg)
{
    object tp = this_player();
    
    if (!get_hair_details(tp)) 
    {
       notify_fail("Some of your hairstyle is missing, strange!\n");
       return 0;
    }
    
    if ((length == "short") ||  wildmatch("*short", length) ||
        wildmatch("short*", length)) 
    { 
        if (indirect) 
            return ({ tp, 0, 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBES("thrash"), 
                         EVH_ACT_POS, "head around wildly" }), 
                        "hthrash", "." }); 

        write("You thrash your head around wildly.\n"); 
        allbb(" thrashes " + tp->query_possessive() + " head " + 
              "around wildly."); 
        return 1; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, EVH_VERBES("thrash"), 
                     EVH_ACT_POS, length + " " + colour + 
                     " hair around wildly" }), 
                    "hthrash", "." }); 

    write("You thrash your " + length + " " + colour + 
          " hair around wildly.\n"); 
    allbb(" thrashes " + tp->query_possessive() + " " + 
           length + " " + colour + " hair around wildly."); 
    return 1; 
}


/* Toss one's head (hair). */
varargs mixed 
htoss(string str, int indirect, object trg)
{
    object tp = this_player();
    
    if (!get_hair_details(tp)) 
    {
       notify_fail("Some of your hairstyle is missing, strange!\n");
       return 0;
    }

    if ((length == "short") ||  wildmatch("*short", length) ||
        wildmatch("short*", length)) 
    {
        if (indirect) 
            return ({ tp, 0, 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBES("toss"), 
                         EVH_ACT_POS, "head" }), 
                        "htoss", "." }); 

        write("You toss your head.\n");
        allbb(" tosses " + tp->query_possessive() + " head.");
        return 1; 
    }

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, EVH_VERBES("toss"), 
                     EVH_ACT_POS, length + " " + colour + 
                     " hair back around", EVH_ACT_POS, "shoulders" }), 
                    "htoss", "." }); 

    write("You toss your " + length + " " + colour + 
          " hair back around your shoulders.\n"); 
    allbb(" tosses " + tp->query_possessive() + " " + length + " " + 
          colour + " hair back around " + tp->query_possessive() + 
          " shoulders.");
    return 1;
}


/* Brush hair from (some)one's face. */
varargs mixed 
hbrush(string str, int indirect, object trg)
{
    object tp = this_player(); 
    object *oblist; 
    string hairpiece; 

    if (stringp(str) && strlen(str)) 
    { 
        if (objectp(trg) && (str == "it" || str == trg->query_objective())) 
        { 
            oblist = ({ trg }); 
        } 
        else 
        { 
            oblist = parse_this(str, "[lock] [of] [hair] [from] %l"); 

            if (!sizeof(oblist)) 
            { 
                notify_fail("Hbrush whom?\n"); 
                return 0; 
            } 

            if (sizeof(oblist) > 1) 
            { 
                notify_fail("You can't brush the hair of more than one " + 
                            "person at once!\n"); 
                return 0; 
            } 
        } 

        if (!get_hair_details(oblist[0])) 
        { 
            notify_fail("That person's hairstyle is missing, strange!\n"); 
            return 0; 
        } 

        if ((length == "short") || 
             wildmatch("*short", length) || 
             wildmatch("short*", length)) 
             hairpiece = "loose strand"; 
        else 
             hairpiece = "stray lock"; 

        if (indirect) 
            return ({ tp, oblist[0], 0, 1, 
                      ({ EVH_ACT_SBJ, EVH_VERBES("brush"), 
                         "a " + hairpiece + " of " + colour + 
                         " hair off", EVH_TRG_POS, "face" }), 
                        "hbrush", "." }); 

        actor("You brush a " + hairpiece + " of " + colour + 
              " hair off", oblist, "'s face."); 
        target(" brushes a " + hairpiece + " of " + colour + " hair " + 
              "off your face.", oblist); 
        all2act(" brushes a " + hairpiece + " of " + colour + " hair " + 
                "off", oblist, "'s face."); 

        return 1; 
    } 

    if (!get_hair_details(tp)) 
    { 
       notify_fail("Some of your hairstyle is missing, strange!\n"); 
       return 0; 
    } 

    if ((length == "short") || 
         wildmatch("*short", length) || 
         wildmatch("short*", length)) 
         hairpiece = "loose strand"; 
    else 
         hairpiece = "stray lock"; 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, EVH_VERBES("brush"), 
                     "a " + hairpiece + " of " + colour + 
                     " hair off", EVH_ACT_POS, "face" }), 
                     "hbrush", "." }); 

    write("You brush a " + hairpiece + " of " + colour + 
          " hair off your face.\n"); 
    allbb(" brushes a " + hairpiece + " of " + 
          colour + " hair off " + tp->query_possessive() + " face."); 

    return 1; 
} 


/* Stroke one's hair. */
varargs mixed
hstroke(string str, int indirect, object trg)
{
    object tp = this_player(); 

    if (!get_hair_details(tp)) 
    { 
       notify_fail("Some of your hairstyle is missing, strange!\n"); 
       return 0; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, "absent-mindedly", 
                     EVH_VERBE("stroke"), EVH_ACT_POS, 
                     length + " " + colour + " hair" }), 
                    "hstroke", "." }); 

    write("You absent-mindedly stroke your " + length + " " + colour + 
          " hair.\n"); 
    allbb(" absent-mindedly strokes " + tp->query_possessive() + " " + 
           length + " " + colour + " hair."); 
    return 1; 
}


/* Hair stands on end. */
varargs mixed 
hstand(string str, int indirect, object trg)
{
    object tp = this_player(); 
    
    if (!get_hair_details(tp)) 
    { 
       notify_fail("Some of your hairstyle is missing, strange!\n"); 
       return 0; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_POS, length + " " + colour + " hair " +  
                     "stands on end" }), 
                    "hstand", "!" }); 

    write("Your " + length + " " + colour + " hair stands on end!\n"); 
    allbb("'s " + length + " " + colour + " hair stands on end!"); 
    return 1; 
}


/* Emote to idly twist a lock of one's hair */
varargs mixed 
htwist(string str, int indirect, object trg)
{
    object tp = this_player(); 
    
    if (!get_hair_details(tp)) 
    { 
       notify_fail("Some of your hairstyle is missing, strange!\n"); 
       return 0; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, "idly", EVH_VERB("twist"), 
                    "a lock of", EVH_ACT_POS, 
                    length + " " + colour + " hair" }), 
                    "htwist", "." }); 

    write("You idly twist a lock of your " + length + " " + colour + 
          " hair.\n"); 
    allbb(" idly twists a lock of " + tp->query_possessive() + " " + 
           length + " " + colour + " hair."); 
    return 1; 
}


/* Emote to despair and pull a tuft of hair from one's scalp */
varargs mixed 
hpull(string str, int indirect, object trg)
{
    object tp = this_player();
    
    if (!get_hair_details(tp)) 
    {
       notify_fail("Some of your hairstyle is missing, strange!\n");
       return 0;
    }

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, EVH_VERB("pull"), 
                    "a tuft of " + length + " " + colour + 
                    " hair from", EVH_ACT_POS, "scalp in despair" }), 
                    "hpull", "." }); 

    write("You pull a tuft of " + length + 
          " " + colour + " hair from your scalp in despair.\n");
    allbb(" pulls a tuft of " +
           length + " " + colour + " hair from " + 
           tp->query_possessive() + " scalp in despair.");
    return 1;
}


/* Emote to wash one's hair in nearby water */
varargs mixed 
hwash(string str, int indirect, object trg)
{
    object tp = this_player();
    object room;
    int room_type, contain_water;
    
    if (!get_hair_details(tp)) 
    {
       notify_fail("Some of your hairstyle is missing, strange!\n");
       return 0;
    }

    room = environment(tp);
    contain_water = room->query_prop(OBJ_I_CONTAIN_WATER);
    room_type = room->query_prop(ROOM_I_TYPE);

    if ((room_type != ROOM_IN_WATER) && 
        (room_type != ROOM_UNDER_WATER) &&
        (room_type != ROOM_BEACH) &&
        (!contain_water)) 
    {
        notify_fail("You can't find any water here.\n");
        return 0;
    }

    if (indirect) 
        return ({ tp, 0, 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBES("wash"), 
                     EVH_ACT_POS, length + " " + colour + 
                     " hair in the water nearby" }), 
                     "hwash", "." }); 

    write("You wash your " + length + " " + colour + 
          " hair in the water nearby.\n"); 
    allbb(" washes " + tp->query_possessive() + " " + 
           length + " " + colour + " hair in the water nearby."); 
    return 1; 
}


/* Emote to have one's hair flutter in the breeze */
varargs mixed 
hflutter(string str, int indirect, object trg)
{
    object tp = this_player();
    object room;
    int room_type, inside;
    
    if (!get_hair_details(tp)) 
    {
       notify_fail("Some of your hairstyle is missing, strange!\n");
       return 0;
    }

    room = environment(tp); 
    room_type = room->query_prop(ROOM_I_TYPE); 
    inside = room->query_prop(ROOM_I_INSIDE); 

    if ((room_type == ROOM_UNDER_WATER) || inside) 
    { 
        notify_fail("This isn't the kind of place you will find a breeze.\n"); 
        return 0; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_POS, length + " " + colour + " hair " + 
                     "flutters gently in the breeze" }), 
                    "hflutter", "." }); 

    write("Your " + length + " " + colour + 
          " hair flutters gently in the breeze.\n"); 
    allbb("'s " + length + " " + colour + " hair flutters gently " + 
          "in the breeze."); 
    return 1; 
} 


/* Check to see if a weapon exists and has a slashing edge */ 
int 
weapon_check(mixed weapon) 
{ 
    if (!weapon) 
        return 0; 

    if (weapon->query_dt() & W_SLASH) 
        return 1; 
    else 
        return 0; 
} 


/* Emote to trim someone's hair with a wielded (edged) weapon */
varargs mixed
htrim(string str, int indirect, object trg)
{
    object tp = this_player();
    object *friend;
    object weapon;
    int me = 0;
    string wname;

    if (!str) 
    {
        notify_fail("Trim the hair of whom?\n");
        return 0;
    }
 
    if (str == "me") 
        me = 1;
    else 
    {
        if (objectp(trg) && (str == "it" || str == trg->query_objective())) 
        { 
            friend = ({ trg }); 
        } 
        else 
        { 
            friend = parse_this(str, "%l"); 

            if (!sizeof(friend)) 
            { 
                notify_fail("Trim the hair of whom?\n"); 
                return 0; 
            } 

            if (sizeof(friend) > 1) 
            {
                notify_fail("You can't trim the hair of more than " +
                            "one person at once!\n");
                return 0;
            }
        } 
    }

    weapon = tp->query_weapon(W_RIGHT);
    if (!weapon_check(weapon)) 
    {
        weapon = tp->query_weapon(W_LEFT);
        if (!weapon_check(weapon)) 
        {
            weapon = tp->query_weapon(W_BOTH); 
            if (!weapon_check(weapon)) 
            {
                notify_fail("You don't seem to be wielding " +
                            "any edged weapons.\n");
                return 0;
            }
        } 
    }
    wname = weapon->short(); 

    if (me) 
    { 
        if (!get_hair_details(tp)) 
        { 
            notify_fail("Some of your hairstyle is missing, strange!\n"); 
            return 0; 
        } 

        if (indirect) 
            return ({ tp, 0, 0, 1, 
                      ({ EVH_ACT_SBJ, "lightly", EVH_VERBD("trim"), 
                         EVH_ACT_POS, length + " " + colour + " hair with", 
                         EVH_ACT_POS, wname }), 
                        "htrim", "." }); 

        write("You lightly trim your " + length + " " + colour + 
              " hair with your " + wname + ".\n"); 
        allbb(" lightly trims " + tp->query_possessive() + " " + 
               length + " " + colour + " hair with " + 
               tp->query_possessive() + " " + wname + "."); 
        return 1; 
    } 

    if (!get_hair_details(friend[0])) 
    { 
        notify_fail("That person doesn't seem to have a hairstyle.\n"); 
        return 0; 
    } 

    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, "lightly", EVH_VERBD("trim"), 
                     EVH_TRG_POS, length + " " + colour + " hair with", 
                     EVH_ACT_POS, wname }), 
                    "htrim", "." }); 

    actor("You lightly trim", friend, "'s " + length + " " + colour + 
          " hair with your " + wname + "."); 
    target(" lightly trims your " + length + " " + colour + " hair " + 
           "with " + tp->query_possessive() + " " + wname + ".", friend); 
    all2actbb(" lightly trims", friend, "'s " + length + " " + colour + 
              " hair with " + tp->query_possessive() + " " + wname + "."); 
    return 1; 
} 


/* Emote for ruffling someone else's hairstyle */ 
varargs mixed 
hruffle(string str, int indirect, object trg) 
{ 
    object tp = this_player(); 
    object *friend; 

    if (!str) 
    { 
        notify_fail("Ruffle the hair of whom?\n"); 
        return 0; 
    } 

    if (objectp(trg) && (str == "it" || str == trg->query_objective())) 
    { 
        friend = ({ trg }); 
    } 
    else 
    { 
        friend = parse_this(str, "%l"); 

        if (!sizeof(friend)) 
        { 
            notify_fail("Ruffle the hair of whom?\n"); 
            return 0; 
        } 

        if (sizeof(friend) > 1) 
        { 
             notify_fail("You can't ruffle the hair of more than " + 
                         "one person at once!\n"); 
             return 0; 
        } 
    } 

    if (!get_hair_details(friend[0])) 
    { 
        notify_fail("That person doesn't seem to have a hairstyle.\n"); 
        return 0; 
    } 

    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBE("ruffle"), 
                     EVH_TRG_POS, length + " " + colour + 
                     " hair playfully" }), 
                    "hruffle", "." }); 

    actor("You ruffle", friend, "'s " + length + " " + colour + 
          " hair playfully."); 
    target(" ruffles your " + length + " " + colour + " hair " + 
            "playfully.", friend); 
    all2actbb(" ruffles", friend, "'s " + length + " " + colour + 
           " hair playfully."); 
    return 1; 
} 


/* Emote for ripping someone else's hairstyle */
varargs mixed
hrip(string str, int indirect, object trg)
{
    object tp = this_player();
    object *friend;

    if (!str)  
    {
        notify_fail("Rip whose hair out?\n");
        return 0;
    }

    if (objectp(trg) && (str == "it" || str == trg->query_objective())) 
    { 
        friend = ({ trg }); 
    } 
    else 
    { 
        friend = parse_this(str, "%l"); 

        if (!sizeof(friend)) 
        { 
            notify_fail("Rip whose hair out?\n"); 
            return 0; 
        } 

        if (sizeof(friend) > 1) 
        { 
            notify_fail("You can't rip the hair of more than " + 
                        "one person at once!\n"); 
            return 0; 
        } 
    } 

    if (!get_hair_details(friend[0])) 
    {
        notify_fail("That person doesn't seem to have a hairstyle.\n");
        return 0;
    }

    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBD("grab"), 
                     "a handful of", EVH_TRG_POS, 
                     length + " " + colour + " hair and viciously", 
                     EVH_VERBY("try"), "to rip it out" }), 
                    "hrip", "." }); 

    actor("You grab hold of a handful of", friend, "'s " + 
          length + " " + colour + " hair and viciously try to rip " +
          "it out.");
    target(" grabs hold of a handful of your " + length + " " + colour + 
           " hair and viciously tries to rip it out.", friend);
    all2actbb(" grabs hold of a handful of", friend, "'s " + length + 
            " " + colour + " hair and viciously tries to rip it out."); 
    return 1;
}


/* Emote for running fingers through someone's hair. */
varargs mixed 
hrun(string str, int indirect, object trg)
{
    object tp = this_player(); 
    object *friend; 

    if (!stringp(str) && !strlen(str)) 
    {
        friend = ({ tp }); 
    } 
    else if (objectp(trg) && (str == "it" || str == trg->query_objective())) 
    { 
        friend = ({ trg }); 
    } 
    else 
    { 
        friend = parse_this(str, "%l", 0, 1); 

        if (!sizeof(friend)) 
        { 
            notify_fail("Run fingers through whose hair?\n"); 
            return 0; 
        } 

        if (sizeof(friend) > 1) 
        { 
            notify_fail("Please be more specific.\n"); 
            return 0; 
        } 
    } 

    if (!get_hair_details(friend[0])) 
    { 
        notify_fail("That person doesn't seem to have a hairstyle.\n"); 
        return 0; 
    } 

    if (friend[0] == tp) 
    { 
        if (indirect) 
            return ({ tp, 0, 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBD("run"), 
                         EVH_ACT_POS, "fingers through", 
                         EVH_ACT_POS, 
                         length + " " + colour + " hair" }), 
                        "hrun", "." }); 

        write("You run your fingers through your " + 
              length + " " + colour + " hair.\n"); 
        allbb(" runs " + tp->query_possessive() + " fingers through " + 
              tp->query_possessive() + " " + length + " " + colour + 
              " hair."); 
        return 1; 
    } 

    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBD("run"), 
                     EVH_ACT_POS, "fingers through", 
                     EVH_TRG_POS, 
                     length + " " + colour + " hair" }), 
                     "hrun", "." }); 

    actor("You run your fingers through", friend, "'s " + 
        length + " " + colour + " hair."); 
    target(" runs " + tp->query_possessive() + " fingers through " + 
        "your " + length + " " + colour + " hair.", friend); 
    all2actbb(" runs " + tp->query_possessive() + " fingers through", 
        friend, "'s " + length + " " + colour + " hair."); 
    return 1; 
} 


mapping
query_cmdlist()
{
    return
    ([
        "help" : "help",
        "hruffle" : "hruffle",
        "hpull" : "hpull",
        "hrip" : "hrip",
        "htrim" : "htrim",
        "hwash" : "hwash",
        "htwist" : "htwist",
        "hrun"   : "hrun",
        "htoss"  : "htoss",
        "hstand" : "hstand",
        "hthrash" : "hthrash",
        "hstroke" : "hstroke",
        "hbrush" : "hbrush", 
        "hflutter" : "hflutter", 
    ]);
}

