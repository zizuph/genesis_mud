/*  Imladris Master.
 *
 *  This file is used to keep track of elf killers and attackers.
 *  As well as some other neat things for the Imladris area.
 *
 *  Created by Chad Richardson a.k.a. Igneous
 *
 *  2007/07/01 Last update
 *  2011/07/19 Lavellan - Fixed goblin detect and added AA to guild list
 */
#pragma strict_types
#pragma no_clone
#pragma no_inherit

inherit "/d/Shire/lib/tell_funcs";

#include "local.h"
#include <language.h>

// Indexes for the mapping
#define CRIME  0
#define AGE    1

// How long we wait until attackers permitted back into the Valley.
// Currently set for 3 days, calculated in heartbeats. 43200=1 day.
#define FORGET_ATTACK  129600

// Global Vars
private mapping player_info = ([]);

/* Function name: save_info
 * Description:   Used to save the player_info mapping to disk
 */
void
save_info()
{
    save_map(player_info, RIVENDELL_SAVE);
}

/* Function name: restore_info
 * Description:   Used to restore the player_info from disk
 */
void
restore_info()
{
    player_info = restore_map(RIVENDELL_SAVE);
    if (!mappingp(player_info))
	player_info = ([]);
}

/* Function name: create
 * Description:   The constructor function.
 */
void
create()
{
    setuid(); seteuid(getuid());
    restore_info();
}

/* Function name: query_elf_attacker
 * Description:   Is the player a known elf attacker.
 * Arguements:    mixed player: an objectpointer to the player
 *                              or the player's name.
 * Returns:       1 if player is an elf attacker.
 *                0 if the player isn't an elf attacker.  
 */
int
query_elf_attacker(mixed player)
{
    string name;

    if (stringp(player))
	player = find_player(lower_case(player));
    if (objectp(player))
	name = player->query_real_name();

    if (!pointerp(player_info[name]))
	return 0;

    if (player_info[name][CRIME] == "attacker")
    {
	if ((player->query_age() - FORGET_ATTACK) >= player_info[name][AGE])
	{
	    // Player has served his/her time
	    player_info = m_delete(player_info, name);
	    save_info();
	    return 0;
	}
	return 1;
    } 
    return 0; 
}

/* Function name: query_elf_killer
 * Description:   Is the player a known elf killer.
 * Arguements:    mixed player: an objectpointer to the player
 *                              or the player's name.
 * Returns:       1 if player is an elf killer.
 *                0 if the player isn't an elf killer.
 */
int
query_elf_killer(mixed player)
{
    string name;

    if (stringp(player))
	name = lower_case(player);
    if (objectp(player))
	name = player->query_real_name();

    if (!pointerp(player_info[name]))
	return 0;    

    if (player_info[name][CRIME] == "killer")
	return 1;

    return 0;
}

/* Function name: query_allowed_enter_rivendell
 * Description:   Checks to see if a player is allowed to enter
 *                Imladris.
 * Agruements:    object player:  The player we are testing
 * Returns:       1 if player is allowed in rivendell
 *                0 if the player isn't allowed in
 */
int
query_allowed_enter_rivendell(object player)
{
    // First we check race
    //if (player->query_race() == "goblin")
    if (player->query_race_name() == "goblin")
	return 0;
    // Check if undead
    if (player->query_prop(LIVE_I_UNDEAD))
	return 0;
    if (player->query_guild_name_occ() == "Angmar Army")
        return 0;
    if (player->query_guild_name_lay() == "Angmar Army")
        return 0;
    if (player->query_guild_name_occ() == "Vampires of Emerald")
	return 0;
    if (player->query_guild_name_occ() == "Morgul Mages")
	return 0;
    if (player->query_guild_name_race() == "Orcs of Middle Earth")
	return 0;
    if (player->query_guild_name_occ() == "Army of Darkness")
	return 0;
    if (player->query_guild_name_occ() == "Necromancers Of Vile Darkness")
        return 0;
    if (player->query_guild_name_occ() == "Warlocks of Faerun")
        return 0;
    if (player->query_guild_name_lay() == "Warlocks of Faerun")
        return 0;


    // Check alignment 
    if (player->query_alignment() <= -150)
	return 0;
    // See if we have an elf killer here
    // We now let elf killers in
    //    if (query_elf_killer(player))
    //        return 0;

    return 1;
}

/* Function name: add_elf_attacker
 * Description:   Adds the player to the known elf attackers
 * Arguements:    object player: an objectpointer to the player
 */
void
add_elf_attacker(object player)
{
    string name;

    name = player->query_real_name();

    if (pointerp(player_info[name]))
    {
	if (player_info[name][CRIME] == "killer")
	    return;
    }

    player_info[name] = ({"attacker", player->query_age()});
    save_info();
}

/* Function name: add_elf_killer
 * Description:   Adds the player to the known elf killers
 * Arguements:    object player: an objectpointer to the player
 */
void
add_elf_killer(object player)
{
    string name;

    name = player->query_real_name();
    player_info[name] = ({"killer", player->query_age()});
    save_info();
}

void
sunrise()
{
    tell_players_in_dir(VALLEY_DIR, "Bells in the valley of "+
      "Imladris announce the beginning of a new day.\n");
}

void
sunset()
{
    tell_players_in_dir(VALLEY_DIR, "Bells in the valley of "+
      "Imladris announce the arrival of nightfall.\n");
}

void
change_hour(int hour)
{
}
