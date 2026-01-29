/*
 *  /d/Sparkle/area/tutorial/herbs/stiltberry.c
 *
 *  Stiltberry is physically ideantical to Silverberry. Only someone
 *  with sufficient herbalism might tell them apart. It is poisonous.
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
    set_name("berry");

    add_name("_tutorial_item");
    set_adj( ({ "gleaming", "silver" }) );
    set_herb_name("stiltberry");

    set_short("gleaming silver berry");
    set_pshort("gleaming silver berries");

    set_ingest_verb("eat");

    set_unid_long("The skin of this berry almost looks as if it were"
      + " made from actual silver. If you trained your herbalism a bit"
      + " more, you might be able to know more about it.\n");
    set_id_long("This is the infamous Stiltberry. Known for its tendency"
      + " to make people feel completely exhausted. It is a dreadful"
      + " berry to eat!\n");

    set_effect(HERB_HEALING, "fatigue", -1000);
    set_id_diff(10);
    set_find_diff(0);
    set_decay_time(5400);
    set_herb_value(50);
} /* create_herb */

