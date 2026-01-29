/*
 *  Union lanthorn flue
 *  Created by Lilith in July, 2004
 *
 *  Revisions:
 *  	Lucius, Aug 2017: Re-Coded.
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <macros.h>
#include <stdproperties.h>

public object *falling = ({ });


public void
union_room(void)
{
    set_short("diving into darkness");
    set_long("Diving in darkness down a well filled with water and shadows.\n");
    add_prop(ROOM_S_DARK_LONG, "Diving in darkness down a well filled "+
      "with water and shadows.\n");

    add_prop(ROOM_I_LIGHT, ALWAYS_DARK);
}

private void
falling_down(object ob, int count)
{
    string str;

    if (!ob)
	return;

    if (environment(ob) != this_object())
    {
	falling -= ({ ob });
	return;
    }

    if (count > 3)
    {
	write("You emerge, gasping for breath, in a cavern luminous "+
	    "with refracted light.\n");

	ob->move_living("M", TUNNEL +"pool", 1, 1);
	say(QCTNAME(ob) +" emerges from the water.\n");
	falling -= ({ ob });
	return;
    }

    switch (count)
    {
    case 0: str = "A welter of feelings, emotions and identities tumble "+
	    "through your consciousness at each touch of flame "+
	    "and shadow.\n";
	break;
    case 1: str = "Shadows flow past you toward the surface, slowing "+
	    "your dive.\n";
	break;

    case 2: str = "Just when you think you are going to need to return "+
	    "to the surface for air, a strong current takes "+
	    "hold of you and pulls you into darkness.\n";
	break;

    case 3: str = "Wonder and panic merge into calmness. You feel certain "+
	    "that you are safe, even in the water, surrounded by darkness.\n";
	break;
    }

    if (query_interactive(ob))
	ob->catch_msg(str + "\n\n");

    set_alarm(5.0, 0.0, &falling_down(ob, ++count));
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    falling = filter(falling, objectp);
    if (member_array(ob, falling) == -1)
    {
	falling += ({ ob });
	set_alarm(1.5, 0.0, &falling_down(ob, 0));
    }
}
