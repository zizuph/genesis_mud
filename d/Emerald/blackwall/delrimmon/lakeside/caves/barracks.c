/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/caves/barracks.c
 *
 *  This room once housed the many soldiers from Telberin who
 *  were garrisoned at Del Rimmon. The bed lofts still remain,
 *  as does a firepit that used to warm the soldiers in their
 *  times of repose. Orcs have recently made the place their
 *  home.
 *
 *  Copyright (c) November 1998, by Cooper Sherry (Gorboth)
 *
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/legacy/fireplace";
inherit "/d/Emerald/blackwall/delrimmon/legacy/room_chairs";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "/d/Emerald/blackwall/delrimmon/legacy/room_chairs.h"
#include "/d/Emerald/blackwall/delrimmon/legacy/fireplace.h"

/* prototypes */
public void    create_del_rimmon();
public void    reset_room();
public void    init();
public string  fire_desc(string arg);  /* VBFC for fire descriptions */
public int     check_exit();
public int     do_sit(string arg);
public void    do_sit_msgs(object pl, string prep, string name);
public void    do_stand_msgs(object pl, string name);
public string  look_block();
public void    leave_inv(object ob, object dest);

/* definitions */
#define    NPC_FILE        (DELRIMMON_DIR + "npc/del_rimmon_orc")
#define    BLOCK_NAME      "block of stone"

/* global variables */
object  *Npcs = allocate(5 + random(3));

/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room.
 */            
