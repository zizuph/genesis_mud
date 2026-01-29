/*
 *	/d/Gondor/common/lib/drink_water.c
 *
 *	Add drinking from a water source in a room.
 *
 *	(C) 1995 by Christian Markus
 *
 *	Created: 13-Oct-1995 by Olorin
 *	Modifications:
 *	02-Sep-1998, Gnadnar: allow "drink from <source>"
 *			      as well as "drink water from 
 *			      <source>", tidy up.
 *
 *	Usage:
 *
 *	inherit "/d/Gondor/common/lib/drink_water.c";
 *
 *	void
 *	create_room()
 *	{
 *	    add_item(({"river", "spring", }), ....);
 *	    //...
 *	    set_drink_from(({"spring", "river", }));
 *	    //.
 *	}
 *
 *	public void
 *	init()
 *	{
 *	    ::init();
 *	    init_drink();
 *	}
 */

#pragma save_binary

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void	set_drink_from(mixed where);
public string	*query_drink_from();
public void	drink_message(string from);
public int	drink_water(string str);
public void	init_drink();

string *drink_from = ({});


public void	set_drink_from(mixed where)  { drink_from = ARRAY(where); }
public string	*query_drink_from()          { return drink_from; }


/*
 * Function name:	drink_message
 * Description	:	write msgs, when TP successfully drinks.
 *			mask this to customize.
 * Arguments	:	string from -- the source from which TP drank
 */
public void
drink_message(string from)
{
    write("You drink some water from the "+from+".\n"
      +  "You feel refreshed.\n");
    say(QCTNAME(TP) + " drinks some water from the "+from+".\n");
} /* drink_message */


/*
 * Function name:	drink_water
 * Descrtiption	:	handle attempts to drink
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
drink_water(string str)
{
    int     i,
            amount,
            size;
    string  source;

    /* N.B. all these notify_fail() calls have no effect. they
     * are overridden by the standard mudlib "drink" failure;
     * no matter what we do here, the player will see "Drink what?"
     */

    if (!strlen(str))
    {
        NF0("Drink what from where?\n");
    }

    str = LOW(str);

    if (str == "water")
    {
        NF0("Drink water from where?\n");
    }

    if (!parse_command(str, ({}), "[water] 'from' %s", source))
    {
        NF0("Drink what from where?\n");
    }

    if ((i = member_array(source, drink_from)) < 0)
    {
        if (present(source, TO) ||
	    TO->item_id(source))
	{
            NF0("You cannot drink any water from the "+source+".\n");
	}
        NF0("You find no "+source+".\n");
    }

    amount = TP->query_prop(LIVE_I_MAX_DRINK) / 20;
    if (TP->drink_soft(amount))
    {
	drink_message(drink_from[i]);
    }
    else
    {
	write("You cannot drink more water.\n");
    }
    return 1;
} /* drink_water */


/*
 * Function name:	init_drink
 * Description	:	add 'drink' verb
 */
public void
init_drink()
{
    add_action(drink_water, "drink");
} /* init_drink */
