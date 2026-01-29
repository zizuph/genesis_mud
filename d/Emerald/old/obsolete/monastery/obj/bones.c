inherit "/std/object";

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

static int rean;

void
reset_object()
{
    string msg;
    object env, skel;

    env = environment();

    if (env->query_prop(ROOM_M_NO_MAGIC))
    {
        return;
    }

    if (living(env))
    {
        env->catch_msg("The pile of bones suddenly begins to move!\n" +
            "You drop the pile of bones.\n");
        tell_room(environment(env), QCTNAME(env) + 
            " drops a pile of bones.\n", env);
        move(environment(env));
        env = environment();
    }

    if (!env->query_prop(ROOM_I_IS))
    {
        return;
    }

    msg = "The pile of bones suddenly reanimates and stands up!\n";
    tell_room(environment(), ({ msg, msg, "" }));

    setuid();
    seteuid(getuid());
    skel = clone_object(MONASTERY_DIR + "npc/skeleton");
    skel->move(env, 1);
    skel->reanimate(--rean);
    remove_object();
}
    
void
create_object()
{
    set_name("bones");
    set_pname("bones");
    set_adj(({ "pile", "pile of" }));

    set_short("pile of bones");

    set_long("A pile of old, yellowed human bones.\n");
    set_pshort("piles of bones");
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 3000);
    remove_prop(OBJ_I_VALUE);

}

void
reanimate(int times)
{
    if (times > 0)
    {
        rean = times;
        enable_reset();

        /* Register the bones with the clone handler under the skeleton's
         * id.  This makes the clone handler think that the skeleton is
         * still in the game, so it won't clone a new skeleton before this
         * one reanimates.
         */
        setuid();
        seteuid(getuid());
        (MONASTERY_DIR + "clone_handler")->register(this_object(),
            CH_SKELETON_ID);
    }
}
