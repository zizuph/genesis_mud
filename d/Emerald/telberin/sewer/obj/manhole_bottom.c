/*
 *  /d/Emerald/telberin/sewer/obj/manhole_bottom.c
 *
 *  This is a manhole cover which grants access to the telberin
 *  sewers. It has two sides, and this is the bottom one.
 *
 *  Copyright (c) October 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

/* global variables */
public int         Open = 0;   /* is the manhole cover open? */
public object      Topside;    /* the room topside of the manhole */

/* prototypes */
public void        create_object();
public string      describe();
public void        set_open(int i);
public void        change_cover(int i);
public int         open_cover(string arg);
public void        init();

public void        set_topside(object o) { Topside = o; }
public int         query_open() { return Open; }


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("ladder");
    set_adj( ({ "grimy", "iron", "black" }) );

    set_short("grimy iron ladder");
    set_long(describe);

    add_prop(OBJ_M_NO_GET, "You tug at the ladder, but it is"
      + " securely fastened to the brick wall.\n");
    add_prop(OBJ_I_WEIGHT, 40002);
    add_prop(OBJ_I_VOLUME, 15234);

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        describe
 * Description  :        provide a variable long description for
 *                       the ladder which tells whether the manhole
 *                       cover is open or closed.
 * Returns      :        string - the description to send to set_long
 */
public string
describe()
{
    string   cover;

    switch(Open)
    {
        case 1:
            cover = "open";
            break;
        default:
            cover = "closed";
            break;
    }
 
    return "An iron ladder is fastened to the brick wall here,"
      + " leading up toward " + LANG_ADDART(cover)
      + " manhole cover in the ceiling. The rungs of"
      + " the ladder are rugged and covered with grime.\n";
} /* describe */


/*
 * Function name:        set_open
 * Description  :        a toggle for the open/closed state of
 *                       the manhole cover
 * Arguments    :        int i: 1 = open, 0 = closed
 */
public void
set_open(int i)
{
    Open = i;
    Topside->change_cover(i);
} /* set_open */


/*
 * Function name:        change_cover
 * Description  :        allow us to change the open/closed state
 *                       of the manhole cover from above. This
 *                       function would be called from the Topside
 *                       file.
 * Arguments    :        int i: 1 = open, 0 = closed
 */
public void
change_cover(int i)
{
    if (i = 1)
    {
        tell_room(environment(this_object()),
            "A grating sound comes from above, and you glimpse"
          + " the manhole cover at the top of the ladder sliding"
          + " closed.\n");
        return;
    }

    tell_room(environment(this_object()),
        "The sharp grating of stone echoes from above, and you"
      + " glimpse a manhole cover being pulled open.\n");
    return;
} /* change_cover */


/*
 * Function name:        open_cover
 * Description  :        allow players to open the manhole cover
 * Arguments    :        string arg: what the player typed
 * Returns      :        int: 1 = success, 0 = failure
 */
public int
open_cover(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [grated] [manhole] 'cover'") &&
        !parse_command(arg, ({}),
        "[the] [grated] 'manhole' [cover]"))
    {
        return 0; /* can't parse player syntax */
    }

    if (query_verb() == "open")
    {
        if (Open)
        {
            write("The manhole cover is already open.\n");
            return 1;
        }

        write("You climb up the ladder and slide the cover of"
          + " the manhole open.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())
          + " climbs up a nearby ladder and slides a manhole cover"
          + " open.\n", this_player());
        Open = 1;
        Topside->change_cover(1);

        return 1;
    }

    if (!Open)
    {
        write("The manhole cover is already closed.\n");
        return 1;
    }

    write("You climb up the ladder and pull the manhole cover"
      + " over the hole, sealing the exit.\n");
    tell_room(environment(this_object()), QCTNAME(this_player())
      + " climbs up a nearby ladder and pulls a manhole cover"
      + " closed.\n", this_player());
    Open = 0;
    Topside->change_cover(0);

    return 1;
} /* open_cover */


/*
 * Function name:        climb_ladder
 * Description  :        allow players to try to climb up
 *                       or down the ladder
 * Arguments    :        string arg: what the player typed
 * Returns      :        int: 1 = success, 0 = failure
 */
public int
climb_ladder(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you want to " + query_verb + "?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [down] [the] [grimy] [iron] 'ladder' / 'manhole'"))
    {
        return 0; /* can't parse the player syntax */
    }

    if (!Open)
    {
        write("You climb up the ladder, and are halted at the"
          + " grating of the closed manhole cover. You make"
          + " your way back down to the ledge again.\n");
        return 1;
    }

    write("Grasping the metal rungs of the ladder, you climb up"
      + " out of the sewers and emerge onto the city streets.\n");
    this_player()->move_living("M", environment(Topside), 1, 1);
    tell_room(environment(this_object()), QCTNAME(this_player())
      + " climbs up a nearby ladder and disappears through an"
      + " open manhole.\n");

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

    add_action(open_cover, "open");
    add_action(open_cover, "close");
    add_action(climb_ladder, "climb");
} /* init */
