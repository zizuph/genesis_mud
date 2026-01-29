/* 
 * Elemental Worshippers of Calia Guild Shadow
 *
 * This is the guild shadow for the Elemental Worshippers of Calia. This is
 * a clerical layman guild. Members of this guild will
 * select one branch to focus on, which equates to serving one of
 * the Five Elementals of Calia.
 *
 * Created by Petros, December 2010
 * Added more title adjectives, June 2017 - Jaacar
 * Modified to properly execute dicharge/expel - Mirandus - 2020
 */

#pragma save_binary

#include <ss_types.h>
#include <macros.h>
#include <files.h>
#include "../defs.h"

inherit "/std/guild/guild_lay_sh";
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define BEEN_BAD_BOY "_been_bad_boy"
#define PUNISHER ({"Lord Pyros","Lord Diabrecho","Lady Gu","Lady Aeria","Psuchae"})
#define DEATH_OBJECT (ELEMENTALIST_OBJS + "elemental_punishment")

#define DEFAULT_TITLES ({ "Undecided Worshipper of the Elementals" })

#define LEADER_TITLES  ({ "Focus of the Elements" }) 
#define COUNCIL_PYROS_TITLES ({ "Close Servant of Pyros" })
#define COUNCIL_GU_TITLES ({ "Close Servant of Gu" }) 
#define COUNCIL_AERIA_TITLES ({ "Close Servant of Aeria" }) 
#define COUNCIL_DIABRECHO_TITLES ({ "Close Servant of Diabrecho" })
#define COUNCIL_PSUCHAE_TITLES ({ "Close Servant of Psuchae" }) 
#define COUNCIL_DEFAULT_TITLES ({ "Close Servant of the Elementals" }) 

/* Titles by Maniac */ 
#define PYROS_TITLES  \
          ({ "Spark of the Elementals", \
             "Flickering Ember of the Elementals", \
             "Burning Hearth of the Elementals", \
             "Radiant Flare of the Elementals", \
             "Luminous Pyre of the Elementals",  \
             "Intense Fire of the Elementals", \
             "Raging Wildfire of the Elementals", \
             "Blazing Inferno of the Elementals",  \
             "Glorious Blaze of the Elementals", \
             "Devotee of Pyros" }) 
            
#define DIABRECHO_TITLES  \
          ({ "Raindrop of the Elementals", \
             "Light Rain of the Elementals", \
             "Mountain Stream of the Elementals", \
             "Flowing River of the Elementals", \
             "Crashing Wave of the Elementals", \
             "Whirlpool of the Elementals",  \
             "Monsoon of the Elementals", \
             "Tsunami of the Elementals", \
             "Great Sea of the Elementals", \
             "Devotee of Diabrecho" }) 
          
#define AERIA_TITLES \
          ({ "Breeze of the Elementals", \
             "Spring Air of the Elementals", \
             "Blue Sky of the Elementals", \
             "Gust of the Elementals", \
             "Gale of the Elementals", \
             "Whirlwind of the Elementals", \
             "Wildwind of the Elementals", \
             "Tornado of the Elementals", \
             "Hurricane of the Elementals", \
             "Devotee of Aeria" })

#define GU_TITLES \
          ({ "Pebble of the Elementals", \
             "Grey Stone of the Elementals", \
             "White Quartz of the Elementals", \
             "Icy Silver of the Elementals", \
             "Glittering Gold of the Elementals", \
             "Shining Platinum of the Elementals", \
             "Deep Sapphire of the Elementals", \
             "Red Ruby of the Elementals", \
             "Eternal Diamond of the Elementals", \
             "Devotee of Gu" }) 
            
#define PSUCHAE_TITLES \
          ({ "Seed of the Elementals", \
             "Sparkling Matter of the Elementals", \
             "Crystal Core of the Elementals", \
             "Crystalline Heart of the Elementals", \
             "Vital Energy of the Elementals", \
             "Umbral Breath of the Elementals", \
             "Vibrant Essence of the Elementals", \
             "Translucent Spirit of the Elementals", \
             "Life Force of the Elementals", \
             "Devotee of Psuchae" })
             
