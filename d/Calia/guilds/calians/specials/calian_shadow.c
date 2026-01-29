
/* 
  Guild shadow for the Calian warriors guild 

  Created by Glykron from a file made by Nick 
  Coders: Maniac and Glykron 

  History: 
    New titles & team-title additions added to query_guild_title_occ()
      by Maniac 4/94 
    Council additions added by Maniac 5/94 
    Check for whether display of insignia is turned on or off, Maniac 12/94 
    query_guild_trainer_occ() added                            Maniac 2/95 
    Took out swarm stuff, all in cmdsoul                     Maniac  19/7/95 
    Added check for Calian special titles, by Maniac 28/12/95 
    Changed handling of team titles, Maniac, 11.1.96 
    Minor changes to calian titles, Maniac, 17/5/96 
    "list project to" support added, Maniac, 17/6/96 
    Title handling modified slightly, Maniac, 15/7/96 
    Switched to general calian options handling, Maniac, 17/9/96 
    catch rack reward skill and maul, Maniac, 31/10/96 
    query_guild_leader_occ() added, Maniac, 30/11/96 
    title handling made more efficeint, Maniac, 17/3/97 
    CALIAN_I_LAST_ATTACK_TIME operation added, Maniac, 7/5/99 
    catch_projected_image added, Maniac, 17/12/00 
    Included specials from soul into shadow, by Maniac 24/3/01
    Updated specials now inherited, new rewards, 
    automatic move behind attempt, Maniac, 14/6/01 
    Added check for re-starting specials after stun, Maniac, 29/6/01 
    Added checks for swarm/maul knowledge skills, Maniac, 3/7/01 
    Added trainee support, Maniac, 13/3/02
    Added trainee tax, Maniac, 24/4/02
    Added riposte special, riposte skill, Bishop, 08/6/05
    Revamped specials to use Genesis Specials, Petros, July 2008
    Assisting against someone who is attackng you no longer stops 
       Move Behind, Petros, July 2009
    At the request of Council member Budwise I altered the title
    ranking formula so it is harder to get to top title, Arman, July 2020
    Fixed shadow cloning, Cotillion, December 2020
*/

#pragma save_binary

inherit "/std/guild/guild_occ_sh";
#include "defs.h"
inherit CALIAN_UTILITY;
inherit SPECIALS_UTILITY;

#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include <language.h>
#include <time.h>
#include <options.h>
#include <files.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <formulas.h>
#include <tasks.h>
#include <adverbs.h>
#include CALIAN_HEADER
#include COUNCIL_HEADER
#include RECRUITER_HEADER
#include DEBUGGER_TELL

#define MAX_PROJECTS 7
#define LAST_CALIAN_REWARD_INDEX 5

static mixed projects = ({ }); 

private string hands_str = 0;           // which hand to attack with 
private string swarm_adv = "fiercely";  // swarm adverb 
private string mb_adv = "quickly";      // mb adverb 
private string mb_player = 0;           // automatic move behind target 
private mixed  special_title; 
private int    stop_swarm_alarm;        // alarm when someone is attacked

static string *rewards_swarmer =
({
    "the colours of Caliana",
    "insignia of the Silver Partisan",
    "insignia of the Golden Glaive",
    "insignia of the Steel Trident",
    "insignia of the Mithril Spear",
    "insignia of the Crystalline Halberd"
});

string query_guild_trainer_occ() { return ROOM("light_trainroom"); }
string query_guild_style_occ() { return "fighter"; }
string query_guild_name_occ() { return "Calian warrior's guild"; }


/*
 * Function name: has_calian_shadow
 * Description:   This shadow always returns true. Used in the specials
 *                to check whether the person can execute the specials.
 * Returns:       1 - true
 */
public int
has_calian_shadow()
{
    return 1;
}

/*
 * Function name: query_top_shadow
 * Description:   Because shadows exist in layers, sometimes you need
 *                to reference functions in a shadow above you. Calling
 *                functions can fail if one doesn't call from the top
 *                shadow. this function allows one to obtain the
 *                top most shadow, giving access to all functions.
 * Returns:       object - top level shadow
 */
