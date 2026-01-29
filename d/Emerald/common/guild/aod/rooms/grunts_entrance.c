/*
 *  /d/Emerald/common/guild/aod/rooms/grunts_entrance.c
 *
 *  This room connects the lower area of the Ogre guild to the
 *  entrance to the Grunts guild. Ogres love goblins, so this
 *  is a natural fit.
 *
 *  Created March 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/d/Emerald/std/room";

#include <macros.h>


/* Prototypes */
public void        create_emerald_room();


/* 
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("beneath the cliffs of the blackwall mountains");
    set_em_long("The dark peaks of the Blackwall mountains rise sheer"
      + " and bleak before you, blocking out all view to the north."
      + " A track runs west here to join with a larger pathway in"
      + " that direction. The track stops here before a small"
      + " hole in the cliffs.\n");

    add_item( ({ "hole", "small hole", "hole in the cliffs",
                 "small hole in the cliffs" }),
        "The hole is completely strewn with unspeakable filth!\n");
    add_item( ({ "unspeakable filth" }),
        "Yes, unspeakable! The smell speaks for itself!\n");
    add_item( ({ "smell" }),
        "Lets just say the responsible party doesn't believe in"
      + " using a toilet.\n");
    add_item( ({ "track", "small track" }),
        "The track is strewn with filth. Whoever uses this track must"
      + " have no use for cleanliness.\n");
    add_item( ({ "filth" }),
        "Err ... yes. The things you see along the track are disgraceful"
      + " to say the least. To put it bluntly, someone is pooping a lot"
      + " here for some reason.\n");
    add_item( ({ "poop", "shit", "crap" }),
        "Yes, exactly.\n");

    add_item( ({ "forest", "wood", "woods" }),
        "To the southwest, the forest grows thickly. Here, however, it"
      + " has been all but obliterated. Trees lie twisted and mangled"
      + " upon the ground on all sides of the path.\n");
    add_item( ({ "tree", "trees" }),
        "Something has torn them apart. Something really REALLY"
      + " strong!\n");
    add_item( ({ "peak", "peaks", "dark peak", "dark peaks",
                 "dark peaks of the blackwall mountains", 
                 "dark peaks of the mountains" }),
        "They seem to glower down at you.\n");
    add_item( ({ "view", "view to the north" }),
        "There isn't much of one, unless you like staring at"
      + " walls of stone.\n");
    add_item( ({ "stone" }),
        "The walls to the north are made of it. Yep.\n");
    add_item( ({ "wall of stone", "walls of stone" }),
        "There they are, staring right back at you.\n");
    add_item( ({ "sky", "up" }),
        "Even the sky looks a bit darker here. This place is"
      + " not a friend to the followers of light.\n");
    add_item( ({ "dark", "darkness", "heavy darkness" }),
        "It is thick here.\n");
    add_item( ({ "light" }),
        "What light there is is heavily muted by the darkness.\n");
    add_item( ({ "path", "trail", "road", "wide path" }),
        "It is a ways to the west.\n");
    add_item( ({ "footprint", "footprints", "prints" }),
        "Huge and terrifying!\n");
    add_item( ({ "slope", "steep slope" }),
        "It travels directly into the heart of the mountains.\n");
    add_item( ({ "mountain", "mountains", "blackwall mountains" }),
        "They tower above you directly to the north. There is a"
      + " heavy darkness hanging over them.\n");
    add_item( ({ "heart of the mountain", "heart of the mountains" }),
        "There appears to be some dark force at work up there.\n");
    add_item( ({ "force", "dark force" }),
        "One can only imagine what it might be.\n");

    add_exit("/d/Emerald/common/guild/aod/rooms/lower_ground",
             "west");

    set_no_exit_msg( ({ "northeast", "north", "northwest" }),
        "You walk a bit along the base of the mountains, but soon"
      + " return to where you were.\n");
    set_no_exit_msg( ({ "east", "southeast", "south", "southwest" }),
        "The woods are too dense in that direction to proceed.\n");

    add_npc(AOD_NPC_DIR + "aod_ogre", 1);
} /* create_emerald_room */


/*
 * Function name:        enter_hole
 * Description  :        allow players to try to enter the hole
 * Arguments    :        string arg - what was typed after the
 *                                    verb
 * Returns      :        1 - success, 0 - failure
 */
public int
enter_hole(string arg)
{
    string  hole_room = "/d/Emerald/common/guild/grunts/room/"
                      + "secret_passage1b";

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[in] [to] [into] [the] [small] 'hole' [in] [the] [cliff]"
      + "[cliffs]"))
    {
        notify_fail("What do you want to " + query_verb() + "?\n");
        return 0;
    }

    switch (this_player()->query_race_name())
    {
        case "ogre":
            notify_fail("You couldn't even fit your left foot in"
              + " that hole!\n");
            break;
        case "hobbit":
            notify_fail("You're small enough, but you're far too"
              + " fat! Maybe you shouldn't have spent your whole"
              + " life eating second breakfast!\n");
            break;
        case "kender":
            notify_fail("Eeeks! No fascinating object in the world"
              + " is worth braving this filth for! No thanks!\n");
            break;
        case "dwarf":
            notify_fail("You're short enough, but not thin enough"
              + " to enter the hole. You could do without coating"
              + " your shoulders in that filth, anyhow.\n");
            break;
        case "goblin":
        case "orc":
        case "half-orc":
            write("You slither through the filth and drop down"
              + " through the small hole.\n");
            tell_room(hole_room, QCTNAME(this_player())
              + " suddenly crashes through the pile of ashes and"
              + " lands on the floor, splattering the area with"
              + " dust and filth.\n");
            this_player()->move_living("M", hole_room, 1, 0);
            tell_room(this_object(), QCTNAME(this_player())
              + " slithers through the filth surrounding the small"
              + " hole in the cliffs and disappears.\n");

            return 1;
            break;
        default:
            notify_fail("Even if you could fit into the hole (which"
              + " looks more goblin-sized than anything,) you most"
              + " certainly wouldn't want to have to push your way"
              + " past all the filth that coats its sides.\n");
            break;
    }

    return 0;
} /* enter_hole */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(enter_hole, "enter");
    add_action(enter_hole, "climb");
    add_action(enter_hole, "crawl");
    add_action(enter_hole, "slither");
} /* init */
