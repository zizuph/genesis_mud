/* 
 * Guild Manager for the Elementalists of Calia
 *
 * This manager will take care of the member data for the entire Elementalists
 * guild. This includes the Elemental Clerics, Elemental Worshippers, and
 * Elemental Seekers.
 *
 * Created by Petros, April 2010
 * Added Elemental Cleric features - Jaacar, 2016/2017
 * Modified the guild leaving functions to work properly in line
 *   with the guild rules (death on leaving) and original intent.
 *   Also allowed for them to be managed offline and properly remove
 *   from guild manager - Mirandus, 2020
 * Fixed Schirmo spell to look for name, not description to find an active one.
 *   Zizuph, Jan 2022.
 */

#pragma strict_types

#include <std.h>
#include <files.h>
#include <ss_types.h>
#include <math.h>
#include <time.h>
#include "../defs.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public mapping      cached_player_info = ([ ]);
public string *     ew_council_members = 0;
public string       ew_focus = 0;
public string       ec_focus = 0;
public string *     ec_council_members = 0;
public string       ec_luminary = 0;
public string       ec_illuminati = 0;
public string       ec_emissary = 0;
public string       ec_cultivator = 0;
public string       ec_liberator = 0;
public string       ec_conservator = 0;
public string       ec_archon_revelation = 0;
public string       ec_archon_deliverance = 0;
public string       ec_archon_apotheosis = 0;

// Defines
#define EVENT_LOG (ELEMENTALIST_LOGS + "events")
#define SS_CARVED 114050
#define SS_PATRON_ELEMENTAL 114052
#define SPIRIT_COUNCIL_CODE "/d/Calia/guilds/scop/specials/council_code"
#define LEFT(x) ({"You hear the thunderous voice of Lord Pyros proclaim: "+x->query_name()+" has betrayed us and has been banished from the Circle!\n",\
        "Winds howl in the voice of Lady Aeria: "+x->query_name()+" has betrayed the Circle and is no longer one of us!\n",\
        "The ground shakes violently below you momentarily as Lady Gu speaks: "+x->query_name()+" has betrayed the Elementals and is no longer one of the Circle!\n",\
        "You hear the angry voice of Lord Diabrecho: "+x->query_name()+" has betrayed the Circle and is no longer with us!\n",\
        "Resonating in your mind you hear Psuchae say: "+x->query_name()+" has betrayed the Circle and is no longer with us!\n"})
#define DEATH_OBJECT (ELEMENTALIST_OBJS + "elemental_punishment")

// Prototypes
public string * query_ew_council();
public string query_ew_focus();
public string query_ec_focus();
public string * query_ec_council();
public string query_ec_luminary();
public string query_ec_illuminati();
public string query_ec_emissary();
public string query_ec_cultivator();
public string query_ec_liberator();
public string query_ec_conservator();
public string query_ec_archon_revelation();
public string query_ec_archon_deliverance();
public string query_ec_archon_apotheosis();
public void set_primary_element(mixed player, string element);
public void set_can_join_worshippers(mixed player, int value);
public void set_can_join_clerics(mixed player, int value);
public void set_carved_value(mixed player, int value);
public void set_ew_council(mixed player, int value);
public void set_ec_council(mixed player, int value);
public void set_practice_level(mixed player, int value);
public int query_is_child_cleric(mixed player);
public int query_is_master_cleric(mixed player);
public int query_is_elder_cleric(mixed player);
public int query_is_full_master(mixed player);
public void set_can_do_wor_task_one(mixed player, int value);
public void set_can_do_wor_task_two(mixed player, int value);
public void set_can_do_wor_task_three(mixed player, int value);
public void set_can_do_wor_task_four(mixed player, int value);
public void set_can_do_ec_task_five(mixed player, int value);
public void set_can_do_ec_task_six(mixed player, int value);
public void set_has_completed_scenarios(mixed player, int value);
public void betray1(object player);

public string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

/*
 * Things that the Guild Manager Keeps track of:
 *
 * query_calendar               - The Elemental version of the date
 *
 * is_cleric                    - flag indicates membership in the occ guild
 * is_worshipper                - flag indicates membership in the lay guild
 * is_seeker                    - flag indicates membership in the seeker lay 
 *                                guild
 *
 * primary_element              - which element member is focused on
 * practice_level               - how much practice they have in casting.
 * tell_history                 - last 10 fartells received
 * carved_value                 - represents the carvings the player has done
 *
 * starting_exp                 - the exp the player started with in the guild
 * starting_date                - the date the player joined the guild
 * conduit_earned               - how much conduit the player has earned
 * conduit_spent                - how much conduit the player has spent
 * guild_notes                  - any notes recorded about the member
 *
 * hide_extra_title             - whether player is hiding their extra carved 
 *                                title or not
 * created_own_title            - whether player has created their own title 
 *                                or not
 * title_created                - what is the player created title
 * racial_spirit_surname        - what is the racial player's spirit surname
 * racial_chosen_surname        - what is the racial player's chosen surname
 * racial_hide_title            - whether the racial player is hiding their 
 *                                racial title or not
 * has_changed_element          - whether player has changed element before 
 *                                or not
 *
 * stop_cleric_notifications    - whether player has stopped cleric 
 *                                notification messages or not
 * stop_worshipper_notifications- whether player has stopped worshipper 
 *                                notification messages or not
 * stop_seeker_notifications    - whether player has stopped seeker 
 *                                notification messages or not
 * stop_all_notifications       - whether player has stopped all notification 
 *                                messages or not
 * 
 *
 * is_ew_council                - whether the person holds the Worshipper 
 *                                council position
 * is_ew_leader                 - whether the person is the leader (Focus) 
 *                                of the Worshippers
 * is_ec_council                - whether the person holds the Cleric council 
 *                                position
 * is_ec_leader                 - whether the person is the leader (Focus) of 
 *                                the Elementalists
 * is_child_cleric              - whether the person is a Child in the Clerics
 * is_master_cleric             - whether the person is a Master in the Clerics
 * is_elder_cleric              - whether the person is an Elder in the Clerics
 * is_full_master               - whether the person is a Full Master rank in 
 *                                the Clerics
 * is_conservator               - whether the person is a Conservator of the 
 *                                Clerics (In charge of the racks/equipment)
 * is_luminary                  - whether the person is a Luminary of the 
 *                                Clerics (In charge of the Library)
 * is_illuminati                - whether the person is an Illuminati of the
 *                                Clerics (In charge researching and vault 
 *                                artifacts)
 * is_emissary                  - whether the person is an Emissary of the 
 *                                Clerics (In charge of diplomatic relations 
 *                                with other guilds)
 * is_cultivator                - whether the person is a Cultivator of the 
 *                                Clerics (In charge of the gardens (herb/gem))
 * is_liberator                 - whether the person is a Liberator of the 
 *                                Clerics (Un-life information expert)
 *
 * is_child_approved            - mentor has granted more power to their 
 *                                student
 * 
 * is_punish_train_banned       - training ban punishment
 * is_punish_spell_banned       - spell ban punishment
 * is_punish_temple_banned      - temple ban punishment
 * is_punish_resource_banned    - temple resource ban punishment
 * is_guild_discharged          - whether the player has been discharged from 
 *                                the guild
 * is_guild_expelled            - whether the player has been expelled from 
 *                                the guild
 * is_guild_betrayed            - whether the player has betrayed the guild
 *
 * can_join_worshippers         - whether person has been granted permission 
 *                                to join worshippers
 * can_join_clerics             - whether person has been granted permission 
 *                                to join clerics
 *
 * can_do_wor_task_one          - whether person has been granted permission 
 *                                to do task one for Worshippers
 * can_do_wor_task_two          - whether person has been granted permission 
 *                                to do task two for Worshippers
 * can_do_wor_task_three        - whether person has been granted permission 
 *                                to do task three for Worshippers
 * can_do_wor_task_four         - whether person has been granted permission 
 *                                to do task four for Worshippers
 *
 * can_do_ec_task_five          - whether person has been granted permission
 *                                to do task five for Clerics
 *
 * can_do_ec_task_six           - whether person has been granted permission
 *                                to do task six for Clerics
 *
 * has_completed_scenarios      - whether person has completed branch 
 *                                scenarios previously
 *
 * emessenger_option            - racial messenger option
 *
 * emount_option                - racial mount option
 *
 */
 
// The create function is called for every object. We mask it here
// to do some basic initialization for the handler
void
create()
{
    setuid();
    seteuid(getuid());
}

/*
 * Function:    get_id
 * Description: Get the real name of the player string or object passed.
 *              It's just a convenience function so that the right answer
 *              is given without checking object types in the calling
 *              code.
 */
public string
get_id(mixed player)
{
    string name;
    
    if (stringp(player) && strlen(player))
    {
        name = player;
    }
    else if (objectp(player) && IS_PLAYER_OBJECT(player))
    {
        name = player->query_real_name();
    }    
    
    return name;
}

/* 
 * Function:    load_player_info
 * Description: This loads the player info from their specific file
 *              and returns the mapping of it.
 */
public mapping
load_player_info(mixed player)
{
    string name;
    mapping player_info;
    
    name = get_id(player);
    if (!strlen(name))
    {
        return ([ ]);
    }
    
    if (cached_player_info[name])
    {
        return cached_player_info[name];
    }
    
    if (!SECURITY->exist_player(name) && name != "guild")
    {
        return ([ ]);
    }
    
    player_info = ([ ]);
        
    // Look for the file
    if (file_size(ELEMENTALIST_DATA + name + ".o") >= 0)
    {
        player_info = restore_map(ELEMENTALIST_DATA + name);
    }

    // Add the value to the cache
    cached_player_info[name] = player_info;
    return player_info;
}

/* 
 * Function:    query_player_property
 * Description: Generic function to return values from the
 *              manager mapping. This will be used by all
 *              customized getters
 */
public mixed
query_player_property(mixed player, string prop)
{
    mapping player_info = load_player_info(player);
    
    return player_info[prop];    
}

/*
 * Function:    set_player_property
 * Description: Generic function to set the values for a player in
 *              the manager mapping. This will be used by all customized
 *              setters
 */
public string
set_player_property(mixed player, string prop, mixed value)
{
    mapping player_info = load_player_info(player);
    string name = get_id(player);
    
    if (value)
    {
        player_info[prop] = value;
    }
    else
    {
        m_delkey(player_info, prop);
    }
    
    cached_player_info[name] = player_info; // insert the info into the cache
    save_map(player_info, ELEMENTALIST_DATA + name);    
    return name;
}

public string
query_calendar()
{
    int real_time, real_day;
    string day, month, message, image, rmonth;

    real_time = time();
    
    day = TIME2FORMAT(real_time,"d");
    real_day = atoi(day);

    month = TIME2FORMAT(real_time,"mmm");

    message = "Focusing your energies, you begin to see celestial symbols "+
        "form in your head. These symbols indicate that it is the ";

    switch (month)
    {
        case "Jan":
            rmonth = "Moon of Phoeinikeos";
            image = "Psuchae";
            break;
        case "Feb":
            rmonth = "Moon of Kraneios";
            image = "Lord Diabrecho";
            break;
        case "Mar":
            rmonth = "Moon of Lanotropios";
            image = "Family";
            break;
        case "Apr":
            rmonth = "Moon of Machaneus";
            image = "Hope";
            break;
        case "May":
            rmonth = "Moon of Dodekateus";
            image = "Lord Pyros.";
            break;
        case "Jun":
            rmonth = "Moon of Eukleios";
            image = "Ceremonies";
            break;
        case "Jul":
            rmonth = "Moon of Artemisios";
            image = "the Sun";
            break;
        case "Aug":
            rmonth = "Moon of Psydreus";
            image = "Lady Gu";
            break;
        case "Sep":
            rmonth = "Moon of Gamilios";
            image = "the Moon";
            break;
        case "Oct":
            rmonth = "Moon of Agrianios";
            image = "Faith";
            break;
        case "Nov":
            rmonth = "Moon of Panamos";
            image = "Lady Aeria";
            break;
        default:
            rmonth = "Moon of Appellaios";
            image = "Secrecy";
            break;
    }
     
    return message + LANG_ORD2WORD(real_day)+" day of the "+rmonth+", "+
        "celebrating "+image+".\n"; 
}

/*========================
 * TITLE RELATED FUNCTIONS
 =========================*/
public int
query_hide_extra_title(mixed player)
{
	return query_player_property(player, "hide_extra_title");
}

public void
set_hide_extra_title(mixed player, mixed value)
{
	set_player_property(player, "hide_extra_title", value);
}

public int
query_created_own_title(mixed player)
{
	return query_player_property(player, "created_own_title");
}

public void
set_created_own_title(mixed player, mixed value)
{
	set_player_property(player, "created_own_title", value);
}

public string
query_title_created(mixed player)
{
	return query_player_property(player, "title_created");
}

public void
set_title_created(mixed player, mixed value)
{
	set_player_property(player, "title_created", value);
}

public string
query_has_changed_element(mixed player)
{
	return query_player_property(player, "has_changed_element");
}

public void
set_has_changed_element(mixed player, mixed value)
{
	set_player_property(player, "has_changed_element", value);
}

public string
query_racial_spirit_surname(mixed player)
{
    return query_player_property(player, "racial_spirit_surname");
}
public void
set_racial_spirit_surname(mixed player, mixed value)
{
    set_player_property(player, "racial_spirit_surname", value);
}

public string
query_racial_chosen_surname(mixed player)
{
    return query_player_property(player, "racial_chosen_surname");
}
public void
set_racial_chosen_surname(mixed player, mixed value)
{
    set_player_property(player, "racial_chosen_surname", value);
}

public string
query_racial_hide_title(mixed player)
{
    return query_player_property(player, "racial_hide_title");
}
public void
set_racial_hide_title(mixed player, mixed value)
{
    set_player_property(player, "racial_hide_title", value);
}

/*=======================
 * NOTIFICATION FUNCTIONS
 ========================*/

public int
query_stop_cleric_notifications(mixed player)
{
	return query_player_property(player, "stop_cleric_notifications");
}

public void
set_stop_cleric_notifications(mixed player, mixed value)
{
	set_player_property(player, "stop_cleric_notifications", value);
}