public object
query_top_shadow()
{
    object last_me, me;
    
    me = shadow_who;
    last_me = me;
    while (me = shadow(me, 0))
    {
        // loop through to find the top level shadow who
        last_me = me;
    }   
    
    // We return now the top level shadow
    return last_me;
}

/*
 * Function name: remove_calian_shadow
 * Description:   Quick and easy way to remove the Calian shadow
 * Returns:       nothing
 */
public void
remove_calian_shadow()
{
    remove_shadow();
}

/* 
 * Function:     is_calian_warrior
 * Description:  Gives back 1 if the shadowed player is a 
 *               Calian warrior, 0 otherwise. 
 * Returns:      int - 1 or 0. 
 */ 
public int 
is_calian_warrior() 
{ 
    return CALIAN_MEMBER_HANDLER->query_is_warrior(shadow_who->query_real_name());
} 

/* 
 * Function:     is_calian_trainee 
 * Description:  Gives back 1 if the shadowed player is a 
 *               Calian trainee, 0 otherwise. 
 * Returns:      int - 1 or 0. 
 */ 
public int 
is_calian_trainee() 
{ 
    return CALIAN_MEMBER_HANDLER->query_is_trainee(shadow_who->query_real_name());
} 

/* 
 * Function:     is_calian_follower
 * Description:  Gives back 1 if the shadowed player is a 
 *               Calian follower, 0 otherwise. 
 * Returns:      int - 1 or 0. 
 */ 
public int 
is_calian_follower() 
{ 
    return CALIAN_MEMBER_HANDLER->query_is_follower(shadow_who->query_real_name());
} 

/*
 * Function name: query_guild_tax_occ
 * Description:   Calian Tax rates are defined in the define calian.h
 *                Tax has been defined for all branches of the Calians
 * Returns:       the tax for Calians depending on branch
 */
public int 
query_guild_tax_occ() 
{
    int branch;
    string name;
    
    setuid();
    seteuid(getuid()); 
    name = shadow_who->query_real_name();
    branch = CALIAN_MEMBER_HANDLER->query_calian_branch(name);
    return CALIAN_MEMBER_HANDLER->query_guild_tax(branch);
}

/* This function allows some players to have larger mailboxes */ 
int
query_guild_leader_occ()
{
    string pn;

    pn = shadow_who->query_real_name(); 
    setuid();
    seteuid(getuid()); 

    return (COUNCIL_CODE->is_council_member(pn) || 
            RECRUITER_CODE->is_recruiter(pn)); 
}

int
query_guild_not_allow_join_occ(object player, string type, string style,
    string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;
    notify_fail("We brave fighters don't like to mess with magic.\n");
    if (style == "magic") return 1;
    return 0;
}


private string
query_gender_title()
{
    switch (shadow_who->query_gender())
    {
        case G_MALE: 
                   return "man";
                   break;
        case G_FEMALE: 
                   return "woman";
                   break;
        case G_NEUTER: 
                   return "monster";
                   break;
    }
}

public void
add_riposte_evade()
{
    object riposte_object, defended, top_shadow;
    object * evade_effects;
    
    top_shadow = query_top_shadow();
    defended = top_shadow->query_shadow_who();
    evade_effects = top_shadow->query_evade_effects();
    if (evade_effects)
    {
        // There are evade effects in place right now. we need to
        // go through and ensure that we aren't duplicating an
        // existing riposte evade already.
        foreach (object evade_obj : evade_effects)
        {
            if (evade_obj->is_riposte_evade())
            {
                return;
            }
        }
    }
    
    // Didn't find any swarm evade effects from the defender
    riposte_object = clone_object(RIPOSTE_EVADE_OBJ);
    riposte_object->set_effect_caster(defended);
    riposte_object->set_effect_target(defended);
    riposte_object->move(defended, 1);
    riposte_object->add_evade_effect(defended);
}