public void
create_del_rimmon()
{
    set_short("a wide and ancient chamber, hewn from the rock");
    set_long(fire_desc);    /* use VBFC for room description */

    add_chair(BLOCK_NAME, "[down] [on] [the] [stone]"
                        + " 'block' / 'blocks' [of] [stone]", 3);
    set_fire_container("firepit");
    /* set the pattern for the parse_command() */
    set_parse_pattern("[the] [shallow] 'firepit'");

    add_item( ({ "cavein", "cave in" }),
        "A cave in seems to have blocked the exit to the west. This seems"
      + " to have happened recently.\n");
    add_item( ({ "firepit", "pit", "shallow pit",
                 "shallow firepit" }), &fire_desc("firepit"));
    add_item( ({ "fire", "flame", "flames" }), &fire_desc("fire"));
    add_item( ({ "wood", "firewood", "wood in firepit",
                 "firewood in firepit", "wood in pit",
                 "firewood in pit" }),
        &fire_desc("wood"));
    add_item( ({ "ash", "ashes", "ash in firepit",
                 "ashes in firepit", "ash in pit",
                 "ashes in pit" }),
        &fire_desc("ashes"));
    add_item( ({"wall", "walls", "roughly hewn wall",
                "roughly hewn walls", "rough wall", "rough walls",
                "chamber walls", "walls of the chamber"}), BSN(
        "The walls of this room expand from the center to form a wide"
      + " perimeter on all sides. Alcoves are visible in the wall"
      + " to the north, which is very long, and steeped in shadow."));
    add_item( ({"center", "center of the room"}), BSN(
        "The center of the room is littered with trash and filth,"
      + " which is quite obviously a recent addition to this"
      + " chamber."));
    add_item( ({"room", "chamber"}), long() );
    add_item( ({"perimeter", "side", "sides", "perimeters",
                "wide perimeter"}), BSN(
        "The chamber is rectangular, with the northern and"
      + " southern walls making up a much longer surface than"
      + " those to the west and east."));
    add_item( ({"north", "north wall", "wall to the north",
                "northern wall"}), BSN(
        "The wall to the north is long, running perhaps fifty"
      + " feet from end to end. It is distinguished by many"
      + " alcoves which have been carved in its stone surface."));
    add_item( ({"stone", "stone surface", "rock", "surface",
                "surfaces", "surface of the wall",
                "surface of the walls"}), BSN(
        "The surface of the walls is rough, having been hewn"
      + " with great skill long ago from the rock of the cliffs."));
    add_item( ({"rock of the cliffs", "cliffs", "cliff"}), BSN(
        "The cliffs are not visible, but the rock which comprises"
      + " their foundation is all about you here."));
    add_item( ({"west wall", "western wall", "wall to the west",
                "west"}), BSN(
        "The wall to the west is marked by a doorway which"
      + " extends into darkness."));
    add_item( ({"south", "southern wall", "south wall",
                "wall to the south"}), BSN(
        "The wall to the south is very long, running fifty feet"
      + " at least in length. A doorway is has been carved into"
      + " the wall, leading into darkness."));
    add_item( ({"doorway", "doorways", "passage", "door",
                "passages"}), BSN(
        "There are three exits from this room. One to the west,"
      + " one to the south, and one to the northeast."));
    add_item( ({"east", "east wall", "eastern wall",
                "wall to the east"}), BSN(
        "The wall to the east is marked by a passageway at its"
      + " northern end which leads into darkness. A large stack"
      + " of firewood rests against its stone surface."));
    add_item( ({"alcove", "alcoves"}), BSN(
        "Many shallow rectangular slots have been carved in the"
      + " stone of the northern wall. They are arranged in"
      + " columns of five high, and there are seven columns for"
      + " a total of thirty-five slots."));
    add_item( ({"slot", "slots"}), BSN(
        "Each slot is approximately three feet high, three feet"
      + " deep, and six feet long. Some of the slots contain"
      + " some very old pieces of cloth."));
    add_item( ({"piece of cloth", "pieces of cloth",
                "cloth", "old cloth", "very old cloth",
                "very old piece of cloth", "old piece of cloth",
                "old pieces of cloth", "very old pieces of cloth"}),
    BSN("It would seem that these ancient pieces of cloth are"
      + " old bedrolls, perhaps used at one time to cover a sleeping"
      + " occupant."));
    add_item( ({"bedroll", "bedrolls", "old bedroll",
                "old bedrolls"}), BSN(
        "They indeed do seem to be bedrolls. Perhaps this was once"
      + " some form of barracks?"));
    add_item( ({"column", "columns"}), BSN(
        "The columns are spaced roughly three feet from one another,"
      + " and cover the entirety of the northern wall."));
    add_item( ({"southwest corner", "southwest", "corner",
                "southwestern corner",
                "southwest corner of the chamber",
                "southwestern corner of the chamber"}), BSN(
        "The southwestern corner of the chamber is marked by a"
      + " depression in the ground, which is surrounded by large"
      + " blocks of stone. A firepit rests in the depression."));
    add_item( ({"depression", "depression in the ground"}), BSN(
        "The floor has been dug out somewhat in the southwest"
      + " corner of the chamber, where a firepit has been set up."));
    add_item( ({"ground", "floor", "floor of the chamber",
                "chamber floor"}), BSN(
        "The floor of the chamber is covered with filth and"
      + " refuse, especially towards the center where a large"
      + " pile of filth is strewn. The floor is relatively flat,"
      + " except in the southwestern corner, where a depression"
      + " has been excavated to house a firepit."));
    add_item( ({"block", "blocks", "block of stone",
                "blocks of stone", "stone block",
                "stone blocks", "large blocks", "large block",
                "large block of stone", "large blocks of stone" }),
                look_block);
    add_item( ({"ceiling", "roof", "ceiling of the room",
                "ceiling of the chamber", "up"}), BSN(
        "The ceiling of this chamber is relatively far from"
      + " the ground, rising perhaps twenty feet from the"
      + " ground near the northern wall, where it is at"
      + " its greatest height."));
    add_item( ({"sky", "sun", "moon", "star", "stars"}), BSN(
        "The sky is not visible from these caverns within"
      + " the cliffs."));
    add_item( ({"trash", "filth", "debris", "pile", "piles",
                "pile of debris", "pile of filth",
                "pile of trash", "piles of debris",
                "piles of filth", "piles of trash"}), BSN(
        "It would seem that some recent inhabitants have taken"
      + " it upon themselves to defile this ancient chamber with"
      + " all sorts of wretched filth."));
    add_item( ({"wretched filth"}), BSN(
        "Most of the filth is not worth investigating up close. It"
      + " all smells quite horrifying."));
    add_item( ({"shadow", "shadows", "dark", "darkness"}), BSN(
        "Darkness fills the corners of this chamber, blanketing"
      + " the stone with its dim haze."));
    add_item( ({"corner", "corners"}), BSN(
        "The corners of the chamber are covered in darkness. A"
      + " firepit rests in the southeastern corner, however."));

    add_cmd_item( ({"slot", "slots", "alcove", "alcoves"}),
                  ({"enter", "crawl", "lie", "lie in"}), BSN(
        "You notice that the slots are very filthy, having been"
      + " used over the centuries by cave-dwelling vermin and other"
      + " beasts. You decide not to try it."));
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);

    set_dark_room_ok(1);

    set_fire_state(FIRE_BURNING);

    add_exit(DELRIMMON_DIR + "lakeside/caves/s_cave", "northeast");
    add_exit(DELRIMMON_DIR + "lakeside/caves/store_room", "south",
             check_exit);
    add_exit(DELRIMMON_DIR + "lakeside/caves/ante_room", "west", check_exit);

    set_no_exit_msg( ({ "northwest", "north" }),
        "You wander along the alcoves, but find no way to pass in"
      + " that direction.\n");
    set_no_exit_msg( ({ "southwest" }),
        "You move toward the firepit, but find that you cannot travel"
      + " in that direction.\n");
    set_no_exit_msg( ({ "east", "southeast" }),
        "You wander along the eastern side of the room, but find"
      + " nothing of interest there.\n");