public int
query_stop_worshipper_notifications(mixed player)
{
	return query_player_property(player, "stop_worshipper_notifications");
}

public void
set_stop_worshipper_notifications(mixed player, mixed value)
{
	set_player_property(player, "stop_worshipper_notifications", value);
}
 
public int
query_stop_seeker_notifications(mixed player)
{
	return query_player_property(player, "stop_seeker_notifications");
}

public void
set_stop_seeker_notifications(mixed player, mixed value)
{
	set_player_property(player, "stop_seeker_notifications", value);
} 

public int
query_stop_all_notifications(mixed player)
{
	return query_player_property(player, "stop_all_notifications");
}

public void
set_stop_all_notifications(mixed player, mixed value)
{
	set_player_property(player, "stop_all_notifications", value);
}
 
/*=====================
 * MEMBERSHIP FUNCTIONS
 ======================*/
public void
add_cleric(mixed player)
{
    string player_name = set_player_property(player, "is_cleric", 1);
    send_debug_message("cleric", capitalize(player_name)
        + " has become an Elemental Cleric.", EVENT_LOG);
}

public int
query_is_cleric(mixed player)
{
    if (objectp(player) && player->query_npc())
    {
        // NPCs are members if they possess the shadow
        return (player->query_guild_name_occ() == GUILD_EC_NAME);
    }
    
    return query_player_property(player, "is_cleric");
}

public void
remove_cleric(mixed player)
{
    string player_name = set_player_property(player, "is_cleric", 0);
    send_debug_message("cleric", capitalize(player_name)
        + " has left the Elemental Clerics.", EVENT_LOG);    
}

public void
add_seeker(mixed player)
{
    string player_name = set_player_property(player, "is_seeker", 1);
    send_debug_message("seeker", capitalize(player_name)
        + " has become an Elemental Seeker.", EVENT_LOG);
}

public int
query_is_seeker(mixed player)
{
    if (objectp(player) && player->query_npc())
    {
        // NPCs are members if they possess the shadow
        return (player->query_guild_name_lay() == GUILD_ES_NAME);
    }
    
    return query_player_property(player, "is_seeker");
}

public void
remove_seeker(mixed player)
{
    string player_name = set_player_property(player, "is_seeker", 0);
}

public void
add_worshipper(mixed player)
{
    string player_name = set_player_property(player, "is_worshipper", 1);
    send_debug_message("worshipper", capitalize(player_name)
        + " has become an Elemental Worshipper.", EVENT_LOG);
}

public int
query_is_worshipper(mixed player)
{
    if (objectp(player) && player->query_npc())
    {
        // NPCs are members if they possess the shadow
        return (player->query_guild_name_occ() == GUILD_EW_NAME);
    }
    
    return query_player_property(player, "is_worshipper");
}

public void
remove_worshipper(mixed player)
{
    string player_name = set_player_property(player, "is_worshipper", 0);
}

public void
add_racial(mixed player)
{
    string player_name = set_player_property(player, "is_racial", 1);
    send_debug_message("cleric", capitalize(player_name)
        + " has joined the Elemental Racial guild.", EVENT_LOG);
}

public int
query_is_racial(mixed player)
{
    if (objectp(player) && player->query_npc())
    {
        // NPCs are members if they possess the shadow
        return (player->query_guild_name_race() == GUILD_EC_NAME);
    }
    
    return query_player_property(player, "is_racial");
}

public void
remove_racial(mixed player)
{
    string player_name = set_player_property(player, "is_racial", 0);
}

public string *
query_all_clerics()
{
    string * files = get_dir(ELEMENTALIST_DATA);
    string * members = ({ });
    
    foreach (string file : files)
    {
        if (!wildmatch("*.o", file))
        {
            continue;
        }
        
        string name = file[..-3];
        if (query_is_cleric(name))
        {
            members += ({ name });
        }
    }
    
    return members;
}

public string *
query_all_children()
{
    string * files = get_dir(ELEMENTALIST_DATA);
    string * members = ({ });
    
    foreach (string file : files)
    {
        if (!wildmatch("*.o", file))
        {
            continue;
        }
        
        string name = file[..-3];
        if (query_is_cleric(name))
        {
        	if (query_is_child_cleric(name))
            	members += ({ name });
        }
    }
    
    return members;
}

public string *
query_all_masters()
{
    string * files = get_dir(ELEMENTALIST_DATA);
    string * members = ({ });
    
    foreach (string file : files)
    {
        if (!wildmatch("*.o", file))
        {
            continue;
        }
        
        string name = file[..-3];
        if (query_is_cleric(name))
        {
        	if (query_is_master_cleric(name))
            	members += ({ name });
        }
    }
    
    return members;
}

public string *
query_all_fullmasters()
{
    string * files = get_dir(ELEMENTALIST_DATA);
    string * members = ({ });
    
    foreach (string file : files)
    {
        if (!wildmatch("*.o", file))
        {
            continue;
        }
        
        string name = file[..-3];
        if (query_is_cleric(name))
        {
        	if (query_is_master_cleric(name))
            	members += ({ name });
        }
    }
    
    return members;
}

public string *
query_all_elders()
{
    string * files = get_dir(ELEMENTALIST_DATA);
    string * members = ({ });
    
    foreach (string file : files)
    {
        if (!wildmatch("*.o", file))
        {
            continue;
        }
        
        string name = file[..-3];
        if (query_is_cleric(name))
        {
        	if (query_is_elder_cleric(name))
            	members += ({ name });
        }
    }
    
    return members;
}

public string *
query_all_racials()
{
    string * files = get_dir(ELEMENTALIST_DATA);
    string * members = ({ });
    
    foreach (string file : files)
    {
        if (!wildmatch("*.o", file))
        {
            continue;
        }
        
        string name = file[..-3];
        if (query_is_racial(name))
        {
            members += ({ name });
        }
    }
    
    return members;
}

public string *
query_all_worshippers()
{
    string * files = get_dir(ELEMENTALIST_DATA);
    string * members = ({ });
    
    foreach (string file : files)
    {
        if (!wildmatch("*.o", file))
        {
            continue;
        }
        
        string name = file[..-3];
        if (query_is_worshipper(name))
        {
            members += ({ name });
        }
    }
    
    return members;
}

public string *
query_all_seekers()
{
    string * files = get_dir(ELEMENTALIST_DATA);
    string * members = ({ });
    
    foreach (string file : files)
    {
        if (!wildmatch("*.o", file))
        {
            continue;
        }
        
        string name = file[..-3];
        if (query_is_seeker(name))
        {
            members += ({ name });
        }
    }
    
    return members;
}

public int
can_see_in_elist(object target, object for_obj)
{
    if (for_obj->query_wiz_level())
    {
        // Wizards can see everyone
        return 1;
    }
    
    if (for_obj == target)
    {
        // Can always see self on list
        return 1;
    }
    
    if (!target->query_wiz_level())
    {
        // Not a wizard. If target is a junior, then cannot be seen by others
        if (wildmatch("*jr", target->query_real_name()))
        {
            return 0;
        }
        return 1;
    }
    
    if (target->query_invis() >= 100
        || !target->query_prop(LIVE_I_ALWAYSKNOWN))
    {
        // Invisible and unknown wizards don't show up on the who
        // list, and they shouldn't show up in alist
        return 0;
    }
    
    return 1;
}

public object *
query_awake_clerics(object for_obj = this_player())
{
    mixed list;
    object * all_players = users() 
        + filter(all_inventory(find_object("/d/Genesis/obj/statue")), living);
    list = filter(all_players, &operator(==)(GUILD_EC_NAME) @
        &->query_guild_name_occ());
    list = filter(list, &can_see_in_elist(, for_obj));
    
    return list;
}

public object *
query_awake_worshippers(object for_obj = this_player())
{
    mixed list;
    object * all_players = users() 
        + filter(all_inventory(find_object("/d/Genesis/obj/statue")), living);
    list = filter(all_players, &operator(==)(GUILD_EW_NAME) @
        &->query_guild_name_lay());
    list = filter(list, &can_see_in_elist(, for_obj));
    
    return list;
}

public object *
query_awake_seekers(object for_obj = this_player())
{
    mixed list;
    object * all_players = users() 
        + filter(all_inventory(find_object("/d/Genesis/obj/statue")), living);
    list = filter(all_players, &operator(==)(GUILD_ES_NAME) @
        &->query_guild_name_lay());
    list = filter(list, &can_see_in_elist(, for_obj));
    
    return list;
}

/*==========================
 * PRIMARY ELEMENT FUNCTIONS
 ===========================*/
public void
set_primary_element(mixed player, string element)
{
    set_player_property(player, "primary_element", element);
}

public int
transfer_old_guild_patron_elemental(object player)
{
    // If the player doesn't have a primary element set in the guild
    // manager, it may be set as a SS_PATRON_ELEMENTAL from the old
    // worshippers guild.
    string element;
    int patron_flag = player->query_skill(SS_PATRON_ELEMENTAL);
    switch (patron_flag)
    {
    case FIRE_FLAG:
        element = "fire";
        break;
        
    case WATER_FLAG:
        element = "water";
        break;
        
    case EARTH_FLAG:
        element = "earth";
        break;
        
    case AIR_FLAG:
        element = "air";
        break;
            
    default:
        return 0;
    }
    
    // If we get here, that means we found the patron elemental
    // Set it so that we don't need to query the skill next time.
    set_primary_element(player, element);
    player->remove_skill(SS_PATRON_ELEMENTAL);
    send_debug_message("worshipper", capitalize(player->query_real_name())
                       + "'s primary element has been transferred from "
                       + patron_flag + " to " + element + ".", EVENTS_LOG);
    return 1;
}

/*
 * Function:    query_primary_element
 * Description: This returns the string of the primary element that the
 *              member has chosen. It will return 0 if nothing has been
 *              chosen.
 */
public string
query_primary_element(mixed player)
{
    if (objectp(player))
    {
        // NPC Primary Element (for testing) is stored in the prop of the
        // player object
        if (player->query_npc())
        {
            if (!player->query_prop("_npc_primary_element"))
            {
                return "fire";
            }
            return player->query_prop("_npc_primary_element");
        }

        // Check to see if we need to transfer the element over
        transfer_old_guild_patron_elemental(player);
    }

    string element = query_player_property(player, "primary_element");
    switch (element)
    {
    case "fire":
    case "water":
    case "air":
    case "earth":
    case "life":
        return element;
    }
    
    return 0;
}

/*
 * Function:    query_primary_element_skillnum
 * Description: This returns the element skillnum for the chosen primary
 *              element. It will return 0 if none has been selected.
 */
public int
query_primary_element_skillnum(mixed player)
{
    string element = query_primary_element(player);
    switch (element)
    {
    case "fire":
        return SS_ELEMENT_FIRE;
        
    case "water":
        return SS_ELEMENT_WATER;
        
    case "air":
        return SS_ELEMENT_AIR;
    
    case "earth":
        return SS_ELEMENT_EARTH;
    
    case "life":
        return SS_ELEMENT_LIFE;
    }

    return 0;    
}

/*==========================
 * ELEMENT CARVING FUNCTIONS
 ===========================*/
public void
set_carved_value(mixed player, int value)
{
    set_player_property(player, "carved_value", value);
}

public int
query_carved_value(mixed player)
{
    return query_player_property(player, "carved_value");
}

public void
set_fire_carving(mixed player) 
{
    int value = query_carved_value(player);
    set_carved_value(player, value | FIRE_FLAG);
}

public void
set_earth_carving(mixed player)
{
    int value = query_carved_value(player);
    set_carved_value(player, value | EARTH_FLAG);
}

public void
set_air_carving(mixed player)
{
    int value = query_carved_value(player);
    set_carved_value(player, value | AIR_FLAG);
}

public void
set_water_carving(mixed player)
{
    int value = query_carved_value(player);
    set_carved_value(player, value | WATER_FLAG);
}

public void
set_spirit_carving(mixed player)
{
    int value = query_carved_value(player);
    set_carved_value(player, value | SPIRIT_FLAG);
}

public int
is_element_carved(mixed player, int element_flag)
{
    int value = query_carved_value(player);
    return ((value & element_flag) != 0) ? 1 : 0;
}

public int
is_fire_carved(mixed player)
{
    return is_element_carved(player, FIRE_FLAG);
}

public int
is_earth_carved(mixed player)
{
    return is_element_carved(player, EARTH_FLAG);
}

public int
is_air_carved(mixed player)
{
    return is_element_carved(player, AIR_FLAG);
}

public int
is_water_carved(mixed player)
{
    return is_element_carved(player, WATER_FLAG);
}

public int
is_spirit_carved(mixed player)
{
    return is_element_carved(player, SPIRIT_FLAG);
}

public int
transfer_old_guild_carving(object player)
{
    if (query_carved_value(player) != 0)
    {
        // Have already converted? No need to do it again.
        return 1;
    }

    int carved_value = player->query_skill(SS_CARVED);
    set_carved_value(player, carved_value);
    player->remove_skill(SS_CARVED);
    send_debug_message("worshipper", capitalize(player->query_real_name())
                       + "'s carving value (" + carved_value + ") has been "
                       + "transferred.", EVENTS_LOG);
    return 1;
}

/*==========================
 * PRACTICE LEVEL FUNCTIONS
 ===========================*/
public int
query_practice_level(mixed player)
{
    return query_player_property(player, "practice_level");
}

public void
set_practice_level(mixed player, int level)
{
    if (level > MAX_PRACTICE_LEVEL)
        level = MAX_PRACTICE_LEVEL;
    set_player_property(player, "practice_level", level);
}

public void
add_practice_level(mixed player, int amount)
{
    int level = query_practice_level(player);
    set_practice_level(player, level + amount);
}

/*==========================
 * CONDUIT LEVEL FUNCTIONS
 ===========================*/
public int
query_player_conduit_earned(mixed player)
{
    return query_player_property(player, "conduit_earned");
}

public void
set_player_conduit_earned(mixed player, int level)
{
	if (level > MAX_PERSONAL_CONDUIT)
        level = MAX_PERSONAL_CONDUIT;
    set_player_property(player, "conduit_earned", level);
}

