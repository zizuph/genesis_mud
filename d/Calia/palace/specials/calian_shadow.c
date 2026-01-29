
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
*/

#pragma save_binary

inherit "/std/guild/guild_occ_sh";
#include "defs.h"
inherit CALIAN_SPECIALS;
inherit CALIAN_UTILITY;

#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include <language.h>
#include <time.h>
#include <options.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <formulas.h>
#include <tasks.h>
#include CALIAN_HEADER
#include COUNCIL_HEADER
#include RECRUITER_HEADER
#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "calian_riposte.h"

#define MAX_PROJECTS 7
#define LAST_CALIAN_REWARD_INDEX 5
#define MEMBER_HANDLER "/d/Calia/guilds/calians/specials/calian_member_handler"

static mixed projects = ({ }); 
int mb_alarm; 
int calian_branch; // 0 = Warrior, 1 = Trainee, 2 = Follower/Applicant

static string *rewards_swarmer =
({
    "the colours of Caliana",
    "insignia of the Silver Partisan",
    "insignia of the Golden Glaive",
    "insignia of the Steel Trident",
    "insignia of the Mithril Spear",
    "insignia of the Crystalline Halberd"
});

static string *rewards_mauler = 
({ 
    "the colours of Caliana",
    "insignia of the Silver Gladius",
    "insignia of the Golden Falchion",
    "insignia of the Steel Scimitar",
    "insignia of the Mithril Sabre",
    "insignia of the Crystalline Broadsword"
}); 

mixed special_title; 

string query_guild_trainer_occ() { return ROOM("light_trainroom"); }
string query_guild_style_occ() { return "fighter"; }
string query_guild_name_occ() { return "Calian warrior's guild"; }

// Prototypes
public int          query_calian_branch();

/*
 * Function name: query_guild_tax_occ
 * Description:   Calian Tax rates are defined in the define calian.h
 *                Tax has been defined for all branches of the Calians
 * Returns:       the tax for Calians depending on branch
 */
public int 
query_guild_tax_occ() 
{
    switch (query_calian_branch())
    {
    case CALIAN_BRANCH_FOLLOWER:
        return CALIAN_FOLLOWER_TAX;
    
    case CALIAN_BRANCH_TRAINEE:
        return CALIAN_TRAINEE_TAX;       
    }

    return CALIAN_WARRIOR_TAX; 
}


/* 
 * Function:     set_calian_branch 
 * Description:  Sets the branch that the Calian will belong in.
 *               Everyone starts out as a Follower, moves on to a
 *               Trainee, and then finally to a full Calian Warrior.
 *               Followers and Trainees have less skills that they can
 *               train and less rooms that they can enter
 * Arguments:    int level - see defines above for branches
 * Returns:      int - 1 if successful, 0 if not. 
 */ 
int
set_calian_branch(int branch)
{
    int current_branch;
    
    if (shadow_who->query_wiz_level()) 
        return 0;

    if (branch != CALIAN_BRANCH_WARRIOR
        && branch != CALIAN_BRANCH_TRAINEE
        && branch != CALIAN_BRANCH_FOLLOWER)
    {
        return 0;
    }
    
    current_branch = query_calian_branch();
    if (current_branch == branch)
    {
        // The player already is set at the right level
        // Simply return success
        return 1;
    }
    
    // First remove the existing shadow. Return if failure here
    if (!(shadow_who->remove_autoshadow(CALIAN_SHADOW + ":")))
    {                                       
        return 0; 
    }

    if (!(shadow_who->add_autoshadow(CALIAN_SHADOW + ":" + branch)))
    { 
        shadow_who->add_autoshadow(CALIAN_SHADOW + ":");
        return 0; 
    } 

    // Set the branch
    calian_branch = branch;
    
    // Now set the tax rate
    shadow_who->set_guild_pref(SS_OCCUP, query_guild_tax_occ()); 
    
    return 1;
} 


/* 
 * Function:     query_calian_branch
 * Description:  Returns which branch the Calian is in. There are three
 *               phases: Follower, Trainee, Warrior
 * Returns:      0/1/2 - Follower, Trainee, or Warrior
 */ 
