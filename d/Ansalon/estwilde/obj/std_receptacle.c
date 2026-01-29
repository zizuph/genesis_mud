inherit "/std/receptacle";

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Ansalon/common/defs.h"

void
create_rack()
{
}

void
create_container()
{
    set_name("rack");
    set_adj("large");
    add_adj("wooden");
    set_long("This is a large rack, made from a blackwood "+
      "pine native to this area. It has been designed to hold "+
      "various items.\n");
    add_prop(OBJ_I_VALUE,	0);
    add_prop(CONT_I_ATTACH,	1);
    add_prop(CONT_I_RIGID,	0);
    add_prop(OBJ_M_NO_GET,	1);
    add_prop(CONT_I_WEIGHT,	10000);
    add_prop(CONT_I_VOLUME,	7500);
    add_prop(CONT_I_MAX_WEIGHT, 900000);
    add_prop(CONT_I_MAX_VOLUME, 900000);

    create_rack();
}

public int
prevent_enter(object ob)
{
    if (living(ob))
	return 1;
    return 0;
}

public int
sort_recover(string str)
{
    int i;
    object *ob, *ob2 = ({});

    if (!(ARMAGEDDON->shutdown_active()))
    {
	NF("Sorting is allowed only during Armageddon.\n");
	return 0;
    }

    if (!strlen(str) ||
      !parse_command(str, E(TP), "[the] %i", ob) ||
      !sizeof(ob = NORMAL_ACCESS(ob, 0, 0)))
    {
	NF(C(query_verb()) + " what?\n");
	return 0;
    }
    if (sizeof(ob) > 1)
    {
	NF(C(query_verb()) + " what?  Be more specific.\n");
	return 0;
    }
    if(ob[0] != TO)
    {
	NF(C(query_verb()) + " what?\n");
	return 0;
    }

    ob = all_inventory(TO);
    if (!sizeof(ob))
    {
	NF("There is nothing to sort in "+short()+".\n");
	return 0;
    }

    for (i=0; i<sizeof(ob); i++)
    {
	if (!ob[i]->check_recoverable())
	    ob2 += ({ ob[i] });
    }
    if (!sizeof(ob2))
    {
	write("Everything in "+short()+" glows.\n");
	return 1;
    }
    ob = ({});

    for (i=0; i<sizeof(ob2); i++)
    {
	if (!ob2[i]->move(E(TO)))
	    ob += ({ ob2[i] });
    }
    if (!sizeof(ob))
    {
	write("You did not sort anything out of "+short()+".\n");
	return 1;
    }
    str = COMPOSITE_DEAD(ob);
    write("You sorted "+str+" out of "+short()+".\n");
    tell_room(E(TP), QCTNAME(TP)+" sorted "+str+" out of "+short()+".\n", TP);
    return 1;
}

public void
init()
{
    ::init();
    add_action(sort_recover, "sort");
}

/*
 * Function name: prevent_leave
 * Description:   Called when an object is trying to leave this container
 *                to see if we allow it to leave.
 * Arguments:     object ob - the object trying to leave
 * Returns:       1 - The object is not allowed to leave
 *                0 - The object is allowed to leave
 */
/*
public int
prevent_leave(object ob)
{
    if (MANAGER->query_punishment(TP, PUN_NOARMOURY) && !(ARMAGEDDON->shutdown_active()))
    {
	write("You have been punished by restricted armoury access.\n");
	return 1;
    }
    return 0;
}
*/