public void
add_player_conduit_earned(mixed player, int amount)
{
    int level = query_player_conduit_earned(player);
    set_player_conduit_earned(player, level + amount);
} 

public void
subtract_player_conduit_earned(mixed player, int amount)
{
    int level = query_player_conduit_earned(player);
    level -= amount;
    if (level < 0)
    	set_player_conduit_earned(player, 0);
    else
    	set_player_conduit_earned(player, level);
}

public int
query_player_conduit_spent(mixed player)
{
    return query_player_property(player, "conduit_spent");
}

public void
set_player_conduit_spent(mixed player, int level)
{
    set_player_property(player, "conduit_spent", level);
}

public void
add_player_conduit_spent(mixed player, int amount)
{
    int level = query_player_conduit_spent(player);
    set_player_conduit_spent(player, level + amount);
} 

public int
query_player_conduit_contribution(mixed player)
{
    int earned = query_player_conduit_earned(player);
    int spent = query_player_conduit_spent(player);
    int contribution = earned - spent;
    
    return contribution;
}

public int
query_guild_conduit()
{
    return query_player_property("guild", "conduit_score");
}

public void
set_guild_conduit(int level)
{
	if (level >= MAX_GUILD_CONDUIT_SCORE)
        level = MAX_GUILD_CONDUIT_SCORE;
    set_player_property("guild", "conduit_score", level);
}

public void
add_guild_conduit(int amount)
{
    int level = query_guild_conduit();
    int total = level + amount;
    if (total >= MAX_GUILD_CONDUIT_SCORE)
        total = MAX_GUILD_CONDUIT_SCORE;
    set_guild_conduit(total);
}

public void
subtract_guild_conduit(int amount)
{
    int level = query_guild_conduit();
    int total = level - amount;
    if (total <= 0)
        total = 0;
    set_guild_conduit(total);
} 

/*==========================
 * TELL HISTORY FUNCTIONS
 ===========================*/

public mixed
query_tell_history(mixed player)
{
    mixed history = query_player_property(player, "tell_history");
    history = filter(history, pointerp);
    if (!sizeof(history))
    {
        return ({ });
    }
    return history;
}

public void
add_tell_message(mixed player, string sender, string message)
{
    mixed history = query_player_property(player, "tell_history");
    if (!pointerp(history))
    {
        history = ({ });
    }
    history = filter(history, not @ stringp);
    history += ({ ({ sender, message }) });
    if (sizeof(history) > 10)
    {
        history = history[-10..];
    }
    set_player_property(player, "tell_history", history);
}

/* ====================================
 * SPELL MAINTENANCE UTILITY FUNCTIONS
 ======================================*/
 
/* 
 * Function:    get_existing_choma_objects
 * Description: choma is a spell with four effects. Need to ensure that only
 *              one of them is active at any time.
 */
public object *
get_existing_choma_objects(object target)
{    
    mixed effects = filter(SPELL_MANAGER_SOUL->query_magic_effects(target),
        &wildmatch("choma*") @ lower_case @ &->query_spell_effect_name()); 
    if (sizeof(effects))    
    {   
        return effects;
    }
    
    return 0;
}

/* 
 * Function:    get_existing_schirmo_objects
 * Description: Schirmo is a spell with four effects. Need to ensure that only
 *              one of them is active at any time.
 */
public object *
get_existing_schirmo_objects(object target)
{    
    mixed effects = filter(target->query_magic_effects(), &wildmatch("schirmo*") 
                           @ lower_case @ &->query_spell_effect_name()); 
    if (sizeof(effects))    
    {   
        return effects;
    }
    
    return 0;
}

/* 
 * Function:    get_existing_unteristi_objects
 * Description: Utility function to identify whether someone has the unteristi
 *              spell effect active.
 */
public object *
get_existing_unteristi_objects(object target)
{
    return (ELEMENTALIST_SPELLS + "unteristi")->get_existing_spell_objects(target);
}

/* 
 * Function:    get_existing_dynami_objects
 * Description: Utility function to identify whether someone has the dynami
 *              spell effect active.
 */
public object *
get_existing_dynami_objects(object target)
{
    return (ELEMENTALIST_SPELLS + "dynami")->get_existing_spell_objects(target);
}

/* 
 * Function:    get_existing_evimero_objects
 * Description: Utility function to identify whether someone has the evimero
 *              spell effect active.
 */
public object *
get_existing_evimero_objects(object target)
{
    return (ELEMENTALIST_SPELLS + "evimero")->get_existing_spell_objects(target);
}

/* 
 * Function:    get_existing_dynami_objects
 * Description: Utility function to identify whether someone has the dynami
 *              spell effect active.
 */
public object *
get_existing_ec_dynami_objects(object target)
{
    return (ELEMENTALIST_SPELLS + "ec_dynami")->get_existing_spell_objects(target);
}

/* 
 * Function:    get_existing_evimero_objects
 * Description: Utility function to identify whether someone has the evimero
 *              spell effect active.
 */
public object *
get_existing_ec_evimero_objects(object target)
{
    return (ELEMENTALIST_SPELLS + "ec_evimero")->get_existing_spell_objects(target);
}

/* 
 * Function:    query_defensive_spells_active
 * Description: Utility function to identify the number of defensive spells the
 *              Elementalist currently has active.
 */
public object *
query_defensive_spells_active(object target)
{
    object * defensive_spells = ({ });
    object * schirmo_objects = get_existing_schirmo_objects(target);
    object * unteristi_objects = get_existing_unteristi_objects(target);
    if (sizeof(schirmo_objects))
    {
        defensive_spells += schirmo_objects;
    }
    if (sizeof(unteristi_objects))
    {
        defensive_spells += unteristi_objects;
    } 
    return defensive_spells;   
}

/* 
 * Function:    query_power_spells_active
 * Description: Utility function to identify the number of power spells the
 *              Elementalist currently has active.
 */
public object *
query_power_spells_active(object target)
{
    object * power_spells = ({ });
    object * dynami_objects = get_existing_dynami_objects(target);
    object * evimero_objects = get_existing_evimero_objects(target);
    if (sizeof(dynami_objects))
    {
        power_spells += dynami_objects;
    }
    if (sizeof(evimero_objects))
    {
        power_spells += evimero_objects;
    } 
    return power_spells;   
}

/*
 * Function:    query_power_spells_combat_aid
 * Description: The caid can be either 30% or 55% depending on
 *              what defensive spells they had in place when
 *              they cast it.
 */
public int
query_power_spells_combat_aid(object target)
{
    object * power_spells = query_power_spells_active(target);
    int caid = 0;
    foreach (object spellobj : power_spells)
    {
        mixed input = spellobj->query_spell_effect_input();
        if (floatp(input))
        {
            // evimero uses a float to indicate combat aid.
            caid += ftoi(input);
        }
        else if (mappingp(input))
        {
            // dynami uses an array of integer values
            caid += SUM_ARRAY(m_values(input));
        }
    }
    return caid;
}

/*
 * Function:    query_active_schirmo_element
 * Description: Allows the current schirmo type to be determined.
 */
public int
query_active_schirmo_element(object target)
{
    object * schirmo_objects = get_existing_schirmo_objects(target);
    foreach (object schirmo_object : schirmo_objects)
    {
        switch (MASTER_OB(schirmo_object))
        {
        case ELEMENTALIST_SPELL_OBJS + "fire_shield_obj":
            return SS_ELEMENT_FIRE;
        
        case ELEMENTALIST_SPELL_OBJS + "earth_shield_obj":
            return SS_ELEMENT_EARTH;
        
        case ELEMENTALIST_SPELL_OBJS + "water_shield_obj":
            return SS_ELEMENT_WATER;
        
        case ELEMENTALIST_SPELL_OBJS + "air_shield_obj":
            return SS_ELEMENT_AIR;
        }
    }
    
    return 0;
}

/* ====================================
 * COUNCIL RELATED FUNCTIONS
 ======================================*/
/*
 * is_ew_council                - whether the person holds the Worshipper 
 *                                council position
 * is_ec_council                - whether the person holds the Cleric council 
 *                                position
 * is_ew_leader                 - whether the person is the leader (Focus) 
 *                                of the Worshippers
 * is_ec_leader                 - whether the person is the leader (Focus) 
 *                                of the Clerics
 * is_child_cleric              - whether the person is a Child in the Clerics
 * is_master_cleric             - whether the person is a Master in the Clerics
 * is_elder_cleric              - whether the person is an Elder in the Clerics
 * is_full_master               - whether the person is a Full Master rank in 
 *                                the Clerics
 * is_conservator               - whether the person is a Conservator of the 
 *                                Clerics (In charge of the racks/equipment)
 * is_luminary                  - whether the person is a Luminary of the 
 *                                Clerics (In charge of the Library)
 * is_illuminati                - whether the person is an Illuminati of the 
 *                                Clerics (In charge researching and vault 
 *                                artifacts)
 * is_emissary                  - whether the person is an Emissary of the 
 *                                Clerics (In charge of diplomatic relations 
 *                                with other guilds)
 * is_cultivator                - whether the person is a Cultivator of the 
 *                                Clerics (In charge of the gardens (herb/gem))
 * is_liberator                 - whether the person is a Liberator of the 
 *                                Clerics (Soulless information expert)
 * is_punish_train_banned       - training ban punishment
 * is_punish_spell_banned       - spell ban punishment
 * is_punish_temple_banned      - temple ban punishment
 * is_punish_resource_banned    - temple resource ban punishment
 * is_child_approved            - mentor has granted more power to their student
 * is_guild_discharged          - whether the player has been discharged from 
 *                                the guild
 * is_guild_expelled            - whether the player has been expelled from 
 *                                the guild
 * is_guild_betrayed            - whether the player has betrayed the guild
 * guild_notes                  - any notes recorded about the member
 */

public void
set_ew_council(mixed player, int value)
{
    set_player_property(player, "is_ew_council", value);
    // Update the cache
    query_ew_council(); // force the loading of the cache
    if (!value)
    {
        // Person is being removed
        ew_council_members -= ({ get_id(player) });
    }
    else
    {
        // Person is being added
        if (!IN_ARRAY(get_id(player), ew_council_members))
        {
            ew_council_members += ({ get_id(player) });
        }
    }
}

public void
set_ec_council(mixed player, int value)
{
    set_player_property(player, "is_ec_council", value);
    // Update the cache
    query_ec_council(); // force the loading of the cache
    if (!value)
    {
        // Person is being removed
        ec_council_members -= ({ get_id(player) });
    }
    else
    {
        // Person is being added
        if (!IN_ARRAY(get_id(player), ec_council_members))
        {
            ec_council_members += ({ get_id(player) });
        }
    }
}

public int
query_is_ew_council(mixed player, int bIncludeNonEW = 0)
{
    if (!bIncludeNonEW)
    {
        return query_player_property(player, "is_ew_council");
    }

    // The following categories are considered EW Council
    // 1. Actual EW Council members
    // 2. SCoP Elders
    // 3. Calian Wizards
    // 4. Wizards of Arch Level or Higher
    if (query_player_property(player, "is_ew_council"))
    {
        return 1;
    }
    
    if (query_player_property(player, "is_ec_leader"))
    {
        return 1;
    }

    if (SPIRIT_COUNCIL_CODE->is_spirit_elder(get_id(player)))
    {
        return 1;
    }

    if (SECURITY->query_wiz_dom(get_id(player)) == "Calia")
    {
        return 1;
    }

    if (SECURITY->query_wiz_rank(get_id(player)) >= WIZ_ARCH)
    {
        return 1;
    }

    return 0;
}

public int
query_is_ec_council(mixed player, int bIncludeNonEW = 0)
{
    if (!bIncludeNonEW)
    {
        return query_player_property(player, "is_ec_council");
    }

    // The following categories are considered EC Council
    // 1. Actual EC Council members
    // 2. SCoP Elders
    // 3. Calian Wizards
    // 4. Wizards of Arch Level or Higher
    if (query_player_property(player, "is_ec_council"))
    {
        return 1;
    }
    
    if (query_player_property(player, "is_ec_leader"))
    {
        return 1;
    }

    if (SPIRIT_COUNCIL_CODE->is_spirit_elder(get_id(player)))
    {
        return 1;
    }

    if (SECURITY->query_wiz_dom(get_id(player)) == "Calia")
    {
        return 1;
    }

    if (SECURITY->query_wiz_rank(get_id(player)) >= WIZ_ARCH)
    {
        return 1;
    }

    return 0;
}

public string *
query_ew_council()
{
    // First check for a cached copy of the ew_council_members
    if (ew_council_members && pointerp(ew_council_members))
    {
        return ew_council_members;
    }

    // If we don't find it, we need to populate the cache
    string * files = get_dir(ELEMENTALIST_DATA);
    string * members = ({ });
    
    foreach (string file : files)
    {
        if (!wildmatch("*.o", file))
        {
            continue;
        }
        
        string name = file[..-3];
        if (query_is_ew_council(name))
        {
            members += ({ name });
        }
    }
    
    ew_council_members = members + ({ }); // save to cache
    return members;
}

public string
query_ew_focus()
{
    // First check for a cached copy of the ew_focus
    if (ew_focus && pointerp(ew_focus))
    {
        return ew_focus;
    }

    // If we don't find it, we need to populate the cache
    string focus;
    focus = query_player_property("guild", "is_ew_focus");
    
    ew_focus = focus; // save to cache
    if (focus == 0)
        focus = "None";
        
    return focus;
}

public string
set_ew_focus(string str, string who)
{
    str = lower_case(str);
    // First check if there is already someone listed as focus in cache
    if (ew_focus && pointerp(ew_focus))
    {
        return "There is already someone set as Focus ("+
            ew_focus+").\n";
    }
    
    // If we don't find it, we need to populate the cache so we can replace
    // them
    string current_focus = query_player_property("guild", "is_ew_focus");
    
    // Are they a council member? If not, they can't be focus
    if (query_player_property(str, "is_ew_council") !=1)
    {
        return capitalize(str)+" isn't a member of the Worshipper Council "+
            "and therefore can't be Focus.\n";
    }
    
    set_player_property("guild", "is_ew_focus", str);
    set_player_property(str, "is_ew_leader", 1);
    ew_focus = str;
    
    if (!current_focus)
        current_focus = "nobody";
    else
    {
        set_player_property(current_focus, "is_ew_leader", 1);
        current_focus = capitalize(current_focus);
    }
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(str) +
        " has been set as the new Focus (was "+current_focus+") by "+
        capitalize(who)+".\n");
    return capitalize(str)+" has been set as the new Focus (was "+
        current_focus+").\n";
}

