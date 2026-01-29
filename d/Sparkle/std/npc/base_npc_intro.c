/*
 * NPC Intro System
 *
 * Holds the functions for the intro system.
 *
 * Usage:
 *
 * Inherit this into the NPC.
 * call setup_npc_introduction(SAVEFILE) from inside the NPC.
 *
 * 
 * This needs to be in the NPC or NPC Base code for the introsystem
 * to actually work.
 *
 * within create_monster() {}

setup_npc_introduction("/path/to/the/savefile");
 
 * after create_monster() {}

void
init_living()
{
    ::init_living();
    init_introduced();

}

 *
 * Description:
 *
 * What it does? well saves if a monk ever introed
 * to a player and then lets the npc be always known
 * to that player forever after.
 *
 * Functions:
 *
 * - save_imaster()
 * - restore_imaster()
 * - purge_imaster()
 * - set_npc_introduction() - to setup the NPC.
 * - query_npc_introduced()
 * - add_npc_introduced()
 * - add_introduced() - to mask the introduction code.
 *
 * Sparkle Domain Code
 * Created by Lunatari (2005-12-21)
 *
 */
#pragma no_clone
#pragma strict_types

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <files.h>
#include <filter_funs.h>
#include <formulas.h>
#include <composite.h>
#include <living_desc.h>
#include <math.h>

string gMasterSave = "unconfigured_introduce_npc";
string gMasterName = "default";

/*
 * Format of the introduction mapping.
 */
mapping introductions;

/*
 * Predefined Functions.
 */
int add_npc_introduced(string name);
int query_npc_introduced();

/*
 * Function: save_introductions
 * Desc:     Saves the introduction file.
 */ 
void
save_imaster()
{
    setuid();
    seteuid(getuid());
    save_map(introductions, gMasterSave);
}

/*
 * Function: restore_introductions
 * Desc:     Restores all the introductions from file.
 */ 
void
restore_imaster()
{
    setuid();
    seteuid(getuid());

    introductions = restore_map(gMasterSave);

    if (!mappingp(introductions))
    introductions = ([ ]);

	save_imaster();
}

/*
 * Function: purge_introductions
 * Desc:     Purges all the introductions that are saved.
 */ 
void
purge_imaster()
{
   introductions = ([ ]);

   save_imaster();  
}

/*
 * Function: set_npc_introduction
 * Desc:     This sets up the NPC to log everything to a file and also
 *           adds the prop for LIVE_I_ALWAYSKNOWN.
 */
void
set_npc_introduction(string file)
{
	gMasterSave = file;
        gMasterName = this_object()->query_real_name();
}

/*
 * Function: add_introduced
 * Desc:     Called from NPC when it wants to add a player
 *           to the introduced database.
 */
int
add_npc_introduced(string name)
{
    object player;
    int    age;
    string how = "neutral";

    player = find_player(name);
    age    = player->query_age();
       
    if (!introductions[gMasterName])
	introductions[gMasterName] = ([ ]);


    if (!introductions[gMasterName][name])
        introductions[gMasterName][name] = ({ age, how, });

    save_imaster();
}

/*
 * Function: query_npc_introduced
 * Desc:     Function called from add_prop(LIVE_I_ALWAYSKNOWN, x);
 */
int
query_npc_introduced()
{
    string name;

    name = this_player()->query_real_name();

    if (!mappingp(introductions))
	  restore_imaster();

    if (!introductions[gMasterName])
        introductions[gMasterName] = ([ ]);

    if (!introductions[gMasterName][name])
        return 0;

    save_imaster();

    return 1;
}

/*
 * Function: add_introduced
 * Desc:     Public NPC/Player function that masks the function
 *           and adds the player to the database.
 */
public void
add_introduced(string name)
{
   if(!query_npc_introduced())
       command("say Greetings " + name);
   else
       command("say Well hello there " + capitalize(name) +
               ", it is a pleasure to see you again");

   add_npc_introduced(name);
   command("introduce me to " + capitalize(name));
}

/*
 * Function: init_introduced
 * Desc:     Actually adds the name to a player if it supposed to 
 *           know the npc.
 */
void
init_introduced()
{
    if(query_npc_introduced() && (gMasterName != "default"))
        this_player()->add_introduced(gMasterName);
}
