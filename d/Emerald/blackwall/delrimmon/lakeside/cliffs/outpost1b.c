/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/outpost1b.c
 *
 *  This room is the chamber of records which was built and maintained
 *  by Formandil and his men during their watch over the Blackwall Mountains.
 *  It yet contains records and logs of the experiences of those
 *  times which the observant andventurer may find and read. One
 *  such adventurer lies dead in the chamber. He did not succeed.
 *
 *  Copyright (c) April 1999, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define TOP_SIDE    (DELRIMMON_DIR + "lakeside/cliffs/signal_room")
/* prototypes */
public int     check_exit(int climb_message = 0);
public void    reset_room();
public int     climb_ladder(string arg);
public void    init();


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    add_name("_torque_quest_rillian_chamber");
    set_short("a small square chamber");
    set_long(BSN(
        "An unsettling silence and dense musty odor combine to give"
      + " a tomblike feeling to this small stone chamber. The walls are"
      + " stark and barren, except for the northern wall, which bears"
      + " a large emblem. A dusty ladder stands in the center of the"
      + " room, leading up through an opening in the ceiling, where"
      + " a shaft of light streaks downward to dimly illuminate the"
      + " area."));

    add_item( ({ "finger", "fingers", "fingers on the hand",
                 "fingers on the figure of the hand" }),
        "The fingers on the figure of the hand are pointing up.\n");
    add_item( ({ "ladder", "dusty ladder", "wooden ladder" }),
        "The ladder is extremely dusty, and looks to have avoided"
      + " much use for centuries. There are a few places along the"
      + " rungs which appear to have less dust on them. The ladder"
      + " leads up through an opening in the ceiling.\n");
    add_item( ({ "rung", "rungs" }),
        "The dust along the rungs seems to have been disturbed"
      + " in the not too distant past.\n");
    add_item( ({ "opening", "opening in the ceiling" }),
        "Light pours in through the opening, suggesting that this"
      + " may be a way of getting back outside.\n");
    add_item( ({ "light", "shaft", "shaft of light" }),
        "The light from above only dimly lights this chamber.\n");
    add_item( ({ "north", "north wall", "northern wall",
                 "wall to the north" }),
        "The north wall is unadorned, and bears no markings aside"
      + " from a large emblem which has been carved into its surface.\n");
    add_item( ({ "here", "area", "chamber", "small chamber",
                 "stone chamber", "small stone chamber" }), BSN(
        "There are no furnishings in this chamber, nor anything else"
      + " to provide clues as to what its purpose may have been,"
      + " except perhaps for the emblem carved upon the northern"
      + " wall."));
    add_item( ({ "wall", "walls" }), BSN(
        "The walls of this chamber are barren of any decoration,"
      + " except for the north wall, which bears a carven emblem."));
    add_item( ({ "west wall", "west", "wall to the west",
                 "western wall" }), BSN(
        "The western wall is bare and unadorned."));
    add_item( ({ "east", "east wall", "wall to the east",
                 "eastern wall" }), BSN(
        "The wall to the east is bare of any decoration or marking."));
    add_item( ({ "south", "wall to the south", "southern wall",
                 "south wall", "passage", "passageway" }), BSN(
        "A passageway opens in the middle of the wall to the"
      + " south, leading into total darkness."));
    add_item( ({ "darkness", "dark", "total darkness" }), BSN(
        "It is uncertain from here what lies beyond the"
      + " darkness."));
    add_item( ({ "silence", "unsettling silence" }), BSN(
        "The silence in this chamber gives it an eerie feel, which"
      + " is augmented by the grim spectacle upon the floor."));
    add_item( ({ "odor", "odor", "musty odor", "musty odour",
                 "must" }), BSN(
        "The dust and years of decay from the corpse are no doubt"
      + " responsible from the musty odor of this chamber."));
    add_item( ({ "ceiling", "up", "roof" }), BSN(
        "The ceiling of this chamber is not particularly high, and"
      + " is covered with cracks. A ladder leads through an opening"
      + " in the middle of its surface."));
    add_item( ({ "cracks", "cracks in the ceiling", "crack" }), BSN(
        "The cracks in the ceiling are perhaps due to the weight"
      + " of the cliffs which bears down on this empty space in"
      + " the rock."));
    add_item( ({ "rock", "rocks", "stone", "stones" }), BSN(
        "The walls, ceiling, and floor all appear to have been"
      + " hewn from the very rock of the cliffs."));
    add_item( ({ "cliff", "cliffs", "cliffside", "cliffsides" }), BSN(
        "It is not possible to view the cliffsides from here,"
      + " where you are within them."));
    add_item( ({ "sky", "sun", "moon" }), BSN(
        "The sky is not visible from inside this chamber."));
    add_item( ({ "tomb" }), BSN(
        "It would appear that this room, if not an actual tomb,"
      + " is at least the final resting place of someone."));
    add_item( ({ "floor", "ground", "down" }), BSN(
        "The floor is covered with thick dust which has partially"
      + " covered the corpse which lies here."));
    add_item( ({ "dust", "thick dust" }), BSN(
        "The dust is thick and heavy in most places. A few footprints"
      + " are visible, however."));
    add_item( ({ "print", "footprint", "prints", "footprints",
                 "foot print", "foot prints" }), BSN(
        "The footprints appear to lead from the passageway to"
      + " the corpse. It seems as if they were made by him, long"
      + " ago, as they themselves are now partially filled with"
      + " dust."));

    FIX_EUID

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/outpost_corridor", "south",
             check_exit);
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/signal_room", "up",
             &check_exit(1), 5, 1);

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                        "southwest", "west", "northwest" }),
        "You are blocked by the walls of the chamber.\n");

    reset_room();
} /* create_del_rimmon */

