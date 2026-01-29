/*
 *  /d/Emerald/common/guild/aod/obj/metal_master.c
 *
 *  This creates a list of weapons and armour that have been rejected
 *  by the Forge. My plan is to examine these files and, if indeed
 *  they are intended to be made of some metal, add the appropriate
 *  adjective to each.
 *
 *  Copyright (c) June 2007, by Cooper Sherry (Gorboth)
 */
#pragma  strict_types
#pragma  save_binary
#pragma  no_inherit
#pragma  no_clone

inherit "/d/Emerald/lib/data_manager";

#include "../defs.h"

/* Prototypes */
public void    create_data_manager();


/*
 * Function name:        create_data_manager
 * Description  :        set up the manager
 */
public void
create_data_manager()
{
    set_save_dir(AOD_LOG_DIR);
    set_garbage_dir(AOD_LOG_DIR + "old/");
} /* create_data_manager */