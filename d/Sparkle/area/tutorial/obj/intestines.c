/*
 *  /d/Sparkle/area/tutorial/obj/intestines.c
 *
 *  This leftover can be cut from the animals which inhabit the
 *  Sterling Woods. It is a quest item. These can be collected for
 *  Farmer Brown, who will dry them and make them into a rope.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth) 
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/leftover";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_leftover();
public string      describe_long();
public void        init();
public int         make_rope(string arg);
public void        leave_env(object from, object to);
public void        blow_away(object from);


/*
 * Function name:        create_leftover
 * Description  :        set up the leftover
 */
public void
create_leftover()
{
    set_name("intestine");
    add_name( ({ "leftover", "gut",
                 "_tutorial_intestine", "_tutorial_item" }) );
    set_adj( ({ "animal" }) );
    set_short("animal intestine");
    set_long(describe_long);
 
    add_prop(OBJ_M_NO_GIVE, "You don't feel like giving that away. You"
      + " could probably <show> it to someone, though.\n");

    set_decay_time(9999); /* lets not have them decay too easily */
    set_amount(3);

    setuid();
    seteuid(getuid());
} /* create_leftover */


/*
 * Function name:        describe_long
 * Description  :        provide a bit-dependant description of the
 *                       object
 * Returns      :        string - the long description
 */
public string
describe_long()
{
    string   txt = "These are the scavenged intestines of some large"
                 + " animal. ";

    if (CHECK_TUTORIAL_BIT(INSTRUCT_BIT))
    {
        txt += "You can <make rope> to make it into a rope.";
    }

    return txt + "\n";
} /* describe_long */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(make_rope, "make");
} /* init */


/*
 * Function name:        make_rope
 * Description  :        allow the player to make some rope from the
 *                       intestine
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
make_rope(string arg)
{
    object  rope;
    mixed  *obj;
    object  intestine;
    int     num;

    if (!strlen(arg))
    {
        notify_fail("What do you want to make?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %i 'in' / 'into' [to] [a] 'rope'", obj) ||
        !sizeof(obj = NORMAL_ACCESS(obj, 0, 0)))
    {
        if (arg == "rope")
        {
            notify_fail("Make what into a rope?\n");
        }
        else if (arg == "intestine" || arg == "intestines")
        {
            notify_fail("Make the intestine into what?\n");
        }
        else
        {
            notify_fail("Make what into what?\n");
        }
        return 0;
    }

    if (!obj[0]->id("_tutorial_intestine"))
    {
        notify_fail("You can't make that into a rope.\n");
        return 0;
    }

    if (!CHECK_TUTORIAL_BIT(INSTRUCT_BIT))
    {
        notify_fail("You haven't been taught how to do that.\n");
        return 0;
    }

    if (sizeof(obj) > 1)
    {
        // Inidicated more than one item....
        return 0;
    }

    intestine = obj[0];

    if (intestine->num_heap() > 1)
    {
        write("You only need to use one " + intestine->singular_short()
          + " to make rope.\n");
        return 1;
    }

    if (!objectp(rope = present("_tutorial_rope", this_player())))
    {
        write("You lay the intestine along the ground, and skillfully"
          + " work with it until it becomes a servicable length of"
          + " rope.\n");
        rope = clone_object(OBJ_DIR + "rope")->move(this_player());
    }
    else
    {
        if (rope->query_length() >= 100)
        {
            write("The rope you already have seems long enough, so you"
              + " decide not to bother.\n");
            return 1;
        }
        rope->increase_length();
        write("You lay the intestine along the ground, and skillfully"
          + " work with it until it becomes a servicable length of rope."
          + " You then add it to your existing rope, increasing its"
          + " length to around " + LANG_NUM2WORD(rope->query_length())
          + " feet.\n");
    }

    intestine->restore_heap();
    if ((num = intestine->num_heap()) <= 1)
    {
        intestine->remove_object();
    }
    else
    {
        intestine->set_heap_size(num - 1);
    }

    return 1;
} /* make_rope */


/*
 * Function name:        leave_env
 * Description  :        we don't want these piling up anywhere, so we
 *                       have them vanish if the player drops them
 * Arguments    :        object from - where it came from
 *                       object to   - where it went
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (!objectp(from) || !objectp(to) || !living(from))
    {
        return;
    }

    if (to->query_prop(ROOM_I_IS))
    {
        set_alarm(0.0, 0.0, &blow_away(from));
        return;
    }

    return;
} /* leave_env */


/*
 * Function name:        blow_away
 * Description  :        Get rid of the item when it is dropped. Also
 *                       check to see if anyone has picked it up first.
 * Arguments    :        object from - the player who dropped it
 */
public void
blow_away(object from)
{
    if (interactive(environment(this_object())))
    {
        return;
    }

    from->catch_tell("You toss the intestine away, and it is lost from"
      + " view.\n");
    remove_object();
} /* blow_away */


string
query_recover()
{
    return MASTER + ":" + "#ic#" + item_count + "#";
}


void
init_recover(string arg)
{
    int     ic;
    string  foo;

    sscanf(arg, "%s#ic#%d#", foo, ic);
    if (ic > 0)
        set_heap_size(ic);
}

