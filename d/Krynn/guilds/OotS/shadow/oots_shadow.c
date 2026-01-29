/* 
 * Krynn's Order of the Stars layman clerical guild. 
 * Arman, April 2017
 */

#pragma save_binary

inherit "/std/guild/guild_lay_sh";

#include <ss_types.h>
#include <macros.h>
#include <const.h>
#include <composite.h>
#include "../defs.h"
#include "/d/Krynn/common/defs.h"

// Defines
#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"
#define MAX_GUILD_LEVEL 8
#define MERCYFUL        "_knight_mercyful"
#define L_SWORD         4

// Prototypes
public void     initialize_oots();
public object   query_top_shadow();

void remove_lay_member();

static string *order_titles = ({"Believer in the Old Gods",
  "Convert of ",
  "Faithful of ",
  "Follower of ",
  "Fervent Follower of ",
  "Disciple of ",
  "Learned Disciple of ",
  "Devout Disciple of ",
  "Cleric of the Holy Order of the Stars, Disciple of ",});

static string *knight_titles = ({"Pious Cohort of the Order of Clerists",
  "Adherent of the Order of Clerists",
  "Devotee of the Order of Clerists",
  "Advocate of the Order of Clerists",
  "Reverent Advocate of the Order of Clerists",
  "Paladin of the Order of Clerists",
  "Devout Paladin of the Order of Clerists",
  "Righteous Paladin of the Order of Clerists",
  "Lord Paladin of the Order of Clerists",});

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

public int
query_guild_level_lay()
{
    int layman_stat = min(60, query_shadow_who()->query_stat(SS_LAYMAN));

    // 4,350,000 guild skill needed to reach max level.
    int guild_stat;

    if(shadow_who->query_skill(OOTS_GUILD_XP) > 0)
       guild_stat = max(0, OOTS_GUILD_STAT_FORMULA(shadow_who));
    else
       guild_stat = 0;

    return MIN(MAX_GUILD_LEVEL, 
              (layman_stat + guild_stat) / OOTS_PROGRESSION_MOD);
}

int 
query_guild_tax_lay() 
{ 
      return GUILD_TAX; 
}

void
init_lay_shadow(string str)
{
    ::init_lay_shadow(); 

    set_alarm(1.5, 0.0, initialize_oots);
    set_alarm(5.0, 0.0, &query_guild_keep_player(shadow_who));
}

public void
initialize_oots()
{
    setuid();
    seteuid(getuid());
    
    // Make sure the command soul gets added
    shadow_who->add_cmdsoul(OOTS_SOUL);
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);

    shadow_who->update_hooks();
    
    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }
    
    // Clone the guild object
    if (!present("oots_guild_object", shadow_who))
    {
        clone_object(OOTS_GUILD_OBJECT)->move(shadow_who, 1);
        shadow_who->command("$wear oots_guild_object");
    }
 
}

public void
remove_shadow()
{
    // We use the removal of the shadow as a way to ensure that the
    // spells for the command soul are removed.
    OOTS_SOUL->remove_spells(shadow_who);
    
    // We no longer need to remove the mana shadow. 

    // query_top_shadow()->remove_mana_shadow();
        
    ::remove_shadow();    
}

public string 
query_guild_title_lay() 
{
    string  god  = OOTS_MANAGER->query_oots_god(shadow_who);
    int     glev = query_guild_level_lay();
    
    if (shadow_who->query_alignment() < 100)
        return "Fallen Follower of the Old Gods";

    if (shadow_who->query_alignment() < 600)
        return "Faithless Sceptic of " + god;

    if (shadow_who->query_guild_name_occ() == "Solamnian Knights")
    {
        if (shadow_who->query_knight_level() < L_SWORD || god != "Kiri-Jolith")
        {
            if (glev > 0)
                return order_titles[glev] + god;
            else
                return order_titles[glev];
        }

        return knight_titles[glev];
    }

    // check top shadow  
    if (query_top_shadow()->query_guild_name_occ() == "Solamnian Knights")
    {
        if (query_top_shadow()->query_knight_level() < L_SWORD || god != "Kiri-Jolith")
        {
            if (glev > 0)
                return order_titles[glev] + god;
            else
                return order_titles[glev];
        }

        return knight_titles[glev];
    }

    if (glev > 0)
        return order_titles[glev] + god;
    else
        return order_titles[glev];
}

