/*
 * File:     lanthorn
 * Created:  Cirion, 1998.06.02
 * Purpose:  Lanthorn. When a candle lit from the Jazur Flame is
 *           placed within it, it will open a door in
 *           ~Avenir/union/room/lanthorn_room
 * Modification Log:
 *
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/receptacle";
#include <stdproperties.h>

public int query_holds_jazur_flame(void); 


public string
lanthorn_long(void)
{
    string str = "The lanthorn hanging from the ceiling is made from "+
	"heavy iron. Paper-thin sheets of crystal make up the windows "+
	"of the lanthorn, distorting the view of its interior. It has "+
	"a small, hinged door.";

    if (query_holds_jazur_flame())
    {
	str += " A bright blue radiance is shining from within "+
	    "the lanthorn, sending fragments of light dancing "+
	    "wildly all about.";
    }

    return str + "\n";
}

public void 
create_receptacle()
{
    set_name("lanthorn");
    add_name("lantern");
    set_short("heavy iron lanthorn");
    set_long(lanthorn_long);

    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_MAX_WEIGHT, 10000 + 500);
    add_prop(CONT_I_MAX_VOLUME, 10000 + 140);
    add_prop(OBJ_I_VALUE, 312);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET,
	"The chain holding the lanthorn is too strong.\n");
    add_prop("is_jazur_lanthorn", 1);
    set_no_show_composite(1);
}

public int
prevent_enter(object ob)
{
    if (ob->query_prop(OBJ_I_VOLUME) > 125)
    {
	write("The "+ ob->short() +" will not fit within the "+
	    short() + ".\n");
	return 1;
    }

    return 0;
}

public int
prevent_leave(object ob)
{
    if (query_holds_jazur_flame())
    {
	write("You will burn your hand if you try to get it!\n");
	return 1;
    }
    return 0;
}

public void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);
    // if we put something containing the jazur flame
    // within the lanthorn, inform the room of this
    // information.
    if (to->query_holds_jazur_flame())
	ENV(TO)->catch_lanthorn_got_flame();
}

/*
 * Function name: query_holds_jazur_flame
 * Description:   Check to see if this object holds the
 *                Jazur flame
 * Returns:       1 if it holds the flame
 */
public int
query_holds_jazur_flame(void)
{
    object *stuff = filter(all_inventory(),
	&->query_holds_jazur_flame());

    return sizeof(stuff);
}

/*
 * Function name: reset_lanthorn
 * Description:   remove burnt-out candles
 */
public void
reset_lanthorn(void)
{
    object candle = present("jazur_candle");

    if (!query_prop(CONT_I_CLOSED))
    {
	add_prop(CONT_I_CLOSED, 1);
	tell_room(ENV(TO),
	    "The door of the lanthorn swings quietly closed.\n");
    }

    if (candle && (candle->query_time(0) == 0)) // remove burned-out candles
	candle->remove_object();
}
