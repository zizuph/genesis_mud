/*
 *  /d/Sparkle/area/tutorial/herbs/gargleroot.c
 *
 *  This is Gargleroot, an unhealthy herb that grows in the Sterling
 *  Woods in Silverdell. The idea here is to teach the players that not
 *  all herbs are good to eat ... but we don't really want to kill anyone
 *  so it isn't very damaging.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma save_binary
#pragma strict_types
#include "../defs.h"

inherit HERB_DIR + "silverdell_herb";

#include <herb.h>
#include <macros.h>

/* Prototypes */
public void        create_herb();

/*
 * Function name:        create_herb
 * Description  :        set up the herb
 */
public void
create_herb()
{
    set_name("root");

    add_name("_tutorial_item");
    set_adj( ({ "gargle", "brown", "twisted" }) );
    set_herb_name("gargleroot");

    set_short("brown twisted root");

    set_ingest_verb("eat");

    set_unid_long("This root looks slightly thicker and more juicy than"
      + " the average thing you might pull out of the ground. If you"
      + " had higher herbalism skill, you might know more about this"
      + " herb.\n");
    set_id_long("This is a specimen of Gargleroot. This fairly common"
      + " herb is very unhealthy to eat, and has very few if any"
      + " practical uses.\n");

    set_effect(HERB_HEALING, "hp", -10);
    set_id_diff(2);
    set_find_diff(0);
    set_decay_time(5400);
    set_herb_value(1);
} /* create_herb */

