/*
 *  /d/Sparkle/area/tutorial/herbs/leaf.c
 *
 *  This is the Sterling Leaf, an herb growing in Sterling Woods in
 *  Silverdell.
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
    set_name("leaf");

    add_name("_tutorial_item");
    set_adj( ({ "sterling", "broad", "silver" }) );
    set_herb_name("sterling leaf");

    set_short("broad silver leaf");
    set_pshort("broad silver leaves");

    set_ingest_verb("eat");

    set_unid_long("This leaf is quite beautiful to look at."
      + " Unfortunately, you have not trained your herbalism skill"
      + " high enough to know anything else about it.\n");
    set_id_long("The beautiful silvery sheen along its length is standard"
      + " for the herb known as Sterling Leaf. These leaves grow"
      + " throughout the Sterling Woods in Silverdell, and are known"
      + " for their properties to heal fatigue.\n");

    set_effect(HERB_HEALING, "fatigue", 30);
    set_id_diff(5);
    set_find_diff(0);
    set_decay_time(5400);
    set_herb_value(40);
} /* create_herb */

