/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/outpost1.c
 *
 *  This is the sleeping chamber of the outpost manned in ancient times
 *  by Formandil and his men when the this area was constantly under
 *  the guard of Telberin and her troops. It is quite deserted now.
 *
 *  Copyright (c) March 1999, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/legacy/random_noise";
inherit "/d/Emerald/blackwall/delrimmon/lib/corporeal_flux";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_del_rimmon();
public void    leave_inv(object ob, object to);
public int     say_password(string arg);
public int     lie_down(string arg);
public void    init();
public int     enter_hole(string arg);


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room with domain presets
 */
public void
create_del_rimmon()
{
    set_short("a stone chamber");
    set_long(BSN("Cold air moves quietly through this stone"
           + " chamber which has been carved in the rock of the"
           + " cliffside. The remains of what appear to be ancient"
           + " bedrolls line the walls on both sides of the room."
           + " Two dark doorways open on each end of the northern"
           + " wall here, and a large stone portal is framed by"
           + " the wall to the south."));

    add_item( ({ "chamber", "room", "stone chamber", "stone room",
                 "area", "here" }), BSN(
        "This room was obviously used as a sleeping quarters in some"
      + " long distant time."));
    add_item( ({ "cliff", "cliffs", "cliffside", "cliffsides" }), BSN(
        "This chamber is nestled within the cliffs, yet provides no"
      + " clear view of them."));
    add_item( ({ "rock", "stone" }), BSN(
        "The stone from which this room has been carved is apparently"
      + " the very rock of the cliffsides."));
    add_item( ({ "dust" }), BSN(
        "There is very little dust in the center of the room, but"
      + " it does appear as if some has managed to accumulate near"
      + " the northeast doorway in a dark corner where the"
      + " winds do not blow."));
    add_item( ({ "accumulation", "accumulation of dust",
                 "corner", "dark corner" }), BSN(
        "There are footprints visible in the dust which has"
      + " accumulated in this corner of the room."));
    add_item( ({ "print", "footprint", "prints", "footprints" }), BSN(
        "The footprints appear to be leading into the chamber to the"
      + " northeast."));
    add_item( ({ "cracks", "large cracks" }), BSN(
        "These cracks run completely through the stone. Such damage"
      + " is often sustained due to earthquakes and other natural"
      + " phenomenon."));
    add_item( ({ "stone of the door",
                 "stone of the doors" }), BSN(
        "The stone of the doors does not appear to have been"
      + " carved from that of the cliff face."));
    add_item( ({ "south", "south wall", "southern wall",
                 "wall to the south" }), BSN(
        "The southern wall is long and barren, aside from a large"
      + " stone portal which has been carved in its center."));
    add_item( ({ "portal", "stone portal", "large stone portal",
                 "large portal" }), BSN(
        "The portal looks simple at a first glance, little more"
      + " than a rectangular depression in the wall. However,"
      + " a cunning doorway lies embedded within this space."));
    add_item( ({ "door", "doorway", "cunning door", 
                 "cunning doorway", "doors", "slabs", "slab",
                 "slab-like door", "slab-like doors", "set",
                 "set of doors", "set of slab-like doors",
                 "space" }), BSN(
        "Resting within the portal in the southern wall, a set of"
      + " slab-like doors stand silently in this chamber. An"
      + " emblem has been carved into the stone."));
    add_item( ({ "air", "cold air", "wind", "cold wind"}), BSN(
        "The air in this room is not still, but rather moves"
      + " constantly from the northwest doorway through a large"
      + " hole in the floor at the foot of the eastern wall."));
    add_item( ({ "hole", "dark hole", "holes" }), BSN(
        "A dark hole opens at the base of the eastern wall, apparently"
      + " the result of some violent activity which has shaken the"
      + " area recently."));
    add_item( ({ "east", "east wall", "eastern wall",
                 "wall to the east" }), BSN(
        "The eastern wall is barren, marked only by a hole which"
      + " has opened at its base, between two bedrolls."));
    add_item( ({ "western wall", "west wall", "west",
                 "wall to the west" }), BSN(
        "The wall to the west is marked by streaks of mud which"
      + " emenate from a long crack which runs along its length," 
      + " towards the ceiling. At its base, what appear to be"
      + " ancient bedrolls rest in a neat line."));
    add_item( ({ "crack", "long crack", "cracks" }), BSN(
        "The long crack which runs along the top of the western"
      + " wall is not large, but seemingly is enough to have allowed"
      + " moisture to leak into this chamber from above."));
    add_item( ({ "moisture", "mud", "streaks", "streak",
                 "streak of mud", "streaks of mud" }), BSN(
        "The streaks of mud appear to be stains left by moisture"
      + " which has leaked into this chamber from the crack along"
      + " the top of the western wall."));
    add_item( ({ "north", "northern wall", "wall to the north",
                 "north eall" }), BSN(
        "Doorways open at both ends of the wall to the north, which"
      + " is barren otherwise."));
    add_item( ({ "doorway", "doorways" }), BSN(
        "The doorways appear to lead to two separate chambers, one"
      + " to the northwest, and another to the northeast."));
    add_item( ({ "chambers", "northeast chamber",
                 "northwest chamber" }), BSN(
        "Only darkness is visible from here."));
    add_item( ({ "wall", "walls" }), BSN(
        "The walls of this chamber are all seemingly comprised of the"
      + " stone of the cliffside. Mostly, they are barren and"
      + " unremarkable."));
    add_item( ({ "ceiling", "roof", "up" }), BSN(
        "The ceiling of this chamber is perhaps eight feet from"
      + " the ground, comprised of the stone of the cliffside."));
    add_item( ({ "floor", "ground", "down" }), BSN(
        "Very little dust is visible on the floor of this"
      + " chamber, perhaps due to the constant movement of the"
      + " air."));
    add_item( ({ "sky", "sun", "moon" }), BSN(
        "The sky is not visible from this chamber."));
    add_item( ({ "bedroll", "remains", "ancient bedroll",
                 "bedrolls", "ancient bedrolls", "bed", "beds", }), BSN(
        "What appear to be very old bedrolls are positioned along"
      + " the walls to the east and west in very neat lines. Though"
      + " clearly very ancient, they have weathered the years"
      + " fairly well, and look much more comfortable than the"
      + " stone of the floor."));
    add_item( ({ "two bedrolls", "two beds" }), BSN(
        "A hole is visible between two bedrolls along the base of"
      + " the eastern wall."));
    add_item( ({ "line", "lines", "neat line", "neat lines" }), BSN(
        "The precision of the bedroll placement seems unlike what"
      + " might result from casual usage."));

    add_cmd_item( ({ "bedroll", "bedrolls", "ancient bedroll",
                     "ancient bedrolls", "remains" }),
                  ({ "search" }), BSN(
        "You carefully move along the bedrolls, inspecting each"
      + " one in turn to see if anything interesting turns up."
      + " After a few moments, you come to the conclusion that"
      + " these are just as they appear, though the positioning"
      + " would indicate that they were used by some sort of"
      + " military personnel."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/outpost1a", "northwest");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/outpost_corridor", "northeast");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/crack1", "down", 0, 4, 1);

    set_no_exit_msg( ({ "south" }), BSN(
        "The doors of the portal in the south wall are closed."));

    set_no_exit_msg( ({ "north", "east", "southeast",
                        "southwest", "west" }),
        "You are blocked by the walls of the chamber.\n");

    reset_room();
}


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
    ::leave_inv(ob, to);

    if (ob->query_prop(TOUCH_PROP))
    {
        ob->catch_tell("You remove your hands from the stone doorway.\n");
        ob->remove_prop(TOUCH_PROP);
    }

    return;
} /* leave_inv */


