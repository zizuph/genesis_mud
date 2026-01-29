/*
 *  /d/Emerald/common/guild/aod/rooms/tower.c
 * 
 *  This is the base of the tower which is the entrance to the Army of
 *  Darkness guild.
 * 
 *  Copyright (c) July 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types;

inherit "/d/Emerald/std/room";

#include <stdproperties.h>
#include "../defs.h"
inherit AOD_LIB_DIR + "add_spike";

/* prototypes */
public void        create_emerald_room();
public int         check_exit();
public int         do_climb(string arg);
public void        init();


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room with domain presets
 */
public void
create_emerald_room()
{
    set_short("within the base of a tall dark tower");
    set_em_long("Darkness weighs down upon you heavily from glassy smooth"
      + " walls which surround you on all sides. This chamber rests"
      + " within the base of a tower of some kind which has been melded"
      + " into the rock of the cliffs. A huge spiral staircase rises"
      + " from the floor, disappearing as it travels into the darkness"
      + " above. A huge opening in the southwestern wall leads out"
      + " of the tower. To the northeast, a massive corridor leads"
      + " into the rock of the mountains themselves.\n");

    add_item( ({ "darkness", "dark", "shadow", "shadows", "light" }),
        "Light seems to die quickly in this tower, where darkness"
      + " hangs like a wet blanket over everything.\n");
    add_item( ({ "wall", "walls", "smooth wall", "smooth walls",
                 "glassy wall", "glassy walls", "glassy smooth wall",
                 "glassy smooth walls", "tower wall", "tower walls",
                 "wall of the tower", "walls of the tower" }),
        "The walls of the tower form a perfect octagonal perimeter to"
      + " this chamber. Their glassy smooth surface is black beyond"
      + " black, almost making you dizzy as you stare into it.\n");
    add_item( ({ "surface", "smooth surface", "glassy smooth surface" }),
        "The surface of the walls is seemingly perfect, without crack"
      + " or scar of any kind. There are no markings of any kind which"
      + " reveal how such material might have been formed, though it"
      + " seems clear that magic must have played a part.\n");
    add_item( ({ "chamber", "area", "here", "base", "tower base",
                 "room", "base of the tower", "tower",
                 "architecture", "angle", "line", "angles", "lines" }),
        "The architecture of this tower is remarkable. Every angle,"
      + " every line, every surface - utterly flawless. Here, at the"
      + " base of the tower, the eye is almost tricked into believing"
      + " you are merely standing in an endlessly huge chamber of"
      + " night.\n");
    add_item( ({ "floor", "down", "ground" }),
        "The floor of the chamber is the same as all the other"
      + " surfaces - midnight black and flawless.\n");
    add_item( ({ "up", "ceiling", "roof" }),
        "The roof of this chamber does not seem to be visible. Looking"
      + " up, you see the staircase disappear into shadow.\n");
    add_item( ({ "rock", "cliff", "cliffs", "mountain", "mountains",
                 "rock of the cliff", "northeast", "corridor",
                 "massive corridor", "rock of the mountain",
                 "rock of the mountains", "corridor",
                 "rock of the cliffs" }),
        "Peering at the area surrounding a massive corridor to the"
      + " northeast, it is difficult to tell where the tower walls end and"
      + " natural rock begins. This structure has been craftily melded with"
      + " the mountain, apparently acting as an entryway into its depths."
      + " The corridor itself is absolutely huge - tall enough for"
      + " elephants to pass through - bearing riders!\n");
    add_item( ({ "stair", "stairs", "step", "steps", "staircase",
                 "stairway", "spiral staircase", "huge spiral staircase",
                 "huge staircase" }),
        "A huge spiral staircase winds its way up from the base of the"
      + " tower to some unseen height. Following its many steps as they"
      + " swist their way skyward, darkness soon obscures the view.\n");
    add_item( ({ "opening", "huge opening", "southwest",
                 "southwestern wall", "southwest wall", "outside" }),
        "The outside is visible through a huge opening in the"
      + " southwest wall. The opening is at least twenty feet high and"
      + " fifteen feet in width!\n");
    add_item( ({ "sky" }),
        "The sky is not visible from inside the tower.\n");
    add_item( ({ "perimeter", "octagonal perimeter", "octagon",
                 "perfect octagon", "symmetry" }),
        "The peremiter of the tower forms a perfect octagon. The"
      + " symmetry is absolute.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_spike("tower");

    add_exit("joinroom", "up");
    add_exit("courtyard", "southwest");
    add_exit("bbroom", "northeast", check_exit, 1, 0);
} /* create_emerald_room */


/*
 * Function name:        check_exit
 * Description  :        only allow ogres into the training zone.
 * Returns      :        int 1 -- cannot go this way,
 *                       int 0 -- allowed to go this way.
 */
public int
check_exit()
{
    if (this_player()->query_guild_name_occ() != GUILD_NAME &&
        this_player()->query_real_name() !=
        CHAMBER_MASTER->get_info("guests", NUM_OFFICER_SHORT) &&
        this_player()->query_real_name() !=
        CHAMBER_MASTER->get_info("guests", SPH_OFFICER_SHORT))
    {
        write("As you walk toward the cavernous entrance, purple"
          + " lightening arcs dangerously through the air, halting"
          + " you in your tracks. Only members of the Army of Darkness"
          + " may proceed beyond this point!");

        if (this_player()->query_wiz_level())
        {
            write(" But since you are a wizard, you may pass.\n");
            return 0;
        }

        write("\n");
        return 1;
    }

    return 0;
} /* check_exit */


/*
 * Function name:        do_climb
 * Description  :        allow players to climb down the stairs
 * Arguments    :        string arg - what was typed following the verb
 * Returns      :        int 1 -- success, 0 -- failure.
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you wish to climb?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [stone] [spiral] 'stair' / 'stairs' /"
      + " 'stairway' / 'staircase' / 'step' / 'steps'"))
    {
        if (parse_command(arg, ({}),
            "'down' [the] [stone] [spiral] 'stair' / 'stairs' /"
          + " 'stairway' / 'staircase' / 'step' / 'steps'"))
        {
            notify_fail("The steps do not lead down. Perhaps you could"
              + " climb up them instead.\n");
            return 0;
        }

        notify_fail("That is not possible. Do you wish to climb up"
          + " the stairs perhaps?\n");
        return 0;
    }

    write("You climb up the spiral staircase.\n");
    this_player()->command("$u");

    return 1;
} /* do_climb */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_climb, "climb");
} /* init */