/*
 *  /d/Emerald/common/guild/aod/obj/trophy_master.c
 *
 *  This object keeps track of the trophies that players hang from either
 *  their belts or the various spikes around the guild.
 *
 *  Copyright (c) August 2006, by Cooper Sherry (Gorboth)
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
    set_save_dir(AOD_TROPHY_DIR);
    set_garbage_dir(AOD_TROPHY_DIR + "old/");
} /* create_data_manager */

