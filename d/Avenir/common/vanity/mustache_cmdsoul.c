// /d/Avenir/common/vanity/mustache_cmdsoul.c
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
 * Details of stache, instantiated during emotes. 
 */ 
string length, colour, style, mustache; 

/* 
 * Function name: get_soul_id
 * Description:   give identification of soul
 * Arguments:     none
 * Returns:       string with id
 */
string
get_soul_id()
{
    return "VanityMustache";
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


/* Get mustache details of a particular player */ 
int 
get_mustache_details(object player) 
{ 

    if (!(length = player->query_mustache_length())) 
        return 0; 

    if (!(colour = player->query_mustache_colour())) 
        return 0; 

    if (!(style = player->query_mustache_style())) 
        return 0; 
	
	if (!(mustache = length +" "+ colour +" "+ style)) 
        return 0; 
	
    return 1; 
} 


/* Help on mustache emotes */ 
int 
help(string str) 
{ 
    if (str != "mustache") 
        return 0; 

    this_player()->more("You have the following emotes available "+ 
                        "for your mustache:\n\n"+ 
           "mbrush [me|them] - brush your mustache [against their cheek].\n"+ 
		   "mclean [me|them] - clean your|their mustache.\n"+
           "mgroom [me|them] - remove the day's debris from your|their mustache.\n"+
           "mpluck           - pull a stray hair from your mustache.\n"+
           "mrun   [me|them] - run your fingers through your|their mustache.\n"+
           "mscratch         - scratch lip through mustache.\n"+
           "mstroke          - stroke your mustache thoughtfully.\n"+
           "mtrim  [me|them] - trim your|their mustache.\n"+		   
           "mtug   [me|them] - tug gently on your|their mustache.\n"+
           "mtwirl           - twirl the ends of your mustache.\n"+
           "mwash            - wash your mustache.\n"+		   
           "\n   Mustache emotes can be used in double emotes - see \"help double\".\n"); 
    return 1; 
} 


/* Brush your or someone else's mustache */
varargs mixed 
mbrush(string str, int indirect, object trg)
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
            notify_fail("Brush who with your mustache?\n"); 
            return 0; 
        } 

        if (sizeof(friend) > 1) 
        { 
            notify_fail("Please be more specific.\n"); 
            return 0; 
        } 
    } 

    if (!get_mustache_details(tp))
    { 
        notify_fail("Mustache? What mustache?\n"); 
        return 0; 
    } 
		
    if (friend[0] == tp) 
    { 
        if (indirect) 
            return ({ tp, 0, 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBD("brush"), 
                         EVH_ACT_POS, "fingers through", 
                         EVH_ACT_POS, mustache }), 
                         "mbrush", "." }); 

        write("You brush your fingers through your " +  mustache +".\n"); 
        allbb(" brushes " + tp->query_possessive() + " fingers through " + 
              tp->query_possessive() + " " + mustache + "."); 
        return 1; 
    } 

    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBD("brush"), 
                     EVH_TRG_OBJ, "'s cheek with",
					 EVH_ACT_POS, mustache }), 
                     "mbrush", "." }); 

    actor("You brush", friend, "'s cheek with your "+ 
        mustache +"."); 
    target(" brushes your cheek with " + tp->query_possessive() +
        mustache +".", friend); 
    all2actbb(" brushes " + tp->query_possessive() + 
        mustache + " against", 
        friend, "'s cheek."); 
    return 1; 
} 



