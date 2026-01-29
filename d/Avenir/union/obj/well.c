/*
 * File:     well
 * Created:  Lilith, July 2004
 * Purpose:  Is the the well of the souls of shadow warriors
 *	     touch flame produces a touch of the essence of someone long gone.
 *
 * Revisions: Lilith Apr 2022: added missing add_items
 *
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>


public string
well_long(void)
{
    string str = "A great flame burns deep blue within the confines "+
	"of the pool, formed of many smaller flames that alternately "+
	"leap apart and merge into one. It rises up in graceful power "+
	"above untainted water whose surface is rippled by the unceasing, "+
	"chaotic dancing. You have found the Well of Souls.\n";

    if (present(SWAY_ID, TP))
    {
	str += "\nIn the altered state of the Sway, you sense that "+
	    "each flame is the essence of a Shadow Warrior. Before "+
	    "you is the well of the souls of all the Warriors past "+
	    "and present, the receptacle of the essence of what each "+
	    "of Us has given to Jazur. These flames will burn eternal, "+
	    "never lost to Unity even when flesh and memory cease "+
	    "to exist. This is the Well of Souls.\n";
    }
    return str;
}

public void
get_name(void)
{
    string *souls = LIST->named_list();
    int name = random(sizeof(souls));
    string who = (souls[name]);

    if (!IS_MEMBER(TP))
	return;

    name++;
    if (name >= sizeof(souls))
	name = 0;

    if (TP->query_real_name() == who)
    {
	write("With wonder, you realize that your fingers have "+
	    "brushed your own essence within the flames.\n");
    }
    else
    {
	write("A sense of wonder fills you as you realize that "+
	    "your fingers have brushed the essence of "+ CAP(who) +
	    " residing within this well of passion.\n");
    }
}

public void
create_object(void)
{
    set_name("_jazur_well_of_passion");
    add_name(({"pool", "water", "well", "flame", "blue flame",
        "smaller flames"}));
    set_short("pool of water");
    set_long(well_long);
    add_prop(OBJ_I_LIGHT, 20);
    add_prop(OBJ_I_VALUE, 100000);
    add_prop(OBJ_M_NO_GET, "Your hands, though deadly and capable, "+
	"are far too small for this task.\n");
    add_prop("is_jazur_well_of_passion", 1);
    set_no_show_composite(1);
}

public int
touch(string str)
{
    NF(CAP(query_verb()) + " what?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}),
	    "[the] [deep] [blue] 'flame' / 'fire' / 'flames'"))
	return 0;

    if (IS_MEMBER(TP))
    {
	write("You reach into the deep blue flames.\n");
	get_name();

	if (!random(3))
	{
	    write("Profound joy uplifts you as you are reminded of the "+
		"many who form the whole of which you are a valued part.\n");
	}
    }
    else
    {
	write("You pass your hand through the flame, as if it were not "+
	    "there.\n");
    }

    say(QCTNAME(TP) +" passes "+ HIS(TP) +" hand through the "+
	"deep blue flame.\n");

    return 1;
}

public void
init(void)
{
    ::init();

    add_action(touch, "touch");
    add_action(touch, "feel");
}

/*
 * Function name: query_holds_jazur_flame
 * Description:   Check to see if this object holds the
 *                Jazur flame
 * Returns:       1 if it holds the flame.
 */
public int
query_holds_jazur_flame(void)	{ return 1; }

/*
 * Function name: query_jazur_flame_present
 * Description:   Check to see if the jazur flame is present
 *                in the room. Used for objects that need to
 *                see if they are in a room with the Jazur
 *                flame.
 * Returns:       1 if Jazur Flame is present.
 */
public int
query_jazur_flame_present(void)	{ return 1; }
