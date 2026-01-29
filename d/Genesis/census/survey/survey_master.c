/*
 *  /d/Genesis/census/survey/survey_master.c
 *
 *  This object does some data-storage work for the survey of new players.
 *
 *  Created August 2011, by Cooper Sherry (Gorboth)
 */
#pragma  strict_types
#pragma  save_binary
#pragma  no_inherit
#pragma  no_clone

#include "defs.h"

inherit "/d/Emerald/lib/data_manager";

/* Prototypes */
public void    create_data_manager();


/*
 * Function name:        create_data_manager
 * Description  :        set up the manager
 */
public void
create_data_manager()
{
    set_save_dir(LOG_DIR);
    set_garbage_dir(LOG_DIR + "old/");
} /* create_data_manager */