public void
add_swarm_evade(object defender)
{
    object swarm_object, defended, top_shadow;
    object * evade_effects;
    
    top_shadow = query_top_shadow();
    defended = top_shadow->query_shadow_who();
    evade_effects = top_shadow->query_evade_effects();
    if (evade_effects)
    {
        // There are evade effects in place right now. we need to
        // go through and ensure that we aren't duplicating an
        // existing swarm evade already.
        foreach (object evade_obj : evade_effects)
        {
            if (!evade_obj->is_swarm_evade())
            {
                continue;
            }
            
            if (evade_obj->query_effect_caster() == defender)
            {
                // Found a swarm evade from the defender
                return;
            }
        }
    }
    
    // Didn't find any swarm evade effects from the defender
    swarm_object = clone_object(SWARM_EVADE_OBJ);
    swarm_object->set_effect_caster(defender);
    swarm_object->set_effect_target(defended);
    swarm_object->move(defended, 1);
    swarm_object->add_evade_effect(defended);
}

public void
remove_swarm_evade(object defender)
{
    object defended, top_shadow;
    object * evade_effects;
    
    top_shadow = query_top_shadow();
    defended = top_shadow->query_shadow_who();
    evade_effects = top_shadow->query_evade_effects();
    if (!evade_effects)
    {
        send_debug_message("swarm_evade", "No swarm evade effects found "
                         + "to be removed in " + defended->query_real_name());
        return;
    }
    
    foreach (object evade_obj : evade_effects)
    {
        if (!evade_obj->is_swarm_evade())
        {
            continue;
        }
        
        if (evade_obj->query_effect_caster() == defender)
        {
            send_debug_message("swarm_evade", "Removing swarm evade "
                             + "object from person "
                             + defended->query_real_name() + " for "
                             + "defender " + defender->query_real_name());
            evade_obj->remove_object();
        }
    }
}

public int
set_leader(object leader)
{
    int result;
    
    object * team, * calians;
    if (!objectp(leader))
    {
        // We are leaving a team
        team = shadow_who->query_team_others();
        calians = filter(team, &->has_calian_shadow());

        foreach (object calian : calians)
        {
            calian->remove_swarm_evade(shadow_who);
            remove_swarm_evade(calian);
        }         
        result = shadow_who->set_leader(leader);
    }
    else
    {
        // We are setting a new leader
        result = shadow_who->set_leader(leader);
        team = shadow_who->query_team_others();
        calians = filter(team, &->has_calian_shadow());
    
        foreach (object calian : calians)
        {
            calian->add_swarm_evade(shadow_who);
            add_swarm_evade(calian);
        }        
    }
    
    return result;
}

static void
add_team_shadow(object target)
{
    if (target->query_got_calian_team_shadow())
        return;

    object sh = clone_object(CRPALACE_SPECIALS + "calian_team_shadow");
    if (!sh->shadow_me(target)) 
    {
        sh->remove_shadow();
    }
}

/*
 * Function name: team_join
 * Description  : Make someone a member of our team.
 *                Fails if we have a leader, then we can't lead others.
 *                Set up team shadows in those who are part of a team
 *                a Calian.
 * Arguments    : object member - The new member of my team.
 * Returns      : int - 1/0 success/failure.
 */
public int 
team_join(object m) 
{ 
    object * team, * calians, * evade_effects;
    object swarm_object;
    
    if (!(shadow_who->team_join(m))) 
        return 0; 

    add_team_shadow(shadow_who);
    add_team_shadow(m);

    return 1; 
} 

/*
 * Function name: team_leave
 * Description  : Someone leaves my team.
 * Arguments    : object member - the member leaving my team.
 */
public void
team_leave(object m)
{     
    shadow_who->team_leave(m);
    m->remove_calian_team_shadow();   

    if (!sizeof(shadow_who->query_team_others()))
    {
        // if there are no more members of my team, remove shadow
        query_top_shadow()->remove_calian_team_shadow();
    }
}