mixed
query_guild_trainer_lay()
{
    return ({ "/d/Krynn/guilds/OotS/room/joinroom",
           });

}

/*
 * Function name: acceptable_oots_member
 * Description:   test to see if the player is an acceptable member of this
 *                guild.
 * Arguments:     object who - the player to test
 * Returns:       0 or a string message saying why the player isn't acceptable
 */
mixed
acceptable_oots_member(object who)
{
    string race_name = who->query_race_name();

    if(IN_ARRAY(race_name, OOTS_INELIGIBLE_RACES))
    {
        return "Your medallion of faith starts smouldering and then " +
          "suddenly burns into ashes. Your choice of " +race_name+ " is " +
          "antithesis to the teachings of the Holy Order of the Stars.\n";
    }

    if(who->query_alignment() < 100)
    {
        return "Your medallion of faith starts smouldering and then " +
          "suddenly burns into ashes. You have strayed too far from the " +
          "path of goodness for you to remain with the Holy Order " +
          "of the Stars.\n";
    }

    return 0;
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

    // player->catch_tell("DEBUG: query guild keep queried.\n");
    
    if (!result)
    {
        // Even the base shadow doesn't want to keep this player. Just return.
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    // If the person's data file indicates that they are not a member,
    // we don't want to keep this player.
    if (!OOTS_MANAGER->query_is_member(player))
    {
        return 0;
    }

    mixed why;

    if (stringp(why = acceptable_oots_member(player)))
    {
        player->catch_msg(why);
        set_alarm(1.0, 0.0, remove_lay_member);
        return 1;
    }
    
    return 1;
}

/*
 * Function name: query_guild_not_allow_join_lay
 * Description:  Check if we allow that the player joins another guild. 
 * Arguments:     player - the player
 *  type, style, name - the type, style and name of the
 *intended guild.
 * Returns:  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_lay(object player, string type, string style,
  string name)
{
    
    if (::query_guild_not_allow_join_lay(player, type, style, name))
        return 1;

    notify_fail("The Holy Order of the Stars requires holy " +
                "devotion and dedication.\n");

    setuid();
    seteuid(getuid());
    
    if (name == "Orcs of Middle Earth")
    {
        player->catch_msg("Orcs are antithesis to the teaching of the " +
           "Holy Order of the Stars.\n");            
        return 1;
    }

    if (name == "Solamnian Knights")
    {
       // Must be knight of the Sword or higher to join, however can
       // join the knights if already a OotS

/* 
       if(player->query_knight_level() < 4)
       {
        player->catch_msg("Only those who have passed the Measure of " +
           "the Sword may be righteous knights of the Order of " +
           "Clerists and members of the Holy Order of the Stars.\n");            
        return 1;
       }
*/

    }
    
    return 0;
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
is_oots()
{
    return IS_MEMBER(shadow_who);
}

public string
query_oots_god()
{
    return OOTS_MANAGER->query_oots_god(shadow_who);
}


/* 
 * Function name: query_guild_skill_name
 * Description:   Give a names for the guild's special skills
 * Arguments:     type - the number of the skill
 * Returns:          0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    if (type == OOTS_GUILD_SKILL)
    {
        return "spiritual lore";
    }

    return 0;
}

/*
 * Function name: remove_lay_member
 * Description:   remove this member from the guild
 */
void
remove_lay_member()
{
    // Clear guild stat, remove guild learn, and begin skill decay
    shadow_who->clear_guild_stat(SS_LAYMAN); 
    shadow_who->setup_skill_decay(); 
    shadow_who->set_guild_pref(SS_LAYMAN, 0);
    // The penalty for leaving means if you rejoin if you have some
    // work to regain levels.
    shadow_who->set_skill(OOTS_GUILD_XP, -100000);

    // Reset the start location of the person leaving the guild
    if (shadow_who->query_default_start_location() == (OOTS_STARTROOM))
    {
        shadow_who->set_default_start_location(shadow_who->query_def_start());
    }

    // Remove the command soul
    shadow_who->remove_cmdsoul(OOTS_SOUL);
    shadow_who->update_hooks();
    
    // Remove the guild object
    object guild_object = present("oots_guild_object", shadow_who);
    if (objectp(guild_object))
    {
        shadow_who->command("$remove oots_guild_object");
        guild_object->remove_object();
    }
    
    // Update the Guild Manager
    OOTS_MANAGER->remove_member(shadow_who);
    OOTS_MANAGER->remove_oots_god(shadow_who);
    OOTS_REMOVE_ALL_REV(shadow_who);

    shadow_who->remove_guild_lay();

    //shadow_who->catch_msg("DEBUG: Got to end of remove_lay_member\n");

}

