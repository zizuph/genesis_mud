/* tree_s.c */
/*
 * Sliver's new home
 *
 * Goldberry May 2002
 *
 * Jan 2021, Lucius - Modernize
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

#define  DIFFICULTY  (TASK_ROUTINE + 172)   /* 23 avg gives 50% success */
#define  DAMAGE      55               /* damage is 5 + 10 * tree height */


public void
create_terel_room()
{
    set_short("A small platform");
    set_long(
      "You are on a sturdy wooden platform, high up in the tree. "+
      "It is quite well concealed by the branches surrounding it.\n");

    add_item( ({ "huge tree", "pine", "huge pine", "tree" }),
      "Even though you've climbed a long way, you look upwards, and realise " +
      "that you are less than a tenth of the way to the top of the tree.\n");

    add_item( ({ "branches" }),
      "The platform is surrounded on all sides by healthy pine branches. "+
      "In one spot the branches are a bit thinner, with a rather flimsy-"+
      "looking branch shooting up through them.\n");

    add_item( ({ "branch", "flimsy branch" }),
      "A thin and whippy little branch. You wonder hor you managed to " +
      "climb up it without breaking it. It appears to be the only way "+
      "back down.\n");

    add_cmd_item(
      ({ "tree", "huge tree", "pine", "huge pine", "huge pine tree", "up" }),
      "climb",
      "There doesn't seem to be any safe way of climbing any higher.\n");

    add_cmd_item(
      ({ "down", "down branch", "down flimsy branch" }),
      "climb",
      "@@climb_down");

    add_npc(CALATHIN_DIR + "npc/sliver");
}

int
climb_down()
{
    int success;

    success = TP->resolve_task((DIFFICULTY - 80),
      ({ SKILL_WEIGHT, 600, SS_CLIMB,
	SKILL_WEIGHT, 150, SS_DEX }) );

    if (success < 0)
    {
	write("You slip while climbing down to the branch below!\n" +
	  "In terror, you loose your grip, and fall!\n" +
	  "You scream in agony, as your body hits the ground.\n");
	say(QCTNAME(TP) + " tries to climb downwards, but falls.\n");
	TP->reduce_hit_point(DAMAGE / 2);
	TP->move_living("falling, screaming, downwards",
	  CALATHIN_DIR + "square2_1");
	return 1;
    }
    write("You slide down the flimsy-looking branch until you reach the "+
      "branch below.\n");
    TP->move_living("slid down the branch", CALATHIN_DIR + "tree4b");
    return 1;
}
