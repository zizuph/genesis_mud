/*
 *  /d/Sparkle/area/tutorial/herbs/clove.c
 *
 *  This is the herb needed to regrow the crop of garlic in Farmer
 *  Brown's fields.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 *  Updated August 8, 2016 by Gronkas : added garlic as name
 *  to fix a bug report by players trying "exa garlic" on the clove
 */
#pragma save_binary
#pragma strict_types
#include "../defs.h"

inherit HERB_DIR + "silverdell_herb";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_herb();


/*
 * Function name:        create_herb
 * Description  :        set up the herb
 */
public void
create_herb()
{
    set_name("clove");
    add_name( ({ "_tutorial_clove", "_tutorial_item", "garlic" }) );

    set_adj( ({ "wild", "small", "aromatic", "of" }) );
    set_herb_name("wild garlic");

    set_short("small aromatic clove");

    set_ingest_verb("eat");

    set_unid_long("This little clove has a strong smell, but looks"
      + " too small to make much of a useful herb. If you were to train"
      + " your herbalism skill a bit more, you would probably know more"
      + " about this potentially useful plant.\n");
    set_id_long("This is a clove of wild garlic known to grow in the"
      + " Sterling Woods northeast of Greenhollow in Silverdell. This"
      + " herb is often used as a start by farmers wishing to grow larger"
      + " varieties of garlic in their gardens. It is also known for its"
      + " properties to heal fatigue when eaten.\n");

    set_effect(HERB_HEALING,"fatigue",1);
    set_id_diff(7);
    set_find_diff(0);
    set_decay_time(5400);
    set_herb_value(36);

    add_prop(OBJ_M_NO_GIVE, "You don't feel like giving the clove away."
      + " Perhaps you could just <show> it to someone.\n");
} /* create_herb */


/*
 * Function name:        leave_env
 * Description  :        we don't want these piling up anywhere, so we
 *                       have them vanish if the player drops them
 * Arguments    :        object from - where it came from
 *                       object to   - where it went
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (!objectp(from) || !objectp(to) || !living(from))
    {
        return;
    }

    if (to->query_prop(ROOM_I_IS))
    {
        set_alarm(0.0, 0.0, &blow_away(from));
        return;
    }

    return;
} /* leave_env */

