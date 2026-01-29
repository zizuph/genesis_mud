/* Training room for Kender race guild */
/* Added new skills to the kender race guild. */
/* Gwyneth, January 20, 2000 */

/* Navarre 25th June 2006, Added add_action for 
 * read book and books.
 */

#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit KEN_OUT;
inherit "/lib/skill_raise";
inherit "/lib/guild_support";

/* Function name : set_up_skills
 * Description   : Initialize the trainer and set the skills we train
*/

void
set_up_skills()
{
    create_skill_raise();
    sk_add_train(SS_WEP_KNIFE, "fight with a knife", "knife", 0, 50 );
    sk_add_train(SS_PICK_POCKET, "borrow things", "borrow", 0, 40 );
    sk_add_train(SS_CLIMB, "climb things", "climb", 0, 50 );
    sk_add_train(SS_LANGUAGE, "speak different languages", "language", 0, 60 );
    sk_add_train(SS_TRACKING, "find tracks", "tracking", 0, 50 );
}

void
reset_kendermore_room()
{
}

public void
create_kendermore_room()
{
    set_short("Behind a giant oak tree in the middle of an ancient forest");
    set_long("You stand behind a giant oak tree in an ancient evergreen " + 
        "forest. The forest seems strangely silent, except for the odd " + 
        "sounds coming occasionally from the branches. Huge roots from " + 
        "the oak claw into the ground " + 
        "around you. Nestled at the base of the tree is a stash of books! " + 
        "It appears as if someone was engaged in reading one of them " + 
        "when he decided to just wander off. A small overgrown path " + 
        "leads around the trunk to the southwest.\n");
    add_item(({"book", "books", "stash", "base"}), "There are five books, " + 
    "each with a different title. Perhaps you could learn something new if you looked more closely at the titles.\n");
    add_item(({"title", "titles"}), 
        "The books are titled:\n" + 
        "All You Ever Wanted to Know about Knife Fighting\n" +
        "How to Find Other People's Lost Goods\n" + 
        "Keep Your Feet on the Ground: A Guide for Climbers\n" + 
        "A Kender's Phrase Book for Foreign Lands\n" + 
        "Tricks of Trailreading\n");
    add_item(({"giant oak tree","oak tree","tree", "trunk"}),
      "A great oak tree rises up before you, its huge limbs " +
      "stretching out above you, filled with a thick and " +
      "lush canopy of green. You think you can hear giggles " +
      "and laughter from within the leaves.\n");
    add_item(({"huge roots","roots","root"}),
      "Huge roots claw into the ground here like great " +
      "burrowing worms. Between two of them is a small opening " +
      "to the north.\n");
    add_item(({"ancient evergreen forest","ancient forest",
        "forest","evergreen forest"}),
      "You stand in the middle of an ancient evergreen forest.\n");

    add_exit(KROOM + "r1", "southwest", 0);

    set_up_skills();

    reset_kendermore_room();
}

int read_book(string args)
{
  if(args != "book" && args != "books")
  {
    notify_fail("Read what?\n");
    return 0;
  }
  TP->catch_tell("You only get to read the books while you train. "+
                 "But you can examine the titles to see what skills "+
                 "you can learn during training.\n");
  return 1;  
}

public void
init()
{
    ::init();
    init_guild_support();
    add_action("gs_meditate", "daydream");
    add_action("read_book", "read");
    init_skill_raise();
}

int
remove_medi_props()
{
    TP->remove_prop(LIVE_I_MEDITATES);
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
}

void
gs_hook_start_meditate()
{
    write("You stare into space, blocking off the world around. " +
        "You let your imagination unfold into wild " +
        "adventures and exotic lands. In such a state, you feel you " +
        "could <estimate> your abilities. As well, you can exert enough " +
        "control over your body to <set> which abilities you want to " +
        "concentrate on. To return to the real world, you can " +
        "<rise>.\n");

    say(QCTNAME(TP) + " finds a relaxing position and closes " + HIS(TP) +
        " eyes. A smile plays over " + HIS(TP) + " lips.\n");
}

int
gs_hook_rise()
{
    write("You gradually bring yourself back to reality. You " +
        "slowly open your eyes, leaving behind your fantasy world, and " +
        "ready to make adventures of your own.\n");

    say(QCTNAME(TP) + " takes a deep breath and slowly opens " + HIS(TP) +
        "eyes. " + HE(TP) + " stands up with a bounce, looking refreshed " +
        "and ready to make some mischief.\n");
}

void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);
    ::leave_inv(ob, to);
}

int
sk_improve(string sk)
{
    int steps;
    string skill, *tmp;

    if (!sk || sscanf(sk, "%d", steps))
        return sk_list(steps);

    tmp = explode(sk, " ");
    if (sscanf(tmp[sizeof(tmp) -1], "%d", steps) == 1 && sizeof(tmp) > 1)
        skill = implode(tmp[0 .. sizeof(tmp) - 2], " ");
    else
    {
        skill = sk;
        steps = 1;
    }

    if ((!TP->query_guild_name_race("The Krynn race guild")) ||
        (TP->query_race_name() != "kender"))
    {
        NF("You quickly lose interest in the books.\n");
        return 0;
    }
    return ::sk_improve(sk);
}

