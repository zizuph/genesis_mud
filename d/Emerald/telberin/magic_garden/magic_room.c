/* Emerald/Telberin/
 * Magic Garden base room
 * Created by Damaris
 * Updated 05/Y2K
 */

#include "../defs.h"


inherit TELBERIN_ROOM;
inherit "/d/Emerald/lib/room_tell";

#include "/d/Emerald/sys/properties.h"
#include "/d/Emerald/sys/terrain_types.h"


void
create_magic_garden()
{
}

nomask void
create_telberin_room()
{
	/* To set the short desc. in the garden rooms. */
    set_short("A mysterious magic garden");

    /* To add items to be examined, from all garden rooms. */
    add_item(({"garden"}),
       "You are in a most mysterious garden. Although it looks like a "+
       "normal garden with trees, bushes and flowers, you can feel the "+
       "magic in air. As you survey this area you realize things aren't quite "+
       "as they appear to be. You might want to take a closer look at "+
       "everything that catches your eyes. Through the silver gate is "+
       "the Royal Circle.\n");

    add_item(({"grass", "ground"}),
       "The grass is sweet smelling and soft to the touch as it covers "+
       "the ground in a delightful blanket.\n");

    add_item(({"fragrance", "fragrances"}),
       "There are so many exotic and mysterious fragrances here "+
       "that you feel an intoxicating effect.\n");

    add_item(({"branch", "branches"}),
       "The branches on the trees sway softly in the light breeze.\n");

    add_item(({"leaf", "leaves"}),
       "The leaves on the trees and bushes rustle softly in the breeze.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_GARDEN);

    /* This sets a tell message in all the rooms. */

    set_tell_time(300);
    add_tell(({
       "A soft breeze carries the sound of a woman's voice singing an "+
       "enchanting song.\n",
       "You hear a sudden rush of water then only silence.\n",
       "A silver haired squirrel studies you for a moment then briskly "+
       "scurries up a tree and disapears.\n",
       }));

create_magic_garden();
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
       start_room_tells();
    }
}

    /* This is for smells in the room. */
void
hook_smelled(string str)
{
    if (!strlen(str) || parse_command(str, ({}), "[the] 'air'"))
    {
        write("The air is filled with exotic and mysterious scents.\n");
        return;
    }

    if (str == "grass")
    {
        write("A soft sweet scent caresses your senses.\n");
	return;
    }

    if (str == "fragrance")
    {
        write("A soft exotic scent fills your senses.\n");
	return;
    }
}


