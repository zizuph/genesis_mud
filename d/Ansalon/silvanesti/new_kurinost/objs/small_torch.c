/*
 * small_torch.c
 *
 * A small torch you can get in the tower inside the draconian camp
 * near Kurinost.
 *
 * Copyright (C): Kellon, June 2013
 *                Poul Erik Jensen
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <macros.h>
#include "local.h"

// I N H E R I T E D   F I L E S
inherit "/std/torch";

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_torch
 *  Arguments: None
 *  Returns  : Void
 * 
 *  create function that sets the properties of the small torch.
 *
 */
public void
create_torch()
{
    set_name("torch");
    set_pname("torches");
    set_adj("small");
    set_long("Rather small and dusty, this torch it nothing more " +
        "than a thick wooden log wrapped in some kind of dark " +
        "cloth and dipped in oil.\n");
    set_short("small torch");
    set_pshort("small torches");

    // Set light strength and duration.
    set_strength(1);
    set_time(900);
}


/*
 *  FUNCTION : query_recover
 *  Arguments: None
 *  Returns  : string
 * 
 *  Returns recovery-information about the torch.
 *
 */
string
query_recover()
{
    return MASTER + ":" + query_torch_recover();
}


/*
 *  FUNCTION : init_recover
 *  Arguments: arg - string, recovery information.
 *  Returns  : Void
 * 
 *  Routine to recover the small torch at login.
 *
 */
void
init_recover(string arg)
{
    init_torch_recover(arg);
}
