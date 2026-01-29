/* Dragon back coded by Nick */

#include "local.h"

inherit  STD_DRAGON + "dragon_room";

#include <stdproperties.h>
#include <macros.h>

void
create_on_dragon_room()
{
    set_short("On dragon");
    set_flying_long("You are on the back of a bronze dragon flying high up " +
		    "in the air. You can feel the wind in your hair. The " +
		    "dragon flies very fast. Far below you can see the " +
		    "ground. It's a long way to fall if you jump.\n");
    set_landed_long("You are sitting on the back of a huge dragon. There is " +
		    "room for two people to sit here. When you want the " +
		    "dragon to fly, just give him a kick.\n");

    add_item("dragon",
	     "You are sitting on its broad back, between the wings.\n");
    OUTSIDE;  /* An outside room */

    /*       FROM WHERE  WITH COMMAND  TO WHERE */
    add_landing(LANDING2,"kick dragon",LANDING1);
    add_landing("anywhere","kick dragon",LANDING2);
    set_dragon(THE_DRAGON);
}

