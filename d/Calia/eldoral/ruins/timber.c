/*
 * timber.c
 *
 * This room is actuall on a long timber projecting out of the end
 * of a ruined tower, hanging out above the north ravine on the island.
 * Players must jump from here to a nearby tree in order to find the
 * vampiric moss required to do the calian sup. guru quest. The timber,
 * however, will break if any object weighing more than 100kg enters,
 * or if there is a total weight or more than 150kg on the timber.
 *
 * Khail - Feb 13/97
 */
#pragma strict_types

#include "defs.h"
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>

inherit STDROOM;

int broken;

/*
 * Function name: create_room
 * Description  : Turns this object into a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_room()
{
    set_short("out on a timber hanging over a dead " +
        "forest");
    set_long("You are hanging onto a long timber " +
        "that's jutting out of the end of a ruined " +
        "tower, hanging over thin air beside the " +
        "top of a tree in a dead forest, in the " +
        "northern parts of the island." +
        "\n\n"); 
    add_item(({"forest","trees", "dead forest", "dead trees"}),
        "It looks " +
        "like this forest is growing, or was growing. " +
        "in the bottom of a crater-like ravine here.\n");
    add_item(({"timber"}),
        "The timber itself doesn't look too healthy, " +
        "making you anxious to be on your way, " +
        "preferably back into the tower rather than " +
        "straight down, which is a long drop.\n");
    add_item(({"tree","tree-top","tree top"}),
        "The " +
        "timber hangs particularly close to a single " +
        "tree top, there's a possibility you could " +
        "jump to it, if you're really careful.\n");

    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_exit(RUIN + "ntower4", "south");
}

/*
 * Function name: query_broken
 * Description  : Returns whether the timber is broken or not.
 * Arguments    : n/a
 * Returns      : 0 - Timber isn't broken.
 *                1 - Timber is broken.
 */
public int
query_broken()
{
    return broken;
}

/*
 * Function name: set_broken
 * Description  : Sets the timber's broken variable.
 * Arguments    : 0 - 'repair' timber.
 *                1 - 'break' timber.
 * Returns      : n/a
 */
public void
set_broken(int i)
{
    broken=i;
}

/*
 * Function name: check_break
 * Description  : Decides if the branch will break under the weight of
 *                the object to test.
 * Arguments    : ob - Object pointer of object to test.
 * Returns      : Nothing if called from this object, otherwise
 *                the result of the test.
 */
public mixed
check_break(object ob)
{
    object *live,
           *dead;
    int i,
        dam;

  /* It's already broken. */
    if (broken)
        return;

  /* Won't break under the weight of a ghost. */
    if (ob->query_ghost())
        return;

  /* Won't break if ob weighs less than 100kg and there's less */
  /* than 150kg here already. */
    if (ob->query_prop(OBJ_I_WEIGHT) < 100000 &&
        TO->query_prop(OBJ_I_WEIGHT) < 150000)
        return;

  /* Otherwise, it'll break if ob enters this room. */
    if (TO != environment(ob))
        return "The timber looks like it would probably break " +
            "beneath your weight.\n";

    tell_room(TO, "Suddenly, the timber breaks! Your entire life " +
        "flashes before your eyes, as you plumment down...down..." +
        "down...\n");

    dead = all_inventory(TO);
    live = FILTER_LIVE(dead);
    dead -= live;

    (RAVINE + "ledge")->load_me();
    if (live && pointerp(live) && sizeof(live))
    {
        live->move_living("M", RAVINE + "ledge", 1, 0);
        tell_room(find_object(RAVINE + "ledge"), "Suddenly, " +
            COMPOSITE_LIVE(live) +
            (sizeof(live) > 1 ? " crash" : " crashes") + 
            " down onto the ground " +
            "with a sickening thud!\n", live);
    }
    if (sizeof(dead))
    {
        dead->move(find_object(RAVINE + "ledge"));
        tell_room(find_object(RAVINE + "ledge"),
            capitalize(COMPOSITE_DEAD(dead)) + " suddenly " +
            (sizeof(dead) > 1 ? "fall" : "falls") + " from " +
            "somewhere above, crashing to the ground.\n", dead);
    }
    for (i = 0; i < sizeof(live); i++)
    {
      
        dam = -3000 + (live[i]->query_base_stat(SS_DEX) * 3) +
            (live[i]->query_skill(SS_ACROBAT) * 4);
        dam = (dam < 0 ? dam : 0);
        live[i]->heal_hp(dam);
        if (live[i]->query_hp() <= 0)
        {
            tell_object(live[i], "As you land, you hear an earth-" +
                "shattering CRACK! from the vicinity of your neck...\n");
            live[i]->do_die(TO);
        }
    }
     
    broken = 1;
}

/*
 * Function name: enter_inv (MASK)
 * Description  : Called when another object enters this inventory.
 * Arguments    : ob - Object entering this inventory.
 *                from - ob's last environment.
 * Returns      : n/a
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob))
        return;

    set_alarm(1.0, 0.0, &check_break(ob));
}

/*
 * Function name: do_jump
 * Description  : Allows players to attempt to jump to a nearby tree.
 * Arguments    : str - Where the player tried to jump.
 * Returns      : 0 - Fail.
 *                1 - Success.
 */
public int
do_jump(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "'in' / 'into' / 'on' / 'onto' / " +
        "'to' [to] [the] 'tree'"))
    {
        return 0;
    }

    if (broken)
    {
        notify_fail("The timber has broken off far to short " +
            "to be able to make the jump to the tree.\n");
        return 0;
    }

    write("Gathering yourself as best as you can on the narrow " +
        "timber, you jump as hard as you can for the tree!\n");
    say(QCTNAME(TP) + " gathers " + TP->query_possessive() + "self " +
        "as best as " + TP->query_pronoun() + " can on the narrow " +
        "timber and propels " + TP->query_possessive() + "self " +
        "into the tree!\n");
    TP->move_living("M", RAVINE + "special", 1, 0);
    say(QCTNAME(TP) + " lands roughly on the branches beside you.\n");
    return 1;
}
    
public void
init()
{
    ::init();
    add_action(do_jump, "jump");
    add_action(do_jump, "leap");
}
