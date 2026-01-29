/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/pool_bottom.c
 *
 *  This is the underwater room which can be reached by diving into the
 *  pool at: /d/Emerald/blackwall/delrimmon/lakeside/caves/grotto_pool.c
 *
 *  Copyright (c) January 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/quest_handler/quest_handler.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define BREATH_PROP        "del_rimmon_holding_breath_prop"

/* prototypes */
public void        create_del_rimmon();
public void        do_surface(object player);
public void        holding_breath(object player);
public void        enter_inv(object ob, object from);
public void        leave_inv(object ob, object to);
public int         do_swim(string arg);
public void        init();
public int         describe_surface();
public void        complete_quest(object player);


/*
 * function name:        create_del_rimmon
 * descripiton  :        set up the room
 */
public void
create_del_rimmon()
{
    add_name("del_rimmon_pool");
    set_short("beneath the waters of a dark subterranean pool");
    set_long("Dark water swirls softly with your movements here beneath"
           + " the surface of a dark subterranean pool. Though the pool"
           + " is not terribly deep, it is too dark to see many"
           + " details in the rock which comprises the sides and bottom"
           + " of this pool.\n");

    add_item( ({ "water", "dark water", "pool", "area",
                 "dark pool", "subterranean pool",
                 "dark subterranean pool", "here" }),
        "Water is all around you here, swirling softly around you"
      + " with every move you make. The surface of the pool is just"
      + " above you here.\n");
    add_item( ({ "surface", "surface of the pool", "up" }),
        "The surface of the pool appears to be just above you, but it"
      + " is difficult to tell due to the lack of light.\n");
    add_item( ({ "details", "rock", "rocks", "side", "side of the pool",
                 "sides", "sides of the pool", "bottom",
                 "bottom of the pool", "pool bottom", "down" }),
        "The sides and bottom of this pool appear to be made of"
      + " the same rock which comprises the cliffs. Very little"
      + " detail can be seen here due to the lack of light. However,"
      + " a faint glow is coming from an opening in the rocks to the"
      + " east.\n");
    add_item( ({ "opening", "opening in the rocks", "east" }),
        "An opening is visible in the rocks just to the east. It looks"
      + " large enough for two to swim abreast. A faint glow is"
      + " coming from the opening.\n");
    add_item( ({ "glow", "faint glow" }),
        "The glow appears to be light from the outside.\n");


    add_prop(ROOM_S_DARK_LONG, "A dark, underwater area.\n");
    add_prop(ROOM_M_NO_ATTACK,
        "Combat is impossible while underwater.\n");
    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from beneath the surface of the pool, gasping for breath,"
      + " and crawls out of the water.");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(DELRIMMON_DIR + "lakeside/caves/grotto_pool", "up",
             describe_surface, 5, 1);

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                        "south", "southwest", "west", "northwest",
                        "down" }),
        "You swim around under the water, but cannot move far in"
      + " that direction.\n");

    FIX_EUID
} /* create_del_rimmon */


/*
 * Function name:        do_surface
 * Description  :        if the player is still underwater, force them
 *                       to surface
 * Arguments    :        object - the player object
 */
public void
do_surface(object player)
{
    if (environment(player)->id("del_rimmon_pool"))
    {
        player->catch_msg("You can no longer hold your breath, and"
          + " struggle upward, seeking the surface.\n");

        tell_room(environment(player), QCTNAME(player)
          + " seems to desperately need air, and struggles quickly"
          + " for the surface.\n", player);

        if (player->query_wiz_level())
        {
            player->catch_msg("Normally, we would move the player"
              + " 'up' here, using command. Since you are a wizard,"
              + " it doesn't work on you.\n");

            return;
        }

        player->command("$up");

        player->catch_msg("Gasping for air, you pull yourself out"
          + " of the water, to stand beside the pool.\n");
    }

    return;
} /* do_surface */


/*
 * Function name:        holding_breath
 * Description  :        let the player know that they are running
 *                       out of air, if they are still under water.
 * Arguments    :        object player - the player object
 */
