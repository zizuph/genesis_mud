/*
 * /d/Gondor/common/potions/mortar.c
 *
 * adds the ability to engrave your name on the mortar -- Gnadnar
 */

#pragma strict_types

inherit "/d/Genesis/std/potions/mortar.c";

#include <macros.h>
#include <language.h>
#include "/d/Gondor/defs.h"

static string	Engraving = "";

public void		init();
public int		do_engrave(string arg);
varargs public mixed	long(string str, object for_obj);
public string		query_auto_load();
public void		init_arg(string arg);


public void
create_container()
{
	::create_container();
        set_short("mortar");
        add_adj("stone");
	add_prop(CONT_I_HOLDS_COMPONENTS, 1);
	
	return;
}

/*
 * Function name:	init
 * Description	:	add the "engrave" verb
 */
public void
init()
{
    ::init();
    add_action(do_engrave, "engrave");
} /* init */

/*
 * Function name:	do_engrave
 * Description	:	handle attempts to engrave mortar
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_engrave(string arg)
{
    object	ob,
		tp = TP;
    string	name = tp->query_real_name();

    if (!strlen(arg))
    {
	NF0("Engrave what?\n");
    }
    arg = LOW(arg);
    /* accept: engrave gnadnar on the mortar, engrave mortar,
     * engrave name on mortar, engrave my name gnadnar on the mortar,
     * etc etc of course, this will accept "engrave my on mortar", but
     * we can probably live with that.
     */
    if (!parse_command(arg, ({ TO }),
        "[my] [name] ["+name+"] [on] [the] %o", ob))
    {
	NF0("Engrave what?\n");
    }
    if (strlen(Engraving))
    {
	NFN0("The mortar already is engraved with the name '"+
	    Engraving+"'.");
    }
    write("You engrave your name on the "+short()+".\n");
    SAY(" engraves something on "+LANG_ADDART(short())+".");
    Engraving = CAP(name);
    return 1;
} /* do_engrave */


/*
 * Function name:	long
 * Description	:	mask parent to append Engraving.
 * Arguments	:	string str - the pseudo-item to describe. This is an
 *                             item added with add_item. If this is 0, it
 *                             will return the description of the whole
 *                             object.
 *			object for_obj - the object trying to get the long.
 * Returns	:	string - the description of the object or pseudo-item.
 */
varargs public mixed
long(string str, object for_obj)
{
    string	desc;

    desc = ::long(str, for_obj);
    if (strlen(Engraving))
    {
	desc += "The name '"+Engraving+"' is engraved on the "+short()+".\n";
    }
    return desc;
} /* long */


/*
 * Function name:	query_auto_load
 * Description	:	return info for autoloading
 * Returns	:	string -- filename + Engraving
 */
public string
query_auto_load()
{
    return MASTER + ":" + Engraving;
} /* query_auto_load */

/*
 * Function name:	init_arg
 * Description	:	called when autoloading, will set Engraving
 * Arguments	:	string arg -- the autoload argument
 */
public void
init_arg(string arg)
{
    if (strlen(arg))
    {
	Engraving = arg;
    }
} /* init_arg */