public string
remove_ew_focus(string who)
{
    string focus;
    focus = query_player_property("guild", "is_ew_focus");
    if (!focus)
    {
        return "There is no Focus set.\n";
    }
    set_player_property("guild", "is_ew_focus", 0);
    set_player_property(focus, "is_ew_leader", 0);
    ew_focus = 0;
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(focus) +
        " has been removed as the Focus by "+ capitalize(who)+".\n");
    return "The Focus has been removed (was "+capitalize(focus)+").\n";
}

public string
query_ec_focus()
{
    // First check for a cached copy of the ec_focus
    if (ec_focus && pointerp(ec_focus))
    {
        return ec_focus;
    }

    // If we don't find it, we need to populate the cache
    string focus;
    focus = query_player_property("guild", "is_ec_focus");
    
    ec_focus = focus; // save to cache
    if (focus == 0)
        focus = "None";
        
    return focus;
}

public string
set_ec_focus(string str, string who)
{
    str = lower_case(str);
    // First check if there is already someone listed as ec_focus in cache
    if (ec_focus && pointerp(ec_focus))
    {
        return "There is already someone set as Focus ("+
            ec_focus+").\n";
    }
    
    // If we don't find it, we need to populate the cache so we can replace
    // them
    string current_focus = query_player_property("guild", "is_ec_focus");
    
    // Are they a council member? If not, they can't be focus
    if (query_player_property(str, "is_ec_council") !=1)
    {
        return capitalize(str)+" isn't a member of the Cleric Council "+
            "and therefore can't be Focus.\n";
    }
    
    set_player_property("guild", "is_ec_focus", str);
    set_player_property(str, "is_ec_leader", 1);
    ew_focus = str;
    
    if (!current_focus)
        current_focus = "nobody";
    else
    {
        set_player_property(current_focus, "is_ec_leader", 1);
        current_focus = capitalize(current_focus);
    }
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(str) +
        " has been set as the new Elementalist Focus (was "+current_focus +
        ") by " + capitalize(who) + ".\n");
    return capitalize(str)+" has been set as the new Elementalist Focus (was "+
        current_focus+").\n";
}

public string
remove_ec_focus(string who)
{
    string focus;
    focus = query_player_property("guild", "is_ec_focus");
    if (!focus)
    {
        return "There is no Focus set.\n";
    }
    set_player_property("guild", "is_ec_focus", 0);
    set_player_property(focus, "is_ec_leader", 0);
    ew_focus = 0;
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(focus) +
        " has been removed as the Elementalist Focus by "+ capitalize(who)+
        ".\n");
    return "The Elementalist Focus has been removed (was "+capitalize(focus)+
        ").\n";
}
    
public string *
query_ec_council()
{
    // First check for a cached copy of the ew_council_members
    if (ec_council_members && pointerp(ec_council_members))
    {
        return ec_council_members;
    }

    // If we don't find it, we need to populate the cache
    string * files = get_dir(ELEMENTALIST_DATA);
    string * members = ({ });
    
    foreach (string file : files)
    {
        if (!wildmatch("*.o", file))
        {
            continue;
        }
        
        string name = file[..-3];
        if (query_is_ec_council(name))
        {
            members += ({ name });
        }
    }
    
    ec_council_members = members + ({ }); // save to cache
    return members;
}

public string
query_ec_conservator()
{
    // First check for a cached copy of the ec_luminary
    if (ec_conservator && pointerp(ec_conservator))
    {
        return ec_conservator;
    }

    // If we don't find it, we need to populate the cache
    string conservator;
    conservator = query_player_property("guild", "is_ec_conservator");
    
    ec_conservator = conservator; // save to cache
    if (conservator == 0)
        conservator = "None";
    return conservator;
}

public string
set_ec_conservator(string str, string who)
{
    str = lower_case(str);
    // First check if there is already someone listed as conservator in cache
    if (ec_conservator && pointerp(ec_conservator))
    {
        return "There is already someone set as Conservator ("+
            ec_conservator+").\n";
    }
    
    // If we don't find it, we need to populate the cache so we can replace 
    // them
    string current_conservator = query_player_property("guild",
         "is_ec_conservator");
    
    // Are they a member? If not, they can't be conservator
    if (query_player_property(str, "is_cleric") !=1)
    {
        return capitalize(str)+" isn't a member of the Clerics "+
            "and therefore can't be Conservator.\n";
    }
    
    set_player_property("guild", "is_ec_conservator", str);
    set_player_property(str, "is_ec_conservator", 1);
    ec_conservator = str;
    
    if (!current_conservator)
        current_conservator = "nobody";
    else
    {
        set_player_property(current_conservator, "is_ec_conservator", 1);
        current_conservator = capitalize(current_conservator);
    }
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(str) +
        " has been set as the new Conservator (was "+current_conservator+
        ") by " + capitalize(who) + ".\n");
    return capitalize(str)+" has been set as the new Conservator (was "+
        current_conservator+").\n";
}

public string
remove_ec_conservator(string who)
{
    string conservator;
    conservator = query_player_property("guild", "is_ec_conservator");
    if (!conservator)
    {
        return "There is no Conservator set.\n";
    }
    
    set_player_property("guild", "is_ec_conservator", 0);
    set_player_property(conservator, "is_ec_conservator", 0);
    ec_conservator = 0;
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(conservator) +
        " has been removed as the Conservator by "+ capitalize(who)+".\n");
    return "The Conservator has been removed (was "+capitalize(conservator)+
        ").\n";
}

public string
query_ec_luminary()
{
    // First check for a cached copy of the ec_luminary
    if (ec_luminary && pointerp(ec_luminary))
    {
        return ec_luminary;
    }

    // If we don't find it, we need to populate the cache
    string luminary;
    luminary = query_player_property("guild", "is_ec_luminary");
    
    ec_luminary = luminary; // save to cache
    if (luminary == 0)
        luminary = "None";
    return luminary;
}

public string
set_ec_luminary(string str, string who)
{
    str = lower_case(str);
    // First check if there is already someone listed as luminary in cache
    if (ec_luminary && pointerp(ec_luminary))
    {
        return "There is already someone set as Luminary ("+
            ec_luminary+").\n";
    }
    
    // If we don't find it, we need to populate the cache so we can replace 
    // them
    string current_luminary = query_player_property("guild", "is_ec_luminary");
    
    // Are they a member? If not, they can't be Luminary
    if (query_player_property(str, "is_cleric") !=1)
    {
        return capitalize(str)+" isn't a member of the Clerics "+
            "and therefore can't be Luminary.\n";
    }
    
    set_player_property("guild", "is_ec_luminary", str);
    set_player_property(str, "is_ec_luminary", 1);
    ec_luminary = str;
    
    if (!current_luminary)
        current_luminary = "nobody";
    else
    {
        set_player_property(current_luminary, "is_ec_luminary", 1);
        current_luminary = capitalize(current_luminary);
    }
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(str) +
        " has been set as the new Luminary (was "+current_luminary+") by "+
        capitalize(who)+".\n");
    return capitalize(str)+" has been set as the new Luminary (was "+
        current_luminary+").\n";
}

public string
remove_ec_luminary(string who)
{
    string luminary;
    luminary = query_player_property("guild", "is_ec_luminary");
    if (!luminary)
    {
        return "There is no Luminary set.\n";
    }
    
    set_player_property("guild", "is_ec_luminary", 0);
    set_player_property(luminary, "is_ec_luminary", 0);
    ec_luminary = 0;
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(luminary) +
        " has been removed as the Luminary by "+ capitalize(who)+".\n");
    return "The Luminary has been removed (was "+capitalize(luminary)+").\n";
}

public string
query_ec_illuminati()
{
    // First check for a cached copy of the ec_illuminati
    if (ec_illuminati && pointerp(ec_illuminati))
    {
        return ec_illuminati;
    }

    // If we don't find it, we need to populate the cache
    string illuminati;
    illuminati = query_player_property("guild", "is_ec_illuminati");
    
    ec_illuminati = illuminati; // save to cache
    if (illuminati == 0)
        illuminati = "None";
    return illuminati;
}

public string
set_ec_illuminati(string str, string who)
{
    str = lower_case(str);
    // First check if there is already someone listed as illuminati in cache
    if (ec_illuminati && pointerp(ec_illuminati))
    {
        return "There is already someone set as Illuminati ("+
            ec_illuminati+").\n";
    }
    
    // If we don't find it, we need to populate the cache so we can replace 
    // them
    string current_illuminati = query_player_property("guild", 
        "is_ec_illuminati");
    
    // Are they a member? If not, they can't be illuminati
    if (query_player_property(str, "is_cleric") !=1)
    {
        return capitalize(str)+" isn't a member of the Clerics "+
            "and therefore can't be Illuminati.\n";
    }
    
    set_player_property("guild", "is_ec_illuminati", str);
    set_player_property(str, "is_ec_illuminati", 1);
    ec_illuminati = str;
    
    if (!current_illuminati)
        current_illuminati = "nobody";
    else
    {
        set_player_property(current_illuminati, "is_ec_illuminati", 1);
        current_illuminati = capitalize(current_illuminati);
    }
    
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(str) +
        " has been set as the new Illuminati (was "+current_illuminati+") by "+
        capitalize(who)+".\n");
    return capitalize(str)+" has been set as the new Illuminati (was "+
        current_illuminati+").\n";
}

public string
remove_ec_illuminati(string who)
{
    string illuminati;
    illuminati = query_player_property("guild", "is_ec_illuminati");
    if (!illuminati)
    {
        return "There is no Illuminati set.\n";
    }
    set_player_property("guild", "is_ec_illuminati", 0);
    set_player_property(illuminati, "is_ec_illuminati", 0);
    ec_illuminati = 0;
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(illuminati) +
        " has been removed as the Illuminati by "+ capitalize(who)+".\n");
    return "The Illuminati has been removed (was "+capitalize(illuminati)+
        ").\n";
}

public string
query_ec_emissary()
{
    // First check for a cached copy of the ec_emissary
    if (ec_emissary && pointerp(ec_emissary))
    {
        return ec_emissary;
    }

    // If we don't find it, we need to populate the cache
    string emissary;
    emissary = query_player_property("guild", "is_ec_emissary");
    
    ec_emissary = emissary; // save to cache
    if (emissary == 0)
        emissary = "None";
    return emissary;
}

public string
set_ec_emissary(string str, string who)
{
    str = lower_case(str);
    // First check if there is already someone listed as emissary in cache
    if (ec_emissary && pointerp(ec_emissary))
    {
        return "There is already someone set as Emissary ("+
            ec_emissary+").\n";
    }
    
    // If we don't find it, we need to populate the cache so we can replace 
    // them
    string current_emissary = query_player_property("guild", "is_ec_emissary");
    
    // Are they a member? If not, they can't be emissary
    if (query_player_property(str, "is_cleric") !=1)
    {
        return capitalize(str)+" isn't a member of the Clerics "+
            "and therefore can't be Emissary.\n";
    }
    
    set_player_property("guild", "is_ec_emissary", str);
    set_player_property(str, "is_ec_emissary", 1);
    ec_emissary = str;
    
    if (!current_emissary)
        current_emissary = "nobody";
    else
    {
        set_player_property(current_emissary, "is_ec_emissary", 1);
        current_emissary = capitalize(current_emissary);
    }
    
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(str) +
        " has been set as the new Emissary (was "+current_emissary+") by "+
        capitalize(who)+".\n");
    return capitalize(str)+" has been set as the new Emissary (was "+
        current_emissary+").\n";
}

public string
remove_ec_emissary(string who)
{
    string emissary;
    emissary = query_player_property("guild", "is_ec_emissary");
    if (!emissary)
    {
        return "There is no Emissary set.\n";
    }
    set_player_property("guild", "is_ec_emissary", 0);
    set_player_property(emissary, "is_ec_emissary", 0);
    ec_emissary = 0;
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(emissary) +
        " has been removed as the Emissary by "+ capitalize(who)+".\n");
    return "The Emissary has been removed (was "+capitalize(emissary)+").\n";
}

public string
query_ec_cultivator()
{
    // First check for a cached copy of the ec_cultivator
    if (ec_cultivator && pointerp(ec_cultivator))
    {
        return ec_cultivator;
    }

    // If we don't find it, we need to populate the cache
    string cultivator;
    cultivator = query_player_property("guild", "is_ec_cultivator");
    
    ec_cultivator = cultivator; // save to cache
    if (cultivator == 0)
        cultivator = "None";
    return cultivator;
}

public string
set_ec_cultivator(string str, string who)
{
    str = lower_case(str);
    // First check if there is already someone listed as cultivator in cache
    if (ec_cultivator && pointerp(ec_cultivator))
    {
        return "There is already someone set as Cultivator ("+
            ec_cultivator+").\n";
    }
    
    // If we don't find it, we need to populate the cache so we can replace 
    // them
    string current_cultivator = query_player_property("guild",
        "is_ec_cultivator");
    
    // Are they a member? If not, they can't be cultivator
    if (query_player_property(str, "is_cleric") !=1)
    {
        return capitalize(str)+" isn't a member of the Clerics "+
            "and therefore can't be Cultivator.\n";
    }
    
    set_player_property("guild", "is_ec_cultivator", str);
    set_player_property(str, "is_ec_cultivator", 1);
    ec_cultivator = str;
    
    if (!current_cultivator)
        current_cultivator = "nobody";
    else
    {
        set_player_property(current_cultivator, "is_ec_cultivator", 1);
        current_cultivator = capitalize(current_cultivator);
    }
    
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(str) +
        " has been set as the new Cultivator (was "+current_cultivator+") by "+
        capitalize(who)+".\n");
    return capitalize(str)+" has been set as the new Cultivator (was "+
        current_cultivator+").\n";
}

