/*
 *  /d/Sparkle/guilds/mercs/room/gnimpsh_room.c
 *
 *  This is where poor old Gnimpsh hangs out. He will help old Mercs
 *  who want to leave, and he will also hand out a quest to players
 *  willing to help him.
 *
 *  Created March 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "/d/Sparkle/guilds/new_merc/merc_defs.h"

inherit MERC_ROOM_BASE;
inherit "/d/Gondor/open/room_chairs/room_chairs2";

#include <stdproperties.h>

/* Definitions */
#define DESK_NAME	"old rotting log"
#define DESK_NUM	3


/* Global Variables */
object gRecruiter;


/* Prototypes */
public void        reset_room();
public string      exa_log();
public void        create_merc_room();
public void        leave_inv(object ob, object dest);
public int         tempt_fate(string arg);
public void        init();


/*
 * Function name:        reset_room
 * Description  :        add the npc to the room if he is missing
 */
public void
reset_room()
{
    if (!objectp(gRecruiter))
    {
        gRecruiter = clone_object(
            "/d/Sparkle/guilds/mercs/npc/gnimpsh_new");
        gRecruiter->arm_me();
        gRecruiter->move_living("grumbling bitterly.", this_object());
        gRecruiter->command("sit on log");
    }
} /* reset_room */


/*
 * Function name:        exa_log
 * Description  :        show the description of the log, and
 *                       show anyone sitting on it.
 * Returns      :        string - the description
 */
public string
exa_log()
{
    return ("This old rotting log is about eight feet long. It"
      + " most likely used to be a favorite spot for people who"
      + " wanted to <sit> and recount tales of their exploits.\n"
      + sitting_on_chair(DESK_NAME, this_player(), 0, 1));
} /* exa_log */


/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("on the outskirts of an abandoned camp");
    set_long("You have come to a mostly forgotten corner on the"
      + " outskirts of an abandoned camp of some kind.\n\n");

    try_item( ({ "corner", "outskirts" }),
        "There isn't much here. Just an old rotting log.\n");
    try_item( ({ "log", "old log", "rotting log",
                 "old rotting log", "rotting old log" }),
        "@@exa_log@@");
    try_item( ({ "abandoned camp" }),
        "There just isn't much left.\n");
    try_item( ({ "forgotten corner" }),
        "Well, mostly forgotten ... you're here aren't you?\n");
    try_item( ({ "mostly forgotten corner" }),
        "It seems a pity. This place once held the fates of many"
      + " who would come and go, seeking their fortunes. Alas,"
      + " times change and the fates are fickle.\n");
    try_item( ({ "fate", "fates" }),
        "Fickle, I said!\n");
    try_item( ({ "fickle", "fickle fate", "fickle fates" }),
        "Don't tempt them.\n");
    try_item( ({ "ground", "floor", "down", }),
        "The ground here was once very well-trodden, but now"
      + " the paths are becoming overgrown with grass.\n");
    try_item( ({ "grass", "grasses" }),
        "It has sprouted up, as grass tends to do.\n");
    try_item( ({ "sky", "up" }),
        "The sky above is filled with slowly moving clouds.\n");
    try_item( ({ "cloud", "clouds", "slowly-moving cloud",
                 "slowly-moving clouds", "moving cloud",
                 "moving clouds", "passing cloud",
                 "passing clouds" }),
        "The clouds float silently past overhead. Peacefull,"
      + " really ...\n");
    try_item( ({ "sign", "signs" }),
        "There can be no mistake. This was once a very busy"
      + " place.\n");
    try_item( ({ "site", "activity", "site of activity",
                 "site of much activity" }),
        "Whatever activity used to take place here, it is long"
      + " gone now.\n");
    try_item( ({ "pit", "hollow pit", "hollowed pit",
                 "hollowed out pit" }),
        "It is a ways to the northwest.\n");
    try_item( ({ "campfire", "large campfire", "fire" }),
        "The pit is off to the northwest.\n");
    try_item( ({ "pathway", "pathways", "path", "paths" }),
        "The pathways are becoming less pronounced with each"
      + " passing week. Grass has grown in to slowly remove all"
      + " signs of what once went on here.\n");
    try_item( ({ "tent", "tents", "various tents" }),
        "The tents do not remain. Only impressions in the earth"
      + " where they once stood mark their places.\n");
    try_item( ({ "impressions", "impression",
                 "impressions in the earth",
                 "impression in the earth" }),
        "These, too, are mostly overgrown with grass.\n");
    try_item( ({ "station", "stations" }),
        "Gone ... all gone ...\n");
    try_item( ({ "outfit", "camp", "campsite", "site",
                 "camp site", "mercenary guild", "guild" }),
        "There is little left to tell the story of whatever"
      + " people used to occupy this site.\n");
    try_item( ({ "people", "mercenary", "mercenaries" }),
        "None remain, except perhaps you?\n");
    try_item( ({ "sun", "sunshine", "sunlight" }),
        "The sun shines brightly in the sky, occasionally obscured"
      + " by a passing cloud.\n");
    try_item( ({ "sound", "sounds", "sound of the forest",
                 "sounds of the forest" }),
        "Linger a while, and you'll be sure to hear them.\n");
    try_item( ({ "forest", "wood", "woods", "tree", "trees" }),
        "The trees have been cleared away here, where a camp of some"
      + " kind once stood. Now, the forest will begin its slow"
      + " task of reclaiming this site.\n");
    
    add_exit("start", "northwest");

    set_no_exit_msg( ({ "north", "northeast", "west", "southeast",
                        "east", "south", "southwest" }),
        "You walk around the perimeter of the area, finding a"
      + " few more reminders of the place this once was. Finding"
      + " nothing more interesting, you return to where you"
      + " were.\n");

    /* Do this with a delay to override the parent file. */
    set_alarm(1.0, 0.0, &add_prop(ROOM_S_MAP_FILE,
              "abandoned_merc_camp.txt"));

    add_chair(DESK_NAME, "[down] [on] / [upon] [the] [old]"
      + " [rotting] 'log'",
        DESK_NUM, "on", 0);

    reset_room();
} /* create_merc_room */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 *
 * Masked to support the room chair code.
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */


/*
 * Function name:        tempt_fate
 * Description  :        Fun little Easter Egg.
 * Arguments    :        Whatever the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
tempt_fate(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Tempt? Tempt what? Don't you do it!\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [fickle] 'fate' / 'fates'"))
    {
        notify_fail("What are you trying to do, anyway?\n");
        return 0;
    }

    write("You cheeky little bastard! I said don't do it!\n");
    return 1;
} /* tempt_fate */


/*
 * Function name:        init
 * Description  :        add actions to the players, and set up the
 *                       actions for the chairs
 */
public void
init()
{
    ::init();

    init_room_chairs();

    add_action(tempt_fate, "tempt");
} /* init */