//  set_no_exit_msg( ({ "west" }),
//      "A cave in has temporarily blocked the exit west.\n");


    reset_room();
} /* create_room */

/*
 * Function name:        reset_room
 * Description  :        replenish the firewood and the fire
 */
public void
reset_room()
{
    /* get some orcs if they aren't already here */
    clone_npcs(Npcs, NPC_FILE, 0.0);

    /* reset wood to default amount */
    set_wood(-1);

    /* if fire's gone out and the orcs are around to rekindle it,
     * start it up again.
     */
    if (query_fire_state() != FIRE_BURNING &&
        present("orc", this_object()))
    {
        tell_room(TO,
            BSN("One of the orcs tosses some fresh wood in the"
              + " firepit and sets it ablaze."));
        set_fire_state(FIRE_BURNING);
/* XXX How to differentiate if there is only one orc here? */
    }
} /* reset_room */

/*
 * Function name:        init
 * Description  :        call init_fire() to add fireplace verbs
                         also, init the room chairs
 */
public void
init()
{
    ::init();
    init_fire();
    init_room_chairs();
} /* init */

/*
 * Function name:        fire_desc
 * Description  :        VBFC for room and items that vary w/ fire
 * Arguments    :        string arg -- what we're looking at
 * Returns      :        string description
 */
public string
fire_desc(string arg)
{
    int fire_state = query_fire_state();

    switch (arg)
    {
        case "firepit":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return BSN("A shallow firepit rests in a"
                             + " depression in the southwestern"
                             + " corner of this chamber which is"
                             + " surrounded by large blocks of stone."
                             + " A fire"
                             + " burns brightly in the pit, casting"
                             + " a flickering light over the room.");
                case FIRE_UNLIT_WOOD:
                    return BSN("A shallow firepit rests in a"
                             + " depression in the southwestern"
                             + " corner of this chamber which is"
                             + " surrounded by large blocks of"
                             + " stone. Firewood"
                             + " is stacked in the pit.");
                default:        /* FIRE_ASHES */
                    return BSN("A shallow firepit rests in a"
                             + " depression in the southwestern"
                             + " corner of this chamber which is"
                             + " surrounded by large blocks of"
                             + " stone.");
            }

        case "fire":
            if (fire_state == FIRE_BURNING)
            {
                return BSN("A fire burns brightly in the firepit.");
            }
            return BSN("You find no fire.");

        case "wood":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return BSN("The wood in the firepit burns"
                             + " brightly, emitting a pleasant"
                             + " warmth.");
                case FIRE_UNLIT_WOOD:
                    return BSN("Unlit wood is piled in the"
                             + " firepit.");
                default:    /* FIRE_ASHES */
                    return BSN("You find no firewood.");
            }

        case "ashes":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return BSN("Beneath the brightly burning fire,"
                             + " ashes cover the bottom of the"
                             + " firepit.");
                case FIRE_UNLIT_WOOD:
                    return BSN("Beneath the wood, ashes cover the"
                             + " bottom of the firepit.");
                default:    /* FIRE_ASHES */
                    return BSN("Ashes cover the bottom of the"
                             + " firepit.");
            }

        default:    /* room long description */
            if (fire_state == FIRE_BURNING)
            {
                return BSN("Long roughly hewn walls expand to form"
                         + " the perimeters of this large chamber."
                         + " A dull flickering from flames in the"
                         + " southwest corner of the room cast long"
                         + " shadows along the floor and up against"
                         + " the alcoves which reside in the northern"
                         + " wall.");
            }
            return BSN("Long, roughly hewn walls expand to form the"
                     + " perimeter of this large chamber. Shadows"
                     + " extend into the darkness, dimly revealing"
                     + " alcoves in the northern wall which face a"
                     + " firepit in the southwestern corner of the"
                     + " room.");
    }
    return "";  /* "cannot" happen */
} /* fire_desc */