// Prototypes
public void     initialize_worshipper();
public object   query_top_shadow();
public void     notify_arrival(object player);
public void     notify_departure(object player);

// Global Variables
static string   * titles = DEFAULT_TITLES;

static string * PYROS_ADJS = ({ "Powerful","Flickering","Burning",
          	                    "Radiant","Luminous","Intense", 
          	                    "Raging","Blazing","Glorious",
                                "Vibrant", "None" });             
static string * PYROS_NOUNS = ({ "Spark","Ember","Hearth",
          	                     "Flare","Pyre","Fire", 
          	                     "Wildfire","Inferno","Blaze", 
                                 "Devotee" });             
static string * PYROS_SUFFIXES = ({ "Elementals","Pyros" }); 

static string * DIABRECHO_ADJS = ({ "Falling","Light","Mountain", 
          	                        "Flowing","Crashing","Churning", 
          	                        "Energetic","Raging","Great",
                                    "Tranquil", "None" });          
static string * DIABRECHO_NOUNS = ({ "Raindrop","Rain","Stream", 
          	                         "River","Wave","Whirlpool", 
          	                         "Monsoon","Tsunami","Sea",
                                     "Devotee" });             
static string * DIABRECHO_SUFFIXES = ({ "Elementals","Diabrecho" });

static string * AERIA_ADJS = ({ "Powerful","Spring","Blue",
          	                    "Strong","Howling","Forcible",
          	                    "Intense","Fresh","Glorious",
                                "Thundering","Northern","Southern",
                                "Eastern","Western","Mistral",
                                "Summer","Winter","Autumn",
                                "Fall","None" });            
static string * AERIA_NOUNS = ({ "Breeze","Air","Sky",
          	                     "Gust","Gale","Whirlwind",
          	                     "Wildwind","Tornado","Hurricane",
          	                     "Zephyr", "Tempest", "Wind",
                                 "Devotee" });             
static string * AERIA_SUFFIXES = ({ "Elementals","Aeria" });

static string * GU_ADJS = ({ "Solid","Grey","White",
          	                 "Icy","Glittering","Shining",
          	                 "Deep","Red","Eternal",
                             "Beautiful", "None" });            
static string * GU_NOUNS = ({ "Pebble","Stone","Quartz",
          	                  "Silver","Gold","Platinum",
          	                  "Sapphire","Ruby","Diamond",
                              "Devotee" });             
static string * GU_SUFFIXES = ({ "Elementals","Gu" });
 
static string * PSUCHAE_ADJS = ({ "Ethereal","Sparkling","Crystal",
          	                      "Crystalline","Vital","Umbral",
          	                      "Vibrant","Translucent","Life",
                                  "Indistinct", "None" });            
static string * PSUCHAE_NOUNS = ({ "Seed","Matter","Core",
          	                       "Heart","Energy","Breath",
          	                       "Essence","Spirit","Force",
                                   "Devotee" });             
static string * PSUCHAE_SUFFIXES = ({ "Elementals","Psuchae" });

private int gTeamAlarm = 0;	                                           	                               

public string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

public string 
query_guild_style_lay() 
{ 
    return GUILD_STYLE; 
}

public string 
query_guild_name_lay() 
{ 
    return GUILD_EW_NAME; 
}

public int
query_guild_leader_lay()
{
    string pn;

    pn = shadow_who->query_real_name(); 
    setuid();
    seteuid(getuid()); 

    return (GUILD_MANAGER->query_is_ew_council(pn)); 
}

public string *
query_pyros_adjs()
{
	return PYROS_ADJS;
}

public string *
query_pyros_nouns()
{
	return PYROS_NOUNS;
}

public string *
query_pyros_suffixes()
{
	return PYROS_SUFFIXES;
}

public string *
query_diabrecho_adjs()
{
	return DIABRECHO_ADJS;
}

public string *
query_diabrecho_nouns()
{
	return DIABRECHO_NOUNS;
}

public string *
query_diabrecho_suffixes()
{
	return DIABRECHO_SUFFIXES;
}

