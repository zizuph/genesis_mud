/*
 *  /d/Sparkle/area/orc_temple/obj/armour_rack.c
 *
 *  An actual functioning armour rack for the Orc Dungeons.
 *
 *  Created December 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "/d/Sparkle/guilds/new_merc/merc_defs.h"

inherit "/d/Sparkle/guilds/new_merc/obj/armour_rack"; 


/*
 * Function name:        create_rack
 * Description  :        the object constructor
 */
public void
create_rack()
{
    remove_name("rack");
    set_name("stand");
    add_adj( ({ "huge", "armour", "armor" }) );
    set_short("huge armour stand");
    set_long("\nThe armour stand in this room looks big enough to suit"
      + " the needs of a small army.\n\n");

    set_enable_recovery(0);
} /* create_rack */


public void
recover_objects_from_database()
{
}