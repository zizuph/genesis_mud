/*
 *  /d/Sparkle/guilds/mercs/room/start.c
 *
 *  This is the starting location for Mercenaries who have for
 *  whatever reason remained in the old Maligant operation. Their
 *  guildhall is gone, and so are their powers. This place can
 *  serve as a place that they can enjoy shared memories.
 *
 *  Created March 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "/d/Sparkle/guilds/new_merc/merc_defs.h"

inherit MERC_ROOM_BASE;

#include <files.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>

/* Definitions */
#define            MEMORY_LOG_DIR "/d/Sparkle/guilds/new_merc/log/"
#define            MAX_MSG_LENGTH 2000
#define            MEMORY_DIR "/d/Sparkle/guilds/mercs/memories/"
#define            MERC_CURRENT_MEMORY_PROP "_current_merc_memory"

/* Global Variables */
public string     *Memories = ({});

/* Prototypes */
public void        create_merc_room();
public int         sort_descending(string a, string b);
public void        establish_memories();
public void        display_merc_memory(object who);
public int         trigger_merc_memory(string arg);
public void        init();
public int         share_merc_memory(string arg);
public void        save_merc_memory(string arg, object who, string mem_file);

public string     *query_memories() { return Memories; }


/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("within the grounds of an abandoned camp");
    set_long("All around you here are the signs of what must have"
      + " once been a site of much activity. A hollowed out pit"
      + " where a large campfire once burned sits positioned"
      + " between pathways which once lead to various tents and"
      + " stations of a large and organized outfit of some"
      + " kind. All that remains now are memories and the sounds"
      + " of the forest.\n\n");

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
        "The clouds float silently past overhead. Peaceful,"
      + " really...\n");
    try_item( ({ "sign", "signs" }),
        "There can be no mistake. This was once a very busy"
      + " place.\n");
    try_item( ({ "site", "activity", "site of activity",
                 "site of much activity" }),
        "Whatever activity used to take place here, it is long"
      + " gone now.\n");
    try_item( ({ "pit", "hollow pit", "hollowed pit",
                 "hollowed out pit" }),
        "A few ashes remain mixed in with the dirt at the bottom"
      + " of the pit.\n");
    try_item( ({ "ash", "ashes" }),
        "Looking at the ashes, you imagine the roaring campfire"
      + " that must have once burned here, sending sparks soaring"
      + " into the night sky as companions shared stories of their"
      + " many adventures. So many memories ...\n");
    try_item( ({ "memory", "memories" }),
        "If you have some, you are welcome to <share> them here."
      + " You may also <recall> the memories others have shared"
      + " in this place.\n");
    try_item( ({ "campfire", "large campfire", "fire" }),
        "No fire has burned here for a very long time.\n");
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
    
    add_exit("/d/Genesis/start/human/wild2/n_road2", "west");
    add_exit("gnimpsh_room", "southeast");

    set_no_exit_msg( ({ "northwest", "north", "northeast",
                        "east", "south", "southwest" }),
        "You walk around the perimeter of the area, finding a"
      + " few more reminders of the place this once was. Finding"
      + " nothing more interesting, you return to where you"
      + " were.\n");

    /* Do this with a delay to override the parent file. */
    set_alarm(1.0, 0.0, &add_prop(ROOM_S_MAP_FILE,
              "abandoned_merc_camp.txt"));

    establish_memories();

} /* create_merc_room */


/*
 * Function name:        sort_descending
 * Description  :        Used to sort our memory list in descending
 *                       order for timestamp purposes.
 * Arguments    :        string a - the first number to check
 *                       string b - the second number to check
 * Returns      :        int - a indicator of ordinance
 *
 * Thanks, Petros!
 */
public int
sort_descending(string a, string b)
{
   if (a < b)
   {
      return 1;
   }
   else if (a > b)
   {
      return -1;
   }
   return 0;
} /* sort_descending */


/*
 * Function name:        establish_memories
 * Description  :        Populate an array with the filenames
 *                       of the memories that have been recorded.
 *                       These filenames are the timestamps of
 *                       the memories at creation. The array will
 *                       be populated with a sort that puts the
 *                       most recent memories first in line.
 */
public void
establish_memories()
{
    Memories = sort_array(get_dir(
        "/d/Sparkle/guilds/mercs/memories/"), sort_descending);
} /* establish_memories */


/*
 * Function name:        display_merc_memory
 * Description  :        Show the next memory available to the
 *                       player
 * Arguments    :        object who - the player
 */
