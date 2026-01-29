/*
 *  /d/Sparkle/guilds/new_merc/rooms/lumber_pile.c
 *
 *  A non-obvious room in the northern parts of the Training Yard just
 *  west of the Mill in the Mercenary Camp in Sparkle.
 *
 *  Created May 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;


/* Prototypes */
public void        create_merc_room();
public void        add_outdoor_tells();
public void        init();
public int         try_climb(string arg);

/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("beside a huge lumber pile next to a mill");
    set_long("Huge amounts of lumber and chopped wood are piled up"
      + " along the side of an old sawmill here. This appears to be"
      + " a somewhat secluded area in the northern parts of the"
      + " training yard of the Mercenary Camp. The sights and sounds"
      + " of practice are all around you to the south and west, but this"
      + " area is not really used other than to store wood, it seems.\n\n");

    try_item( ({ "sight", "sound", "sights", "sounds",
                 "sights and sounds", "sights and sounds of practice",
                 "practice" }),
        "The real practice is taking place to the south, closer to the"
      + " lodge. You'll need to head that way to get a closer look.\n");
    try_item( ({ "side", "side of the mill", "wall of the mill",
                 "mill wall", "side of an old sawmill",
                 "wall of the sawmill" }),
        "The wall of the sawmill is covered to about half way by a large"
      + " pile of lumber here.\n");
    try_item( ({ "area", "secluded area" }),
        "This area is relatively private and quiet compared to the other"
      + " parts of the training yard.\n");
    try_item( ({ "training yard" }),
        "The training yard is all around you to the south and west.\n");
    try_item( ({ "individual", "rugged individual", "individuals",
                 "rugged individuals", "trainer", "trainers",
                 "weapon trainer", "weapon trainers",
                 "instructor", "instructors" }),
        "The trainers and their pupils are mostly off to the south"
      + " a bit, closer to the lodge.\n");
    try_item( ({ "east" }),
        "The mill rises directly to the east.\n");
    try_item( ({ "north", "clearcut", "clear-cut" }),
        "The river is just a short distance to the north.\n");
    try_item( ({ "east", "fence", "guarded fence" }),
        "A fence of criss-crossed sharpened poles has been placed along"
      + " the access route between the mill and the lodge just south"
      + " of here.\n");
    try_item( ({ "pole", "poles", "sharpened pole", "sharpened poles",
                 "criss-crossed poles", "criss-crossed sharpened poles",
                 "blockade", "route", "access route" }),
        "The fence clearly means business. No one is going through"
      + " that without first getting permission.\n");
    try_item( ({ "lawn", "wide lawn", "yard", "training yard",
                 "mercenary training yard", "training ground",
                 "training grounds" }),
        "These training grounds extend a ways to the north toward"
      + " the river and then curve around the lodge west and to the"
      + " south, where it appears as if various types of"
      + " training might be available.\n");
    try_item( ({ "south" }),
        "The old logging lodge which houses the Mercenaries rises"
      + " south of here, overlooking a weapon training area.\n");
    try_item( ({ "weapon training area" }),
        "Just to the south. You'll have to get closer for details.\n");
    try_item( ({ "bridge" }),
        "The bridge is not visible from here.\n");
    try_item( ({ "stump", "stumps" }),
        "The stumps are everywhere - this was clearly once a large"
      + " forest. Much of the training is happening on and around the"
      + " stumps, which the instructors are using as natural terrain"
      + " to faciliate various methods on uneven ground.\n");
    try_item( ({ "weapon", "weapons", "weaponry" }),
        "The Mercenaries seem to work with just about any weapon"
      + " type. You see all forms represented.\n");
    try_item( ({ "west" }),
        "To the west, the training yard extends toward the forest.\n");
    try_item( ({ "form", "forms", "all forms", "sword", "swords",
                 "axe", "axes", "club", "clubs", "polearm", "polearms",
                 "knife", "knives" }),
        "Swords, axes, clubs, polearms, knives ... yep, they all seem"
      + " to be present in the mix of things here.\n");
    try_item( ({ "mill", "sawmill", "old mill", "old sawmill",
                 "saw mill", "old saw mill" }),
        "The sawmill is just beside you here, to the east.\n");
    try_item( ({ "roof of the mill", "mill roof", "roof of the sawmill",
                 "sawmill roof" }),
        "The roof of the sawmill overhangs the pile of lumber just"
      + " overhead here.\n");
    try_item( ({ "lumber", "log", "logs", "pile", "pile of lumber",
                 "lumber pile", "huge amounts of lumber" }),
        "Much of the lumber is actually logs that have been chopped and"
      + " are presumably used by the Mercenary guild for firewood. At"
      + " the bottom of the pile are many layers of old discarded lumber"
      + " from the old days of the mill.\n");
    try_item( ({ "firewood", "chopped wood", "wood" }),
        "Some poor Mercenary probably has wood-chopping duty every"
      + " weekend.\n");
    try_item( ({ "bottom of the pile", "layer", "layers",
                 "discarded lumber", "old discarded lumber" }),
        "The lumber at the bottom of the pile looks to have lain here"
      + " for literally decades. There is a lot of moss growing on some"
      + " of the boards.\n");
    try_item( ({ "board", "boards", "old board", "old boards" }),
        "The old boards are covered in moss. Looks like the loggers"
      + " never got around to using them.\n");
    try_item( ({ "moss" }),
        "It covers some of the old boards at the bottom of the lumber"
      + " pile. One wonders how long these have been sitting here.\n");
    try_item( ({ "bug", "bugs", "insect", "insects" }),
        "They scurry like mad, don't they?\n");

    add_delay_cmd_item(
        ({ "pile", "lumber pile", "lumber", "wood", "chopped wood",
           "firewood", "board", "boards", "old board", "old boards",
           "bottom of the pile", "layer", "layers", "discarded lumber",
           "old discarded lumber" }),
        "search",
        "searching the lumber pile",
        10,
        "You begin searching around the lumber pile.\n",
        "Not much there. Just the usual bugs scurrying for cover as"
      + " you move boards that have rested in place for a long time.\n");

    add_river_view();
    add_outdoor_view();
    add_lodge_view();
    add_mill_view();

    add_exit("wep_train", "southwest", 0, 1, 1);

    set_no_exit_msg( ({ "northeast", "north", "northwest" }),
        "You wander through the many stumps of the training ground"
      + " to the edge of the river. Finding nothing of interest, you"
      + " return to the side of the mill.\n");
    set_no_exit_msg( ({ "west" }),
        "You wander among the stumps for a while, but don't find much"
      + " of interest, so you return to where you were.\n");
    set_no_exit_msg( ({ "south" }),
        "The fence blocks your movement in that direction.\n");
    set_no_exit_msg( ({ "east", "southeast" }),
        "The mill blocks your movement.\n");

} /* create_merc_room */