public string
remove_ec_cultivator(string who)
{
    string cultivator;
    cultivator = query_player_property("guild", "is_ec_cultivator");
    if (!cultivator)
    {
        return "There is no Cultivator set.\n";
    }
    
    set_player_property("guild", "is_ec_cultivator", 0);
    set_player_property(cultivator, "is_ec_cultivator", 0);
    ec_cultivator = 0;
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(cultivator) +
        " has been removed as the Cultivator by "+ capitalize(who)+".\n");
    return "The Cultivator has been removed (was "+capitalize(cultivator)+
        ").\n";
}

public string
query_ec_liberator()
{
    // First check for a cached copy of the ec_liberator
    if (ec_liberator && pointerp(ec_liberator))
    {
        return ec_liberator;
    }

    // If we don't find it, we need to populate the cache
    string liberator;
    liberator = query_player_property("guild", "is_ec_liberator");
    
    ec_liberator = liberator; // save to cache
    if (liberator == 0)
        liberator = "None";
    return liberator;
}

public string
set_ec_liberator(string str, string who)
{
    str = lower_case(str);
    // First check if there is already someone listed as liberator in cache
    if (ec_liberator && pointerp(ec_liberator))
    {
        return "There is already someone set as Liberator ("+
            ec_liberator+").\n";
    }
    
    // If we don't find it, we need to populate the cache so we can replace 
    // them
    string current_liberator = query_player_property("guild",
        "is_ec_liberator");
    
    // Are they a member? If not, they can't be liberator
    if (query_player_property(str, "is_cleric") !=1)
    {
        return capitalize(str)+" isn't a member of the Clerics "+
            "and therefore can't be Liberator.\n";
    }
    
    set_player_property("guild", "is_ec_liberator", str);
    set_player_property(str, "is_ec_liberator", 1);
    ec_liberator = str;
    
    if (!current_liberator)
        current_liberator = "nobody";
    else
    {
        set_player_property(current_liberator, "is_ec_liberator", 1);
        current_liberator = capitalize(current_liberator);
    }
    
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(str) +
        " has been set as the new Liberator (was "+current_liberator+") by "+
        capitalize(who)+".\n");
    return capitalize(str)+" has been set as the new Liberator (was "+
        current_liberator+").\n";
}

public string
remove_ec_liberator(string who)
{
    string liberator;
    liberator = query_player_property("guild", "is_ec_liberator");
    if (!liberator)
    {
        return "There is no Liberator set.\n";
    }
    set_player_property("guild", "is_ec_liberator", 0);
    set_player_property(liberator, "is_ec_liberator", 0);
    ec_liberator = 0;
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(liberator) +
        " has been removed as the Liberator by "+ capitalize(who)+".\n");
    return "The Liberator has been removed (was "+capitalize(liberator)+").\n";
}

public string
query_ec_archon_revelation()
{
    // First check for a cached copy of the ec_archon_revelation
    if (ec_archon_revelation && pointerp(ec_archon_revelation))
    {
        return ec_archon_revelation;
    }

    // If we don't find it, we need to populate the cache
    string archon_revelation;
    archon_revelation = query_player_property("guild",
        "is_ec_archon_revelation");
    
    ec_archon_revelation = archon_revelation; // save to cache
    if (archon_revelation == 0)
        archon_revelation = "None";
    return archon_revelation;
}

public string
set_ec_archon_revelation(string str, string who)
{
    str = lower_case(str);
    // First check if there is already someone listed as ec_archon_revelation 
    // in cache
    if (ec_archon_revelation && pointerp(ec_archon_revelation))
    {
        return "There is already someone set as Archon of Revelation ("+
            ec_archon_revelation+").\n";
    }
    
    // If we don't find it, we need to populate the cache so we can replace 
    // them
    string current_archon_revelation = query_player_property("guild",
        "is_ec_archon_revelation");
    
    // Are they a council member? If not, they can't be ec_archon_revelation
    if (query_player_property(str, "is_ec_council") !=1)
    {
        return capitalize(str)+" isn't a member of the council "+
            "and therefore can't be Archon of Revelation.\n";
    }
    
    set_player_property("guild", "is_ec_archon_revelation", str);
    set_player_property(str, "is_ec_archon_revelation", 1);
    ec_archon_revelation = str;
    
    if (!current_archon_revelation)
        current_archon_revelation = "nobody";
    else
    {
        set_player_property(current_archon_revelation, 
            "is_ec_archon_revelation", 1);
        current_archon_revelation = capitalize(current_archon_revelation);
    }
    
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(str) +
        " has been set as the new Archon of Revelation (was "+
        current_archon_revelation + ") by " + capitalize(who)+".\n");
    return capitalize(str)+" has been set as the new Archon of Revelation "+
        "(was " + current_archon_revelation+").\n";
}

public string
remove_ec_archon_revelation(string who)
{
    string archon_revelation;
    archon_revelation = query_player_property("guild", 
        "is_ec_archon_revelation");
    if (!archon_revelation)
    {
        return "There is no Archon of Revelation set.\n";
    }
    set_player_property("guild", "is_ec_archon_revelation", 0);
    set_player_property(archon_revelation, "is_ec_archon_revelation", 0);
    ec_archon_revelation = 0;
    COUNCIL_LOG_BOOK->update_log_book(my_time() + 
        capitalize(archon_revelation) + " has been removed as the Archon "+
        "of Revelation by "+ capitalize(who)+".\n");
    return "The Archon of Revelation has been removed (was "+
        capitalize(archon_revelation)+").\n";
}

public string
query_ec_archon_deliverance()
{
    // First check for a cached copy of the ec_archon_deliverance
    if (ec_archon_deliverance && pointerp(ec_archon_deliverance))
    {
        return ec_archon_deliverance;
    }

    // If we don't find it, we need to populate the cache
    string archon_deliverance;
    archon_deliverance = query_player_property("guild", 
        "is_ec_archon_deliverance");
    
    ec_archon_deliverance = archon_deliverance; // save to cache
    if (archon_deliverance == 0)
        archon_deliverance = "None";
    return archon_deliverance;
}

public string
set_ec_archon_deliverance(string str, string who)
{
    str = lower_case(str);
    // First check if there is already someone listed as ec_archon_deliverance 
    // in cache
    if (ec_archon_deliverance && pointerp(ec_archon_deliverance))
    {
        return "There is already someone set as Archon of Deliverance ("+
            ec_archon_deliverance+").\n";
    }
    
    // If we don't find it, we need to populate the cache so we can replace 
    // them
    string current_archon_deliverance = query_player_property("guild", 
        "is_ec_archon_deliverance");
    
    // Are they a council member? If not, they can't be ec_archon_deliverance
    if (query_player_property(str, "is_ec_council") !=1)
    {
        return capitalize(str)+" isn't a member of the council "+
            "and therefore can't be Archon of Deliverance.\n";
    }
    
    set_player_property("guild", "is_ec_archon_deliverance", str);
    set_player_property(str, "is_ec_archon_deliverance", 1);
    ec_archon_deliverance = str;
    
    if (!current_archon_deliverance)
        current_archon_deliverance = "nobody";
    else
    {
        set_player_property(current_archon_deliverance, 
            "is_ec_archon_deliverance", 1);
        current_archon_deliverance = capitalize(current_archon_deliverance);
    }
    
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(str) +
        " has been set as the new Archon of Deliverance (was "+
        current_archon_deliverance + ") by " + capitalize(who)+".\n");
    return capitalize(str)+" has been set as the new Archon of Deliverance "+
        "(was " + current_archon_deliverance + ").\n";
}

public string
remove_ec_archon_deliverance(string who)
{
    string archon_deliverance;
    archon_deliverance = query_player_property("guild", 
        "is_ec_archon_deliverance");
    if (!archon_deliverance)
    {
        return "There is no Archon of Deliverance set.\n";
    }
    set_player_property("guild", "is_ec_archon_deliverance", 0);
    set_player_property(archon_deliverance, "is_ec_archon_deliverance", 0);
    ec_archon_deliverance = 0;
    COUNCIL_LOG_BOOK->update_log_book(my_time() + 
        capitalize(archon_deliverance) +
        " has been removed as the Archon of Deliverance by "+ 
        capitalize(who)+".\n");
    return "The Archon of Deliverance has been removed (was "+
        capitalize(archon_deliverance) + ").\n";
}

public string
query_ec_archon_apotheosis()
{
    // First check for a cached copy of the ec_archon_apotheosis
    if (ec_archon_apotheosis && pointerp(ec_archon_apotheosis))
    {
        return ec_archon_apotheosis;
    }

    // If we don't find it, we need to populate the cache
    string archon_apotheosis;
    archon_apotheosis = query_player_property("guild", 
        "is_ec_archon_apotheosis");
    
    ec_archon_apotheosis = archon_apotheosis; // save to cache
    if (archon_apotheosis == 0)
        archon_apotheosis = "None";
    return archon_apotheosis;
}

public string
set_ec_archon_apotheosis(string str, string who)
{
    str = lower_case(str);
    // First check if there is already someone listed as ec_archon_deliverance 
    // in cache
    if (ec_archon_apotheosis && pointerp(ec_archon_apotheosis))
    {
        return "There is already someone set as Archon of Apotheosis ("+
            ec_archon_apotheosis+").\n";
    }
    
    // If we don't find it, we need to populate the cache so we can replace 
    // them
    string current_archon_apotheosis = query_player_property("guild", 
        "is_ec_archon_apotheosis");
    
    // Are they a council member? If not, they can't be ec_archon_apotheosis
    if (query_player_property(str, "is_ec_council") !=1)
    {
        return capitalize(str)+" isn't a member of the council "+
            "and therefore can't be Archon of Apotheosis.\n";
    }
    
    set_player_property("guild", "is_ec_archon_apotheosis", str);
    set_player_property(str, "is_ec_archon_apotheosis", 1);
    ec_archon_apotheosis = str;
    
    if (!current_archon_apotheosis)
        current_archon_apotheosis = "nobody";
    else
    {
        set_player_property(current_archon_apotheosis, 
            "is_ec_archon_apotheosis", 1);
        current_archon_apotheosis = capitalize(current_archon_apotheosis);
    }
    
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(str) +
        " has been set as the new Archon of Apotheosis (was "+
        current_archon_apotheosis + ") by " + capitalize(who)+".\n");
    return capitalize(str)+" has been set as the new Archon of Apotheosis "+
        "(was " + current_archon_apotheosis + ").\n";
}

public string
remove_ec_archon_apotheosis(string who)
{
    string archon_apotheosis;
    archon_apotheosis = query_player_property("guild", 
        "is_ec_archon_apotheosis");
    if (!archon_apotheosis)
    {
        return "There is no Archon of Apotheosis set.\n";
    }
    set_player_property("guild", "is_ec_archon_apotheosis", 0);
    set_player_property(archon_apotheosis, "is_ec_archon_apotheosis", 0);
    ec_archon_apotheosis = 0;
    COUNCIL_LOG_BOOK->update_log_book(my_time() + 
        capitalize(archon_apotheosis) +
        " has been removed as the Archon of Apotheosis by "+ 
        capitalize(who)+".\n");
    return "The Archon of Apotheosis has been removed (was "+
        capitalize(archon_apotheosis) + ").\n";
}

public void
set_ew_leader(mixed player, int value)
{
    set_player_property(player, "is_ew_leader", value);
}

public void
set_ec_leader(mixed player, int value)
{
    set_player_property(player, "is_ec_leader", value);
}

public int
query_is_ew_leader(mixed player)
{
    return query_player_property(player, "is_ew_leader");
}

public int
query_is_ec_leader(mixed player)
{
    return query_player_property(player, "is_ec_leader");
}

public void
set_child_cleric(mixed player, int value)
{
    set_player_property(player, "is_child_cleric", value);
}

public int
query_is_child_cleric(mixed player)
{
    return query_player_property(player, "is_child_cleric");
}

public void
set_master_cleric(mixed player, int value)
{
    set_player_property(player, "is_child_cleric", 0);
    set_player_property(player, "is_master_cleric", value);
}

public int
query_is_master_cleric(mixed player)
{
    return query_player_property(player, "is_master_cleric");
}

public void
set_elder_cleric(mixed player, int value)
{
    set_player_property(player, "is_elder_cleric", value);
}

public int
query_is_elder_cleric(mixed player)
{
    return query_player_property(player, "is_elder_cleric");
}

public void
set_full_master(mixed player, int value)
{
    set_player_property(player, "is_full_master", value);
}

public int
query_is_full_master(mixed player)
{
    return query_player_property(player, "is_full_master");
}

public void
set_conservator(mixed player, int value)
{
    set_player_property(player, "is_conservator", value);
}

public int
query_is_conservator(mixed player)
{
    return query_player_property(player, "is_conservator");
}

public void
set_luminary(mixed player, int value)
{
    set_player_property(player, "is_ec_luminary", value);
}

public int
query_is_luminary(mixed player)
{
    return query_player_property(player, "is_ec_luminary");
}

public void
set_illuminati(mixed player, int value)
{
    set_player_property(player, "is_illuminati", value);
}

public int
query_is_illuminati(mixed player)
{
    return query_player_property(player, "is_illuminati");
}

public void
set_emissary(mixed player, int value)
{
    set_player_property(player, "is_emissary", value);
}

public int
query_is_emissary(mixed player)
{
    return query_player_property(player, "is_emissary");
}

public void
set_cultivator(mixed player, int value)
{
    set_player_property(player, "is_cultivator", value);
}

public int
query_is_cultivator(mixed player)
{
    return query_player_property(player, "is_cultivator");
}

public void
set_liberator(mixed player, int value)
{
    set_player_property(player, "is_liberator", value);
}

public int
query_is_liberator(mixed player)
{
    return query_player_property(player, "is_liberator");
}

public void
set_punish_train_banned(mixed player, int value)
{
    set_player_property(player, "is_punish_train_banned", value);
}

public int
query_is_punish_train_banned(mixed player)
{
    return query_player_property(player, "is_punish_train_banned");
}

public void
set_punish_spell_banned(mixed player, int value)
{
    set_player_property(player, "is_punish_spell_banned", value);
}

