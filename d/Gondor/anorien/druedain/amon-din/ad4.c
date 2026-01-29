/*
 *  This is ad4.c
 *
 *  June 1995 by Gorboth
 */

inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

#define HARD_TO_CLIMB 25 /* how hard is it to climb to slope? */

void
create_room()
{
    set_short("A pathway halfway up the northern side of Amon Din");
    set_long(BSN(
     "The pathway is rough here due to the increased slope of the hillside. " +
     "All around, the forest has begun to thin and from here the top of Amon " +
     "Din is visible directly above and to the south. The path curves down " +
     "to the southwest, or one might continue up the steep slope directly south."));
    add_item(({"pathway","path","track","hillside","hill"}), BSN(
     "The slope of the hill is truly steep from here to the summit. Crude " +
     "steps are visible in the pathway above, and a number of small " +
     "switchbacks can be seen as well."));
    add_item(({"trees","tree","forest"}), BSN(
     "The trunks of the trees rise at odd angles to compensate for the " +
     "ever increasing slope of the hillside. The forest seems to end near " +
     "to the summit, which rises to the south."));
    add_item(({"trunks","trunk"}), BSN("They are twisted so that the tips " +
     "might better compete for sunlight."));
    add_item(({"summit","top","amon din"}), BSN(
     "Through the trees to the south, you can see what appears to be " +
     "exposed rock rising from the green of the hilltop. It looks as if " +
     "a plateau of sorts may exist above."));
    add_item(({"step","steps","switchback","switchbacks"}), BSN(
     "The makeshift steps, which appear to be nothing more than partially " +
     "buried debris, are interspersed amidst various switchbacks which run " +
     "from this location to the summit. Such a climb would make one weary " +
     "to be sure!"));
    add_exit(AMON_DIR + "summit","south","@@climb",6);
    add_exit(AMON_DIR + "ad3","southwest");
}

int
climb() /* inspired by code in /d/Gondor/tharbad/ford */
{
    object tp = TP;
    int    diff,
           climb = tp->query_skill(SS_CLIMB);

    diff = random(HARD_TO_CLIMB)+14;
    if (climb < diff)
    {
        write("Despite the steps and switchbacks, you are confounded in your \n");
        write("attempt to climb the steep slope. Loosing your footing, you \n");
        write("tumble down the hill amidst a cloud of dust and rubble.\n");
        tp->reduce_hit_point((diff-climb)*7);
        write("OUCH! You brush yourself off, noticing you are back where you started.\n");
        say(QCTNAME(tp) + " fails to make it up the slope.\n");
        return 1;
     }

        write("You follow the switchbacks up to the summit.\n");
     return 0;
}
