/*
 * /d/Gondor/common/guild2/death_room.c
 *
 * The room where one can join the Morgul Mages
 * - at the same time the master object of the guild
 *
 * Created: Olorin, 05-jan-1994
 *
 * Copyright (c) 1997 by Christian Markus
 *
 * Modification Log:
 * 20-Jan-1997, Olorin: General revision.
 *  8-Mar-1998, Mercade: Punishment of players not logged in.
 *
 * Feb, 8 2006 Altrus:
 * Changed the joining code to query_race_name instead of query_race
 * to allow certain masked races to join. The forbidden races are listed
 * in a changed list in the morgul_defs.h. This was to allow the presence
 * of orcs who are base-elf bodies.
 *
 * Jan 5, 2007 Toby:
 * Added support to store the rank of mages and the time it was last updated.
 * This is a helpful tool for the Nine to monitor the status of the Society.
 *
 * May 11th, 2009: Eowul
 * Made a temporary copy to log calls to this object and pass them to the 
 * new guilds control object.
 *
 * Functions available for Call here:
 *
 *    - query_mages
 *    - query_is_mage      (str)
 *    - query_morgul_level (str)
 *    - query_mage_title   (str) [Outdated]
 *    - print_mage_list          [Erronous due to query_mage_title outdate]
 *    - query_male_titles
 *    - query_female_titles
 *    - query_mage_names
 *    - query_mage_name    (str)
 *    - query_mage_rank    (str)
 */
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower.c";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <time.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

#define  MORGUL_S_SPONSOR         "_morgul_s_sponsor"
#define  MORGUL_I_DEATH_WARNING   "_morgul_i_death_warning"
#define  IDLENESS ("/d/Gondor/common/guild2/idleness")

public string query_sage_title(object mage);
int    update_mage_rank(object mage);
int    query_mage_rank(string mage);

public void incr_ISE_counter();
public int query_ISE_counter();
public void reset_ISE_counter();

/*
 *      Global variables:
 *
 * Mages       - list of names of the morgul mages.
 * Mage_Names  - index is player name, value is mage name.
 * Mage_Ranks  - index is players name, value is the numerical value of current rank  
 * Punishments - punishments of players not logged in. Index is player name.
 *               Values: ({ name of punisher, punishment, reason })
 * SulambarCharges - Remaining charges for the Sulambar spell
 *                   Values: ({ last age at recharge, number of charges remain })
 */
string *Mages = ({ });
mapping Mage_Names = ([ "olorin" : "Annatar", ]);
mapping Mage_Ranks = ([ ]);
mapping Punishments = ([ ]);
mapping SulambarCharges = ([ ]);

static public int _Idleness_System_Error_counter = 0;

/*
 * load titles into a global variable at creation: this saves cpu time!
 */
static  string *Male_Titles  = MORGUL_COMMON_MALE_TITLES,
*Female_Titles = MORGUL_COMMON_FEMALE_TITLES;

#define DEBUGT(x)            find_player("toby")->catch_msg(x + "\n");



/*
 * Function name: create_morgul_tower_room
 * Description:   room creator for tower rooms
 */
private void
create_morgul_tower_room()
{
    set_level(2);
    set_room_type("great hall");
    set_name("Morgul_Mage_Master");
    set_extra_long("The hall is devoid of decorations and furniture " +
      "except for a large black stone slab in the back of the hall. " +
      "The hall continues to the south.");

    add_floor();
    add_no_roof();
    add_walls();

    add_item(({"stone","stone slab","altar","slab"}), BSN(
        "The stone slab is about four feet high, eight feet long, and " +
        "four feet broad. It was hewn from the same rock as the stones " +
        "that make the walls and the floor. On the smooth surface are " +
        "dark brown stains. If you are a servant of the Dark Lord, you " +
        "can beg for a new robe at this altar if you have lost your " +
        "old one. If you should decide to leave the Society, you can " +
        "come here to betray its Lord Sauron."));
    add_item(({"stain","stains","blood","blood stains","brown stains",
        "dark stains"}), BSN(
        "On top of the stone slab are dark brown stains. They look " +
        "like dried blood."));
    add_item(({"hall","great hall"}), BSN(
        "Except for the altar, the hall is devoid of decorations and " +
        "furniture. The walls are also almost featureless, the seams " +
        "between the stone blocks are hardly visible. The roof is hidden " +
        "in the darkness above. The hall continues further to the south, " +
        "where a doorway is visible."));
    add_item(({"door","entrance","doorway","exit"}), BSN(
        "The doorway in the southern half of the hall is leading out " +
        "onto the staircase."));

    add_prop(ROOM_I_LIGHT,1);
/*
    add_prop( ROOM_M_NO_ATTACK,
        "The Power of the Dark Lord prevents your attack.\n" );
    add_prop( ROOM_M_NO_MAGIC_ATTACK,
        "The Power of the Dark Lord prevents your attack.\n" );
*/
    add_prop( ROOM_I_NO_CLEANUP, 1 );

    /* Allow players to use the "mlist" command even when paralyzed. */
    CMDPARSE_PARALYZE_ALLOW_CMDS( ({ "mlist" }) );
    
    ("/d/Gondor/common/guild2/idleness")->start_idling();
    return;
}

