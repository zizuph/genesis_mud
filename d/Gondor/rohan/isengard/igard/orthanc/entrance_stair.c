/*
 *  ORTHANC + "entrance_stair.c"
 *
 *  Isle of rock at the base of Orthanc, with stairs
 *  leading up to the tower.
 *
 *  Last modified by Alto, 19 October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

#define CLIMBING_THE_STAIRS    "_climbing_the_stairs"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "plain_funcs.c";

public void        create_gondor();
public string      long_desc();
public int         climb_stairs();
public int         exit_room();
public int         check_stairs();

object             actor;

public void
create_gondor()
{
    set_short("At the stairs of Orthanc");
    set_long(&long_desc());

    sky_add_items();
    outside_add_items();
    plain_add_items();
    isle_add_items();

    add_item(({"room", "area", "surroundings", "isle", "place",
        "landscape"}), long_desc);

    add_item(({"street", "wide street", "road"}), "A wide street leads away "
        + "from Orthanc toward the ring wall. It is paved with stone-flags, "
        + "dark and hard, squared and laid with great skill. No blade of grass "
        + "can be seen in any joint. Long lines of pillars, some of marble, "
        + "some of copper and of iron march along the road in long lines.\n");
    add_item(({"flight", "stair", "stairs", "broad stairs", "broad stair"}),
        "The broad stairs lead up to the great door of the tower and were "
        + "hewn by the same unknown art as that of the black stone of the "
        + "tower itself. A nagging pressure from your subconscious urges "
        + "you to climb up the stairs.\n");
    add_item(({"door", "great door"}), "You would have to climb the twenty-"
        + "seven broad stairs to examine it more closely. There is something "
        + "about this place that seduces you to do so, and yet the thought "
        + "of climbing them fills you with revulsion.\n");
    add_item(({"step", "steps"}), "The steps of the broad stairwell are "
        + "black and glistening. There are twenty-seven of them.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_cmd_item(({"stairs", "the stairs", "up stairs", "up the stairs"}), 
            "climb", &exit_room());

    add_exit(IGARD_PLAIN  + "east_road10",  "east", check_stairs, 2, 0);
    add_exit(IGARD_PLAIN  + "isle1",        "north", check_stairs, 2, 0);
    add_exit(IGARD_PLAIN  + "isle7",        "south", check_stairs, 2, 0);

    reset_room();
}


string
long_desc()
{
    return "You stand at the very foot of the mighty tower Orthanc, which "
      + "vaults high into the sky over your head. The isle of rock at its "
      + "base is black and gleams as if it is wet. The many faces of the "
      + "stone have sharp edges as though they have been newly chiselled." 
      + sky_desc() + " A street leads to the east, and a small path leads "
      + "around the isle to the west and south. A flight of "
      + "twenty-seven broad stairs leads up to the great door of Orthanc.\n";
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     sky_add_items();
}


int
climb_stairs()
{
    actor = TP;

    TP->add_prop(CLIMBING_THE_STAIRS, 1);

    set_alarm(0.0, 0.0, &write("You begin to climb the stairs. A sudden "
        + "dread seizes your heart.\n"));
    set_alarm(1.0, 0.0, &write("One step ...\n"));
    set_alarm(2.0, 0.0, &write("Two steps ...\n"));
    set_alarm(3.0, 0.0, &write("Three ...\n"));
    set_alarm(4.0, 0.0, &write("Four  ...\n"));
    set_alarm(5.0, 0.0, &write("Five  ...\n"));
    set_alarm(6.0, 0.0, &write("Six   ...\n"));
    set_alarm(7.0, 0.0, &write("Seven ...\n"));
    set_alarm(8.0, 0.0, &write("Your nerves tie your stomach in knots, and "
        + "you lose count.\n"));
    set_alarm(14.0, 0.0, &write("You are halfway up the broad stairs. Each "
        + "footstep becomes harder to take.\n"));
    set_alarm(21.0, 0.0, &write("Almost there ...\n"));
    set_alarm(25.0, 0.0, &write("Not quite there ...\n"));
    set_alarm(27.0, 0.0, &write("With a sigh you reach the top, feeling "
        + "insignificant and small.\n"));

    tell_room(environment(actor), QCTNAME(actor) + " begins to "
        + "climb the stairs.\n", 
        ({actor}));
    set_alarm(14.0, 0.0, &tell_room(environment(actor), 
        QCTNAME(actor) + " is halfway up the stairs and looks as though "
        + PRONOUN(actor) + " dreads every step.\n", ({actor})));

    return 1;
}


int
move_player()
{
    say(QCTNAME(TP) + " reaches the top at last, where "
        + PRONOUN(actor) + " seems insignificant and small.\n");
    tell_room(ORTHANC + "doorway", QCNAME(TP) + " arrives from the "
        + "broad flight of stairs.\n");

    TP->move_living("M", ORTHANC + "doorway", 1, 0);
    TP->remove_prop(CLIMBING_THE_STAIRS);

    return 1;
}


int
check_stairs()
{
    if (TP->query_prop(CLIMBING_THE_STAIRS))
    {
        write("You are climbing the stairs! For some reason you "
            + "entirely lack the will to return to the bottom.\n");
        return 1;
    }

    return 0;
}


int
exit_room()
{
    if (!SIO)
    {
        write("You look up the long flight of stairs and prepare to ascend "
        + "them. Suddenly a strong and malevolent will contests your own. "
        + "As the alien will easily wins, you find that you no longer possess "
        + "the conviction to climb the stairs.\n");
    return 1;
    }

    climb_stairs();
    set_alarm(28.0, 0.0, &move_player());        
    return 1;

}
