/* 
 *  Options Handling Code for the Elven Archers
 *  
 *  This manager keeps track of the options available to the guild member
 *  
 *  By keeping track of this information in a centralized place, it can
 *  be displayed and queried even if players aren't logged in. 
 *
 *  Created by Petros, May 2008
 *  Copied by Carnak
 */

#pragma strict_types
#pragma save_binary

#include "../guild.h"
#include <macros.h>
#include <files.h>

inherit "/d/Genesis/specials/guilds/council/options_manager";

/* Defines */
#define OPTIONS_DATA      (GUILD_DIR + "data/options_data")

/* Global Variables */
string *approved = ({}), *denied = ({});

/*
 * Function:    query_options_file
 * Description: Mask this function to specify where the option data should
 *              be stored.
 */
public string
query_options_file()
{
    return OPTIONS_DATA;
} /* query_options_file */

public string
query_archer_armour(object armour)
{
    string desc;
    
    if (!objectp(armour) || !IS_ARMOUR_OBJECT(armour))
        return 0;
    
    if (member_array(MASTER_OB(armour), approved) > -1)
        return 0;
    
    if (member_array(MASTER_OB(armour), denied) > -1 ||
        wildmatch("*plate*", armour->short() + armour->long()))
    {
        
        return "The " + armour->short() + " would hinder your movement in "
        + "combat, you decide against wearing it.\n";
    }
        
    return 0;
}

public status
add_archer_armour(object armour)
{
    if (!objectp(armour) || !IS_ARMOUR_OBJECT(armour))
        return 0;
    
    if (member_array(MASTER_OB(armour), denied) > -1)
        denied -= ({ MASTER_OB(armour) });
    
    if (member_array(MASTER_OB(armour), approved) < 0)
        approved += ({ MASTER_OB(armour) });
    
    save_data();
    return 1;
}

public status
remove_archer_armour(object armour)
{
    if (!objectp(armour) || !IS_ARMOUR_OBJECT(armour))
        return 0;
    
    if (member_array(MASTER_OB(armour), denied) < 0)
        denied += ({ MASTER_OB(armour) });
    
    if (member_array(MASTER_OB(armour), approved) > -1)
        approved -= ({ MASTER_OB(armour) });
    
    save_data();
    return 1;
}