public string *
query_aeria_adjs()
{
	return AERIA_ADJS;
}

public string *
query_aeria_nouns()
{
	return AERIA_NOUNS;
}

public string *
query_aeria_suffixes()
{
	return AERIA_SUFFIXES;
}

public string *
query_gu_adjs()
{
	return GU_ADJS;
}

public string *
query_gu_nouns()
{
	return GU_NOUNS;
}

public string *
query_gu_suffixes()
{
	return GU_SUFFIXES;
}

public string *
query_psuchae_adjs()
{
	return PSUCHAE_ADJS;
}

public string *
query_psuchae_nouns()
{
	return PSUCHAE_NOUNS;
}

public string *
query_psuchae_suffixes()
{
	return PSUCHAE_SUFFIXES;
}

int 
query_guild_tax_lay() 
{ 
    return GUILD_EW_TAX; 
}

/* 
 * Return 1 if they try to join an occupational or layman guild, since
 * Elemental Clerics use up both layman and occupational slots. Set up 
 * a notify fail to say why in response to the join action. 
 */ 
public int
query_guild_not_allow_join_lay(object player, string type, 
                               string style, string name) 
{
    switch (type)
    {
    case "layman":
        notify_fail("You are a member of the Elemental Worshippers of Calia "
            + "and cannot devote yourself to other side studies.\n");
        return 1;
    }
    
    return ::query_guild_not_allow_join_lay(player, type, style, name);
}

void
init_lay_shadow(string str)
{
    ::init_lay_shadow(); 

    set_alarm(1.0, 0.0, initialize_worshipper);
}

/*
 * Function:    init_worshipper_titles
 * Description: Worshipper titles are dependent on:
 *                a) which patron elemental they serve most
 *                b) whether they are council
 */
public void
init_worshipper_titles()
{
    setuid();
    seteuid(getuid());
    int spe = GUILD_MANAGER->query_primary_element(shadow_who);

    if (GUILD_MANAGER->query_is_ew_council(shadow_who, 0)) 
    {
        switch (spe) 
        { 
            case "fire": 
                titles = COUNCIL_PYROS_TITLES;  
                break;
            case "air": 
                titles = COUNCIL_AERIA_TITLES; 
                break;
            case "water": 
                titles = COUNCIL_DIABRECHO_TITLES;  
                break;
            case "earth": 
                titles = COUNCIL_GU_TITLES;  
                break;
            case "life":
                titles = COUNCIL_PSUCHAE_TITLES;
                break;
            default: 
                titles = COUNCIL_DEFAULT_TITLES;  
        } 
        return;
    } 

    switch (spe) 
    { 
    case "fire": 
        titles = PYROS_TITLES;  
        break;
    case "air": 
        titles = AERIA_TITLES; 
        break;
    case "water": 
        titles = DIABRECHO_TITLES;  
        break;
    case "earth": 
        titles = GU_TITLES;  
        break;
    case "life":
        titles = PSUCHAE_TITLES;
        break;
    default: 
        titles = DEFAULT_TITLES;  
    }
}

public void
initialize_worshipper()
{
    setuid();
    seteuid(getuid());
    
    // Make sure the command soul gets added
    shadow_who->add_cmdsoul(EW_SOUL);
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);

    shadow_who->update_hooks();
    
    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }
    
    init_worshipper_titles();
    notify_arrival(shadow_who);

    shadow_who->catch_tell("\nWelcome, " + query_guild_title_lay() + "!\n\n");    
}

public void
remove_shadow()
{
    // We use the removal of the shadow as a way to ensure that the
    // spells for the command soul are removed.
    EC_SOUL->remove_spells(shadow_who);
    
    // We also need to remove the mana shadow. This removal assumes
    // that the person can only have one caster guild shadow.
    query_top_shadow()->remove_mana_shadow();

    notify_departure(shadow_who);
    
    ::remove_shadow();    
}

public void
remove_object()
{
    if (IS_CLONE)
    {
        // We don't want to notify when the master object is being removed
        notify_departure(shadow_who);
    }
    ::remove_object();
}

