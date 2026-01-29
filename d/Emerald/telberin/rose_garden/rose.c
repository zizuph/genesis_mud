/* Created by Lucius
 * Modified by Damaris for rose_garden
 * In Telberin
 * - rose.c
 *
 * Generic rose file to create various edible roses.
 */
/* Pragma to make us code properly. */
#pragma strict_types

inherit "/std/object";
/* So we can hold it if we want. */
inherit "/lib/holdable_item";

/* Usefull defines we want to use. */
#include <language.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

/* Our rose specific defines, need them. */
#include "rose.h"


/*
 * Function name: set_rose
 * Description	: Sets the type of rose we are.
 * Arguments	: string str - Fruit type we want.
 *		  mixed  adj - Adjectives we ant to use (optional)
 * Returns	: Void.
 * Notes	: Setting an invalid rose type will result in a
 *		  random type rose being set.
 */
public varargs void
set_rose(string str, mixed adj)
{
    /* Valid rose type check */
    if (!ROSES[str])
    {
    /* Invalid type, pick one at random */
	str = one_of_list(m_indexes(ROSES));
    }

    /* Lets make this look like a real rose! */
    set_name("rose");

    if (stringp(adj) || pointerp(adj))
    {
    /* We are asking to set special adjectives. */
	set_adj(adj);
    }
    else
    {
	set_adj( ({ ROSES[str], str }) );
    }

    if (ROSE_SHORT[str])
    {
    /* We defined special short and pshorts, use them. */
	set_short(ROSE_SHORT[str][0]);
	set_pshort(ROSE_SHORT[str][1]);
    }
    else if (query_adjs())
    {
    /* We have adj's, include them in the short. */
	set_short(implode(query_adjs(), " ") + " rose");
        set_pshort(LANG_PWORD(query_short()));
    }
    else
    {
	set_short(str + " rose");
	set_pshort(LANG_PWORD(query_short()));
    }

    if (ROSE_LONG[str])
    {
    /* We defined a special long, use it. */
	set_long(ROSE_LONG[str]);
    }
    else
    {
	set_long("A beautiful looking "+ short() +".\nIt looks "+
	    "to be soft and delicate.\n");
    }
}

public void
create_object()
{
    /* Setup up some basics */
    set_name("rose");
    set_short("rose");
    set_pshort("roses");
    set_long("A generic rose.\n");

    /* So we may hold it. */
    set_slots(A_ANY_HAND);
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}