public void log_obsolete_call()
{
    log_file("mage_obsolete", sprintf("deathroom/%O called by %O/%O\nInteractive: %s\n", 
        calling_function(), calling_object(-1), calling_function(-1),
        (objectp(this_interactive()) ? this_interactive()->query_real_name() : "") ), -1);
}

public varargs int
add_mage(string newmage, string sponsor_name)
{
    log_obsolete_call();
    MORGUL_MASTER->add_player_to_guild(find_living(newmage), sponsor_name);
}

/*
 * Function name: remove_player_from_guild
 * Description:   this function is called from the shadow to
 *                remove a player from the guild
 * Argument:      player - player object
 *                reason - information for the log
 */
public void
remove_player_from_guild(object player, string reason = 0)
{
    log_obsolete_call();
    MORGUL_MASTER->remove_player_from_guild(player, reason);
}

/*
 * Function name: expel_player_from_guild
 * Description  : Function is called from the Nazgul "expel" command. It
 *                assumes that this_player() is the person who expelled,
 *                should the player not be present.
 * Arguments    : string caster - the nazgul exelling the player.
 *                string name - the name of the player to expel.
 *                string reason - the reason (with the name of the expeller).
 */
public void
expel_player_from_guild(string caster, string name, string reason)
{
    log_obsolete_call();
    MORGUL_MASTER->expel_player_from_guild(caster, name, reason);
}

/*
 * Function name: expulsion_pending
 * Description  : Returns whether the player should be expelled upon entering
 *                the realms.
 * Arguments    : string name - the name of the player to check.
 * Returns      : string - the name of the person responsible for the
 *                    expulsion, then a colon, then the official log reason.
 */
public string
expulsion_pending(string name)
{
    log_obsolete_call();
    return MORGUL_MASTER->expulsion_pending(name);
}

public string *
query_mages()
{
    log_obsolete_call();
    return MORGUL_MASTER->query_mages();
}

/*
 * Function name: query_is_mage
 * Description  : Tests whether a player is registered as mage.
 * Arguments    : string name - the name of the player to test.
 * Returns      : int - if true, the person is a mage.
 */
public int
query_is_mage(string name)
{
    log_obsolete_call();
    return MORGUL_MASTER->query_is_mage(name);
}

public int
query_morgul_level(string mage)
{
    log_obsolete_call();
    
    object  player;
    int     morgul_level,
            nlevels = sizeof(Male_Titles),
            morgul_stat;

    mage = LOW(mage);

    if (!(player = find_player(mage)))
    {
        player = SECURITY->finger_player(mage);
    }

    morgul_stat = player->query_stat(SS_OCCUP);

    if (player->query_finger_player())
    {
        player->remove_object();
    }

    if (morgul_stat > 100)
        morgul_stat = 100;

    morgul_level = ((morgul_stat * (nlevels - 1)) / 100);

    return morgul_level;
}

