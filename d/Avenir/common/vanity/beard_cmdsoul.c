// /d/Avenir/common/vanity/beard_cmdsoul.c
// Created by Lilith, March 2022
//      Borrowed heavily from the Gelan hairstyle 
//      code by Maniac and Glykron for consistency 
//      of player experience. 

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
#include "/d/Avenir/common/vanity/vanity.h"
#include "/d/Genesis/cmd/emotes.h"

/* 
 * Details of beard, instantiated during emotes. 
 */ 
string length, colour, style, beard; 


/* 
 * Function name: get_soul_id
 * Description:   give identification of soul
 * Arguments:     none
 * Returns:       string with id
 */
string
get_soul_id()
{
    return "VanityBeard";
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


/* Get beard details of a particular player */ 
int 
get_beard_details(object player) 
{ 

    if (!(length = player->query_beard_length())) 
        return 0; 

    if (!(colour = player->query_beard_colour())) 
        return 0; 

    if (!(style = player->query_beard_style())) 
        return 0; 

	if (!(beard = length +" "+ colour +" "+ style)) 
        return 0; 

    return 1; 
} 


/* Help on beard emotes */ 
int 
help(string str) 
{ 
    if (str != "beard") 
        return 0; 

    this_player()->more("You have the following emotes available "+ 
                        "for your beard:\n\n"+ 
           "bbrush [me|them] - brush your beard [against their cheek].\n"+ 
		   "bchin            - thrust your chin out to show off your beard.\n"+
		   "bclean [me|them] - clean your|their beard.\n"+
           "bgroom [me|them] - remove the day's debris from your|their beard.\n"+
           "bpluck           - pull a stray hair from your beard.\n"+
           "brun   [me|them] - run your fingers through your|their beard.\n"+
           "bscratch         - scratch cheek through beard.\n"+
           "bstroke          - stroke your beard thoughtfully.\n"+
           "btrim  [me|them] - trim your|their beard.\n"+		   
           "btug   [me|them] - tug gently on your|their beard.\n"+
           "bwash            - wash your beard.\n"+		   
           "\nBeard emotes can be used in double emotes - see \"help double\".\n"); 
    return 1; 
} 


/* Brush your or someone else's beard */
varargs mixed 
bbrush(string str, int indirect, object trg)
{
    object tp = this_player(); 
    object *friend; 

    if (!stringp(str) && !strlen(str)) 
    {
        friend = ({ tp }); 
    } 
	if (str == "me")
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
            notify_fail("Brush who with your beard?\n"); 
            return 0; 
        } 

        if (sizeof(friend) > 1) 
        { 
            notify_fail("Please be more specific.\n"); 
            return 0; 
        } 
    } 

    if (!get_beard_details(tp))
    { 
        notify_fail("Beard, what beard?\n"); 
        return 0; 
    } 
		
    if (friend[0] == tp) 
    { 
        if (indirect) 
            return ({ tp, 0, 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBD("brush"), 
                         EVH_ACT_POS, "fingers through", 
                         EVH_ACT_POS, 
                         beard }), 
                         "bbrush", "." }); 

        write("You brush your fingers through your " + beard +".\n"); 
        allbb(" brushes " + tp->query_possessive() + " fingers through " + 
              tp->query_possessive() + " " + beard +"."); 
        return 1; 
    } 
	
    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBD("brush"), 
                     EVH_ACT_POS, beard +" against the cheek of", 
                     EVH_TRG_OBJ }), 
                     "bbrush", "." }); 

    actor("You brush", friend, "'s cheek with your "+ 
        beard +"."); 
    target(" brushes your cheek with " + tp->query_possessive() +
        " "+ beard +".", friend); 
    all2actbb(" brushes " + tp->query_possessive() +" "+ 
        beard + " against", friend, "'s cheek."); 
    return 1; 
} 



