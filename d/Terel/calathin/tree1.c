/* tree1.c */

/* metaprat - 920702 */
/* Shinto - 12-7-98
 *
 * Jan 2021, Lucius - Modernized
 */
/* First level on tree */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

#define  DIFFICULTY  (TASK_ROUTINE + 225)  /* 30 average gives 50% success */
#define  DAMAGE      15    /* damage is 5 + 10 * tree height */

public void
create_terel_room()
{
    set_short("Huge pine tree, standing on sign bracket");
    set_long(
      "You are perched precariously on an iron bracket of the shop below. " +
      "Quivering with terror, you rest against the slippery trunk of the " +
      "tree, trying to ignore the shaking in your legs, and the sensation " +
      "of the bracket slowly tearing out of the bark.. if you're wise, " +
      "you'll climb down right now. Above you, you can see a window sill, " +
      "probably into the shopkeeper's personal quarters.\n");

    add_item( ({ "sill", "window sill" }),
      "It's a small wooden overhang for the window, so that the rain doesn't " +
      "pour all over the shop customers below. It's a bit shakey, but if " +
      "you're extremely careful, it might not break under your weight.\n");

    add_item( ({ "door" }),
      "You're standing over it! No way you can see it from here.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "At the moment, all you can see is a huge expanse of icy bark about " +
      "six centimeters from the tip of your nose. Glancing up, briefly, " +
      "the tree seems to climb for miles into the sky. Looking downwards, " +
      "you see that you are a couple of meters from the ground, but it feels "+
      "like a lot more.\n");

    add_item( ({ "bracket", "sign" }),
      "You're standing on it!\n");

    add_cmd_item( ({ "bracket", "sign", "onto bracket", "onto sign" }),
      "climb",
      "But you're already standing on it!!\n");

    add_item( ({ "building", "buildings", "town square", "square", "monument",
	"statue", "sign", "town", "silvoria", "mansion", "house", "houses",
	"road", "landscape", "path" }),
      "You start to look around, but feel your grip start to slip, so you " +
      "turn back,\nvertigo making your head spin.\n");

    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

    add_item( ({ "snow" }),
      "There is no snow here at all, its all been trodden into oblivion. " +
      "There is a lot of snow on the trees in the forest, and also in the " +
      "landscape visible from here.\n");

    add_item( ({ "ground", "footprint", "footprints" }),
      "Deeply frozen all year round, the ground never holds footprints.\n");

    add_cmd_item(
      ({ "tree", "huge tree", "pine", "huge pine", "huge pine tree", "up" }),
      "climb",
      "What are you going to climb onto? The trunk itself is too icy.\n");

    add_cmd_item(
      ({ "onto window sill", "window sill", "onto sill", "sill", "window" }),
      "climb",
      "@@climb_tree");

    add_cmd_item(
      ({ "down", "ground", "onto ground" }),
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
	  "You try to grab the window sill, but it is slightly too far " +
	  "away. You slip! You start to fall! Reaching out, you try " +
	  "to grab the sign, but you are too late.\n");
	say(QCTNAME(TP) + " tried to climb onto the window sill, " +
	  "but falls.\n");
	TP->reduce_hit_point(DAMAGE);
	TP->move_living("falling, screaming, downwards",
	  CALATHIN_DIR + "square2_1");
	return 1;
    }
    if (success < 0)
    {
	write(
	  "You try to grab the window sill, but it is slightly too far " +
	  "away. You slip! You start to fall! Reaching out, you grab " +
	  "the sign, and climb back on to the bracket, saving yourself from " +
	  "injury.\n");
	say(QCTNAME(TP) + " tried to climb onto the window sill, " +
	  "but slips.\n");
	return 1;
    }
    if (success < 20)
    {
	write(
	  "You lunge across to the window sill, and grab it with your " +
	  "fingertips. Dragging yourself slowly upwards, you pull yourself " +
	  "onto the sill, and rest for a moment, breathing heavily from the " +
	  "exertion.\n");
	TP->move_living("clambering onto a window sill, above you",
	  CALATHIN_DIR + "tree2");
	return 1;
    }
    write(
      "You reach over to the window sill, and lift yourself up with one " +
      "powerful movement. With a skilled roll, you stand upright, carefully "+
      "keeping your centre of balance close to the trunk of the tree.\n");
    TP->move_living("clambering onto a window sill, above you",
      CALATHIN_DIR + "tree2");
    return 1;
}

int
climb_down()
{
    write(
      "With a sigh of relief, you lower yourself off the bracket, " +
      "and drop to the ground.\n");
    TP->move_living("downwards to the ground",
      CALATHIN_DIR + "square2_1");
    return 1;
}
