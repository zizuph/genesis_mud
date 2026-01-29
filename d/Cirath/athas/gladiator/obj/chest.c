/* chest.c: The gladiator chest: Godfire.
 *     Corrupted by Serpine on 4-24-95
 */

/* define/undefine this to allow/disallow the chest logger */
#undef LOGGING_ENABLED

#pragma save_binary

inherit "/std/container";
#include "defs.h"

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

    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
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

#ifdef LOGGING_ENABLED
// modified by Valen, to allow logging the moves
    CHEST_LOGGER->report_sort(TP, inv);
#endif

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

#ifdef LOGGING_ENABLED

/*
 * The following code is added to allow for creating log files useable
 * to track possible breaking of Genesis rules by some players, who
 * use 'seconds' to steal things out of the chest. The code is not
 * supposed to help mortals directly, so balance/tax issues are void.
 * 
 * Valen, Feb 2003
 */

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    CHEST_LOGGER->report_create();
}

public void
remove_object(void)
{
    CHEST_LOGGER->report_remove();
    ::remove_object();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!from || !interactive(from)) return;

    CHEST_LOGGER->report_enter(ob, from);
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!to || !interactive(to)) return;

    CHEST_LOGGER->report_leave(ob, to);
}
#endif
