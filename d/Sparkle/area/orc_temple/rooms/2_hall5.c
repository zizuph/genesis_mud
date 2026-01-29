/*
 *  /d/Sparkle/area/orc_temple/2_hall5.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 2.
 *
 *  Created September 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit ROOMS_DIR + "dungeon_room";


/* Prototypes */
public void         create_dungeon_room();


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    object   door;

    set_short("at the north end of a long row of prison cells");
    set_long("What appear to be prison cells extend into the gloom"
      + " south of here, where you hear moans and smell things you"
      + " wish you hadn't. Flickering torches cast a grim illumination"
      + " over the entire scene. The passage rounds a bend here and"
      + " also heads west.\n\n");

    try_item( ({ "passage", "here" }),
        "This passage has seen a lot of sorrow, you guess.\n");
    try_item( ({ "sorrow" }),
        "Well, it is a prison, you know. Not quite the sort of place"
      + " for a picnic.\n");
    try_item( ({ "prison" }),
        "Bars. Cells. Moans. Smells. Yup ... its a prison.\n");
    try_item( ({ "smell", "smells" }),
        "Smells like ... like ... like a room filled with corpses"
      + " that have been stuffed with limburger cheese!\n");
    try_item( ({ "toilet" }),
        "The whole place smells like one. For all you know, the orcs"
      + " simply do their business wherever they stand, so maybe the"
      + " whole place IS one! Yeeeesh.\n");
    try_item( ({ "row", "long row", "cells", "prison cells",
                 "cell", "row of cells", "long row of cells",
                 "row of prison cells", "prison cell",
                 "long row of prison cells" }),
        "There seem to be cells all along the corridor to the"
      + " south.\n");
    try_item( ({ "corridor to the south" }),
        "There appear to be cells all along its length.\n");
    try_item( ({ "gloom", "gloom south of here" }),
        "Just can't escapt it down here, can you?\n");
    try_item( ({ "moan", "moans", "sound", "sounds",
                 "sounds of the prison" }),
        "The sounds of the prison are those of sorrow.\n");
    try_item( ({ "grim illumination" }),
        "Yeah, and not the fun kind like the stuff from a jack-o"
      + "-lantern either.\n");
    try_item( ({ "jack-o-lantern" }),
        "No trick or treating here. Well, the orcs might like to"
      + " treat themselves to some tricks at your expense. Probably"
      + " the kind that involve your skin and their torches.\n");
    try_item( ({ "scene", "entire scene" }),
        "Like a horror movie, but with smells included.\n");
    try_item( ({ "horror movie" }),
        "Yeah, and you want your money back.\n");
    try_item( ({ "bend", "corner" }),
        "The corridor turns both west and south.\n");

    add_dungeon_items();
    add_jail_npcs(3);

    door = clone_object(DOORS_DIR + "2_cell_door");
    door->configure_cell_door("east");
    door->set_other_room(ROOMS_DIR + "2_cell5");
    door->move(this_object());

    add_exit("2_hall9", "west");
    add_exit("2_hall6", "south");

    set_no_exit_msg( ({ "north", "northeast", "southeast",
                        "south", "southwest", "northwest" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_dungeon_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
} /* init */
