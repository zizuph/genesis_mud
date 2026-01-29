#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <language.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define FALL_LOG        ("/d/Emerald/log/del_rimmon/cliff_fall")

/* prototypes */
public void    create_del_rimmon();
public void    enter_inv(object ob, object from);
public void    reach_bottom(object ob, object from);
public void    do_log(object ob, string logtxt);


/*
 * Function name:        create_del_rimmon
 * Description  :        This is the room players enter for the
 *                       duration of the fall from the ledge
 *                       to the ground.
 */
public void
create_del_rimmon()
{
    set_short("you plunge in a free fall from the ledge, and the"
            + " ground speeds towards you");
    set_long(CAP(short()) + "!\n");

    add_item( ({ "ground", "down" }), BSN(
        "The ground is rushing towards you with alarming speed!"));
    add_item( ({ "cliff", "cliffs", "ledge" }), BSN(
        "The cliff rushes by you leaving the ledge high above."));
} /* create_del_rimmon */


/*
 * Function name:        enter_inv
 * Description  :        called to catch the player or other objects
 *                       which are dropped off of the cliff.
 * Arguments    :        object ob -- the object in question
 *                       object from -- its former location
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    set_alarm(1.0, 0.0, &reach_bottom(ob, from));
} /* enter_inv */


/*
 * Function name:        reach_bottom
 * Description  :        move the object or player to the cliff
 *                       base, and apply damage, etc.
 * Arguments    :        object ob -- the object or player
 *                       object from -- where it came from
 */
public void
reach_bottom(object ob, object from)
{
    object  cbase = find_object(from->query_cliff_base());
    int     falldamage;

    falldamage = 1000 + (random(ob->query_encumberance_weight() * 5));
    ob->reduce_hit_point(falldamage);
    do_log(ob, " fell off ledge. Damage: " + falldamage);

    if (ob->query_hp() <= 0)
    {
        ob->do_die(TO);
        do_log(ob, " DIED FROM FALLING OFF THE CLIFF LEDGE");
    }

    tell_room(cbase, CAP(LANG_ADDART(ob->short())) + " falls suddenly"
      + " from above, and lands on the ground with a thud.\n");
    ob->move_living("M", cbase, 1, 1);
find_living("gorboth")->catch_msg("Fallroom: "+from->query_cliff_base()+"\n");
} /* reach_bottom */


/*
 * function name:        do_log
 * description  :        helps us log unpleasantries that happen
 *                       players here
 * arguments    :        object ob -- the player
 *                       string logtxt -- what happened
 */
public void
do_log(object ob, string logtxt)
{
    log_file(FALL_LOG, ctime(time())
           + " -- " + ob->query_name() + " ("
           + ob->query_average_stat() + ")"
           + logtxt + ".\n");

    return;
} /* do_log */
