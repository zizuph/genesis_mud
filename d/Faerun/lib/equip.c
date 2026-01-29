#pragma no_clone
#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"

/*
 * Called by equip (see below) to wear/wield as appropriate.
 */
void
wield_wear_item(object ob)
{
    if (function_exists("wear_me", ob))
	ob->wear_me();
    else if (function_exists("wield_me", ob))
	ob->wield_me();
}

/*
 * Function name: equip
 * Description	: Clone a list of items (weapons/armours/clothing/etc)
 * 		  onto an npc to use.
 * Arguments	: mixed items - string or string * of items to use.
 * 		  int no_equip - don't equip items after clone/move.
 */
public varargs void
equip(mixed list, int no_equip)
{
    object old_tp, *fail;

    /* This is needed for messages */
    old_tp = this_player();
    set_this_player(this_object());

    if (stringp(list))
	list = ({ list });

    /* Clone and move the items to us */
    list = map(filter(list, strlen), clone_object);
    fail = map(list, &->move(this_object()));

    /* These items failed to move, remove them. */
    fail->remove_object();
    list -= ({ 0 });

    /* Do we wear/wield the items? */
    if (no_equip == 0)
	map(list, wield_wear_item);

    /* Reset this_player() */
    set_this_player(old_tp);
}
