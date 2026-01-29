/*
 * redwood.c
 *
 * Used in carisca/ftree1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Added consistent singular and plural names - Tapakah, 04/2021
 */

/* a redwood leaf, used for healing - chew on it */

#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>

void
create_herb()
{
    set_ingest_verb("chew");

    set_name("leaf");
    set_short("red leaf");
    set_adj("red");

    add_name(({"herb", "redwood"}));

    set_herb_name("redwood leaf");

    set_unid_long("An ordinary red leaf found somewhere in a forest.\n");
    set_id_long("This is a redwood leaf, chewed to heal faster.\n");

    set_herb_value(500);

    set_id_diff(2);

    set_find_diff(1);
    
    set_effect(HERB_HEALING, "hp", 20);
}