/*
public int 
calculate_adjusted_guild_stat()
{
    int real_guild_stat = shadow_who->query_stat(SS_LAYMAN);
    // We have our own calculation for guild stat here. Instead of basing
    // it on their "true" guild stat which can be gamed, we calculate
    // how much experience they've accrued since joining and convert that
    // into guild stat.
    setuid();
    seteuid(getuid());
    int starting_exp = GUILD_MANAGER->query_starting_exp(shadow_who);
    // use max exp instead of exp to help account for death situations. Also, we use "max" function in case query_max_exp isn't functioning correctly.
    int current_exp = max(shadow_who->query_max_exp(), shadow_who->query_exp()); 
    // We make it so that even if they "game" the system, we'll use 1/10 of
    // what they gamed as a minimum. This should help a bit with real death
    // situations
    int minimum_guild_stat = max(1, real_guild_stat / 10);
    int guild_exp = max(100, current_exp - starting_exp);
    // treat this adjusted exp as if the guild tax was 13
    int tax_rate = 13;
    int adjusted_guild_stat = shadow_who->exp_to_stat(guild_exp * tax_rate / (100 - tax_rate));
    // Separately, we also calculate practice level. A player can gain up to 50
    // guild stat by practicing a lot.
    int practice_level = GUILD_MANAGER->query_practice_level(shadow_who);
    int practice_adjustment = min(50, max(0, practice_level / 400));
    // Do the min/max adjustment. Range should be between 10% of real guild stat
    // up to the adjusted guild stat or real guild stat (whichever is lower)
    return min(real_guild_stat, max(minimum_guild_stat, adjusted_guild_stat)) + practice_adjustment;
}
*/

/*
 * Function name: query_stat
 * Description  : Get the compound value of a stat. Never less than 1.
 * Arguments    : int stat - Which stat to find.
 * Returns      : int - the stat value.
 */
 /*
public int
query_stat(int stat)
{
    int real_guild_stat = shadow_who->query_stat(stat);
    if (stat != SS_LAYMAN)
    {
        return real_guild_stat;
    }
    return calculate_adjusted_guild_stat();
}
*/

/*
 * Function:    query_worshipper_level
 * Description: Returns the layman guild stat divided by 10.
 *              This will be used to determine the title
 *              of the player.
 */
public int
query_worshipper_level()
{
    return (shadow_who->query_stat(SS_LAYMAN) / 10); 
}

public string
query_guild_default_title_lay()
{
	int title_level, s;
	string full_title;
	
	title_level = query_worshipper_level();
    s = sizeof(titles); 	
    title_level = max(0, min(s - 1, title_level));
    full_title = titles[title_level];
    
    return full_title;
}

public string 
query_guild_title_lay() 
{
    int title_level, s;
    string full_title = "";

    // If they are temple banned, replace their title showing 
	// they are banned
	
	if (GUILD_MANAGER->query_is_punish_temple_banned(shadow_who))
	{
		return "Ostracized";
	}
    
    // Have they created their own title? If not, give the default one
    // for their current rank
    if (!GUILD_MANAGER->query_created_own_title(shadow_who))
    {
    	title_level = query_worshipper_level();
	    s = sizeof(titles); 	
	    title_level = max(0, min(s - 1, title_level));
	    full_title = titles[title_level];
	}
	
	// Return their created title
	if (GUILD_MANAGER->query_created_own_title(shadow_who))
	{
		full_title += (GUILD_MANAGER->query_title_created(shadow_who));
	}
	
	// Have they carved all four tools?
    if (GUILD_MANAGER->query_carved_value(shadow_who) == ALL_FLAGS)
    {
    	// Are they the EW Leader? If so, append Focus title
	    if (GUILD_MANAGER->query_is_ew_leader(shadow_who, 0))
	    {
	    	// Are they hiding their extra carved title?
	    	if (!GUILD_MANAGER->query_hide_extra_title(shadow_who))
	        {
	        	full_title += ", Focus and Dedicated Worshipper of the Elements";
	        	return full_title;
	        }
	        else
	        {
	        	full_title += ", Focus of the Elements";
	        	return full_title;
	        }
	    }
	    
        // Are they council? If so append Close Servant
		if (GUILD_MANAGER->query_is_ew_council(shadow_who, 0))
		{
			// Are they hiding their extra carved title?
	    	if (!GUILD_MANAGER->query_hide_extra_title(shadow_who))
	        {
	        	full_title += ", Close Servant and Dedicated Worshipper of the Elements";
	        	return full_title;
	        }
	        else
	        {
	        	return full_title;
	        }
		}
    	// Are they hiding their extra carved title?
    	if (!GUILD_MANAGER->query_hide_extra_title(shadow_who))
        {
        	full_title += ", Dedicated Worshipper of the Elements";
        }
    }
    
    return full_title;
} 