public string
query_calian_normal_title()
{
    int occ_level, avg, title_level, branch; 
    string name;
    
    // Followers and Trainees have set titles. There are no variations
    // within them.
    name = shadow_who->query_real_name();
    branch = CALIAN_MEMBER_HANDLER->query_calian_branch(name);
    if (CALIAN_MEMBER_HANDLER->query_is_follower(name))
    {
        return "Follower of Caliana";
    }
    else if (CALIAN_MEMBER_HANDLER->query_is_trainee(name))
    {
        return "Calian Trainee";
    }
    
    // Below here are the titles for full Calian Warriors
    
    occ_level = shadow_who->query_stat(SS_OCCUP); 

    /* Only the stats that make for a good warrior are considered */ 
    avg = (shadow_who->query_stat(SS_STR) + 
           shadow_who->query_stat(SS_DEX) + 
           shadow_who->query_stat(SS_CON) + 
           shadow_who->query_stat(SS_DIS)) / 8; 

    /* 
     * Title now reflects the effectiveness of the warrior, as well 
     * as the level of SS_OCCUP. 
     */ 
    title_level = (occ_level + avg) / 2;

    switch (title_level / 11)
    {
    case 0:
    case 1:
        return "Calian Initiate";
    case 2:
        return "Calian Adventurer";
    case 3:
        return "Warrior of Calia";
    case 4:
        return "Swords" + query_gender_title() + " of Calia";
    case 5:
        return "Swashbuckler of Calia";
    case 6:
        return "Comrade in Arms of Calia";
    case 7:
        return "Cavalier of Calia";
    case 8:
        return "Calian Fighter";
    case 9:
        return "Defender of Calia";
    case 10:
        return "Noble" + query_gender_title() + " of Calia";
    case 11:
        return "Calian Champion";
    case 12:
        if (shadow_who->query_gender() == G_FEMALE)
            return "Weapon Mistress of Calia";
        else
            return "Weapon Master of Calia";
    case 13:
        if (shadow_who->query_gender() == G_FEMALE)
            return "Battle Heroine of Calia";
        else
            return "Battle Hero of Calia";
    case 14:
        return "War Legend of Calia";
    default:
        return "Exalted Member of Caliana's Elite Guard";
    }
}


/* 
 *  This is the special title, for instance "Goldenwolf". 
 *  It is set up in setup_calian_special_title() 
 */ 
mixed
query_calian_special_title()
{
    return special_title; 
}


void
setup_calian_special_title()
{
    mixed e;

    setuid();
    seteuid(getuid());
    e =
    CALIAN_TITLE_HANDLER->query_calian_title_el(shadow_who->query_real_name()); 

    if (pointerp(e) && (sizeof(e) > 1)) 
        special_title = capitalize(e[0] + e[1]); 
    else 
        special_title = 0; 
}


/* 
 * The guild title. This can vary according to title options 
 * that involve a special title (see the title handler) 
 */ 
string
query_guild_title_occ()
{
    string normal_title; 
    int v;

    v = shadow_who->query_skill(CALIAN_OPTIONS); 

    if ((v & CALOPT_TITLE_SPECIAL) || (v & CALOPT_TITLE_MIXED)) {  
        if (!stringp(special_title)) 
            v = CALOPT_TITLE_NORMAL; 
    } 

    if (v & CALOPT_TITLE_SPECIAL) 
        return (special_title + " of Calia"); 

    normal_title = query_calian_normal_title(); 

    if (v & CALOPT_TITLE_MIXED) 
        return (special_title + ", " + normal_title); 

    return normal_title; 
}


string
query_guild_skill_name(int skill)
{
    if (skill == SS_MOVE_BEHIND) return "move behind"; 
    if (skill == SS_SWARM_KNOWLEDGE) return "swarm"; 
    if (skill == SS_CALIAN_RIPOSTE_SKILL) return "riposte";

    // These skills are for guild specific record keeping.
    if ((skill == CALIAN_OPTIONS) || (skill == PUNISHMENT) || 
        (skill == REWARD) || (skill == CALIAN_RACK_POINTS)) 
        return ""; 
    return 0;
}


/* 
 * Function:      query_appropriate_calian_reward_arr 
 * Description:   Should return an array of possible reward 
 *                descriptions based on whether the shadowed 
 *                Calian is a swarmer or mauler. 
 * Returns:       string * - reward descriptions. 
 */ 
