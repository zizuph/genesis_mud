/*
 *  /d/Emerald/common/guild/aod/obj/vendor_master.c
 *
 *  Data controller object for the Quest Vendor in Sparkle City.
 *
 *  Created February 2008, by Cooper Sherry (Gorboth)
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
    set_save_dir(DATA_DIR);
    set_garbage_dir(DATA_DIR + "old/");
} /* create_data_manager */