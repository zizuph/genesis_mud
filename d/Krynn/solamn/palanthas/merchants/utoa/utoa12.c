/* Mortis 10.2014
 */

#include <macros.h>
#include "../../local.h"
#include CLOCKH

inherit UTOA_ROOMBASE;

object skel1, skel2;

string
query_to_jail()
{
    return "west";
}

void
reset_palan_room()
{
    if (!objectp(skel1))
    {
        skel1 = clone_object(UTOA + "living/utoa_skeleton");
        skel1->move(TO);
    }
    if (!objectp(skel2))
    {
        skel2 = clone_object(UTOA + "living/utoa_skeleton");
        skel2->move(TO);
    }
}

void
create_palan_room()
{
    SHORT("A dark and dusty crypt beneath the Tower of Arms");
    LONG("You stand in a cramped crypt of dusty, grey stone somewhere "
    + "beneath the Tower of Arms. " + "@@add_long@@");

    EXIT(UTOA + "utoa12n", "north", "@@pass_skels@@", 0);
    EXIT(UTOA + "utoa13", "east", "@@pass_skels@@", 0);
    EXIT(UTOA + "utoa12s", "south", "@@pass_skels@@", 0);
    EXIT(UTOA + "utoa11", "west", 0, 0);

    reset_palan_room();
}

/* Check to see that the skeletons are in this room and able to see the
 * player trying to use the exit. Invisible or successfully sneaking people
 * should be able to pass. Anyone can pass if the skeleton is not in the
 * room. */
int
pass_skels()
{
    if (!skel1 && !skel2)
    { return 0; }

    int spass;

    if (present(skel1, TO))
    {
        spass = skel1->can_see_you(TP);
    }

    if (present(skel2, TO) && spass == 0)
    {
        spass = skel2->can_see_you(TP);
    }

    if (spass == 0)
    { return spass; }

    write("A skeleton is in your way and clacking its jaw hungrily at you.\n");
    say(QCTNAME(TP) + " is blocked from proceeding by a skeleton.\n");
    return spass;
}