/*
 * Function name:        say_password
 * Description  :        catch it if the player happens to speak the
 *                       password which he has been assigned for the
 *                       outpost doors
 * Arguments    :        string arg - what the player typed after 'say'
 * Returns      :        1 - success, 0 - failure
 */
public int
say_password(string arg)
{
    string  txt = LOW(arg);

    if (txt == MANAGER->query_password(this_player()) ||
        txt == MANAGER->query_password(this_player()) + "." ||
        txt == MANAGER->query_password(this_player()) + "!")
    {
        write("You incant: "
          + CAP(MANAGER->query_password(this_player())) + "!\n"
          + "The cracks of the doorway blink with dim blue"
          + " light, but nothing else happens.\n");
        return 1;
    }

    return 0; /* let the mudlib take it from here */
} /* say_password */


/*
 * Function name:        lie_down
 * Description  :        let the player lie down on the bedrolls
 * Arguments    :        string arg -- what the player typed
 * Returns      :        1 -- success, 0 -- failure
 */
public int
lie_down(string arg)
{
    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " where?");
    }

    if (!parse_command(arg, ({}),
        "[down] [on] [the] 'bedroll' / 'bedrolls' / 'bed' / 'beds'"))
    {
        if (parse_command(arg, ({}),
            "[down] [on] [the] 'floor' / 'ground'"))
        {
            NFN0("The ground is made of hard stone. Lying there would"
               + " be most uncomfortable.");
        }

        return 0;
    }

    WRITE("You carefully lie down on one of the ancient bedrolls and"
        + " make yourself comfortable. As your mind relaxes, you"
        + " gain an awareness of what it might have been like to"
        + " have slept on this floor night after night, in some"
        + " forgotten time in an age long past. Somewhat wistfully,"
        + " you return to your feet.");
    say(QCTNAME(TP) + " lies down for a few moments on one of the"
                    + " ancient bedrolls, only to return to "
                    + TP->query_possessive() + " feet with a"
                    + " wistful sigh.\n");

    return 1;
} /* lie_down */