/*
 * Function name:        check_exit
 * Description  :        If someone tries to leave with the journal
 *                       from the corpse in their possession, we do
 *                       not allow it.
 * Arguments    :        int climb_message: if true, then we want to
 *                       print to the room a message about climbing
 *                       the ladder.
 * Returns      :        int 0 - ok to leave,
 *                       int 1 - don't allow it.
 */
public int
check_exit(int climb_message = 0)
{
    if (present("del_rimmon_quest_journal", TP) ||
        present("del_rimmon_quest_journal", deep_inventory(TP)))
    {
        if (TP->query_stat(SS_WIS) >= 136)
        {
            write("As you attempt to leave, an unbearable feeling"
              + " of wrongdoing comes over you for not returning the"
              + " journal to the corpse. It seems the enchantment upon"
              + " the book is too strong to resist.\n");

            return 1;
        }

        write("As you attempt to leave, an unbearable feeling"
          + " grips you, and forces into your mind the fact that the"
          + " journal must be returned to the corpse. You break out"
          + " in a sweat, and panic freezes you in your tracks.\n");

        return 1;
    }

    if (climb_message)
    {
        write("You grasp the rungs of the ladder, and make your way"
            + " up through the opening in the ceiling.\n");
        tell_room(this_object(), QCTNAME(this_player()) + " climbs"
            + " up the ladder and disappears through the opening"
            + " in the ceiling.\n", this_player());
        TOP_SIDE->entry_msg(this_player());
    }

    return 0;
} /* check_exit */


/*
 * Function name:        leave_inv
 * Description  :        Called when objects leave this container or
 *                       when an object is about to change its weight,
 *                       volume, or light status.
 * Arguments    :        ob: The object that just left this inventory
 *                       to: where it went
 */
public void
leave_inv(object ob, object to)
{
    object   obj;

    ::leave_inv(ob, to);

    if ((obj = present("del_rimmon_quest_journal", ob)) ||
        (obj = present("del_rimmon_quest_journal", deep_inventory(ob))))
    {
        obj->move(this_object());

        ob->catch_tell("A sense of panic grips you momentarily, and"
                     + " your body flinches, forcing you to drop"
                     + " the tattered journal to the ground.\n");
        tell_room(this_object(), "A tattered journal falls to the floor"
          + " from where " + QCTNAME(this_player()) + " was just"
          + " standing.\n");

        return;
    }

    return;
} /* leave_inv */


/*
 * Function name:        reset_room
 * Description  :        clone the corpse of Borgil into this room
 */
public void
reset_room()
{
    object corpse,
           emblem;

    if (!present("corpse_of_rillian"))
    {
        corpse =
            clone_object(DELRIMMON_DIR + "obj/rillian")->move(this_object());
    }

    if (emblem = present("torque_quest_emblem"))
    {
        emblem->blank_emblem();
    }
    else
    {
        emblem =
            clone_object(DELRIMMON_DIR + "obj/emblem")->move(this_object());
    }
} /* reset_room */


/*
 * Function name:        climb_ladder
 * Description  :        allow the player to climb up the ladder
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
climb_ladder(string arg)
{
    if (!strlen(arg))
    {
        NFN0("Climb what?");
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [dusty] [wooden] 'ladder'"))
    {
        NFN0("What?"); /* the player used bad syntax */
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'up' here, using"
            + " command. Since you are a wiz, that won't work.\n");
    }

    this_player()->command("up");
    return 1;
} /* climb_ladder */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(climb_ladder, "climb");
} /* init */