/* Emote for cleaning a beard. */
varargs mixed 
bclean(string str, int indirect, object trg)
{
    object tp = this_player(); 
    object *friend; 

    if (!stringp(str) && !strlen(str)) 
    {
        friend = ({ tp }); 
    } 
	if (str == "me")
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
            notify_fail("bclean whose beard?\n"); 
            return 0; 
        } 

        if (sizeof(friend) > 1) 
        { 
            notify_fail("Please be more specific.\n"); 
            return 0; 
        } 
    } 

    if (!get_beard_details(friend[0]))
    { 
        notify_fail("Beard, what beard?\n"); 
        return 0; 
    } 

    if (friend[0] == tp) 
    { 
        if (indirect) 
            return ({ tp, 0, 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBD("clean"), 
                         EVH_ACT_POS, 
                         beard }), 
                        "bclean", "." }); 

        write("You quickly clean your "+ beard +".\n"); 
        allbb(" quickly cleans " + tp->query_possessive() + 
              " "+ beard + "."); 
        return 1; 
    } 

    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBD("comb"), 
                     EVH_ACT_POS, "fingers through the "+ 
                     beard +" of", EVH_TRG_OBJ, "to clean it up a bit"}), 
                     "bclean", "." }); 

    actor("You comb your fingers through", friend, "'s " + 
        beard +", giving it a quick clean."); 
    target(" combs " + tp->query_possessive() + " fingers through "+ 
        "your " + beard + ", giving it a quick clean.", friend); 
    all2actbb(" quickly combs " + tp->query_possessive() + " fingers through", 
        friend, "'s " + beard + ", cleaning it."); 
    return 1; 
} 


/* thrust chin out, showing beard off. */
varargs mixed 
bchin(string str, int indirect, object trg)
{
    object tp = this_player(); 
    
    if (!get_beard_details(tp)) 
    { 
       notify_fail("Some of your beard is missing, strange!\n"); 
       return 0; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, EVH_VERBD("show"), "off", EVH_ACT_POS, beard }), 
                    "bchin", "!" }); 

    write("You thrust your chin out, showing off your " + 
        beard +".\n"); 
    allbb(" thrusts " + tp->query_possessive() + " chin out, showing off "+
        tp->query_possessive() + " " + beard + ".");
    return 1; 
}



/* Emote for grooming a beard. */
varargs mixed 
bgroom(string str, int indirect, object trg)
{
    object tp = this_player(); 
    object *friend; 

    if (!stringp(str) && !strlen(str)) 
    {
        friend = ({ tp }); 
    }
	
    if (str == "me") 
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
            notify_fail("bgroom whose beard?\n"); 
            return 0; 
        } 

        if (sizeof(friend) > 1) 
        { 
            notify_fail("Please be more specific.\n"); 
            return 0; 
        } 
    } 

    if (!get_beard_details(friend[0])) 
    { 
        notify_fail("That person doesn't seem to have a beard.\n"); 
        return 0; 
    } 

    if (friend[0] == tp) 
    { 
        if (indirect) 
            return ({ tp, 0, 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBD("groom"), 
                         EVH_ACT_POS, 
                         beard }), "bgroom", "." }); 

        write("You groom your " + beard + ", removing the day's debris from it.\n"); 
        allbb(" grooms " + tp->query_possessive() +" "+ beard + "."); 
        return 1; 
    } 

    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBD("groom"), 
                     "the "+ beard +" on", 
                     EVH_TRG_OBJ }), 
                     "bgroom", "." }); 

    actor("You groom", friend, "'s " + beard +", removing the day's debris from it."); 
    target(" grooms your " + beard +", removing the day's debris from it.", friend); 
    all2actbb(" quickly grooms", friend, "'s " + beard +"."); 
    return 1; 
} 





/* pluck a stray hair out of beard  */
varargs mixed 
bpluck(string str, int indirect, object trg)
{
    object tp = this_player(); 
 	if (str && str != "me")
    {
       notify_fail("You can only pluck your own beard.\n"); 
       return 0;          
    }   
    if (!get_beard_details(tp)) 
    { 
       notify_fail("Some of your beard is missing, strange!\n"); 
       return 0; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, "quickly", EVH_VERB("pluck"), 
                    "a stray hair from", EVH_ACT_POS, 
                    beard }), 
                    "bpluck", "." }); 

    write("You quickly pluck a stray hair from your " + beard + ".\n"); 
    allbb(" quickly plucks a stray hair from " + tp->query_possessive() 
        + " " + beard + "."); 
    return 1; 
}