/*
 * Function name: query_guild_trainer_lay
 * Description:   Return one or more references to the object that define
 *                sk_train_max for the player. The returned refernce can
 *                be a string reference, an object pointer or an array of
 *                those.
 * Returns:       See description.
 */
public mixed
query_guild_trainer_lay()
{
    return ({ ELEMENTALIST_TEMPLE + "ew_practice" });
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
    // Conditions to kick out should be here, and should return 0
    if (GUILD_MANAGER->query_is_guild_expelled(player))
    {
        // Player has been kicked out of the guild, but somehow still has the
        // shadow. Do the kicking out here.
        player->catch_tell(sprintf("\n\n%'='|75s\n", "EXPELLED"));
        player->catch_tell(sprintf("\n%=-75s\n\n", "You have been expelled from the Elemental Worshippers "
                                   + "guild by the Worshippers Council."));
        player->catch_tell(sprintf("%'='|75s\n\n", ""));
        GUILD_MANAGER->leave_guild_expel(player);
        return 0;
    }
   if (GUILD_MANAGER->query_is_guild_discharged(player))
    {
        // Player has been kicked out of the guild, but somehow still has the
        // shadow. Do the kicking out here.
        player->catch_tell(sprintf("\n\n%'='|75s\n", "DISCHARGED"));
        player->catch_tell(sprintf("\n%=-75s\n\n", "You have been discharged from the Elemental Seekers "
                                   + "guild by the Worshippers Council."));
        player->catch_tell(sprintf("%'='|75s\n\n", ""));
        GUILD_MANAGER->leave_guild(player);
   }
    if (!GUILD_MANAGER->query_is_worshipper(player))
    {
        // Player has been kicked out of the guild, but somehow still has the
        // shadow. Do the kicking out here.
        player->catch_tell(sprintf("\n\n%'='|75s\n", "REMOVED FROM GUILD"));
        player->catch_tell(sprintf("\n%=-75s\n\n", "You are no longer a member of "
                                   + "the Elemental Worshippers guild."));
        player->catch_tell(sprintf("%'='|75s\n\n", ""));
        GUILD_MANAGER->leave_guild(player);
        return 0;
    }

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

public int
is_elemental_worshipper()
{
    return 1;
}

public object *
get_audience_for_notification(object player)
{
    if (!objectp(player))
    {
        return ({ });
    }

    object * members, * clerics, * wizards, * seekers, *scops, * audience;
    
    string name = player->query_real_name();
    // Layman members will notify both clerics and worshippers
    members = filter(users(), &->is_elemental_worshipper());
    clerics = filter(users(), &->is_elemental_cleric());
    seekers = filter(users(), &->is_elemental_seeker());
    scops = filter(users(), &->is_spirit_member());
    members -= clerics; // subtract and add to get rid of duplicates
    members += clerics;
    members -= seekers;
    members += seekers;
    members -= scops;
    members += scops;
    members -= ({ player }); // don't notify self.
    
    for (int i=0; i < sizeof(members); i++)
    {
    	if (GUILD_MANAGER->query_stop_all_notifications(members[i]))
    		members -= ({ members[i] });
    	else  if (GUILD_MANAGER->query_stop_worshipper_notifications(members[i]))
    		members -= ({ members[i] });
    }
    
    wizards = filter(members, &->query_wiz_level());
    if (!sizeof(members))
    {
        return ({ });
    }
    
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
    return audience;
}

public void
notify_arrival(object player)
{
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return;
    }

    string p_element = GUILD_MANAGER->query_primary_element(shadow_who);
    string diety_message;
    
    switch(p_element)
    {
        case "fire":
            diety_message = "The voice of Lord Pyros echoes through your " +
                "mind announcing that ";
            break;
        case "water":
            diety_message = "The voice of Lord Diabrecho echoes through your " +
                "mind announcing that ";
            break;
        case "air":
            diety_message = "The voice of Lady Aeria echoes through your " +
                "mind announcing that ";
            break;
        case "earth":
            diety_message = "The voice of Lady Gu echoes through your " +
                "mind announcing that ";
            break;
        case "life":
            diety_message = "The voice of Psuchae echoes through your " +
                "mind announcing that ";
            break;
        default:
            diety_message = "You sense the stirring of the elements as ";
            break;
    }
     
    object * audience = get_audience_for_notification(player);
    map(audience, &->catch_msg(diety_message + capitalize(player->query_real_name()) +
        ", "+query_guild_title_lay()+" has entered the realms.\n"));   
}

