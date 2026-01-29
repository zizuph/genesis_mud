/*
 *  Union lanthorn flue
 *  Created by Lilith in July, 2004
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <macros.h>
#include <stdproperties.h>

#define ENTER	(ROOM + "lanth_stairt")
#define EXIT	(ROOM + "circle0")

public object *falling = ({ });
public string *land = ({ "feet", "hands and knees" }),
	      *tells = ({
    "You are launched into the air for a moment.",
    "Your stomach shifts as you spiral downward.",
    "You are going so fast the air seems to wail past "+
        "your ears.",
    "Something rushes up toward you in the impenetrable "+
        "darkness.",
    "The scent of water fills your nostrils.",
    "You slide downward into the darkness, falling faster "+
        "with each passing moment."
});


public void
union_room(void)
{
    set_short("sliding into darkness");
    set_long("Sliding in darkness down a spiral stone flue.\n");
    add_prop(ROOM_S_DARK_LONG,
	"Sliding in darkenss down a spiral stone flue.\n");
    add_prop(ROOM_I_LIGHT, ALWAYS_DARK);

    add_item(({"flue", "spiral"}),
      "It is a flue or channel made of the same dark stone as the "+
      "rest of this place. It appears to be glossy and smooth, and "+
      "it spirals downward into a black abyss.\n");
    add_item(({"down", "darkness", "space"}),
      "As you look down into the abyss, you sense that the abyss also "+
      "looks back into you.\n");
}

public void
falling_down(object ob, int count)
{
    if (!objectp(ob) || (environment(ob) != this_object()))
    {
	falling -= ({ ob });
    }
    else if (count > 3)
    {
	string where = one_of_list(land);

	ob->catch_tell("The bottom falls out of the spiralling flue!\n"+
	    "You land hard on your "+ where +".\n");
	tell_room(EXIT, QCTNAME(ob) +" falls out of the spiral flue and "+
	    "lands hard on "+ HIS(ob) +" "+ where +".\n", ob);

	ob->move_living("M", EXIT, 1);
	falling -= ({ ob });
    }
    else
    {
	ob->catch_tell("\n" + one_of_list(tells) + "\n\n");
	set_alarm(4.0, 0.0, &falling_down(ob, ++count));
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (member_array(ob, falling) == -1)
	set_alarm(1.5, 0.0, &falling_down(ob, 0));
}
