/* chest.c: The gladiator chest: Godfire.
 *     Corrupted by Serpine on 4-24-95
 */
#pragma save_binary

inherit "/std/container";
#include "defs.h"

#define CHEST_ROOM (GLAD_ROOM + "gldchest")

public void
create_container()
{
    set_name("chest");
    add_name("_gladiator_chest");
    set_adj("huge");
    add_adj("stone");
    set_long("This massive stone chest is used to hold equipment for the "+
      "Gladiators so they can keep themselves supplied. As this "+
      "saves their master Kalak money, he encourages them to use, "+
      "supply, and defend it as they see fit.\n");

    add_prop(CONT_I_MAX_WEIGHT, 800000);
    add_prop(CONT_I_MAX_VOLUME, 800000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_I_NO_GET, "Even a half-giant couldn't lift this thing.\n");
}

/*
 * Sort out the saving equipment.
 */
public int
kick_chest()
{
    object *inv = all_inventory();
    inv = filter(inv, not @ &->check_recoverable());
    inv->move(environment());
    return sizeof(inv);
}
#if 0

/*
 * A check to see if they may take from the chest.
 *
 * Commented out as its can easily be bypassed by kicking the chest for
 * the most part.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (living(to) && CHECK_PUNISHMENT(to->query_real_name(), PUN_CHEST))
    {
	ob->move(this_object());
	tell_object(to, "Your chest priviledges have been revoked.\n");
    }
}
#endif

#if 0
/*
 * AoB whined about this requiring an increase in tax so
 * it is commented out as I disagreed.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    ob->add_prop(OBJ_M_NO_SELL, 
      "This item belongs to the Gladiators of Athas.\n");
}
#endif

