/*
 *  /d/Sparkle/area/orc_temple/1_barracks2.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 1.
 *
 *  Created June 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <macros.h>   /* for QCTNAME */
#include "../defs.h"

inherit ROOMS_DIR + "dungeon_room";


/* Prototypes */
public void         create_dungeon_room();
public int          do_smell(string arg);
public void         init();


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    set_short("a large chamber within the dungeons");
    set_long("What a ... terrible! ... smell! This appears to be"
      + " a barracks for orcs. Filth and debris are strewn throughout"
      + " this large chamber which spreads out to the south.\n\n");

    try_item( ({ "smell", "terrible smell" }),
        "It's worse than lutefisk!\n");
    try_item( ({ "lutefisk" }),
        "There isn't any, and this is worse!\n");
    try_item( ({ "arch", "archway", "low arch", "low archway" }),
        "It is at the south end of the chamber.\n");
    try_item( ({ "chamber", "large chamber" }),
        "If you had to guess, you'd have to assume this is a barracks"
      + " for the orcs who exist here.\n");
    try_item( ({ "orc", "orcs" }),
        "You don't have to look far for them down here!\n");
    try_item( ({ "barrack", "barracks" }),
        "This is where the orcs must eat and sleep. Of course, because"
      + " of this, it is the LAST place most people would choose to do"
      + " either.\n");
    try_item( ({ "filth" }),
        "Use your imagination. Looking too close might result in"
      + " very ill-health.\n");
    try_item( ({ "debris" }),
        "Are these ... beds? One presumes so, but they look more like"
      + " an unhappy marriage of rotting straw and oily fabric.\n");
    try_item( ({ "rotting straw", "straw" }),
        "If there is a hell for bedding, this is it.\n");
    try_item( ({ "bedding" }),
        "Sort of.\n");
    try_item( ({ "fabric", "oily fabric" }),
        "Even for bed bugs, a sign should be posted that states: Abandon"
      + " All Hope, Ye Who Enter Here!\n");
    try_item( ({ "bed", "beds" }),
        "You are being too generous. These things? Beds? Do you also"
      + " consider an outhouse a swimming hole?\n");
    try_item( ({ "bug", "bugs", "bed bug", "bed bugs" }),
        "They are all dead. Worse than dead.\n");
    try_item( ({ "roach", "roaches" }),
        "Evidently, it is true what they say about roaches. If this"
      + " is any evidence, they really CAN survive anything!\n");

    add_cmd_item( ({ "here", "bed", "beds", "in bed", "in beds",
                     "debris", "in debris", "on bed", "on beds",
                     "on debris" }),
                  ({ "sleep", "lie", "rest", "lay" }),
        "That would be akin to snuggling up with a pile of used"
      + " toilet paper. The mere thought triggers a gag-reflex of the"
      + " soul.\n");

    add_delay_cmd_item(
        ({ "bed", "beds", "debris", "bedding", "fabric", "oily fabric",
           "straw", "rotting straw" }),
        "search",
        "searching around in the debris",
        10,
        "You begin poking around in the debris.\n",
        "Every time you lift something new, another dozen roaches"
      + " scurry for cover. There is nothing of value here - QUITE"
      + " the opposite, in fact!\n");

    add_delay_cmd_item(
        ({ "filth", }),
        "search",
        "searching through some nearby filth",
        10,
        "Tempting fate, you begin searching through some nearby filth.\n",
        "Ohhhh .... OHHHHHHH! THE HORROR! THE HORRRRRRRRORRRRRR!\n\n"
      + "You fall to your knees and pray to your Gods that you could"
      + " please be allowed to unsee what you have just ... seen.\n");

    add_dungeon_items();
    add_npc(NPC_DIR + "goblin_runt", 5 + (random(4)), &->arm_me());

    add_exit("1_barracks1", "south");

    set_no_exit_msg( ({ "north", "east", "west" }),
        "You boldly stroll directly into a wall. OOOF!\n");
    set_no_exit_msg( ({ "northeast", "southeast", "southwest",
                        "northwest" }),
        "You scout the perimeter of the room, but don't find any way"
      + " forward in that direction.\n");
} /* create_dungeon_room */


/*
 * Function name:        do_smell
 * Description  :        allow players to ... enjoy? ... the aroma here.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_smell(string arg)
{
    if (!strlen(arg))
    {
        write("You inhale deeply ...\n");
        say(QCTNAME(this_player()) + " inhales deeply.\n");
        this_player()->command("$choke");
        this_player()->command("$puke");
        write(" ... too ... deeply!\n");

        return 1;
    }

    notify_fail("You don't need to " + query_verb()
      + " anything in particular, just"
      + " the simple command will tell you all you need to know by"
      + " itself!\n");
    return 0;
} /* do_smell */


/*
 * Function name:        init
 * Description  :        add actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_smell, "smell");
    add_action(do_smell, "inhale");
    add_action(do_smell, "sniff");
} /* init */