/* Stralle @ Genesis 040522
 */

/* Navarre Nov 28th 2006: Added small check !pl in the do_arrive method.
                          It was causing a runtime error when calling
                          environment(pl) when pl was 0.

 * Navarre March 12th 2007: Added small check !pl in do_act method.
                            Was causing a runtime error when calling
                            environment(pl) when pl was 0.
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"

mapping gLoc = ([]);

/* We shouldn't be able to tell the time in the Abyss
 */
int
query_no_time()
{
    return 1;
}

void
create_room()
{
    set_short("The Abyss");
    set_long("Bleak dunes below a grey sky spread out in every " +
             "direction, one looking just like the other. In fact it " +
             "isn't just a resemblance, they are the same. Where the " +
             "horizon cuts in to separate ground from sky is difficult " +
             "indeed to make out, if there even is a horizon in this " +
             "alien place.\n");
    add_item(({"dunes", "bleak dunes"}), "They spread out in " +
               "every direction. No vegetation as far as the eye can see.\n");
    add_item(({"sky", "grey sky"}), "Not a single cloud, no sun nor " +
               "moon - nothing to break off the grey blanket that is above " +
               "you.\n");
}

void
set_planeswalk_loc(string pl, string room)
{
    gLoc[pl] = room;
}

mapping
query_planeswalk_loc()
{
    return gLoc;
}

varargs void
msg(string str1, object pl, string str2 = "")
{
    pl->catch_msg(str1 + "\n");
    if (strlen(str2))
    {
        tell_room(this_object(), str2 + "\n", pl);
    }
}

void
do_act(object pl)
{
    if (!pl || (environment(pl) != this_object()))
    {
        return;
    }

    switch (random(3))
    {
        case 0:
            msg("You pick a direction and decide to walk towards it. " +
                "Nothing changes in the scenery, in fact having walked " +
                "quite a bit you are unsure if you even moved a yard.",
                pl, QTNAME(pl) + " starts walking off in a " +
                (({"forward", "leftward", "rightward",
                "backward"})[random(4)]) + " direction, yet treads in " +
                "the same spot on the ground.");
            break;
        case 1:
            msg("The total lack of sound and smell makes you feel uneasy.",
                pl);
            break;
        case 2:
            msg("Not even a single breeze to break off the dull " +
                "sight of non-descript dunes.", pl);
            break;
        case 3:
            msg("", pl);
    }

    set_alarm(10.0 + itof(random(5)), 0.0, &do_act(pl));
}

void
do_arrive(object pl)
{
    if (!pl || (environment(pl) != this_object()))
    {
        return;
    }

    msg("You spot a shimmering portal in the distance. Suddenly " +
        "you stand right infront of it and chance going through it.",
        pl, "A shimmering portal speeds its way towards " + QTNAME(pl) +
        " that stops just infront of " + HIM(pl) + " who enters " +
        "through it.");
    pl->move_living("X", gLoc[pl->query_real_name()]);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    set_alarm(60.0, 0.0, &do_arrive(ob));
    set_alarm(10.0 + itof(random(5)), 0.0, &do_act(ob));
}

void
leave_inv(object from, object to)
{
    ::leave_inv(from, to);
}
