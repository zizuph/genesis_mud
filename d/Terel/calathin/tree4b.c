/* tree4b.c

   metaprat - 920702
   Shinto 12-7-98

   Jan 2021, Lucius - Modernized.
   Mar 2022: Lilith - updated syntax for the branches/jump
   4th level on tree - on branch
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

#define CLIMB_DIFF      TASK_ROUTINE
#define FIND_DIFF       TASK_DIFFICULT
#define HARD_TO_CLIMB   23    /* gets easier as you climb higher */
#define DAMAGE          45    /* damage is 5 + 10 * tree height */
#define FOUND_BRANCH    "_calathin_branch"
#define CLIMB_LOG       "/d/Terel/log/climbed_sliver"


public void
create_terel_room()
{
    set_short("Huge pine tree, middle branch");
    set_long(
      "You are walking along a branch in a huge pine tree. Nothing " +
      "much is here though: the branch originates from the tree to " +
      "the north, and continues southwards. However, the branch gets " +
      "too thin to walk along, southwards. There are other, smaller "+
	  "branches everwhere, some of them with snow piled on them.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "You can see the tree a bit more clearly from here, and you realise " +
      "just how little you've climbed. Well under a tenth of the way up. " +
      "You're probably about seven meters above the town square here.\n");

    add_item( ({ "branch" }),
      "The branch seems fairly stable here, but is too thin to the " +
      "south to walk along.\n");

    add_item( ({ "building", "buildings", "town square", "square", "monument",
	"statue", "sign", "town", "silvoria", "mansion", "house", "houses",
	"road", "path" }),
      "You start to look around, but feel your grip start to slip, so you " +
      "turn back, vertigo making your head spin.\n");

    add_item(({"thin branch","flimsy branch","thin branch", "thin branches",
    "smaller branches", "branches"}), 
      "@@fbranch");

    add_prop(OBJ_S_SEARCH_FUN, "search_branches");

    add_exit(CALATHIN_DIR + "tree4", "north", 0);
}

public int
climb_up(string str)
{
    int success;

    if (!TP->query_prop(FOUND_BRANCH))
	return 0;
	
/* If the player found the branch, any "climb" str should be enough.
   This syntax is unreasonably obscure.
    if ((str!="flimsy branch") && (str!="thin branch"))
	return 0;
*/
    success = TP->resolve_task(TASK_DIFFICULT,
      ({TS_DEX, SS_CLIMB}));

    if (success < 1)
    {
	write("You attempt to negotiate the flimsy branch, but lose your " +
	  "grip when the branch bends without warning!\n"+
	  "You plummet to the ground below.\n"+
	  "Everything goes black for a moment, as your body hits "+
	  "the ground.\n");
	say(QCTNAME(TP) + " tries to take hold of a branch but falls.\n");
	TP->reduce_hit_point(DAMAGE / 2);
	TP->move_living("falling, screaming, downwards",
	  CALATHIN_DIR + "square2_1");
	return 1;
    }

    write("You adroitly shimmy up the thin branch and climb your way up " +
      "onto a wooden platform that you could not see from below.\n");

    TP->move_living("up a branch", CALATHIN_DIR + "tree_s");
    write_file(CLIMB_LOG, TP->query_name()+" " + ctime(time()) + "\n");
    return 1;
}

string
search_branches(object me, string arg)
{
    int success;

    if (arg != "branches")
	return "";

    success = TP->resolve_task(FIND_DIFF + 100,
      ({TS_INT, TS_DIS, SS_AWARENESS}));

    if (success > 0)
    {
	TP->add_prop(FOUND_BRANCH, 1);
	return " You find a thin branch that looks possible to climb.\n";
    }
    return "Your search reveals nothing special.\n";
}

string
fbranch()
{
    TP->add_prop(FOUND_BRANCH, 1);
    return "There is a thin and flimsy branch that bends up into the "+
        "branches above. It looks like it might be possible to climb "+
        "it, but it sure is a long way down if it breaks.\n";
}

public void
init()
{
    ::init();
    add_action(climb_up, "climb");
}