/*
 * Function name:    check_exit
 * Description  :    if the orcs are in the room, they will not let
 *                   players they can see into certain rooms
 * Returns      :    0 -- the player gets through
 *                   1 -- the player is blocked
 */
public int
check_exit()
{
    object  block = present("_blackwall_orc", this_object());
    string  npc = block->query_nonmet_name();

    if (!objectp(block))
    {
        return check_sitting();
    }

    if (!CAN_SEE_IN_ROOM(block) || !CAN_SEE(block, TP))
    {
        return check_sitting();
    }

    if (TP->id("_blackwall_orc"))
    {
        return check_sitting();
    }

    TP->catch_msg(BSN("The " +npc+ " steps in front of you,"
      + " saying: You aren't going anywhere, "
      + TP->query_race_name() + "!"));
    say(QCTNAME(block) + " stops " + QCTNAME(TP) + " from going"
      + " any further.\n", ({TP, block}));
    return 1;
} /* check_exit */


/*
 * Function name:       do_sit
 * Description  :       mask parent to block "sit" and "sit down"
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 on success, 0 on failure
 */
public int
do_sit(string arg)
{
    if (!arg ||
        arg == "down")
    {
        NF0("Sit on what?\n");
    }
    return ::do_sit(arg);
} /* do_sit */

/*
 * Function name:       do_sit_msgs
 * Description  :       mask parent so the block msgs look right
 * Arguments    :       object pl -- the person who's sitting
 *                      string prep -- the preposition
 *                      string name -- the name of the chair
 */
public void
do_sit_msgs(object pl, string prep, string name)
{
    write("You climb over the stone block and sit down.\n");
    SAY(" climbs over the stone block and sits down.");
} /* do_sit_msgs */

/*
 * Function name:       do_stand_msgs
 * Description  :       mask parent so the block msgs look right
 * Arguments    :       object pl -- the person who's standing
 *                      string name -- the name of the chair
 */
public void
do_stand_msgs(object pl, string name)
{
    write("You stand up from the stone block.\n");
    SAY(" stands up from the stone block.");
} /* do_stand_msgs */

/*
 * Function name:        look_block
 * Description  :        VBFC for block; include occupants
 * Returns      :        string -- the desc
 */
public string
look_block()
{
    return    "The blocks of stone are shaped in such a way as to"
         + " make them comfortable to sit upon. Hewn very much"
         + " in the manner of the walls of this chamber, it"
         + " may be that they are just as old. They are arranged"
         + " arround the firepit.\n"
         + sitting_on_chair(BLOCK_NAME, TP, 0, 1);
} /* look_block */

/*
 * Function name:       leave_inv
 * Description  :       mask parent to be sure that departing players
 *                      are removed from block occupants
 * Arguments    :       object ob -- the departing object
 *                      object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand.
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */
