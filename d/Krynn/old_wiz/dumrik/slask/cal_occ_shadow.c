/*
  Guild shadow for the Calian warriors guild

  Created by Glykron from a file made by Nick

  History:
    New titles & team-title additions added to query_guild_title_occ()
      by Maniac 3/94
    Council additions added by Maniac 5/94
    Check for whether display of insignia is turned on or off, Maniac 12/94
    query_guild_trainer_occ() added                            Maniac 2/95
    move down for sanctbanned calians put in guild.c room instead  Maniac " 
    Took out swarm stuff, all in cmdsoul                     Maniac  19/7/95
    
*/

inherit "/std/guild/guild_occ_sh";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include "defs.h"
#include CALIAN_HEADER
#include COUNCIL_HEADER

static string *rewards =
({
    "the colours of Caliana",
    "insignia of the Silver War Hammer",
    "insignia of the Golden Axe",
    "insignia of the Steel Spear",
    "insignia of the Mithril Halberd",
    "insignia of the Crystalline Sword"
});


string query_guild_trainer_occ() { return ROOM("light_trainroom"); }
string query_guild_style_occ() { return "fighter"; }
string query_guild_name_occ() { return "Calian warrior's guild"; }
int query_guild_tax_occ() { return GUILD_TAX; }

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
    switch(THIS->query_gender())
    {
        case G_MALE:        return "man";
        case G_FEMALE:        return "woman";
        case G_NEUTER:        return "monster";
    }
}

string
query_guild_title_occ()
{
    int occ_level, str, dex, con, dis, avg, title_level;
    object this;
    string team_title, team_name;

    this = THIS;

    occ_level = this->query_stat(SS_OCCUP);

    str = this->query_stat(SS_STR);
    dex = this->query_stat(SS_DEX);
    con = this->query_stat(SS_CON);
    dis = this->query_stat(SS_DIS);

    /* Only the stats that make for a good warrior are considered */
    avg = (str + dex + con + dis) / 4;

    /* Now work out the Calian team title, if any */
    if (this->query_team_others() == ({ }) )
        team_title = "";
    else
    {
        if (sizeof(this->query_team()) > 0)
        {
            team_name = this->query_prop(CALIAN_S_TEAM_TITLE);
            if (team_name)
                team_title = ", Proud Leader of " + team_name;
            else
                team_title = "";
        }
        else
        {
            team_name = this->query_leader()->query_prop(CALIAN_S_TEAM_TITLE);
            if (team_name)
                team_title = ", Trusted Member of " + team_name;
            else
                team_title = "";
        }
    }

    /* Title now reflects the effectiveness of the warrior, as well
       as the level of SS_OCCUP */
    title_level = (occ_level + avg) / 2;

    switch (title_level / 11)
    {
    case 0:
        return "Calian Trainee" + team_title;
    case 1:
        return "Calian Adventurer" + team_title;
    case 2:
        return "Warrior of Calia" + team_title;
    case 3:
        return "Swords" + query_gender_title() + " of Calia" + team_title;
    case 4:
        return "Swashbuckler of Calia" + team_title;
    case 5:
        return "Comrade in Arms of Calia" + team_title;
    case 6:
        return "Cavalier of Calia" + team_title;
    case 7:
        return "Paladin of Calia" + team_title;
    case 8:
        return "Defender of Calia" + team_title;
    case 9:
        return "Noble" + query_gender_title() + " of Calia" + team_title;
    case 10:
        return "Calian Champion" + team_title;
    case 11:
        return "Weapon Master of Calia" + team_title;
    case 12:
        if (this->query_gender() == G_FEMALE)
            return "Battle Heroine of Calia" + team_title;
        else
            return "Battle Hero of Calia" + team_title;
    case 13:
        return "War Legend of Calia" + team_title;
    default:
        return "Exalted Member of Caliana's Elite Guard" + team_title;
    }
}

string
query_guild_skill_name(int skill)
{
    if (skill == SS_SWARM) return "swarm";
    if (skill == SS_MOVE_BEHIND) return "move behind";
    return 0;
}

string
show_subloc(string subloc, object on, object for_obj)
{
    string data;
    int level;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != CALIA_REWARD)
        return on->show_subloc(subloc, on, for_obj);

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

/* Function to check for punishments or rewards set by the council
 * for this player, carries them out if there are any.  Returns 1
 * if player still in guild, 0 if not.
 */
int
council_check(object pl)
{
    seteuid(getuid());
    COUNCIL_CODE->carry_out_punishments(pl);
    if (COUNCIL_CODE->is_expelled(pl))
        return 0;
    else return 1;
}

void
init_occ_shadow(string str)
{
    ::init_occ_shadow(str);
    if (council_check(shadow_who))
    {
        set_alarm(1.5, 0.0, "greet");
        shadow_who->add_subloc(CALIA_REWARD, THIS);
        shadow_who->add_prop(CALIAN_I_WEARING_INSIGNIA, 1);
    }
}


/* Give greeting when a Calian logs on */
void
greet()
{
    shadow_who->catch_msg("Greetings, " + query_guild_title_occ() + "!\n");
}



