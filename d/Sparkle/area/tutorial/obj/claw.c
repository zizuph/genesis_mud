/*
 *  /d/Sparkle/area/tutorial/obj/claw.c
 *
 *  This leftover can be cut from the mountain lions which inhabit the
 *  Mountains. It is a quest item. These can be attached to the rope
 *  to make a grappling hook.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth) 
 */
#pragma strict_types
#include "../defs.h"
#include "/d/Sparkle/sys/quests.h"

inherit "/std/leftover";
inherit LIB_DIR + "quest_reward";

#include <cmdparse.h>
#include <macros.h>
#include <language.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_leftover();
public string      describe_long();
public void        init();
public int         make_hook(string arg);
public void        leave_env(object from, object to);
public void        blow_away(object from);


/*
 * Function name:        create_leftover
 * Description  :        set up the leftover
 */
public void
create_leftover()
{
    set_name("claw");
    add_name( ({ "leftover", "_tutorial_claw", "_tutorial_item" }) );
    set_adj( ({ "animal", "lion" }) );
    set_short("lion claw");
    set_long(describe_long);
 
    set_decay_time(9999); /* lets not have them decay too easily */
    set_amount(1);

    add_prop(OBJ_M_NO_GIVE, "You don't feel like giving the claw away."
      + " You could probably <show> it to someone, if you wished.\n");

    setuid();
    seteuid(getuid());
} /* create_leftover */


/*
 * Function name:        describe_long
 * Description  :        provide a variable description of the
 *                       object
 * Returns      :        string - the long description
 */
public string
describe_long()
{
    mixed    rope;
    string   txt = "This is the scavenged claw of a mountain lion. ";

    if (objectp(rope = present("_tutorial_rope", this_player()))
        && rope->query_length() >= 100)
    {
        txt += "You can <attach> it to the rope.";
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

    add_action(make_hook, "attach");
} /* init */


/*
 * Function name:        make_hook
 * Description  :        allow the player to make hooks on the rope
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
make_hook(string arg)
{
    object  rope;
    int     num;
    mixed  *obj;
    object  claw;

    if (!strlen(arg))
    {
        notify_fail("What do you want to attach?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] [a] [animal] [lion] %i 'to' [the] %o", obj, rope) ||
        !sizeof(obj = NORMAL_ACCESS(obj, 0, 0)))
    {
        notify_fail("Attach what to where?\n");
        return 0;
    }

    if (!obj[0]->id("_tutorial_claw"))
    {
        notify_fail("You can't attach that to the rope.\n");
        return 0;
    }

    if (!rope->id("_tutorial_rope"))
    {
        if (rope->id("_tutorial_hook"))
        {
            notify_fail("The grappling hook looks complete. You don't"
              + " need to add another claw.\n");
            return 0;
        }

        notify_fail("Attaching the claw to that would do no good.\n");
        return 0;
    }

    if (rope->query_length() < 100)
    {
        write("The rope needs to be longer first.\n");
        return 1;
    }

    if (sizeof(obj) > 1)
    {
        // Inidicated more than one item....
        return 0;
    }

    claw = obj[0];

    if (claw->num_heap() > 1)
    {
        write("You can only attach one " + claw->singular_short()
          + " to the rope at a time.\n");
        return 1;
    }

    num = rope->query_claws();

    if (num < 2)
    {
        rope->increase_claws();

        write("You carefully fix a lion claw to the end of the rope."
          + " You'll need " + LANG_NUM2WORD(2 - num) + " more to complete"
          + " the grappling hook.\n");
    }
    else
    {
        write("You complete the grappling hook by adding the last"
          + " claw.\n");
        write("This looks like a very useful tool, indeed!\n");

        rope->remove_object();
        give_reward(this_player(), TUTORIAL_ROPE_GROUP, TUTORIAL_ROPE_BIT,
            TUTORIAL_ROPE_EXP, "Tutorial Rope");
        rope = clone_object(
                    WEP_DIR + "grappling_hook")->move(this_player());
    }


    claw->restore_heap();
    if ((num = claw->num_heap()) <= 1)
    {
        claw->remove_object();
    }
    else
    {
        claw->set_heap_size(num - 1);
    }

    return 1;
} /* make_hook */


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

    from->catch_tell("You toss the claw away, and it is lost from"
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

