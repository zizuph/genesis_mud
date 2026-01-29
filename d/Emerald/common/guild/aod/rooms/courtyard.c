/*
 *  /d/Emerald/common/guild/aod/rooms/courtyard.c
 *
 *  This is the room right outside both the Repository of Skulls and
 *  the Darkling Tower at the Army of Darkness Headquarters.
 *
 *  Copyright (c) June 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"
inherit AOD_ROOM_DIR + "blackwall_room";

/* Prototypes */
public void        create_blackwall_room();
public int         check_exit();


/*
 * Function name:        create_blackwall_room
 * Description  :        set up the room
 */
public void
create_blackwall_room()
{
    set_short("before a black tower near an opening in the mountainside");
    set_em_long("As a great curtain of rock, the cliffs of the Blackwall"
      + " Mountains loom down over this area. Directly"
      + " to the north, a great archway has been made in the"
      + " mountainside framed by grey stone blocks. Northeast, the"
      + " path runs up to the base of a tall black tower which appears"
      + " to be embedded in the rock of the cliffs. Northwest, the"
      + " path winds its way up the rocky slopes, disappearing among"
      + " the high ledges in that direction. The path descends to"
      + " lower ground to the south.\n");

    add_item( ({ "cliff", "cliffs", "cliffs of the blackwall mountains",
                 "rock", "rock of the cliff", "rock of the cliffs",
                 "slope", "rocky slope", "rocky slopes", "slopes",
                 "ledge", "ledges", "high ledge", "high ledges" }),
        "North of here, the cliffs of the Blackwall Mountains send their"
      + " sheer slopes shooting high into the sky.\n");
    add_item( ({ "archway", "high archway", "south", "southern wall",
                 "south wall", "block", "blocks", "stone block",
                 "great stone block", "great stone blocks", "arch",
                 "opening", "great arch", "great archway",
                 "grey block", "grey blocks", "grey stone block",
                 "grey stone blocks", "great grey stone blocks" }),
        "The archway is framed by great grey stone blocks which were"
      + " almost certainly hewn from the very rock of the mountains."
      + " Beyond it, you can somewhat glimpse a large chamber that"
      + " has been hollowed out of the mountainside.\n");
    add_item( ({ "mountain", "mountainside", "mountain side",
                 "side of the mountain", "north" }),
        "Just to the north, the path travels up to the side of the"
      + " mountain, where it travels beneath a great archway into"
      + " a chamber beyond.\n");
    add_item( ({ "path", "trail", "road" }),
        "The path is well trod, leading north into the mountainside,"
      + " northeast up to a tall black tower, and south down the"
      + " slope. A slightly less-travelled path leads northwest"
      + " up the sides of a rocky cliff.\n");
    add_item( ({ "less-travelled path", "slightly less-travelled path",
                 "cliff", "rocky cliff", "cliff sides", "cliffside",
                 "sides of a rocky cliff", "sides", "northwest path",
                 "path to the northwest", "northwestern path",
                 "path that leads up the cliff" }),
        "The path that leads up the cliff is broken in places by"
      + " huge steps that only someone of great size could ever hope"
      + " to traverse.\n");
    add_item( ({ "step", "steps", "huge steps", "huge step" }),
        "One would have to be an Ogre to climb that way!\n");
    add_item( ({ "south", "slope" }),
        "To the south, the path travels down the slope to lower"
      + " ground.\n");
    add_item( ({ "chamber", "large chamber", "repository",
                 "repository of skulls" }),
        "The chamber is yet too distant to view clearly. One could"
      + " travel north from here to reach it.\n");
    add_item( ({ "tower", "black tower", "dark tower", "tall tower",
                 "tall black tower" }),
        "Northeast of here, a tall black tower rises like an obelisk"
      + " from the rocky terrain. Its surface is black beyond black,"
      + " seeming to almost radiate darkness. The symmetry of the tower"
      + " is remarkable, with six perfect sides proceeding from the"
      + " base to taper at the top to a slightly rounded cap. A"
      + " doorless entrance at the base appears to be the only"
      + " way in.\n");
    add_item( ({ "surface", "surface of the tower", "edge",
                 "edges", "glassy edge", "glassy edges",
                 "smooth edge", "smooth edges", "glassy smooth edge",
                 "glassy smooth edges", "darkness" }),
        "The surface of the tower far beyond black, actually seeming"
      + " to radiate darkness from its glassy smooth edges.\n");
    add_item( ({ "symmetry", "symmetry of the tower", "side",
                 "sides", "side of the tower", "sides of the tower",
                 "base", "base of the tower", "hexagon" }),
        "The base of the tower is a perfect hexagon from which"
      + " six symmetrical sides rise up, tapering slightly as they"
      + " proceed to the top of the tower.\n");
    add_item( ({ "top of the tower", "top", "cap", "rounded cap",
                 "slightly rounded cap" }),
        "The cap at the top of the tower appears small only because it"
      + " is so high above this spot.\n");
    add_item( ({ "entrance", "doorless entrance", "portal",
                 "entryway", "rounded entrance", "rounded entryway",
                 "rounded portal", "entry", "rounded entry" }),
        "To the northeast, a rounded entryway leads into the base of"
      + " the tower. No door or hinges are visible, simply a portal"
      + " through the tower walls.\n");

    add_outdoor_items();

    add_exit("ogre_train", "northwest", check_exit, 1, 0);
    add_exit("repository", "north");
    add_exit("tower", "northeast");
    add_exit("middle_ground", "south");

    set_no_exit_msg( ({ "east", "southeast", "southwest", "west" }),
        "You wander along the outskirts of the area, finding no"
      + " passage in that direction.\n");
} /* create_blackwall_room */


/*
 * Function name:        check_exit
 * Description  :        only allow ogres into the training zone.
 * Returns      :        int 1 -- cannot go this way,
 *                       int 0 -- allowed to go this way.
 */
public int
check_exit()
{
    if (this_player()->query_guild_name_occ() != GUILD_NAME)
    {
        write("As soon as the path reaches the cliffs in that direction,"
          + " it joins with steps so massive, only a giant of some kind"
          + " could easily traverse them. You cannot travel that way.\n");

        if (this_player()->query_wiz_level())
        {
            write("Of course, being a wizard, you hop up them quite"
              + " easily.\n");
            return 0;
        }

        return 1;
    }

    return 0;
} /* check_exit */               
