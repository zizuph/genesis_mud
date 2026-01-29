/* ambush1.c
 * An elven encampment in the Qualinesti forest.
 * There is an oak with a sharpshooter sitting on it.
 *
 * Blizzard, 01/2003
 */

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "../local.h"

inherit FORESTBASE;

#define OAK_ROOM       CDIR + "oak1.c"

object  archer;

string       branch_desc();
int          climb_tree(string args);
int          exit_check();
object       *check_enemies();
int          filter_enemy(object enemy);
varargs int  friend_or_foe(mixed who);
int          hold_him(object who);
int          let_him_pass(object who);

object guard;

string
query_sniper_room()
{
    return OAK_ROOM;
}

void
reset_qualinesti_room()
{
    if ( !guard )
    {
        guard = clone_object(NPC + "guard1");
        guard->move(TO);
        guard->command("hide");
    }

}

public void
create_forest()
{
    add_my_desc("A small clearing opens to your east. You also notice " +
        "a big oak standing here.\n");

    add_item(({"oak", "tree", "big tree", "big oak"}),
        "This oak, with a wide and hide stretched branches, looks " +
        "quite old. It makes a nice place for a lookout.\n");
    add_item(({"branches", "foliage" }), &branch_desc());
    add_item(({ "opening", "clearing" }),
        "There seem to be a small clearing east of here. You feel a scent " +
        "of burning wood coming from that direction.\n");
    add_item(({ "trail", "trails" }),
        "As you look around, you realize there is a " +
        "barely noticable trail leading westwards.\n");
        
    OUTSIDE;

    add_exit(CDIR + "camp1.c", "east", "@@exit_check", 2);
    add_exit(FDIR + "path8.c", "west", 0, 2);

    reset_qualinesti_room();

}

/*
 * Function:    query_range_targets
 *
 * Description: Returns information about adjacent rooms
 *              that you can reach with missile weapons
 *              from this room.
 *
 * Arguments:   (object) The person that wishes to fire
 *              into an adjacent room.
 *
 * Returns:     An array with the following content. If
 *              there is more then one room accessible
 *              from this room, each room pads their
 *              values to the array.
 *
 * ({ path to remote room,
 *    matching pattern with parse_command syntax,
 *    description of remote room,
 *    description of this room as seen from remote room
 *  })
 *
 */

mixed
query_range_targets(object archer)
{
   seteuid(getuid(this_object()));
   (OAK_ROOM)->load_me();
   return ({    (OAK_ROOM),
       "[on] [the] 'oak' / 'tree'",
       "in the oak",
       "the path below" });
}

void
init()
{
    ::init();
    add_action(climb_tree, "climb");
}

int
climb_tree(string args)
{
    if ( !stringp(args) )
    {
        notify_fail("Climb oak?\n");
        return 0;
    }

    if ( args == "up" || args == "oak" || args == "tree" || args == "big oak" )
    {
        if ( guard = present("_guard_", TO) /*&& CAN_SEE(guard, TP)*/ &&
            !TP->query_wiz_level() )
        { 
            notify_fail("The elf is standing too close to the tree. " +
                "It is impossible to climb the oak.\n");
            return 0;
        }

        write("You climb up the trunk of the oak.\n");
        tell_room(this_object(), QCTNAME(this_player()) +
            " climbs up the trunk of the oak.\n", ({ this_player() }));
        tell_room(OAK_ROOM, QCTNAME(this_player()) + " arrives from below.\n",
            ({ this_player() }));
        this_player()->move_living("M", OAK_ROOM);
        return 1;
    } 
    else
    {
        notify_fail("Climb oak?\n");
        return 0;
    }
}

string
branch_desc()
{
    object *seen;

    seen = FILTER_LIVE((OAK_ROOM)->subinventory());
    seen = FILTER_CAN_SEE(seen, this_player());

    if (sizeof(seen))
    {
        return "The branches stretches far over your head.\n" +
            "You see " + COMPOSITE_LIVE(seen) + " standing on one " +
            "of the solid branches high above you.\n";
    }
    else
    {
        return "The branches stretches far over your head.\n";
    }
}

int
exit_check()
{
    if ( (guard = present("_guard_", TO)) &&
        (TP->query_race_name() == "kender") )
    {
        TP->catch_msg("You stop and look around slowly. Intrigued, you pick " +
            "a pine cone and throw it into the trees. Then you "+
            "skillfully sneak east, wondering if anyone caught that!\n");
        tell_room(TO, QCTNAME(TP) + " throws something into the trees. " +
            "You look in that direction, but after a moment you realize " +
            QTNAME(TP) + " is gone!\n", TP);
        TP->catch_msg("You giggle mischievously.\n");

        return 0;
    }

    if ( (guard = present("_guard_", TO)) && TP->query_prop(I_KILLED_ELF) &&
        CAN_SEE(guard, TP) )
    {
        TP->catch_msg(QCTNAME(guard) + " skillfully blocks your way.\n");
        tell_room(TO, QCTNAME(guard) + " stops " + QTNAME(TP) +
            " from going west.\n", TP);
        switch ( random(3) )
        {
        case 0:
            guard->command("say You shall not pass!");
        break;
        case 1:
            TP->catch_msg(QCTNAME(guard) + " scowls madly at you.\n");
            tell_room(TO, QCTNAME(guard) + " scowls madly at " + QTNAME(TP) +
                ".\n", TP);
        break;
        case 2:
            guard->command("emote laughs.");
            guard->command("say No way!");
        break;
        }

        return 1;
    }

    if ( (guard = present("_guard_", TO)) && !(TP->query_prop(ELVEN_TOKEN)) &&
        CAN_SEE(guard, TP) )
    {
        TP->catch_msg(QCTNAME(guard) + " is standing in your way.\n");
        tell_room(TO, QCTNAME(guard) + " stops " + QTNAME(TP) +
            " from going east.\n", TP);
        switch (random(3))
        {
        case 0:
            guard->command("say I told you to wait! Stay there!");
        break;
        case 1:
            guard->command("say I warn you! Stay there!");
        break;
        case 2:
            guard->command("say Stay there!");
        break;
        }

        return 1;
    }

    return 0;
}

