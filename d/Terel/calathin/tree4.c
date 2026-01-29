/* tree4.c */
/* metaprat - 920702 */
/* Shinto - 12-7-98
 *
 * Jan 2021, Lucius - Modernize
 */
/* 4th level on tree - on branch */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

#define  DIFFICULTY  (TASK_ROUTINE + 172)   /* 23 avg gives 50% success */
#define  DAMAGE      45               /* damage is 5 + 10 * tree height */

public void
create_terel_room()
{
    set_short("Huge pine tree branch");
    set_long(
      "You are standing on a branch, high in the huge pine tree. There's " +
      "enough room to turn around now, and look away from the trunk... " +
      "although the act of doing so makes your head swim with vertigo. " +
      "You can now see east, south and west for miles around: to the west, "+
      "a chain of mountains stretches north towards a valley. A road leads "+
      "from the mountains, eastwards until it reaches the town square below, "+
      "then continues south and east into the distance. "+
      "It crosses a river, to your south, and splits in two; one path " +
      "continuing east, over the horizon, and the other going south into " +
      "the winderness. Looking towards the east, you see an old, ruined " +
      "mansion, near the road. Below you, you can see the square, with " +
      "buildings to the east and south of it. Many houses are visible from " +
      "here, mostly within walking distance of the town square. " +
      "Some fields, with what may be farm houses, occupy the middle distance "+
      "past the houses, on all sides.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "Even though you've climbed a long way, you look upwards, and realise " +
      "that you are less than a tenth of the way to the top of the tree. " +
      "Judging your actual height is difficult, but its roughly seven meters, "+
      "higher than any building in the area, except for the mansion. Down " +
      "below you, you can see the ledge above the window you passed on the " +
      "way up the tree.\n");

    add_item( ({ "branch" }),
      "The branch seems fairly stable, which is not suprising considering " +
      "its huge girth. If you want, you can walk further out to the south, "+
      "but there is little of interest in that direction.\n");

    add_item( ({ "building", "buildings", "town square", "square", "monument",
	"statue", "sign", "town", "silvoria", "mansion", "house", "houses",
	"road", "path" }),
      "You start to look around, but feel your grip start to slip, so you " +
      "turn back,\nvertigo making your head spin.\n");

    add_item( ({ "window" }),
      "You can't see much of the window itself, but you have a glimpse of " +
      "the window\nledge that you used to get up here.\n");

    add_item( ({ "window ledge", "ledge" }),
      "You can see the window ledge below you. It seems to be the only " +
      "way back down from here.\n");

    add_cmd_item(
      ({ "tree", "huge tree", "pine", "huge pine", "huge pine tree", "up" }),
      "climb",
      "What are you going to climb onto? The trunk itself is too icy..\n");

    add_cmd_item(
      ({ "down", "onto ledge", "onto window ledge", "window ledge" }),
      "climb",
      "@@climb_down");

    add_exit(CALATHIN_DIR + "tree4b", "south", 0);
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
	write("You drop down to the ledge below, but overbalance.\nScreaming " +
	  "in terror, you loose your grip, and fall!\n" +
	  "You scream in agony, as your body hits the ground.\n");
	say(QCTNAME(TP) + " tries to climb downwards, but falls.\n");
	TP->reduce_hit_point(DAMAGE / 2);
	TP->move_living("falling, screaming, downwards",
	  CALATHIN_DIR + "square2_1");
	return 1;
    }
    write("You slide down the bark of the tree several feet, until you " +
      "land neatly\non the ledge.\n");
    TP->move_living("slid down onto the ledge",
      CALATHIN_DIR + "tree3");
    return 1;
}
