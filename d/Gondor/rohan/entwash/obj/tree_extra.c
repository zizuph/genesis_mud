#include <macros.h>
#include "/d/Gondor/defs.h"

#define ENT_I_BROKE_BRANCH		"_ent_i_broke_branch"

int
break_branch(string str)
{
    string what;
    object  branch = clone_object(ENTWASH_DIR+"obj/willow_branch");

    if (!strlen(str))
    {
        NFN("Break what?");
        return 0;
    }

    if (!parse_command(str, ({ }), "[off] [a] 'branch' [off] [from] [the] 'tree'"))
    {
        NFN("Perhaps you wish to break a branch off from the tree?");
        return 0;
    }

    if (TP->query_prop(ENT_I_BROKE_BRANCH))
    {
        NFN("You seem to have already broken off the only branch"
          + " within reach.");
        return 0;
    }

    write("You break off the only branch which is low enough to"
      + " grasp.\n");
    tell_room(environment(TP), QCTNAME(TP)+" breaks off a low lying"
      + " branch from the tree.\n", TP);
    branch->move(TP);
    TP->add_prop(ENT_I_BROKE_BRANCH, 1);

    return 1;
}