public void
notify_departure(object player)
{
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return;
    }
    
    string p_element = GUILD_MANAGER->query_primary_element(shadow_who);
    string diety_message, element;
    
    switch(p_element)
    {
        case "fire":
            diety_message = "The voice of Lord Pyros echoes through your " +
                "mind announcing that ";
            element = "fire";
            break;
        case "water":
            diety_message = "The voice of Lord Diabrecho echoes through your " +
                "mind announcing that ";
            element = "water";
            break;
        case "air":
            diety_message = "The voice of Lady Aeria echoes through your " +
                "mind announcing that ";
            element = "air";
            break;
        case "earth":
            diety_message = "The voice of Lady Gu echoes through your " +
                "mind announcing that ";
            element = "earth";
            break;
        case "life":
            diety_message = "The voice of Psuchae echoes through your " +
                "mind announcing that ";
            element = "shadows";
            break;
        default:
            diety_message = "You sense a calming of the elements as ";
            element = "elements";
            break;
    }
    
    object * audience = get_audience_for_notification(player);
    map(audience, &->catch_msg(diety_message + capitalize(player->query_real_name()) +
        ", "+query_guild_title_lay() +
        " has retired to " + player->query_possessive() + " bunk, returning to "+
        "the realm of "+element+" and dreams.\n"));     
}

public void
do_die(object killer)
{
    object *members;

    if ((shadow_who->query_hp() > 0) || shadow_who->query_wiz_level() ||
        shadow_who->query_ghost())
    {
        return;
    }

    members = get_audience_for_notification(shadow_who);
    if (!sizeof(members))
    {
        shadow_who->do_die(killer);
        return;
    }
    
    string p_element = GUILD_MANAGER->query_primary_element(shadow_who);
    string diety_message;
    
    switch(p_element)
    {
        case "fire":
            diety_message = "The voice of Lord Pyros echoes through your " +
                "mind announcing that ";
            break;
        case "water":
            diety_message = "The voice of Lord Diabrecho echoes through your " +
                "mind announcing that ";
            break;
        case "air":
            diety_message = "The voice of Lady Aeria echoes through your " +
                "mind announcing that ";
            break;
        case "earth":
            diety_message = "The voice of Lady Gu echoes through your " +
                "mind announcing that ";
            break;
        case "life":
            diety_message = "The voice of Psuchae echoes through your " +
                "mind announcing that ";
            break;
        default:
            diety_message = "You sense a calming of the elements as ";
            break;
    }
    
    shadow_who->add_prop(LIVE_I_NO_CORPSE,1);
    shadow_who->do_die(killer);
    map(members, &->catch_msg(diety_message + capitalize(shadow_who->query_real_name())+
        " has just perished.\n"));
    tell_room(environment(shadow_who),QCTNAME(shadow_who)+"'s body "+
        "suddenly blackens and fades into it's own shadow then "+
        "disappears!\n",shadow_who);
}

