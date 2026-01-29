/* 
 * Gelan's Academy of Elemental Arts Guild Shadow
 *
 * This is the guild shadow for the Academy of Elemental Arts. Members
 * of this guild are usually young students who get to experience a
 * taste of what being in a magical guild is like.
 *
 * Created by Petros, September 2009
 */

#pragma save_binary

inherit "/std/guild/guild_lay_sh";

#include <ss_types.h>
#include <macros.h>
#include "../defs.h"

// Defines
#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

// Prototypes
public void     initialize_academic();
public object   query_top_shadow();
public void     notify_arrival(object player);

public string 
query_guild_style_lay() 
{ 
    return GUILD_STYLE; 
}

public string 
query_guild_name_lay() 
{ 
    return GUILD_NAME; 
}

int 
query_guild_tax_lay() 
{ 
    return GUILD_TAX; 
}

/* 
 * Return 1 if they try to join an occupational guild, since
 * people in the cadets can't have an occupation. Set up a notify 
 * fail to say why in response to the join action. 
 */ 
public int
query_guild_not_allow_join_lay(object player, string type, 
                               string style, string name) 
{
    if ((type == "occupational") && !player->query_wiz_level()) 
    { 
         notify_fail("You may not be in the Academy " +
                     "and have an occupation.\n"); 
         return 1;
    } 

    return ::query_guild_not_allow_join_lay(player, type, style, name);
}

void
init_lay_shadow(string str)
{
    ::init_lay_shadow(); 

    set_alarm(1.0, 0.0, initialize_academic);
}

public void
initialize_academic()
{
    setuid();
    seteuid(getuid());
    
    // Make sure the command soul gets added
    shadow_who->add_cmdsoul(ACADEMIC_SOUL);
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);

    shadow_who->update_hooks();
    
    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }
    
    shadow_who->catch_tell("\nWelcome, Academic. The mysteries of the "
        + "Elemental Arts await!\n\n");
    
    // Clone the guild object
    if (!present("academic_guild_object", shadow_who))
    {
        clone_object(ACADEMIC_GUILD_OBJECT)->move(shadow_who, 1);
    }

    notify_arrival(shadow_who); 
}

public void
remove_shadow()
{
    // We use the removal of the shadow as a way to ensure that the
    // spells for the command soul are removed.
    ACADEMIC_SOUL->remove_spells(shadow_who);
    
    // We also need to remove the mana shadow. This removal assumes
    // that the person can only have one caster guild shadow.
    query_top_shadow()->remove_mana_shadow();
        
    ::remove_shadow();    
}

public string 
query_guild_title_lay() 
{
    string * gstat_titles = ({ "Initiate",  "Apprentice", "Adept", 
        "Experienced", "Advanced" });
    string * practice_titles = ({ "Pupil", "Student", "Learner", 
        "Scholar", "Academic" });
    
    int guild_stat = shadow_who->query_stat(SS_LAYMAN);
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
    string chosen_element;
    if (chosen_element = ACADEMIC_MANAGER->query_primary_element(shadow_who))
    {
        chosen_element = capitalize(chosen_element);
    }
    int practice_level = ACADEMIC_MANAGER->query_practice_level(shadow_who);
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
query_guild_trainer_lay()
{
    return ACADEMIC_SCHOOL + "joinroom";
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
    // If the person's data file indicates that they are not a member,
    // we don't want to keep this player.
    if (!ACADEMIC_MANAGER->query_is_member(player))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function:    record_illegal_attack
 * Description: This function will do the actual record keeping for
 *              when an Academic attacks someone that they shouldn't.
 */
public void
record_illegal_attack(object player, object target)
{
    if (ACADEMIC_MANAGER->is_casting_banned(player))
    {
        player->catch_tell("For continuing to break the rules of conduct "
            + "your ban from casting combat spells has been extended by "
            + "another day.\n");
    }
    else
    {
        player->catch_tell("For breaking the rules of conduct, you have "
            + "now been banned from casting combat spells for a day.\n");
    }
    ACADEMIC_MANAGER->add_casting_ban(player);
}

/*
 * Function:    attack_object
 * Description: Academics should not attack other academics, Cadets,
 *              and Gelan npcs. They are in Gelan to learn, not to
 *              cause trouble. If they attack someone they're not
 *              supposed to, they will be warned. On the third such
 *              attempt, they will be banned from using their abilities
 *              for a day.
 */
public void
attack_object(object ob)
{
    if (!IN_ARRAY(shadow_who, ob->query_enemy(-1))
        && !IN_ARRAY(ob, shadow_who->query_enemy(-1)))
    {
        // Initiated attack
        if (IS_MEMBER(ob) || IS_GELAN_NPC(ob) || IS_CADET(ob))
        {
            record_illegal_attack(shadow_who, ob);
        }
    }
    
    shadow_who->attack_object(ob);
}

/*
 * Function name: notify_you_killed_me
 * Description  : This routine is called in the killer when it causes the death
 *                of the victim. It can be used for additional processing.
 *
 *                This routin does not actually exist. It is a trick to fool
 *                the document maker.
 * Arguments    : object victim - the victim we caused to perish.
 */
public void
notify_you_killed_me(object victim)
{
    shadow_who->notify_you_killed_me(victim);
    
    if (IS_MEMBER(victim) || IS_GELAN_NPC(victim) || IS_CADET(victim))
    {
        // Illegal to kill someone you're not supposed to.
        // Kicked from guild immediately.
        shadow_who->catch_tell("You have killed someone, directly violating "
            + "the rules of the Academy of Elemental Arts. As a result, you "
            + "are expelled from the school.\n");
        ACADEMIC_MANAGER->add_join_restricted(shadow_who);
        ACADEMIC_STARTROOM->leave_guild(shadow_who);
    }
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

public int
is_academic()
{
    return IS_MEMBER(shadow_who);
}

public void
notify_arrival(object player)
{
    if (!objectp(player))
    {
        return;
    }

    object * members, * wizards, * audience;
    
    string name = player->query_real_name();
    members = filter(users(), &->is_academic());
    members -= ({ player }); // don't notify self.
    wizards = filter(members, &->query_wiz_level());
    if (!sizeof(members))
        return;

    if (!player->query_wiz_level() 
        && !wildmatch("*jr", player->query_real_name()))    
    {
        // Don't announce juniors and wizards to normal members
        audience = members;
    }
    else
    {
        // Wizards should always be notified about everyone
        audience = wizards;
    }
    map(audience, &->catch_msg("You sense a ripple through the air "
        + "as " + capitalize(name) + " awakens in the Academy.\n"));    
}
