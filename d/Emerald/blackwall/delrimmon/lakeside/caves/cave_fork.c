/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/caves/cave_fork.c
 *
 *  Deep within the western cliffs which border Del Rimmon in the
 *  Blackwall Mountains, a passage runs north and south here, offering
 *  an opening to the east.
 *
 *  Copyright (c) September 1998, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
void           create_del_rimmon();
public void    reset_room();


/*
 * function name:        create_del_rimmon
 * description  :        set up the room
 */
void
create_del_rimmon()
{
    set_short("a manmade passageway deep within the cliffsides of the"
            + " Blackwall Mountains");
    set_long(BSN("Roughly hewn corridors run both north and south from"
               + " here, trailing into the darkness in either direction."
               + " An emblem of some sort has been carved in the west"
               + " wall, directly facing a doorway which opens"
               + " onto a spacious chamber to the east."));

    add_item( ({"cliff", "cliffs", "cliffside", "cliffsides"}), BSN(
        "The cliffsides are not visible from these passageways,"
      + " which run through the rock of their foundations."));
    add_item( ({"corridor", "corridors", "hewn corridor",
                "hewn corridors", "roughly hewn corridor",
                "roughly hewn corridors", "passageway",
                "passageways", "manmade passageway",
                "manmade passageways"}), BSN(
        "The passageways look identical both to the north and the"
      + " south, where they travel for a distance before fading"
      + " into shadow."));
    add_item( ({"north passageway", "northern passageway",
                "north corridor", "northern corridor",
                "passageway to the north", "one to the north",
                "corridor to the north"}), BSN(
        "The northern passageway looks nearly identical to the one"
      + " to the south. It appears to run for a long distance,"
      + " perhaps rounding a bend after a ways. It is difficult"
      + " to see clearly."));
    add_item( ({"south passageway", "southern passageway",
                "south corridor", "southern corridor",
                "passageway to the south", "one to the south",
                "corridor to the south"}), BSN(
        "The passageway to the south is nearly identical to its"
      + " northern counterpart. It appears to run for a distance,"
      + " perhaps rounding a bend before it falls completely into"
      + " darkness."));
    add_item( ({"bend", "bend to the north", "bend to the south"}), BSN(
        "From this distance, only a faint hint down the long"
      + " passageway suggests that the corridor rounds a bend."));
    add_item( ({"shadow", "shadows", "dark", "darkness"}), BSN(
        "So deep within the cliffs, shadows are everywhere, making"
      + " it difficult to see very far in any one direction."));
    add_item( ({"wall", "walls"}), BSN(
        "The walls of these passageways have been closely hewn from"
      + " the stone of the cliffs. They are rough, and yet even,"
      + " suggesting that the skilled hands which formed them had"
      + " little time for embellishment."));
    add_item( ({"stone", "stone of the cliffs", "rock",
                "stone walls", "rock walls", "stone wall",
                "rock wall"}), BSN(
        "The stone which makes up the walls of these corridors"
      + " has been evenly carved with careful strokes."));
    add_item( ({"stroke", "strokes", "careful stroke", 
                "careful strokes"}), BSN(
        "The strokes do not appear masterful enough to suggest"
      + " Dwarven work. This looks more like the tunneling of Men."));
    add_item( ({"west", "west wall"}), BSN(
        "The west wall appears to have been hewn with the same"
      + " careful strokes which mark the rest of this corridor. It"
      + " is, however, distinguished by a circular emblem which"
      + " has been engraved in the stone."));
    add_item( ({"stain", "dark stain", "stains"}), BSN(
        "The stain looks to be relatively fresh, and is perhaps"
      + " little more than mud. It is roughly fashioned in the"
      + " shape of a hand."));
    add_item( ({"hand", "shape of a hand"}), BSN(
        "Whoever created this stain was not much of an artist, yet"
      + " the impression of a hand is certainly visible."));
    add_item( ({"east wall", "door", "doorway"}), BSN(
        "The east wall of this passageway frames a doorway in the"
      + " stone, which opens onto a much larger chamber."));
    add_item( ({"east", "chamber", "spacious chamber", "large chamber",
                "much larger chamber", "chamber to the east",
                "eastern chamber", "spacious chamber to the east"}), BSN(
        "A vast and spacious chamber lies through a doorway in the"
      + " eastern wall. Little of the chamber can be seen in the"
      + " intense darkness."));
    add_item( ({"intense darkness"}), BSN(
        "The chamber through the eastern doorway is completely"
      + " embedded in darkness. Little can be seen from here."));
    add_item( ({"floor", "ground"}), BSN(
        "The ground here has been hewn with the same careful strokes"
      + " which mark the walls. It runs evenly to the north and south."));
    add_item( ({"roof", "ceiling"}), BSN(
        "The roof of this corridor is somewhat low, and bears the same"
      + " markings of toil which adorn the walls and floor."));
    add_item( ({"marking", "markings", "marking of toil",
                "markings of toil"}), BSN(
        "The work which went into the creation of these passages must"
      + " have been laborious, indeed."));
    add_item( ({"sky", "sun", "moon"}), BSN(
        "The sky is not visible from within this deep passageway."));
    add_item( ({"mud", "mud stain"}), BSN(
        "The stain does seem to be mud which has been wiped on the"
      + " emblem, though it could also be other, less pleasant"
      + " substances."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(DELRIMMON_DIR + "lakeside/caves/large_room", "east");
    add_exit(DELRIMMON_DIR + "lakeside/caves/s_cave", "south");
    add_exit(DELRIMMON_DIR + "lakeside/caves/n_cave", "north");

    set_no_exit_msg( ({ "west", "northwest", "northeast",
                        "southwest", "southeast" }),
        "You run up against the walls of the corridor.\n");

    reset_room();
} /* create_del_rimmon */


/*
 * Function name:        reset_room
 * Description  :        Called when the room is updated. Here, we
 *                       add the emblem to the door, if it is not
 *                       already there.
 */
public void
reset_room()
{
    object  emblem;

    if (!present("kot_emblem"))
    {
        emblem = clone_object(DELRIMMON_DIR + "obj/normal_emblem");
        emblem->set_emblem(
            "Unlike the strokes which seem to have carved the walls of"
          + " this corridor, great care has gone into the making of"
          + " this emblem in the stone. It depicts the symbol of"
          + " Telberin - a four-pointed star within a circular band."
          + " A dark stain of some sort marrs the emblem.");
        emblem->set_stained();
        emblem->move(this_object());
    }
} /* reset_room */