public void
display_merc_memory(object who)
{
    int     current_memory = who->query_prop(MERC_CURRENT_MEMORY_PROP);
    string  memory;      /* The timestamp name of the file */
    string  memory_txt;  /* The memory itself */
    string  memory_age;  /* How long ago was this memory shared? */

    /* If the player has seen all of the memories, we cycle them
     * back to the beginning.
     */
    if ((current_memory + 1) > sizeof(Memories))
    {
        current_memory = 0;
    }

    if (!sizeof(Memories))
    {
        who->catch_tell("You sense that no one has yet taken the time"
          + " to <share> any memories here. Perhaps you will be the"
          + " first?\n");
        return;
    }

    memory = Memories[current_memory];
    memory_age = CONVTIME(time() - LANG_WORD2NUM(memory));

    memory_txt = "A memory that was shared " + memory_age
      + " ago enters your thoughts ...\n\n";

    memory_txt += read_file(MEMORY_DIR + memory);

    who->catch_tell(memory_txt + "\n\n"
      + "The memories fade, and you open your eyes again.\n");

    current_memory++;
    who->add_prop(MERC_CURRENT_MEMORY_PROP, current_memory);

    return;
} /* display_merc_memory */


/*
 * Function name:        trigger_merc_memory
 * Description  :        Allow the player to get in touch with
 *                       memories here.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
trigger_merc_memory(string arg)
{
    string  memory_msg = one_of_list( ({
        " closes " + this_player()->query_possessive() + " eyes"
      + " and becomes very quiet and still.",
        " tugs thoughtfully at "
      + this_player()->query_possessive() + " chin,"
      + " recalling an old memory.",
        " pauses and stares vacantly into the trees for a few"
      + " moments.",
        " savors an old memory that lingers here.",
        " peers reflectively around, taking in the memories.",
        " looks suddenly reflective, and withdraws somewhat into "
      + this_player()->query_possessive() + " own thoughts.",
        " smiles quietly to " + this_player()->query_objective()
      + "self, caught up in an old memory.",
        }) );

    if (!strlen(arg))
    {
        notify_fail("Recall what? Memories, perhaps?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[some] [old] 'memory' / 'memories'"))
    {
        notify_fail("Perhaps you would like to recall some"
          + " memories?\n");
        return 0;
    }

    write("You close your eyes, and allow the memories that may"
      + " linger in this place to wash over you ...\n\n");
    tell_room(this_object(), QCTNAME(this_player())
      + memory_msg + "\n", this_player());

    set_alarm(3.0, 0.0, &display_merc_memory(this_player()));
    return 1;
} /* trigger_merc_memory */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(trigger_merc_memory, "recall");
    add_action(share_merc_memory, "share");
} /* init */


/*
 * Function name:        share_merc_memory
 * Description  :        Allow players to share memories that will
 *                       linger here for others to recall.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
share_merc_memory(string arg)
{
    string  memory_file = "" + time();

    if (!strlen(arg))
    {
        notify_fail("Share what? A memory, perhaps?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[a] [some] 'memory' / 'memories'"))
    {
        notify_fail("Perhaps you feel like sharing a memory,"
          + " instead?\n");
        return 0;
    }

    tell_room(this_object(), QCTNAME(this_player())
      + " stares at the firepit, waxing reminiscent for a few"
      + " moments.\n", this_player());
    write("You stare into the empty firepit, and memories begin to"
      + " flow from you.\n");
    write("Enter the memory you wish to share. ("
      + MAX_MSG_LENGTH + " characters max)\n\n");

    clone_object(EDITOR_OBJECT)->edit(
        &save_merc_memory( , this_player(), memory_file));

    return 1;
} /* share_merc_memory */


/*
 * Function name:        save_merc_memory
 * Description  :        Take the input from the share_merc_memory
 *                       function and save it to the appropriate file.
 * Arguments    :        string arg - the text that was shared
 *                       object who - the player doing the sharing
 *                       string mem_file - the filename to save to
 *                                         (the timestamp, really)
 */
public void
save_merc_memory(string arg, object who, string mem_file)
{
    int     msg_length = strlen(arg);
    int     remainder = 72 - msg_length;
    int     mrnd = random(remainder);
    int     remainder2 = remainder - mrnd;
    string  msg;

    if (!who)
    {
        return;
    }

    if (!msg_length)
    {
        who->catch_tell("Not feeling very nostalgic? So be it.\n");
        return;
    }

    if (arg == "~q" || arg == "quit" || arg == "**")
    {
        who->catch_tell("Not feeling very nostalgic? So be it.\n");
        return;
    }

    if (strlen(arg) > MAX_MSG_LENGTH)
    {
        who->catch_tell("You can't share memories that are so"
          + " huge! Trim it down or split it up if you want to"
          + " share it here.\n");
        return;
    }

    msg = arg + "\n(Shared by "
      + capitalize(who->query_real_name()) + ")";

    write_file(MEMORY_DIR + mem_file, msg);

    write_file(MEMORY_LOG_DIR + "old_memories",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
      + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_real_name()) 
      + " shared a memory. [filename=" + mem_file + "]\n");

    who->catch_tell("As you finish reliving your memory, you sense"
      + " that it will linger here for othes to know as well.\n");
    tell_room(this_object(), QCTNAME(who) + " blinks a few times,"
      + " and you sense that a fresh memory now lingers"
      + " in this place.\n", who);

    establish_memories();

    return;
} /* save_merc_memory */

