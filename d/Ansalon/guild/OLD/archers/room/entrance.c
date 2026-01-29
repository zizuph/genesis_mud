/* File name: entrance.c
 * Entrance to the Elven Archers' guild. There is a tree with a
 * sharpshooter on it.
 *
 * Blizzard, 05.11.2003
 */

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Krynn/qualinesti/local.h"
#include "../guild.h"

inherit      FORESTBASE;

#define      TREE_ROOM       GUILD_ROOM + "guard_tree1.c"

string       branch_desc();
int          climb_tree(string args);
int          exit_check();
object       *check_enemies();
int          filter_enemy(object enemy);
varargs int  friend_or_foe(mixed who);

object guard1, guard2, guard3, guard;


string
query_sniper_room()
{
    return TREE_ROOM;
}


void
reset_qualinesti_room()
{
    if ( !guard1 )
    {
        guard1 = clone_object(GUILD_NPC + "guard1");
        guard1->move(TO);
        guard1->command("hide");
    }

    if ( !guard3 )
    {
        guard3 = clone_object(GUILD_STD + "guard_base");
        guard3->move(TO);
        guard3->command("hide");
    }

    if ( !guard2 )
    {
        guard2 = clone_object(GUILD_STD + "guard_base");
        guard2->move(TO);
        guard2->command("hide");
    }
    

}

public void
create_forest()
{
    set_long_desc("You are standing at the entrance to the camp, that " +
        "was set here as a training ground for the elven elite warriors.");
    add_my_desc("\n");

    add_item(({"tree", "big tree", "high tree"}),
        "There are many trees around, but this particualr one has wide " +
        "stretched branches, what makes it an excellent place for a " +
        "lookout.\n");
    add_item(({"branches", "foliage" }), &branch_desc());
    add_item(({ "opening", "clearing" }),
        "There is a clearing just to the north. Further in that direction " +
        "you notice a bigger encampment. It seem you have found the " +
        "elven archers training base.\n");
        
    OUTSIDE;

    add_exit(GUILD_ROOM + "archer_camp2.c", "north", "@@exit_check", 2);

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

   (TREE_ROOM)->load_me();

   return ({    (TREE_ROOM),
       "[on] [the] [big] [high] 'tree'",
       "on the tree",
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
        notify_fail("Climb the big tree?\n");
        return 0;
    }

    if ( args == "up" || args == "tree" || args == "big tree" ||
        args == "high tree" )
    {
        if ( guard = present("_guard_", TO) /*&& CAN_SEE(guard, TP)*/ &&
            !TP->query_wiz_level() )
        { 
            notify_fail("The guard glares at you angrily. You decide " +
                "to step back.\n");
            return 0;
        }

        write("You climb up the trunk of the big tree.\n");
        tell_room(this_object(), QCTNAME(this_player()) +
            " climbs up the trunk of the big tree.\n", ({ this_player() }));
        tell_room(TREE_ROOM, QCTNAME(this_player()) + " arrives from below.\n",
            ({ this_player() }));
        this_player()->move_living("M", TREE_ROOM);
        return 1;
    } 
    else
    {
        notify_fail("Climb the big tree?\n");
        return 0;
    }
}

string
branch_desc()
{
    object *seen;

    seen = FILTER_LIVE((TREE_ROOM)->subinventory());
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
stop_intruder(object who)
{
    object *enemy, *friend;

    if ( !objectp(who) || E(who) != TO )
    {
        return 0;
    }

    if ( !guard1 && !guard2 && !guard3 )
        return 0;      

    enemy  = check_enemies();

    if ( sizeof(enemy) )
    {
        guard->attack_him(enemy, TREE_ROOM);
        return 1;
    }


}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if ( interactive(ob) && !ob->query_invis() )
        set_alarm(1.0, 0.0, &stop_intruder(ob));

}
