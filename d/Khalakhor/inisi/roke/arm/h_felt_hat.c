/*
 * h_felt_hat.c
 *
 * Used in npc/van_helsing.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  This hat belongs to Van Helsing. 
    coded by Calonderiel 930906      */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("hat");
    set_adj("felt");
    add_adj("heavy");
    set_short("felt hat");
    set_long("A normal looking felt hat, but it seems very heavy for felt.\n" +
             "Inside the hat there is a  small label that reads:\n" +
             "   A gift to my dear friend, from Judge Bradshaw.\n");

    set_default_armour(20, A_HEAD, ({0, 0, 0}), 0);

    add_prop(OBJ_I_WEIGHT, 1900);
    add_prop(OBJ_I_VOLUME, 800);
}
