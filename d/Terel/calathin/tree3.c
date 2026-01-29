/* tree3.c */
/* metaprat - 920702 */
/* Shinto - 12-7-98
 *
 * Jan 2021, Lucius - Modernize
 * Mar 2022, Lilith - added more syntax options for the jump
 */
/* Third level on tree - on ledge above window */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

#define  DIFFICULTY  (TASK_ROUTINE + 188)   /* 25 avg gives 50% success */
#define  DAMAGE      35               /* damage is 5 + 10 * tree height */

public void
create_terel_room()
{
    set_short("Huge pine tree, standing on ledge above window");
    set_long(
      "You are standing on a wooden ledge, above a window on the huge tree. "+
      "The wind is blowing coldly against you, and you shiver, not only " +
      "from the temperature, but also from the fearsome height you are " +
      "above the ground. Just above you is a branch, but that is all " +
      "you can see, while you are facing towards the trunk of the tree. " +
      "There is still not enough space to turn however.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "At the moment, all you can see is a huge expanse of icy bark, and " +
      "a branch a couple of meters above you. The tree seems to climb for " +
      "miles into the sky above you. Looking downwards, you seem to be about "+
      "five meters above the ground, although it feels like a hell of a long "+
      "way down. You are currently standing on a ledge above a window.\n");

    add_item( ({ "branch" }),
      "The branch is thick enough to support your weight... but it's beyond " +
      "the reach of your hands. If you're willing to jump up to it, you " +
      "may be able to grab hold, but if you miss the branch, you could be " +
      "badly hurt by the fall.\n");

    add_item( ({ "building", "buildings", "town square", "square", "monument",
	"statue", "sign", "town", "silvoria", "mansion", "house", "houses",
	"road", "path", "landscape" }),
      "You start to look around, but feel your grip start to slip, so you " +
      "turn back,\nvertigo making your head spin.\n");

    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "the air.\n");

    add_item( ({ "window" }),
      "You can't see much of the window itself, but you have a glimpse of " +
      "the window\nsill that you used to get up here.\n");

    add_item( ({ "window sill", "sill" }),
      "It seems like an amazingly small target to drop onto, particularly\n" +
      "since you will have to do it without looking.\n");

    add_item( ({ "bracket", "iron bracket" }),
      "The bracket is the only possible foothold on the way down, unless you "+
      "jump\nall that distance...\n");

    add_item( ({ "window ledge", "ledge" }),
      "You're standing on a wooden ledge, above the window. It seems " +
      "stable enough,\nas long as you don't make any sudden movements.\n");

    add_item( ({ "snow" }),
      "There is no snow here at all, its all been trodden into oblivion. " +
      "There is a lot of snow on the trees in the forest, and also in the " +
      "landscape visible from here.\n");

    add_item( ({ "ground", "footprint", "footprints" }),
      "Deeply frozen all year round, the ground never holds footprints.\n");

    add_cmd_item(
      ({ "tree", "huge tree", "pine", "huge pine", "huge pine tree", "up" }),
      "climb",
      "What are you going to climb onto? The trunk itself is too icy...\n");

    add_cmd_item(
      ({ "up to branch", "onto branch", "branch", "for branch", "on branch",
         "up for branch", "up onto branch"	  }),
      "jump",
      "@@climb_tree");

    add_cmd_item(
      ({ "onto branch", "branch" }),
      "climb",
      "Its to far to climb onto .. you'll just have to jump up to it, if " +
      "you're\nwilling to risk it.\n");

    add_cmd_item(
      ({ "down", "onto sill", "onto window sill", "window sill" }),
      "climb",
      "@@climb_down");
}

/* climb() taken from /doc/examples/room/sc_room */
int
climb_tree()
{
    int success;

    success = TP->resolve_task(DIFFICULTY,
      ({ SKILL_WEIGHT, 600, SS_CLIMB,
	SKILL_WEIGHT, 150, SS_DEX }) );

    if (success < -20)
    {
	write(
	  "You jump up to the branch, and try to wrap your arms round " +
	  "it. But they slip on the ice! The world starts to spin " +
	  "around you, as you fall to the ground far below.\n");
	say(QCTNAME(TP) + " tries to climb upwards, but falls.\n");
	TP->reduce_hit_point(DAMAGE);
	TP->move_living("falling, screaming, downwards",
	  CALATHIN_DIR + "square2_1");
	return 1;
    }
    if (success < 0)
    {
	write(
	  "You jump up to the branch, and try to wrap your arms round " +
	  "it. But they slip on the ice! You start to fall, but luckily " +
	  "your feet catch on the window ledge.\n");
	say(QCTNAME(TP) + " tries to climb upwards, but slips.\n");
	TP->reduce_hit_point(DAMAGE);
	return 1;
    }
    if (success < 20)
    {
	write(
	  "You jump up to the branch, and wrap your arms around it. Twisting "+
	  "your body, you bring your legs up as well, and roll onto the  " +
	  "top of the branch. You sigh in relief, as you realise you " +
	  "survived this insane risk.\n");
	TP->move_living("jumped up, onto a branch",
	  CALATHIN_DIR + "tree4");
	return 1;
    }
    write(
      "You jump up to the branch, and wrap your arms around it. Twisting "+
      "your body, you bring your legs up as well, and roll onto the  " +
      "top of the branch.\n");
    TP->move_living("jumped up, onto a branch",
      CALATHIN_DIR + "tree4");
    return 1;
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
	write(
	  "You try to drop down to the window sill below, but as you " +
	  "start lowering yourself, you loose your grip, and fall! " +
	  "You scream in agony, as your body hits the ground.\n");
	say(QCTNAME(TP) + " tries to climb downwards, but falls.\n");
	TP->reduce_hit_point(DAMAGE / 2);
	TP->move_living("falling, screaming, downwards",
	  CALATHIN_DIR + "square2_1");
	return 1;
    }
    write("You drop down to the window sill, just catching it with your " +
      "toes.\n");
    TP->move_living("dropped down onto the window sill",
      CALATHIN_DIR + "tree2");
    return 1;
}
