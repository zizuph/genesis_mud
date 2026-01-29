/*
 * Unconciousness for overdosing on capanella herb.
 * Finwe, March 2009
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit "/std/paralyze";

// out for 4 min + random 60 second
#define PASSOUT_TIME    240 + random(60)
void
create_paralyze()
{
    set_name("_capanella_herb__paralyze_");
    set_remove_time(PASSOUT_TIME);
    set_stop_message("\nYou regain consciousness.\n\n");
    set_fail_message("You passed out after eating too many herbs.\n");
    set_stop_verb(0);   /* No command to stop paralyze! */
    set_stop_object(0); /* Use the messages set above   */
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    env->add_stun();
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    env->remove_stun();
}