public string
query_mage_title(string mage)
{
    log_obsolete_call();
    
    object  player;
    int     is_finger,
    morgul_level,
    nlevels = sizeof(Male_Titles),
    morgul_stat;
    string  morgul_title;

    mage = LOW(mage);

    if (SECURITY->query_wiz_level(mage))
        return "wizard";

    is_finger = 0;
    if (!(player = find_player(mage)))
    {
        player = SECURITY->finger_player(mage);
        is_finger = 1;
    }
    if (!player)
        return "";

    morgul_stat = player->query_stat(SS_OCCUP);
    if (morgul_stat > 100)
        morgul_stat = 100;

    morgul_level = ((morgul_stat * (nlevels - 1)) / 100);

    if (player->query_gender_string() == "female")
        morgul_title = "the " + Female_Titles[morgul_level];
    morgul_title = "the " + Male_Titles[morgul_level];

    if (is_finger)
        player->remove_object();

    return morgul_title;
}

public string
query_sage_title(object mage)
{
    log_obsolete_call();
    return mage->query_morgul_level();
}

public string
print_mage_list()
{
    log_obsolete_call();
    return "This function is temporarely disabled.\n";
}

public string *
query_male_titles()
{
    log_obsolete_call();
    return Male_Titles;
}

public string *
query_female_titles()
{
    log_obsolete_call();
    return Female_Titles;
}

/*
 *      Support for mage names.
 */
public mapping
query_mage_names()
{
    log_obsolete_call();
    return MORGUL_MASTER->query_mage_names();
}

public varargs string
query_mage_name(string name)
{
    log_obsolete_call();
    return MORGUL_MASTER->query_mage_name(name);
}

/*
 * Function name: add_mage_name
 * Description:   add a mage name to the mage_names mapping
 * Arguments:     mage - the name of the mage, or an objectpointer
 *                       to the player object of the mage
 *                name - the mage name
 * Returns:       -1   - mage is not a player in the game
 *                -2   - mage is not a Morgul mage
 *                 1   - success
 *                 2   - success, but there was an old mage name
 */
public int
add_mage_name(mixed mage, string name)
{
    log_obsolete_call();
    return MORGUL_MASTER->add_mage_name(mage, name);
}

public void
remove_mage_name(string name)
{
    log_obsolete_call();
    return MORGUL_MASTER->remove_mage_name(name);
}

/*
 * Security support for the idleness system. It serves as an external
 * reference for the IS selfcheck.
 */
public void incr_ISE_counter()
{
    if (previous_object() == find_object( IDLENESS ))
    {
        _Idleness_System_Error_counter++;
    }
}

public int query_ISE_counter()
{
    return _Idleness_System_Error_counter;
}

public void reset_ISE_counter()
{
    if (previous_object() == find_object( IDLENESS ))
    {
        _Idleness_System_Error_counter = 0;
    }
}

/*
 * Function name: query_sulambar_charges
 * Description  : See how much charges the mage has left for Sulambar
 *              : This function also makes sure the value is recharged.
 * Arguments    : mage - the mage to check for
 * Returns      : a number
 */
public int query_sulambar_charges(object mage)
{
    log_obsolete_call();
    return MORGUL_MASTER->query_sulambar_charges(mage);
}

/*
 * Function name: decrease_sulambar_charge
 * Description  : Remove one of the mage's sulambar charges
 * Arguments    : mage - the object of the mage casting sulambar
 */
void decrease_sulambar_charge(object mage)
{
    log_obsolete_call();
    MORGUL_MASTER->decrease_sulambar_charge(mage);
}

/*
 * Function name: update_mage_rank
 * Description  : Store the mage's rank into the save file (morgul_mages.o)
 *                for use at the Nazguls plaque to keep track of members
 *                ranks in times of idleness.
 * Arguments    : mage - the object of the mage
 * Returns:       -1   - mage is not a player in the game
 *                -2   - mage is not a Morgul mage
 *                 1   - success
 *                 2   - success, an update occured
 */
int update_mage_rank(object mage)
{
    log_obsolete_call();
    MORGUL_MASTER->update_mage_rank(mage);
}

/*
 * Function name: query_mage_rank
 * Description  : Returns the rank of a player if it has been stored
 * Arguments    : mage - the object of the mage
 * Returns:       The rank if it is listed and the month and year
 *                the rank was written/updated into the file.
 */
string query_mage_rank(string mage_name)
{
    log_obsolete_call();
    return "Temporarely disabled";
}
