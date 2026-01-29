/*
 * /std/act/gift.c
 *
 * This module supports easy handling of gift recieving npcs.
 * It can be used in quests for example.
 *
 * Example:
 *  To make the npc call found_wine(object ob, object from) when the
 *  object called "emonds_quest_wine" is given to it do: 
 *   add_gift("emonds_quest_wine", found_wine);
 *
 * If the function returns true then it is assumed it handled the
 * gift. If it returns false then the item will be dropped unless another
 * gift matches it also.
 *
 * To use it you must define a enter_inv function in the living which
 * looks like this:
 *
 * public void
 * enter_inv(object ob, object from)
 * {
 *    ::enter_inv(ob, from);
 *    recieve_gift(ob, from);
 * }
 *
 * Copyright Cotillion@Genesis, ask before you copy.
 */
#include <macros.h>

static mapping gifts;

/*
 * Function Name: add_gift
 * Description  : Add a gift the living should accept and process.
 *                ex - add_gift("quest_wine", found_wine);
 * Arguments    : string - a name of the objects that should match
 *                mixed - The function to call when the living is given
 *                        the object. Preferably a function.
 * Returns      : void
 */
public void
add_gift(string id, mixed action)
{
    if (!mappingp(gifts))
	gifts = ([ ]);
	
    gifts[id] = action;
}

/*
 * Function Name: remove_gift
 * Description  : Removes an item from the list of gifts the living accepts.
 * Arguments    : string - the gift id
 * Returns      : int - true on success
 */
public int
remove_gift(string id)
{
    if (!gifts[id])
	return 0;

    gifts = m_delete(gifts, id);
    return 1;
}

/*
 * Function Name: drop_unknown
 * Description  : Called from process_gift to drop an unknown object
 *                Mask this if you want the npc to drop differently.
 * Arguemtns    : object - The object to drop.
 *                object - The living, if any.
 */
public varargs void
drop_unknown(object gift, object from)
{
	command("drop " + OB_NAME(gift));
}

/*
 * Function Name: process_gift
 * Description  : Processes a gift given to this npc by a living.
 *                It will call the approperiate function to handle
 *                this gift or drop it.
 * Arguments    : object - the item
 *                object - the living who gave it to us
 */
static void
process_gift(object ob, object from)
{
    string gift, *gift_names;
    int index;
    function fun;
    
    if (!objectp(ob))
        return;

    /* If the object or living ran of we abort */
    if (environment(ob) != this_object() ||
	environment(from) != environment() ||
	!CAN_SEE(this_object(), from))
    {
	drop_unknown(ob);
	return;
    }
    
    gift_names = m_indexes(gifts);
    index = sizeof(gift_names);

    while (index--)
    {
	if (ob->id(gift_names[index]))
	{
	    gift = gift_names[index];
	    /* These are the gifts you are looking for */
	    if (functionp(gifts[gift]))
	    {
		fun = gifts[gift];
		if (fun(ob, from))
		    return;
		continue;
	    }

	    /* We support VBFC here, but it's frowned upon */
	    if (stringp(gifts[gift]))
	    {
		this_object()->check_call(gifts[gift], from);
		ob->remove_object();
		return;
	    }
	}
    }
    
    drop_unknown(ob, from);
}

/*
 * Function Name: recieve_gift
 * Description  : This function should be called from enter_inv in
 *                gift recieving livings.
 */
void
recieve_gift(object ob, object from)
{
    /* We are only interested in things from livings */
    if (!gifts || !from || !living(from))
	return;
    
    set_alarm(rnd() * 2.0 + 1.0, 0.0, &process_gift(ob, from));
}