public int
query_is_punish_spell_banned(mixed player)
{
    return query_player_property(player, "is_punish_spell_banned");
}

public void
set_punish_temple_banned(mixed player, int value)
{
    set_player_property(player, "is_punish_temple_banned", value);
}

public int
query_is_punish_temple_banned(mixed player)
{
    return query_player_property(player, "is_punish_temple_banned");
}

public void
set_punish_resource_banned(mixed player, int value)
{
    set_player_property(player, "is_punish_resource_banned", value);
}

public int
query_is_punish_resource_banned(mixed player)
{
    return query_player_property(player, "is_punish_resource_banned");
}

public void
set_guild_discharged(mixed player, int value)
{
    set_player_property(player, "is_guild_discharged", value);
}

public int
query_is_guild_discharged(mixed player)
{
    return query_player_property(player, "is_guild_discharged");
}

public void
set_guild_expelled(mixed player, int value)
{
    set_player_property(player, "is_guild_expelled", value);
}

public int
query_is_guild_expelled(mixed player)
{
    return query_player_property(player, "is_guild_expelled");
}

public void
set_guild_betrayed(mixed player, int value)
{
    set_player_property(player, "is_guild_betrayed", value);
}

public int
query_is_guild_betrayed(mixed player)
{
    return query_player_property(player, "is_guild_betrayed");
}

public void
set_child_approved(mixed player, int value)
{
    set_player_property(player, "is_child_approved", value);
}

public int
query_child_approved(mixed player)
{
    return query_player_property(player, "is_child_approved");
}

public void
set_starting_exp(mixed player, int experience)
{
    set_player_property(player, "starting_exp", experience);
}

public int
query_starting_exp(mixed player) 
{
    return query_player_property(player, "starting_exp");
}

public int
query_starting_date(mixed player) 
{
    return query_player_property(player, "starting_date");
}

public void
set_starting_date(mixed player, int start_date)
{
    set_player_property(player, "starting_date", start_date);
}

public string
query_guild_notes(mixed player) 
{
    return query_player_property(player, "guild_notes");
}

public void
set_guild_notes(mixed player, string notes)
{
    set_player_property(player, "guild_notes", notes);
}

/*
 * Function:    leave_occ_guild
 * Description: Function to remove someone from the Clerics guild.
 */
public int 
leave_occ_guild_discharge(mixed player) 
{ 
    string id = get_id(player);

    object player_obj = find_player(id);
    if (!objectp(player_obj))
    {
        // We simply set the variable so that they will get kicked out
        // the next time they log in.
        remove_cleric(player);
        return 1;
    }

    player_obj->remove_guild_occ();
    player_obj->remove_guild_lay();
    if (player_obj->query_guild_name_race() == GUILD_EC_NAME)
    {
        player_obj->remove_guild_race();
        player_obj->clear_guild_stat(SS_RACE);
        player_obj->setup_skill_decay();
        player_obj->set_guild_pref(SS_RACE, 0);
        player_obj->remove_cmdsoul(EC_RACE_SOUL);
        player_obj->update_hooks();
    }

    int old_occ_guild_stat = player_obj->query_stat(SS_OCCUP);
    int old_lay_guild_stat = player_obj->query_stat(SS_LAYMAN);
    // Clear guild stat, remove guild learn, and begin skill decay
    player_obj->clear_guild_stat(SS_OCCUP);
    player_obj->clear_guild_stat(SS_LAYMAN); 
    player_obj->setup_skill_decay(); 
    player_obj->set_guild_pref(SS_OCCUP, 0);
    player_obj->set_guild_pref(SS_LAYMAN, 0); 
    present("_elemental_guild_wand", player_obj)->remove_object();
    present("_elemental_guild_dagger", player_obj)->remove_object();
    present("_elemental_guild_chalice", player_obj)->remove_object();
    present("_elemental_guild_pentacle", player_obj)->remove_object();
    present("_elemental_guild_mandala", player_obj)->remove_object();
    present("_echosen_", player_obj)->remove_object();

    // Reset the start location of the person leaving the guild
    if (wildmatch(ELEMENTALIST_TEMPLE + "*", 
    	player_obj->query_default_start_location()))
    {
        player_obj->set_default_start_location(player_obj->query_def_start());
    }

    // Remove the command soul
    player_obj->remove_cmdsoul(EC_SOUL);
    player_obj->remove_cmdsoul(EC_LAY_SOUL);
    player_obj->update_hooks();
    
    // Update the Guild Manager
    remove_cleric(player);

    // Log all the existing values in case we need to restore them
    string old_values = "Guild Stat: " + old_occ_guild_stat + "\n"
        + "Carved Value: " + query_carved_value(player) + "\n"
        + "Primary Element: " + query_primary_element(player) + "\n"
        + "Practice Level: " + query_practice_level(player) + ".\n";
    send_debug_message("cleric", capitalize(player_obj->query_real_name())
                       + " has left the guild. Current values are:\n"
                       + old_values, EVENTS_LOG);
    // Reset variables that no longer apply (in case they rejoin)
    set_carved_value(player, 0);
    set_primary_element(player_obj, 0);
    set_practice_level(player, 0);
    set_ew_council(player, 0);
    set_ec_council(player, 0);
    set_can_join_worshippers(player, 0);
    set_can_do_wor_task_one(player, 0);
    set_can_do_wor_task_two(player, 0);
    set_can_do_wor_task_three(player, 0);
    set_can_do_wor_task_four(player, 0);
    set_can_do_ec_task_five(player, 0);
    set_can_do_ec_task_six(player, 0);
    set_starting_exp(player, 0);
    set_starting_date(player, 0);
    set_ew_leader(player, 0);
    set_punish_train_banned(player, 0);
    set_punish_spell_banned(player, 0);
    set_punish_temple_banned(player, 0);
    set_punish_resource_banned(player, 0);
    set_player_conduit_earned(player, 0);
    set_player_conduit_spent(player, 0);
    set_created_own_title(player, 0);
    set_title_created(player, 0);
    set_child_cleric(player, 0);
    set_master_cleric(player, 0);
    set_elder_cleric(player, 0);
    set_full_master(player, 0);
    set_ec_leader(player, 0);
    set_conservator(player, 0);
    set_luminary(player, 0);
    set_illuminati(player, 0);
    set_emissary(player, 0);
    set_cultivator(player, 0);
    set_liberator(player, 0);
    set_player_property(player, "syndyasmos_partners", 0);
    set_player_property(player, "teleport_locations", 0);
    set_player_property(player, "current_syndyasmos_partner", 0);
    return 1; 
}


/*
 * Function:    leave_occ_guild
 * Description: Function to remove someone from the Clerics guild.
 */
public int 
leave_occ_guild(mixed player) 
{ 
    string id = get_id(player);

    object player_obj = find_player(id);
    if (!objectp(player_obj))
    {
        // We simply set the variable so that they will get kicked out
        // the next time they log in.
        remove_cleric(player);
        return 1;
    }

    player_obj->remove_guild_occ();
    player_obj->remove_guild_lay();
    if (player_obj->query_guild_name_race() == GUILD_EC_NAME)
    {
        player_obj->remove_guild_race();
        player_obj->clear_guild_stat(SS_RACE);
        player_obj->setup_skill_decay();
        player_obj->set_guild_pref(SS_RACE, 0);
        player_obj->remove_cmdsoul(EC_RACE_SOUL);
        player_obj->update_hooks();
    }

    int old_occ_guild_stat = player_obj->query_stat(SS_OCCUP);
    int old_lay_guild_stat = player_obj->query_stat(SS_LAYMAN);
    // Clear guild stat, remove guild learn, and begin skill decay
    player_obj->clear_guild_stat(SS_OCCUP);
    player_obj->clear_guild_stat(SS_LAYMAN); 
    player_obj->setup_skill_decay(); 
    player_obj->set_guild_pref(SS_OCCUP, 0);
    player_obj->set_guild_pref(SS_LAYMAN, 0); 
    present("_elemental_guild_wand", player_obj)->remove_object();
    present("_elemental_guild_dagger", player_obj)->remove_object();
    present("_elemental_guild_chalice", player_obj)->remove_object();
    present("_elemental_guild_pentacle", player_obj)->remove_object();
    present("_elemental_guild_mandala", player_obj)->remove_object();
    present("_echosen_", player_obj)->remove_object();

    // Reset the start location of the person leaving the guild
    if (wildmatch(ELEMENTALIST_TEMPLE + "*", 
    	player_obj->query_default_start_location()))
    {
        player_obj->set_default_start_location(player_obj->query_def_start());
    }

    // Remove the command soul
    player_obj->remove_cmdsoul(EC_SOUL);
    player_obj->remove_cmdsoul(EC_LAY_SOUL);
    player_obj->update_hooks();
    
    // Update the Guild Manager
    remove_cleric(player);

    // Log all the existing values in case we need to restore them
    string old_values = "Guild Stat: " + old_occ_guild_stat + "\n"
        + "Carved Value: " + query_carved_value(player) + "\n"
        + "Primary Element: " + query_primary_element(player) + "\n"
        + "Practice Level: " + query_practice_level(player) + ".\n";
    send_debug_message("cleric", capitalize(player_obj->query_real_name())
                       + " has left the guild. Current values are:\n"
                       + old_values, EVENTS_LOG);
    // Reset variables that no longer apply (in case they rejoin)
    set_carved_value(player, 0);
    set_primary_element(player_obj, 0);
    set_practice_level(player, 0);
    set_ew_council(player, 0);
    set_ec_council(player, 0);
    set_can_join_worshippers(player, 0);
    set_can_do_wor_task_one(player, 0);
    set_can_do_wor_task_two(player, 0);
    set_can_do_wor_task_three(player, 0);
    set_can_do_wor_task_four(player, 0);
    set_can_do_ec_task_five(player, 0);
    set_can_do_ec_task_six(player, 0);
    set_starting_exp(player, 0);
    set_starting_date(player, 0);
    set_ew_leader(player, 0);
    set_punish_train_banned(player, 0);
    set_punish_spell_banned(player, 0);
    set_punish_temple_banned(player, 0);
    set_punish_resource_banned(player, 0);
    set_player_conduit_earned(player, 0);
    set_player_conduit_spent(player, 0);
    set_created_own_title(player, 0);
    set_title_created(player, 0);
    set_child_cleric(player, 0);
    set_master_cleric(player, 0);
    set_elder_cleric(player, 0);
    set_full_master(player, 0);
    set_ec_leader(player, 0);
    set_conservator(player, 0);
    set_luminary(player, 0);
    set_illuminati(player, 0);
    set_emissary(player, 0);
    set_cultivator(player, 0);
    set_liberator(player, 0);
    set_player_property(player, "syndyasmos_partners", 0);
    set_player_property(player, "teleport_locations", 0);
    set_player_property(player, "current_syndyasmos_partner", 0);
    set_alarm(2.0, 0.0, &betray1(player_obj));
    return 1; 
}

/*
 * Function:    leave_race_guild
 * Description: Function to remove someone from the Clerics racial guild.
 */
public int 
leave_race_guild(mixed player) 
{ 
    string id = get_id(player);

    object player_obj = find_player(id);
    if (!objectp(player_obj))
    {
        // We simply set the variable so that they will get kicked out
        // the next time they log in.
        remove_racial(player);
        return 1;
    }

    player_obj->remove_guild_race();

    int old_race_guild_stat = player_obj->query_stat(SS_RACE);
    // Clear guild stat, remove guild learn, and begin skill decay
    player_obj->clear_guild_stat(SS_RACE); 
    player_obj->setup_skill_decay(); 
    player_obj->set_guild_pref(SS_RACE, 0); 

    // Remove the command soul
    player_obj->remove_cmdsoul(EC_RACE_SOUL);
    player_obj->update_hooks();
    
    // Update the Guild Manager
    remove_racial(player);

    // Log all the existing values in case we need to restore them
    string old_values = "Guild Stat: " + old_race_guild_stat + "\n"
        + "Carved Value: " + query_carved_value(player) + "\n"
        + "Primary Element: " + query_primary_element(player) + "\n"
        + "Practice Level: " + query_practice_level(player) + ".\n";
    send_debug_message("cleric", capitalize(player_obj->query_real_name())
                       + " has left the racial guild. Current values are:\n"
                       + old_values, EVENTS_LOG);
    // Reset variables that no longer apply (in case they rejoin)
    set_racial_spirit_surname(player, 0);
    set_racial_chosen_surname(player, 0);
    set_racial_hide_title(player, 0);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + 
        capitalize(player->query_real_name()) +
        " has left the Elemental Racial guild.\n");

    return 1; 
}

/*
 * Function:    leave_guild_expel
 * Description: Function to remove someone from the Worshippers guild
 *              when they have been expelled. Causes death.
 */
public int 
leave_guild_expel(mixed player) 
{ 
    string id = get_id(player);

    object player_obj = find_player(id);
    if (!objectp(player_obj))
    {
        // We simply set the variable so that they will get kicked out
        // the next time they log in.
        remove_worshipper(player);
        return 1;
    }

    player_obj->remove_guild_lay();

    int old_layman_guild_stat = player_obj->query_stat(SS_LAYMAN);
    // Clear guild stat, remove guild learn, and begin skill decay
    player_obj->clear_guild_stat(SS_LAYMAN); 
    player_obj->setup_skill_decay(); 
    player_obj->set_guild_pref(SS_LAYMAN, 0); 

    // Reset the start location of the person leaving the guild
    if (wildmatch(ELEMENTALIST_TEMPLE + "*", 
    	player_obj->query_default_start_location()))
    {
        player_obj->set_default_start_location(player_obj->query_def_start());
    }

    // Remove the command soul
    player_obj->remove_cmdsoul(EW_SOUL);
    player_obj->remove_cmdsoul(ES_SOUL);
    player_obj->update_hooks();
    
    // Update the Guild Manager
    remove_worshipper(player);
    remove_seeker(player);

    // Log all the existing values in case we need to restore them
    string old_values = "Guild Stat: " + old_layman_guild_stat + "\n"
        + "Carved Value: " + query_carved_value(player) + "\n"
        + "Primary Element: " + query_primary_element(player) + "\n"
        + "Practice Level: " + query_practice_level(player) + ".\n";
    send_debug_message("worshipper", capitalize(player_obj->query_real_name())
                       + " has left the guild. Current values are:\n"
                       + old_values, EVENTS_LOG);
    // Reset variables that no longer apply (in case they rejoin)
    set_carved_value(player, 0);
    set_primary_element(player_obj, 0);
    set_practice_level(player, 0);
    set_ew_council(player, 0);
    set_can_join_worshippers(player, 0);
    set_can_do_wor_task_one(player, 0);
    set_can_do_wor_task_two(player, 0);
    set_can_do_wor_task_three(player, 0);
    set_can_do_wor_task_four(player, 0);
    set_can_do_ec_task_five(player, 0);
    set_can_do_ec_task_six(player, 0);
    set_starting_exp(player, 0);
    set_starting_date(player, 0);
    set_ew_leader(player, 0);
    set_punish_train_banned(player, 0);
    set_punish_spell_banned(player, 0);
    set_punish_temple_banned(player, 0);
    set_punish_resource_banned(player, 0);
    set_player_conduit_earned(player, 0);
    set_player_conduit_spent(player, 0);
    set_created_own_title(player, 0);
    set_title_created(player, 0);
    set_alarm(2.0, 0.0, &betray1(player_obj));

    return 1; 
}

