#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define LEDGE_SUBLOC "_ledge_subloc"
#define IS_ON_LEDGE(ob) (ob->query_subloc() == LEDGE_SUBLOC)

public int     no_hide(string arg);
public int     do_jump(string arg);
public int     ledge_kill_check(string arg);
public string  describe_ledge_occupants(object for_obj);
public string  look_at_ledge();
public void    leave_inv(object ob, object to);

/*
 * function name:        create_gondor
 * description  :        set up the room with domain presets
 */
public void
create_gondor()
{
    set_short("a wide circular stone chamber");
    set_long(BSN("Long shadows are cast across the walls of this"
               + " wide stone chamber, its vaulted ceiling looming"
               + " high above the circular perimeter of the walls"
               + " which close in on all sides.")
               + "@@describe_ledge_occupants@@");

    add_prop(ROOM_I_INSIDE, 1);
    /* XXX add the light level! */

    add_item( ({ "ledge", "stony ledge" }),
        &look_at_ledge() );

    add_exit(DELRIMMON_DIR + "lakeside/caves/barracks", "east", 0, 1);

    add_subloc(LEDGE_SUBLOC, this_object());

} /* create_gondor */

/*
 * function name:        do_climb
 * description  :        a redefinition of gnadnar's function so we
 *                       get the messages we want (long way again!)
 */
public int
do_climb(string arg)
{
    object  *occupants,
             tp = this_player();

    if (arg == "down")
    {
        return do_jump(arg);
    }

    if (!strlen(arg) || ((arg != "up") && !parse_command(arg, ({}),
        "[up] [to] [the] [stony] 'stones' / 'ledge'")))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (IS_ON_LEDGE(tp))
    {
        notify_fail("You are already standing on the ledge.\n");
        return 0;
    }

    if (tp->query_prop(OBJ_I_HIDE) ||
        tp->query_prop(OBJ_I_INVIS) ||
        tp->query_invis())
    {
        write(break_string("You decide not to try, since that would " +
            "probably reveal your presence.", 75) + "\n");
        return 1;
    }

    if (sizeof(occupants = subinventory(LEDGE_SUBLOC)) > 1)
    {
        write("There is no room for you on the ledge.\n");
        return 1;
    }

    tp->set_no_show_composite(1);
    tp->move(this_object(), LEDGE_SUBLOC);
    write("You climb up the rocks to stand on the stony ledge.\n");
    say(QCTNAME(this_player()) + " climbs up the rocks to stand on " +
        "the stony ledge.\n");

    return 1;
}

/*
 * function name:        do_jump
 * description  :        a redefinition of gnadnar's func for message
 *                       purposes
 */
public int
do_jump(string arg)
{
    string vb;

    if (strlen(arg) &&
        arg != "down")
    {
        vb = capitalize(query_verb());
        notify_fail(vb + " where? " + vb + " down, perhaps?\n");
        return 0;
    }

    if (!IS_ON_LEDGE(this_player()))
    {
        notify_fail("You are already on the ground.\n");
        return 0;
    }

    this_player()->unset_no_show_composite();
    this_player()->move(this_object());

    write("You jump down from the ledge.\n");
    say(QCTNAME(this_player()) + " jumps down from the ledge.\n");

    return 1;
} /* do_jump */

string
occupant_names(object occupant, object for_obj)
{
    return ((occupant == for_obj) ? "you" : occupant->query_art_name(for_obj));
}

public string
describe_ledge_occupants(object for_obj)
{
    object *occupants;

    if (!sizeof(occupants = subinventory(LEDGE_SUBLOC)))
    {
        return "";
    }

    if (!for_obj)
    {
        for_obj = this_player();
    }

    return 
        capitalize(COMPOSITE_WORDS(map(occupants, &occupant_names(,for_obj)))) +
       (((sizeof(occupants) == 1) && (for_obj != occupants[0])) ? 
        " is " : " are ") + "standing on the ledge.\n";
}

/*
 * function name:        no_hide
 * description  :        redefinition of gnadnar's func for msgs
 */
public int
no_hide(string arg)
{
    if (IS_ON_LEDGE(this_player()))
    {
        write("It's too difficult to " + query_verb() +
            " while you are up on this ledge.\n");
        return 1;
    }

    return 0;
} /* no_hide */

/*
 * function name:        init
 * description  :        mask parent so we can call init_room_chairs()
 */
public void
init()
{
    ::init();

    add_action(do_climb, "climb");
    add_action(do_jump, "jump");
    add_action(do_jump, "down");
    add_action(do_jump, "d");
    add_action(no_hide, "hide");

    if (this_player()->query_wiz_level())
    {
        add_action(no_hide, "invis");
    }
} /* init */

/*
 * function name:        look_at
 * description  :        VBFC to describe ledge + occupants
 * arguments    :        string arg -- what's being looked at
 *                       null str -> it's the room
 * returns      :        string -- the description
 */
public string
look_at_ledge()
{
    return "A ledge is at one end of the room.\n" +
        describe_ledge_occupants(this_player());
} /* look_at */

/*
 * function name:        ledge_kill_check
 * description  :        persons on the ground cannot fight with
 *                       people on the ledge, and vise-versa
 * arguments:            arg -- what the player typed
 * returns      :        1 -- ok to attack, 0 -- not ok
 */
public int
ledge_kill_check(string arg)
{
} /* ledge_kill_check */

/*
 * function name:        leave_inv
 * description  :        Called when objects leave this container or
 *                       when an object is about to change its weight/
 *                       volume/light status.
 *                       We also want to make sure that the player
 *                       jumps off the ledge before leaving, and
 *                       gets rid of our combat props for this room
 * arguments:            ob: the object that just left this inventory
 *                       to: where it went
 */
public void
leave_inv(object ob, object to)
{
    string  chairname,
            vb = query_verb();

    if (living(ob) &&
        vb != "In" &&
        vb != "At")
    {
        ob->unset_no_show_composite();

        if (strlen(chairname = ob->query_prop(LEDGE_SUBLOC)))
        {
            stand_up(ob, chairname, 0);
        }
    }
    /* XXX make sure that we remove the attack props! */
} /* leave_inv */