private string * 
query_appropriate_calian_reward_arr() 
{ 
    return rewards_swarmer; 
} 


string
show_subloc(string subloc, object on, object for_obj)
{
    string data; 
    int level; 

    if (subloc != CALIA_REWARD) 
        return on->show_subloc(subloc, on, for_obj); 

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) 
        return ""; 

    if (!shadow_who->query_prop(CALIAN_I_WEARING_INSIGNIA)) 
         return ""; 

    level = min(shadow_who->query_skill(REWARD), LAST_CALIAN_REWARD_INDEX); 

    if (for_obj != on) 
        data = capitalize(on->query_pronoun()) + 
               " is wearing " + 
               query_appropriate_calian_reward_arr()[level] + ".\n"; 
    else 
        data = "You are wearing " + 
                query_appropriate_calian_reward_arr()[level] + ".\n"; 

    return data; 
}


/* 
 * Function to do punishments or rewards set by the council
 * for this player just after player logs in.
 */
void
council_check()
{
    setuid();    
    seteuid(getuid());
    COUNCIL_CODE->carry_out_punishments(shadow_who);
}


public void
notify_player_about_active_vote(object player)
{
    // Give a notification to the player if there is an active vote.
    if (!IS_PLAYER_OBJECT(player))
    {
        // Only players should receive the notification.
        return;
    }
    string player_name = player->query_real_name();
    if (!CALIAN_MEMBER_HANDLER->query_is_warrior(player_name))
    {
        // Only Full Calian Warriors will see the vote.
        return;
    }
    setuid();
    seteuid(getuid());
    mapping active_vote = COUNCIL_VOTING_MANAGER->get_active_vote();
    if (!active_vote)
    {        
        return;
    }    
    string category = active_vote["category"];
    int vote_id = active_vote["id"];
    // Check to see if the voter has already cast a vote
    mapping votes = COUNCIL_VOTING_MANAGER->get_votes_cast(vote_id);
    int has_cast_vote = 0;
    if (votes[player_name])
    {
        // Player has already cast a vote
        has_cast_vote = 1;
    }
    string vote_message = "";
    switch (category)
    {
    case "nomination":
        vote_message += "There is an active nomination process right now. ";
        if (has_cast_vote)
        {
            vote_message += "You have already nominated " 
                + capitalize(votes[player_name]) + " for a Council position.\n";
        }
        else
        {
            vote_message += "You have not yet nominated anyone for a Council "
                + "position.\n";
        }
        break;
    
    case "council":
        vote_message += "There is an active council vote right now. ";
        if (has_cast_vote)
        {
            vote_message += "You have already cast a vote for " 
                + capitalize(votes[player_name]) + " to become a member of the "
                + "Calian Council.\n";
        }
        else
        {
            vote_message += "You have not yet voted for anyone to become a "
                + "member of the Calian Council.\n";
        }
        break;

    default:
        return;
    }
    vote_message = "\n"
                 + sprintf("%'='75s\n", "") 
                 + sprintf("%=-75s", vote_message)
                 + sprintf("%'='75s\n\n", "");
    player->catch_tell(vote_message);
}

/* Give greeting when a Calian logs on */
void
greet(object player)
{
    tell_object(player, "Greetings, " + query_guild_title_occ() + "!\n");
    
    // This will check to see if there's an active vote and will notify the
    // Calian member about their current actions for the vote.
    notify_player_about_active_vote(player);
}


void
setup_calian_objects()
{
    setuid();    
    seteuid(getuid());
    
    // Calians need the following things when they log in:
    // 1. Calian Team Object
    // 2. Riposte evade object and shadow
    // 3. Swarm evade object and shadow
    if (!objectp(present(CALIAN_TEAM_OBJ, shadow_who)))
    {
        clone_object(CRPALACE_OBJECTS + "team_obj")->move(shadow_who);
    }
    
    add_swarm_evade(shadow_who);
    add_riposte_evade();

    set_alarm(1.0, 0.0, &greet(shadow_who)); 
}


