/* ctower_manager.c
 *
 * This object tries to manage access to the tower, so
 * that only one person is allowed in at one time, and
 * the tower is fully reset for each new player.  If a
 * player goes linkdead while in the tower, he/she has
 * 30 minutes to revive before someone else is allowed
 * in.
 */

#pragma strict_types
#pragma no_clone
#pragma no_shadow

#include "ctower.h"

#define LD_TIME (60 * 30)

static int need_reset;
static object quester;

static object *reset_objects = ({});

static nomask void
do_reset()
{
    if (!need_reset)
    {
        return;
    }

    reset_objects -= ({ 0 });
    reset_objects->ctower_reset();
    need_reset = quester = 0;
}

void
reset()
{
    int ld;

    if (!quester)
    {
        /* No quester in the tower, so reset */
        do_reset();
        return;
    }

    /* Is the quester linkdead? */
    if ((ld = quester->query_linkdead()) > 0)
    {
        /* The quester is ld, so give him some time before
         * we reset and allow someone else in.
         */
        if (ld > LD_TIME)
	{
            do_reset();
	}
    }
    else
    {
        /* The quester is active, so check if he has left the tower */
        if (!environment(quester)->query_inside_ctower())
	{
            do_reset();
	}
    }
}

void
create()
{
    reset();
}

nomask void
kick_out_of_tower(object ob)
{
    if (!ob)
    {
        return;
    }

    ob->catch_tell("You feel a strange tingle through your body, " +
        "and suddenly you find yourself in a different place!\n");

    ob->move_living("X", CTOWER_ROOM + "pointday", 1);
}

nomask int
check_tower_entrance(object ob)
{
    if ((quester == ob) ||
        ob->query_wiz_level())
    {
        return 1;
    }

    return 0;
}    

nomask void
enter_tower(object ob)
{
    if (!check_tower_entrance(ob))
    {
        set_alarm(1.0, 0.0, &kick_out_of_tower(ob));   
    }
}

nomask int
register_quester(object ob)
{
    if (quester || need_reset)
    {
        return 0;
    }

    if (!quester->query_wiz_level())
    {
        quester = ob;
    }

    return 1;
}

nomask void
leave_tower(object ob)
{
    deep_inventory(ob)->remove_ctower_object();
    need_reset = 1;
}

nomask void
register_reset(object ob)
{
    reset_objects += ({ ob });
}

nomask void
remove_object()
{
    if (quester || need_reset || sizeof(reset_objects))
    {
        throw("Cannot remove manager unless tower is inactive\n");
    }

    destruct();
}

nomask void
remove_ctower_manager()
{
    destruct();
}
