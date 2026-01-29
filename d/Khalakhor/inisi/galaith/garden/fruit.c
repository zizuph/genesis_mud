/*
 * - fruit.c
 *
 * Generic fruit file to create various edible fruits.
 */
/* Pragma to make us code properly. */
#pragma strict_types

/* Usefull defines we want to use. */
#include <language.h>

/* Our fruit specific defines, need them. */
#include "fruit.h"

/* The base food object. */
inherit "/std/food";

/*
 * Function name: set_fruit
 * Description	: Sets the type of fruit we are.
 * Arguments	: string str - Fruit type we want.
 *		  mixed  adj - Adjectives we ant to use (optional)
 * Returns	: Void.
 * Notes	: Setting an invalid fruit type will result in a
 *		  random type fruit being set.
 */
public varargs void
set_fruit(string str, mixed adj)
{
    /* Valid fruit type check */
    if (!FRUITS[str])
    {
    /* Invalid type, pick one at random */
	str = one_of_list(m_indexes(FRUITS));
    }

    /* Lets make this look like a real fruit! */
    set_name(str);
    set_amount(FRUITS[str]);

    if (FRUIT_ADJS[str])
    {
    /* We defined certain adjectives to use, so use them. */
	set_adj(FRUIT_ADJS[str]);
    }
    else if (stringp(adj) || pointerp(adj))
    {
    /* We are asking to set special adjectives. */
	set_adj(adj);
	set_short(implode(query_adjs(), " ") + " " + str);
	set_pshort(LANG_PWORD(query_short()));
    }

    if (FRUIT_SHORT[str])
    {
    /* We defined special short and pshorts, use them. */
	set_short(FRUIT_SHORT[str][0]);
	set_pshort(FRUIT_SHORT[str][1]);
    }
    else if (query_adjs())
    {
    /* We have adj's, include them in the short. */
	set_short(implode(query_adjs(), " ") + " " + str);
        set_pshort(LANG_PWORD(query_short()));
    }
    else
    {
	set_short(str);
	set_pshort(LANG_PWORD(str));
    }

    add_prop(HEAP_S_UNIQUE_ID, query_short());

    if (FRUIT_LONG[str])
    {
    /* We defined a special long, use it. */
	set_long(FRUIT_LONG[str]);
    }
    else
    {
	set_long("A delicious looking "+ str +".\nIt looks "+
	    "to be quite edible and tasty.\n");
    }
}

public void
create_food()
{
    /* Setup up some basics */
    set_amount(20);
    set_name("fruit");
    set_short("fruit");
    set_long("A generic piece of fruit.\n");
}

public void
special_effect(int amnt)
{
    int   sz;
    mixed tmp = FRUIT_SPC[query_short()];

    if (!tmp)
	return;

    /* Check to see if we set a special effect string(s).
     * If so, print them.
     */
    if (stringp(tmp))
    {
	write(tmp + "\n");
    }
    else if (pointerp(tmp))
    {
	if (sz = sizeof(tmp))
	{
	    write(tmp[0] + "\n");
	}

	if (sz == 2)
	{
	    say(tmp[1] + "\n");
	}
    }
}