/*
 * Function name:        add_outdoor_tells
 * Description  :        mask the inherited one to provide unique
 *                       tells for this room
 */
public void
add_outdoor_tells()
{
    add_tell("A shout sounds to the south as a trainer leaps from a stump,"
      + " brandishing a " + one_of_list( ({ "large axe", "blunted sword",
        "sharp dagger", "heavy mace", "long spear" }) ) + " and forcing "
      + one_of_list( ({ "his", "her" }) ) + " pupil to yield.\n");
    add_tell("The clang of steel on steel sounds from the south.\n");
    add_tell("The sound of the river echoes out of a sudden stillness"
      + " on the training yard.\n");
    add_tell("Two combatants come into view, each trying to best the"
      + " other in a sparring match.\n");
} /* add_outdoor_tells */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(try_climb, "climb");
} /* init */


/*
 * Function name:        try_climb
 * Description  :        let players try to climb stuff
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
try_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (arg == "up" || arg == "down")
    {
        notify_fail("Climb " + arg + " what?\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[up] [down] [the] [water] 'wheel' / 'waterwheel'"))
    {
        notify_fail("The waterwheel is on the north side of the mill,"
          + " and can't be reached from here.\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[up] [down] [from] [the] [old] 'mill' / 'roof'"))
    {
        notify_fail("The roof is completely out of reach here.\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[up] [on] [upon] [to] [over] [the] [large] [lumber]"
      + " 'pile' / 'lumber' [of] [lumber] [pile]"))
    {
        write("You try to scramble up onto the lumber pile, but it is"
          + " just too uneven and slippery.\n");
        return 1;
    }

    notify_fail("You don't seem to be able to climb that.\n");
    return 0;
} /* try_climb */