/**********************************************************
 * Shadowed functions within the player object
 **********************************************************/
/*
 * Function name: set_alignment
 * Description:	  Sets the alignment of a player, we will check if
 * 	          the alignment is getting out of bounds for a priest
 * Arguments:	  a - The amount of points
 */
public void
set_alignment(int a)
{
    int current_alignment = shadow_who->query_alignment();
    int near_expulsion = 120;
    int no_cast_limit = 600;
    int casting_penalty = 1000;
    int cast_penalty, cast_warning;

    if(current_alignment < no_cast_limit)
        cast_penalty = 1;
    else
        cast_penalty = 0;

    // DEBUG("Alignment value: " +a);

    if(current_alignment < casting_penalty)
        cast_warning = 1;
    else
        cast_warning = 0;
	
    shadow_who->set_alignment(a);

    if (cast_penalty && (shadow_who->query_alignment() > no_cast_limit))
    {
    	tell_object(shadow_who,"Once more you walk a path aligned with " +
    	"the Gods of Good, and regain your divine spells.\n");
    }

    if (!cast_penalty && (shadow_who->query_alignment() < no_cast_limit))
    {
    	tell_object(shadow_who,"You no longer walk a path aligned with " +
    	"the Gods of Good. They will not answer your prayers until you " +
        "return to a more righteous path.\n");
    }

    if (!cast_warning && (shadow_who->query_alignment() < casting_penalty))
    {
    	tell_object(shadow_who,"Your actions are diverging from the path " +
           "of the righteous. Your holy spells will progressively become " +
           "less effective if you continue down this path.\n");
    }

    if ((shadow_who->query_alignment() < near_expulsion))
    {
    	tell_object(shadow_who,"You no longer walk a path aligned with " +
    	"the Gods of Good, and are dangerously close to being ejected " +
        "from the Holy Order.\n");
    }

    // Expel if alignment drops to neutral
    if ((shadow_who->query_alignment() < 100))
    {
    	tell_object(shadow_who,"Your medallion of faith starts smouldering " +
          "and then suddenly burns into ashes. You have strayed too far " +
          "from the path of goodness for you to remain with the Holy " +
          "Order of the Stars.\n");

        setuid();
        seteuid(getuid());
        OOTS_JOINROOM->leave_guild(shadow_who);
     }

}

public void
notify_you_killed_me(object victim)
{
    int victim_align = victim->query_alignment(); 

    // There are a maximum of 19 possible revelations
    int revelations = m_sizeof(OOTS_MANAGER->query_oots_revelations(shadow_who));

    // DEBUG("No. of revelations: "+revelations+ ".");

    // Guild stat reduced when you kill anything not evil
    // Takes into account whether the knight is merciful or not
    if((victim_align > 200) && 
       ((victim->query_prop(MERCYFUL) != shadow_who)))
    {
        OOTS_ADD_EXP(shadow_who, (0 - (victim_align)));

        // DEBUG("Guild xp reduced by: " +(victim_align)+ ".");
    }
    else
    {
        // Defeating evil creatures around the same size or 
        // bigger gives guild xp
        // The number of revelations the member has discovered 
        // impacts this range
        int xp_mod = 20 + revelations + victim->query_average_stat() - 
                     shadow_who->query_average_stat();
        
        // The number of revelations the member has discovered provides 
        // an xp bonus of up to +18.
        int rev_bonus = revelations;
        int victim_xp;

        if(xp_mod < 0)
          victim_xp = 0;
        else
          victim_xp = rev_bonus + min(60, 0 - (victim_align / 20));

        OOTS_ADD_EXP(shadow_who, victim_xp);

    }   

    shadow_who->notify_you_killed_me(victim);
}