/* Set up some initial stuff when the Calian logs in. */ 
void 
init_occ_shadow(string str) 
{ 
    int skval, branch; 
    string name;
    
    ::init_occ_shadow(str); 

    setuid();
    seteuid(getuid()); 

    // Now set the tax rate
    shadow_who->set_guild_pref(SS_OCCUP, query_guild_tax_occ()); 

    council_check(); 
    setup_calian_special_title(); 

    set_alarm(1.0, 0.0, setup_calian_objects); 

    shadow_who->add_subloc(CALIA_REWARD, THIS); 
    shadow_who->add_prop(CALIAN_I_WEARING_INSIGNIA, 1);     
} 


/* List Project To Support */ 
void 
list_project_to() 
{
    int i, t, j, n; 
    string s; 

    if (!(j = sizeof(projects))) { 
        tell_object(shadow_who, 
            "You have received no Calian projects " + 
            "during this visit to the realms.\n"); 
        return; 
    } 

    n = j / 3; 
    if (n == 1) 
        s = ("This is the last Calian project that you have received " + 
             "during this visit to the realms:\n\n"); 
    else 
        s = ("These are the last " + LANG_WNUM(n) + " Calian projects " + 
             "that you have received during this visit to the realms:\n\n"); 
    t = time(); 

    for (i = 0; i < j; i += 3) 
        s += (projects[i] + " (" + (CONVTIME(t - projects[i + 2])) + 
             " ago):\n" + projects[i + 1] + "\n\n"); 

    shadow_who->more(s); 
}


/* Records a new project to in an array */ 
void
add_project_to(string sender, string message)
{
    if (sizeof(projects) == (MAX_PROJECTS*3)) 
        projects = exclude_array(projects, 0, 2); 

    projects += ({ sender, message, time() }); 
}


/* This is called from Calian medallions */ 
void
catch_project_to(string sender, string message)
{
    sender = capitalize(sender); 
    message = capitalize(message); 

    tell_object(shadow_who, sender + " projects " + 
               "a thought to you:\n" + message + "\n");
    // Send this to the GMCP for players who use the web client
    shadow_who->gmcp_comms("project", sender,
        sender + " projects a thought to you: " + message);

    add_project_to(sender, message); 
}


/* This is called from Calian medallions */ 
void 
catch_projected_image(string sender, string message) 
{
    tell_object(shadow_who, message); 
    add_project_to(capitalize(sender), message); 
}


void
attack_object(object trg)
{
    if (!IN_ARRAY(trg, shadow_who->query_enemy(-1))
        && !IN_ARRAY(shadow_who, trg->query_enemy(-1)))
    {
        send_debug_message("calian_shadow", "Attacking someone "
            + "who is not on the enemy list.");
        // Prop added to prevent move behind after an attack
        shadow_who->add_prop(CALIAN_I_LAST_ATTACK_TIME, time()); 
    }
    shadow_who->attack_object(trg); 
}
                           
/* 
 * Function:     calian_change_hands 
 * Description:  Action function to change the hand that is used 
 *               for the "swarm" special
 * Arguments:    string str - predicate 
 * Returns:      int - success. 
 */ 
int 
calian_change_hands(string str) 
{
    string specials;
    
    if (this_object()->query_shadow_who() != TP) 
        return 0; 

    specials = "<swarm> special.";
    
    if (str == "right" || str == "rhand") 
    { 
        hands_str = "right"; 
        write("You prefer to attack with the weapon wielded in " + 
              "the RIGHT hand when using the " + specials + "\n"); 
        return 1; 
    } 
    else if (str == "left" || str == "lhand") 
    { 
        hands_str = "left"; 
        write("You prefer to attack with the weapon wielded in the " + 
              "LEFT hand when using the " + specials + "\n"); 
        return 1; 
    } 
    else if (str == "both") 
    { 
        hands_str = "both"; 
        write("You prefer to attack with a weapon wielded in " + 
              "BOTH hands when using the " + specials + "\n"); 
        return 1; 
    } 

    if (!stringp(str) || !strlen(str)) 
    { 
        if (!stringp(hands_str)) 
        { 
            write("You have not specified which hand(s) " + 
                  "you prefer to attack with when using the " + 
                  specials + "\n"); 
            return 1; 
        } 
        write("You prefer to attack with " + 
              (hands_str == "both" ? "a " : "the ") + 
              "weapon wielded in " + 
              (hands_str == "both" ? "BOTH hands" : "the " + 
              (hands_str == "left" ? "LEFT" : "RIGHT") + " hand") + 
              " when using the " + specials + "\n"); 
        return 1; 
    } 
    notify_fail(capitalize(query_verb()) + " [left/right/both]?\n"); 
    return 0; 
} 


