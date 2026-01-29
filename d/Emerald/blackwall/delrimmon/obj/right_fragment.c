/*
 *  /d/Emerald/blackwall/delrimmon/obj/right_fragment.c
 *
 *  This is the right fragment of the tablet which players are rewarded
 *  with by solving the puzzle Maeltar set up with the emblems.
 *
 *  Copyright (c) ?? 1997, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
inherit "/d/Emerald/blackwall/delrimmon/obj/tablet";

#include <macros.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

public void
create_tablet()
{
    set_name(({"tablet","tablets","fragment","fragments",
               "_del_rimmon_tablet_right"}));

    add_item( ({ "figure", "tiny figure", "carved figure",
                 "tiny carved figure", "ear" }),
        "Beneath the markings, the tiny figure of an ear has been"
      + " carved into the back of the stone fragment.\n");
}


/*
 * Function name:        query_auto_load
 * Description  :        players may keep this item over multiple
 *                       logins
 * Returns      : string - the filename of this module.
 */
public string
query_auto_load()
{
    return MASTER + ":";
} /* query_auto_load */
