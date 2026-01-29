/*
 * monk_occtrain2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object spider;

//FIXA, spider?, new descr
/* From hazelnut:
I would make this small room full of a really nasty giant spider.

Do you want to see if I can get the one from Rhovanion I wrote off a
backup tape?  That spider made a container and webbed you in it.  The
only way out was to cut the web.  No edged weapon meant that you were
dead.  That might be too nasty --- it was to duplicate what happened
to Bilbo and the dwarves in the Hobbit.  A plain really nasty spider
would probably suffice here.
*/

void
reset_room()
{
    if (!objectp(spider))
    {
        spider = clone_object(ROKEDIR + "npc/bigspider");
        spider->move(TO);
    }
}

string
mylong()
{
    return "This is a very small room." +
        ((objectp(spider) && present(spider, TO)) ?
        " There is only one thing drawing your attention " +
        "in here, a giant spider.\n" : "\n");
}

void
create_room()
{
    set_short("small room");
/*
    set_long("This is a very small room. There is only one thing drawing your attention " +
             "in here, the master of unarmed combat.\n");
*/

    set_long("@@mylong");

    INSIDE;
    add_exit("monk_occtrain1", "west");
    reset_room();
}
