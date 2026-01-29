
/*
 *  /w/novo/open/auction/auction_master.c
 *
 *  Data controller object for the Auction in Sparkle
 *
 *  Created March 2008, by Novo
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

