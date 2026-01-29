/*
 * Study Room for the Academy of Elemental Arts in Gelan
 * 
 * Created by Petros, September 2009
 */

#pragma strict_types

#include <macros.h>
#include "defs.h"

inherit SCHOOL_ROOM_BASE;
inherit "/lib/guild_support";

// Global variables
object teacher;

public void
create_school_room()
{
    set_short("Study Room");
    set_long("This is a medium-sized room and the very air emanates a sense "
        + "of focus. Along the northern wall you see many students meditating "
        + "in various sitting and kneeling positions on plush mats. The "
        + "southern wall is lined by a large set of bookshelves with books "
        + "of various kinds. A set of golden orbs hang from stands attached "
        + "to the eastern wall. Under these orbs, a small group of students, "
        + "supervised by a teacher, are lined up and seem to be lost in "
        + "a deep trancelike concentration."
        + "\n"
        + "You may join the students on the mats and <meditate>. If you have "
        + "been given permission, you can try and <channel> the elemental "
        + "energies here.\n\n");
    
    try_item( ({ "mats", "mat", "plush mats", "plush mat" }),
            "The plush mats look very comfortable. You see others sitting "
          + "or kneeling upon them to <meditate>. There are a few mats "
          + "available for you do the same as well.\n");
    
    try_item( ({ "student", "students" }),
            "The students here are as varied as they come. Some are "
          + "meditating on the plush mats while others are standing "
          + "in a line practicing how to channel their abilities.\n");
          
    try_item( ({ "stands", "stand", "globe", "golden orb", "orb",
        "orbs", "golden orbs", "large golden orbs", "large golden orb",
        "eastern wall" }),
            "Metal stands attached to wall hold the large golden orbs that "
          + "each radiate a soft golden glow from the eastern wall. They "
          + "emphasize the serene atmosphere in this room.\n");
    
    try_item( ({ "bookshelf", "bookshelves", "set of bookshelves",
        "large set of bookshelves" }),
            "Simple wooden bookshelves take up most of the southern wall. "
          + "A few of the books look like interesting enough to take "
          + "a closer look at their titles.\n");
    
    try_item( ({ "book", "books" }),
            "Though there are a few individual books on the bookshelves. "
          + "Most of the books seem to be several copies of the same "
          + "book for class education. You notice titles such as \"Herblore, "
          + "why is this important?\", \"My First Spellbook! (now with "
          + "moving pictures)\", \"Conjurations and Long Beards\", and \"Staves "
          + "and Hats and Other Accessories\".\n");
          
    add_exit(ACADEMIC_SCHOOL + "lounge", "west");
    
    set_alarm(0.0, 0.0, reset_room);
}

public void
reset_room()
{
    // Ensure that the teacher is always present
    if (!objectp(teacher))
    {
        setuid();
        seteuid(getuid());
        teacher = clone_object(ACADEMIC_TEACHER);
        teacher->move(this_object());
        teacher->arm_me();        
    }
}

public void
init()
{
    ::init();
    
    init_guild_support();
    
    add_action("channel", "channel");
}

/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);

    ::leave_inv(ob, to);    
}

public int
channel(string str)
{
    object player = this_player();
    if (!IS_MEMBER(player))
    {
        notify_fail("You are not a member of the Academy!\n");
        return 0;
    }
    
    // A player can channel after completion of every task. Each channeling
    // provides the player with a spell in this order:
    // 1. pyrofosti (fire)
    // 2. hydrokine (water)
    // 3. cheiropoto (elemental)
    // 4. lithodermu (earth)
    int bAllowedToChannel = 0;
    string spellToLearn;
    if (ACADEMIC_MANAGER->query_completed_task_1(player)
        && !ACADEMIC_MANAGER->acquired_fire_spell(player))
    {
        // Allowed to channel for the pyrofosti spell
        bAllowedToChannel = 1;
        spellToLearn = "pyrofosti";
    }
    else if (ACADEMIC_MANAGER->query_completed_task_2(player)
             && !ACADEMIC_MANAGER->acquired_water_spell(player))
    {
        // Allowed to channel for the hydrokine spell
        bAllowedToChannel = 1;
        spellToLearn = "hydrokine";
    }
    else if (ACADEMIC_MANAGER->query_completed_task_3(player)
             && !ACADEMIC_MANAGER->acquired_elemental_spell(player))
    {
        // Allowed to channel for the cheiropoto spell
        bAllowedToChannel = 1;
        spellToLearn = "cheiropoto";
    }
    else if (ACADEMIC_MANAGER->query_completed_task_4(player)
             && !ACADEMIC_MANAGER->acquired_earth_spell(player))
    {
        // Allowed to channel for the lithodermu spell
        bAllowedToChannel = 1;
        spellToLearn = "lithodermu";
    }
    else if (ACADEMIC_MANAGER->query_completed_task_4(player)
             && ACADEMIC_MANAGER->acquired_earth_spell(player))
    {
        // Player has done all the channeling they need to do
        write("You have already completed all the courses you can "
            + "on channeling. Go forth and practice what you have "
            + "learned!\n");
        return 1;
    }
    
    if (!bAllowedToChannel)
    {
        notify_fail("You have not been given permission by the Taskmaster to "
            + "join this class yet. Go speak with Amjal if you wish to "
            + "further your studies in channeling.\n");
        return 0;
    }
    else
    {
        write("With permission from the Taskmaster you are allowed to join "
            + "the channeling class currently in session. Samoht motions "
            + "to you to quickly join before he changes his mind.\n");
        tell_room(environment(player), QCTNAME(player) + " joins the current "
            + "channeling session.\n", ({ player }));
        object channel_object = clone_object(ACADEMIC_CHANNEL_OBJECT);
        channel_object->set_spell_to_learn(spellToLearn);
        channel_object->move(player, 1);
    }
    
    return 1;
}