public int
query_calian_branch()
{
    return calian_branch;
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
    return calian_branch == CALIAN_BRANCH_WARRIOR; 
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
    return calian_branch == CALIAN_BRANCH_TRAINEE; 
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
    return calian_branch == CALIAN_BRANCH_FOLLOWER; 
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


/* Set up team shadows in those who are part of a team led by a Calian */
int 
team_join(object m) 
{ 
    if (!(shadow_who->team_join(m))) 
        return 0; 

    setuid();
    seteuid(getuid()); 
    if (!shadow_who->query_got_calian_team_shadow()) 
        clone_object(CRPALACE_SPECIALS + 
                     "calian_team_shadow")->shadow_me(shadow_who); 

    if (!m->query_got_calian_team_shadow()) 
        clone_object(CRPALACE_SPECIALS + 
                     "calian_team_shadow")->shadow_me(m); 

    return 1; 
} 


void
team_leave(object m)
{
    shadow_who->team_leave(m);

    m->remove_calian_team_shadow(); 
}


string
query_calian_normal_title()
{
    int occ_level, avg, title_level; 

    // Followers and Trainees have set titles. There are no variations
    // within them.
    switch (query_calian_branch())
    {
    case CALIAN_BRANCH_FOLLOWER:
        return "Follower of Caliana";
    
    case CALIAN_BRANCH_TRAINEE:
        return "Calian Trainee";
    }
    
    // Below here are the titles for full Calian Warriors
    
    occ_level = shadow_who->query_stat(SS_OCCUP); 

    /* Only the stats that make for a good warrior are considered */ 
    avg = (shadow_who->query_stat(SS_STR) + 
           shadow_who->query_stat(SS_DEX) + 
           shadow_who->query_stat(SS_CON) + 
           shadow_who->query_stat(SS_DIS)) / 4; 

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
    if (skill == SS_SWARM) return "swarm form"; 
    if (skill == SS_MOVE_BEHIND) return "move behind"; 
    if (skill == SS_MAUL) return "maul form"; 
    if (skill == SS_SWARM_KNOWLEDGE) return "swarm knowledge"; 
    if (skill == SS_MAUL_KNOWLEDGE) return "maul knowledge"; 
    if (skill == SS_CALIAN_RIPOSTE_SKILL) return "riposte";

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
    if (shadow_who->query_skill(SS_MAUL) > 
        shadow_who->query_skill(SS_SWARM)) 
        return rewards_mauler; 

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


/* Give greeting when a Calian logs on */
void
greet()
{
    tell_object(shadow_who, 
                "Greetings, " + query_guild_title_occ() + "!\n");
}


void
team_object_check()
{
    setuid();    
    seteuid(getuid());
    if (!objectp(present(CALIAN_TEAM_OBJ, shadow_who)))
         clone_object(CRPALACE_OBJECTS + "team_obj")->move(shadow_who);
    set_alarm(1.0, 0.0, greet); 
}

void
convert_to_new_calian_shadow(object player)
{
    setuid();
    seteuid(getuid());     

    MEMBER_HANDLER->convert_calian_shadow(player);
}


/* Set up some initial stuff when the Calian logs in. */ 
void 
init_occ_shadow(string str) 
{ 
    int skval; 

    ::init_occ_shadow(str); 

    if (strlen(str)) 
        sscanf(str, "%d", calian_branch); 

    // This code now just calls and converts to the new shadow stuff.
    set_alarm(1.0, 0.0, &convert_to_new_calian_shadow(shadow_who));
    return;

/*        
    // Now set the tax rate
    shadow_who->set_guild_pref(SS_OCCUP, query_guild_tax_occ()); 

    setuid();
    seteuid(getuid()); 
    council_check(); 
    setup_calian_special_title(); 
*/

/*
    if ((skval = shadow_who->query_skill(SS_SWARM)) > 
        shadow_who->query_skill(SS_SWARM_KNOWLEDGE)) 
    { 
        shadow_who->set_skill(SS_SWARM_KNOWLEDGE, skval); 
    } 
    if ((skval = shadow_who->query_skill(SS_MAUL)) > 
        shadow_who->query_skill(SS_MAUL_KNOWLEDGE)) 
    { 
        shadow_who->set_skill(SS_MAUL_KNOWLEDGE, skval); 
    } 
*/ 
/*
    set_alarm(1.0, 0.0, team_object_check); 

    shadow_who->add_subloc(CALIA_REWARD, THIS); 
    shadow_who->add_prop(CALIAN_I_WEARING_INSIGNIA, 1); 
*/
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
    shadow_who->add_prop(CALIAN_I_LAST_ATTACK_TIME, time()); 
    shadow_who->attack_object(trg); 
    if (objectp(trg) && query_calian_ready_auto_repeat(shadow_who)) 
    { 
        set_alarm(0.0, 0.0, &restart_calian_special(shadow_who)); 
    } 
}


/* 
 * Function:      calian_attacked_by_mb_hook 
 * Description:   Called when the shadowed Calian is attacked. If 
 *                s/he previously set the name of the player to 
 *                move behind, the attempt will be made automatically. 
 * Arguments:     object attacker   -  living who attacked the Calian 
 */ 
void
calian_attacked_by_mb_hook(object attacker)
{
    ::calian_attacked_by_mb_hook(attacker); 
    mb_alarm = 0; 
}


/* 
 * Function:      attacked_by 
 * Description:   Called when someone attacks the player. 
 *                This instance will set an alarm for the 
 *                player to attempt moving behind automatically 
 *                if appropriate. 
 */ 
void 
attacked_by(object attacker) 
{ 
    shadow_who->attacked_by(attacker); 
    if (!mb_alarm && objectp(attacker) && 
        query_calian_attempt_mb_automatically()) 
    { 
        mb_alarm = 
           set_alarm(0.0, 0.0, &calian_attacked_by_mb_hook(attacker)); 
    } 
} 


/* 
 * Function:     remove_prop_live_i_attack_delay 
 * Description:  When an attack delay is removed, this makes sure 
 *               to re-start a special attack if it's set to be 
 *               repeated. 
 */ 
int 
remove_prop_live_i_attack_delay() 
{ 
    int r; 

    if (!shadow_who->query_prop(LIVE_I_ATTACK_DELAY)) 
        return shadow_who->remove_prop_live_i_attack_delay(); 

    if (!(r = shadow_who->remove_prop_live_i_attack_delay())) 
    { 
        if (query_calian_ready_auto_repeat(shadow_who)) 
            set_alarm(0.0, 0.0, &restart_calian_special(shadow_who)); 
        return 0; 
    } 
    return r; 
} 


/* 
 * Function:     remove_prop_live_i_attack_delay 
 * Description:  When an attack delay is removed, this makes sure 
 *               to re-start a special attack if it's set to be 
 *               repeated. 
 */ 
int 
remove_prop_live_i_stunned() 
{ 
    int r; 

    if (!shadow_who->query_prop(LIVE_I_STUNNED)) 
        return shadow_who->remove_prop_live_i_stunned(); 

    if (!(r = shadow_who->remove_prop_live_i_stunned())) 
    { 
        if (query_calian_ready_auto_repeat(shadow_who)) 
            set_alarm(0.0, 0.0, &restart_calian_special(shadow_who)); 
        return 0; 
    } 
    return r; 
} 
