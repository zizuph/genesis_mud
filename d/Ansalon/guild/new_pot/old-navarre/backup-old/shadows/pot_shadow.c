/* 
 * Priests of Takhisis Shadow.
 *
 * Created by Navarre October 2010.
 */
#pragma save_binary

inherit "/std/guild/guild_occ_sh";

#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/guild/pot/guild.h"

// Defines
#define MANA_SHADOW         "/d/Genesis/specials/guilds/shadows/mana_shadow"
#define SPELL_MANAGER_SOUL  "/d/Genesis/specials/guilds/souls/spell_manager_soul"
#define CASTER_SOUL         "/d/Ansalon/guild/new_pot/souls/pot_soul"
#define GUILD_TAX 30

// Prototypes
public void     initialize_pot_shadow();
public object   query_top_shadow();

void
init_occ_shadow(string str)
{
    ::init_occ_shadow(); 

    set_alarm(1.0, 0.0, initialize_pot_shadow);
}

public void
initialize_pot_shadow()
{
    setuid();
    seteuid(getuid());
    
    // Make sure the command soul gets added
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);
    shadow_who->add_cmdsoul(CASTER_SOUL);

    shadow_who->update_hooks();
    
    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }    
}

public void
remove_shadow()
{
    // Remove the spells specified in the soul
    CASTER_SOUL->remove_spells(shadow_who);
    
    // We also need to remove the mana shadow. This removal assumes
    // that the person can only have one caster guild shadow.
    query_top_shadow()->remove_mana_shadow();
        
    ::remove_shadow();    
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

public string 
query_guild_style_occ() 
{ 
    return GUILD_STYLE; 
}

public string 
query_guild_name_occ() 
{ 
    return GUILD_NAME; 
}

int 
query_guild_tax_occ() 
{ 
    return GUILD_TAX; 
}

/* 
 * Return 1 if they try to join an occupational guild, since
 * people in the cadets can't have an occupation. Set up a notify 
 * fail to say why in response to the join action. 
 */ 
public int
query_guild_not_allow_join_occ(object player, string type, 
                               string style, string name) 
{
    return ::query_guild_not_allow_join_occ(player, type, style, name);
}

public string 
query_guild_title_occ() 
{
    string * gstat_titles = ({ "Initiate",  "Apprentice", "Adept", 
        "Experienced", "Advanced" });
    string * practice_titles = ({ "Pupil", "Student", "Learner", 
        "Scholar", "Academic" });
    
    int guild_stat = shadow_who->query_stat(SS_OCCUP);
    string stat_title;
    switch (guild_stat)
    {
    case 0..10:
        stat_title = gstat_titles[0];
        break;
        
    case 11..25:
        stat_title = gstat_titles[1];
        break;
        
    case 26..40:
        stat_title = gstat_titles[2];
        break;
        
    case 41..60:
        stat_title = gstat_titles[3];
        break;
        
    default:
        stat_title = gstat_titles[4];
    }
    string chosen_element = "Water";

    int practice_level = 1000;
    string practice_title;
    switch (practice_level)
    {
    case 0..150:
        practice_title = practice_titles[0];
        break;
    
    case 151..500:
        practice_title = practice_titles[1];
        break;
    
    case 501..1000:
        practice_title = practice_titles[2];
        break;
    
    case 1001..2000:
        practice_title = practice_titles[3];
        break;
    
    default:
        practice_title = practice_titles[4];        
    }
    
    string whole_title = stat_title 
        + (chosen_element ? " " + chosen_element : "")
        + " " + practice_title + " of the Elemental Arts";
    return whole_title;
} 


public string
query_guild_trainer_occ()
{
    return "";
}

/* function name: query_guild_keep_player
 * Description:   This gives you a chance to tell if you want to keep the
 *                the player when the shadow is autoloading when a player
 *                logs on.
 * Arguments:     player - the player
 * Returns:       1 - keep player, 0 - kick him out.
 */
public int
query_guild_keep_player(object player)
{
    int result = ::query_guild_keep_player(player);
    
    if (!result)
    {
        // Even the base shadow doesn't want to keep this player. Just return.
        return 0;
    }
    
    setuid();
    seteuid(getuid());

    // Add check to see if the player is a member of the guild.
    
    return 1;
}
