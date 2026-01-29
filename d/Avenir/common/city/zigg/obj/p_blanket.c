// Ziggurat  ~p_blanket.c
// creator(s):   Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include "zigg.h"

inherit "/std/container";

#define SHORT "red and black gingham blanket"

private static object seat;

public mixed
query_no_get(void)
{
   if (ENV()->query_prop(ROOM_I_IS))
    {
	if (sizeof(seat->query_sitting()))
	{
	    return "You can't pick it up while someone is sitting on it!\n";
	}

	if (sizeof(TO->subinventory()))
	{
	    return "You'd better clear it off first.\n";
	}
    }
    return 0;
}

public int
query_no_show_composite(void)
{
    if (ENV()->query_prop(ROOM_I_IS))
    {
	if (sizeof(seat->query_sitting()))
	{
	    return 1;
	}
    }

    return 0;
}

public mixed
query_no_in(void)
{
    if (ENV()->query_prop(ROOM_I_IS))
    {
	return 1;
    }
    else
    {
	return 0;
    }
}

public void
create_container(void)
{
    setuid();
    seteuid(getuid());

    set_name(({"blanket", "cloth", "zigg::picnic"}));
    set_short("folded "+ SHORT);
    set_adj(({"red", "black", "gingham", "cloth", "picnic", "folded", 
    	"sybarun", "ziggurat"}));
    set_long("@@my_long");

    add_prop(CONT_I_WEIGHT, 100);
    add_prop(CONT_I_MAX_WEIGHT, 20000);
    add_prop(CONT_I_VOLUME, 100);
    add_prop(CONT_I_MAX_VOLUME, 20000);
    add_prop(OBJ_M_NO_GET, query_no_get);
    add_prop(CONT_I_IN, query_no_in);
    add_prop(CONT_I_ATTACH, 1);
	set_keep(1);
	if (IS_CLONE)
      set_item_expiration(); 
}

public string
my_long(void)
{
    string str = "It is a square blanket with red and black checkers. "+
	"It is the perfect size to carry along with you for a picnic, "+
	"giving you a place to sit or even lie on as well as put your "+
	"food. The cloth has been lightly waxed to make it resistant "+
	"to spills and damp ground. ";

    if (ENV()->query_prop(ROOM_I_IS))
    {
	return str +"\n";
    }
    else
    {
	return str +"It is folded into a neat square.\n";
    }
}

public void
f_spread(object from)
{
    /* Due we get dropped due to quitting? */
    if (!objectp(from))
	return;

    seat = clone_object(ZIG_OBJ +"p_blanket_s");
    seat->move(ENV(), 1);

    set_short(SHORT);
    remove_adj("folded");
    from->catch_tell("You spread out the "+ short() +" and smooth out "+
	"the wrinkles.\n");
    tell_room(ENV(), QCTNAME(from) +" spreads out the "+ short() +
	" and smooths out the wrinkles.\n", from, TO);
}

public void
f_fold(object to)
{
    seat->remove_object();

    to->catch_tell("You neatly fold the "+ short() +".\n");
    tell_room(ENV(to), QCTNAME(to) +" neatly folds the "+ short() +
	".\n", to, TO);
    set_short("folded "+ SHORT);
    add_adj("folded");
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (to->query_prop(ROOM_I_IS))
    {
	set_alarm(1.0, 0.0, &f_spread(from));
    }

    if (from->query_prop(ROOM_I_IS))
    {
	set_alarm(1.0, 0.0, &f_fold(to));
    }
}

public void
remove_object(void)
{
    seat->remove_object();
    ::remove_object();
}

public varargs int
move(mixed dest, mixed subloc)
{
    if (dest->query_prop(ROOM_I_IS) && present("zigg::picnic", dest))
    {
	ENV()->catch_tell("There is only room for one "+ short() +
	    " right here.\n");
	return 7;
    }

    return ::move(dest, subloc);
}

public void
describe_contents(object who, object *obarr)
{
    int size = sizeof(obarr);

    who->catch_tell(show_sublocs(who));

    if (TO->query_prop(CONT_I_ATTACH))
    {
	if (!size)
	{
	    who->catch_tell("There is nothing on the " + short() + ".\n");
	    return;
	}

	if (size == 1)
	{
	    if (obarr[0]->num_heap())
		size = obarr[0]->num_heap();
	}

	who->catch_tell(capitalize(COMPOSITE_DEAD(obarr)) +
	    (size > 1 ? " are" : " is") + " on the " + short() + ".\n");
    }
    else if (size > 0)
    {
        who->catch_tell("The " + short() + " contains " +
	    COMPOSITE_DEAD(obarr) + ".\n");
    }
    else
    {
        who->catch_tell("  " + "The " + short() + " is empty.\n");
    }
}


public string
query_recover(void)
{
    return MASTER + ":" + query_item_expiration_recover(); 
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
}