/* 
 * Function:     calian_set_adverb 
 * Description:  Set adverb to be used with swarm or move behind specials. 
 * Arguments:    string str - predicate 
 * Returns:      int - success 
 */ 
int 
calian_set_adverb(string str) 
{ 
    string *tmp, spec, adv, usage; 
    int ix; 

    if (this_object()->query_shadow_who() != TP) 
        return 0; 

    usage = "<calian specials | move behind | swarm> <how>"; 

    /*
     * If no argument or syntax was incorrect, give 
     * adverb status for each special and describe 
     * correct syntax. 
     */ 
    if (!stringp(str) || !strlen(str) || 
        (sizeof(tmp = explode(str, " ")) < 2) || 
        (sizeof(tmp) > 3)) 
    {
        spec = "Currently you carry out move behind " + mb_adv;
        spec += " and swarm " + swarm_adv;
        spec += ". To make a change, try:\n" + query_verb() 
              + " " + usage + ".\n";
        write(spec);
        return 1; 
    } 

    /* 
     * Get text for special and adverb. 
     */ 
    if (sizeof(tmp) == 2) 
    { 
        spec = lower_case(tmp[0]); 
        adv = tmp[1]; 
    } 
    else 
    { 
        spec = lower_case(tmp[0]) + " " + tmp[1]; 
        adv = tmp[2]; 
    } 

    /* 
     * Check that full adverb exists. 
     */ 
    if (!strlen(adv = FULL_ADVERB(adv))) 
    { 
        notify_fail("That adverb is unknown.\n"); 
        return 0; 
    } 

    /* 
     * Set adverb for special(s). 
     */ 
    switch (spec) 
    { 
        case "calian specials" : 
            mb_adv = swarm_adv = adv; 
            break; 
        case "move behind" : 
            mb_adv = adv; 
            break; 
        case "swarm" : 
            swarm_adv = adv; 
            break; 
        default : 
            notify_fail(capitalize(query_verb()) + " " 
                      + usage + "?\n");
            return 0; 
    } 

    /* 
     * Give final confirmation message about the adverb to the Calian. 
     */ 
    write(capitalize(spec) + " will be carried out " + adv + "!\n"); 
    return 1; 
} 

/* 
 * Function:     query_swarm_adverb 
 * Description:  Returns the adverb being used for swarm
 * Arguments:    none
 * Returns:      the string for the adverb
 */ 
public string
query_swarm_adverb()
{
    return swarm_adv;
}

/* 
 * Function:     query_mb_adverb 
 * Description:  Returns the adverb being used for move behind
 * Arguments:    none
 * Returns:      the string for the adverb
 */ 
public string
query_mb_adverb()
{
    return mb_adv;
}

/* 
 * Function:     query_calian_main_weapon 
 * Description:  Should return the main weapon wielded by the 
 *               shadowed Calian, or 0 if no weapon is wielded. 
 *               If a preference was stated about which hand to 
 *               use, that is checked first. Otherwise, the 
 *               default order of checks is: right, left, both. 
 * Arguments:    object player - the Calian 
 * Returns:      object - The main weapon 
 */ 
