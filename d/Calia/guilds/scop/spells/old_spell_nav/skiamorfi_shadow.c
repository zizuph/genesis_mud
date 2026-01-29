/*
 *   Skiamorfi Shadow based off of Igneous' Disguise Shadow   
 *
 *   This shadow is used to disguise a players met/nonmet description
 *
 *   Copyright (C) Chad Richardson July 1996
 *
 *   Jaacar, July 31st, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 * Modifications by Bishop, April 2004.
 *
 * December 10th 2006: Remove LIVE_I_NEVERKNOWN prop
 * as decided by AoB is a violation of the rules.
 * The rangers have already responded to the new rules
 * and as such we should follow troop.
 * -- Navarre 
 */

#pragma save_binary
#pragma strict_types

inherit "/std/shadow";

#include <macros.h>
#include <living_desc.h>
#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

#define SW   shadow_who

//    Prototypes
private mixed query_list(mixed list, int arg);

//   Global Vars
int shield = 0;
int skiamorfi_level = 1;
string Adj1 = "large", Adj2 = "ghostly";

/*
 * Function name :  remove_disguise_shadow
 * Description   :  remove this shadow from a player.
 */
void remove_disguise_shadow() {remove_shadow();}

/*
 * Function name :  remove_shadow
 * Description   :  Removes all the props we added to the player
 *                  and removes the shadow
 */
void
remove_shadow()
{	
    destruct();
}

/*
 * Function name :  set_disguise
 * Arguments     :  *string vars,  an array of vars we need to have to make
 *                  this disguise.
 * Description   :  Does what is says... sets up the disguise.
 */
void
set_disguise(string *vars)
{
    Adj1 = vars[0];
    Adj2 = vars[1];
}

void
shield_active(int i)
{
    shield = i;
}

void
set_skiamorfi_level(int i)
{
    skiamorfi_level = i;
}

/* 
 *  All functions that this shadow masks should be placed 
 *  below this comment header, -Igneous-  
 */


/*
 * Function name :  parse_command_adjectiv_id_list
 * Description   :  Adds the disguised adverbs to the adjective list
 */
string *
parse_command_adjectiv_id_list()
{
    return ({Adj1}) + ({Adj2});
}

string *
parse_command_id_list()
{
    string *ids =  ({SW->query_real_name(), OB_NAME(SW), "presence"});
    
    if (SW->notmet_me(TP))
    {
        ids -= ({ SW->query_real_name() });
    }
 
    return ids;
}

private mixed
query_list(mixed list, int arg)
{
    if (!pointerp(list))
	return 0;
    if (!arg && sizeof(list))
	return list[0];
    else
	return list + ({});
}

varargs public mixed
query_adj(int arg)
{
    return query_list(({Adj1,Adj2}), arg);
}

public string *
query_adjs() 
{ 
    return query_list(({Adj1, Adj2}), 1);
}

public int
adjectiv_id(string str)
{
    return (member_array(str, ({Adj1, Adj2})) >= 0);
}

string
query_race_name()
{
    return "presence";
}

public varargs string
long(mixed for_obj)
{
    string sex, me_desc, other_desc;

    if (shadow_who->query_gender() == G_MALE)
    {
        sex = "male.";
    }
    else if (shadow_who->query_gender() == G_FEMALE)
    {
        sex = "female.";
    }
    else
    {
        sex = "neuter.";
    }

    if (!objectp(for_obj))
    {
        for_obj = TP;
    }

    me_desc = "You are cloaked in shadows. All of your possessions are concealed from "+
        "sight by the shadowy presence you have become.";
    
    if (skiamorfi_level == 1)
    {
        other_desc = "This strange presence is cloaked in shifting shadows." +
            " The shadows contract and expand eerily as the being moves, but" +
            " in spite of its forbidding exterior, you do not feel threatened"+
            " by it. Its shape is only vaguely humanoid, but you get a sense" +
            " that it is " + sex; 
    }
    else
    if (skiamorfi_level == 2)
    {
        other_desc = "Your breath catches as you take in the haunting beauty" +
            " of this radiant presence. It moves languidly and with purpose," +
            " and though clearly not of this world, it does not strike you as"+
            " ominous or menacing. Instead, you find it comforting to look at"+
            " and be near. Its shape is only vaguely humanoid, but you get a" +
            " sense that it is " + sex;
    }
    else
    {
        other_desc = "This mesmerizing presence has been touched by the" +
            " divine. It appears forged  from light and shadow equally," +
            " casting a glow upon its surroundings that makes them seem" +
            " greater and more alive. From the serene manner of its" +
            " movements, to the sheer majesty of its presence, everything" +
            " about this being suggests that it possesses the wisdom of the" +
            " ages. Its shape is only vaguely humanoid, but you get a sense" +
            " that it is " + sex;
    }      

    return (SW == for_obj ? me_desc : other_desc) + "\n";
} 

public string
race_sound()
{
    return "whispers in an eerie voice";
}

public void
shadow_me_transform(object target)
{
    shadow_me(target);
}

/*
 * Function   : query_not_attack_me()
 * Arguments  : who: the attacker, aid: the attack ID
 * Description: Determines whether an attack is successful
 * Returns    : true if the attack fails, false if the attack succeeds
 */
int 
query_not_attack_me(object who, int aid)
{
     if (shield && random(100) >= (100 - shield))
     {
         shadow_who->catch_tell(LANG_POSS(who->query_The_name(shadow_who)) + 
             " attack on you hits nothing but shadows and mist.\n");
         who->catch_tell("Your attack on " + shadow_who->query_the_name(who) +
             " hits nothing but shadows and mist.\n"); 
         shadow_who->tell_watcher(LANG_POSS(QCTNAME(who)) + " attack on " +
             QTNAME(shadow_who) + " hits nothing but shadows and mist.\n", 
             (({who, shadow_who})));      
     
         return 1;
     }
     
     return shadow_who->query_not_attack_me(who, aid);
}
