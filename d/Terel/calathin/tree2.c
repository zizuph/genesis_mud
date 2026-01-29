/* tree2.c */

/* metaprat - 920702 */
/* Shinto - 12-7-98
 *
 * Jan 2021, Lucius - Modernized
 */
/* First level on tree - possible entry to living quarters of shop */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

#define  DIFFICULTY  (TASK_ROUTINE + 200)  /* 27 avg gives 50% success */
#define  DAMAGE      25              /* damage is 5 + 10 * tree height */

public void
create_terel_room()
{
    set_short("Huge pine tree, cowering on window sill");
    set_long(
      "You are standing on an icy window sill, about three and a half meters "+
      "above the ground. Immediately to the north (in fact, several " +

      "centimeters from your nose), is a locked and barred window. " +
      "The window sill seems more stable than the sign's bracket, so you " +
      "are less terrified than you were earlier. However, the sill is only "+
      "a few centimeters wide, and you can't move around much. A branch " +
      "meters above you is the only thing that relieves the monotony.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "At the moment, all you can see is a huge expanse of icy bark, and " +
      "a branch a few meters above you. The tree seems to climb for miles " +
      "into the sky above you. Looking downwards, you seem to be roughly " +
      "three and a half meters above the ground, but it looks a long way" +
      ".... A couple of meters below, a sign blows backwards and forwards, " +
      "making a rusty creaking noise in the wind.\n");

    add_item( ({ "building", "buildings", "town square", "square", "monument",
	"statue", "sign", "town", "silvoria", "mansion", "house", "houses",
	"road", "path" }),
      "You start to look around, but feel your grip start to slip, so you " +
      "turn back,\nvertigo making your head spin.\n");

    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

    add_item( ({ "sign" }),
      "The sign is supported by an iron bracket.\n");

    add_item( ({ "bracket", "iron bracket" }),
      "The bracket is the only possible foothold on the way down, unless you "+
      "jump\nall that distance...\n");

    add_item( ({ "snow" }),
      "There is no snow here at all, its all been trodden into oblivion. " +
      "There is a lot of snow on the trees in the forest, and also in the " +
      "landscape visible from here.\n");

    add_item( ({ "ground", "footprint", "footprints" }),
      "Deeply frozen all year round, the ground never holds footprints.\n");

    add_item( ({ "window" }),
      "Its a fairly large locked and barred window. " +
      "Above it, a solid wooden ledge keeps the rain from splashing against "+
      "it, and below is the sill that you are standing on.\n");

    add_cmd_item( ({ "window" }),
      ({ "open", "unlock", "break" }),
      "Hey, the thing is locked and barred! Forget it..\n");


    add_cmd_item(
      ({ "tree", "huge tree", "pine", "huge pine", "huge pine tree", "up" }),
      "climb",
      "What are you going to climb onto? The trunk itself is too icy...\n");

    add_item( ({ "branch" }),
      "Its a thick branch, about 3 meters above you.\n");

    add_cmd_item(
      ({ "onto branch", "branch" }),
      "climb",
      "Its too far above you.\n");

    add_item( ({ "ledge", "wooden ledge" }),
      "Basically a wooden overhang above the window, designed to keep the "+
      "rain from splashing the customers below. It looks sturdy enough " +
      "to stand on, if you're careful.\n");

    add_cmd_item(
      ({ "onto top of window", "onto ledge", "ledge" }),
      "climb",
      "@@climb_tree");

    add_cmd_item(
      ({ "down", "onto sign", "onto bracket", "sign", "bracket" }),
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
	write("You try to grab the ledge, but as you do so, your grip on " +
	  "the window sill\nfails! You start falling.. ARGH!\n");
	say(QCTNAME(TP) + " tries to climb upwards, but falls.\n");
	TP->reduce_hit_point(DAMAGE);
	TP->move_living("falling, screaming, downwards",
	  CALATHIN_DIR + "square2_1");
	return 1;
    }
    if (success < 0)
    {
	write("You try to grab the ledge, but miss. You start to fall... " +
	  "but grab hold\njust in time. Lucky!\n");
	say(QCTNAME(TP) + " tries to climb upwards, but slips.\n");
	return 1;
    }
    if (success < 20)
    {
	write(
	  "You grab onto the ledge, and pull yourself up with sheer brute " +
	  "force. Hooking a leg onto it, you balance and stand upright. " +
	  "You're forced to lean against the trunk for a moment, as your " +
	  "aching muscles shudder from the effort.\n");
	TP->move_living("climbing upwards, onto a ledge",
	  CALATHIN_DIR + "tree3");
	return 1;
    }
    write(
      "You grab onto the ledge, and lift yourself up with a graceful " +
      "movement, rolling your body onto it, and upright at the same " +
      "time.\n");
    TP->move_living("climbing upwards, onto a ledge",
      CALATHIN_DIR + "tree3");
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
	  "You lower yourself down to the bracket, but as you drop the " +
	  "last meter, a gust of wind blows you! You're falling! " +
	  "Pain shoots through your abused body, as you hit the ground.\n");
	say(QCTNAME(TP) + " tries to climb downwards, but falls.\n");
	TP->reduce_hit_point(DAMAGE / 2);
	TP->move_living("falling, screaming, downwards",
	  CALATHIN_DIR + "square2_1");
	return 1;
    }
    write(
      "You lower yourself down to the bracket, dropping the last meter. " +
      "It shudders under the sudden pressure, but holds, and you sigh " +
      "in relief.\n");
    TP->move_living("climbing downwards, onto a sign's bracket",
      CALATHIN_DIR + "tree1");
    return 1;
}
