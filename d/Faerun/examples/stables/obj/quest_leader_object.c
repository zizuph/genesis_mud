/*
 *
 * Steed's object for leaders
 *
 *Palmer, December 2002
 *
 *
 */

inherit "/d/Genesis/steed/new/leader_object.c";
inherit "/lib/commands";


#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include "/d/Shire/sys/defs.h"
#include "../bree_stables.h"

/* Function prototypes */
int destruct_horse();

void
enter_env(object ob, object from)
{
    ::enter_env(ob, from);
    add_action(destruct_horse, "hdestruct");
}


int
destruct_horse()
{
    object steed;
    steed = TO->query_steed();
    steed->remove_object();
    return 1;

}
