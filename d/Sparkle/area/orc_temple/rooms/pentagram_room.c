/*
 *  /d/Sparkle/area/orc_temple/pentagram_room.c
 *
 *  This is the master file for cell rooms on the priest level (level 3)
 *  of the orc dungeons near Sparkle.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <filepath.h>
#include <stdproperties.h>
#include <time.h>
#include "../defs.h"
#include "/d/Sparkle/sys/quests.h"

inherit ROOMS_DIR + "dungeon_room";

/* Global Variables */
public string       Side = "";
public string       Extraline = "";


/* Prototypes */
public nomask void  create_dungeon_room();
public void         create_pentagram_room();
public void         add_dungeon_tells();
public string       exit_blocked_hook(object guard);

public void         set_side(string s) { Side = s; }
public void         set_extraline(string s) { Extraline = s + " "; }


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public nomask void
create_dungeon_room()
{
    create_pentagram_room();

    set_short("the " + Side + "ern end of a vast candle-lit chamber");
    set_long("You stand at the " + Side + "ern end of a vast chamber. The"
      + " eerie glow of thousands of candles dances off the low"
      + " ceiling. " + Extraline + "A feeling of"
      + " intense dread is burrowing into your mind.\n\n");

    try_item( ({ "chamber", "large chamber", "vast chamber", "open chamber",
                 "large open chamber", "vast open chamber",
                 "large vast open chamber", "large, vast open chamber",
                 "candle-lit chamber", "candle lit chamber",
                 "vast candle-lit chamber", }),
        "This chamber is enormous, taking up most of this level of"
      + " the dungeons. A feeling of horror fills the every corner"
      + " of this place.\n");
    try_item( ({ "horror", "dread", "intense dread", "feeling",
                 "feeling of horror", "feeling of dread",
                 "feeling of intense dread" }),
        "As you search your own mind for the source of your feelings,"
      + " a terrible whispering pierces your consciousness: Yog ... So"
      + " ... Thoth ...\n");
    try_item( ({ "yog ... so ... thoth", "yogsothoth",
                 "yog-so-thoth", "yog so thoth" }),
        yogsothoth);
    try_item( ({ "whisper", "whispering", "terrible whispering" }),
        "Yog ... Sa ... Thoth ...\n");
    try_item( ({ "glow", "eerie glow" }),
        "Shadows stretch and bend in the unnatural illumination.\n");
    try_item( ({ "shadow", "shadows" }),
        "The shadows almost appear alive, dancing in the eerie glow.\n");
    try_item( ({ "illumination", "unnatural illumination" }),
        "Creepy. Worse than creepy.\n");
    try_item( ({ "low ceiling", "ceiling" }),
        "The ceiling flutters with shadows.\n");
    try_item( ({ "candle", "candles", "thousands of candles",
                 "down", "floor", "ground" }),
        "Candles have been used to create a colossal pentagram upon"
      + " the floor of this chamber.\n");
    try_item( ({ "pentagram", "colossal pentagram" }),
        "The pentagram fills the chamber, which even the most unlearned"
      + " person would now recognize as a huge summoning circle.\n");
    try_item( ({ "summoning circle", "circle",
                 "huge circle", "huge summoning circle" }),
        "Summoning circles are usually no more than a few yards in"
      + " diameter, as most sorcerors would not dare summon anything more"
      + " powerful than a lesser demon. To summon a greater demon is"
      + " tantamount to suicide, but even such a foolish act as that"
      + " would not require a focal point of this degree."
      + " The size of this chamber suggests"
      + " that the orcs here are playing with unholy forces beyond"
      + " imagining!\n");
    try_item( ({ "point", "points", "two points", "one point",
                 "point of the pentagram", "points of the pentagram",
                 "two points of a pentagram", "point of a pentagram",
                 "points of a pentagram", "five points" }),
        "The pentagram has five points at which the star touches the"
      + " circle that surrounds it.\n");
    try_item( ({ "star", "great star" }),
        "The great star within the pentagram has five points that"
      + " stretch outward to touch the surrounding circle.\n");
    try_item( ({ "circle", "surrounding circle" }),
        "The circle surrounds a great star, completing the form of"
      + " the pentagram.\n");
    try_item( ({ "form", "form of the pentagram" }),
        "It is a disquieting sight, indeed.\n");

    add_cmd_item( ({ "demon", "yog sothoth", "yog-sothoth" }),
                  ({ "summon" }),
        "You have no authority over the powers within this circle.\n");

    add_dungeon_items();

    add_npc(NPC_DIR + "goblin_priest", 2 + random(3), &->arm_me());
} /* create_dungeon_room */


/*
 * Function name:        create_pentagram_room
 * Description  :        dummy routine to be used by inheriting
 *                       files
 */
public void
create_pentagram_room()
{
} /* create_pentagram_room */


/*
 * Function name:        add_dungeon_tells
 * Description  :        Provide room tells that are ubiquitous to
 *                       rooms in the dungeon
 *
 * Can be masked if these room tells are not desired for a given room.
 */
public void
add_dungeon_tells()
{
    add_tell("Shadows dance along the low ceiling.\n");
    add_tell("A distant shuffling echoes throughout the chamber.\n");
    add_tell("The flames of the candles flutter in a sudden"
      + " unnatural breeze, dim, and then return to normal.\n");
    add_tell("The chamber shakes suddenly, and you hear a deep"
      + " and distant moan from somewhere beneath the floor.\n");
    add_tell("The back of your neck prickles as a sense of"
      + " deep and unnatural fear creeps over you.\n");
    add_tell("Some low, stooping forms move at the far end of the"
      + " chamber.\n");
    add_tell("An unnatural breeze tugs suddenly at your clothing.\n");
    add_tell("A nearby torch flickers in a sudden breeze, and then"
      + " flares back to life.\n");
} /* add_dungeon_tells */


/*
 * Function name:        exit_blocked_hook
 * Description  :        provide a message that can be customized
 *                       when an npc blocks the path moving in a given
 *                       direction in the dungeons.
 * Arguments    :        object guard - the npc blocking the path
 * Returns      :        string - the message
 */
public string
exit_blocked_hook(object guard)
{
    return "The " + guard->short() + " steps swiftly in front of you,"
      + " saying: Not approach pit without blessing"
      + " of High Priest!\n";
} /* exit_blocked_hook */