/* Emote for cleaning a mustache. */
varargs mixed 
mclean(string str, int indirect, object trg)
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
            notify_fail("mclean whose mustache?\n"); 
            return 0; 
        } 

        if (sizeof(friend) > 1) 
        { 
            notify_fail("Please be more specific.\n"); 
            return 0; 
        } 
    } 

    if (!get_mustache_details(friend[0])) 
    { 
        notify_fail("Mustache? What mustache?\n"); 
        return 0; 
    } 

    if (friend[0] == tp) 
    { 
        if (indirect) 
            return ({ tp, 0, 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBD("clean"), 
                         EVH_ACT_POS, 
                         mustache }),
                         "mclean", "." }); 

        write("You quickly clean your " + mustache + ".\n"); 
        allbb(" quickly cleans " + tp->query_possessive() + 
              " "+ mustache + "."); 
        return 1; 
    } 

    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBD("comb"), 
                     EVH_ACT_POS, "fingers through", 
                     EVH_TRG_OBJ, "'s "+ mustache +					  
                     "to clean it up"}), 
                     "mclean", "." }); 

    actor("You run your fingers through", friend, "'s " + 
        mustache +", giving it a quick clean."); 
    target(" runs " + tp->query_possessive() + " fingers through " + 
        "your " + mustache +", giving it a quick clean.", friend); 
    all2actbb(" quickly combs " + tp->query_possessive() + 
        " fingers through", friend, "'s " + mustache + ", cleaning it."); 
    return 1; 
} 


/* Emote for grooming a mustache. */
varargs mixed 
mgroom(string str, int indirect, object trg)
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
            notify_fail("mgroom whose mustache?\n"); 
            return 0; 
        } 

        if (sizeof(friend) > 1) 
        { 
            notify_fail("Please be more specific.\n"); 
            return 0; 
        } 
    } 

    if (!get_mustache_details(friend[0])) 
    { 
        notify_fail("That person doesn't seem to have a mustache.\n"); 
        return 0; 
    } 

    if (friend[0] == tp) 
    { 
        if (indirect) 
            return ({ tp, 0, 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBD("groom"), 
                         EVH_ACT_POS, 
                         mustache }), "mgroom", "." }); 

        write("You groom your " + mustache + ", removing the day's debris from it.\n"); 
        allbb(" grooms " + tp->query_possessive() + mustache + "."); 
        return 1; 
    } 

    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBD("groom"), 
                     "the "+ mustache +" on",
                     EVH_TRG_OBJ }), 
                     "mgroom", "." }); 

    actor("You groom", friend, "'s " + mustache +", removing the day's debris from it."); 
    target(" grooms your " + mustache +", removing the day's debris from it.", friend); 
    all2actbb(" quickly grooms", friend, "'s " + mustache + "."); 
    return 1; 
} 



/* pluck a stray hair out of mustache  */
varargs mixed 
mpluck(string str, int indirect, object trg)
{
    object tp = this_player(); 
   	if (str && str != "me")
    {
       notify_fail("You can only pluck your own beard.\n"); 
       return 0;          
    }   
  
    if (!get_mustache_details(tp)) 
    { 
       notify_fail("Some of your mustache is missing, strange!\n"); 
       return 0; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, "quickly", EVH_VERB("pluck"), 
                    "a stray hair from", EVH_ACT_POS, 
                    mustache }), 
                    "mpluck", "." }); 

    write("You quickly pluck a stray hair from your " + mustache + ".\n"); 
    allbb(" quickly plucks a stray hair from " + tp->query_possessive() 
        + " " + mustache + "."); 
    return 1; 
}


/* run fingers through mustache. */
varargs mixed 
mrun(string str, int indirect, object trg)
{
    object tp = this_player(); 
    object *friend; 

    if (!stringp(str) && !strlen(str)) 
    {
        friend = ({ tp }); 
    }
    if (str != "me") 
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
            notify_fail("mrun whose mustache?\n"); 
            return 0; 
        } 

        if (sizeof(friend) > 1) 
        { 
            notify_fail("Please be more specific.\n"); 
            return 0; 
        } 
    } 

    if (!get_mustache_details(friend[0])) 
    { 
        notify_fail("That person doesn't seem to have a mustache.\n"); 
        return 0; 
    } 

    if (friend[0] == tp) 
    { 
        if (indirect) 
            return ({ tp, 0, 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBD("run"), 
                         EVH_ACT_POS, "fingers through",
						 EVH_ACT_POS,
                         mustache }), 
                        "mrun", "." }); 

        write("You slowly run your fingers through your " + 
              mustache + ".\n"); 
        allbb(" slowly runs " + tp->query_possessive() + 
              " fingers through " + tp->query_possessive() + 
              " " + mustache +  "."); 
        return 1; 
    } 

    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBD("run"), 
                     EVH_ACT_POS, "fingers through the "+ 
                     mustache +" on", EVH_TRG_OBJ }), 
                     "mrun", "." }); 

    actor("You slowly run your fingers through", friend, "'s " + 
        mustache +"."); 
    target(" slowly runs " + tp->query_possessive() + " fingers through " + 
        "your " + mustache +".", friend); 
    all2actbb(" slowly runs " + tp->query_possessive() + " fingers through", 
        friend, "'s " + mustache + "."); 
    return 1; 
} 


/* scratch an itch through the mustache */
varargs mixed 
mscratch(string str, int indirect, object trg)
{
    object tp = this_player(); 
  
  	if (str && str != "me")
    {
       notify_fail("You can only scratch your own beard.\n"); 
       return 0;          
    }
	
    if (!get_mustache_details(tp)) 
    { 
       notify_fail("Some of your mustache is missing, strange!\n"); 
       return 0; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, "idly", EVH_VERB("scratch"), 
                     EVH_ACT_POS, "upper lip through", EVH_ACT_POS,
                     mustache }), 
                    "mscratch", "." }); 

    write("You idly scratch your upper lip through your " + 
          mustache +".\n"); 
    allbb(" idly scratches " + tp->query_possessive() + 
          " upper lip through " + tp->query_possessive() + " " + 
          mustache + "."); 
    return 1; 
}

/* Stroke one's mustache thoughtfully. */
varargs mixed
mstroke(string str, int indirect, object trg)
{
    object tp = this_player(); 

	if (str && str != "me")
    {
       notify_fail("You can only stroke your own beard.\n"); 
       return 0;          
    }

    if (!get_mustache_details(tp)) 
    { 
       notify_fail("Some of your mustache is missing, strange!\n"); 
       return 0; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, "thoughtfully", 
                     EVH_VERBE("stroke"), EVH_ACT_POS, 
                     mustache }), 
                    "mstroke", "." }); 

    write("You thoughtfully stroke your " + mustache +".\n"); 
    allbb(" thoughtfully strokes " + tp->query_possessive() + " " + 
           mustache + "."); 
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


/* Emote to trim someone's mustache with a wielded (edged) weapon */
varargs mixed
mtrim(string str, int indirect, object trg)
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
                notify_fail("Trim whose mustache?\n"); 
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
        if (!get_mustache_details(tp)) 
        { 
            notify_fail("Some of your mustache is missing, strange!\n"); 
            return 0; 
        } 

        if (indirect) 
            return ({ tp, 0, 0, 1, 
                      ({ EVH_ACT_SBJ, "carefully", EVH_VERBD("trim"), 
                         EVH_ACT_POS, mustache +
                         " with", EVH_ACT_POS, wname }), 
                         "mtrim", "." }); 

        write("You carefully trim your " + mustache + " with your " 
              + wname + ".\n"); 
        allbb(" carefully trims " + tp->query_possessive() + " " + 
               mustache + " with " + 
               tp->query_possessive() + " " + wname + "."); 
        return 1; 
    } 

    if (!get_mustache_details(friend[0])) 
    { 
        notify_fail("That person doesn't seem to have a trimmable mustache.\n"); 
        return 0; 
    } 

    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, "carefully", EVH_VERBD("trim"), 
                     EVH_TRG_POS, mustache + " with", 
                     EVH_ACT_POS, wname }), 
                    "mtrim", "." }); 

    actor("You carefully trim", friend, "'s " + mustache + 
          " with your " + wname + "."); 
    target(" carefully trims your " + mustache + 
          " with " + tp->query_possessive() + " " + wname + ".",
           friend); 
    all2actbb(" carefully trims", friend, "'s " + mustache + 
          " with " + tp->query_possessive() + " " + wname + "."); 
    return 1; 
} 

/* tug on mustache. */
varargs mixed 
mtug(string str, int indirect, object trg)
{
    object tp = this_player(); 
    object *friend; 

    if (!stringp(str) && !strlen(str)) 
    {
        friend = ({ tp }); 
    }
    if (str != "me") 
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
            notify_fail("mtug whose mustache?\n"); 
            return 0; 
        } 

        if (sizeof(friend) > 1) 
        { 
            notify_fail("Please be more specific.\n"); 
            return 0; 
        } 
    } 

    if (!get_mustache_details(friend[0])) 
    { 
        notify_fail("That person doesn't seem to have a mustache.\n"); 
        return 0; 
    } 

    if (friend[0] == tp) 
    { 
        if (indirect) 
            return ({ tp, 0, 0, 0, 
                      ({ EVH_ACT_SBJ, EVH_VERBD("tug"), 
                         "on", EVH_ACT_POS,
                         mustache }), 
                        "mtug", "." }); 

        write("You tug gently on your " + mustache + ".\n"); 
        allbb(" tugs gently on " + tp->query_possessive() + " "+ 
              mustache +  "."); 
        return 1; 
    } 

    if (indirect) 
        return ({ tp, friend[0], 0, 1, 
                  ({ EVH_ACT_SBJ, EVH_VERBD("tug"), 
                     "on",  EVH_TRG_POS, 
                     mustache }), 
                     "mtug", "." }); 

    actor("You gently tug on", friend, "'s " + mustache +"."); 
    target(" gently tugs on your " + mustache +".", friend); 
    all2actbb(" gently tugs on", friend, "'s " + mustache + "."); 
    return 1; 
} 


/* twirl the ends of the mustache  */
varargs mixed 
mtwirl(string str, int indirect, object trg)
{
    object tp = this_player(); 
    
    if (!get_mustache_details(tp)) 
    { 
       notify_fail("Some of your mustache is missing, strange!\n"); 
       return 0; 
    } 

    if (indirect) 
        return ({ tp, 0, 0, 0, 
                  ({ EVH_ACT_SBJ, "slowly", EVH_VERB("twirl"), 
                    "the ends of", EVH_ACT_POS, 
                    mustache }), 
                    "mtwirl", "." }); 

    write("You slowly twirl the ends of your " + mustache + ".\n"); 
    allbb(" slowly twirls the ends of " + tp->query_possessive() 
        + " " + mustache + "."); 
    return 1; 
}





/* Emote to wash one's hair in nearby water */
varargs mixed 
mwash(string str, int indirect, object trg)
{
    object tp = this_player();
    object room;
    int room_type, contain_water;
    
    if (!get_mustache_details(tp)) 
    {
       notify_fail("Some of your mustache is missing, strange!\n");
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
                     EVH_ACT_POS, mustache + " in the water nearby" }), 
                     "b-wash", "." }); 

    write("You wash your " + mustache + " in the water nearby.\n"); 
    allbb(" washes " + tp->query_possessive() + " " + 
          mustache + " in the water nearby."); 
    return 1; 
}

/* end emotes */


mapping
query_cmdlist()
{
    return
    ([
        "help"     : "help",
		"mbrush"   : "mbrush",
		"mclean"   : "mclean",
        "mgroom"   : "mgroom",
		"mpluck"   : "mpluck",
        "mrub"     : "mrub",
		"mrun"     : "mrun",
		"mscratch" : "mscratch", 
 		"mstroke"  : "mstroke",
        "mtrim"    : "mtrim",
        "mtwirl"   : "mtwirl",
        "mtug"     : "mtug",
        "mwash"    : "mwash",
    ]);
}