/*
 * Function:    betray1
 * Description: Function to kill someone who's been expelled.
 */
public void
betray1(object player)
{
    setuid();
    seteuid(getuid());

    tell_object(player, "Your blood begins to boil under your skin.\n"+
                "You hear a demonic laughter filling the air around you.\n");
                              
    tell_room(environment(player), capitalize(player->query_pronoun()) +
              " is surrounded totally by "+
              "darkness.\nThe ground shakes massively.\n", player);
    tell_object(player,"A voice echoes in your mind: You have betrayed us and "+
            "shall now pay the ultimate price!\n"+
            "The last thing you feel is your arms and legs literally exploding "+
            "from the pressure of your boiling blood.\n");
          
	tell_room(environment(player),"Suddenly, all is back "+
          "to normal, except where " + QTNAME(player) + " was standing is now a "+
          "smouldering pile of remains.\n", player);
	if (!player->query_prop(LIVE_I_NO_CORPSE))
	{
    	player->add_prop(LIVE_I_NO_CORPSE, 1);
	}
	string enemy_race = player->query_race_name();
	player->heal_hp(-player->query_max_hp());
  	player->do_die(this_object());
    object piece = clone_object(DEATH_OBJECT);
    piece->set_race(enemy_race);
    piece->move(this_object(), 1);

    object * listeners = query_awake_clerics() + query_awake_worshippers();
    listeners->catch_tell(LEFT(player)[random(4)]);
}

/*
 * Function:    leave_guild
 * Description: Function to remove someone from the Worshippers guild
 *              when they've been discharged. No death.
 */
public int 
leave_guild(mixed player) 
{ 
    string id = get_id(player);

    object player_obj = find_player(id);
    if (!objectp(player_obj))
    {
        // We simply set the variable so that they will get kicked out
        // the next time they log in.
        remove_worshipper(player);
        return 1;
    }

    player_obj->remove_guild_lay();

    int old_layman_guild_stat = player_obj->query_stat(SS_LAYMAN);
    // Clear guild stat, remove guild learn, and begin skill decay
    player_obj->clear_guild_stat(SS_LAYMAN); 
    player_obj->setup_skill_decay(); 
    player_obj->set_guild_pref(SS_LAYMAN, 0); 

    // Reset the start location of the person leaving the guild
    if (wildmatch(ELEMENTALIST_TEMPLE + "*", 
    	player_obj->query_default_start_location()))
    {
        player_obj->set_default_start_location(player_obj->query_def_start());
    }

    // Remove the command soul
    player_obj->remove_cmdsoul(EW_SOUL);
    player_obj->remove_cmdsoul(ES_SOUL);
    player_obj->update_hooks();
    
    // Update the Guild Manager
    remove_worshipper(player);
    remove_seeker(player);

    // Log all the existing values in case we need to restore them
    string old_values = "Guild Stat: " + old_layman_guild_stat + "\n"
        + "Carved Value: " + query_carved_value(player) + "\n"
        + "Primary Element: " + query_primary_element(player) + "\n"
        + "Practice Level: " + query_practice_level(player) + ".\n";
    send_debug_message("worshipper", capitalize(player_obj->query_real_name())
                       + " has left the guild. Current values are:\n"
                       + old_values, EVENTS_LOG);
    // Reset variables that no longer apply (in case they rejoin)
    set_carved_value(player, 0);
    set_primary_element(player_obj, 0);
    set_practice_level(player, 0);
    set_ew_council(player, 0);
    set_can_join_worshippers(player, 0);
    set_can_do_wor_task_one(player, 0);
    set_can_do_wor_task_two(player, 0);
    set_can_do_wor_task_three(player, 0);
    set_can_do_wor_task_four(player, 0);
    set_can_do_ec_task_five(player, 0);
    set_can_do_ec_task_six(player, 0);
    set_starting_exp(player, 0);
    set_starting_date(player, 0);
    set_ew_leader(player, 0);
    set_punish_train_banned(player, 0);
    set_punish_spell_banned(player, 0);
    set_punish_temple_banned(player, 0);
    set_punish_resource_banned(player, 0);
    set_player_conduit_earned(player, 0);
    set_player_conduit_spent(player, 0);
    set_created_own_title(player, 0);
    set_title_created(player, 0);

    return 1; 
}


/*
 * Function:    leave_seekers_guild
 * Description: Function to remove someone from the seekers guild.
 */
public int 
leave_seekers_guild(mixed player) 
{ 
    string id = get_id(player);

    object player_obj = find_player(id);
    if (!objectp(player_obj))
    {
        // We simply set the variable so that they will get kicked out
        // the next time they log in.
        remove_seeker(player);
        return 1;
    }

    player_obj->remove_guild_lay();

    int old_layman_guild_stat = player_obj->query_stat(SS_LAYMAN);
    // Clear guild stat, remove guild learn, and begin skill decay
    player_obj->clear_guild_stat(SS_LAYMAN); 
    player_obj->setup_skill_decay(); 
    player_obj->set_guild_pref(SS_LAYMAN, 0); 

    // Reset the start location of the person leaving the guild
    if (wildmatch(ELEMENTALIST_TEMPLE + "*", 
    	player_obj->query_default_start_location()))
    {
        player_obj->set_default_start_location(player_obj->query_def_start());
    }

    // Remove the command soul
    player_obj->remove_cmdsoul(ES_SOUL);
    player_obj->update_hooks();
    
    // Update the Guild Manager
    remove_seeker(player);

    // Log all the existing values in case we need to restore them
    string old_values = "Guild Stat: " + old_layman_guild_stat + "\n"
        + "Carved Value: " + query_carved_value(player) + "\n"
        + "Primary Element: " + query_primary_element(player) + "\n"
        + "Practice Level: " + query_practice_level(player) + ".\n";
    send_debug_message("seeker", capitalize(player_obj->query_real_name())
                       + " has left the guild. Current values are:\n"
                       + old_values, EVENTS_LOG);
    // Reset variables that no longer apply (in case they rejoin)
    set_carved_value(player, 0);
    set_primary_element(player_obj, 0);
    set_practice_level(player, 0);
    set_ew_council(player, 0);
    set_can_join_worshippers(player, 0);
    set_can_do_wor_task_one(player, 0);
    set_can_do_wor_task_two(player, 0);
    set_can_do_wor_task_three(player, 0);
    set_can_do_wor_task_four(player, 0);
    set_can_do_ec_task_five(player, 0);
    set_can_do_ec_task_six(player, 0);
    set_starting_exp(player, 0);
    set_starting_date(player, 0);
    set_punish_train_banned(player, 0);
    set_punish_spell_banned(player, 0);
    set_punish_temple_banned(player, 0);
    set_punish_resource_banned(player, 0);
    set_player_conduit_earned(player, 0);
    set_player_conduit_spent(player, 0);
    set_created_own_title(player, 0);
    set_title_created(player, 0);

    return 1; 
}

/*
 * Function:    convert_occ_guild
 * Description: Function to add someone to the Cleric occupational guild
 *              that was in the Spirit Circle guild
 */
public int 
convert_occ_guild(mixed player) 
{ 
    string id = get_id(player);

    object player_obj = find_player(id);
    if (!objectp(player_obj))
    {
        return 0;
    }
    
    // Remove the old guild    
    player_obj->remove_guild_lay();
    player_obj->remove_cmdsoul("/d/Calia/guilds/scop/specials/spiritlaysoul");
    player_obj->remove_guild_occ();
    player_obj->remove_cmdsoul("/d/Calia/guilds/scop/specials/spiritsoul");
    player_obj->update_hooks();
    
    // Add the new guild shadows	
    object guild_occ_shadow = clone_object(EC_OCC_SHADOW);
    int occ_return_code = guild_occ_shadow->shadow_me(player_obj, 
        GUILD_EC_TYPE, GUILD_STYLE, GUILD_EC_NAME, "");
    if (occ_return_code != 1)
    {
        player_obj->catch_tell("For some unknown reason you cannot join (occ "+
        occ_return_code+"). Please contact the Guildmaster.\n");
        guild_occ_shadow->remove_shadow();
        return 0;
    }
    
    object guild_lay_shadow = clone_object(EC_LAY_SHADOW);
    int lay_return_code = guild_lay_shadow->shadow_me(player_obj, "layman", 
        GUILD_STYLE, GUILD_EC_NAME, "");
    if (lay_return_code != 1)
    {
        player_obj->catch_tell("For some unknown reason you cannot join (lay "+
        lay_return_code+"). Please contact the Guildmaster.\n");
        guild_lay_shadow->remove_shadow();
        return 0;
    }

    // Don't clear guild stat, remove guild learn, and begin skill decay  
    player_obj->setup_skill_decay(); 
    player_obj->set_guild_pref(SS_OCCUP, GUILD_EC_OCC_TAX);
    player_obj->set_guild_pref(SS_LAYMAN, GUILD_EC_LAY_TAX);

    // Remove the command soul
    player_obj->remove_cmdsoul(EC_SOUL);
    player_obj->remove_cmdsoul(EC_LAY_SOUL);
    player_obj->update_hooks();
    
    // Update the Guild Manager
    add_cleric(player);
    set_carved_value(player, 0);
    set_primary_element(player_obj, 0);
    set_ew_council(player, 0);
    set_ec_council(player, 0);
    set_can_join_worshippers(player, 0);
    set_punish_train_banned(player, 0);
    set_punish_spell_banned(player, 0);
    set_punish_temple_banned(player, 0);
    set_punish_resource_banned(player, 0);
    set_guild_discharged(player, 0);
    set_guild_expelled(player, 0);
    set_guild_betrayed(player, 0);
    set_created_own_title(player, 0);
    set_title_created(player, 0);
    object chosen_object = present("_echosen_",player_obj);
    if (chosen_object)
    	chosen_object->remove_object();

    set_starting_date(player, time());

    return 1; 
}

/*
 * Function:    join_occ_guild
 * Description: Function to add someone to the Cleric occupational guild.
 */
public int 
join_occ_guild(mixed player) 
{ 
    string id = get_id(player);

    object player_obj = find_player(id);
    if (!objectp(player_obj))
    {
        return 0;
    }
    
    if (IS_SEEKER(player))
    {
    	leave_seekers_guild(player);
    }
    
    if (IS_WORSHIPPER(player))
    {
        leave_guild(player);
    }
    	
    object guild_occ_shadow = clone_object(EC_OCC_SHADOW);
    int occ_return_code = guild_occ_shadow->shadow_me(player_obj, 
        GUILD_EC_TYPE, GUILD_STYLE, GUILD_EC_NAME, "");
    if (occ_return_code != 1)
    {
        player_obj->catch_tell("For some unknown reason you cannot join (occ "+
        occ_return_code+"). Please contact the Guildmaster.\n");
        guild_occ_shadow->remove_shadow();
        return 0;
    }
    
    object guild_lay_shadow = clone_object(EC_LAY_SHADOW);
    int lay_return_code = guild_lay_shadow->shadow_me(player_obj, "layman", 
        GUILD_STYLE, GUILD_EC_NAME, "");
    if (lay_return_code != 1)
    {
        player_obj->catch_tell("For some unknown reason you cannot join (lay "+
        lay_return_code+"). Please contact the Guildmaster.\n");
        guild_lay_shadow->remove_shadow();
        return 0;
    }

    // Clear guild stat, remove guild learn, and begin skill decay
    player_obj->clear_guild_stat(SS_OCCUP); 
    player_obj->clear_guild_stat(SS_LAYMAN);  
    player_obj->setup_skill_decay(); 
    player_obj->set_guild_pref(SS_OCCUP, GUILD_EC_OCC_TAX);
    player_obj->set_guild_pref(SS_LAYMAN, GUILD_EC_LAY_TAX);

    // Remove the command soul
    player_obj->remove_cmdsoul(EC_SOUL);
    player_obj->remove_cmdsoul(EC_LAY_SOUL);
    player_obj->update_hooks();
    
    // Update the Guild Manager
    add_cleric(player);
    set_child_cleric(player, 1);
    set_carved_value(player, 0);
    set_primary_element(player_obj, 0);
    set_practice_level(player, 0);
    set_ew_council(player, 0);
    set_ec_council(player, 0);
    set_can_join_worshippers(player, 0);
    set_can_join_clerics(player, 0);
    set_punish_train_banned(player, 0);
    set_punish_spell_banned(player, 0);
    set_punish_temple_banned(player, 0);
    set_punish_resource_banned(player, 0);
    set_guild_discharged(player, 0);
    set_guild_expelled(player, 0);
    set_guild_betrayed(player, 0);
    set_created_own_title(player, 0);
    set_title_created(player, 0);
    object chosen_object = present("_echosen_",player_obj);
    if (chosen_object)
    	chosen_object->remove_object();

    set_starting_date(player, time());

    return 1; 
}

/*
 * Function:    join_racial_guild
 * Description: Function to add someone to the Cleric racial guild.
 */
