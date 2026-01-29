/*
 *  /d/Emerald/blackwall/delrimmon/obj/borgil_torch.c
 *
 *  This torch was once carried by Borgil, a elven scholar who died
 *  in the Blackwall Mountains, searching for Maeltar's secret. It has long
 *  ago served its purpose, and is not able to reignite.
 *
 *  Copyright (c) April 1999, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/torch.c";

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_torch();
public int     query_torch_may_decay();
public mixed   query_light_fail();


/*
 * Function name:        create_torch
 * Description  :        set up the torch
 */
public void
create_torch()
{
    set_name("torch");
    set_pname("torches");
    set_short("torch");
    set_pshort("torches");

    set_long(BSN(
        "This torch looks rather old. Most if its wooden stump"
      + " has decayed away, leaving only the upper portion of the"
      + " shaft, which appears to have survived on the merits of its"
      + " tar coating."));
} /* create_torch */


/*
 * Function name:        query_torch_may_decay
 * Description  :        a redefinition, this torch may not decay
 * Returns      :        0 - always
 */
public int
query_torch_may_decay()
{
    return 0;
} /* query_torch_may_decay */


/*
 * Function name:        query_light_fail
 * Description  :        a redefinition from /std/torch, basically
 *                       because I hated the original message
 * Returns      :        string message - failure
 */
public mixed
query_light_fail()
{
    return "You attempt to light the end of the " + short() + ", but"
         + " find that it has long since outlived its usefulness.\n";
} /* query_light_fail */