/*
 * Function name: punish_teaming
 * Description  : Punish teaming after a few minutes
 * Arguments    : object who - the questioned team member
 */

int
punish_teaming(object who, int warned)
{
    int success, align, ran_align;

    if (!objectp(who) || !objectp(shadow_who))
        return 1;

    switch(warned)
    {
	    case 0:
	        shadow_who->catch_tell("\nThe Elementals disapprove of your " +
	        	"joining forces with the Soulless, " + 
	        	who->query_the_name(shadow_who) + "!\n\n");
	
	        if (!gTeamAlarm)
	            gTeamAlarm = set_alarm(60.0, 0.0, &punish_teaming(who, 1));
	
	        break;
	
	    case 1:
	        if (objectp(who) &&
	            member_array(who, shadow_who->query_team_others()) != -1)
	        {
	            shadow_who->catch_tell("\nYou feel the building wrath of the " +
	                "Elementals as you remain in defiance of your Vows and " +
	                "continue to join forces with the Soulless, " +
	                who->query_the_name(shadow_who) + ".\n\n");
	            gTeamAlarm = set_alarm(90.0, 0.0, &punish_teaming(who, 2));
	        }
	        else
	        {
	            gTeamAlarm = 0;
	        }
	        break;
	
	    case 2:
	        if (objectp(who) &&
	            member_array(who, shadow_who->query_team_others()) != -1)
	        {
	        	string pri_elem, elem_name;
	        	pri_elem = (GUILD_MANAGER->query_primary_element(shadow_who->
	        		query_real_name()));
	        	switch(pri_elem)
	        	{
	        		case "fire":
	        			elem_name = "Lord Pyros";
	        			break;
	        		case "water":
	        			elem_name = "Lord Diabrecho";
	        			break;
	        		case "air":
	        			elem_name = "Lady Aeria";
	        			break;
	        		case "earth":
	        			elem_name = "Lady Gu";
	        			break;
	        		default:
	        			elem_name = "Psuchae";
	        			break;
	        	}
	            shadow_who->catch_tell("\nYou feel "+elem_name+
	            	" is both disappointed and angered by your "+
	            	"continued actions of defiance of your Vows.\n\n");
	            COUNCIL_LOG_BOOK->update_log_book(my_time() + 
	            capitalize(shadow_who->query_real_name()) +
	            " was warned for teaming with " +
	            capitalize(who->query_real_name()) + ".\n");
	            send_debug_message("cleric", capitalize(shadow_who->
	            	query_real_name()) + " was warned for teaming with " + 
	                capitalize(who->query_real_name()) + ".", EVENTS_LOG);
        	}
	        gTeamAlarm = 0;
	        break;

	    default:
	        break;
    }
}

/*
 * Function name:    set_leader
 * Description  :    Sets this living as a member in a team
 *                   It will fail if this living is a leader itself
 * Arguments    :    leader: The objectpointer to the leader of the team
 * Returns      :    True if successfull
 */

public int
set_leader(object leader)
{
    int i, size, current_exp, success;
    object *team;
    string name, ogname, lgname;

    if (leader == 0)
        success = shadow_who->set_leader(leader);

    else
    {
        // Make them join first so we can get team info. 
        success = shadow_who->set_leader(leader);
        
        // They couldn't join. Don't do anything else. 
        if (!success)
            return success;

        team = shadow_who->query_team_others();
        ogname = leader->query_guild_name_occ();
        lgname = leader->query_guild_name_lay();
        
        if (leader->query_wiz_level() || shadow_who->query_wiz_level())
            return success;

        if (success && member_array(ogname, BANNED_GUILDS) != -1)
        {
            punish_teaming(leader, 0);
            return success;
        }
        
        if (success && member_array(lgname, BANNED_GUILDS) != -1)
        {
            punish_teaming(leader, 0);
            return success;
        }
    }

    return success;
}