public object 
query_calian_main_weapon() 
{
    object weapon, player; 

    player = shadow_who;
    if (hands_str == "left") 
    { 
        if (objectp(weapon = player->query_weapon(W_LEFT)))
            return weapon; 

        if (objectp(weapon = player->query_weapon(W_RIGHT))) 
            return weapon; 

        return player->query_weapon(W_BOTH); 
    } 
    else if (hands_str == "both") 
    {
        if (objectp(weapon = player->query_weapon(W_BOTH))) 
            return weapon; 

        if (objectp(weapon = player->query_weapon(W_RIGHT)))
            return weapon; 

        return player->query_weapon(W_LEFT); 
    } 

    if (objectp(weapon = player->query_weapon(W_RIGHT))) 
        return weapon; 

    if (objectp(weapon = player->query_weapon(W_LEFT)))
        return weapon; 

    return player->query_weapon(W_BOTH); 
}


/* 
 * Function:     try_assist 
 * Description:  If this_player() not in combat, try assisting. 
 * Returns:      object - who is fought, 0 if no-one. 
 */ 
public object 
try_assist(int auto)
{
    object enemy; 

    /* 
     * If not in combat yet, assist and check again. 
     */ 
    if (!objectp(enemy = TP->query_attack())) 
    { 
        TP->command("$assist"); /* Will assist a fellow team member */ 
        if (!objectp(enemy = TP->query_attack())) 
        { 
            calian_special_notify_fail("You are not fighting anyone.\n", 
                TP, auto); 
            return 0; 
        } 
    } 
    else 
    { 
        /* 
         * To avoid the swarmer's paradox you need to swarm an enemy who 
         * is not attacking someone who is attacking someone who is 
         * attacking you, which results in a knot. That sentence is not 
         * a typo! 
         */ 
        if (((enemy->query_attack())->query_attack())->query_attack() == TP) 
        { 
            TP->command("$assist"); /* Will assist a fellow team member */ 
            if (!objectp(enemy = TP->query_attack())) 
            { 
                calian_special_notify_fail("You are not fighting anyone.\n", 
                     TP, auto); 
                return 0; 
            } 
        } 
    } 
    return enemy; 
}

public string
query_mb_target()
{
    return mb_player;
}

public void
set_mb_target(string player)
{
    mb_player = player;
}

/*
 * Function name: query_prop
 * Description  : Find the value of a property. This function is usually
 *                implemented as CFUN, i.e. as real C implementation in the
 *                gamedriver as it is used so often. You should NOT mask this
 *                function in code. Use VBFC on the property value, if you
 *                must.
 * Arguments    : mixed prop - the name of the property (usually a string).
 * Returns      : mixed - the value of the property, or 0 if the property did
 *                    not exist..
 */
public mixed
query_prop(string prop)
{
    object attacker, player;
    // Calians are allowed to execute their special. As of this writing,
    // (October 2009), they have a 4 second preparation period during which
    // the cannot be attacked. During the 6 second cooldown, they can be
    // attacked.
    //
    // Additionally, Calians get a 1-2 second period during which they cannot
    // be attacked following a move behind. This is slightly different from
    // the Knight's rescue. The move behind ability takes about a second to
    // execute, and can fail. Giving them a second or two before they attack
    // is a fair protection scheme. The main purpose here is so that they can
    // set themselves up to do a swarming attack, which gives them protection
    // anyway.
    if (prop == OBJ_M_NO_ATTACK)
    {
        attacker = this_player();
        player = query_shadow_who();
        if ((time() - random(2) - 1) <= player->query_prop(CALIAN_I_LAST_MOVE_BEHIND)
            || SWARM_ABILITY->query_ability_preparing(player))
        {
            string fail_message;
            switch (random(2))
            {
            case 0:
                fail_message = "You move to attack " + player->query_the_name(attacker)
                    + ", but are unable to follow the quick movements as "
                    + player->query_pronoun() + " ducks out of harm's way.\n";
                break;
            
            case 1:
            default:
                fail_message = "You try and catch up to the movements of "
                    + player->query_the_name(attacker) + ", but the strange "
                    + "combat dance that " + player->query_pronoun() + " seems "
                    + "to be dancing confuses you.\n";
                break;    
            }
            return fail_message;
        }
    }
    
    // All other properties, just return the base.
    return shadow_who->query_prop(prop);
}
