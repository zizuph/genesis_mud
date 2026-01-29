/*
 * - seating.c
 *
 * These are some routines to let you add seating into a room.
 * To get this to work, you need to:
 *
 * - include this file.
 * - at the end of your long desc, add a call to seat_desc() (optional)
 * - create an add_item and point it to seat_desc() (optional)
 * - add init_seat() into your init() function. (create if needed)
 */

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#define SUBLOC  "_subloc_sitting"

/*
 * This holds our data, went with a mapping instead of props
 * for ease of use and speed.
 *
 * mapping seated = ([ 
 *     <player> : ({ <int 1|2|3>, <0|player> }), ])
 *
 * 1 = sitting.
 * 2 = sitting with player in lap.
 * 3 = sitting in players lap.
 */
private mapping seated = ([]);

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (ob && !present(ob) && seated[ob])
    {
        ob->catch_tell("You arise from the chair and leave the room.\n");
        ob->unset_no_show_composite();
        ob->remove_subloc(SUBLOC);

        if (seated[ob][0] == 2 && (to = seated[ob][1]))
        {
            seated = m_delete(seated, to);
            to->unset_no_show_composite();
            to->catch_tell("You are dumped unceremoniously onto the "+
              "ground.\n");
            tell_room(this_object(), QCTNAME(to) + " is dumped " +
              "unceremoniously onto the ground.\n", to);
        }
        seated = m_delete(seated, ob);
    }
}

#define SIT_STR ({ "down", "chair", "in chair" })

public int
do_sit(string str)
{
    object *obs, ob;

    if (seated[this_player()])
    {
        return notify_fail("But you are already sitting!\n");
    }

    if ((member_array(str, SIT_STR) == -1) &&
        !sizeof(obs = FIND_STR_IN_ARR(str, m_indexes(seated)))) 
    {
        return notify_fail(capitalize(query_verb()) + " where?\n");
    }

    if (sizeof(obs))
    {
        if (sizeof(obs) > 1)
        {
            return notify_fail("You may only sit in one lap at a time.\n");
        }

        if (objectp(ob = seated[obs[0]][1]))
        {
            return notify_fail(QCTPNAME(obs[0]) + " laps is already " +
                "occupied.\n");
        }

        seated[this_player()] = ({ 3, obs[0] });
        seated[obs[0]] = ({ 2, this_player() });

        this_player()->catch_msg(
            "You climb into " + QTPNAME(obs[0]) + " lap.\n");
        obs[0]->catch_tell(this_player()->query_The_name(obs[0]) +
          " climbs into your lap.\n");
        say(QCTNAME(this_player()) + " climbs into " + QTPNAME(obs[0]) +
          " lap.\n", ({ obs[0], this_player() }));
    }
    else
    {
        seated[this_player()] = ({ 1, 0 });
        write("You sink down into one of the chairs.\n");
        say(QCTNAME(this_player())+ " sinks into one of the chairs.\n");
    }

    this_player()->set_no_show_composite(1);
    this_player()->add_subloc(SUBLOC, this_object());
    return 1;
}

public int
do_stand(string arg)
{
    object ob;
    mixed tmp;

    if (arg != "up")
    {
        return notify_fail("Stand up, maybe?\n");
    }

    if (!pointerp(tmp = seated[this_player()]))
    {
        return notify_fail("But you are not sitting!\n");
    }

    this_player()->unset_no_show_composite();
    this_player()->remove_subloc(SUBLOC);

    if (tmp[0] == 3 && objectp(ob = tmp[1]))
    {
        this_player()->catch_msg(
            "You climb off of " + QTPNAME(ob) + " lap.\n");
        ob->catch_tell(this_player()->query_The_name(ob) + " climbs off "+
          "of your lap.\n");
        say(QCTNAME(this_player()) + " climbs out of " + QTPNAME(ob) +
          " lap.\n", ({ this_player(), ob }));

        seated[ob] = ({ 1, 0 });
    }
    else
    {
        write("You arise from your chair.\n");
        say(QCTNAME(this_player()) + " arises from one of the chairs.\n");

        if (tmp[0] == 2 && objectp(ob = tmp[1]))
        {
            ob->unset_no_show_composite();

            ob->catch_tell("You are dumped unceremoniously "+
              "onto the floor.\n");
            tell_room(this_object(), QCTNAME(ob) + " is dumped "+
              "unceremoniously onto the floor.\n", ob);

            seated = m_delete(seated, ob);
        }
    }
    seated = m_delete(seated, this_player());
    return 1;
}

public string
seat_desc()
{
    object *obs = ({});
    string *who = ({}), str;
    int i, j;

    str = "Several chairs are arranged about the giant square-shaped table.\n";

    obs = m_indexes(seated) - ({ 0 });
    i = -1; j = sizeof(obs);

    if (j < 1)
        return str;

    if ((j == 1) && (obs[0] == this_player()))
        return str + "You are seated comfortably within one of the chairs.\n";

    while (++i < j)
    {
        if (seated[obs[i]][0] > 2)
            continue;

        if (seated[obs[i]][0] == 2)
        {
            object ob = seated[obs[i]][1];

            if (obs[i] == this_player())
            {
                who += ({ "yourself with " +
                    ob->query_the_name(this_player()) +
                    " snuggled up in your lap" });
            }
            else
            {
                who += ({ obs[i]->query_the_name(this_player()) +
                    " with " + (ob == this_player() ? "you" : 
                     ob->query_the_name(this_player())) +
                     " snuggled up in "+ 
                     obs[i]->query_possessive() +" lap" });
            }
            continue;
        }

        if (obs[i] == this_player())
        {
            who += ({ "yourself" });
        }
        else
        {
            who += ({ obs[i]->query_the_name(this_player()) });
        }
    }

    return str + capitalize(COMPOSITE_WORDS(who)) + (j == 1 ? 
        " is" : " are") +" sitting comfortably in the chairs around the table.\n";
}

nomask string
show_subloc(string subloc, object on, object for_ob)
{
    string str;
    mixed tmp;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) || subloc != SUBLOC)
        return "";

    if (!pointerp(tmp = seated[on]))
        return "";

    if (for_ob == on)
        str = "You are";
    else
        str = capitalize(on->query_pronoun()) + " is";

    if (tmp[0] < 3)
    {
        str += " sitting in a chair";
        if (objectp(tmp = tmp[1]))
        {
            str += " with " + (tmp == for_ob ? "you" :
              tmp->query_the_name(on) ) + " snuggled up on " +
            (for_ob == on ? "your" : on->query_possessive()) +" lap";
        }
        return str + ".\n";
    }

    if (tmp[1] == for_ob)
        return str + " snuggled up on your lap.\n";

    return str + " snuggled up on " + 
        tmp[1]->query_the_name(for_ob) + "'s lap.\n";
}

void
init_seat()
{
    add_action(  do_sit,  "sit"   );
    add_action( do_stand, "stand" );
}

