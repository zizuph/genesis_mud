/*
 *
 *  Deagol, March 2003
 *  Tigerlily, added a few descriptions April, 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/clubs/nisse/lib/nisse_funcs.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/clubs/nisse/nisse_defs.h"

/*
 *  Prototypes
 */
string  long_desc();

void
create_gondor()
{
    ::create_gondor();

    set_short("Path through a field in Lebennin");
    set_long(&long_desc());

    add_item("path", &long());
    add_item(({"field", "oats", "barley", "crops", "crop"}),
        "Oats and barley grow abundantly on either side " +
        "of the path.\n");
    add_item(({"hedge", "tall hedge"}),
        "A tall dark-green hedge marks the boundary of " +
        "the field toward the northwest. It is too " +
        "distant to see details, however.\n");
    add_item(({"road", "paved road"}),
        "The path intersects with a ancient paved road to " +
        "the southeast from here.\n");
    add_item(({"pelargir", "Pelargir"}),
        "The great walled city lies farther to the " +
        "east at the mouth of the river Anduin.\n");
    add_item(({"river", "Anduin"}),
        "The Anduin is close to its end here " +
        "and several miles wide. Not far from here, " +
        "it will reach the Mouths of the Anduin, or " +
        "the Ethir Anduin, where it divides into " +
        "many smaller river courses before it finally " +
        "reaches the Sea in the Bay of Belfalas.\n");

    add_exit("/d/Gondor/lebennin/sroad/sr3", "northeast", 0, 0);
    add_exit(LEB_DIR + "sroad/sr5", "southwest", 0, 0);
}

/*
 *  Function name: long_desc
 *  Description  : Gives a long description of this room. It depends on
 *                 fact if a player is the Nisse member or not.
 */
string
long_desc()
{

    string text = "A path across a field in the southern " +
        "parts of Lebennin in Gondor." + sky_desc() +
        " Toward the northwest a tall dark green hedge " +
        "marks the boundary of the field. Some distance " +
        "to the east stand the walls of " +
        "Pelargir on the river Anduin. An abundant " +
        "crop of oats and barley grows on either " +
        "side of the path that joins a paved road to " +
        "the southwest.\n";

    return text;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if(interactive(ob))
    {
        sky_add_items();
        start_room_tells();
    }
}
