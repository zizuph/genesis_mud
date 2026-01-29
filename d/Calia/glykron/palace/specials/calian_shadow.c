
/* 
  Guild shadow for the Calian warriors guild 

  Created by Glykron from a file made by Nick 

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
*/

#pragma save_binary

inherit "/std/guild/guild_occ_sh";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include <language.h>
#include <time.h>
#include "defs.h"
#include CALIAN_HEADER
#include COUNCIL_HEADER
#include RECRUITER_HEADER

#define MAX_PROJECTS 7

static mixed projects = ({ }); 

static string *rewards =
({
    "the colours of Caliana",
    "insignia of the Silver War Hammer",
    "insignia of the Golden Axe",
    "insignia of the Steel Spear",
    "insignia of the Mithril Halberd",
    "insignia of the Crystalline Sword"
});

mixed special_title; 

string query_guild_trainer_occ() { return ROOM("light_trainroom"); }
string query_guild_style_occ() { return "fighter"; }
string query_guild_name_occ() { return "Calian warrior's guild"; }
int query_guild_tax_occ() { return GUILD_TAX; }


/* This function allows some players to have larger mailboxes */ 
int
query_guild_leader_occ()
{
    string pn;

    pn = shadow_who->query_real_name(); 
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
    int r, i;
    object *to_sh = ({ });
    
    r = shadow_who->team_join(m);

    if (!r)
        return r;

    if (!shadow_who->query_got_calian_team_shadow())
        to_sh += ({shadow_who});

    if (!m->query_got_calian_team_shadow())
        to_sh += ({m});

   seteuid(getuid());
   for (i = 0; i < sizeof(to_sh); i++) 
     clone_object(GLYKRON_SPECIALS+"calian_team_shadow")->shadow_me(to_sh[i]); 

   return r;
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
    int occ_level, str, dex, con, dis, avg, title_level; 

    occ_level = shadow_who->query_stat(SS_OCCUP);

    str = shadow_who->query_stat(SS_STR);
    dex = shadow_who->query_stat(SS_DEX);
    con = shadow_who->query_stat(SS_CON);
    dis = shadow_who->query_stat(SS_DIS);

    /* Only the stats that make for a good warrior are considered */
    avg = (str + dex + con + dis) / 4;

    /* Title now reflects the effectiveness of the warrior, as well
       as the level of SS_OCCUP */
    title_level = (occ_level + avg) / 2;

    switch (title_level / 11)
    {
    case 0:
    case 1:
        return "Calian Trainee";
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

    seteuid(getuid()); 
    e = 
    CALIAN_TITLE_HANDLER->query_calian_title_el(shadow_who->query_real_name()); 

    if (pointerp(e) && (sizeof(e) > 1))  
        special_title = capitalize(e[0] + e[1]); 
    else
        special_title = 0;
}


/* The guild title. This can vary according to title options 
   that involve a special title (see the title handler) */ 
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
    if (skill == SS_SWARM) return "swarm";
    if (skill == SS_MOVE_BEHIND) return "move behind";
    if (skill == SS_MAUL) return "maul";

    if ((skill == CALIAN_OPTIONS) || (skill == PUNISHMENT) ||  
        (skill == REWARD) || (skill == CALIAN_RACK_POINTS)) 
        return ""; 
    return 0;
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
    level = shadow_who->query_skill(REWARD);
    if (level > (sizeof(rewards) - 1))
        level = sizeof(rewards) - 1;

    if (for_obj != on)
        data = capitalize(on->query_pronoun()) +
            " is wearing " + rewards[level] + ".\n";
    else
        data = "You are wearing " + rewards[level] + ".\n";

    return data;
}


/* Function to do punishments or rewards set by the council
 * for this player just after player logs in.
 */
void
council_check()
{
    seteuid(getuid());
    COUNCIL_CODE->carry_out_punishments(shadow_who);
}


void
team_object_check()
{
    seteuid(getuid());
    if (!objectp(present(CALIAN_TEAM_OBJ, shadow_who)))
         clone_object(GLYKRON_OBJECTS+"team_obj")->move(shadow_who);
}


/* Give greeting when a Calian logs on */ 
void 
greet() 
{ 
    shadow_who->catch_msg("Greetings, " + query_guild_title_occ() + "!\n"); 
    if (shadow_who->query_wiz_level()) { 
        shadow_who->catch_tell(
            "---------------------------------------------------\n" + 
            "The directories for the Calian guild have changed.\n" + 
            "Please update your shadow to:\n" + 
            "/d/Calia/palace/specials/calian_shadow:\n" + 
            "And your cmdsoul to:\n" + 
            "/d/Calia/palace/specials/calian_cmdsoul\n"); 
    } 
} 


/* Set up some initial stuff when the Calian logs in. */ 
void
init_occ_shadow(string str)
{
    ::init_occ_shadow(str);
    seteuid(getuid()); 
    council_check();
    setup_calian_special_title(); 
    set_alarm(1.0, 0.0, team_object_check); 
    set_alarm(1.5, 0.0, greet);
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
}