/*
 * Function name:   team_join
 * Description:     Sets this living as the leader of another.
 *                  Mask parent so that teaming with enemy guilds affects
 *                  cleric's alignment. 
 * Arguments:       members: The objectpointer to the new member of my team
 *                  NOTE: Had to change 'member' to 'members' because of weird
 *                  macro error (/d/Calia/guilds/elementalists/shadows/
 *                  occ_cleric_shadow.c: Missing '(' in macro call line 2309)
 * Returns:         True if member accepted in the team
 */

public int
team_join(object members)
{
    int success;
    string ogname, lgname;

    success = shadow_who->team_join(members);
    if (!success || members->query_wiz_level() || shadow_who->query_wiz_level())
        return success;

    ogname = members->query_guild_name_occ();
    lgname = members->query_guild_name_lay();

    if (success && member_array(ogname, BANNED_GUILDS) != -1)
        punish_teaming(members, 0);
    
    if (success && member_array(lgname, BANNED_GUILDS) != -1)
        punish_teaming(members, 0);
        
    return success;
}

public void
elementals_stop_fight(object me, object target, string caller)
{
    int i;
    string pn;

    i = random(5);
    pn = PUNISHER[i]; 

    seteuid(getuid());
    me->stop_fight(target);
    target->stop_fight(me);
    if (file_name(me) == caller)
    {
        if (me->query_prop(BEEN_BAD_BOY))
        {
            tell_room(environment(me), pn +" suddenly "+
                "appears, looking very angry.\n");
            tell_object(me, pn+" points at you and screams "+
                "out in anger: You have been warned, but have not "+
                "listened!  Action must be taken!\nSuddenly, you feel "+
                "mentally and physically weakened.\n" + pn +
                " smiles wickedly, and disappears.\n");
            tell_room(environment(me),pn+" points at "+
                QTNAME(me) +" and screams out in anger:  You have " +
                "been warned, but have not "+
                "listened!  Action must be taken!\n"+
                pn +" smiles wickedly, and disappears.\n"+
                QTNAME(me)+" looks visibly drained.\n",me);
            me->set_mana(0);
            me->heal_hp(-(me->query_max_hp()/2));
                COUNCIL_LOG_BOOK->update_log_book(GUILD_MANAGER->my_time() +
                    capitalize(me->query_real_name())+" has been "+
                    "punished by "+ pn +" for attacking "+
                    capitalize(target->query_real_name())+".\n");
            if (me->query_hp() <= 0)
            {
                DEATH_OBJECT->load_me();
                me->do_die(find_object(DEATH_OBJECT));
            }
        }
        else 
        {
            tell_room(environment(me), pn + " suddenly "+
                "appears, looking slightly annoyed.\n");
            tell_object(me, pn + " whispers to you: Do not "+
                "attack another in our family again, or you shall "+
                "feel the wrath of the Elementals.  I hope I make "+
                "myself clear.\n");
            tell_room(environment(me), pn + " whispers to "+
                QTNAME(me)+".\n",me);
            tell_room(environment(me), pn + " disappears.\n");
            me->add_prop(BEEN_BAD_BOY,1);
        }
    }
    else
    {
        tell_room(environment(me), pn + " suddenly appears, "+
            "looking very angry.\n" + pn + " shouts: I don't "+
            "know which of you did it, but you had best behave!  "+
            "You aren't going to like it if I have to come back!\n"+
            pn + " disappears.\n");
    }
}

public void
attack_object(object target)
{
    if (IS_MEMBER(target))
    {
        int i;
        object temp;

        for (i = 0; i < 20; i++)
        {
            if (calling_object(-i))
                temp = calling_object(-i);
            else
                break;
        }
        set_alarm(1.0, 0.0,
              &elementals_stop_fight(shadow_who, target, file_name(temp)));
    }
    shadow_who->attack_object(target);
}

public varargs void
add_prop(string prop, mixed val)
{    
    if (prop == LIVE_I_UNDEAD && val != 0)
    {
        query_shadow_who()->catch_tell("You can feel the unclean forces "
            + "of the Soulless wrack your body, and you struggle "
            + "internally. Gradually, you feel the soothing calm of "
            + "Psuchae cleanse your body of the abominating effects.\n");
        return;
    }
    
    query_shadow_who()->add_prop(prop, val);
}