/* run fingers through beard. */
varargs mixed 
brun(string str, int indirect, object trg)
{
    object tp = this_player(); 
    object *friend; 

    if (!stringp(str) && !strlen(str)) 
    {
        friend = ({ tp }); 
    } 
	if (str == "me")
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
            notify_fail("brun whose beard?\n"); 
            return 0; 
        } 

        if (sizeof(friend) > 1) 
        { 
            notify_fail("Please be more specific.\n"); 
            return 0; 
        } 
    } 

    if (!get_beard_details(friend[0]))
    { 
        notify_fail("Beard, what beard?\n"); 
        return 0; 
    } 

    if (friend[0] == tp) 
    { 
        if (indirect) 
            return ({ tp, 0, 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBD("run"), 
                         EVH_ACT_POS, "fingers through",
						 EVH_ACT_POS,
                         beard }), 
                        "brun", "." }); 

        write("You slowly run your fingers through your " + beard + ".\n"); 
        allbb(" slowly runs " + tp->query_possessive() + " fingers through "+ 
              tp->query_possessive() + " " + beard + "."); 
        return 1; 
    } 

    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBD("run"), 
                     EVH_ACT_POS, "fingers through the "+ 
                     beard +" on", EVH_TRG_OBJ }), 
                     "brun", "." }); 

    actor("You slowly run your fingers through", friend, "'s " + 
        beard +"."); 
    target(" slowly runs " + tp->query_possessive() + " fingers through " + 
        "your " + beard +".", friend); 
    all2actbb(" slowly runs " + tp->query_possessive() + " fingers through", 
        friend, "'s " + beard + "."); 
    return 1; 
} 


/* scratch an itch through the beard */
varargs mixed 
bscratch(string str, int indirect, object trg)
{
    object tp = this_player(); 

	if (str && str != "me")
    {
       notify_fail("You can only scratch your own beard.\n"); 
       return 0;          
    }
	
    if (!get_beard_details(tp)) 
    { 
       notify_fail("Some of your beardstyle is missing, strange!\n"); 
       return 0; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, "idly", EVH_VERB("scratch"), 
                     EVH_ACT_POS, "cheek through", EVH_ACT_POS,
                     beard }), 
                    "bscratch", "." }); 

    write("You idly scratch your cheek through your " + beard +".\n"); 
    allbb(" idly scratches " + tp->query_possessive() + " cheek through " + 
          tp->query_possessive() + " " + beard + "."); 
    return 1; 
}

/* Stroke one's beard thoughtfully. */
varargs mixed
bstroke(string str, int indirect, object trg)
{
    object tp = this_player(); 

	if (str && str != "me")
    {
       notify_fail("You can only stroke your own beard.\n"); 
       return 0;          
    }
	
    if (!get_beard_details(tp)) 
    { 
       notify_fail("Some of your beard is missing, strange!\n"); 
       return 0; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, "thoughtfully", 
                     EVH_VERBE("stroke"), EVH_ACT_POS, 
                     beard }), 
                    "bstroke", "." }); 

    write("You thoughtfully stroke your " + beard +".\n"); 
    allbb(" thoughtfully strokes " + tp->query_possessive() + " " + 
           beard + "."); 
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