public int 
join_racial_guild(mixed player, string spirit_surname, string chosen_surname) 
{ 
    string id = get_id(player);

    object player_obj = find_player(id);
    if (!objectp(player_obj))
    {
        return 0;
    }
    	
	object guild_race_shadow = clone_object(EC_RACE_SHADOW);
	int race_return_code = guild_race_shadow->shadow_me(player_obj, "race", 
	    GUILD_STYLE, GUILD_EC_NAME, "");
    if (race_return_code != 1)
    {
        player_obj->catch_tell("For some unknown reason you cannot join (race "+
        race_return_code+"). Please contact the Guildmaster.\n");
        guild_race_shadow->remove_shadow();
        return 0;
    }

    // Clear guild stat, remove guild learn, and begin skill decay
    player_obj->clear_guild_stat(SS_RACE); 
    player_obj->setup_skill_decay(); 
    player_obj->set_guild_pref(SS_RACE, GUILD_EC_RACE_TAX); 

    // Remove the command soul
    player_obj->remove_cmdsoul(EC_RACE_SOUL);
    player_obj->update_hooks();
    
    // Update the Guild Manager
    add_racial(player);
    set_racial_spirit_surname(player, spirit_surname);
    set_racial_chosen_surname(player, chosen_surname);
    set_racial_hide_title(player, 0);

    COUNCIL_LOG_BOOK->update_log_book(my_time() + 
        capitalize(player->query_real_name()) +
        " has joined the Elemental Racial guild.\n");
    return 1; 
}

/*
 * Function:    join_guild
 * Description: Function to add someone to the Worshippers guild.
 */
public int 
join_guild(mixed player) 
{ 
    string id = get_id(player);

    object player_obj = find_player(id);
    if (!objectp(player_obj))
    {
        return 0;
    }
    
    leave_seekers_guild(player);

    object guild_shadow = clone_object(EW_SHADOW);
    if (guild_shadow->shadow_me(player_obj, GUILD_EW_TYPE, GUILD_STYLE, 
    	GUILD_EW_NAME, "") != 1)
    {
        player_obj->catch_tell("For some unknown reason you cannot join. "+
            "Please contact the Guildmaster.\n");
        shadow->remove_shadow();
        return 0;
    }

    // Clear guild stat, remove guild learn, and begin skill decay
    player_obj->clear_guild_stat(SS_LAYMAN); 
    player_obj->setup_skill_decay(); 
    player_obj->set_guild_pref(SS_LAYMAN, GUILD_EW_TAX); 

    // Remove the command soul
    player_obj->remove_cmdsoul(EW_SOUL);
    player_obj->update_hooks();
    
    // Update the Guild Manager
    add_worshipper(player);
    set_carved_value(player, 0);
    set_primary_element(player_obj, 0);
    set_practice_level(player, 0);
    set_ew_council(player, 0);
    set_ec_council(player, 0);
    set_can_join_worshippers(player, 0);
    set_can_do_wor_task_one(player, 0);
    set_can_do_wor_task_two(player, 0);
    set_can_do_wor_task_three(player, 0);
    set_can_do_wor_task_four(player, 0);
    /*
    if (!query_starting_exp(player))
    {
    	set_starting_exp(player, player_obj->query_exp());
    }
    */
    set_starting_date(player, time());
    set_punish_train_banned(player, 0);
    set_punish_spell_banned(player, 0);
    set_punish_temple_banned(player, 0);
    set_punish_resource_banned(player, 0);
    set_guild_discharged(player, 0);
    set_guild_expelled(player, 0);
    set_guild_betrayed(player, 0);
    set_created_own_title(player, 0);
    set_title_created(player, 0);

    return 1; 
}

/*
 * Function:    join_seekers_guild
 * Description: Function to add someone to the seekers guild.
 */
public int 
join_seekers_guild(mixed player) 
{ 
    string id = get_id(player);

    object player_obj = find_player(id);
    if (!objectp(player_obj))
    {
        return 0;
    }

    object guild_shadow = clone_object(ES_SHADOW);
    int shadow_result = guild_shadow->shadow_me(player_obj, GUILD_ES_TYPE, 
        GUILD_STYLE, GUILD_ES_NAME, "");
    if (shadow_result != 1)
    {
        player_obj->catch_tell("For some unknown reason you cannot join. "+
            "Please contact the Guildmaster. " +"(" + shadow_result + ")\n");
        shadow->remove_shadow();
        return 0;
    }

    // Clear guild stat, remove guild learn, and begin skill decay
    player_obj->clear_guild_stat(SS_LAYMAN); 
    player_obj->setup_skill_decay(); 
    player_obj->set_guild_pref(SS_LAYMAN, GUILD_EW_TAX); 

    // Remove the command soul
    player_obj->remove_cmdsoul(ES_SOUL);
    player_obj->set_skill(SS_PATRON_ELEMENTAL,SEEKER_FLAG);
    player_obj->update_hooks();
    
    // Update the Guild Manager
    add_seeker(player);
    set_primary_element(player_obj, 0);
    set_practice_level(player, 0);
    set_ew_council(player, 0);
    set_ec_council(player, 0);
    set_can_join_worshippers(player, 0);
    set_can_do_wor_task_one(player, 0);
    set_can_do_wor_task_two(player, 0);
    set_can_do_wor_task_three(player, 0);
    set_can_do_wor_task_four(player, 0);
    /*
    set_starting_exp(player, player_obj->query_exp());
    */
    set_punish_train_banned(player, 0);
    set_punish_spell_banned(player, 0);
    set_punish_temple_banned(player, 0);
    set_punish_resource_banned(player, 0);
    set_guild_discharged(player, 0);
    set_guild_expelled(player, 0);
    set_guild_betrayed(player, 0);
    set_created_own_title(player, 0);
    set_title_created(player, 0);

    return 1; 
}

public void
set_can_join_worshippers(mixed player, int value)
{
    set_player_property(player, "can_join_worshippers", value);
}

public void
set_can_join_clerics(mixed player, int value)
{
    set_player_property(player, "can_join_clerics", value);
}

public void
set_can_do_wor_task_one(mixed player, int value)
{
    set_player_property(player, "can_do_wor_task_one", value);
}

public void
set_can_do_wor_task_two(mixed player, int value)
{
    set_player_property(player, "can_do_wor_task_two", value);
}

public void
set_can_do_wor_task_three(mixed player, int value)
{
    set_player_property(player, "can_do_wor_task_three", value);
}

public void
set_can_do_wor_task_four(mixed player, int value)
{
    set_player_property(player, "can_do_wor_task_four", value);
}

public void
set_can_do_ec_task_five(mixed player, int value)
{
    set_player_property(player, "can_do_ec_task_five", value);
}

public void
set_can_do_ec_task_six(mixed player, int value)
{
    set_player_property(player, "can_do_ec_task_six", value);
}

public void
set_task_two_answer_one(mixed player, mixed value)
{
	set_player_property(player, "task_two_answer_one", value);
}

public void
set_task_two_answer_two(mixed player, mixed value)
{
	set_player_property(player, "task_two_answer_two", value);
}

public void
set_task_two_answer_three(mixed player, mixed value)
{
	set_player_property(player, "task_two_answer_three", value);
}

public void
set_task_two_answer_four(mixed player, mixed value)
{
	set_player_property(player, "task_two_answer_four", value);
}

public void
set_task_two_answer_five(mixed player, mixed value)
{
	set_player_property(player, "task_two_answer_five", value);
}

public void
set_task_two_answer_six(mixed player, mixed value)
{
	set_player_property(player, "task_two_answer_six", value);
}

public void
set_task_two_answer_seven(mixed player, mixed value)
{
	set_player_property(player, "task_two_answer_seven", value);
}

public void
set_task_two_answer_eight(mixed player, mixed value)
{
	set_player_property(player, "task_two_answer_eight", value);
}

public void
set_task_three_answer_one(mixed player, mixed value)
{
	set_player_property(player, "task_three_answer_one", value);
}

public void
set_task_three_answer_two(mixed player, mixed value)
{
	set_player_property(player, "task_three_answer_two", value);
}

public void
set_task_six_answer_one(mixed player, mixed value)
{
	set_player_property(player, "task_six_answer_one", value);
}

public void
set_task_six_answer_two(mixed player, mixed value)
{
	set_player_property(player, "task_six_answer_two", value);
}

public void
set_task_six_answer_three(mixed player, mixed value)
{
	set_player_property(player, "task_six_answer_three", value);
}

public void
set_task_six_answer_four(mixed player, mixed value)
{
	set_player_property(player, "task_six_answer_four", value);
}

public void
set_task_six_answer_five(mixed player, mixed value)
{
	set_player_property(player, "task_six_answer_five", value);
}

public void
set_task_six_answer_six(mixed player, mixed value)
{
	set_player_property(player, "task_six_answer_six", value);
}
	
public int
query_can_join_worshippers(mixed player)
{
    return query_player_property(player, "can_join_worshippers");
}

public int
query_can_join_clerics(mixed player)
{
    return query_player_property(player, "can_join_clerics");
}

public int
query_can_do_wor_task_one(mixed player)
{
    return query_player_property(player, "can_do_wor_task_one");
}

public int
query_can_do_wor_task_two(mixed player)
{
    return query_player_property(player, "can_do_wor_task_two");
}

public int
query_can_do_wor_task_three(mixed player)
{
    return query_player_property(player, "can_do_wor_task_three");
}

public int
query_can_do_wor_task_four(mixed player)
{
    return query_player_property(player, "can_do_wor_task_four");
}

public int
query_can_do_ec_task_five(mixed player)
{
    return query_player_property(player, "can_do_ec_task_five");
}

public int
query_can_do_ec_task_six(mixed player)
{
    return query_player_property(player, "can_do_ec_task_six");
}

public mixed
query_task_two_answer_one(mixed player)
{
	return query_player_property(player, "task_two_answer_one");
}

public mixed
query_task_two_answer_two(mixed player)
{
	return query_player_property(player, "task_two_answer_two");
}

public mixed
query_task_two_answer_three(mixed player)
{
	return query_player_property(player, "task_two_answer_three");
}

public mixed
query_task_two_answer_four(mixed player)
{
	return query_player_property(player, "task_two_answer_four");
}

public mixed
query_task_two_answer_five(mixed player)
{
	return query_player_property(player, "task_two_answer_five");
}

public mixed
query_task_two_answer_six(mixed player)
{
	return query_player_property(player, "task_two_answer_six");
}

public mixed
query_task_two_answer_seven(mixed player)
{
	return query_player_property(player, "task_two_answer_seven");
}

public mixed
query_task_two_answer_eight(mixed player)
{
	return query_player_property(player, "task_two_answer_eight");
}

public mixed
query_task_three_answer_one(mixed player)
{
	return query_player_property(player, "task_three_answer_one");
}

public mixed
query_task_three_answer_two(mixed player)
{
	return query_player_property(player, "task_three_answer_two");
}

public mixed
query_task_six_answer_one(mixed player)
{
	return query_player_property(player, "task_six_answer_one");
}

public mixed
query_task_six_answer_two(mixed player)
{
	return query_player_property(player, "task_six_answer_two");
}

public mixed
query_task_six_answer_three(mixed player)
{
	return query_player_property(player, "task_six_answer_three");
}

public mixed
query_task_six_answer_four(mixed player)
{
	return query_player_property(player, "task_six_answer_four");
}

public mixed
query_task_six_answer_five(mixed player)
{
	return query_player_property(player, "task_six_answer_five");
}

public mixed
query_task_six_answer_six(mixed player)
{
	return query_player_property(player, "task_six_answer_six");
}

// Teleport location functions

public mapping
query_teleport_locations(object player)
{ 
    mixed locations = query_player_property(player, "teleport_locations");
    
    if (!mappingp(locations))
        locations = ([ ]);
    
    return locations;
}

public void
add_teleport_locations(object player, string name, string loc)
{
    mapping locations = query_teleport_locations(player);
    
    if (!m_sizeof(locations) || !member_array(name, m_indexes(locations)) > -1)
        locations += ([ name : loc ]);
    
    set_player_property(player, "teleport_locations", locations);
}

public void 
remove_teleport_locations(object player, string name)
{
    mapping locations = query_teleport_locations(player);
    
    if (m_sizeof(locations) && member_array(name, m_indexes(locations)) > -1)
        m_delkey(locations, name);
    
    set_player_property(player, "teleport_locations", locations);
}

// Syndyasmos Functions

public mapping
query_syndyasmos_partners(object player)
{ 
    mixed partners = query_player_property(player, "syndyasmos_partners");
    
    if (!mappingp(partners))
        partners = ([ ]);
    
    return partners;
}

public void
add_syndyasmos_partner(object player, string name)
{
    mapping partners = query_syndyasmos_partners(player);
    
    if (!m_sizeof(partners) || !member_array(name, m_indexes(partners)) > -1)
        partners += ([ name : "1" ]);
    
    set_player_property(player, "syndyasmos_partners", partners);
}

public void 
remove_syndyasmos_partner(object player, string name)
{
    mapping partners = query_syndyasmos_partners(player);
    
    if (m_sizeof(partners) && member_array(name, m_indexes(partners)) > -1)
        m_delkey(partners, name);
    
    set_player_property(player, "syndyasmos_partners", partners);
}

public void
set_current_syndyasmos_partner(mixed player, mixed value)
{
	set_player_property(player, "current_syndyasmos_partner", value);
}
	
public mixed
query_current_syndyasmos_partner(mixed player)
{
    return query_player_property(player, "current_syndyasmos_partner");
}

// Scenario Functions

public void
set_has_completed_scenarios(mixed player, int value)
{
	set_player_property(player, "has_completed_scenarios", value);
}
	
public int
query_has_completed_scenarios(mixed player)
{
    return query_player_property(player, "has_completed_scenarios");
}

public void
set_emessenger_option(mixed player, string str)
{
	set_player_property(player, "emessenger_option", str);
}

public string
query_emessenger_option(mixed player)
{
	return query_player_property(player, "emessenger_option");
}

public void
set_emount_option(mixed player, string str)
{
	set_player_property(player, "emount_option", str);
}

public string
query_emount_option(mixed player)
{
	return query_player_property(player, "emount_option");
}
