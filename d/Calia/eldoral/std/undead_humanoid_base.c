/*  
 * Standard Undead Base
 *  
 * This is the base class for all undeads in Calia. It sets up basic things
 * like skills, stats, and treasure.
 *
 * Created by Petros, November 2008
 */

inherit "/std/monster";
inherit "/d/Calia/eldoral/std/undead_content_base";

#include <wa_types.h>
#include <ss_types.h>
#include "/d/Genesis/gems/gem.h"
#include "../defs.h"

// Global Variables
public object * added_objects = ({ });

/*
 * Function:    create_undead_creature
 * Description: Default configure function to mask for undeads
 *              Define this in your own undead to override the standard
 *              stuff set here.
 * Arguments:   none
 * Returns:     nothing
 */
public void
create_undead_creature()
{
}

public nomask void
create_monster()
{
    object gem;

    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_SEE_DARK, 5); // Undeads typically inhabit dark places
    add_prop(OBJ_I_RES_COLD, 100);
    
    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_VOLUME, 70000);
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    
    set_alignment(-(350 + random(200)));
    set_gender(G_NEUTER);

    // Setup the adjectives for the undead.
    string *adj1 = ({"ugly", "smelly", "rancid", "putrid", "rotting", 
                     "repulsive", "loathsome", "horrid", "nasty"});
    string *adj2 = ({"foul", "odious", "unearthly", "disgusting", 
                     "unholy", "vile", "corrupt", "ungodly"});
    set_adj(one_of_list(adj1));
    add_adj(one_of_list(adj2));
    set_race_name("undead");
    set_short(implode(query_adjs(), " ") + " " + query_race_name());
    set_long("This " + query_short() + " is a Soulless being who inhabits "
        + "the dark places of Calia.\n");
    
    create_undead_creature();
    
    add_name("undead");
}

public void
default_config_undead(int level)
{
    int skill, avg_stat;
    object * inventory, * new_inventory;
    
    // We set the stat to somewhere between 80-120% of the passed in
    // level. That means that if you set it to 100, you can get an undead
    // between the levels of 80-120.
    avg_stat = ((4 * level) / 5) + random((level / 5) + 1) + random((level / 5) + 1);
    default_config_creature(avg_stat);
    add_prop(LIVE_I_UNDEAD, level);
    set_undead_skills(this_object());
    
    added_objects -= ({ 0 });
    foreach (object item : added_objects)
    {
        if (objectp(item) && environment(item) == this_object())
        {
            send_debug_message("config_undead", "Removing " 
                + item->query_short());
            item->remove_object();
        }
    }
    // Give the undead its treasure and equip it. Keep track of the
    // added object to get rid of them later.
    inventory = all_inventory(this_object());
    add_treasure(this_object());
    equip_undead(this_object());
    new_inventory = all_inventory(this_object());
    added_objects = new_inventory - inventory;
}
