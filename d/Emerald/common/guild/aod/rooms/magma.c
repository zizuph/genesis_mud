/*
 *  /d/Emerald/common/guild/aod/rooms/tunnel5.c
 *
 *  This is a connecting tunnel for the Army of Darkness guild.
 *
 *  Created July 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"
#include <stdproperties.h>

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "add_spike";

/* prototypes */
public void        create_cave_room();
public int         check_exit(int checking_east = 0);


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    set_short("in a rounded lava tube");
    set_em_long("Though thick and crusted, the walls here are"
      + " softened by smooth rounded curves and corners. Above,"
      + " this lava tube passes out of the magma dome into the"
      + " volcano. A warm glow can be seen emanating from two"
      + " chambers which branch off from the main portion of the"
      + " tube both to the east and west. North, a hole in the"
      + " tube opens onto a vast chamber.\n");

    add_item( ({ "hole", "hole in the tube" }),
        "The hole appears to have been kicked in the wall.\n");
    add_item( ({ "vast chamber", "north" }),
        "The chamber to the north is truly immense. It looks like"
      + " you could almost get lost in there.\n");
    add_item( ({ "wall", "walls", "thick wall", "thick walls",
                   "crust", "crusted wall", "crusted walls",
                   "crusty wall", "crusty walls" }),
        "There is a surreal quality to these walls. They are"
      + " so crusty, and yet they flow smoothly, like the"
      + " inside of a macaroni noodle.\n");
    add_item( ({ "noodle", "macaroni", "noodles",
                 "macaroni noodle", "macaroni noodles" }),
        "Mmmmmm ... macaroni ...\n");
    add_item( ({ "curve", "corner", "curves", "corners",
                 "smooth curve", "smooth corners",
                 "round curve", "round corners",
                 "smooth corner", "round corner",
                 "smooth curves", "smooth corners",
                 "smooth curves and corners",
                 "round curves and corners",
                 "rounded curve", "rounded corners",
                 "rounded curves", "rounded corner",
                 "rounded curves and corners",
                 "smooth and rounded curves and corners" }),
        "Such formations can only be the result of moving"
      + " liquid passing through them.\n");
    add_item( ({ "liquid", "moving liquid" }),
        "Fortunately for you, there isn't any right now. Swimming"
      + " through piping hot magma tends to irritate the skin.\n");
    add_item( ({ "magma" }),
        "There isn't any here right now. That's a good thing, so"
      + " just move along.\n");
    add_item( ({ "hot magma", "piping hot magma" }),
        "Um ... yes. It doesn't tend to flow in any other way.\n");
    add_item( ({ "floor", "ground" }),
        "The ground here is not well defined. It is just as"
      + " rounded and smooth as the walls.\n");
    add_item( ({ "ceiling", "roof" }),
        "Above, the tube opens onto the volcano.\n");
    add_item( ({ "tube", "magma tube", "tubes", "lava tubes",
                 "magma tubes", "lava tube" }),
        "You stand for a moment and ponder the forces that must"
      + " have formed this place. As you do, your life expectancy"
      + " drops by another fraction of a percent.\n");
    add_item( ({ "volcano", "volcanos" }),
        "Volcanos and lava tubes go hand in hand.\n");
    add_item( ({ "glow", "warm glow" }),
        "Ahh ... its rather cozy in here. Deadly cozy.\n");
    add_item( ({ "chamber", "chambers" }),
        "They have a warm, inviting look to them.\n");
    add_item( ({ "dome", "magma dome" }),
        "You seem to be inside it.\n");
    add_item( ({ "main portion", "portion",
                 "main portion of the tube" }),
        "The tube is not very long. It branches into two separate"
      + " chambers just east and west of here.\n");
    add_item( ({ "two chambers" }),
        "You practice your counting. 1 . . . . . . . . . . . . . "
      + ". . . 2. Good for you! Gold sticker.\n");
    add_item( ({ "gold sticker", "sticker" }),
        "You wish.\n");

    add_cave_items();
    add_spike("magma");

    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from the magma dome, slowly emerging from its depths.");

    add_exit("council", "up");
    add_exit("trophy_10x7", "north");
    add_exit("sph_officer", "west", check_exit, 1, 0);
    add_exit("num_officer", "east", &check_exit(1), 1, 0);
} /* create_cave_room */


/*
 * Function name:        check_exit
 * Description  :        Only allow the correct persons into these
 *                       rooms.
 * Arguments    :        int checking_east - which direction is being
 *                                           tried? (0 by default)
 * Returns      :        int 1 - block the exit
 *                           0 - allow passage
 */
public int
check_exit(int checking_east = 0)
{
    if (checking_east)
    {
        if (!AOD_GENERAL(this_player()) &&
            !this_player()->query_wiz_level() &&
            this_player()->query_real_name() !=
            CHAMBER_MASTER->get_info("guests", NUM_OFFICER_SHORT))
        {
            write("A strange magic force stops you in your tracks!\n");
            DARKLING_TELL("You shall come no further. None may disturb"
              + " the chambers of the Headhunter General without"
              + " permission.");
            return 1;
        }

        return 0;
    }

    if (!AOD_CORPORAL(this_player()) &&
        !this_player()->query_wiz_level() &&
        this_player()->query_real_name() !=
        CHAMBER_MASTER->get_info("guests", SPH_OFFICER_SHORT))
    {
        write("A strange magic force stops you in your tracks!\n");
            DARKLING_TELL("You shall come no further. None may disturb"
              + " the chambers of the Black Corporal without"
              + " permission.");
        return 1;
    }

    return 0;
} /* check_exit */