/*
 * Function name:        init
 * Description  :        add some verbs to the player
 */
public void
init()
{
    ::init();
    init_random_noise();

    add_action(lie_down, "lie");
    add_action(lie_down, "lay");
    add_action(lie_down, "rest");
    add_action(enter_hole, "enter");
    add_action(say_password, "incant");
    add_action(do_touch, "touch");
} /* init */


/*
 * Function name: random_noise
 * Description  : the wind is blowing in here
 * Returns      : int -- non-zero if noises should continue,
 *                 zero if they should stop
 */
public int
random_noise()
{
    tell_room(TO, BSN(        ({
        "A gust of wind blows suddenly through the chamber.",
        "The wind whistles softly through a hole in the base"
      + " of the wall to the east.",
        "A low whistle comes from the doorway to the"
      + " northwest, and wind blows suddenly through the"
      + " chamber.",
        })[random(3)] ) );

    return 1;
} /* random_noise */


/*
 * function name:    enter_hole
 * description  :    move the player up if they try to enter the
 *                   hole more verbosely
 * arguments    :    arg -- what the player typed
 * returns      :    1 -- success, 0 -- failure
 */
public int
enter_hole(string arg)
{
    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [dark] 'hole'"))
    {
        return 0;
    }

    if (TP->query_wiz_level())
    {
        WRITE("Normally, we would move the player 'down' here using"
            + " command(). Since you are a wiz, that won't work.");
    }

    TP->command("down");
    return 1;
} /* enter_hole */


/*
 * Function name:        reset_room
 * Description  :        Called when the room is updated. Here, we
 *                       add the emblem to the door, if it is not
 *                       already there.
 */
public void
reset_room()
{
    object  emblem;

    if (!present("kot_emblem"))
    {
        emblem =
            clone_object(DELRIMMON_DIR 
                       + "obj/normal_emblem")->move(this_object());
    }
} /* reset_room */