/* Function name : filter_enemy
 * Description   : filter enemies
 * Returns       : 1    if is enemy
 *                 0    if not
 */
public int
filter_enemy(object enemy)
{
    return ( interactive(enemy) && (friend_or_foe(enemy) == -1) );
}

/* Function name : check_enemies
 * Description   : check if the person is enemy or not
 */
object *
check_enemies()
{
    return filter(all_inventory(TO), filter_enemy);
}

/*
 * Function name: friend_or_foe
 * Description  : Decides if it is a friend or enemy
 * Arguments    : object who - we check him
 * Returns      :  1    - enemy
 *                 0    - other
 */
varargs int
friend_or_foe(mixed who)
{
    if ( stringp(who) )
    {
        who = find_living(lower_case(who));
    }
    else if ( !objectp(who) )
    {
        who = TP;
    }

    if ( !objectp(who) )
        return 0;

    if ( who->query_dragonarmy_occ_member() )
        return -1;

    if ( who->query_guild_member("Priests of Takhisis") )
        return -1;
    
    if ( who->query_prop(I_KILLED_ELF) )
        return -1;

    if ( who->query_prop(ELVEN_TOKEN) )
        return 1;

}



int
let_him_pass(object who)
{
    if ( guard = present("_guard_", TO) && !(who->query_prop(ELVEN_TOKEN)) )
    {
        if ( E(who) == TO )
        {
            who->catch_msg("Suddenly, a strange whistling sound may be " +
                "heard. The elf relaxes a bit, but still keeps observing " +
                "you. \nIt seems you may pass now.\n");


            if ( !(who->query_prop(ELVEN_TOKEN)) )
                who->add_prop(ELVEN_TOKEN, 1);

            return 1;
        }
        
        return 0;
    }

    return 0;

}

int
hold_him(object who)
{
    if ( !objectp(who) || E(who) != TO )
    {
        return 0;
    }

    if ( guard = present("_guard_", TO) )
    {
        who->catch_msg(QCTNAME(guard) + " watches the area, aiming at you " +
            "with his sleek ashwood longbow. He seems to be waiting for " +
            "something.\n");
        set_alarm(5.0, 0.0, &let_him_pass(who));

        return 1;
    }

}

int
stop_intruder(object who)
{
    object *enemy, *friend;

    if ( !objectp(who) || E(who) != TO )
    {
        return 0;
    }

    if ( (guard = present("_guard_", TO)) )
    {
        guard->command("reveal me");
        guard->remove_descr();
        guard->add_descr(" aiming at you with " + POSSESSIVE(guard) +
            " sleek ashwood longbow");

        if ( friend_or_foe(who) == 1 )
        {
            switch( random(3) )
            {
            case 0:
                guard->command("say Stay there, " + who->query_race_name() +
                    "!");
                guard->command("say Ahh, it is you again. You may pass.");
            break;
            case 1:
                guard->command("say You again. All right, move along.");
            break;
            case 2:
                who->catch_msg(QCTNAME(guard) + " recognizes you and allows " +
                    "you pass.\n");
                tell_room(TO, QCTNAME(guard) + " recognizes " + QTNAME(who) +
                    " and allows " + OBJECTIVE(who) + " pass.\n", who);
            break;
            }

            return 0;

        }
        else
        {
            switch ( random(3) )
            {
            case 0:
                guard->command("say You there! Stop!");
            break;
            case 1:
                guard->command("say Stay there!");
            break;
            case 2:
                guard->command("emote stands in your way.");
            break;
            }
        }

        enemy  = check_enemies();

        if ( sizeof(enemy) )
        {
            guard->attack_him(enemy, OAK_ROOM);
            return 1;
        }

        hold_him(who);

        return 1;
    }

    if ( !guard )
    {
        if ( !random(4) )
        {
            who->catch_msg("You look around slowly.\n");
            tell_room(TO, QCTNAME(who) + " looks around slowly.\n", who);

            return 0;
        }
    }

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if ( interactive(ob) && !ob->query_invis() )
        set_alarm(1.0, 0.0, &stop_intruder(ob));

}

int
hide_again(object guard)
{
    guard->command("hide");
    guard->remove_descr();
    guard->add_descr(" watching the forest");
    return 1;
}

void
leave_inv(object ob, object new)
{
    ::leave_inv(ob, new);

    if ( guard = present("_guard_", TO) )
        set_alarm(1.0, 0.0, &hide_again(guard));
}
