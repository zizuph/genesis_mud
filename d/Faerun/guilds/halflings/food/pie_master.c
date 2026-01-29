/*
 *  /d/Faerun/guilds/halflings/pie_master.c
 *
 *  This object keeps track of the pie-making and using process
 *  in the Halflings guild for Faerun.
 *
 *  Copyright (c) March 2016, by Cooper Sherry (Gorboth)
 */
#pragma  strict_types
#pragma  save_binary
#pragma  no_inherit
#pragma  no_clone

inherit "/d/Emerald/lib/data_manager";

#include "../halflings.h"

/* Prototypes */
public void    create_data_manager();


/*
 * Function name:        create_data_manager
 * Description  :        set up the manager
 */
public void
create_data_manager()
{
    set_save_dir(GUILD_DATA);
    set_garbage_dir(GUILD_DATA + "old/");
} /* create_data_manager */