public void
holding_breath(object player)
{
    if (environment(player)->id("del_rimmon_pool"))
    {
        player->catch_msg("You are beginning to have a hard time"
          + " holding your breath. You'll have to surface soon.\n");

        set_alarm(10.0, 0.0, &do_surface(player));
    }

    return;
} /* holding_breath */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!living(ob) || ob->query_prop(BREATH_PROP))
    {
        return;
    }

    set_alarm(15.0, 0.0, &holding_breath(ob));
    ob->add_prop(BREATH_PROP, 1);

    return;
} /* enter_inv */


/*
 * Function name:        check_exit
 * Description  :        if players are leaving the water, then they
 *                       no longer will need the BREATH_PROP, so
 *                       we remove it
 * Returns      :        int 0 - we always let them leave
 */
public int
check_exit()
{
    if (this_player()->query_prop(BREATH_PROP))
    {
        this_player()->remove_prop(BREATH_PROP);
    }

    write("You poke your head above the surface of the water, and"
        + " gasp for air.\n");
    return 0;
} /* check_exit */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just leaved this inventory
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (to->id("del_rimmon_pool"))
    {
        return;
    }

    ob->remove_prop(BREATH_PROP);

    if (to->id("_grotto_pool"))
    {
        if (QH_QUERY_QUEST_COMPLETED(ob, "torque_grotto") ||
            ob->query_prop("_tried_grotto_pool"))
        {
            return;
        }

        set_alarm(2.0, 0.0, &complete_quest(ob));
        return;
    }
} /* leave_inv */


/*
 * Function name:        complete_quest
 * Description  :        reward the player if they have earned it
 * Arguments    :        object player - the player object (duh)
 */
public void
complete_quest(object player)
{
    if (MANAGER->query_dug_waterfall(player))
    {
        player->catch_tell("A sense of satisfaction comes to you as you"
          + " stand in this strange place. Your thoughts drift"
          + " momentarily to all the hard work you put into getting"
          + " here.\n");

        if (QH_QUEST_COMPLETED(player, "torque_grotto"))
        {
            player->catch_tell("You feel more experienced!\n");
        }
        else
        {
            player->catch_tell("You feel no more experienced.\n");
        }

        return;
    }

    player->catch_tell("As you gaze at the cave around you, you can't"
      + " help but wonder how you would have gotten in here had it"
      + " not been for whoever it was who washed clean the pool.\n");
    player->add_prop("_tried_grotto_pool", 1);

    return;
} /* complete_quest */




/*
 * Function name:        do_swim
 * Description  :        allow the player to swim around
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
do_swim(string arg)
{
    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " where?");
    }

    if (parse_command(arg, ({}),
        "[in] [to] [into] [through] [the] [large] 'opening'"))
    {
        write("You swim through the opening in the rocks, and emerge"
            + " into a pool beneath the open sky.\n");

        this_player()->move_living("M", 
            DELRIMMON_DIR + "lakeside/pool_bottom", 1, 0);

        tell_room(this_object(), QCTNAME(this_player())
          + " swims through an opening in the rocks and disappears"
          + " to the east.\n", 0);

        this_player()->add_fatigue(-20);

        return 1;
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would use command to initiate the"
            + " movement, but since you are a wizard, that will not"
            + " work. Just use direction commands as you would"
            + " on land.\n");
    }

    this_player()->command(arg);
    return 1;
} /* do_swim */


/* 
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_swim, "swim");
    add_action(do_swim, "enter");
} /* init */


/*
 * Function name:        describe_surface
 * Description  :        tell the player a bit about the experience of
 *                       climbing out of the pool when they use the 
 *                       "up" exit
 * Returns      :        int 0 - we let them use the exit
 */
public int
describe_surface()
{
    write("You poke your head above the surface, and climb out of"
        + " the water to stand beside the pool.\n");

    return 0;
} /* describe_surface */
