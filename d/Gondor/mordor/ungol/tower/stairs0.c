/*
 * /d/Gondor/mordor/ungol/tower/stairs0.c
 *
 * This is the ground level of the tower of Cirith Ungol. It isn't very
 * exciting except for the fact that you will hear it if people are walking
 * in the tower withing hearing distance. In this particular room an orc will
 * run down the stairs the moment you enter the room... This orc isn't brave
 * for he will run up again, just like in the book.
 *
 * /Mercade, 26 September 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/ungol/tower/stdtower";

#include <stdproperties.h>
#include <language.h>
#include "/d/Gondor/defs.h"

#define SCARED_ORC "/d/Gondor/mordor/npc/scared_orc"

/*
 * Global variables
 */
int orc_just_arrived = 0; /* check for the orc running the stairs   */
object orc;               /* the orc running down the stairs        */

/*
 * This function defines the room.
 */
void
create_room()
{
    make_torch();    /* don't add an add_item torch as well */
    make_the_room(); /* including several add_items :-)     */

    set_name("Ungol tower, ground level");
    add_name( ({ "room", "passage" }) );

    set_short("The tower at Cirith ungol at the ground level");
    set_long(BSN("You are in a wide and echoing passage, leading from the " +
        "entrance south of you to the mountain side in the opposite " +
        "direction. It is dimly lit with torches flaring in brackets on " +
        "the walls, but its distant end is lost in the gloom. The dank " +
        "black walls seem to drip with blood. To the west you see a great " +
        "arched gate at the end of the passage, the inner side of the under-" +
        "gate. In the dimly lit hall, you see a dark opening to the north " +
        "and in it you vaguely recognize some stairs leading up in this " +
        "dreadful place."));

    add_item( ({ "stair", "stairs", "opening" }),
        BSN("Peering into the gloom you cannot see much of the stairs, " +
        "except for the fact that they are made of stone and leading up " +
        "into the tower."));
    add_item( ({ "gate", "arched gate", "under-gate" }),
        BSN("To the west, in a dimly lit room, you can see a great arched " +
        "door, probably leading to Torech Ungol, Shelobs lair. From here " +
        "you cannot see the details of it though."));

    add_prop(ROOM_I_LIGHT, 1); /* I want it light for my orc-show :-) */
    add_prop(OBJ_S_WIZINFO,
        BSN("This tower has a nice feature, being the fact that you will " +
        "hear the footsteps echoing in the tower of people that walk within " +
        "a certain hearing distance. The stairs in this tower are bit " +
        "special. They are created as a so-called winding staircase. If you " +
        "northeast you go down, northwest will take you up. In this " +
        "particular room, you are at ground level and you just go north to " +
        "get to the first floor."));

    add_exit(CIRITH_DIR + "west05",   "west");
    add_exit(CIRITH_DIR + "centre02", "east");
    add_exit(CIRITH_DIR + "winding0", "north", "@@walk_north", 2);
    add_exit(CIRITH_DIR + "west02",   "south");
  enable_reset();
}

/*
 * When you leave north, you will climb the stairs and in fact go up ;-)
 */
int
walk_north()
{
    write(BSN("Walking north, you climb the stairs to the first floor."));
    SAY(" climbs the stairs as " + PRONOUN(TP) + " walks north.");
    return 0;
}

/*
 * This function is used to let an orc come running from the stairs the moment
 * someone enters this room. Obviously, this will only happen if you enter the
 * tower from the outside and if the orc hasn't come down for some time.
 */
void
init()
{
    ::init();

    if ((TP->query_npc()) ||
        (TP->query_prop(LIVE_S_LAST_MOVE) != "west"))
    {
        return;
    }

    if (orc_just_arrived)
    {
        return;
    }

    orc_just_arrived = 1;
    set_alarm(100.0, 0.0, "reset_arrived");
    set_alarm(4.0, 0.0, "orc_warning");
}

/*
 * You get a pre-warning that you hear the orc running down the stairs.
 */
void
orc_warning()
{
    tell_room(TO, BSN("Suddenly you hear feet comming. Something is running " +
        "in great haste down an echoing stairway overhead."));
    set_alarm(4.0, 0.0, "orc_arrival");
}

/*
 * The orc enters the room.
 */
void
orc_arrival()
{
    if (objectp(orc))
    {
        LTELL_ROOM(ENV(orc), orc, "Suddenly you hear a cry and ",
            " runs away, probably following the order the cry was.", orc);
        orc->remove_object();
    }

    orc = clone_object(SCARED_ORC);
    orc->make_the_orc(45);
    tell_room(TO, BSN(CAP(LANG_ADDART(orc->short())) + " comes clattering " +
        "down. Leaping out of a dark opening to the right, it runs towards " +
        "you. It is no more than six paces away from you when it lifts its " +
        "head. You can hear its gasping breath and see the glare in its " +
        "bloodshot eyes. It stops short aghast."));
    orc->move(TO);

    set_alarm(4.0, 0.0, "orc_retreat");
}

/*
 * And then it retreats...
 */
void
orc_retreat()
{
    tell_room(TO, BSN("For a moment the orc crouches, and then with a " +
        "hideous yelp of fear it turns and flees back as it had come. Never " +
        "was any dog more heartened when its enemy turns tail than you at " +
        "this unexpected flight."));
    orc->command("north");
    orc->finish_the_orc();
}

/*
 * 100 heartbeat after the orc arrived, a new orc may do the same trick.
 */
void
reset_arrived()
{
    orc_just_arrived = 0;
}