/* Emote to trim someone's beard with a wielded (edged) weapon */
varargs mixed
btrim(string str, int indirect, object trg)
{
    object tp = this_player();
    object *friend;
    object weapon;
    int me = 0;
    string wname;

 
    if (!str || str == "me") 
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
                notify_fail("Trim whose beard?\n"); 
                return 0; 
            } 

            if (sizeof(friend) > 1) 
            {
                notify_fail("You can only trim one at a time!\n");
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
        if (!get_beard_details(tp)) 
        { 
            notify_fail("Some of your beard is missing, strange!\n"); 
            return 0; 
        } 

        if (indirect) 
            return ({ tp, 0, 0, 1, 
                      ({ EVH_ACT_SBJ, "carefully", EVH_VERBD("trim"), 
                         EVH_ACT_POS, beard +
                         " with", EVH_ACT_POS, wname }), 
                        "btrim", "." }); 

        write("You carefully trim your " + beard + " with your " 
              + wname + ".\n"); 
        allbb(" carefully trims " + tp->query_possessive() + " " + 
               beard + " with " + 
               tp->query_possessive() + " " + wname + "."); 
        return 1; 
    } 

    if (!get_beard_details(friend[0])) 
    { 
        notify_fail("That person doesn't seem to have a trimmable beard.\n"); 
        return 0; 
    } 

    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, "carefully", EVH_VERBD("trim"), 
                     EVH_TRG_POS, beard + 
                     " with", EVH_ACT_POS, wname }), 
                    "btrim", "." }); 

    actor("You carefully trim", friend, "'s " + beard + " with your " + 
        wname + "."); 
    target(" carefully trims your " + beard + " with " + 
           tp->query_possessive() + " " + wname + ".",
           friend); 
    all2actbb(" carefully trims", friend, "'s " + beard + 
           " with " + tp->query_possessive() + " " + wname + "."); 
    return 1; 
} 

/* tug on beard. */
varargs mixed 
btug(string str, int indirect, object trg)
{
    object tp = this_player(); 
    object *friend; 

    if (!stringp(str) && !strlen(str)) 
    {
        friend = ({ tp }); 
    } 
	if (str == "me")
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
            notify_fail("btug whose beard?\n"); 
            return 0; 
        } 

        if (sizeof(friend) > 1) 
        { 
            notify_fail("Please be more specific.\n"); 
            return 0; 
        } 
    } 

    if (!get_beard_details(friend[0]))
    { 
        notify_fail("Beard, what beard?\n"); 
        return 0; 
    } 

    if (friend[0] == tp) 
    { 
        if (indirect) 
            return ({ tp, 0, 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBD("tug"), 
                         "on", EVH_ACT_POS,
                         beard }), 
                        "btug", "." }); 

        write("You tug gently on your " + beard +".\n"); 
        allbb(" tugs gently on " + tp->query_possessive() + " "+ 
              beard +  "."); 
        return 1; 
    } 

 
    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBD("tug"), 
                     "on",  EVH_TRG_POS, 
                     beard }), 
                     "btug", "." }); 

    actor("You gently tug on", friend, "'s " + beard +"."); 
    target(" gently tugs on " + "your " + beard + ".", friend); 
    all2actbb(" gently tugs on", friend, "'s " + beard + "."); 
    return 1; 
} 

/* Emote to wash one's hair in nearby water */
varargs mixed 
bwash(string str, int indirect, object trg)
{
    object tp = this_player();
    object room;
    int room_type, contain_water;
    
    if (!get_beard_details(tp)) 
    {
       notify_fail("Some of your beard is missing, strange!\n");
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
                     EVH_ACT_POS, beard + " in the water nearby" }), 
                     "bwash", "." }); 

    write("You wash your " + beard + " in the water nearby.\n"); 
    allbb(" washes " + tp->query_possessive() + " " + 
           beard + " in the water nearby."); 
    return 1; 
}

/* end emotes */


mapping
query_cmdlist()
{
    return
    ([
        "help"     : "help",
		"bbrush"   : "bbrush",
		"bclean"   : "bclean",
		"bchin"    : "bchin",
        "bgroom"   : "bgroom",
		"bpluck"   : "bpluck",
        "brub"     : "brub",
		"brun"     : "brun",
		"bscratch" : "bscratch", 
 		"bstroke"  : "bstroke",
        "btrim"    : "btrim",
        "btug"     : "btug",
        "bwash"    : "bwash",
    ]);
}

